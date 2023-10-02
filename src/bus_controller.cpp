//
// Bus controller: implement the required address map.
// This module manages instructon & data bus. It has 2 target ports,
// cpu_instr_socket and cpu_data_socket that receives accesses from CPU and
// has 7 initiator ports to access ROM, SRAM, Flash memory and peripherals.
//
//                      -------------------
//                      |       fetch/read|<--- rom_socket
// cpu_instr_socket <---|fetch   fetch/r/w|<--> sram_socket
//                      |       fetch/read|<--- flash_socket
//                      |              r/w|<--> periph1_socket
//                      |              r/w|<--> periph2_socket
//                      |              r/w|<--> periph3_socket
//  cpu_data_socket <-->|r/w           r/w|<--> periph4_socket
//                      |              r/w|<--> periph5_socket
//                      |              r/w|<--> periph6_socket
//                      -------------------
//
#include "bus_controller.h"

Bus_Controller::Bus_Controller(sc_core::sc_module_name const name) : sc_module(name)
{
    cpu_instr_socket.register_b_transport(this, &Bus_Controller::b_transport_instr);

    cpu_data_socket.register_b_transport(this, &Bus_Controller::b_transport_data);
    cpu_data_socket.register_transport_dbg(this, &Bus_Controller::transport_dbg);
}

void Bus_Controller::sram_bind(tlm_utils::simple_target_socket<Memory> &socket, unsigned base_addr, unsigned last_addr)
{
    sram_base = base_addr;
    sram_limit = last_addr + 1;
    sram_socket.bind(socket);
}

void Bus_Controller::rom_bind(tlm_utils::simple_target_socket<Memory> &socket, unsigned base_addr, unsigned last_addr)
{
    rom_base = base_addr;
    rom_limit = last_addr + 1;
    rom_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>("rom");
    rom_socket->bind(socket);
}

void Bus_Controller::flash_bind(tlm_utils::simple_target_socket<Memory> &socket, unsigned base_addr, unsigned last_addr)
{
    flash_base = base_addr;
    flash_limit = last_addr + 1;
    flash_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>("flash");
    flash_socket->bind(socket);
}

void Bus_Controller::periph1_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                                  unsigned base_addr, unsigned last_addr, const std::string &name)
{
    periph1_base = base_addr;
    periph1_limit = last_addr + 1;
    periph1_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>(name.c_str());
    periph1_socket->bind(socket);
}

void Bus_Controller::periph2_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                                  unsigned base_addr, unsigned last_addr, const std::string &name)
{
    periph2_base = base_addr;
    periph2_limit = last_addr + 1;
    periph2_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>(name.c_str());
    periph2_socket->bind(socket);
}

void Bus_Controller::periph3_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                                  unsigned base_addr, unsigned last_addr, const std::string &name)
{
    periph3_base = base_addr;
    periph3_limit = last_addr + 1;
    periph3_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>(name.c_str());
    periph3_socket->bind(socket);
}

void Bus_Controller::periph4_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                                  unsigned base_addr, unsigned last_addr, const std::string &name)
{
    periph4_base = base_addr;
    periph4_limit = last_addr + 1;
    periph4_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>(name.c_str());
    periph4_socket->bind(socket);
}

void Bus_Controller::periph5_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                                  unsigned base_addr, unsigned last_addr, const std::string &name)
{
    periph5_base = base_addr;
    periph5_limit = last_addr + 1;
    periph5_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>(name.c_str());
    periph5_socket->bind(socket);
}

void Bus_Controller::periph6_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                                  unsigned base_addr, unsigned last_addr, const std::string &name)
{
    periph6_base = base_addr;
    periph6_limit = last_addr + 1;
    periph6_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>(name.c_str());
    periph6_socket->bind(socket);
}

void Bus_Controller::timer_bind(tlm_utils::simple_target_socket<Timer> &socket)
{
    timer_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>("timer");
    timer_socket->bind(socket);
}

//
// Fetch request.
//
void Bus_Controller::b_transport_instr(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay)
{
    tlm::tlm_command cmd = trans.get_command();
    uint32_t addr        = trans.get_address();

    if (cmd != tlm::TLM_READ_COMMAND) {
        // Write requests should not happen with fetch.
        Log::err() << "Fetch write at 0x" << std::hex << std::setw(8) << std::setfill('0') << addr
                   << std::endl;
        SC_REPORT_ERROR("Fetch", "Write");
    }
    trans.set_gp_option(tlm::TLM_MIN_PAYLOAD); // Flag of fetch request

    // Internal SRAM.
    if (addr >= sram_base && addr < sram_limit) {
        trans.set_address(addr - sram_base);
        sram_socket->b_transport(trans, delay);
        return;
    }

    // Internal ROM.
    if (addr >= rom_base && addr < rom_limit) {
        trans.set_address(addr - rom_base);
        (*rom_socket)->b_transport(trans, delay);
        return;
    }

    // Flash memory (XIP).
    if (addr >= flash_base && addr < flash_limit) {
        trans.set_address(addr - flash_base);
        (*flash_socket)->b_transport(trans, delay);
        return;
    }

    // Fetch exception.
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
}

//
// Load/store request.
//
void Bus_Controller::b_transport_data(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay)
{
    uint32_t addr = trans.get_address();

    trans.set_gp_option(tlm::TLM_FULL_PAYLOAD); // Flag of data request

    // Internal SRAM.
    if (addr >= sram_base && addr < sram_limit) {
        trans.set_address(addr - sram_base);
        sram_socket->b_transport(trans, delay);
        return;
    }

    // Internal ROM.
    if (addr >= rom_base && addr < rom_limit) {
        trans.set_address(addr - rom_base);
        (*rom_socket)->b_transport(trans, delay);
        return;
    }

    // Flash memory (XIP).
    if (addr >= flash_base && addr < flash_limit) {
        trans.set_address(addr - flash_base);
        (*flash_socket)->b_transport(trans, delay);
        return;
    }

    //
    // Peripherals.
    //
    uint32_t addr_base = addr & ~0x3000; // ignore set/clr/xor bits

    if (addr_base >= periph1_base && addr_base < periph1_limit) {
        trans.set_address(addr - periph1_base);
        (*periph1_socket)->b_transport(trans, delay);
        return;
    }
    if (addr_base >= periph2_base && addr_base < periph2_limit) {
        trans.set_address(addr - periph2_base);
        (*periph2_socket)->b_transport(trans, delay);
        return;
    }
    if (addr_base >= periph3_base && addr_base < periph3_limit) {
        trans.set_address(addr - periph3_base);
        (*periph3_socket)->b_transport(trans, delay);
        return;
    }
    if (addr_base >= periph4_base && addr_base < periph4_limit) {
        trans.set_address(addr - periph4_base);
        (*periph4_socket)->b_transport(trans, delay);
        return;
    }
    if (addr_base >= periph5_base && addr_base < periph5_limit) {
        trans.set_address(addr - periph5_base);
        (*periph5_socket)->b_transport(trans, delay);
        return;
    }
    if (addr_base >= periph6_base && addr_base < periph6_limit) {
        trans.set_address(addr - periph6_base);
        (*periph6_socket)->b_transport(trans, delay);
        return;
    }

    // Load/store exception.
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
}

//
// Debug request.
//
unsigned Bus_Controller::transport_dbg(tlm::tlm_generic_payload &trans)
{
    uint32_t addr = trans.get_address();

    // Internal SRAM.
    if (addr >= sram_base && addr < sram_limit) {
        trans.set_address(addr - sram_base);
        return sram_socket->transport_dbg(trans);
    }

    // Internal ROM.
    if (addr >= rom_base && addr < rom_limit) {
        trans.set_address(addr - rom_base);
        return (*rom_socket)->transport_dbg(trans);
    }

    // Flash memory (XIP).
    if (addr >= flash_base && addr < flash_limit) {
        trans.set_address(addr - flash_base);
        return (*flash_socket)->transport_dbg(trans);
    }

    // Nothing to read/write.
    return 0;
}

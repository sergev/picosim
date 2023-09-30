//
// Bus controller: implement the required address map.
// This module manages instructon & data bus. It has 2 target ports,
// cpu_instr_socket and cpu_data_socket that receives accesses from CPU and
// has 7 initiator ports to access ROM, SRAM, Flash memory and peripherals.
//
//                      -------------------
//                      |                 |
// cpu_instr_socket <---|fetch            |
//                      |       fetch/read|<--- rom_socket
//                      |        fetch/r/w|<--> sram_socket
//                      |       fetch/read|<--- flash_socket
//                      |              r/w|<--> periph_socket
//  cpu_data_socket <-->|r/w              |
//                      |                 |
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

void Bus_Controller::periph_bind(tlm_utils::simple_target_socket<Peripherals> &socket, unsigned base_addr, unsigned last_addr)
{
    periph_base = base_addr;
    periph_limit = last_addr + 1;
    periph_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>("periph");
    periph_socket->bind(socket);
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

    // Peripherals.
    if (addr >= periph_base && addr < periph_limit) {
        trans.set_address(addr - periph_base);
        (*periph_socket)->b_transport(trans, delay);
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

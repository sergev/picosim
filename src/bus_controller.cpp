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
//  cpu_data_socket <-->|r/w           r/w|<--> periph_socket
//                      |                 |
//                      -------------------
//
#include "bus_controller.h"

#include <iomanip>

Bus_Controller::Bus_Controller(sc_core::sc_module_name const name, const std::string &config)
    : sc_module(name)
{
    cpu_instr_socket.register_b_transport(this, &Bus_Controller::b_transport_instr);

    cpu_data_socket.register_b_transport(this, &Bus_Controller::b_transport_data);
    cpu_data_socket.register_transport_dbg(this, &Bus_Controller::transport_dbg);

    if (config == "linux") {
        // Map SRAM to Linux address range.
        linux_mode = true;
    }
}

void Bus_Controller::sram_bind(tlm_utils::simple_target_socket<Memory> &socket)
{
    sram_socket.bind(socket);
}

void Bus_Controller::rom_bind(tlm_utils::simple_target_socket<Memory> &socket)
{
    rom_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>("rom");
    rom_socket->bind(socket);
}

void Bus_Controller::flash_bind(tlm_utils::simple_target_socket<Memory> &socket)
{
    flash_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>("flash");
    flash_socket->bind(socket);
}

void Bus_Controller::periph_bind(tlm_utils::simple_target_socket<Peripherals> &socket)
{
    periph_socket = std::make_unique<tlm_utils::simple_initiator_socket<Bus_Controller>>("periph");
    periph_socket->bind(socket);
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

    if (linux_mode) {
        // Internal SRAM.
        if (addr >= LINUX_SRAM_BASE && addr <= LINUX_SRAM_LAST) {
            trans.set_address(addr - LINUX_SRAM_BASE);
            sram_socket->b_transport(trans, delay);
            return;
        }
    } else {
        // Internal SRAM.
        if (addr >= RP2040_SRAM_BASE && addr <= RP2040_SRAM_LAST) {
            trans.set_address(addr - RP2040_SRAM_BASE);
            sram_socket->b_transport(trans, delay);
            return;
        }

        // Internal ROM.
        if (addr >= RP2040_ROM_BASE && addr <= RP2040_ROM_LAST) {
            trans.set_address(addr - RP2040_ROM_BASE);
            (*rom_socket)->b_transport(trans, delay);
            return;
        }

        // Flash memory (XIP).
        if (addr >= RP2040_FLASH_BASE && addr <= RP2040_FLASH_LAST) {
            trans.set_address(addr - RP2040_FLASH_BASE);
            (*flash_socket)->b_transport(trans, delay);
            return;
        }
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

    if (linux_mode) {
        // Internal SRAM.
        if (addr >= LINUX_SRAM_BASE && addr <= LINUX_SRAM_LAST) {
            trans.set_address(addr - LINUX_SRAM_BASE);
            sram_socket->b_transport(trans, delay);
            return;
        }
    } else {
        // Internal SRAM.
        if (addr >= RP2040_SRAM_BASE && addr <= RP2040_SRAM_LAST) {
            trans.set_address(addr - RP2040_SRAM_BASE);
            sram_socket->b_transport(trans, delay);
            return;
        }

        // Internal ROM.
        if (addr >= RP2040_ROM_BASE && addr <= RP2040_ROM_LAST) {
            trans.set_address(addr - RP2040_ROM_BASE);
            (*rom_socket)->b_transport(trans, delay);
            return;
        }

        // Flash memory (XIP).
        if (addr >= RP2040_FLASH_BASE && addr <= RP2040_FLASH_LAST) {
            trans.set_address(addr - RP2040_FLASH_BASE);
            (*flash_socket)->b_transport(trans, delay);
            return;
        }

        //
        // Peripherals.
        //
        uint32_t addr_base = addr & ~0x3000; // ignore set/clr/xor bits

        if ((addr_base >= RP2040_SYSINFO_BASE && addr_base <= RP2040_SYSINFO_LAST) || // sysinfo
            (addr_base >= RP2040_AHB_BASE && addr_base <= RP2040_AHB_LAST) ||         // ahb
            (addr_base >= RP2040_SIO_BASE && addr_base <= RP2040_SIO_LAST) ||         // sio
            (addr_base >= RP2040_SSI_BASE && addr_base <= RP2040_SSI_LAST) ||         // ssi
            (addr_base >= RP2040_PPB_BASE && addr_base <= RP2040_PPB_LAST) ||         // ppb
            (addr_base >= RP2040_XIP_BASE && addr_base <= RP2040_XIP_LAST)) {         // xip
            trans.set_address(addr);
            (*periph_socket)->b_transport(trans, delay);
            return;
        }
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

    if (linux_mode) {
        // Internal SRAM.
        if (addr >= LINUX_SRAM_BASE && addr <= LINUX_SRAM_LAST) {
            trans.set_address(addr - LINUX_SRAM_BASE);
            return sram_socket->transport_dbg(trans);
        }
    } else {
        // Internal SRAM.
        if (addr >= RP2040_SRAM_BASE && addr <= RP2040_SRAM_LAST) {
            trans.set_address(addr - RP2040_SRAM_BASE);
            return sram_socket->transport_dbg(trans);
        }

        // Internal ROM.
        if (addr >= RP2040_ROM_BASE && addr <= RP2040_ROM_LAST) {
            trans.set_address(addr - RP2040_ROM_BASE);
            return (*rom_socket)->transport_dbg(trans);
        }

        // Flash memory (XIP).
        if (addr >= RP2040_FLASH_BASE && addr <= RP2040_FLASH_LAST) {
            trans.set_address(addr - RP2040_FLASH_BASE);
            return (*flash_socket)->transport_dbg(trans);
        }
    }

    // Nothing to read/write.
    return 0;
}

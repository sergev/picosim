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

    // Internal ROM.
    if (addr >= ADDR_ROM_START && addr <= ADDR_ROM_LAST) {
        trans.set_address(addr - ADDR_ROM_START);
        rom_socket->b_transport(trans, delay);
        return;
    }

    // Flash memory (XIP).
    if (addr >= ADDR_FLASH_START && addr <= ADDR_FLASH_LAST) {
        trans.set_address(addr - ADDR_FLASH_START);
        flash_socket->b_transport(trans, delay);
        return;
    }

    // Internal SRAM.
    if (addr >= ADDR_SRAM_START && addr <= ADDR_SRAM_LAST) {
        trans.set_address(addr - ADDR_SRAM_START);
        sram_socket->b_transport(trans, delay);
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

    // Internal ROM.
    if (addr >= ADDR_ROM_START && addr <= ADDR_ROM_LAST) {
        trans.set_address(addr - ADDR_ROM_START);
        rom_socket->b_transport(trans, delay);
        return;
    }

    // Flash memory (XIP).
    if (addr >= ADDR_FLASH_START && addr <= ADDR_FLASH_LAST) {
        trans.set_address(addr - ADDR_FLASH_START);
        flash_socket->b_transport(trans, delay);
        return;
    }

    // Internal SRAM.
    if (addr >= ADDR_SRAM_START && addr <= ADDR_SRAM_LAST) {
        trans.set_address(addr - ADDR_SRAM_START);
        sram_socket->b_transport(trans, delay);
        return;
    }

    // Peripherals.
    if (addr >= ADDR_PERIPH_START && addr <= ADDR_PERIPH_LAST) {
        trans.set_address(addr - ADDR_PERIPH_START);
        periph_socket->b_transport(trans, delay);
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

    // Internal ROM.
    if (addr >= ADDR_ROM_START && addr <= ADDR_ROM_LAST) {
        trans.set_address(addr - ADDR_ROM_START);
        return rom_socket->transport_dbg(trans);
    }

    // Flash memory (XIP).
    if (addr >= ADDR_FLASH_START && addr <= ADDR_FLASH_LAST) {
        trans.set_address(addr - ADDR_FLASH_START);
        return flash_socket->transport_dbg(trans);
    }

    // Internal SRAM.
    if (addr >= ADDR_SRAM_START && addr <= ADDR_SRAM_LAST) {
        trans.set_address(addr - ADDR_SRAM_START);
        return sram_socket->transport_dbg(trans);
    }

    // Nothing to read/write.
    return 0;
}

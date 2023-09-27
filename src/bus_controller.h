//
// Bus controller
//
// This module manages instructon & data bus. It has 2 target ports,
// cpu_instr_socket and cpu_data_socket that receives accesses from CPU and
// has 7 initiator ports to access ROM, SRAM, Flash memory and peripherals.
//
#ifndef __BUSCTRL_H__
#define __BUSCTRL_H__

#include <fstream>
#include <iostream>

#include "log.h"
#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

//
// Address Map from RP2040 Datasheet, page 24.
//
#define ADDR_ROM_START 0x00000000 // ROM_BASE
#define ADDR_ROM_LAST  0x00003fff // 16 kbytes

#define ADDR_FLASH_START 0x10000000 // XIP_BASE
#define ADDR_FLASH_LAST  0x101fffff // 2 Mbytes

#if 1
#define ADDR_SRAM_START 0x00008000 // skip 32 kbytes - newlib binary
#define ADDR_SRAM_LAST  0x0007ffff // 512 kbytes
#else
#define ADDR_SRAM_START 0x20000000 // SRAM_BASE
#define ADDR_SRAM_LAST  0x20041fff // 256 + 8 kbytes
#endif

#define ADDR_PERIPH_START 0x40000000 // SYSINFO_BASE
#define ADDR_PERIPH_LAST  0x4007ffff // 512 kbytes

class Bus_Controller : public sc_core::sc_module {
public:
    // Incoming fetch requests from CPU.
    tlm_utils::simple_target_socket<Bus_Controller> cpu_instr_socket{ "cpu_instr" };

    // Incoming data loads/stores from CPU.
    tlm_utils::simple_target_socket<Bus_Controller> cpu_data_socket{ "cpu_data" };

    // Outgoing requests to SoC memories and peripherals.
    tlm_utils::simple_initiator_socket<Bus_Controller> rom_socket{ "rom" };
    tlm_utils::simple_initiator_socket<Bus_Controller> flash_socket{ "flash" };
    tlm_utils::simple_initiator_socket<Bus_Controller> sram_socket{ "sram" };
    tlm_utils::simple_initiator_socket<Bus_Controller> periph_socket{ "periph" };
    tlm_utils::simple_initiator_socket<Bus_Controller> timer_socket{ "timer" }; // TODO: remove

    // Constructor.
    explicit Bus_Controller(sc_core::sc_module_name name);

private:
    // Process fetch requests.
    void b_transport_instr(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    // Process load/store requests.
    void b_transport_data(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    // Process debug requests.
    unsigned transport_dbg(tlm::tlm_generic_payload &trans);
};

#endif

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
// According to the technical reference manual, ESP32-C3 microcontroller
// has the following memory regions:
//
// Memory Region        Access          Address Range           Kbytes
// -----------------------------------------------------------------------
// Internal ROM 0       Fetch/Read      4000_0000 - 4003_FFFF   256
// Internal ROM 1       Read only       3FF0_0000 - 3FF1_FFFF   128
//   (mapped twice)     Fetch/Read      4004_0000 - 4005_FFFF   (same)
// Internal SRAM 1      Read/Write      3FC8_0000 - 3FCD_FFFF   384
//   (mapped twice)     Fetch/Read      4038_0000 - 403D_FFFF   (same)
// Flash memory data    Read only       3C00_0000 - 3C7F_FFFF   8192
// Flash memory code    Fetch/Read      4200_0000 - 427F_FFFF   8192
// RTC FAST Memory      Read/Write      5000_0000 - 5000_1FFF   8
// Peripherals          Read/Write      6000_0000 - 600D_0FFF   836
//
// There is also Internal SRAM 0, but it is typically used as I cache,
// invisible to the software, so we don't have to simulate it.
//
#define ADDR_DATA_FLASH_START   0x3c000000  // 8 Mbytes
#define ADDR_DATA_FLASH_LAST    0x3c7fffff

#define ADDR_DATA_SRAM1_START   0x3fc80000  // 384 kbytes
#define ADDR_DATA_SRAM1_LAST    0x3fcdffff

#define ADDR_DATA_ROM1_START    0x3ff00000  // 128 kbytes
#define ADDR_DATA_ROM1_LAST     0x3ff1ffff

#define ADDR_FETCH_ROM0_START   0x40000000  // 256 kbytes
#define ADDR_FETCH_ROM0_LAST    0x4003ffff

#define ADDR_FETCH_ROM1_START   0x40040000  // 128 kbytes
#define ADDR_FETCH_ROM1_LAST    0x4005ffff

#define ADDR_FETCH_SRAM1_START  0x40380000  // 384 kbytes
#define ADDR_FETCH_SRAM1_LAST   0x403dffff

#define ADDR_FETCH_FLASH_START  0x42000000  // 8 Mbytes
#define ADDR_FETCH_FLASH_LAST   0x427fffff

#define ADDR_DATA_RTCMEM_START  0x50000000  // 8 kbytes
#define ADDR_DATA_RTCMEM_LAST   0x50001fff

#define ADDR_DATA_PERIPH_START  0x60000000  // 836 kbytes
#define ADDR_DATA_PERIPH_LAST   0x600d0fff

class Bus_Controller : public sc_core::sc_module {
public:
    // Incoming fetch requests from CPU.
    tlm_utils::simple_target_socket<Bus_Controller> cpu_instr_socket{ "cpu_instr" };

    // Incoming data loads/stores from CPU.
    tlm_utils::simple_target_socket<Bus_Controller> cpu_data_socket{ "cpu_data" };

    // Outgoing requests to SoC memories and peripherals.
    tlm_utils::simple_initiator_socket<Bus_Controller> rom0_socket{ "rom0" };
    tlm_utils::simple_initiator_socket<Bus_Controller> rom1_socket{ "rom1" };
    tlm_utils::simple_initiator_socket<Bus_Controller> sram1_socket{ "sram1" };
    tlm_utils::simple_initiator_socket<Bus_Controller> flash_socket{ "flash" };
    tlm_utils::simple_initiator_socket<Bus_Controller> rtc_mem_socket{ "rtc_mem" };
    tlm_utils::simple_initiator_socket<Bus_Controller> periph_socket{ "periph" };
    tlm_utils::simple_initiator_socket<Bus_Controller> timer_socket{ "timer" }; //TODO: remove

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

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
#define RP2040_ROM_BASE 0x00000000 // ROM_BASE
#define RP2040_ROM_LAST 0x00003fff // 16 kbytes

#define RP2040_FLASH_BASE 0x10000000 // XIP_BASE
#define RP2040_FLASH_LAST 0x101fffff // 2 Mbytes

#define RP2040_XIP_BASE 0x14000000 // XIP_CTRL_BASE
#define RP2040_XIP_LAST 0x1400001f // 32 bytes

#define RP2040_SSI_BASE 0x18000000 // XIP_SSI_BASE
#define RP2040_SSI_LAST 0x180000ff // 256 bytes

#define RP2040_SRAM_BASE 0x20000000 // SRAM_BASE
#define RP2040_SRAM_LAST 0x20041fff // 256 + 8 kbytes

#define RP2040_SYSINFO_BASE 0x40000000 // SYSINFO_BASE
#define RP2040_SYSINFO_LAST 0x4007ffff // 512 kbytes

#define RP2040_AHB_BASE 0x50000000 // DMA_BASE
#define RP2040_AHB_LAST 0x504fffff // 5 Mbytes

#define RP2040_SIO_BASE 0xd0000000 // SIO_BASE
#define RP2040_SIO_LAST 0xd00001ff // 512 bytes

#define RP2040_PPB_BASE 0xe0000000 // PPB_BASE
#define RP2040_PPB_LAST 0xe000ffff // 64 kbytes

//
// Address Map of binaries compiled for Linux with Newlib.
//
#define LINUX_SRAM_BASE 0x00008000 // skip 32 kbytes - newlib binary
#define LINUX_SRAM_LAST  0x0007ffff // 480 kbytes

class Memory;
class Peripherals;
class Timer;

class Bus_Controller : public sc_core::sc_module {
public:
    // Incoming fetch requests from CPU.
    tlm_utils::simple_target_socket<Bus_Controller> cpu_instr_socket{ "cpu_instr" };

    // Incoming data loads/stores from CPU.
    tlm_utils::simple_target_socket<Bus_Controller> cpu_data_socket{ "cpu_data" };

    // Constructor.
    explicit Bus_Controller(sc_core::sc_module_name name, const std::string &config);

    // Bind to outgoing sockets.
    void sram_bind(tlm_utils::simple_target_socket<Memory> &socket);
    void rom_bind(tlm_utils::simple_target_socket<Memory> &socket);
    void flash_bind(tlm_utils::simple_target_socket<Memory> &socket);
    void periph_bind(tlm_utils::simple_target_socket<Peripherals> &socket);
    void timer_bind(tlm_utils::simple_target_socket<Timer> &socket); // TODO: remove

private:
    // Outgoing requests to SoC memories and peripherals.
    tlm_utils::simple_initiator_socket<Bus_Controller> sram_socket{ "sram" };
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> rom_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> flash_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> periph_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> timer_socket;

    // Only SRAM is enabled.
    bool linux_mode{};

    // Process fetch requests.
    void b_transport_instr(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    // Process load/store requests.
    void b_transport_data(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    // Process debug requests.
    unsigned transport_dbg(tlm::tlm_generic_payload &trans);
};

#endif

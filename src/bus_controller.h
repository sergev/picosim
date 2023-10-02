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
    explicit Bus_Controller(sc_core::sc_module_name name);

    // Bind to outgoing sockets.
    void sram_bind(tlm_utils::simple_target_socket<Memory> &socket, unsigned base_addr, unsigned last_addr);
    void rom_bind(tlm_utils::simple_target_socket<Memory> &socket, unsigned base_addr, unsigned last_addr);
    void flash_bind(tlm_utils::simple_target_socket<Memory> &socket, unsigned base_addr, unsigned last_addr);
    void periph1_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                      unsigned base_addr, unsigned last_addr, const std::string &name);
    void periph2_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                      unsigned base_addr, unsigned last_addr, const std::string &name);
    void periph3_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                      unsigned base_addr, unsigned last_addr, const std::string &name);
    void periph4_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                      unsigned base_addr, unsigned last_addr, const std::string &name);
    void periph5_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                      unsigned base_addr, unsigned last_addr, const std::string &name);
    void periph6_bind(tlm_utils::simple_target_socket<Peripherals> &socket,
                      unsigned base_addr, unsigned last_addr, const std::string &name);
    void timer_bind(tlm_utils::simple_target_socket<Timer> &socket); // TODO: remove

private:
    // Outgoing requests to SoC memories and peripherals.
    tlm_utils::simple_initiator_socket<Bus_Controller> sram_socket{ "sram" };
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> rom_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> flash_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> periph1_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> periph2_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> periph3_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> periph4_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> periph5_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> periph6_socket;
    std::unique_ptr<tlm_utils::simple_initiator_socket<Bus_Controller>> timer_socket;

    // Address map.
    unsigned sram_base{}, sram_limit{};
    unsigned rom_base{}, rom_limit{};
    unsigned flash_base{}, flash_limit{};
    unsigned periph1_base{}, periph1_limit{};
    unsigned periph2_base{}, periph2_limit{};
    unsigned periph3_base{}, periph3_limit{};
    unsigned periph4_base{}, periph4_limit{};
    unsigned periph5_base{}, periph5_limit{};
    unsigned periph6_base{}, periph6_limit{};

    // Process fetch requests.
    void b_transport_instr(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    // Process load/store requests.
    void b_transport_data(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    // Process debug requests.
    unsigned transport_dbg(tlm::tlm_generic_payload &trans);
};

#endif

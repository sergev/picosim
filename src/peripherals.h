#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__

#include <fstream>
#include <iostream>
#include <map>

#include "log.h"
#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

class Processor;

/**
 * @brief Basic TLM-2 memory
 */
class Peripherals : public sc_core::sc_module {
public:
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Peripherals> socket{ "socket" };

    // Allocate memory of given size.
    explicit Peripherals(Processor &c, sc_core::sc_module_name const &name);

    // Deallocate.
    ~Peripherals() override;

private:
    // Shadow storage, allocated via calloc().
    uint8_t *mem_sysinfo;
    uint8_t *mem_ahb;
    uint8_t *mem_sio;
    uint8_t *mem_ssi;
    uint8_t *mem_ppb;
    uint8_t *mem_xip;

    // Reference to processor.
    Processor &cpu;

    // Get shadow memory.
    uint32_t &get_shadow(unsigned addr);

    // Latency of the read/write access.
    const sc_core::sc_time LATENCY{ 1, sc_core::SC_NS };

    // Blocking transport method.
    void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);
};
#endif /* __PERIPHERALS_H__ */

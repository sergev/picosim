#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__

#include <fstream>
#include <iostream>
#include <map>

#include "log.h"
#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

class Simulator;

/**
 * @brief Basic TLM-2 memory
 */
class Peripherals : public sc_core::sc_module {
public:
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Peripherals> socket{ "socket" };

    // Allocate memory of given size.
    explicit Peripherals(Simulator &s, sc_core::sc_module_name const &name);

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

    // Reference to simulator.
    Simulator &sim;

    // Get shadow memory.
    uint32_t &get_shadow(unsigned addr);

    // Get register name by address.
    std::string reg_name(unsigned addr);

    // Read peripheral register.
    unsigned periph_read(unsigned addr);

    // Write to a peripheral register.
    // Update reg_name.
    void periph_write(unsigned addr, unsigned val);

    // Latency of the read/write access.
    const sc_core::sc_time LATENCY{ 1, sc_core::SC_NS };

    // Blocking transport method.
    void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    //
    // Peripheral registers.
    //
    unsigned resets_reset_done{};
    unsigned clk_sys_ctrl{};
    unsigned clk_ref_ctrl{};
    unsigned ss_ctrl{};
    unsigned m0plus_vtor{0x10000100};

    unsigned div_dividend{};
    unsigned div_divisor{};
    unsigned div_quotient{};
    unsigned div_remainder{};
    unsigned div_csr{ 1 };
    void div_start(char op);
};
#endif /* __PERIPHERALS_H__ */

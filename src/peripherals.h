#ifndef __PERIPHERALS_H__
#define __PERIPHERALS_H__

#include <fstream>
#include <iostream>
#include <map>

#include "log.h"
#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

/**
 * @brief Basic TLM-2 memory
 */
class Peripherals : public sc_core::sc_module {
public:
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Peripherals> socket{ "socket" };

    // Allocate memory of given size.
    explicit Peripherals(sc_core::sc_module_name const &name, unsigned kbytes);

    // Deallocate.
    ~Peripherals() override;

private:
    // Shadow storage, allocated via calloc().
    uint8_t *mem;

    // Size of the memory in bytes.
    unsigned size_bytes;

    // Get register name by address.
    static std::string reg_name(unsigned addr);

    // Read peripheral register.
    unsigned periph_read(unsigned addr);

    // Write to a peripheral register.
    // Update reg_name.
    void periph_write(unsigned addr, unsigned val);

    // Latency of the read/write access.
    const sc_core::sc_time LATENCY{ 1, sc_core::SC_NS };

    // Blocking transport method.
    void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);
};
#endif /* __PERIPHERALS_H__ */
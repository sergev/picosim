/*!
 \file PhysMemory.h
 \brief Basic TLM-2 memory model
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <fstream>
#include <iostream>

#include "log.h"
#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

/**
 * @brief Basic TLM-2 memory
 */
class Memory : public sc_core::sc_module {
public:
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Memory> socket;

    // Allocate memory of given size.
    explicit Memory(sc_core::sc_module_name const &name, unsigned kbytes);

    // Deallocate.
    ~Memory() override;

    // Make it read only.
    void set_read_only() { is_read_only = true; }

    // Set base address.
    void set_base(unsigned address) { base_address = address; }

private:
    // Memory contents, allocated via calloc().
    uint8_t *mem;

    // Size of the memory in bytes.
    unsigned size_bytes;

    // Base address in memory map.
    unsigned base_address;

    // Latency of the memory access.
    const sc_core::sc_time LATENCY{ 1, sc_core::SC_NS };

    // Whether this memory is read only.
    bool is_read_only{ false };

    // Blocking transport method.
    void b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    // Forward DMI method.
    bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data);

    // Debug transport method.
    unsigned int transport_dbg(tlm::tlm_generic_payload &trans);
};
#endif /* __MEMORY_H__ */

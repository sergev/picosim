/*!
 \file Memory.cpp
 \brief Basic TLM-2 memory model
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later
#include "phys_memory.h"

#include <algorithm>

Memory::Memory(sc_core::sc_module_name const &name, unsigned base_addr, unsigned last_addr)
    : sc_module(name),
      socket("socket"),
      base_address(base_addr),
      size_bytes((last_addr + 1 - base_addr) * 1024)
{
    // Register callbacks for incoming interface method calls
    socket.register_b_transport(this, &Memory::b_transport);
    socket.register_get_direct_mem_ptr(this, &Memory::get_direct_mem_ptr);
    socket.register_transport_dbg(this, &Memory::transport_dbg);

    // Use calloc() to allocate zer-initialized memory efficiently,
    // using OS-specific mechanisms.
    mem = (uint8_t *)calloc(size_bytes, 1);
    if (mem == nullptr) {
        SC_REPORT_ERROR(name, "Cannot allocate memory");
        return;
    }
}

Memory::~Memory()
{
    free(mem);
}

void Memory::b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay)
{
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64 addr   = trans.get_address();
    unsigned char *ptr   = trans.get_data_ptr();
    unsigned int len     = trans.get_data_length();
    bool is_fetch        = trans.get_gp_option() == tlm::TLM_MIN_PAYLOAD;

    if (addr >= size_bytes) {
        trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
        return;
    }

    if (cmd == tlm::TLM_READ_COMMAND) {
        //
        // Read from memory.
        //
        memcpy(ptr, &mem[addr], len);

        if (!is_fetch && Log::is_verbose()) {
            auto &out = Log::out();
            out << std::hex << std::setw(8) << std::setfill('0') << "          Read " << basename()
                << " [" << (addr + base_address) << "] = ";
            switch (len) {
            case 1:
                out << std::setw(2) << *(uint8_t *)ptr;
                break;
            case 2:
                out << std::setw(4) << *(uint16_t *)ptr;
                break;
            case 4:
                out << std::setw(8) << *(uint32_t *)ptr;
                break;
            default:
                out << std::dec << len << " bytes";
                break;
            }
            out << std::endl;
        }
    } else if (cmd == tlm::TLM_WRITE_COMMAND) {
        //
        // Write to memory.
        //
        if (Log::is_verbose()) {
            auto &out = Log::out();
            out << std::hex << std::setw(8) << std::setfill('0') << "          Write " << basename()
                << " [" << (addr + base_address) << "] = ";
            switch (len) {
            case 1:
                out << std::setw(2) << *(uint8_t *)ptr;
                break;
            case 2:
                out << std::setw(4) << *(uint16_t *)ptr;
                break;
            case 4:
                out << std::setw(8) << *(uint32_t *)ptr;
                break;
            default:
                out << std::dec << len << " bytes";
                break;
            }
            out << std::endl;
        }

        if (is_read_only) {
            Log::err() << basename() << ": Write to read-only memory at 0x" << std::hex
                       << (addr + base_address) << std::endl;
            SC_REPORT_ERROR(basename(), "Write to read-only memory");
            // TODO: take EXCEPTION_CAUSE_STORE_ACCESS_FAULT
        }
        memcpy(&mem[addr], ptr, len);
    }

    // Take latency into account
    delay += LATENCY;

    // TODO: Set DMI hint to indicated that DMI is supported
    // trans.set_dmi_allowed(true);

    // Obliged to set response status to indicate successful completion
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

bool Memory::get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data)
{
    (void)trans;

    // TODO: enable direct mem ptr later
    if (true) {
        return false;
    }

    // Permit read and write access
    if (!is_read_only) {
        dmi_data.allow_read_write();
    }

    // Set other details of DMI region
    dmi_data.set_dmi_ptr(reinterpret_cast<unsigned char *>(&mem[0]));
    dmi_data.set_start_address(0);
    dmi_data.set_end_address(size_bytes - 1);
    dmi_data.set_read_latency(LATENCY);
    dmi_data.set_write_latency(LATENCY);

    return true;
}

unsigned int Memory::transport_dbg(tlm::tlm_generic_payload &trans)
{
    tlm::tlm_command cmd = trans.get_command();
    unsigned addr        = trans.get_address();
    unsigned len         = trans.get_data_length();
    unsigned char *ptr   = trans.get_data_ptr();
#if 0
    if (Log::is_verbose()) {
        Log::out() << "--- " << basename()
                   << (cmd == tlm::TLM_READ_COMMAND ? " read " : " write ")
                   << len << " bytes at 0x" << std::hex << addr
                   << std::dec << std::endl;
    }
#endif
    if (addr >= size_bytes) {
        trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
        return 0;
    }

    // Calculate the number of bytes to be actually copied
    unsigned int num_bytes = std::min(len, size_bytes - addr);

    if (cmd == tlm::TLM_READ_COMMAND)
        memcpy(ptr, &mem[addr], num_bytes);
    else if (cmd == tlm::TLM_WRITE_COMMAND) {
        if (is_read_only) {
            // Cannot write to read-only memory.
            return 0;
        }
        memcpy(&mem[addr], ptr, num_bytes);
    }

    return num_bytes;
}

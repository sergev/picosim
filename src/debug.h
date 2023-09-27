/*!
 \file debug.h
 \brief GDB connector
 \author Màrius Montón
 \date February 2021
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef INC_DEBUG_H_
#define INC_DEBUG_H_

#include <unordered_set>

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

class Simulator;
class Processor;

class Debug : public sc_core::sc_module {
    SC_HAS_PROCESS(Debug);

public:
    Debug(Simulator &sim, Processor &p, bool debug_session);
    ~Debug() override;

private:
    Simulator &sim;
    Processor &cpu;

    static constexpr size_t bufsize = 1024 * 8;
    char iobuf[bufsize]{};
    int conn;
    tlm::tlm_generic_payload dbg_trans;
    std::unordered_set<uint32_t> breakpoints;

    static std::string compute_checksum_string(const std::string &msg);
    void send_packet(int m_conn, const std::string &msg);
    std::string receive_packet();
    void gdb_thread();
};

#endif /* INC_DEBUG_H_ */

/*!
 \file debug.cpp
 \brief GDB connector
 \author Màrius Montón
 \date February 2021
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#include "debug.h"

#include <netinet/in.h>
#include <sys/socket.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#include "simulator.h"

constexpr char nibble_to_hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

Debug::Debug(Simulator &s, Processor &p)
    : sc_module(sc_core::sc_module_name("Debug")), sim(s), cpu(p)
{
    SC_THREAD(gdb_thread);
}

Debug::~Debug()
{
}

void Debug::send_packet(int conn, const std::string &msg)
{
    std::string frame = "+$" + msg + "#" + compute_checksum_string(msg);

    memcpy(iobuf, frame.c_str(), frame.size());

    ::send(conn, iobuf, frame.size(), 0);
}

std::string Debug::receive_packet()
{
    int nbytes = ::recv(conn, iobuf, bufsize, 0);

    if (nbytes == 0) {
        return "";
    } else if (nbytes == 1) {
        return std::string("+");
    } else {
        char *start = strchr(iobuf, '$');
        char *end   = strchr(iobuf, '#');

        std::string message(start + 1, end - (start + 1));

        return message;
    }
}

static bool starts_with(const std::string &haystack, const std::string &needle)
{
    return needle.length() <= haystack.length() &&
           equal(needle.begin(), needle.end(), haystack.begin());
}

void Debug::gdb_thread()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(1234);

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, 1);

    socklen_t len = sizeof(addr);
    conn          = accept(sock, (struct sockaddr *)&addr, &len);

    std::cout << "Handle_GDB_Loop" << std::endl;

    while (true) {
        std::string msg = receive_packet();

        if (msg.size() == 0) {
            std::cout << "remote connection seems to be closed, terminating ..." << std::endl;
            break;
        } else if (msg == "+") {
            // NOTE: just ignore this message, nothing to do in this case
        } else if (starts_with(msg, "qSupported")) {
            send_packet(conn, "PacketSize=256;swbreak+;hwbreak+;vContSupported+;multiprocess-");
        } else if (msg == "vMustReplyEmpty") {
            send_packet(conn, "");
        } else if (msg == "Hg0") {
            send_packet(conn, "OK");
        } else if (msg == "Hc0") {
            send_packet(conn, "");
        } else if (msg == "qTStatus") {
            send_packet(conn, "");
        } else if (msg == "?") {
            send_packet(conn, "S05");
        } else if (msg == "qfThreadInfo") {
            send_packet(conn, "");
        } else if (starts_with(msg, "qL")) {
            send_packet(conn, "");
        } else if (msg == "Hc-1") {
            send_packet(conn, "OK");
        } else if (msg == "qC") {
            send_packet(conn, "-1");
        } else if (msg == "qAttached") {
            send_packet(conn, "0"); // 0 process started, 1 attached to process
        } else if (msg == "g") {
            std::stringstream stream;
            stream << std::setfill('0') << std::hex;
            for (int i = 1; i < 32; i++) {
                stream << std::setw(8) << cpu.get_reg(i);
            }
            send_packet(conn, stream.str());
        } else if (starts_with(msg, "p")) {
            long n = strtol(msg.c_str() + 1, 0, 16);
            int reg_value;
            if (n < 32) {
                reg_value = cpu.get_reg(n);
            } else if (n == 32) {
                reg_value = cpu.get_pc();
            } else {
                // see: https://github.com/riscv/riscv-gnu-toolchain/issues/217
                // risc-v register 834
                reg_value = cpu.get_sysreg(n - 65);
            }
            std::stringstream stream;
            stream << std::setfill('0') << std::hex;
            stream << std::setw(8) << htonl(reg_value);
            send_packet(conn, stream.str());
        } else if (starts_with(msg, "P")) {
            char *pEnd;
            long reg = strtol(msg.c_str() + 1, &pEnd, 16);
            int val  = strtol(pEnd + 1, 0, 16);
            cpu.set_reg(reg + 1, val);
            send_packet(conn, "OK");
        } else if (starts_with(msg, "m")) {
            char *pEnd;
            long addr = strtol(msg.c_str() + 1, &pEnd, 16);
            int len   = strtol(pEnd + 1, &pEnd, 16);
            uint8_t buf[len];

            sim.debug_read(buf, addr, len);

            std::stringstream stream;
            stream << std::setfill('0') << std::hex;
            for (auto &c : buf) {
                stream << std::setw(2) << (unsigned)c;
            }

            send_packet(conn, stream.str());

        } else if (starts_with(msg, "M")) {
            std::cout << "M TBD" << std::endl;
            send_packet(conn, "OK");
        } else if (starts_with(msg, "X")) {
            send_packet(conn, ""); // binary data unsupported
        } else if (msg == "qOffsets") {
            send_packet(conn, "Text=0;Data=0;Bss=0");
        } else if (msg == "qSymbol::") {
            send_packet(conn, "OK");
        } else if (msg == "vCont?") {
            send_packet(conn, "vCont;cs");
        } else if (msg == "c") {
            bool breakpoint_hit = false;
            bool bkpt           = false;
            do {
                cpu.cpu_step();
                bkpt               = false; // TODO
                uint32_t currentPC = cpu.get_pc();

                auto search = breakpoints.find(currentPC);
                if (search != breakpoints.end()) {
                    breakpoint_hit = true;
                }
            } while ((breakpoint_hit == false) && (bkpt == false));

            std::cout << "Breakpoint hit at 0x" << std::hex << cpu.get_pc() << std::endl;
            send_packet(conn, "S05");
        } else if (msg == "s") {
            bool breakpoint;
            cpu.cpu_step();

            uint32_t currentPC = cpu.get_pc();
            auto search        = breakpoints.find(currentPC);
            if (search != breakpoints.end()) {
                breakpoint = true;
            } else {
                breakpoint = false;
            }

            if (breakpoint) {
                send_packet(conn, "S03");
            } else {
                send_packet(conn, "S05");
            }

        } else if (starts_with(msg, "vKill")) {
            send_packet(conn, "OK");
            break;
        } else if (starts_with(msg, "Z1")) {
            char *pEnd;
            long addr = strtol(msg.c_str() + 3, &pEnd, 16);
            ;
            breakpoints.insert(addr);
            std::cout << "Breakpoint set to address 0x" << std::hex << addr << std::endl;
            send_packet(conn, "OK");
        } else if (starts_with(msg, "z1")) {
            char *pEnd;
            long addr = strtol(msg.c_str() + 3, &pEnd, 16);
            ;
            breakpoints.erase(addr);
            send_packet(conn, "OK");
        } else if (starts_with(msg, "z0")) {
            char *pEnd;
            long addr = strtol(msg.c_str() + 3, &pEnd, 16);
            ;
            breakpoints.erase(addr);
            send_packet(conn, "");
        } else if (starts_with(msg, "Z0")) {
            char *pEnd;
            long addr = strtol(msg.c_str() + 3, &pEnd, 16);
            ;
            breakpoints.insert(addr);
            std::cout << "Breakpoint set to address 0x" << std::hex << addr << std::endl;
            send_packet(conn, "OK");
        } else {
            std::cout << "unsupported message '" << msg << "' detected, terminating ..."
                      << std::endl;
            break;
        }
    }
}

std::string Debug::compute_checksum_string(const std::string &msg)
{
    unsigned sum = 0;
    for (auto c : msg) {
        sum += unsigned(c);
    }
    sum = sum % 256;

    char low  = nibble_to_hex[sum & 0xf];
    char high = nibble_to_hex[(sum & (0xf << 4)) >> 4];

    return { high, low };
}

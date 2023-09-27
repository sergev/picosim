/*
 * Virtual console TTY.
 * Copyright (c) 2005,2006 Christophe Fillot (cf@utc.fr)
 * Copyright (C) yajin 2008 <yajinzhou@gmail.com>
 * Copyright (C) 2014,2021 Serge Vakulenko
 *
 * "Interactive" part idea by Mtve.
 * TCP console added by Mtve.
 * Serial console by Peter Ross (suxen_drol@hotmail.com)
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaim all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 */
#include <sys/select.h>
#include <termios.h>

#include <string>

class Vtty {
    // 4 Kb should be enough for a keyboard buffer
    static const int BUFFER_SIZE = 4096;

    // VTTY connection states (for TCP)
    enum class Tcp_State {
        INVALID, // connection is not working
        WAITING, // waiting for incoming connection
        RUNNING, // character reading/writing ok
    };

    // VTTY input states
    enum class Input_State {
        TEXT,
        IVT1,
        IVT2,
        REMOTE,
        TELNET,
        TELNET_IYOU,
        TELNET_SB1,
        TELNET_SB2,
        TELNET_SB_TTYPE,
        TELNET_NEXT,
    };

public:
    // Create console or TCP port.
    explicit Vtty(const std::string &n, int p = 0);

    // Destroy the virtual tty
    ~Vtty();

    // Start the VTTY thread.
    static void start();

    // Returns TRUE if a character is available on input.
    bool is_char_avail();

    // Returns TRUE if input buffer is full.
    bool is_full() { return read_ptr == write_ptr; }

    // Read a character from the buffer (-1 if the buffer is empty).
    int get_char();

    // Send character to tty.
    void put_char(char ch);

    // Wait for input and return a bitmask of file descriptors.
    static int wait(fd_set *rfdp);

private:
    // List of all allocated vttys.
    static Vtty *first;
    Vtty *next{ nullptr };

    const std::string name;

    int tcp_port{ 0 };

    Input_State input_state{ Input_State::TEXT };

    Tcp_State tcp_state{ Tcp_State::INVALID };

    FILE *output_stream{ nullptr };

    int fd{ -1 };
    int accept_fd{ -1 };
    int *select_fd{ nullptr };

    bool use_telnet_protocol{ false };
    int telnet_cmd{ -1 };
    int telnet_opt{ -1 };
    int telnet_qual{ -1 };

    uint8_t buffer[BUFFER_SIZE]{};
    unsigned read_ptr{ 0 };
    unsigned write_ptr{ 0 };

    pthread_mutex_t lock;
    static pthread_t thread;

    static struct termios tios, tios_orig;

    // Put the tty device into single-character mode without echo.
    static int term_init();

    // Restore original settings of local tty device.
    static void term_reset();

    // Wait for TCP connection.
    int tcp_conn_wait();

    // Accept TCP connection.
    int tcp_conn_accept();

    // Send Telnet command: does the client support terminal type message?
    void telnet_do_ttype();

    // Send Telnet command: WILL TELOPT_ECHO.
    void telnet_will_echo();

    // Send Telnet command: Suppress Go-Ahead.
    void telnet_will_suppress_go_ahead();

    // Send Telnet command: Don't use linemode.
    void telnet_dont_linemode();

    // Read a character from the virtual TTY.
    int read();

    // Read a character (until one is available) and store it in buffer.
    void read_and_store();

    // Read a character from the TCP connection.
    int tcp_read();

    // Read a character from the terminal.
    int term_read();

    // Store a character to the input buffer.
    int store(uint8_t c);

    // VTTY thread polls connections and transfers data between endpoints.
    static void *thread_main(void *arg);
};

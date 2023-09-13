#include <algorithm>

#include "peripherals.h"
#include "esp32c3/soc.h"
#include "esp32c3/uart_reg.h"

Peripherals::Peripherals(sc_core::sc_module_name const &name, unsigned kbytes)
    : sc_module(name), size_bytes(1024 * kbytes)
{
    // Register callbacks for incoming interface method calls
    socket.register_b_transport(this, &Peripherals::b_transport);

    // Use calloc() to allocate zer-initialized memory efficiently,
    // using OS-specific mechanisms.
    mem = (uint8_t *)calloc(size_bytes, 1);
    if (mem == nullptr) {
        SC_REPORT_ERROR(name, "Cannot allocate memory");
        return;
    }
}

Peripherals::~Peripherals()
{
    free(mem);
}

void Peripherals::b_transport(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay)
{
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64 addr = trans.get_address();
    unsigned char *ptr = trans.get_data_ptr();
    unsigned int len = trans.get_data_length();
    unsigned val = 0;

    // Only byte, word and half word sizes are allowed.
    if (len != 1 && len != 2 && len != 4) {
        SC_REPORT_ERROR(basename(), "Bad data size");
    }
    assert(len == 1 || len == 2 || len == 4);

    if (cmd == tlm::TLM_READ_COMMAND) {
        //
        // Read value from peripheral register.
        //
        val = periph_read(addr);

        switch (len) {
        case 1:
            *(uint8_t *)ptr = val;
            break;
        case 2:
            *(uint16_t *)ptr = val;
            break;
        case 4:
            *(uint32_t *)ptr = val;
            break;
        }
        if (Log::is_verbose()) {
            Log::out() << "          Read " << std::hex << std::setw(len * 2) << std::setfill('0')
                       << val << " from " << reg_name(addr) << std::endl;
        }
    } else if (cmd == tlm::TLM_WRITE_COMMAND) {
        //
        // Write value to peripheral register.
        //
        switch (len) {
        case 1:
            val = *(uint8_t *)ptr;
            break;
        case 2:
            val = *(uint16_t *)ptr;
            break;
        case 4:
            val = *(uint32_t *)ptr;
            break;
        }
        periph_write(addr, val);

        if (Log::is_verbose()) {
            Log::out() << "          Write " << std::hex << std::setw(len * 2) << std::setfill('0')
                       << val << " to " << reg_name(addr) << std::endl;
        }
    }

    // Take latency into account
    delay += LATENCY;

    // Must set response status to indicate successful completion
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

//
// Read peripheral register.
// Update reg_name.
//
unsigned Peripherals::periph_read(unsigned addr)
{
    auto shadow = (uint32_t*) &mem[addr];

    return *shadow;
}

//
// Write to a peripheral register.
// Update reg_name.
//
void Peripherals::periph_write(unsigned addr, unsigned val)
{
    auto shadow = (uint32_t*) &mem[addr];

    switch (addr + SOC_PERIPHERAL_LOW) {
    case UART_FIFO_REG(0):
        putchar(val);
    }

    *shadow = val;
}

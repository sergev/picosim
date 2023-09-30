#include "peripherals.h"

#include <algorithm>
#include "rp2040/addressmap.h"
#include "rp2040/resets.h"
#include "rp2040/clocks.h"
#include "rp2040/tbman.h"
#include "rp2040/xosc.h"

Peripherals::Peripherals(sc_core::sc_module_name const &name, unsigned base_addr, unsigned last_addr)
    : sc_module(name),
      base_address(base_addr),
      size_bytes((last_addr + 1 - base_addr) * 1024)
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
    sc_dt::uint64 addr   = trans.get_address();
    unsigned char *ptr   = trans.get_data_ptr();
    unsigned int len     = trans.get_data_length();
    unsigned val         = 0;

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
            Log::out() << "          Read " << reg_name(addr) << " = "
                       << std::hex << std::setw(len * 2) << std::setfill('0') << val
                       << std::endl;
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
            Log::out() << "          Write " << reg_name(addr) << " = "
                       << std::hex << std::setw(len * 2) << std::setfill('0') << val
                       << std::endl;
        }
    }

    // Take latency into account
    delay += LATENCY;

    // Must set response status to indicate successful completion
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

//
// Read peripheral register.
//
unsigned Peripherals::periph_read(unsigned addr)
{
    auto shadow = (uint32_t *)&mem[addr];

    switch (addr + base_address) {

    case RESETS_BASE + RESETS_RESET_DONE_OFFSET:
        return resets_reset_done;

    case TBMAN_BASE + TBMAN_PLATFORM_OFFSET:
        // Indicate the platform is ASIC.
        return TBMAN_PLATFORM_ASIC_BITS;

    case CLOCKS_BASE + CLOCKS_CLK_SYS_SELECTED_OFFSET:
        // Indicate that clksrc_pll_sys is selected.
        return 1;

    case XOSC_BASE + XOSC_STATUS_OFFSET:
        // Oscillator is running and stable.
        return XOSC_STATUS_STABLE_BITS;

#if 1
    case 0x40028000:
        // Terminate for now.
        Log::out() << "--- " << reg_name(addr) + " is not implemented yet" << std::endl;
        sc_core::sc_stop();
        break;
#endif
    }
    return *shadow;
}

//
// Write to a peripheral register.
//
void Peripherals::periph_write(unsigned addr, unsigned val)
{
    auto shadow = (uint32_t *)&mem[addr];

    switch (addr + base_address) {
    case RESETS_BASE + RESETS_RESET_OFFSET:
        // Set RESET value - invert as RESET_DONE value.
        resets_reset_done = ~val;
        return;
    case RESETS_BASE + REG_ALIAS_SET_BITS + RESETS_RESET_OFFSET:
        // Set RESET bits - clear RESET_DONE bits.
        resets_reset_done &= ~val;
        return;
    case RESETS_BASE + REG_ALIAS_CLR_BITS + RESETS_RESET_OFFSET:
        // Clear RESET bits - set RESET_DONE bits.
        resets_reset_done |= val;
        return;
    }
    *shadow = val;
}

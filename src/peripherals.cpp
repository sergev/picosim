#include "simulator.h"
#include "rp2040/addressmap.h"

Peripherals::Peripherals(Processor &c, sc_core::sc_module_name const &name)
    : sc_module(name), cpu(c)
{
    // Register callbacks for incoming interface method calls
    socket.register_b_transport(this, &Peripherals::b_transport);

    // Use calloc() to allocate zer-initialized memory efficiently,
    // using OS-specific mechanisms.
    mem_sysinfo = (uint8_t *)calloc(RP2040_SYSINFO_LAST + 1 - RP2040_SYSINFO_BASE, 1);
    mem_ahb = (uint8_t *)calloc(RP2040_AHB_LAST + 1 - RP2040_AHB_BASE, 1);
    mem_sio = (uint8_t *)calloc(RP2040_SIO_LAST + 1 - RP2040_SIO_BASE, 1);
    mem_ssi = (uint8_t *)calloc(RP2040_SSI_LAST + 1 - RP2040_SSI_BASE, 1);
    mem_ppb = (uint8_t *)calloc(RP2040_PPB_LAST + 1 - RP2040_PPB_BASE, 1);
    mem_xip = (uint8_t *)calloc(RP2040_XIP_LAST + 1 - RP2040_XIP_BASE, 1);

    if (!mem_sysinfo || !mem_ahb || !mem_sio || !mem_ssi || !mem_ppb || !mem_xip) {
        SC_REPORT_ERROR(name, "Cannot allocate memory for peripherals");
        return;
    }
}

Peripherals::~Peripherals()
{
    free(mem_sysinfo);
    free(mem_ahb);
    free(mem_sio);
    free(mem_ssi);
    free(mem_ppb);
    free(mem_xip);
}

//
// Get shadow memory location for given register address.
//
uint32_t &Peripherals::get_shadow(unsigned addr)
{
    // Is this correct?
    addr &= ~(REG_ALIAS_SET_BITS | REG_ALIAS_CLR_BITS | REG_ALIAS_XOR_BITS);

    if (addr >= RP2040_SYSINFO_BASE && addr <= RP2040_SYSINFO_LAST) {
        return *(uint32_t *)&mem_sysinfo[addr - RP2040_SYSINFO_BASE];
    }
    if (addr >= RP2040_AHB_BASE && addr <= RP2040_AHB_LAST) {
        return *(uint32_t *)&mem_ahb[addr - RP2040_AHB_BASE];
    }
    if (addr >= RP2040_SIO_BASE && addr <= RP2040_SIO_LAST) {
        return *(uint32_t *)&mem_sio[addr - RP2040_SIO_BASE];
    }
    if (addr >= RP2040_SSI_BASE && addr <= RP2040_SSI_LAST) {
        return *(uint32_t *)&mem_ssi[addr - RP2040_SSI_BASE];
    }
    if (addr >= RP2040_PPB_BASE && addr <= RP2040_PPB_LAST) {
        return *(uint32_t *)&mem_ppb[addr - RP2040_PPB_BASE];
    }
    if (addr >= RP2040_XIP_BASE && addr <= RP2040_XIP_LAST) {
        return *(uint32_t *)&mem_xip[addr - RP2040_XIP_BASE];
    }
    // Cannot happen.
    std::stringstream msg;
    msg << "Bad register address in get_shadow(): 0x" << std::hex << addr;
    throw std::runtime_error(msg.str());
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
        val = cpu.periph_read(addr, get_shadow(addr));

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
            Log::out() << "          Read " << cpu.periph_name(addr) << " = "
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
        cpu.periph_write(addr, val, get_shadow(addr));

        if (Log::is_verbose()) {
            Log::out() << "          Write " << cpu.periph_name(addr) << " = "
                       << std::hex << std::setw(len * 2) << std::setfill('0') << val
                       << std::endl;
        }
    }

    // Take latency into account
    delay += LATENCY;

    // Must set response status to indicate successful completion
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

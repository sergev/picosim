#include "simulator.h"

#include "rp2040/addressmap.h"
#include "rp2040/resets.h"
#include "rp2040/clocks.h"
#include "rp2040/tbman.h"
#include "rp2040/xosc.h"
#include "rp2040/pll.h"
#include "rp2040/sio.h"
#include "rp2040/io_qspi.h"
#include "rp2040/ssi.h"
#include "rp2040/m0plus.h"
#include "rp2040/uart.h"

Peripherals::Peripherals(Simulator &s, sc_core::sc_module_name const &name, unsigned base_addr, unsigned last_addr)
    : sc_module(name),
      sim(s),
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

    case CLOCKS_BASE + CLOCKS_CLK_SYS_CTRL_OFFSET:
        return clk_sys_ctrl;

    case CLOCKS_BASE + CLOCKS_CLK_SYS_SELECTED_OFFSET:
        if (clk_sys_ctrl & CLOCKS_CLK_SYS_CTRL_SRC_BITS) {
            // Indicate that clksrc_clk_sys_aux is selected.
            return 2;
        } else {
            // Indicate that clk_ref is selected.
            return 1;
        }

    case CLOCKS_BASE + CLOCKS_CLK_REF_CTRL_OFFSET:
        return clk_ref_ctrl;

    case CLOCKS_BASE + CLOCKS_CLK_REF_SELECTED_OFFSET:
        // Indicate which clock source is selected.
        return 1 << (clk_ref_ctrl & CLOCKS_CLK_REF_CTRL_SRC_BITS);

    case XOSC_BASE + XOSC_STATUS_OFFSET:
        // Oscillator is running and stable.
        return XOSC_STATUS_STABLE_BITS;

    case PLL_SYS_BASE + PLL_CS_OFFSET:
    case PLL_USB_BASE + PLL_CS_OFFSET:
        // PLL is locked.
        return PLL_CS_LOCK_BITS;

    case SIO_BASE + SIO_GPIO_HI_IN_OFFSET:
        // Indicate flash is present: /CS pulled up.
        return 2;

    case XIP_SSI_BASE + SSI_RXFLR_OFFSET:
        // Receive FIFO level.
        return 1; // pretend we have something to send

    case XIP_SSI_BASE + SSI_SR_OFFSET:
        // SSI status: Transmit FIFO not full, and Transmit FIFO empty,
        // and Receive FIFO not empty.
        return SSI_SR_TFNF_BITS | SSI_SR_TFE_BITS | SSI_SR_RFNE_BITS;

    case SIO_BASE + SIO_SPINLOCK0_OFFSET:
    case SIO_BASE + SIO_SPINLOCK1_OFFSET:
    case SIO_BASE + SIO_SPINLOCK2_OFFSET:
    case SIO_BASE + SIO_SPINLOCK3_OFFSET:
    case SIO_BASE + SIO_SPINLOCK4_OFFSET:
    case SIO_BASE + SIO_SPINLOCK5_OFFSET:
    case SIO_BASE + SIO_SPINLOCK6_OFFSET:
    case SIO_BASE + SIO_SPINLOCK7_OFFSET:
    case SIO_BASE + SIO_SPINLOCK8_OFFSET:
    case SIO_BASE + SIO_SPINLOCK9_OFFSET:
    case SIO_BASE + SIO_SPINLOCK10_OFFSET:
    case SIO_BASE + SIO_SPINLOCK11_OFFSET:
    case SIO_BASE + SIO_SPINLOCK12_OFFSET:
    case SIO_BASE + SIO_SPINLOCK13_OFFSET:
    case SIO_BASE + SIO_SPINLOCK14_OFFSET:
    case SIO_BASE + SIO_SPINLOCK15_OFFSET:
    case SIO_BASE + SIO_SPINLOCK16_OFFSET:
    case SIO_BASE + SIO_SPINLOCK17_OFFSET:
    case SIO_BASE + SIO_SPINLOCK18_OFFSET:
    case SIO_BASE + SIO_SPINLOCK19_OFFSET:
    case SIO_BASE + SIO_SPINLOCK20_OFFSET:
    case SIO_BASE + SIO_SPINLOCK21_OFFSET:
    case SIO_BASE + SIO_SPINLOCK22_OFFSET:
    case SIO_BASE + SIO_SPINLOCK23_OFFSET:
    case SIO_BASE + SIO_SPINLOCK24_OFFSET:
    case SIO_BASE + SIO_SPINLOCK25_OFFSET:
    case SIO_BASE + SIO_SPINLOCK26_OFFSET:
    case SIO_BASE + SIO_SPINLOCK27_OFFSET:
    case SIO_BASE + SIO_SPINLOCK28_OFFSET:
    case SIO_BASE + SIO_SPINLOCK29_OFFSET:
    case SIO_BASE + SIO_SPINLOCK30_OFFSET:
    case SIO_BASE + SIO_SPINLOCK31_OFFSET: {
        unsigned index = (addr >> 2) & 0x1f;
        if (sim.spinlock_is_locked(index)) {
            return 0;
        }
        sim.lock_spinlock(index);
        return 1 << index;
    }

    case PPB_BASE + M0PLUS_VTOR_OFFSET:
        return m0plus_vtor;

    case XIP_SSI_BASE + SSI_DR0_OFFSET:
        // TODO: receive data from Flash interface
        return sim.flash_receive();

    case IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SS_CTRL_OFFSET:
        // Select Flash interface.
        return ss_ctrl;

    //
    // Integer Divider.
    //
    case SIO_BASE + SIO_DIV_UDIVIDEND_OFFSET:
    case SIO_BASE + SIO_DIV_SDIVIDEND_OFFSET:
        return div_dividend;
    case SIO_BASE + SIO_DIV_UDIVISOR_OFFSET:
    case SIO_BASE + SIO_DIV_SDIVISOR_OFFSET:
        return div_divisor;
    case SIO_BASE + SIO_DIV_QUOTIENT_OFFSET:
        // Reading from QUOTIENT clears the CSR_DIRTY flag.
        div_csr &= ~SIO_DIV_CSR_DIRTY_BITS;
        return div_quotient;
    case SIO_BASE + SIO_DIV_REMAINDER_OFFSET:
        return div_remainder;
    case SIO_BASE + SIO_DIV_CSR_OFFSET:
        return div_csr;

#if 1
    case IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD1_CTRL_OFFSET:
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

    case CLOCKS_BASE + CLOCKS_CLK_SYS_CTRL_OFFSET:
        clk_sys_ctrl = val;
        return;
    case CLOCKS_BASE + REG_ALIAS_SET_BITS + CLOCKS_CLK_SYS_CTRL_OFFSET:
        clk_sys_ctrl |= val;
        return;
    case CLOCKS_BASE + REG_ALIAS_CLR_BITS + CLOCKS_CLK_SYS_CTRL_OFFSET:
        clk_sys_ctrl &= ~val;
        return;
    case CLOCKS_BASE + REG_ALIAS_XOR_BITS + CLOCKS_CLK_SYS_CTRL_OFFSET:
        clk_sys_ctrl ^= val;
        return;

    case CLOCKS_BASE + CLOCKS_CLK_REF_CTRL_OFFSET:
        clk_ref_ctrl = val;
        return;
    case CLOCKS_BASE + REG_ALIAS_SET_BITS + CLOCKS_CLK_REF_CTRL_OFFSET:
        clk_ref_ctrl |= val;
        return;
    case CLOCKS_BASE + REG_ALIAS_CLR_BITS + CLOCKS_CLK_REF_CTRL_OFFSET:
        clk_ref_ctrl &= ~val;
        return;
    case CLOCKS_BASE + REG_ALIAS_XOR_BITS + CLOCKS_CLK_REF_CTRL_OFFSET:
        clk_ref_ctrl ^= val;
        return;

    case SIO_BASE + SIO_SPINLOCK0_OFFSET:
    case SIO_BASE + SIO_SPINLOCK1_OFFSET:
    case SIO_BASE + SIO_SPINLOCK2_OFFSET:
    case SIO_BASE + SIO_SPINLOCK3_OFFSET:
    case SIO_BASE + SIO_SPINLOCK4_OFFSET:
    case SIO_BASE + SIO_SPINLOCK5_OFFSET:
    case SIO_BASE + SIO_SPINLOCK6_OFFSET:
    case SIO_BASE + SIO_SPINLOCK7_OFFSET:
    case SIO_BASE + SIO_SPINLOCK8_OFFSET:
    case SIO_BASE + SIO_SPINLOCK9_OFFSET:
    case SIO_BASE + SIO_SPINLOCK10_OFFSET:
    case SIO_BASE + SIO_SPINLOCK11_OFFSET:
    case SIO_BASE + SIO_SPINLOCK12_OFFSET:
    case SIO_BASE + SIO_SPINLOCK13_OFFSET:
    case SIO_BASE + SIO_SPINLOCK14_OFFSET:
    case SIO_BASE + SIO_SPINLOCK15_OFFSET:
    case SIO_BASE + SIO_SPINLOCK16_OFFSET:
    case SIO_BASE + SIO_SPINLOCK17_OFFSET:
    case SIO_BASE + SIO_SPINLOCK18_OFFSET:
    case SIO_BASE + SIO_SPINLOCK19_OFFSET:
    case SIO_BASE + SIO_SPINLOCK20_OFFSET:
    case SIO_BASE + SIO_SPINLOCK21_OFFSET:
    case SIO_BASE + SIO_SPINLOCK22_OFFSET:
    case SIO_BASE + SIO_SPINLOCK23_OFFSET:
    case SIO_BASE + SIO_SPINLOCK24_OFFSET:
    case SIO_BASE + SIO_SPINLOCK25_OFFSET:
    case SIO_BASE + SIO_SPINLOCK26_OFFSET:
    case SIO_BASE + SIO_SPINLOCK27_OFFSET:
    case SIO_BASE + SIO_SPINLOCK28_OFFSET:
    case SIO_BASE + SIO_SPINLOCK29_OFFSET:
    case SIO_BASE + SIO_SPINLOCK30_OFFSET:
    case SIO_BASE + SIO_SPINLOCK31_OFFSET: {
        unsigned index = (addr >> 2) & 0x1f;
        sim.release_spinlock(index);
        return;
    }

    case PPB_BASE + M0PLUS_VTOR_OFFSET:
        m0plus_vtor = val;
        return;

    case XIP_SSI_BASE + SSI_DR0_OFFSET:
        // Send data to Flash interface.
        sim.flash_send(val);
        return;

    case IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SS_CTRL_OFFSET:
        // Select Flash interface.
        // Bits 9:8 - OUTOVER - connected as /SS for Flash chip.
        // 0 - drive output from peripheral signal selected by funcsel
        // 1 - drive output from inverse of peripheral signal selected by funcsel
        // 2 - drive output low (select enabled)
        // 3 - drive output high
        ss_ctrl = val;
flash_select:
        sim.flash_select((val & IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_BITS) ==
                         (IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_VALUE_LOW << IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_LSB));
        return;
    case IO_QSPI_BASE + REG_ALIAS_CLR_BITS + IO_QSPI_GPIO_QSPI_SS_CTRL_OFFSET:
        ss_ctrl &= ~val;
        goto flash_select;
    case IO_QSPI_BASE + REG_ALIAS_XOR_BITS + IO_QSPI_GPIO_QSPI_SS_CTRL_OFFSET:
        ss_ctrl ^= val;
        goto flash_select;

    case UART0_BASE + UART_UARTDR_OFFSET:
        // Print byte on stdout.
        sim.put_char(val);
        return;

    //
    // Integer Divider.
    //
    case SIO_BASE + SIO_DIV_UDIVIDEND_OFFSET:
        div_dividend = val;
        div_start('u');
        return;
    case SIO_BASE + SIO_DIV_SDIVIDEND_OFFSET:
        div_dividend = val;
        div_start('s');
        return;
    case SIO_BASE + SIO_DIV_UDIVISOR_OFFSET:
        div_divisor = val;
        div_start('u');
        return;
    case SIO_BASE + SIO_DIV_SDIVISOR_OFFSET:
        div_divisor = val;
        div_start('s');
        return;
    case SIO_BASE + SIO_DIV_QUOTIENT_OFFSET:
        div_quotient = val;
        return;
    case SIO_BASE + SIO_DIV_REMAINDER_OFFSET:
        div_remainder = val;
        return;
    case SIO_BASE + SIO_DIV_CSR_OFFSET:
        // Write to DIV_CSR is ignored.
        return;
    }
    *shadow = val;
}

//
// Start integer divider operation.
//
void Peripherals::div_start(char op)
{
    switch (op) {
    case 's':
        div_quotient = (int32_t)div_dividend / (int32_t)div_divisor;
        div_remainder = (int32_t)div_dividend % (int32_t)div_divisor;
        break;
    case 'u':
        div_quotient = (uint32_t)div_dividend / (uint32_t)div_divisor;
        div_remainder = (uint32_t)div_dividend % (uint32_t)div_divisor;
        break;
    }
    div_csr |= SIO_DIV_CSR_DIRTY_BITS;
}

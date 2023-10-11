//
// ARMv6-M Processor
//
// Copyright (C) 2023 Serge Vakulenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "processor.h"
#include "simulator.h"
#include "disassemble.h"

#include "rp2040/addressmap.h"
#include "rp2040/exception.h"
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

Processor::Processor(Simulator &s, sc_core::sc_module_name const name, bool debug, const std::string &config)
    : sc_module(name), sim(s)
{
    instr_bus.register_invalidate_direct_mem_ptr(this, &Processor::invalidate_direct_mem_ptr);

    if (!debug) {
        SC_THREAD(cpu_thread);
    }

    if (config == "linux") {
        // Allow Linux syscalls.
        linux_mode = true;
    }

    // Machine starts in Thread mode after Reset.
    mode = Mode::THREAD_MODE;

    //
    // Initial values.
    //
    xpsr.u32    = 0;
    primask.u32 = 0;
    control.u32 = 0;
}

//TODO
#if 0
void Processor::irq_bind(tlm_utils::simple_initiator_socket<Timer> &socket)
{
    irq_line_socket = std::make_unique<tlm_utils::simple_target_socket<Processor>>("irq");
    irq_line_socket->register_b_transport(this, &Processor::call_interrupt);
    irq_line_socket->bind(socket);
}
#endif

void Processor::terminate_simulation(const std::string &reason) const
{
    if (!reason.empty()) {
        std::cout << std::endl << reason << std::endl;
        Log::out() << reason << std::endl;
    }

    sc_core::sc_stop();
    sc_core::wait(sc_core::SC_ZERO_TIME);
}

//
// Process one of pending interrupts.
// Clear appropriate pending bit.
// Enter exception with appropriate vector.
//
void Processor::cpu_process_interrupt()
{
    // Find the lowest bit set.
    unsigned irq = __builtin_ctz(nvic_pending_mask & nvic_enable_mask);

    // Clear pending bit for this IRQ.
    nvic_pending_mask &= ~(1 << irq);

    // Take exception with appropriate vector.
    cpu_enter_exception(irq);
}

//
// Return true if the given priority exceeds priority of exception
// currently being serviced.
//
bool Processor::check_priority(unsigned prio)
{
    switch (xpsr.field.exception) {
    case 0:
        // No current exception.
        return true;
    case SVCALL_EXCEPTION + 16:
        return prio > svcall_priority;
    case PENDSV_EXCEPTION + 16:
        return prio > pendsv_priority;
    case SYSTICK_EXCEPTION + 16:
        return prio > systick_priority;
    default:
        if (xpsr.field.exception >= 16 && xpsr.field.exception < 48) {
            // External interrupt.
            return prio > nvic_priority[xpsr.field.exception - 16];
        }
        return false;
    }
}

//
// Return true if priority of pending IRQ exceeds priority of exception
// currently being serviced.
//
bool Processor::check_irq_priority()
{
    // Find the lowest bit set.
    unsigned irq = __builtin_ctz(nvic_pending_mask & nvic_enable_mask);

    return check_priority(nvic_priority[irq]);
}

//
// Enter exception with given number.
// Push registers onto stack.
// Jump to appropriate exception veltor.
//
void Processor::cpu_enter_exception(int irq)
{
    if (Log::is_verbose()) {
        auto &out = Log::out();
        switch (irq) {
        case NMI_EXCEPTION:
            out << "----- NMI Exception -----" << std::endl;
            break;
        case HARDFAULT_EXCEPTION:
            out << "----- HardFault Exception -----" << std::endl;
            break;
        case SVCALL_EXCEPTION:
            out << "----- SVCall Exception -----" << std::endl;
            break;
        case PENDSV_EXCEPTION:
            out << "----- PendSV Exception -----" << std::endl;
            break;
        case SYSTICK_EXCEPTION:
            out << "----- SysTick Exception -----" << std::endl;
            break;
        default:
            out << "----- Interrupt #" << irq << " -----" << std::endl;
            break;
        }
    }

    //
    // Save registers on stack.
    //
    unsigned sp     = get_sp() - 0x20;
    unsigned status = xpsr.u32 | 0x0100'0000; // Set Thumb bit
    if (sp & 4) {
        // Align stack.
        sp -= 4;
        status |= 0x200; // Set xPSR bit 9
    }
    set_sp(sp);
    data_write32(sp + 0x1c, status);
    data_write32(sp + 0x18, get_pc());
    data_write32(sp + 0x14, get_reg(Registers::LR));
    data_write32(sp + 0x10, get_reg(12));
    data_write32(sp + 0x0c, get_reg(3));
    data_write32(sp + 0x08, get_reg(2));
    data_write32(sp + 0x04, get_reg(1));
    data_write32(sp + 0x00, get_reg(0));

    //
    // Set EXC_RETURN value, based on mode.
    //
    if (mode == Mode::HANDLER_MODE) {
        set_reg(Registers::LR, 0xfffffff1);
    } else if (control.field.spsel) {
        set_reg(Registers::LR, 0xfffffffd);
    } else {
        set_reg(Registers::LR, 0xfffffff9);
    }

    // Enter Handler Mode, now Privileged.
    mode = Mode::HANDLER_MODE;

    // Set exception number.
    xpsr.field.exception = irq + 16;
    if (Log::is_verbose()) {
        Log::out() << "          xpsr = " << std::hex << std::setw(8)
                   << std::setfill('0') << xpsr.u32 << std::endl;
    }

    // Jump to appropriate vector.
    unsigned vector = data_read32(m0plus_vtor + (irq + 16) * 4);
    set_pc(vector & ~1);
}

//
// Return from exception with given return code.
// Pop registers from stack.
//
void Processor::cpu_exit_exception(unsigned exc_return)
{
    if (Log::is_verbose()) {
        Log::out() << "----- Return from exception -----" << std::endl;
    }

    //
    // Switch mode.
    //
    if (exc_return & 8) {
        mode = Mode::THREAD_MODE; // return to Thread mode
    } else {
        mode = Mode::HANDLER_MODE; // return to Handler mode
    }
    unsigned sp;
    if (exc_return & 4) {
        sp = register_bank.getPSP(); // return to Process stack
    } else {
        sp = register_bank.getMSP(); // return to Main stack
    }

    //
    // Restore registers from stack.
    // Stack accesses are performed as Unprivileged if we return to Thread mode
    // and control.field.spsel=1, otherwise as Privileged accesses.
    //
    set_reg(0, data_read32(sp + 0x00));
    set_reg(1, data_read32(sp + 0x04));
    set_reg(2, data_read32(sp + 0x08));
    set_reg(3, data_read32(sp + 0x0c));
    set_reg(12, data_read32(sp + 0x10));
    set_reg(Registers::LR, data_read32(sp + 0x14));
    next_pc = data_read32(sp + 0x18);
    unsigned status = data_read32(sp + 0x1c);

    xpsr.u32 = status & 0xf000003f;
    if (mode == Mode::THREAD_MODE) {
        xpsr.field.exception = 0;
    }

    //
    // Update stack pointer.
    //
    unsigned stack_align = ((status >> 9) & 1) << 2;
    sp = (sp + 0x20) | stack_align;
    if (exc_return & 4) {
        register_bank.setPSP(sp); // return to Process stack
    } else {
        register_bank.setMSP(sp); // return to Main stack
    }
}

//
// Fetch two-byte instruction at given address.
//
uint16_t Processor::fetch16(unsigned address)
{
    uint16_t buf;
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

    if (dmi_ptr_valid) {
        /* if memory_offset at Memory module is set, this won't work */
        memcpy(&buf, dmi_ptr + address, sizeof(buf));
        delay += dmi_read_latency;
#if 0
        if (Log::is_verbose() && address >= 0x40000000 && address <= 0x4005ffff) {
            Log::out() << "-------- Fetch from ROM" << std::endl;
        }
#endif
    } else {
        tlm::tlm_generic_payload trans;
        trans.set_command(tlm::TLM_READ_COMMAND);
        trans.set_data_ptr(reinterpret_cast<unsigned char *>(&buf));
        trans.set_data_length(sizeof(buf));
        trans.set_streaming_width(sizeof(buf)); // = data_length to indicate no streaming
        trans.set_byte_enable_ptr(nullptr);     // 0 indicates unused
        trans.set_dmi_allowed(false);           // Mandatory initial value
        trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
        trans.set_address(address);

        instr_bus->b_transport(trans, delay);
        if (trans.is_response_error()) {
            Log::err() << "Bad Fetch at 0x" << std::hex << address << std::endl;
            SC_REPORT_ERROR("CPU base", "Read memory");
        }

        if (trans.is_dmi_allowed()) {
            tlm::tlm_dmi dmi_data;
            dmi_ptr_valid = instr_bus->get_direct_mem_ptr(trans, dmi_data);
            if (dmi_ptr_valid) {
                // std::cout << "Get DMI_PTR " << std::endl;
                dmi_ptr          = dmi_data.get_dmi_ptr();
                dmi_read_latency = dmi_data.get_read_latency();
            }
        }
    }
    wait(delay);

    return buf;
}

//
// Fetch and execute one instruction at PC.
//
void Processor::cpu_step()
{
    // Fetch instruction.
    // Assume 16-bit opcode.
    unsigned pc           = register_bank.getPC();
    opcode                = fetch16(pc);
    unsigned pc_increment = arm_opcode_length(opcode);
    if (pc_increment == 4) {
        // Extend to 32-bit opcode.
        opcode = (opcode << 16) | fetch16(pc + 2);
    }

    if (Log::is_verbose()) {
        auto &out = Log::out();
        out << std::hex << std::setw(8) << std::setfill('0') << pc << ": ";
        if (pc_increment == 2)
            out << std::setw(4) << (uint16_t)opcode << "     ";
        else
            out << std::setw(8) << opcode << " ";
        out << arm_disassemble(opcode, pc) << std::endl;
    }

    // Execute instruction.
    if (opcode == 0) {
        // Zero opcode cannot happen in valid program.
        terminate_simulation("Illegal instruction");
    }

    // Assume next PC value for regular instructions.
    // In case of jump or exception,
    // instructions must update pc_next value.
    next_pc = pc + pc_increment;

    unsigned prev_xpsr = xpsr.u32;
    if (pc_increment == 4) {
        process_opcode32();
    } else {
        process_opcode16();
    }

    if (Log::is_verbose())
        print_nzcv(prev_xpsr);

    instructions_executed++;
    set_pc(next_pc & ~1);

    if (linux_mode && app_finished) {
        terminate_simulation("");
    }
}

//
// Print NZCV flags when changed.
//
void Processor::print_nzcv(unsigned prev_xpsr)
{
    if ((xpsr.u32 >> 28) != (prev_xpsr >> 28)) {
        Log::out() << "          nzcv = "
                   << (xpsr.field.n ? '1' : '.')
                   << (xpsr.field.z ? '1' : '.')
                   << (xpsr.field.c ? '1' : '.')
                   << (xpsr.field.v ? '1' : '.') << std::endl;
    }
}

void Processor::cpu_thread()
{
    if (!linux_mode) {
        // Read master stack pointer from ROM.
        set_reg(Registers::SP, data_read32(0));

        if (get_pc() == 0) {
            // Read PC value from ROM.
            set_pc(data_read32(4) & ~1);
        }
    }

    while (true) {
        sc_core::wait(sc_core::SC_ZERO_TIME);

        // Check for exceptions.
        if (nmi_request) {
            nmi_request = false;
            cpu_enter_exception(NMI_EXCEPTION);
        }
        else if (hardfault_request) {
            hardfault_request = false;
            cpu_enter_exception(HARDFAULT_EXCEPTION);
        }
        else if (svcall_request && !primask.field.pm && check_priority(svcall_priority)) {
            svcall_request = false;
            cpu_enter_exception(SVCALL_EXCEPTION);
        }
        else if (pendsv_request && !primask.field.pm && check_priority(pendsv_priority)) {
            pendsv_request = false;
            cpu_enter_exception(PENDSV_EXCEPTION);
        }
        else if (systick_request && !primask.field.pm && check_priority(systick_priority)) {
            systick_request = false;
            cpu_enter_exception(SYSTICK_EXCEPTION);
        }
        else if ((nvic_pending_mask & nvic_enable_mask) != 0 && !primask.field.pm && check_irq_priority()) {
            cpu_process_interrupt();
        }
        else {
            // Process one instruction.
            cpu_step();
        }
    }
}

void Processor::call_interrupt(tlm::tlm_generic_payload &m_trans, sc_core::sc_time &delay)
{
    //TODO: interrupt = true;
    //TODO: memcpy(&int_cause, m_trans.get_data_ptr(), sizeof(uint32_t));
    delay += sc_core::sc_time(1, sc_core::SC_NS);
}

void Processor::invalidate_direct_mem_ptr(sc_dt::uint64 start, sc_dt::uint64 end)
{
    (void)start;
    (void)end;
    dmi_ptr_valid = false;
}

void Processor::set_mode(Mode m)
{
    // TODO: update CPU state when changing modes.
    mode = m;
}

/**
 * Access data memory to get data
 * @param  addr address to access to
 * @param size size of the data to read in bytes
 * @return data value read
 */
uint32_t Processor::data_read(uint32_t addr, int size)
{
    uint32_t data;
    tlm::tlm_generic_payload trans;

    trans.set_command(tlm::TLM_READ_COMMAND);
    trans.set_data_ptr(reinterpret_cast<unsigned char *>(&data));
    trans.set_data_length(size);
    trans.set_streaming_width(4);       // = data_length to indicate no streaming
    trans.set_byte_enable_ptr(nullptr); // 0 indicates unused
    trans.set_dmi_allowed(false);       // Mandatory initial value
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans.set_address(addr);

    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    data_bus->b_transport(trans, delay);
    wait(delay);

    if (trans.is_response_error()) {
        Log::err() << "Read error at 0x" << std::hex << std::setw(8) << std::setfill('0') << addr
                   << std::endl;
        SC_REPORT_ERROR("Memory", "Read");
    }
    return data;
}

/**
 * Acces data memory to write data
 * @brief
 * @param addr addr address to access to
 * @param data data to write
 * @param size size of the data to write in bytes
 */
void Processor::data_write(uint32_t addr, uint32_t data, int size)
{
    tlm::tlm_generic_payload trans;

    trans.set_command(tlm::TLM_WRITE_COMMAND);
    trans.set_data_ptr(reinterpret_cast<unsigned char *>(&data));
    trans.set_data_length(size);
    trans.set_streaming_width(4);       // = data_length to indicate no streaming
    trans.set_byte_enable_ptr(nullptr); // 0 indicates unused
    trans.set_dmi_allowed(false);       // Mandatory initial value
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans.set_address(addr);

    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    data_bus->b_transport(trans, delay);
    wait(delay);

    if (trans.is_response_error()) {
        Log::err() << "Write failed at address 0x" << std::hex << std::setw(8) << std::setfill('0')
                   << addr << std::endl;
        SC_REPORT_ERROR("Memory", "Write");
    }
}

uint32_t Processor::get_sysreg(unsigned sysm)
{
    switch (sysm) {
    case SYSM_APSR:  // Application status register
    case SYSM_EAPSR: // A composite of EPSR and APSR
    case SYSM_IAPSR: // A composite of IPSR and APSR
    case SYSM_XPSR:  // A composite of all three PSR registers
        return xpsr.u32;

    case SYSM_IPSR:  // Interrupt status register
    case SYSM_IEPSR: // A composite of IPSR and EPSR
        return xpsr.u32 & 0x3f;

    case SYSM_EPSR:
        // Execution status register: always zero.
        return 0;

    case SYSM_MSP:
        // The Main Stack pointer
        return register_bank.getMSP();

    case SYSM_PSP:
        // The Process Stack pointer
        return register_bank.getPSP();

    case SYSM_PRIMASK:
        // Register to mask out configurable exceptions
        return primask.u32;

    case SYSM_CONTROL:
        // Stack select, Thread mode privilege
        return control.u32;

    default:
        Log::err() << "Read unknown sysreg 0x" << std::hex << std::setw(3) << std::setfill('0')
                   << sysm << std::endl;
        SC_REPORT_ERROR("SYSREG", "Read");
        return 0;
    }
}

//
// Set value of CSR register.
// Only writable bits are modified.
//
void Processor::set_sysreg(unsigned sysm, uint32_t value)
{
    switch (sysm) {
    case SYSM_APSR:  // Application status register
    case SYSM_EAPSR: // A composite of EPSR and APSR
    case SYSM_IAPSR: // A composite of IPSR and APSR
    case SYSM_XPSR:  // A composite of all three PSR registers
        xpsr.field.n = value >> 31;
        xpsr.field.z = value >> 30;
        xpsr.field.c = value >> 29;
        xpsr.field.v = value >> 28;
        if (Log::is_verbose()) {
            Log::out() << "          xpsr = " << std::hex << std::setw(8)
                       << std::setfill('0') << xpsr.u32 << std::endl;
        }
        return;

    case SYSM_IPSR:  // Interrupt status register
    case SYSM_IEPSR: // A composite of IPSR and EPSR
    case SYSM_EPSR: // Execution status register: always zero
        // Write ignored.
        return;

    case SYSM_MSP:
        // The Main Stack pointer
        register_bank.setMSP(value & ~3);
        return;

    case SYSM_PSP:
        // The Process Stack pointer
        register_bank.setPSP(value & ~3);
        return;

    case SYSM_PRIMASK:
        // Register to mask out configurable exceptions
        primask.field.pm = value;
        if (Log::is_verbose()) {
            Log::out() << "          primask = " << std::hex << std::setw(8)
                       << std::setfill('0') << primask.u32 << std::endl;
        }
        return;

    case SYSM_CONTROL:
        // Stack select, Thread mode privilege
        control.field.npriv = value;
        control.field.spsel = value >> 1;
        if (Log::is_verbose()) {
            Log::out() << "          control = " << std::hex << std::setw(8)
                       << std::setfill('0') << control.u32 << std::endl;
        }
        return;

    default:
        // Exception on write.
        cpu_enter_exception(HARDFAULT_EXCEPTION);
        return;
    }
}

//
// Start integer divider operation.
//
void Processor::div_start(char op)
{
    switch (op) {
    case 's':
        if (div_dividend == 0x8000'0000 && div_divisor == 0xffff'ffff) {
            // INT_MIN divided by -1 - overflow.
            div_quotient = div_dividend;
            div_remainder = 0;
        } else if (div_divisor != 0) {
            div_quotient = (int32_t)div_dividend / (int32_t)div_divisor;
            div_remainder = (int32_t)div_dividend % (int32_t)div_divisor;
        } else {
            // Signed division by zero.
            div_quotient = ((int32_t)div_dividend >= 0) ? -1 : 1;
            div_remainder = div_dividend;
        }
        break;
    case 'u':
        if (div_divisor != 0) {
            div_quotient = (uint32_t)div_dividend / (uint32_t)div_divisor;
            div_remainder = (uint32_t)div_dividend % (uint32_t)div_divisor;
        } else {
            // Unsigned division by zero.
            div_quotient = ~0;
            div_remainder = div_dividend;
        }
        break;
    }
    div_csr |= SIO_DIV_CSR_DIRTY_BITS;
}

//
// Read IPRn register.
//
unsigned Processor::get_nvic_ipr(unsigned n)
{
    return nvic_priority[n] |
          (nvic_priority[n+1] << 8) |
          (nvic_priority[n+2] << 16) |
          (nvic_priority[n+3] << 24);
}

//
// Write IPRn register.
//
void Processor::set_nvic_ipr(unsigned n, unsigned value)
{
    nvic_priority[n] = value & 0xc0;
    nvic_priority[n+1] = (value >> 8) & 0xc0;
    nvic_priority[n+2] = (value >> 16) & 0xc0;
    nvic_priority[n+3] = (value >> 24) & 0xc0;
}

//
// Read peripheral register.
//
unsigned Processor::periph_read(unsigned addr, uint32_t &shadow)
{
    switch (addr) {

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

    case XIP_SSI_BASE + SSI_DR0_OFFSET:
        // Receive data from Flash interface.
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

    //
    // Interrupt Controller.
    //
    case PPB_BASE + M0PLUS_VTOR_OFFSET:
        return m0plus_vtor;
    case PPB_BASE + M0PLUS_NVIC_ISER_OFFSET: // Interrupt Set-Enable Register
    case PPB_BASE + M0PLUS_NVIC_ICER_OFFSET: // Interrupt Clear-Enable Register
        return nvic_enable_mask;
    case PPB_BASE + M0PLUS_NVIC_ISPR_OFFSET: // Interrupt Set-Pending Register
    case PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET: // Interrupt Clear-Pending Register
        return nvic_pending_mask;
    case PPB_BASE + M0PLUS_NVIC_IPR0_OFFSET: // Priority level for interrupt N...N+3
    case PPB_BASE + M0PLUS_NVIC_IPR1_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR2_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR3_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR4_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR5_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR6_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR7_OFFSET:
        return get_nvic_ipr((addr >> 2) & 7);
    case PPB_BASE + M0PLUS_SHPR2_OFFSET: // Priority level for SVCall exception
        return svcall_priority << 24;
    case PPB_BASE + M0PLUS_SHPR3_OFFSET: // Priority level for PendSV and SysTick
        return (pendsv_priority << 16) | (systick_priority << 24);

#if 1
    case IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD1_CTRL_OFFSET:
        // Terminate for now.
        Log::out() << "--- " << periph_name(addr) + " is not implemented yet" << std::endl;
        sc_core::sc_stop();
        break;
#endif
    }

    // Read from shadow memory.
    return shadow;
}

//
// Write to a peripheral register.
//
void Processor::periph_write(unsigned addr, unsigned val, uint32_t &shadow)
{
    switch (addr) {
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
        put_char(val);
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

    //
    // Interrupt Controller.
    //
    case PPB_BASE + M0PLUS_VTOR_OFFSET:
        m0plus_vtor = val;
        return;
    case PPB_BASE + M0PLUS_NVIC_ISER_OFFSET: // Interrupt Set-Enable Register
        nvic_enable_mask |= val;
        return;
    case PPB_BASE + M0PLUS_NVIC_ICER_OFFSET: // Interrupt Clear-Enable Register
        nvic_enable_mask &= ~val;
        return;
    case PPB_BASE + M0PLUS_NVIC_ISPR_OFFSET: // Interrupt Set-Pending Register
        nvic_pending_mask |= val;
        return;
    case PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET: // Interrupt Clear-Pending Register
        nvic_pending_mask &= ~val;
        return;
    case PPB_BASE + M0PLUS_NVIC_IPR0_OFFSET: // Priority level for interrupt N...N+3
    case PPB_BASE + M0PLUS_NVIC_IPR1_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR2_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR3_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR4_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR5_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR6_OFFSET:
    case PPB_BASE + M0PLUS_NVIC_IPR7_OFFSET:
        set_nvic_ipr((addr >> 2) & 7, val);
        return;
    case PPB_BASE + M0PLUS_SHPR2_OFFSET: // Priority level for SVCall exception
        svcall_priority = (val >> 24) & 0xc0;
        return;
    case PPB_BASE + M0PLUS_SHPR3_OFFSET: // Priority level for PendSV and SysTick
        pendsv_priority = (val >> 16) & 0xc0;
        systick_priority = (val >> 24) & 0xc0;
        return;
    }

    // Store to shadow memory.
    shadow = val;
}

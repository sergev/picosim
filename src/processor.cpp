/*!
 \file processor.cpp
 \brief Main CPU class
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later
#include "processor.h"
#include "disassemble.h"

//
// Special register field encoding
//
enum {
    SYSM_APSR = 0,      // The flags from previous instructions
    SYSM_IAPSR = 1,     // A composite of IPSR and APSR
    SYSM_EAPSR = 2,     // A composite of EPSR and APSR
    SYSM_XPSR = 3,      // A composite of all three PSR registers
    SYSM_IPSR = 5,      // The Interrupt status register
    SYSM_EPSR = 6,      // The execution status register
    SYSM_IEPSR = 7,     // A composite of IPSR and EPSR
    SYSM_MSP = 8,       // The Main Stack pointer
    SYSM_PSP = 9,       // The Process Stack pointer
    SYSM_PRIMASK = 16,  // Register to mask out configurable exceptions
    SYSM_CONTROL = 20,  // Stack select, Thread mode privilege
};

static const std::map<int, const std::string> sysm_name = {
    { SYSM_APSR,         "apsr" },
    { SYSM_IAPSR,        "iapsr" },
    { SYSM_EAPSR,        "eapsr" },
    { SYSM_XPSR,         "xpsr" },
    { SYSM_IPSR,         "ipsr" },
    { SYSM_EPSR,         "epsr" },
    { SYSM_IEPSR,        "iepsr" },
    { SYSM_MSP,          "msp" },
    { SYSM_PSP,          "psp" },
    { SYSM_PRIMASK,      "primask" },
    { SYSM_CONTROL,      "control" },
};

Processor::Processor(sc_core::sc_module_name const name, bool debug)
    : sc_module(name), instr_bus("instr_bus")
{
    irq_line_socket.register_b_transport(this, &Processor::call_interrupt);

    instr_bus.register_invalidate_direct_mem_ptr(this, &Processor::invalidate_direct_mem_ptr);

    if (!debug) {
        SC_THREAD(cpu_thread);
    }

    // Machine starts in Thread mode after Reset.
    mode = Mode::THREAD_MODE;

    //
    // Initial values.
    //
    psr.u32 = 0;
    primask.u32 = 0;
    control.u32 = 0;
    psr.field.t = 1;
}

void Processor::raise_exception(uint32_t cause, uint32_t mtval)
{
    if (Log::is_verbose()) {
        const char *name = "Unknown Exception";
        //switch (cause & MCAUSE_EXCEPTION_CODE) {
        //case EXCEPTION_CAUSE_INSTRUCTION_ACCESS:
        //    name = "Instruction Access Fault";
        //    break;
        //case EXCEPTION_CAUSE_ILLEGAL_INSTRUCTION:
        //    name = "Illegal Instruction";
        //    break;
        //case EXCEPTION_CAUSE_BREAKPOINT:
        //    name = "Breakpoint";
        //    break;
        //case EXCEPTION_CAUSE_LOAD_MISALIGN:
        //    name = "Load Misalign";
        //    break;
        //case EXCEPTION_CAUSE_LOAD_ACCESS_FAULT:
        //    name = "Load Access Fault";
        //    break;
        //case EXCEPTION_CAUSE_STORE_MISALIGN:
        //    name = "Store Misalign";
        //    break;
        //case EXCEPTION_CAUSE_STORE_ACCESS_FAULT:
        //    name = "Store Access Fault";
        //    break;
        //case EXCEPTION_CAUSE_ECALL_U:
        //    name = "Syscall";
        //    break;
        //case EXCEPTION_CAUSE_ECALL_M:
        //    name = "Syscall from Machine mode";
        //    break;
        //}
        Log::out() << "-------- " << name << std::endl;
    }

    // Save info about the trap.
    //set_csr(CSR_MEPC, get_pc());
    //set_csr(CSR_MTVAL, mtval);
    //set_csr(CSR_MCAUSE, cause);

    //
    // Update mstatus: disable interrupts.
    //
    //uint32_t old_status = get_csr(CSR_MSTATUS);
    //uint32_t new_status = old_status & MSTATUS_TW;

    // Copy MIE to MPIE.
    //if (old_status & MSTATUS_MIE)
    //    new_status |= MSTATUS_MPIE;

    // Set previous privilege mode.
    //new_status |= get_priv() << MSTATUS_MPP_shift;

    //set_csr(CSR_MSTATUS, new_status);

    // Jump to the trap vector.
    //uint32_t mtvec = get_csr(CSR_MTVEC);
    uint32_t new_pc = 0 /*mtvec & ~1*/;
    //if ((cause & MCAUSE_INTERRUPT_FLAG) && (mtvec & 1)) {
    //    // Interrupt in vector mode.
    //    new_pc += (cause & MCAUSE_EXCEPTION_CODE) * 4;
    //}
    //set_pc(new_pc);
    if (Log::is_verbose()) {
        Log::out() << "-------- Vector 0x" << std::hex << new_pc << std::endl;
    }

    // Switch to Machine mode.
    //set_priv(MSTATUS_MPP_MACHINE);
}

void Processor::terminate_simulation(const std::string &reason) const
{
    std::cout << std::endl
              << reason << std::endl;

    Log::out() << reason << std::endl;

    sc_core::sc_stop();
    sc_core::wait(sc_core::SC_ZERO_TIME);
}

bool Processor::cpu_process_interrupt()
{
    //uint32_t csr_temp;
    bool ret_value = false;

    if (interrupt) {
        //csr_temp = get_csr(CSR_MSTATUS);
        //if ((csr_temp & MSTATUS_MIE) == 0) {
        //    Log::err() << "interrupt delayed" << std::endl;
        //    return ret_value;
        //}
    } else {
        if (!irq_already_down) {
            //TODO: deactivate interrupt
            //csr_temp = get_csr(CSR_MIP);
            //csr_temp &= ~MIP_MEIP;
            //set_csr(CSR_MIP, csr_temp);
            irq_already_down = true;
        }
    }

    return ret_value;
}

//
// Get new value of instruction at PC.
//
void Processor::fetch_instruction()
{
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    union {
        uint8_t u8[4];
        uint16_t u16[2];
    } buf;

    if (dmi_ptr_valid) {
        /* if memory_offset at Memory module is set, this won't work */
        memcpy(&buf.u8, dmi_ptr + register_bank.getPC(), 4);
        delay += dmi_read_latency;
#if 0
        if (Log::is_verbose() && register_bank.getPC() >= 0x40000000 && register_bank.getPC() <= 0x4005ffff) {
            Log::out() << "-------- Fetch from ROM" << std::endl;
        }
#endif
    } else {
        tlm::tlm_generic_payload trans;
        trans.set_command(tlm::TLM_READ_COMMAND);
        trans.set_data_ptr(reinterpret_cast<unsigned char *>(&buf));
        trans.set_data_length(4);
        trans.set_streaming_width(4);       // = data_length to indicate no streaming
        trans.set_byte_enable_ptr(nullptr); // 0 indicates unused
        trans.set_dmi_allowed(false);       // Mandatory initial value
        trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
        trans.set_address(register_bank.getPC());

        instr_bus->b_transport(trans, delay);
        if (trans.is_response_error()) {
            Log::err() << "Bad Fetch at 0x" << std::hex << register_bank.getPC() << std::endl;
            SC_REPORT_ERROR("CPU base", "Read memory");
        }

        if (trans.is_dmi_allowed()) {
            tlm::tlm_dmi dmi_data;
            dmi_ptr_valid = instr_bus->get_direct_mem_ptr(trans, dmi_data);
            if (dmi_ptr_valid) {
                // std::cout << "Get DMI_PTR " << std::endl;
                dmi_ptr = dmi_data.get_dmi_ptr();
                dmi_read_latency = dmi_data.get_read_latency();
            }
        }
    }
    wait(delay);

    // Convert from little endian.
    instruction = (buf.u16[0] << 16) | buf.u16[1];
}

bool Processor::cpu_step()
{
    bool PC_not_affected = false;
    bool breakpoint = false;
    unsigned pc_increment = arm_opcode_length(instruction);

    fetch_instruction();

    if (Log::is_verbose()) {
        auto &out = Log::out();
        out << std::hex << std::setw(8) << std::setfill('0') << register_bank.getPC() << ": ";
        if (pc_increment == 2)
            out << std::setw(4) << (uint16_t)instruction << "     ";
        else
            out << std::setw(8) << instruction << " ";
        out << arm_disassemble(instruction, register_bank.getPC()) << std::endl;
    }

    // Execute instruction.
    PC_not_affected = base_inst.process_instruction(instruction, &breakpoint);

    if (breakpoint) {
        std::cout << "Breakpoint set to true" << std::endl;
        PC_not_affected = false;
    }

    instructions_executed++;

    if (PC_not_affected) {
        inc_pc(pc_increment);
    }

    return breakpoint;
}

void Processor::cpu_thread()
{
    while (true) {
        sc_core::wait(sc_core::SC_ZERO_TIME);

        /* Process one instruction */
        cpu_step();

        /* Process IRQ (if any) */
        cpu_process_interrupt();
    }
}

void Processor::call_interrupt(tlm::tlm_generic_payload &m_trans, sc_core::sc_time &delay)
{
    interrupt = true;
    /* Socket caller send a cause (its id) */
    memcpy(&int_cause, m_trans.get_data_ptr(), sizeof(uint32_t));
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
    //TODO: update CPU state when changing modes.
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
        Log::err() << "Load error at 0x" << std::hex << std::setw(8) << std::setfill('0') << addr << std::endl;
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
        SC_REPORT_ERROR("Memory", "Write");
    }
}

uint32_t Processor::get_sysreg(int sysm)
{
    switch (sysm) {
    //TODO
    default:
        Log::err() << "Read unknown sysreg 0x" << std::hex << std::setw(3) << std::setfill('0') << sysm << std::endl;
        SC_REPORT_ERROR("SYSREG", "Read");
        return 0;
    }
}

//
// Update system register unconditionally, and print.
//
void Processor::update_sysreg(uint32_t &reg, uint32_t value, uint32_t mask, const std::string &name)
{
    reg = (reg & ~mask) | (value & mask);

    if (Log::is_verbose()) {
        auto &out = Log::out();
        out << "          " << name << " = " << std::hex << std::setw(8)
            << std::setfill('0') << value << std::endl;
    }
}

//
// Set value of CSR register.
// Only writable bits are modified.
//
void Processor::set_sysreg(int sysm, uint32_t value)
{
    switch (sysm) {
    default:
        // Exception on write.
        raise_exception(EXCEPTION_CAUSE_ILLEGAL_INSTRUCTION, instruction);
        return;
    //TODO
    }
}

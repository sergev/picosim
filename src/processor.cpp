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
// Writable bits of CSRs.
//
enum {
    MASK_MSTATUS  = MSTATUS_UIE | MSTATUS_MIE | MSTATUS_UPIE | MSTATUS_MPIE | MSTATUS_MPP | MSTATUS_TW,
    MASK_USTATUS  = MSTATUS_UIE | MSTATUS_UPIE,
    MASK_MTVEC    = 0xffffff00,
    MASK_MEPC     = 0xfffffffe,
    MASK_MCAUSE   = 0x8000001f,
    MASK_TSELECT  = 0x00000007,
    MASK_TDATA1   = 0x001000cf,
    MASK_TCONTROL = 0x00000088,
    MASK_MPCER    = 0x00000fff,
    MASK_MPCMR    = 0x00000003,
    MASK_UCUSTOM0 = 0x00000fff,
    MASK_UCUSTOM1 = 0x00000003,
    MASK_UCUSTOM3 = 0x000000ff,
    MASK_UCUSTOM5 = 0x000000ff,
};

static const std::map<int, const std::string> csr_name = {
    { CSR_DCSR,         "dcsr" },       // Debug Control and Status
    { CSR_DPC,          "dpc" },        // Debug PC
    { CSR_DSCRATCH0,    "dscratch0" },  // Debug Scratch Register 0
    { CSR_DSCRATCH1,    "dscratch1" },  // Debug Scratch Register 1
    { CSR_MARCHID,      "marchid" },    // Machine Architecture ID
    { CSR_MCAUSE,       "mcause" },     // Machine Trap Cause
    { CSR_MEPC,         "mepc" },       // Machine Trap Program Counter
    { CSR_MHARTID,      "mhartid" },    // Machine Hart ID
    { CSR_MIMPID,       "mimpid" },     // Machine Implementation ID
    { CSR_MISA,         "misa" },       // Machine ISA
    { CSR_MPCCR,        "mpccr" },      // Machine Performance Counter Count
    { CSR_MPCER,        "mpcer" },      // Machine Performance Counter Event
    { CSR_MPCMR,        "mpcmr" },      // Machine Performance Counter Mode
    { CSR_MSCRATCH,     "mscratch" },   // Machine Scratch
    { CSR_MSTATUS,      "mstatus" },    // Machine Mode Status
    { CSR_MTVAL,        "mtval" },      // Machine Trap Value
    { CSR_MTVEC,        "mtvec" },      // Machine Trap Vector
    { CSR_MVENDORID,    "mvendorid" },  // Machine Vendor ID
    { CSR_PMPADDR(0),   "pmpaddr0" },   // Physical memory protection address registers 0-15
    { CSR_PMPADDR(1),   "pmpaddr1" },
    { CSR_PMPADDR(10),  "pmpaddr10" },
    { CSR_PMPADDR(11),  "pmpaddr11" },
    { CSR_PMPADDR(12),  "pmpaddr12" },
    { CSR_PMPADDR(13),  "pmpaddr13" },
    { CSR_PMPADDR(14),  "pmpaddr14" },
    { CSR_PMPADDR(15),  "pmpaddr15" },
    { CSR_PMPADDR(2),   "pmpaddr2" },
    { CSR_PMPADDR(3),   "pmpaddr3" },
    { CSR_PMPADDR(4),   "pmpaddr4" },
    { CSR_PMPADDR(5),   "pmpaddr5" },
    { CSR_PMPADDR(6),   "pmpaddr6" },
    { CSR_PMPADDR(7),   "pmpaddr7" },
    { CSR_PMPADDR(8),   "pmpaddr8" },
    { CSR_PMPADDR(9),   "pmpaddr9" },
    { CSR_PMPCFG(0),    "pmpcfg0" },    // Physical memory protection configuration
    { CSR_PMPCFG(1),    "pmpcfg1" },
    { CSR_PMPCFG(2),    "pmpcfg2" },
    { CSR_PMPCFG(3),    "pmpcfg3" },
    { CSR_TCONTROL,     "tcontrol" },   // Global Trigger Control
    { CSR_TDATA1,       "tdata1" },     // Trigger Abstract Data 1
    { CSR_TDATA2,       "tdata2" },     // Trigger Abstract Data 2
    { CSR_TSELECT,      "tselect" },    // Trigger Select Register
    { CSR_USTATUS,      "ustatus" },    // User Mode Status
    { CSR_UCUSTOM0,     "ucustom0" },   // User Custom Register 0
    { CSR_UCUSTOM1,     "ucustom1" },   // User Custom Register 1
    { CSR_UCUSTOM2,     "ucustom2" },   // User Custom Register 2
    { CSR_UCUSTOM3,     "ucustom3" },   // User Custom Register 3
    { CSR_UCUSTOM4,     "ucustom4" },   // User Custom Register 4
    { CSR_UCUSTOM5,     "ucustom5" },   // User Custom Register 5
};

Processor::Processor(sc_core::sc_module_name const name, bool debug)
    : sc_module(name), instr_bus("instr_bus")
{
    irq_line_socket.register_b_transport(this, &Processor::call_interrupt);

    instr_bus.register_invalidate_direct_mem_ptr(this, &Processor::invalidate_direct_mem_ptr);

    if (!debug) {
        SC_THREAD(cpu_thread);
    }

    // Start from ROM0.
    register_bank.setPC(0x40000000);

    // Machine mode.
    privilege = MSTATUS_MPP_MACHINE;

    //
    // Initial CSR values.
    //
    csr_mvendorid = 0x00000612;
    csr_marchid = 0x80000001;
    csr_mimpid = 1;
    csr_mhartid = 0;
    csr_misa = MISA_MXL_32 | MISA_M_EXTENSION | MISA_C_EXTENSION | MISA_U_EXTENSION | MISA_I_BASE;
    csr_mtvec = 1;
    csr_tdata1 = 0x23e00000;
    csr_mpcmr = 3;

    csr_pmpcfg[0] = 0x89888f88;
    csr_pmpcfg[1] = 0x888d898b;
    csr_pmpcfg[2] = 0x8f888d8f;
    csr_pmpcfg[3] = 0x90888b88;

    csr_pmpaddr[0] = 0x08000000;
    csr_pmpaddr[1] = 0x0a000000;
    csr_pmpaddr[2] = 0x0f000000;
    csr_pmpaddr[3] = 0x0ff20000;
    csr_pmpaddr[4] = 0x0ff38000;
    csr_pmpaddr[5] = 0x0ffc8000;
    csr_pmpaddr[6] = 0x10018000;
    csr_pmpaddr[7] = 0x100df000;
    csr_pmpaddr[8] = 0x100f8000;
    csr_pmpaddr[9] = 0x10a00000;
    csr_pmpaddr[10] = 0x14000000;
    csr_pmpaddr[11] = 0x14000800;
    csr_pmpaddr[12] = 0x18000000;
    csr_pmpaddr[13] = 0x18040000;
    csr_pmpaddr[14] = 0x3fffffff;
    csr_pmpaddr[15] = 0x3fffffff;
}

void Processor::raise_exception(uint32_t cause, uint32_t mtval)
{
    if (Log::is_verbose()) {
        const char *name;
        switch (cause & MCAUSE_EXCEPTION_CODE) {
        case EXCEPTION_CAUSE_INSTRUCTION_ACCESS:
            name = "Instruction Access Fault";
            break;
        case EXCEPTION_CAUSE_ILLEGAL_INSTRUCTION:
            name = "Illegal Instruction";
            break;
        case EXCEPTION_CAUSE_BREAKPOINT:
            name = "Breakpoint";
            break;
        case EXCEPTION_CAUSE_LOAD_MISALIGN:
            name = "Load Misalign";
            break;
        case EXCEPTION_CAUSE_LOAD_ACCESS_FAULT:
            name = "Load Access Fault";
            break;
        case EXCEPTION_CAUSE_STORE_MISALIGN:
            name = "Store Misalign";
            break;
        case EXCEPTION_CAUSE_STORE_ACCESS_FAULT:
            name = "Store Access Fault";
            break;
        case EXCEPTION_CAUSE_ECALL_U:
            name = "Syscall";
            break;
        case EXCEPTION_CAUSE_ECALL_M:
            name = "Syscall from Machine mode";
            break;
        default:
            name = "Unknown Exception";
            break;
        }
        Log::out() << "-------- " << name << std::endl;
    }

    // Save info about the trap.
    set_csr(CSR_MEPC, get_pc());
    set_csr(CSR_MTVAL, mtval);
    set_csr(CSR_MCAUSE, cause);

    //
    // Update mstatus: disable interrupts.
    //
    uint32_t old_status = get_csr(CSR_MSTATUS);
    uint32_t new_status = old_status & MSTATUS_TW;

    // Copy MIE to MPIE.
    if (old_status & MSTATUS_MIE)
        new_status |= MSTATUS_MPIE;

    // Set previous privilege mode.
    new_status |= get_priv() << MSTATUS_MPP_shift;

    set_csr(CSR_MSTATUS, new_status);

    // Jump to the trap vector.
    uint32_t mtvec = get_csr(CSR_MTVEC);
    uint32_t new_pc = mtvec & ~1;
    if ((cause & MCAUSE_INTERRUPT_FLAG) && (mtvec & 1)) {
        // Interrupt in vector mode.
        new_pc += (cause & MCAUSE_EXCEPTION_CODE) * 4;
    }
    set_pc(new_pc);
    if (Log::is_verbose()) {
        Log::out() << "-------- Vector 0x" << std::hex << new_pc << std::endl;
    }

    // Switch to Machine mode.
    set_priv(MSTATUS_MPP_MACHINE);
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
    uint32_t csr_temp;
    bool ret_value = false;

    if (interrupt) {
        csr_temp = get_csr(CSR_MSTATUS);
        if ((csr_temp & MSTATUS_MIE) == 0) {
            Log::err() << "interrupt delayed" << std::endl;
            return ret_value;
        }

        //TODO: implement esp32c3 interrupt controller
        //csr_temp = get_csr(CSR_MIP);
        if (/*(csr_temp & MIP_MEIP) ==*/ 0) {
            //csr_temp |= MIP_MEIP; // MEIP bit in MIP register (11th bit)
            //set_csr(CSR_MIP, csr_temp);
            Log::err() << "Interrupt!" << std::endl;

            /* updated MEPC register */
            uint32_t old_pc = register_bank.getPC();
            set_csr(CSR_MEPC, old_pc);
            Log::out() << "Old PC Value 0x" << std::hex << old_pc << std::dec << std::endl;

            /* update MCAUSE register */
            set_csr(CSR_MCAUSE, 0x80000000);

            /* set new PC address */
            uint32_t new_pc = get_csr(CSR_MTVEC);
            // new_pc = new_pc & 0xFFFFFFFC; // last two bits always to 0
            Log::err() << "NEW PC Value 0x" << std::hex << new_pc << std::dec << std::endl;
            register_bank.setPC(new_pc);

            ret_value = true;
            interrupt = false;
            irq_already_down = false;
        }
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

bool Processor::cpu_step()
{
    bool PC_not_affected = false;
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

    /* Get new PC value */
    if (dmi_ptr_valid) {
        /* if memory_offset at Memory module is set, this won't work */
        memcpy(&instruction, dmi_ptr + register_bank.getPC(), 4);
        delay += dmi_read_latency;
#if 1
        if (Log::is_verbose() && register_bank.getPC() >= 0x40000000 && register_bank.getPC() <= 0x4005ffff) {
            Log::out() << "-------- Fetch from ROM" << std::endl;
        }
#endif
    } else {
        tlm::tlm_generic_payload trans;
        trans.set_command(tlm::TLM_READ_COMMAND);
        trans.set_data_ptr(reinterpret_cast<unsigned char *>(&instruction));
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

    bool breakpoint = false;
    auto extension = check_extension();
    bool incPCby2 = (extension == C_EXTENSION);

    if (Log::is_verbose()) {
        auto &out = Log::out();
        out << std::hex << std::setw(8) << std::setfill('0') << register_bank.getPC() << ": ";
        if (incPCby2)
            out << std::setw(4) << (uint16_t)instruction << "     ";
        else
            out << std::setw(8) << instruction << " ";
        out << riscv_disassemble(instruction) << std::endl;
    }

    /* check what type of instruction is and execute it */
    switch (check_extension()) {
    case BASE_EXTENSION:
        PC_not_affected = base_inst.process_instruction(instruction, &breakpoint);
        break;
    case C_EXTENSION:
        PC_not_affected = c_inst.process_instruction(instruction, &breakpoint);
        break;
    case M_EXTENSION:
        PC_not_affected = m_inst.process_instruction(instruction);
        break;
    // case A_EXTENSION:
    //    PC_not_affected = a_inst.process_instruction(instruction);
    //    break;
    default:
        std::cout << "Extension not implemented yet" << std::endl;
        std::cout << std::hex << "0x" << instruction << std::dec << std::endl;
    }

    // Increment the HW counter.
    if (csr_ucustom[0] != 0 && csr_ucustom[1] != 0) {
        csr_ucustom[2] += 1;
    }

    if (breakpoint) {
        std::cout << "Breakpoint set to true" << std::endl;
        PC_not_affected = false;
    }

    instructions_executed++;

    if (PC_not_affected) {
        inc_pc(incPCby2 ? 2 : 4);
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

extension_t Processor::check_extension() const
{
    if (((instruction & 0x7F) == 0b0110011) && (((instruction & 0x7F000000) >> 25) == 0b0000001)) {
        return M_EXTENSION;
    }
    if ((instruction & 0x7F) == 0b0101111) {
        return A_EXTENSION;
    }
    if ((instruction & 0x03) == 0b11) {
        return BASE_EXTENSION;
    }
    if ((instruction & 0x03) == 0b00) {
        return C_EXTENSION;
    }
    if ((instruction & 0x03) == 0b01) {
        return C_EXTENSION;
    }
    if ((instruction & 0x03) == 0b10) {
        return C_EXTENSION;
    }
    std::cout << "Unknown" << std::endl;
    return UNKNOWN_EXTENSION;
}

void Processor::set_priv(int prv)
{
    switch (prv) {
    case MSTATUS_MPP_MACHINE:
        // Machine mode.
        break;
    case MSTATUS_MPP_USER:
        // User mode is supported by ESP32-C3.
        break;
    default:
        // Other modes are not supported: treat as User mode.
        prv = MSTATUS_MPP_USER;
        break;
    }
    privilege = prv;
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

uint32_t Processor::get_csr(int csr)
{
    switch (csr) {
    case CSR_MARCHID:
        // Machine Architecture ID
        return csr_marchid;
    case CSR_MCAUSE:
        // Machine Trap Cause
        return csr_mcause;
    case CSR_MEPC:
        // Machine Trap Program Counter
        return csr_mepc;
    case CSR_MHARTID:
        // Machine Hart ID
        return csr_mhartid;
    case CSR_MIMPID:
        // Machine Implementation ID
        return csr_mimpid;
    case CSR_MISA:
        // Machine ISA
        return csr_misa;
    case CSR_MPCCR:
        // Machine Performance Counter Count
        return csr_mpccr;
    case CSR_MPCER:
        // Machine Performance Counter Event
        return csr_mpcer;
    case CSR_MPCMR:
        // Machine Performance Counter Mode
        return csr_mpcmr;
    case CSR_MSCRATCH:
        // Machine Scratch
        return csr_mscratch;
    case CSR_MSTATUS:
        // Machine Mode Status
        return csr_mstatus;
    case CSR_MTVAL:
        // Machine Trap Value
        return csr_mtval;
    case CSR_MTVEC:
        // Machine Trap Vector
        return csr_mtvec;
    case CSR_MVENDORID:
        // Machine Vendor ID
        return csr_mvendorid;
    case CSR_PMPADDR(0):
    case CSR_PMPADDR(1):
    case CSR_PMPADDR(2):
    case CSR_PMPADDR(3):
    case CSR_PMPADDR(4):
    case CSR_PMPADDR(5):
    case CSR_PMPADDR(6):
    case CSR_PMPADDR(7):
    case CSR_PMPADDR(8):
    case CSR_PMPADDR(9):
    case CSR_PMPADDR(10):
    case CSR_PMPADDR(11):
    case CSR_PMPADDR(12):
    case CSR_PMPADDR(13):
    case CSR_PMPADDR(14):
    case CSR_PMPADDR(15):
        // Physical memory protection address registers 0-15
        return csr_pmpaddr[csr - CSR_PMPADDR(0)];
    case CSR_PMPCFG(0):
    case CSR_PMPCFG(1):
    case CSR_PMPCFG(2):
    case CSR_PMPCFG(3):
        // Physical memory protection configuration
        return csr_pmpcfg[csr - CSR_PMPCFG(0)];
    case CSR_TCONTROL:
        // Global Trigger Control
        return csr_tcontrol;
    case CSR_TDATA1:
        // Trigger Abstract Data 1
        return csr_tdata1;
    case CSR_TDATA2:
        // Trigger Abstract Data 2
        return csr_tdata2;
    case CSR_TSELECT:
        // Trigger Select Register
        return csr_tselect;
    case CSR_USTATUS:
        // User Mode Status
        return csr_ustatus;
    case CSR_UCUSTOM0:
    case CSR_UCUSTOM1:
    case CSR_UCUSTOM2:
    case CSR_UCUSTOM3:
    case CSR_UCUSTOM4:
    case CSR_UCUSTOM5:
        // User Custom Registers
        return csr_ucustom[csr - CSR_UCUSTOM0];
    default:
        Log::err() << "Read unknown CSR 0x" << std::hex << std::setw(3) << std::setfill('0') << csr << std::endl;
        SC_REPORT_ERROR("CSR", "Read");
        return 0;
    }
}

//
// Update the CSR value unconditionally, and print.
//
void Processor::update_csr(uint32_t &reg, uint32_t value, uint32_t mask, const std::string &name)
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
void Processor::set_csr(int csr, uint32_t value)
{
    switch (csr) {
    default:
    case CSR_MARCHID:   // Machine Architecture ID
    case CSR_MVENDORID: // Machine Vendor ID
    case CSR_MIMPID:    // Machine Implementation ID
    case CSR_MHARTID:   // Machine Hart ID
        // Exception on write.
        raise_exception(EXCEPTION_CAUSE_ILLEGAL_INSTRUCTION, instruction);
        return;
    case CSR_MCAUSE: // Machine Trap Cause
        update_csr(csr_mcause, value, MASK_MCAUSE, "mcause");
        return;
    case CSR_MEPC: // Machine Trap Program Counter
        update_csr(csr_mepc, value, MASK_MEPC, "mepc");
        return;
    case CSR_MISA: // Machine ISA
        // Write ignored.
        return;
    case CSR_MPCCR: // Machine Performance Counter Count
        update_csr(csr_mpccr, value, ~0U, "mpccr");
        return;
    case CSR_MPCER: // Machine Performance Counter Event
        update_csr(csr_mpcer, value, MASK_MPCER, "mpcer");
        return;
    case CSR_MPCMR: // Machine Performance Counter Mode
        update_csr(csr_mpcmr, value, MASK_MPCMR, "mpcmr");
        return;
    case CSR_MSCRATCH: // Machine Scratch
        update_csr(csr_mscratch, value, ~0U, "mscratch");
        return;
    case CSR_MSTATUS: // Machine Mode Status
        update_csr(csr_mstatus, value, MASK_MSTATUS, "mstatus");
        return;
    case CSR_MTVAL: // Machine Trap Value
        update_csr(csr_mtval, value, ~0U, "mtval");
        return;
    case CSR_MTVEC: // Machine Trap Vector
        update_csr(csr_mtvec, value, MASK_MTVEC, "mtvec");
        return;
    case CSR_PMPCFG(0): // Physical memory protection configuration
    case CSR_PMPCFG(1):
    case CSR_PMPCFG(2):
    case CSR_PMPCFG(3):
    case CSR_PMPADDR(0):
    case CSR_PMPADDR(1):
    case CSR_PMPADDR(2):
    case CSR_PMPADDR(3):
    case CSR_PMPADDR(4):
    case CSR_PMPADDR(5):
    case CSR_PMPADDR(6):
    case CSR_PMPADDR(7):
    case CSR_PMPADDR(8):
    case CSR_PMPADDR(9):
    case CSR_PMPADDR(10):
    case CSR_PMPADDR(11):
    case CSR_PMPADDR(12):
    case CSR_PMPADDR(13):
    case CSR_PMPADDR(14):
    case CSR_PMPADDR(15):
        // TODO: write to PMP registers ignored for now.
        if (Log::is_verbose()) {
            auto &out = Log::out();
            out << "          " << csr_name.at(csr) << " = " << std::hex << std::setw(8)
                << std::setfill('0') << value << " (write ignored)" << std::endl;
        }
        return;
    case CSR_TCONTROL: // Global Trigger Control
        update_csr(csr_tcontrol, value, MASK_TCONTROL, "tcontrol");
        return;
    case CSR_TDATA1: // Trigger Abstract Data 1
        update_csr(csr_tdata1, value, MASK_TDATA1, "tdata1");
        return;
    case CSR_TDATA2: // Trigger Abstract Data 2
        update_csr(csr_tdata2, value, ~0U, "tdata2");
        return;
    case CSR_TSELECT: // Trigger Select Register
        update_csr(csr_tselect, value, MASK_TSELECT, "tselect");
        return;
    case CSR_USTATUS: // User Mode Status
        update_csr(csr_ustatus, value, MASK_USTATUS, "ustatus");
        return;
    case CSR_UCUSTOM0: // User Custom Registers
        update_csr(csr_ucustom[0], value, MASK_UCUSTOM0, "ucustom0");
        return;
    case CSR_UCUSTOM1:
        update_csr(csr_ucustom[1], value, MASK_UCUSTOM1, "ucustom1");
        return;
    case CSR_UCUSTOM2:
        update_csr(csr_ucustom[2], value, ~0U, "ucustom2");
        return;
    case CSR_UCUSTOM3:
        update_csr(csr_ucustom[3], value, MASK_UCUSTOM3, "ucustom3");
        return;
    case CSR_UCUSTOM4:
        // Write ignored.
        return;
    case CSR_UCUSTOM5:
        update_csr(csr_ucustom[5], value, MASK_UCUSTOM5, "ucustom5");
        return;
    }
}

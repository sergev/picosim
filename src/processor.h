/*!
 \file processor.h
 \brief Main CPU class
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CPU_BASE_H
#define CPU_BASE_H

#include <unordered_map>

#include "log.h"
#include "memory.h"
#include "registers.h"
#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/tlm_quantumkeeper.h"

/**
 * @brief ISC_V CPU model
 * @param name name of the module
 */
class Processor : public sc_core::sc_module {
    SC_HAS_PROCESS(Processor);

public:
    /**
     * @brief Instruction Memory bus socket
     */
    tlm_utils::simple_initiator_socket<Processor> instr_bus{ "instr_bus" };

    /**
     * @brief Data memory bus socket
     */
    tlm_utils::simple_initiator_socket<Processor> data_bus{ "data_bus" };

    /**
     * @brief IRQ line socket
     */
    tlm_utils::simple_target_socket<Processor> irq_line_socket{ "irq" };

    /**
     * @brief Constructor
     * @param name Module name
     * @param debug To start debugging
     */
    Processor(sc_core::sc_module_name name, bool debug);

    //
    // Fetch two-byte value at given address.
    //
    uint16_t fetch16(unsigned address);

    //
    // Fetch and execute one instruction at PC.
    //
    void cpu_step();

    //
    // Execute current opcode.
    // Set pc_next when jump performed.
    //
    void process_opcode16();
    void process_opcode32();

    void raise_exception(uint32_t cause, uint32_t inst);
    void terminate_simulation(const std::string &reason) const;

    //
    // Allow Linux syscalls.
    //
    void set_linux_mode(bool on) { linux_mode = on; }

    /**
     * @brief Get statistics counters.
     */
    uint64_t get_instructions_executed() { return instructions_executed; }

    /**
     * Returns register value
     * @param  reg_num register number
     * @return         register value
     */
    int32_t get_reg(int reg_num)
    {
        if (reg_num == Registers::SP && control.field.spsel)
            return register_bank.getPSP();
        else
            return register_bank.getValue(reg_num);
    }

    /**
     * Set value for a register
     * @param reg_num register number
     * @param value   register value
     */
    void set_reg(int reg_num, int32_t value)
    {
        if (reg_num == Registers::PC) {
            // Branch to a given address.
            next_pc = value;
        } else if (reg_num == Registers::SP && control.field.spsel) {
            // Use Program stack.
            register_bank.setPSP(value);
        } else {
            register_bank.setValue(reg_num, value);
        }
    }

    //
    // Set value for a register, and N Z flags
    //
    void set_reg_nz(int reg_num, int32_t value)
    {
        set_reg(reg_num, value);
        xpsr.field.n = (value < 0);
        xpsr.field.z = (value == 0);
    }

    /**
     * Returns PC value
     * @return register value
     */
    uint32_t get_pc() { return register_bank.getPC(); }

    /**
     * Set PC value
     * @param value register value
     */
    void set_pc(uint32_t value) { register_bank.setPC(value); }

    /**
     * Increment PC value
     */
    void inc_pc(unsigned increment) { register_bank.incPC(increment); }

    //
    // Get system register.
    //
    uint32_t get_sysreg(unsigned sysm);

    //
    // Set system register.
    //
    void set_sysreg(unsigned sysm, uint32_t value);

    //
    // CPU runs in either Thread mode or in Handler mode.
    //
    enum class Mode {
        THREAD_MODE,
        HANDLER_MODE,
    };

    //
    // Return Thread/Handler mode
    //
    Mode get_mode() const { return mode; }

    //
    // Set Thread/handler mode
    //
    void set_mode(Mode m);

    /**
     * Read data memory.
     */
    uint32_t data_read(uint32_t addr, int size);
    uint8_t data_read8(uint32_t addr) { return data_read(addr, 1); }
    uint16_t data_read16(uint32_t addr) { return data_read(addr, 2); }
    uint32_t data_read32(uint32_t addr) { return data_read(addr, 4); }

    /**
     * Write data memory.
     */
    void data_write(uint32_t addr, uint32_t data, int size);
    void data_write8(uint32_t addr, uint8_t data) { data_write(addr, data, 1); }
    void data_write16(uint32_t addr, uint16_t data) { data_write(addr, data, 2); }
    void data_write32(uint32_t addr, uint32_t data) { data_write(addr, data, 4); }

    //
    // Special register field encoding
    //
    enum {
        SYSM_APSR    = 0,  // The flags from previous instructions
        SYSM_IAPSR   = 1,  // A composite of IPSR and APSR
        SYSM_EAPSR   = 2,  // A composite of EPSR and APSR
        SYSM_XPSR    = 3,  // A composite of all three PSR registers
        SYSM_IPSR    = 5,  // The Interrupt status register
        SYSM_EPSR    = 6,  // The execution status register
        SYSM_IEPSR   = 7,  // A composite of IPSR and EPSR
        SYSM_MSP     = 8,  // The Main Stack pointer
        SYSM_PSP     = 9,  // The Process Stack pointer
        SYSM_PRIMASK = 16, // Register to mask out configurable exceptions
        SYSM_CONTROL = 20, // Stack select, Thread mode privilege
    };

    //
    // Add two numbers, update PSR flags.
    //
    int32_t add_with_carry(int32_t x, int32_t y, bool carry_in);

private:
    /**
     * @brief Bank of CPU registers, including PC.
     */
    Registers register_bank;

    //
    // Current CPU mode: Thread or Handler.
    //
    Mode mode{ Mode::THREAD_MODE };

    //
    // XPSR - combined Program Status Register
    //
    // 31_30_29_28_________________________5_4_3_2_1_0
    //  n  z  c  v                          exception
    // ---APSR----                         ---IPSR----
    //
    union {
        uint32_t u32;
        struct {
            unsigned exception : 6; // Exception number being serviced
            unsigned _unused : 22;  // Zeroes
            unsigned v : 1;         // Overflow condition code
            unsigned c : 1;         // Carry condition code
            unsigned z : 1;         // Zero condition code
            unsigned n : 1;         // Negative condition code
        } field;
    } xpsr;

    //
    // PRIMASK register.
    //
    // 31_______________________________1__0
    // -----------reserved--------------- pm
    //
    union {
        uint32_t u32;
        struct {
            unsigned pm : 1;
        } field;
    } primask;

    //
    // CONTROL register.
    //
    // 31___________________________2___1_____0
    // -----------reserved----------- spsel npriv
    //
    union {
        uint32_t u32;
        struct {
            unsigned npriv : 1; // 1 = Thread mode has no privilege
            unsigned spsel : 1; // Select stack: 0 = use SP_main, 1 = use SP_process
        } field;
    } control;

    enum Exception {
        Reset             = 1,
        NMI               = 2,
        HardFault         = 3,
        SVCall            = 11,
        PendSV            = 14,
        SysTick           = 15,
        ExternalInterrupt = 16,
    };

    bool linux_mode{};                // Interpret Linux syscalls
    bool app_finished{};              // Set by exit() syscall.
    uint64_t instructions_executed{}; // Count instructions

    uint32_t opcode{};  // Current instruction, 16-bit or 32-bit
    uint32_t next_pc{}; // Set PC to this value after current instruction

    bool interrupt{};
    uint32_t int_cause{};
    bool irq_already_down{};

    bool dmi_ptr_valid{};
    unsigned char *dmi_ptr{};
    sc_core::sc_time dmi_read_latency;

    /**
     * main thread for CPU simulation
     * @brief CPU mai thread
     */
    void cpu_thread();

    /**
     *
     * @brief Process and triggers IRQ if all conditions met
     * @return true if IRQ is triggered, false otherwise
     */
    bool cpu_process_interrupt();

    /**
     * @brief callback for IRQ simple socket
     * @param trans transaction to perform (empty)
     * @param delay time to annotate
     *
     * it triggers an IRQ when called
     */
    void call_interrupt(tlm::tlm_generic_payload &trans, sc_core::sc_time &delay);

    /**
     * DMI pointer is not longer valid
     * @param start memory address region start
     * @param end memory address region end
     */
    void invalidate_direct_mem_ptr(sc_dt::uint64 start, sc_dt::uint64 end);

    //
    // Instructions.
    //
    void thumb_shift_imm();
    void thumb_add_sub();
    void thumb_arith_imm();
    void thumb_arith_reg();
    void thumb_add_cmp_mov();
    void thumb_bx();
    void thumb_load_literal();
    void thumb_load_store_reg();
    void thumb_load_store_imm();
    void thumb_load_store_stack();
    void thumb_add_sp_pc();
    void thumb_adjust_stack();
    void thumb_extend();
    void thumb_byterev();
    void thumb_breakpoint();
    void thumb_hint();
    void thumb_ldmia();
    void thumb_stmia();
    void thumb_pop();
    void thumb_push();
    void thumb_cond_branch();
    void thumb_branch();
    void thumb_branch_link();
    void thumb_barrier();
    void thumb_sysreg();
    void thumb_cps();
    void thumb_udf();
    void thumb_svc();
    void linux_syscall(int op);
};

#endif

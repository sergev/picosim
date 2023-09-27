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
#include "base_instructions.h"
#include "log.h"
#include "memory.h"
#include "registers.h"
#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/tlm_quantumkeeper.h"

enum {
    EXCEPTION_CAUSE_INSTRUCTION_ACCESS = 1,
    EXCEPTION_CAUSE_ILLEGAL_INSTRUCTION = 2,
    EXCEPTION_CAUSE_BREAKPOINT = 3,
    EXCEPTION_CAUSE_LOAD_MISALIGN = 4,
    EXCEPTION_CAUSE_LOAD_ACCESS_FAULT = 5,
    EXCEPTION_CAUSE_STORE_MISALIGN = 6,
    EXCEPTION_CAUSE_STORE_ACCESS_FAULT = 7,
    EXCEPTION_CAUSE_ECALL_U = 8,
    EXCEPTION_CAUSE_ECALL_M = 0xb,
};

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

    /**
     * @brief Fetch and execute one instruction.
     */
    bool cpu_step();

    void raise_exception(uint32_t cause, uint32_t inst);
    void terminate_simulation(const std::string &reason) const;

    /**
     * @brief Get statistics counters.
     */
    uint64_t get_instructions_executed() { return instructions_executed; }

    /**
     * Returns register value
     * @param  reg_num register number
     * @return         register value
     */
    int32_t get_reg(int reg_num) { return register_bank.getValue(reg_num); }

    /**
     * Set value for a register
     * @param reg_num register number
     * @param value   register value
     */
    void set_reg(int reg_num, int32_t value) { register_bank.setValue(reg_num, value); }

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
    uint32_t get_sysreg(int sysm);

    //
    // Set system register.
    //
    void set_sysreg(int sysm, uint32_t value);

    /**
     * Returns privilege value
     * @return privilege value
     */
    int get_priv() const { return privilege; }

    /**
     * Sets privilege value
     * @param prv new privilege
     */
    void set_priv(int prv);

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

private:
    /**
     * @brief Bank of CPU registers, including PC.
     */
    Registers register_bank;

    //
    // APSR - Application Program Status Register
    // IPSR - Interrupt Program Status Register
    // EPSR - Execution Program Status Register
    //
    // 31_30_29_28_______24___________9____5_4_3_2_1_0
    //  n  z  c  v        t           a    -exception-
    // ---APSR----       -----EPSR-----    ---IPSR----
    //
    union {
        uint32_t u32;
        struct {
            unsigned exception : 6;  // Exception number of the currently-executing exception
            unsigned _unused1  : 3;
            unsigned a         : 1;  // Alignment flag of SP for exception handler
            unsigned _unused2  : 14;
            unsigned t         : 1;  // Thumb mode, always 1
            unsigned _unused3  : 3;
            unsigned v         : 1;  // Overflow condition code
            unsigned c         : 1;  // Carry condition code
            unsigned z         : 1;  // Zero condition code
            unsigned n         : 1;  // Negative condition code
        } field;
    } psr;

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
            unsigned npriv : 1; // 1 = Thread mode has unprivileged access
            unsigned spsel : 1; // Select stack: 0 = use SP_main, 1 = use SP_process
        } field;
    } control;

    /**
     * User/Machine/Supervisor privilege (2 bits width)
     */
    int privilege;

    uint64_t instructions_executed{};

    Base_Instructions base_inst{ *this };

    uint32_t instruction{ 0 };
    bool interrupt{ false };
    uint32_t int_cause{ 0 };
    bool irq_already_down{ false };

    bool dmi_ptr_valid{ false };
    unsigned char *dmi_ptr{ nullptr };
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
    // Update system register unconditionally, and print.
    //
    void update_sysreg(uint32_t &reg, uint32_t value, uint32_t mask, const std::string &name);
};

#endif

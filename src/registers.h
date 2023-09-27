/*!
 \file Registers.h
 \brief Basic register file
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>
#include <iomanip>

#include "phys_memory.h"
#include "systemc"
#include "tlm.h"

/**
 * @brief Register file implementation
 */
class Registers {
public:
    enum {
        R0 = 0,
        R1 = 1,
        R2,
        R3,
        R4,
        R5,
        R6,
        R7,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15,
        SL = R10,   // Stack Limit
        FP = R11,   // Frame Pointer
        IP = R12,   // Intra-Procedure scratch register
        SP = R13,   // Main Stack Pointer
        LR = R14,   // Link Register
        PC = R15,   // Program Counter
    };

    /**
     * Set value for a register
     * @param reg_num register number
     * @param value   register value
     */
    void setValue(int reg_num, int32_t value);

    /**
     * Returns register value
     * @param  reg_num register number
     * @return         register value
     */
    int32_t getValue(int reg_num);

    /**
     * Returns PC value
     * @return PC value
     */
    uint32_t getPC() const { return register_bank[15]; }

    /**
     * Sets arbitraty value to PC
     * @param new_pc new address to PC
     */
    void setPC(uint32_t new_pc);

    /**
     * Increments PC couunter to next address
     */
    void incPC(unsigned increment)
    {
        register_bank[15] += increment;
    }

    /**
     * Dump register data to console
     */
    void dump();

private:
    /**
     * bank of registers (32 regs of 32bits each)
     */
    std::array<int32_t, 16> register_bank{};

    /**
     * Program stack pointer (32 bits width)
     */
    uint32_t register_psp{};
};

#endif

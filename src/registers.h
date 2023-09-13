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
        x0 = 0,
        x1 = 1,
        x2,
        x3,
        x4,
        x5,
        x6,
        x7,
        x8,
        x9,
        x10,
        x11,
        x12,
        x13,
        x14,
        x15,
        x16,
        x17,
        x18,
        x19,
        x20,
        x21,
        x22,
        x23,
        x24,
        x25,
        x26,
        x27,
        x28,
        x29,
        x30,
        x31,
        zero = x0,
        ra = x1,
        sp = x2,
        gp = x3,
        tp = x4,
        t0 = x5,
        t1 = x6,
        t2 = x7,
        s0 = x8,
        fp = x8,
        s1 = x9,
        a0 = x10,
        a1 = x11,
        a2 = x12,
        a3 = x13,
        a4 = x14,
        a5 = x15,
        a6 = x16,
        a7 = x17,
        s2 = x18,
        s3 = x19,
        s4 = x20,
        s5 = x21,
        s6 = x22,
        s7 = x23,
        s8 = x24,
        s9 = x25,
        s10 = x26,
        s11 = x27,
        t3 = x28,
        t4 = x29,
        t5 = x30,
        t6 = x31
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
    uint32_t getPC() const { return register_PC; }

    /**
     * Sets arbitraty value to PC
     * @param new_pc new address to PC
     */
    void setPC(uint32_t new_pc);

    /**
     * Increments PC couunter to next address
     */
    inline void incPC(unsigned increment)
    {
        register_PC += increment;
    }

    /**
     * Dump register data to console
     */
    void dump();

private:
    /**
     * bank of registers (32 regs of 32bits each)
     */
    std::array<int32_t, 32> register_bank = { { 0 } };

    /**
     * Program counter (32 bits width)
     */
    uint32_t register_PC{ 0 };
};

#endif

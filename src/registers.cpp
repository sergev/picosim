/*!
 \file registers.cpp
 \brief Basic register file implementation
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#include "registers.h"

static const char *ireg_name[32] = {
    "zero", "ra",   "sp",   "gp",   "tp",   "t0",   "t1",   "t2",
    "s0",   "s1",   "a0",   "a1",   "a2",   "a3",   "a4",   "a5",
    "a6",   "a7",   "s2",   "s3",   "s4",   "s5",   "s6",   "s7",
    "s8",   "s9",   "s10",  "s11",  "t3",   "t4",   "t5",   "t6",
};

static void dump_reg(const std::string &str, uint32_t val)
{
    std::cout << str;
    if (val <= 9)
        std::cout << std::right << std::setfill(' ') << std::setw(10) << val;
    else
        std::cout << "0x" << std::setfill('0') << std::setw(8) << val;
}

void Registers::dump()
{
    std::cout << "************************************" << std::endl;
    std::cout << "Registers dump" << std::hex << std::endl;

    dump_reg("x0 (zero): ", register_bank[0]);
    dump_reg("  x8 (s0/fp): ", register_bank[8]);
    dump_reg("  x16 (a6): ", register_bank[16]);
    dump_reg("   x24 (s8): ", register_bank[24]); std::cout << std::endl;

    dump_reg("  x1 (ra): ", register_bank[1]);
    dump_reg("     x9 (s1): ", register_bank[9]);
    dump_reg("  x17 (a7): ", register_bank[17]);
    dump_reg("   x25 (s9): ", register_bank[25]); std::cout << std::endl;

    dump_reg("  x2 (sp): ", register_bank[2]);
    dump_reg("    x10 (a0): ", register_bank[10]);
    dump_reg("  x18 (s2): ", register_bank[18]);
    dump_reg("  x26 (s10): ", register_bank[26]); std::cout << std::endl;

    dump_reg("  x3 (gp): ", register_bank[3]);
    dump_reg("    x11 (a1): ", register_bank[11]);
    dump_reg("  x19 (s3): ", register_bank[19]);
    dump_reg("  x27 (s11): ", register_bank[27]); std::cout << std::endl;

    dump_reg("  x4 (tp): ", register_bank[4]);
    dump_reg("    x12 (a2): ", register_bank[12]);
    dump_reg("  x20 (s4): ", register_bank[20]);
    dump_reg("   x28 (t3): ", register_bank[28]); std::cout << std::endl;

    dump_reg("  x5 (t0): ", register_bank[5]);
    dump_reg("    x13 (a3): ", register_bank[13]);
    dump_reg("  x21 (s5): ", register_bank[21]);
    dump_reg("   x29 (t4): ", register_bank[29]); std::cout << std::endl;

    dump_reg("  x6 (t1): ", register_bank[6]);
    dump_reg("    x14 (a4): ", register_bank[14]);
    dump_reg("  x22 (s6): ", register_bank[22]);
    dump_reg("   x30 (t5): ", register_bank[30]); std::cout << std::endl;

    dump_reg("  x7 (t2): ", register_bank[7]);
    dump_reg("    x15 (a5): ", register_bank[15]);
    dump_reg("  x23 (s7): ", register_bank[23]);
    dump_reg("   x31 (t6): ", register_bank[31]); std::cout << std::endl;

    std::cout << "PC: 0x" << std::hex << register_PC << std::dec << std::endl;
    std::cout << "************************************" << std::endl;
}

void Registers::setValue(int reg_num, int32_t value)
{
    if ((reg_num != 0) && (reg_num < 32)) {
        register_bank[reg_num] = value;

        if (Log::is_verbose()) {
            Log::out() << "          " << ireg_name[reg_num] << " = " << std::hex
                       << std::setw(8) << std::setfill('0') << value << std::endl;
        }
    }
}

int32_t Registers::getValue(int reg_num)
{
    if ((reg_num >= 0) && (reg_num < 32)) {
        return register_bank[reg_num];
    } else {
        return static_cast<int32_t>(0xFFFFFFFF);
    }
}

void Registers::setPC(uint32_t new_pc)
{
    register_PC = new_pc;
}

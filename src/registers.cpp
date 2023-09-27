/*!
 \file registers.cpp
 \brief Basic register file implementation
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#include "registers.h"

static const char *reg_name[32] = {
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "sl", "fp", "ip", "sp", "lr", "pc",
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

    dump_reg("r0: ", register_bank[0]);
    dump_reg("  r8: ", register_bank[8]);
    std::cout << std::endl;

    dump_reg("  r1: ", register_bank[1]);
    dump_reg("     r9: ", register_bank[9]);
    std::cout << std::endl;

    dump_reg("  r2: ", register_bank[2]);
    dump_reg("    r10 (sl): ", register_bank[10]);
    std::cout << std::endl;

    dump_reg("  r3: ", register_bank[3]);
    dump_reg("    r11 (fp): ", register_bank[11]);
    std::cout << std::endl;

    dump_reg("  r4: ", register_bank[4]);
    dump_reg("    r12 (ip): ", register_bank[12]);
    std::cout << std::endl;

    dump_reg("  r5: ", register_bank[5]);
    dump_reg("    r13 (sp): ", register_bank[13]);
    std::cout << std::endl;

    dump_reg("  r6: ", register_bank[6]);
    dump_reg("    r14 (lr): ", register_bank[14]);
    std::cout << std::endl;

    dump_reg("  r7: ", register_bank[7]);
    dump_reg("    r15 (pc): ", register_bank[15]);
    std::cout << std::endl;

    std::cout << "psp: 0x" << std::hex << register_psp << std::dec << std::endl;
    std::cout << "************************************" << std::endl;
}

void Registers::setValue(int reg_num, int32_t value)
{
    if (reg_num < 16) {
        register_bank[reg_num] = value;

        if (Log::is_verbose()) {
            Log::out() << "          " << reg_name[reg_num] << " = " << std::hex << std::setw(8)
                       << std::setfill('0') << value << std::endl;
        }
    }
}

int32_t Registers::getValue(int reg_num)
{
    if ((reg_num >= 0) && (reg_num < 16)) {
        return register_bank[reg_num];
    } else {
        return static_cast<int32_t>(0xFFFFFFFF);
    }
}

void Registers::setPC(uint32_t new_pc)
{
    register_bank[15] = new_pc;
}

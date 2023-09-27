#include <gtest/gtest.h>

#include "processor.h"

TEST(arith, add_with_carry)
{
    Processor cpu("cpu", false);

    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0);

    // Zero
    EXPECT_EQ(cpu.add_with_carry(0, 0, 0), 0);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x40000000); // Zero flag

    EXPECT_EQ(cpu.add_with_carry(-1, 1, 0), 0);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x60000000); // Zero+Carry flags

    EXPECT_EQ(cpu.add_with_carry(-1, 0, 1), 0);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x60000000); // Zero+Carry flags

    // Negative
    EXPECT_EQ(cpu.add_with_carry(0, -1, 0), -1);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x80000000); // Negative flag

    // 0x7502fe1f + 0xc015a134 -> 0x35189f53, carry
    EXPECT_EQ(cpu.add_with_carry(1963130399, -1072324300, 0), 890806099);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x20000000); // Carry flag

    // 0x8c832ed2 + 0xd306fde3 -> 0x5f8a2cb5, carry, overflow
    EXPECT_EQ(cpu.add_with_carry(-1937559854, -754516509, 0), 1602890933);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x30000000); // Carry+Overflow flags

    // 0x9b74a3db + 0x776dd37e -> 0x12e27759, carry
    EXPECT_EQ(cpu.add_with_carry(-1686854693, 2003686270, 0), 316831577);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x20000000); // Carry flag

    // 0xce671cdd + 0x549c13ba -> 0x23033097, carry
    EXPECT_EQ(cpu.add_with_carry(-832103203, 1419514810, 0), 587411607);
    EXPECT_EQ(cpu.get_sysreg(Processor::SYSM_XPSR), 0x20000000); // Carry flag
}

#include "sc_main.cpp"

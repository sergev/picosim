#include "util.h"

//
// Check ADC instruction.
//
TEST(opcode, adc)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/adc.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 20);
    EXPECT_EQ(sim.get_pc(), 0x8032);
    EXPECT_EQ(sim.get_reg(0), 0x35189f54); // 1963130399 - 1072324300 + 1
    EXPECT_EQ(sim.get_reg(1), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(2), 0x5f8a2cb6); // -1937559854 - 754516509 + 1
    EXPECT_EQ(sim.get_reg(3), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(4), 0x12e2775a); // -1686854693 + 2003686270 + 1
    EXPECT_EQ(sim.get_reg(5), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(6), 0x23033098); // -832103203 + 1419514810 + 1
    EXPECT_EQ(sim.get_reg(8), 0x20000000); // Carry flag
}

#include "sc_main.cpp"

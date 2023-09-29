#include "util.h"

//
// Check SBC instruction.
//
TEST(opcode, sbc)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/sbc.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 20);
    EXPECT_EQ(sim.get_pc(), 0x8032);
    EXPECT_EQ(sim.get_reg(0), 0xb4ed5ceb); // 1963130399 - (-1072324300)
    EXPECT_EQ(sim.get_reg(1), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0xb97c30ee); // -1937559854 - (-754516509) - 1
    EXPECT_EQ(sim.get_reg(3), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(4), 0x2406d05c); // -1686854693 - 2003686270 - 1
    EXPECT_EQ(sim.get_reg(5), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(6), 0x79cb0923); // -832103203 - 1419514810
    EXPECT_EQ(sim.get_reg(8), 0x30000000); // Carry+Overflow flags
}

#include "sc_main.cpp"

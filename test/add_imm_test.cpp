#include "util.h"

//
// Check ADD instruction with 8-bit immediate.
//
TEST(opcode, add_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/add_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 14);
    EXPECT_EQ(sim.get_pc(), 0x8024);
    EXPECT_EQ(sim.get_reg(0), 0x80000041);
    EXPECT_EQ(sim.get_reg(1), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0x0000005a);
    EXPECT_EQ(sim.get_reg(3), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(4), 0x0000008d);
    EXPECT_EQ(sim.get_reg(5), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(6), 0x000000a5);
    EXPECT_EQ(sim.get_reg(8), 0x00000000); // No flags
}

#include "sc_main.cpp"

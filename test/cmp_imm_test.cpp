#include "util.h"

//
// Check CMP instruction with 8-bit immediate.
//
TEST(opcode, cmp_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/cmp_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 14);
    EXPECT_EQ(sim.get_pc(), 0x8024);
    EXPECT_EQ(sim.get_reg(0), 0x80000000);
    EXPECT_EQ(sim.get_reg(1), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0x00000064);
    EXPECT_EQ(sim.get_reg(3), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(4), 0xffffffff);
    EXPECT_EQ(sim.get_reg(5), 0xa0000000); // Negative+Carry flags
    EXPECT_EQ(sim.get_reg(6), 0x00000000);
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
}

#include "sc_main.cpp"

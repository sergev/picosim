#include "util.h"

//
// Check SUB instruction with register + immediate.
//
TEST(opcode, sub_reg_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/sub_reg_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 14);
    EXPECT_EQ(sim.get_pc(), 0x8024);
    EXPECT_EQ(sim.get_reg(0), 0x7ffffffc);
    EXPECT_EQ(sim.get_reg(1), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0xfffffffe);
    EXPECT_EQ(sim.get_reg(3), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(4), 0xfffffff9);
    EXPECT_EQ(sim.get_reg(5), 0xa0000000); // Negative+Carry flags
    EXPECT_EQ(sim.get_reg(6), 0xfffffff9);
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
}

#include "sc_main.cpp"

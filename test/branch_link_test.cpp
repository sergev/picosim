#include "util.h"

//
// Check BL instruction.
//
TEST(opcode, branch_link)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/branch_link.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 7);
    EXPECT_EQ(sim.get_pc(), 0x801a);
    EXPECT_EQ(sim.get_reg(1), 0x8004);
    EXPECT_EQ(sim.get_reg(2), 0x8014);
    EXPECT_EQ(sim.get_reg(3), 0x800c);
}

#include "sc_main.cpp"

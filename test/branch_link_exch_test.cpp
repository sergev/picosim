#include "util.h"

//
// Check BLX instruction.
//
TEST(opcode, branch_link_exch)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/branch_link_exch.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 11);
    EXPECT_EQ(sim.get_pc(), 0x801c);
    EXPECT_EQ(sim.get_reg(1), 0x8004 | 1);
    EXPECT_EQ(sim.get_reg(2), 0x8016 | 1);
    EXPECT_EQ(sim.get_reg(3), 0x800e | 1);
}

#include "sc_main.cpp"

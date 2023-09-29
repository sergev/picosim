#include "util.h"

//
// Check B instruction.
//
TEST(opcode, branch_jump)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/branch_jump.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 4);
    EXPECT_EQ(sim.get_pc(), 0x800e);
}

#include "sc_main.cpp"

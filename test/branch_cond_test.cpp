#include "util.h"

//
// Check Bxx instructions.
//
TEST(opcode, branch_cond)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/branch_cond.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 257);
    EXPECT_EQ(sim.get_pc(), 0x8302);
}

#include "sc_main.cpp"

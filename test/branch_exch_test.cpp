#include "util.h"

//
// Check BX instruction.
//
TEST(opcode, branch_exch)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/branch_exch.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 7);
    EXPECT_EQ(sim.get_pc(), 0x8014);
}

#include "sc_main.cpp"

#include "util.h"

//
// Check NOP instruction.
// Also check DSB, DMB and ISB opcodes.
//
TEST(opcode, nop)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/nop.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 5);
    EXPECT_EQ(sim.get_pc(), 0x8010);
}

#include "sc_main.cpp"

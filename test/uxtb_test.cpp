#include "util.h"

//
// Check UXTB instruction.
//
TEST(opcode, uxtb)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/uxtb.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_pc(), 0x8012);
    EXPECT_EQ(sim.get_reg(0), 0x00000034);
    EXPECT_EQ(sim.get_reg(2), 0x000000e3);
    EXPECT_EQ(sim.get_reg(4), 0x0000007e);
    EXPECT_EQ(sim.get_reg(6), 0x000000ba);
}

#include "sc_main.cpp"

#include "util.h"

//
// Check SXTH instruction.
//
TEST(opcode, sxth)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/sxth.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_pc(), 0x8012);
    EXPECT_EQ(sim.get_reg(0), 0xffffa134);
    EXPECT_EQ(sim.get_reg(2), 0xfffffde3);
    EXPECT_EQ(sim.get_reg(4), 0xffffd37e);
    EXPECT_EQ(sim.get_reg(6), 0x000013ba);
}

#include "sc_main.cpp"

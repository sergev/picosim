#include "util.h"

//
// Check SXTB instruction.
//
TEST(opcode, sxtb)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/sxtb.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_pc(), 0x8012);
    EXPECT_EQ(sim.get_reg(0), 0x00000034);
    EXPECT_EQ(sim.get_reg(2), 0xffffffe3);
    EXPECT_EQ(sim.get_reg(4), 0x0000007e);
    EXPECT_EQ(sim.get_reg(6), 0xffffffba);
}

#include "sc_main.cpp"

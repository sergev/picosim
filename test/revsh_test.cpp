#include "util.h"

//
// Check REVSH instruction.
//
TEST(opcode, revsh)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/revsh.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_pc(), 0x8012);
    EXPECT_EQ(sim.get_reg(0), 0x000034a1);
    EXPECT_EQ(sim.get_reg(2), 0xffffe3fd);
    EXPECT_EQ(sim.get_reg(4), 0x00007ed3);
    EXPECT_EQ(sim.get_reg(6), 0xffffba13);
}

#include "sc_main.cpp"

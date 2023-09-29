#include "util.h"

//
// Check ORR instruction.
//
TEST(opcode, orr)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/orr.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0xf517ff3f);
    EXPECT_EQ(sim.get_reg(1), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(2), 0xdf87fff3);
    EXPECT_EQ(sim.get_reg(3), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(4), 0xff7df3ff);
    EXPECT_EQ(sim.get_reg(5), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(6), 0xffff1cdd);
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
}

#include "sc_main.cpp"

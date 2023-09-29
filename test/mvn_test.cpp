#include "util.h"

//
// Check MVN instruction.
//
TEST(opcode, mvn)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/mvn.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 14);
    EXPECT_EQ(sim.get_pc(), 0x8024);
    EXPECT_EQ(sim.get_reg(0), 0x3fea5ecb);
    EXPECT_EQ(sim.get_reg(1), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(2), 0x2cf9021c);
    EXPECT_EQ(sim.get_reg(3), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(4), 0x88922c81);
    EXPECT_EQ(sim.get_reg(5), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(6), 0xab63ec45);
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
}

#include "sc_main.cpp"

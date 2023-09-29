#include "util.h"

//
// Check EOR instruction.
//
TEST(opcode, eor)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/eor.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0xb5175f2b);
    EXPECT_EQ(sim.get_reg(1), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(2), 0x5f85d331);
    EXPECT_EQ(sim.get_reg(3), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(4), 0xec1970a5);
    EXPECT_EQ(sim.get_reg(5), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(6), 0x31981cdd);
    EXPECT_EQ(sim.get_reg(8), 0x00000000); // No flags
}

#include "sc_main.cpp"

#include "util.h"

//
// Check MUL instruction.
//
TEST(opcode, mul)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/mul.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0x00000000); // Zero
    EXPECT_EQ(sim.get_reg(1), 0x40000000); // Zero flag
    EXPECT_EQ(sim.get_reg(2), 0x6c840e36);
    EXPECT_EQ(sim.get_reg(3), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(4), 0x37b526ca);
    EXPECT_EQ(sim.get_reg(5), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(6), 0xb8bb5f92);
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
}

#include "sc_main.cpp"

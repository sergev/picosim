#include "util.h"

//
// Check AND instruction.
//
TEST(opcode, and)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/and.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0x4000a014);
    EXPECT_EQ(sim.get_reg(1), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(2), 0x80022cc2);
    EXPECT_EQ(sim.get_reg(3), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(4), 0x1364835a);
    EXPECT_EQ(sim.get_reg(5), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(6), 0xce670000);
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
}

#include "sc_main.cpp"

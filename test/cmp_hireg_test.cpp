#include "util.h"

//
// Check CMP instruction with high registers.
//
TEST(opcode, cmp_hireg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/cmp_hireg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 40);
    EXPECT_EQ(sim.get_pc(), 0x8060);
    EXPECT_EQ(sim.get_reg(0), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(1), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(2), 0x30000000); // Carry+Overflow flag
    EXPECT_EQ(sim.get_reg(3), 0x30000000); // Carry+Overflow flag
    EXPECT_EQ(sim.get_reg(4), 0xa0000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(5), 0xa0000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(6), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
}

#include "sc_main.cpp"

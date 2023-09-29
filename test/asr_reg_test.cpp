#include "util.h"

//
// Check ASR instruction with register.
//
TEST(opcode, asr_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/asr_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0xc015a134);
    EXPECT_EQ(sim.get_reg(1), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(2), 0xffffffff);
    EXPECT_EQ(sim.get_reg(3), 0xa0000000); // Negative+Carry flags
    EXPECT_EQ(sim.get_reg(4), 0x00000776);
    EXPECT_EQ(sim.get_reg(5), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(6), 0x00a93827);
    EXPECT_EQ(sim.get_reg(8), 0x00000000); // No flags
}

#include "sc_main.cpp"

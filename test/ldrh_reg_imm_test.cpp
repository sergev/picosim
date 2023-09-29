#include "util.h"

//
// Check LDRH instruction, with register plus immediate.
//
TEST(opcode, ldrh_reg_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/ldrh_reg_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 15);
    EXPECT_EQ(sim.get_pc(), 0x801e);
    EXPECT_EQ(sim.get_reg(0), 0x67c5);
    EXPECT_EQ(sim.get_reg(1), 0xe0d8);
    EXPECT_EQ(sim.get_reg(2), 0x8ce5);
    EXPECT_EQ(sim.get_reg(3), 0xf8f4);
    EXPECT_EQ(sim.get_reg(4), 0x0173);
    EXPECT_EQ(sim.get_reg(5), 0xa3db);
    EXPECT_EQ(sim.get_reg(6), 0x7fa2);
}

#include "sc_main.cpp"

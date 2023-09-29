#include "util.h"

//
// Check SUB instruction, with SP plus immediate.
//
TEST(opcode, sub_sp_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/sub_sp_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 15);
    EXPECT_EQ(sim.get_pc(), 0x801e);
    EXPECT_EQ(sim.get_reg(0), 1234567890);
    EXPECT_EQ(sim.get_reg(1), 1234567890);
    EXPECT_EQ(sim.get_reg(2), 1234567462);
    EXPECT_EQ(sim.get_reg(3), 1234567182);
    EXPECT_EQ(sim.get_reg(4), 1234567130);
    EXPECT_EQ(sim.get_reg(5), 1234566782);
    EXPECT_EQ(sim.get_reg(6), 1234566274);
}

#include "sc_main.cpp"

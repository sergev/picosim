#include "util.h"

//
// Check ADD instruction, with SP plus immediate.
//
TEST(opcode, add_sp_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/add_sp_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 15);
    EXPECT_EQ(sim.get_pc(), 0x801e);
    EXPECT_EQ(sim.get_reg(0), 1234567890);
    EXPECT_EQ(sim.get_reg(1), 1234567890);
    EXPECT_EQ(sim.get_reg(2), 1234568318);
    EXPECT_EQ(sim.get_reg(3), 1234568598);
    EXPECT_EQ(sim.get_reg(4), 1234568650);
    EXPECT_EQ(sim.get_reg(5), 1234568998);
    EXPECT_EQ(sim.get_reg(6), 1234569506);
}

#include "sc_main.cpp"

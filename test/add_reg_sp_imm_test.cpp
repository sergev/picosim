#include "util.h"

//
// Check ADD instruction, with register <- SP plus immediate.
//
TEST(opcode, add_reg_sp_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/add_reg_sp_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 10);
    EXPECT_EQ(sim.get_pc(), 0x8014);
    EXPECT_EQ(sim.get_reg(0), 1234567890);
    EXPECT_EQ(sim.get_reg(1), 1234568318);
    EXPECT_EQ(sim.get_reg(2), 1234568170);
    EXPECT_EQ(sim.get_reg(3), 1234567942);
    EXPECT_EQ(sim.get_reg(4), 1234568738);
    EXPECT_EQ(sim.get_reg(5), 1234568878);
    EXPECT_EQ(sim.get_reg(6), 1234568910);
}

#include "sc_main.cpp"

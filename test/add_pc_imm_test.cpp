#include "util.h"

//
// Check ADD instruction, with PC plus immediate.
//
TEST(opcode, add_pc_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/add_pc_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 8);
    EXPECT_EQ(sim.get_pc(), 0x8010);
    EXPECT_EQ(sim.get_reg(0), 0x8000 + 4 + 0x178);
    EXPECT_EQ(sim.get_reg(1), 0x8002 + 2 + 0x320);
    EXPECT_EQ(sim.get_reg(2), 0x8004 + 4 + 0x1dc);
    EXPECT_EQ(sim.get_reg(3), 0x8006 + 2 + 0x118);
    EXPECT_EQ(sim.get_reg(4), 0x8008 + 4 + 0x274);
    EXPECT_EQ(sim.get_reg(5), 0x800a + 2 + 0x220);
    EXPECT_EQ(sim.get_reg(6), 0x800c + 4 + 0x158);
}

#include "sc_main.cpp"

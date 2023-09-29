#include "util.h"

//
// Check MOVS instruction with immediate.
//
TEST(opcode, movs_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/movs_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_reg(0), 0xd3);
    EXPECT_EQ(sim.get_reg(1), 0x9d);
    EXPECT_EQ(sim.get_reg(2), 0x97);
    EXPECT_EQ(sim.get_reg(3), 0x1a);
    EXPECT_EQ(sim.get_reg(4), 0x91);
    EXPECT_EQ(sim.get_reg(5), 0xd7);
    EXPECT_EQ(sim.get_reg(6), 0x29);
    EXPECT_EQ(sim.get_reg(7), 0xab);
    EXPECT_EQ(sim.get_pc(), 0x8012);
}

#include "sc_main.cpp"

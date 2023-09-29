#include "util.h"

//
// Check MOVS instruction with registers.
//
TEST(opcode, movs_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/movs_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_reg(0), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(1), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0xc015a134);
    EXPECT_EQ(sim.get_reg(4), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(5), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(6), 0xd306fde3);
    EXPECT_EQ(sim.get_pc(), 0x8012);
}

#include "sc_main.cpp"

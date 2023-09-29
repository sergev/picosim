#include "util.h"

//
// Check LDR instruction, PC-relative.
//
TEST(opcode, ldr_pc)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/ldr_pc.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 8);
    EXPECT_EQ(sim.get_pc(), 0x8010);
    EXPECT_EQ(sim.get_reg(0), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(1), 0xc015a134);
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(4), 0xd965247d);
    EXPECT_EQ(sim.get_reg(5), 0xcf097d2e);
    EXPECT_EQ(sim.get_reg(6), 0x36204518);
}

#include "sc_main.cpp"

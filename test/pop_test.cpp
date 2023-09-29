#include "util.h"

//
// Check POP instruction.
//
TEST(opcode, pop)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/pop.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 5);
    EXPECT_EQ(sim.get_pc(), 0x800c);
    EXPECT_EQ(sim.get_reg(0), 0x36204518);
    EXPECT_EQ(sim.get_reg(1), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0xc015a134);
    EXPECT_EQ(sim.get_reg(4), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(5), 0xd965247d);
    EXPECT_EQ(sim.get_reg(6), 0xcf097d2e);
    EXPECT_EQ(sim.get_reg(13), 0x8010 + 28); // new SP
}

#include "sc_main.cpp"

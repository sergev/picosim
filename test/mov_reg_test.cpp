#include "util.h"

//
// Check MOV instruction with registers.
//
TEST(opcode, mov_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/mov_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 22);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(15), 0x802c);
    EXPECT_EQ(sim.get_reg(5),  0x8004);
    EXPECT_EQ(sim.get_reg(14), 0xc015a134);
    EXPECT_EQ(sim.get_reg(3),  0xc015a134);
    EXPECT_EQ(sim.get_reg(13), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(6),  0xd306fde3);
    EXPECT_EQ(sim.get_reg(12), 0x43f705a9);
    EXPECT_EQ(sim.get_reg(1),  0x43f705a9);
    EXPECT_EQ(sim.get_reg(11), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(2),  0x8c832ed2);
    EXPECT_EQ(sim.get_reg(10), 0xf83a2582);
    EXPECT_EQ(sim.get_reg(0),  0xf83a2582);
    EXPECT_EQ(sim.get_reg(9),  0xabe76d49);
    EXPECT_EQ(sim.get_reg(4),  0xabe76d49);
    EXPECT_EQ(sim.get_reg(8),  0xc5e3fe7d);
}

#include "sc_main.cpp"

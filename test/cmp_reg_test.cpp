#include "util.h"

//
// Check CMP instruction with registers.
//
TEST(opcode, cmp_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/cmp_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(1), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(4), 0x9b74a3db);
    EXPECT_EQ(sim.get_reg(5), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(6), 0xce671cdd);
    EXPECT_EQ(sim.get_reg(8), 0x30000000); // Carry+Overflow flags
}

#include "sc_main.cpp"

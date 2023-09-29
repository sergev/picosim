#include "util.h"

//
// Check CMN instruction.
//
TEST(opcode, cmn)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/cmn.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(1), 0x20000000); // Carry flags
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(4), 0x9b74a3db);
    EXPECT_EQ(sim.get_reg(5), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(6), 0xce671cdd);
    EXPECT_EQ(sim.get_reg(8), 0xa0000000); // Negative+Carry flag
}

#include "sc_main.cpp"

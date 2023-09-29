#include "util.h"

//
// Check CPSIE/CPSID instructions.
//
TEST(opcode, cpsie_cpsid)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/cpsie_cpsid.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 7);
    EXPECT_EQ(sim.get_pc(), 0x8014);
    EXPECT_EQ(sim.get_reg(0), 0);           // after cpsie
    EXPECT_EQ(sim.get_reg(1), 1);           // after cpsid
    EXPECT_EQ(sim.get_reg(2), 0);           // after cpsie
}

#include "sc_main.cpp"

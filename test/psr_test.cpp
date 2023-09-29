#include "util.h"

//
// Check MRS/MSR instructions with PSR registers.
//
TEST(opcode, mrs_msr_psr)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/psr.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 16);
    EXPECT_EQ(sim.get_pc(), 0x803c);
    EXPECT_EQ(sim.get_reg(0), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(1), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(2), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(3), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(4), 0x0000'0000);
    EXPECT_EQ(sim.get_reg(5), 0x0000'0000);
    EXPECT_EQ(sim.get_reg(6), 0x0000'0000);
}

#include "sc_main.cpp"

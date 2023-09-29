#include "util.h"

//
// Check MRS/MSR instructions with MSP/PSP/PRIMASK/COMTROL registers.
//
TEST(opcode, mrs_msr_sysreg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/sysreg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 20);
    EXPECT_EQ(sim.get_pc(), 0x8048);
    EXPECT_EQ(sim.get_reg(0), 0);
    EXPECT_EQ(sim.get_reg(1), 0xfffffffc);  // MSP all ones
    EXPECT_EQ(sim.get_reg(2), 0xfffffffc);  // PSP all ones
    EXPECT_EQ(sim.get_reg(3), 0x00000001);  // PRIMASK all ones
    EXPECT_EQ(sim.get_reg(4), 0x00000000);  // PRIMASK cleared
    EXPECT_EQ(sim.get_reg(5), 0x00000002);  // CONTROL all ones (except nPRIV bit)
    EXPECT_EQ(sim.get_reg(6), 0x00000000);  // CONTROL cleared
}

#include "sc_main.cpp"

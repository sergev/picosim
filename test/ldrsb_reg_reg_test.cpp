#include "util.h"

//
// Check LDRSB instruction, with register plus register.
//
TEST(opcode, ldrsb_reg_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/ldrsb_reg_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 22);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0xffffffd9);
    EXPECT_EQ(sim.get_reg(1), 0xffffffcd);
    EXPECT_EQ(sim.get_reg(2), 0x54);
    EXPECT_EQ(sim.get_reg(3), 0x01);
    EXPECT_EQ(sim.get_reg(4), 0x56);
    EXPECT_EQ(sim.get_reg(5), 0xffffffdb);
    EXPECT_EQ(sim.get_reg(6), 0x33);
}

#include "sc_main.cpp"

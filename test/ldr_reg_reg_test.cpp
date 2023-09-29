#include "util.h"

//
// Check LDR instruction, with register plus register.
//
TEST(opcode, ldr_reg_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/ldr_reg_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 22);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0x573d213c);
    EXPECT_EQ(sim.get_reg(1), 0x3903762c);
    EXPECT_EQ(sim.get_reg(2), 0x561469da);
    EXPECT_EQ(sim.get_reg(3), 0x4e6c6ac2);
    EXPECT_EQ(sim.get_reg(4), 0x494fa207);
    EXPECT_EQ(sim.get_reg(5), 0x9b74a3db);
    EXPECT_EQ(sim.get_reg(6), 0x6c94ee62);
    EXPECT_EQ(sim.get_reg(7), 40);
}

#include "sc_main.cpp"

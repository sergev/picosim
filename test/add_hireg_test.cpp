#include "util.h"

//
// Check ADD instruction with high registers.
//
TEST(opcode, add_hireg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/add_hireg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 39);
    EXPECT_EQ(sim.get_pc(), 0x8050);
    EXPECT_EQ(sim.get_reg(0), 0x8050);
    EXPECT_EQ(sim.get_reg(1), 0x7d998f56);
    EXPECT_EQ(sim.get_reg(2), 0x1ae58539);
    EXPECT_EQ(sim.get_reg(3), 0xb6103dca);
    EXPECT_EQ(sim.get_reg(4), 0xf60a2e7a);
    EXPECT_EQ(sim.get_reg(5), 0x8a504ad7);
    EXPECT_EQ(sim.get_reg(6), 0xedad1291);
    EXPECT_EQ(sim.get_reg(8), 0x6a313ea6);
    EXPECT_EQ(sim.get_reg(9), 0x5f8a2cb5);
    EXPECT_EQ(sim.get_reg(10), 0x12e27759); // SL
    EXPECT_EQ(sim.get_reg(11), 0x23033097); // FP
    EXPECT_EQ(sim.get_reg(12), 0xf5fa9c96); // IP
    EXPECT_EQ(sim.get_reg(13), 0x071565d4); // SP
    EXPECT_EQ(sim.get_reg(14), 0x61d56e94); // LR
}

#include "sc_main.cpp"

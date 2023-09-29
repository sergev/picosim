#include "util.h"

//
// Check REV instruction.
//
TEST(opcode, rev32)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/rev.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_pc(), 0x8012);
    EXPECT_EQ(sim.get_reg(0), 0x34a115c0);
    EXPECT_EQ(sim.get_reg(2), 0xe3fd06d3);
    EXPECT_EQ(sim.get_reg(4), 0x7ed36d77);
    EXPECT_EQ(sim.get_reg(6), 0xba139c54);
}

#include "sc_main.cpp"

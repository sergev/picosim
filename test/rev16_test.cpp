#include "util.h"

//
// Check REV16 instruction.
//
TEST(opcode, rev16)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/rev16.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_pc(), 0x8012);
    EXPECT_EQ(sim.get_reg(0), 0x15c034a1);
    EXPECT_EQ(sim.get_reg(2), 0x06d3e3fd);
    EXPECT_EQ(sim.get_reg(4), 0x6d777ed3);
    EXPECT_EQ(sim.get_reg(6), 0x9c54ba13);
}

#include "sc_main.cpp"

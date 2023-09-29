#include "util.h"

//
// Check STR instruction, SP-relative.
//
TEST(opcode, str_sp)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/str_sp.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 17);
    EXPECT_EQ(sim.get_pc(), 0x8022);
    EXPECT_EQ(sim.debug_load32(0x9044 + 124), 0x12345678);
    EXPECT_EQ(sim.debug_load32(0x9044 + 112), 0x23456789);
    EXPECT_EQ(sim.debug_load32(0x9044 + 88),  0x3456789a);
    EXPECT_EQ(sim.debug_load32(0x9044 + 64),  0x456789ab);
    EXPECT_EQ(sim.debug_load32(0x9044 + 36),  0x56789abc);
    EXPECT_EQ(sim.debug_load32(0x9044 + 0),   0x6789abcd);
    EXPECT_EQ(sim.debug_load32(0x9044 + 76),  0x789abcde);
}

#include "sc_main.cpp"

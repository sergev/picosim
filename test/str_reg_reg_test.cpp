#include "util.h"

//
// Check STR instruction, with register plus register.
//
TEST(opcode, str_reg_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/str_reg_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 29);
    EXPECT_EQ(sim.get_pc(), 0x803a);
    EXPECT_EQ(sim.debug_load32(0x906c + 124), 0x12345678);
    EXPECT_EQ(sim.debug_load32(0x906c + 112), 0x23456789);
    EXPECT_EQ(sim.debug_load32(0x906c + 88),  0x3456789a);
    EXPECT_EQ(sim.debug_load32(0x906c + 64),  0x456789ab);
    EXPECT_EQ(sim.debug_load32(0x906c + 36),  0x56789abc);
    EXPECT_EQ(sim.debug_load32(0x906c + 0),   0x6789abcd);
    EXPECT_EQ(sim.debug_load32(0x906c + 76),  0x789abcde);
}

#include "sc_main.cpp"

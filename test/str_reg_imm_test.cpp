#include "util.h"

//
// Check STR instruction, with register plus immediate.
//
TEST(opcode, str_reg_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/str_reg_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 22);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.debug_load32(0x905c + 124), 0x12345678);
    EXPECT_EQ(sim.debug_load32(0x905c + 112), 0x23456789);
    EXPECT_EQ(sim.debug_load32(0x905c + 88),  0x3456789a);
    EXPECT_EQ(sim.debug_load32(0x905c + 64),  0x456789ab);
    EXPECT_EQ(sim.debug_load32(0x905c + 36),  0x56789abc);
    EXPECT_EQ(sim.debug_load32(0x905c + 0),   0x6789abcd);
    EXPECT_EQ(sim.debug_load32(0x905c + 76),  0x789abcde);
}

#include "sc_main.cpp"

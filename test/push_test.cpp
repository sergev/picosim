#include "util.h"

//
// Check PUSH instruction.
//
TEST(opcode, push)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/push.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 15);
    EXPECT_EQ(sim.get_pc(), 0x801e);
    EXPECT_EQ(sim.get_reg(13), 0x9068 - 32);              // new SP
    EXPECT_EQ(sim.debug_load32(0x9068 - 32), 0x3456789a); // r2
    EXPECT_EQ(sim.debug_load32(0x9068 - 28), 0x456789ab); // r3
    EXPECT_EQ(sim.debug_load32(0x9068 - 24), 0x56789abc); // r4
    EXPECT_EQ(sim.debug_load32(0x9068 - 20), 0x789abcde); // r6
    EXPECT_EQ(sim.debug_load32(0x9068 - 16), 0x89abcdef); // r7
    EXPECT_EQ(sim.debug_load32(0x9068 - 12), 0x9abcdef1); // LR
    EXPECT_EQ(sim.debug_load32(0x9068 - 8),  0x12345678); // r0
    EXPECT_EQ(sim.debug_load32(0x9068 - 4),  0x23456789); // r1
}

#include "sc_main.cpp"

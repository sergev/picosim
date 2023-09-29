#include "util.h"

//
// Check STMIA instruction.
//
TEST(opcode, stmia)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/stmia.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 11);
    EXPECT_EQ(sim.get_pc(), 0x8016);
    EXPECT_EQ(sim.debug_load32(0x9038 + 0),  0x9038);     // r0
    EXPECT_EQ(sim.debug_load32(0x9038 + 4),  0x23456789); // r1
    EXPECT_EQ(sim.get_reg(0), 0x9038 + 8);                // new r0
    EXPECT_EQ(sim.debug_load32(0x9038 + 8),  0x3456789a); // r2
    EXPECT_EQ(sim.debug_load32(0x9038 + 12), 0x456789ab); // r3
    EXPECT_EQ(sim.debug_load32(0x9038 + 16), 0x56789abc); // r4
    EXPECT_EQ(sim.debug_load32(0x9038 + 20), 0x789abcde); // r6
    EXPECT_EQ(sim.debug_load32(0x9038 + 24), 0x89abcdef); // r7
    EXPECT_EQ(sim.get_reg(5), 0x9038 + 28);               // new r5
}

#include "sc_main.cpp"

#include "util.h"

//
// Check SUB instruction with three registers.
//
TEST(opcode, sub_reg_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/sub_reg_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0xb4ed5ceb); // 1963130399 - (-1072324300)
    EXPECT_EQ(sim.get_reg(1), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0xb97c30ef); // -1937559854 - (-754516509)
    EXPECT_EQ(sim.get_reg(3), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(4), 0x2406d05d); // -1686854693 - 2003686270
    EXPECT_EQ(sim.get_reg(5), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(6), 0x79cb0923); // -832103203 - 1419514810
    EXPECT_EQ(sim.get_reg(8), 0x30000000); // Carry+Overflow flags

    // Tested on RP2040 board:
    // 7502fe1f - c015a134 -> b4ed5ceb flags 90000000
    // 8c832ed2 - d306fde3 -> b97c30ef flags 80000000
    // 9b74a3db - 776dd37e -> 2406d05d flags 30000000
    // ce671cdd - 549c13ba -> 79cb0923 flags 30000000
}

#include "sc_main.cpp"

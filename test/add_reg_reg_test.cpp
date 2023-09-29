#include "util.h"

//
// Check ADD instruction with three registers.
//
TEST(opcode, add_reg_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/add_reg_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.get_reg(0), 0x35189f53); // 1963130399 - 1072324300
    EXPECT_EQ(sim.get_reg(1), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(2), 0x5f8a2cb5); // -1937559854 - 754516509
    EXPECT_EQ(sim.get_reg(3), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(4), 0x12e27759); // -1686854693 + 2003686270
    EXPECT_EQ(sim.get_reg(5), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(6), 0x23033097); // -832103203 + 1419514810
    EXPECT_EQ(sim.get_reg(8), 0x20000000); // Carry flag

    // Tested on RP2040 board:
    // 7502fe1f + c015a134 -> 35189f53 flags 20000000
    // 8c832ed2 + d306fde3 -> 5f8a2cb5 flags 30000000
    // 9b74a3db + 776dd37e -> 12e27759 flags 20000000
    // ce671cdd + 549c13ba -> 23033097 flags 20000000
}

#include "sc_main.cpp"

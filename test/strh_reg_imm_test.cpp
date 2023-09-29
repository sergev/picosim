#include "util.h"

//
// Check STRH instruction, with register plus immediate.
//
TEST(opcode, strh_reg_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/strh_reg_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 22);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.debug_load16(0x905c + 62), 0x1234);
    EXPECT_EQ(sim.debug_load16(0x905c + 58), 0x2345);
    EXPECT_EQ(sim.debug_load16(0x905c + 46), 0x3456);
    EXPECT_EQ(sim.debug_load16(0x905c + 34), 0x4567);
    EXPECT_EQ(sim.debug_load16(0x905c + 18), 0x5678);
    EXPECT_EQ(sim.debug_load16(0x905c + 0),  0x6789);
    EXPECT_EQ(sim.debug_load16(0x905c + 56), 0x789a);
}

#include "sc_main.cpp"

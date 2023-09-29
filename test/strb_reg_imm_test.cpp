#include "util.h"

//
// Check STRB instruction, with register plus immediate.
//
TEST(opcode, strb_reg_imm)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/strb_reg_imm.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 22);
    EXPECT_EQ(sim.get_pc(), 0x802c);
    EXPECT_EQ(sim.debug_load8(0x905c + 31), 0x12);
    EXPECT_EQ(sim.debug_load8(0x905c + 29), 0x23);
    EXPECT_EQ(sim.debug_load8(0x905c + 27), 0x34);
    EXPECT_EQ(sim.debug_load8(0x905c + 19), 0x45);
    EXPECT_EQ(sim.debug_load8(0x905c + 9),  0x56);
    EXPECT_EQ(sim.debug_load8(0x905c + 0),  0x67);
    EXPECT_EQ(sim.debug_load8(0x905c + 30), 0x78);
}

#include "sc_main.cpp"

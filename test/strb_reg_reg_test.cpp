#include "util.h"

//
// Check STRB instruction, with register plus register.
//
TEST(opcode, strb_reg_reg)
{
    Simulator sim;
    enable_trace();
    sim.read_elf_file(TEST_DIR "/test_files/strb_reg_reg.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 29);
    EXPECT_EQ(sim.get_pc(), 0x803a);
    EXPECT_EQ(sim.debug_load8(0x906c + 31), 0x12);
    EXPECT_EQ(sim.debug_load8(0x906c + 29), 0x23);
    EXPECT_EQ(sim.debug_load8(0x906c + 27), 0x34);
    EXPECT_EQ(sim.debug_load8(0x906c + 19), 0x45);
    EXPECT_EQ(sim.debug_load8(0x906c + 9),  0x56);
    EXPECT_EQ(sim.debug_load8(0x906c + 0),  0x67);
    EXPECT_EQ(sim.debug_load8(0x906c + 30), 0x78);
}

#include "sc_main.cpp"

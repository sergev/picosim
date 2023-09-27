#include "util.h"

//
// Check ADD instruction, with PC plus immediate.
//
TEST(opcode, add_pc_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa05e);      // add r0, pc, #0x178
    sim.debug_store16(0x8002, 0xa1c8);      // add r1, pc, #0x320
    sim.debug_store16(0x8004, 0xa277);      // add r2, pc, #0x1dc
    sim.debug_store16(0x8006, 0xa346);      // add r3, pc, #0x118
    sim.debug_store16(0x8008, 0xa49d);      // add r4, pc, #0x274
    sim.debug_store16(0x800a, 0xa588);      // add r5, pc, #0x220
    sim.debug_store16(0x800c, 0xa656);      // add r6, pc, #0x158
    sim.debug_store16(0x800e, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8010, 0xdf00);      // svc 0

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 11);
    EXPECT_EQ(sim.get_pc(), 0x801a);
    EXPECT_EQ(sim.get_reg(0), 0x8178);
    EXPECT_EQ(sim.get_reg(1), 0x8322);
    EXPECT_EQ(sim.get_reg(2), 0x81e0);
    EXPECT_EQ(sim.get_reg(3), 0x811e);
    EXPECT_EQ(sim.get_reg(4), 0x827c);
    EXPECT_EQ(sim.get_reg(5), 0x822a);
    EXPECT_EQ(sim.get_reg(6), 0x8164);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

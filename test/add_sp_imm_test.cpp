#include "util.h"

//
// Check ADD instruction, with SP plus immediate.
//
TEST(opcode, add_sp_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4805);      // ldr r0, [pc, #20] @ (8018 <_start+0x18>)
    sim.debug_store16(0x8002, 0x4685);      // mov sp, r0
    sim.debug_store16(0x8004, 0xa800);      // add r0, sp, #0
    sim.debug_store16(0x8006, 0xa96b);      // add r1, sp, #428 @ 0x1ac
    sim.debug_store16(0x8008, 0xaa46);      // add r2, sp, #280 @ 0x118
    sim.debug_store16(0x800a, 0xab0d);      // add r3, sp, #52 @ 0x34
    sim.debug_store16(0x800c, 0xacd4);      // add r4, sp, #848 @ 0x350
    sim.debug_store16(0x800e, 0xadf7);      // add r5, sp, #988 @ 0x3dc
    sim.debug_store16(0x8010, 0xaeff);      // add r6, sp, #1020 @ 0x3fc
    sim.debug_store16(0x8012, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8014, 0xdf00);      // svc 0
    sim.debug_store32(0x8018, 0x499602d2);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 11);
    EXPECT_EQ(sim.get_pc(), 0x8016);
    EXPECT_EQ(sim.get_reg(0), 1234567890);
    EXPECT_EQ(sim.get_reg(1), 1234568318);
    EXPECT_EQ(sim.get_reg(2), 1234568170);
    EXPECT_EQ(sim.get_reg(3), 1234567942);
    EXPECT_EQ(sim.get_reg(4), 1234568738);
    EXPECT_EQ(sim.get_reg(5), 1234568878);
    EXPECT_EQ(sim.get_reg(6), 1234568910);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

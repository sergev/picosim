#include "util.h"

//
// Check STRB instruction, with register plus register.
//
TEST(opcode, strb_reg_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x490e);      // ldr r1, [pc, #56]
    sim.debug_store16(0x8002, 0x221f);      // movs r2, #31
    sim.debug_store16(0x8004, 0x480e);      // ldr r0, [pc, #56]
    sim.debug_store16(0x8006, 0x5488);      // strb r0, [r1, r2]
    sim.debug_store16(0x8008, 0x4a0e);      // ldr r2, [pc, #56]
    sim.debug_store16(0x800a, 0x2319);      // movs r3, #25
    sim.debug_store16(0x800c, 0x490e);      // ldr r1, [pc, #56]
    sim.debug_store16(0x800e, 0x54d1);      // strb r1, [r2, r3]
    sim.debug_store16(0x8010, 0x4b0e);      // ldr r3, [pc, #56]
    sim.debug_store16(0x8012, 0x240f);      // movs r4, #15
    sim.debug_store16(0x8014, 0x4a0e);      // ldr r2, [pc, #56]
    sim.debug_store16(0x8016, 0x551a);      // strb r2, [r3, r4]
    sim.debug_store16(0x8018, 0x4c0a);      // ldr r4, [pc, #40]
    sim.debug_store16(0x801a, 0x250f);      // movs r5, #15
    sim.debug_store16(0x801c, 0x4b0d);      // ldr r3, [pc, #52]
    sim.debug_store16(0x801e, 0x5563);      // strb r3, [r4, r5]
    sim.debug_store16(0x8020, 0x4d0d);      // ldr r5, [pc, #52]
    sim.debug_store16(0x8022, 0x2601);      // movs r6, #1
    sim.debug_store16(0x8024, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x8026, 0x55ac);      // strb r4, [r5, r6]
    sim.debug_store16(0x8028, 0x4e04);      // ldr r6, [pc, #16]
    sim.debug_store16(0x802a, 0x2700);      // movs r7, #0
    sim.debug_store16(0x802c, 0x4d0c);      // ldr r5, [pc, #48]
    sim.debug_store16(0x802e, 0x55f5);      // strb r5, [r6, r7]
    sim.debug_store16(0x8030, 0x4f0c);      // ldr r7, [pc, #48]
    sim.debug_store16(0x8032, 0x200a);      // movs r0, #10
    sim.debug_store16(0x8034, 0x4e0c);      // ldr r6, [pc, #48]
    sim.debug_store16(0x8036, 0x543e);      // strb r6, [r7, r0]
    sim.debug_store16(0x8038, 0x2701);      // movs r7, #1
    sim.debug_store16(0x803a, 0xdf00);      // svc 0
    sim.debug_store32(0x803c, 0x0000906c);
    sim.debug_store32(0x8040, 0x00000012);
    sim.debug_store32(0x8044, 0x00009070);
    sim.debug_store32(0x8048, 0x00000023);
    sim.debug_store32(0x804c, 0x00009078);
    sim.debug_store32(0x8050, 0x00000034);
    sim.debug_store32(0x8054, 0x00000045);
    sim.debug_store32(0x8058, 0x00009074);
    sim.debug_store32(0x805c, 0x00000056);
    sim.debug_store32(0x8060, 0x00000067);
    sim.debug_store32(0x8064, 0x00009080);
    sim.debug_store32(0x8068, 0x00000078);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 30);
    EXPECT_EQ(sim.get_pc(), 0x803c);
    EXPECT_EQ(sim.debug_load8(0x906c + 31), 0x12);
    EXPECT_EQ(sim.debug_load8(0x906c + 29), 0x23);
    EXPECT_EQ(sim.debug_load8(0x906c + 27), 0x34);
    EXPECT_EQ(sim.debug_load8(0x906c + 19), 0x45);
    EXPECT_EQ(sim.debug_load8(0x906c + 9),  0x56);
    EXPECT_EQ(sim.debug_load8(0x906c + 0),  0x67);
    EXPECT_EQ(sim.debug_load8(0x906c + 30), 0x78);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

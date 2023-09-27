#include "util.h"

//
// Check STR instruction, with register plus register.
//
TEST(opcode, str_reg_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x490e);      // ldr r1, [pc, #56]
    sim.debug_store16(0x8002, 0x227c);      // movs r2, #124
    sim.debug_store16(0x8004, 0x480e);      // ldr r0, [pc, #56]
    sim.debug_store16(0x8006, 0x5088);      // str r0, [r1, r2]
    sim.debug_store16(0x8008, 0x4a0e);      // ldr r2, [pc, #56]
    sim.debug_store16(0x800a, 0x2364);      // movs r3, #100
    sim.debug_store16(0x800c, 0x490e);      // ldr r1, [pc, #56]
    sim.debug_store16(0x800e, 0x50d1);      // str r1, [r2, r3]
    sim.debug_store16(0x8010, 0x4b0e);      // ldr r3, [pc, #56]
    sim.debug_store16(0x8012, 0x243c);      // movs r4, #60
    sim.debug_store16(0x8014, 0x4a0e);      // ldr r2, [pc, #56]
    sim.debug_store16(0x8016, 0x511a);      // str r2, [r3, r4]
    sim.debug_store16(0x8018, 0x4c0e);      // ldr r4, [pc, #56]
    sim.debug_store16(0x801a, 0x253c);      // movs r5, #60
    sim.debug_store16(0x801c, 0x4b0e);      // ldr r3, [pc, #56]
    sim.debug_store16(0x801e, 0x5163);      // str r3, [r4, r5]
    sim.debug_store16(0x8020, 0x4d06);      // ldr r5, [pc, #24]
    sim.debug_store16(0x8022, 0x2624);      // movs r6, #36
    sim.debug_store16(0x8024, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x8026, 0x51ac);      // str r4, [r5, r6]
    sim.debug_store16(0x8028, 0x4e04);      // ldr r6, [pc, #16]
    sim.debug_store16(0x802a, 0x2700);      // movs r7, #0
    sim.debug_store16(0x802c, 0x4d0c);      // ldr r5, [pc, #48]
    sim.debug_store16(0x802e, 0x51f5);      // str r5, [r6, r7]
    sim.debug_store16(0x8030, 0x4f0c);      // ldr r7, [pc, #48]
    sim.debug_store16(0x8032, 0x2028);      // movs r0, #40
    sim.debug_store16(0x8034, 0x4e0c);      // ldr r6, [pc, #48]
    sim.debug_store16(0x8036, 0x503e);      // str r6, [r7, r0]
    sim.debug_store16(0x8038, 0x2701);      // movs r7, #1
    sim.debug_store16(0x803a, 0xdf00);      // svc 0
    sim.debug_store32(0x803c, 0x0000906c);
    sim.debug_store32(0x8040, 0x12345678);
    sim.debug_store32(0x8044, 0x00009078);
    sim.debug_store32(0x8048, 0x23456789);
    sim.debug_store32(0x804c, 0x00009088);
    sim.debug_store32(0x8050, 0x3456789a);
    sim.debug_store32(0x8054, 0x00009070);
    sim.debug_store32(0x8058, 0x456789ab);
    sim.debug_store32(0x805c, 0x56789abc);
    sim.debug_store32(0x8060, 0x6789abcd);
    sim.debug_store32(0x8064, 0x00009090);
    sim.debug_store32(0x8068, 0x789abcde);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 30);
    EXPECT_EQ(sim.get_pc(), 0x803c);
    EXPECT_EQ(sim.debug_load32(0x906c + 124), 0x12345678);
    EXPECT_EQ(sim.debug_load32(0x906c + 112), 0x23456789);
    EXPECT_EQ(sim.debug_load32(0x906c + 88),  0x3456789a);
    EXPECT_EQ(sim.debug_load32(0x906c + 64),  0x456789ab);
    EXPECT_EQ(sim.debug_load32(0x906c + 36),  0x56789abc);
    EXPECT_EQ(sim.debug_load32(0x906c + 0),   0x6789abcd);
    EXPECT_EQ(sim.debug_load32(0x906c + 76),  0x789abcde);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

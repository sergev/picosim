#include "util.h"

//
// Check STR instruction, with register plus immediate.
//
TEST(opcode, str_reg_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x490b);      // ldr r1, [pc, #44]
    sim.debug_store16(0x8002, 0x480c);      // ldr r0, [pc, #48]
    sim.debug_store16(0x8004, 0x67c8);      // str r0, [r1, #124]
    sim.debug_store16(0x8006, 0x4a0c);      // ldr r2, [pc, #48]
    sim.debug_store16(0x8008, 0x490c);      // ldr r1, [pc, #48]
    sim.debug_store16(0x800a, 0x6651);      // str r1, [r2, #100]
    sim.debug_store16(0x800c, 0x4b0c);      // ldr r3, [pc, #48]
    sim.debug_store16(0x800e, 0x4a0d);      // ldr r2, [pc, #52]
    sim.debug_store16(0x8010, 0x63da);      // str r2, [r3, #60]
    sim.debug_store16(0x8012, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x8014, 0x4b0d);      // ldr r3, [pc, #52]
    sim.debug_store16(0x8016, 0x63e3);      // str r3, [r4, #60]
    sim.debug_store16(0x8018, 0x4d05);      // ldr r5, [pc, #20]
    sim.debug_store16(0x801a, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x801c, 0x626c);      // str r4, [r5, #36]
    sim.debug_store16(0x801e, 0x4e04);      // ldr r6, [pc, #16]
    sim.debug_store16(0x8020, 0x4d0c);      // ldr r5, [pc, #48]
    sim.debug_store16(0x8022, 0x6035);      // str r5, [r6, #0]
    sim.debug_store16(0x8024, 0x4f0c);      // ldr r7, [pc, #48]
    sim.debug_store16(0x8026, 0x4e0d);      // ldr r6, [pc, #52]
    sim.debug_store16(0x8028, 0x62be);      // str r6, [r7, #40]
    sim.debug_store16(0x802a, 0x2701);      // movs r7, #1
    sim.debug_store16(0x802c, 0xdf00);      // svc 0
    sim.debug_store32(0x8030, 0x00009060);
    sim.debug_store32(0x8034, 0x12345678);
    sim.debug_store32(0x8038, 0x0000906c);
    sim.debug_store32(0x803c, 0x23456789);
    sim.debug_store32(0x8040, 0x0000907c);
    sim.debug_store32(0x8044, 0x3456789a);
    sim.debug_store32(0x8048, 0x00009064);
    sim.debug_store32(0x804c, 0x456789ab);
    sim.debug_store32(0x8050, 0x56789abc);
    sim.debug_store32(0x8054, 0x6789abcd);
    sim.debug_store32(0x8058, 0x00009084);
    sim.debug_store32(0x805c, 0x789abcde);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 23);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.debug_load32(0x9060 + 124), 0x12345678);
    EXPECT_EQ(sim.debug_load32(0x9060 + 112), 0x23456789);
    EXPECT_EQ(sim.debug_load32(0x9060 + 88),  0x3456789a);
    EXPECT_EQ(sim.debug_load32(0x9060 + 64),  0x456789ab);
    EXPECT_EQ(sim.debug_load32(0x9060 + 36),  0x56789abc);
    EXPECT_EQ(sim.debug_load32(0x9060 + 0),   0x6789abcd);
    EXPECT_EQ(sim.debug_load32(0x9060 + 76),  0x789abcde);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

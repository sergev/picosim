#include "util.h"

//
// Check STRB instruction, with register plus immediate.
//
TEST(opcode, strb_reg_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x490b);      // ldr r1, [pc, #44]
    sim.debug_store16(0x8002, 0x480c);      // ldr r0, [pc, #48]
    sim.debug_store16(0x8004, 0x77c8);      // strb r0, [r1, #31]
    sim.debug_store16(0x8006, 0x4a0c);      // ldr r2, [pc, #48]
    sim.debug_store16(0x8008, 0x490c);      // ldr r1, [pc, #48]
    sim.debug_store16(0x800a, 0x7651);      // strb r1, [r2, #25]
    sim.debug_store16(0x800c, 0x4b0c);      // ldr r3, [pc, #48]
    sim.debug_store16(0x800e, 0x4a0d);      // ldr r2, [pc, #52]
    sim.debug_store16(0x8010, 0x73da);      // strb r2, [r3, #15]
    sim.debug_store16(0x8012, 0x4c09);      // ldr r4, [pc, #36]
    sim.debug_store16(0x8014, 0x4b0c);      // ldr r3, [pc, #48]
    sim.debug_store16(0x8016, 0x73e3);      // strb r3, [r4, #15]
    sim.debug_store16(0x8018, 0x4d0c);      // ldr r5, [pc, #48]
    sim.debug_store16(0x801a, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x801c, 0x706c);      // strb r4, [r5, #1]
    sim.debug_store16(0x801e, 0x4e04);      // ldr r6, [pc, #16]
    sim.debug_store16(0x8020, 0x4d0c);      // ldr r5, [pc, #48]
    sim.debug_store16(0x8022, 0x7035);      // strb r5, [r6, #0]
    sim.debug_store16(0x8024, 0x4f0c);      // ldr r7, [pc, #48]
    sim.debug_store16(0x8026, 0x4e0d);      // ldr r6, [pc, #52]
    sim.debug_store16(0x8028, 0x72be);      // strb r6, [r7, #10]
    sim.debug_store16(0x802a, 0x2701);      // movs r7, #1
    sim.debug_store16(0x802c, 0xdf00);      // svc 0
    sim.debug_store32(0x8030, 0x00009060);
    sim.debug_store32(0x8034, 0x00000012);
    sim.debug_store32(0x8038, 0x00009064);
    sim.debug_store32(0x803c, 0x00000023);
    sim.debug_store32(0x8040, 0x0000906c);
    sim.debug_store32(0x8044, 0x00000034);
    sim.debug_store32(0x8048, 0x00000045);
    sim.debug_store32(0x804c, 0x00009068);
    sim.debug_store32(0x8050, 0x00000056);
    sim.debug_store32(0x8054, 0x00000067);
    sim.debug_store32(0x8058, 0x00009074);
    sim.debug_store32(0x805c, 0x00000078);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 23);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.debug_load8(0x9060 + 31), 0x12);
    EXPECT_EQ(sim.debug_load8(0x9060 + 29), 0x23);
    EXPECT_EQ(sim.debug_load8(0x9060 + 27), 0x34);
    EXPECT_EQ(sim.debug_load8(0x9060 + 19), 0x45);
    EXPECT_EQ(sim.debug_load8(0x9060 + 9),  0x56);
    EXPECT_EQ(sim.debug_load8(0x9060 + 0),  0x67);
    EXPECT_EQ(sim.debug_load8(0x9060 + 30), 0x78);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

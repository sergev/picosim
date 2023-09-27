#include "util.h"

//
// Check STRH instruction, with register plus immediate.
//
TEST(opcode, strh_reg_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x490b);      // ldr r1, [pc, #44]
    sim.debug_store16(0x8002, 0x480c);      // ldr r0, [pc, #48]
    sim.debug_store16(0x8004, 0x87c8);      // strh r0, [r1, #62]
    sim.debug_store16(0x8006, 0x4a0c);      // ldr r2, [pc, #48]
    sim.debug_store16(0x8008, 0x490c);      // ldr r1, [pc, #48]
    sim.debug_store16(0x800a, 0x8651);      // strh r1, [r2, #50]
    sim.debug_store16(0x800c, 0x4b0c);      // ldr r3, [pc, #48]
    sim.debug_store16(0x800e, 0x4a0d);      // ldr r2, [pc, #52]
    sim.debug_store16(0x8010, 0x83da);      // strh r2, [r3, #30]
    sim.debug_store16(0x8012, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x8014, 0x4b0d);      // ldr r3, [pc, #52]
    sim.debug_store16(0x8016, 0x83e3);      // strh r3, [r4, #30]
    sim.debug_store16(0x8018, 0x4d05);      // ldr r5, [pc, #20]
    sim.debug_store16(0x801a, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x801c, 0x826c);      // strh r4, [r5, #18]
    sim.debug_store16(0x801e, 0x4e04);      // ldr r6, [pc, #16]
    sim.debug_store16(0x8020, 0x4d0c);      // ldr r5, [pc, #48]
    sim.debug_store16(0x8022, 0x8035);      // strh r5, [r6, #0]
    sim.debug_store16(0x8024, 0x4f0c);      // ldr r7, [pc, #48]
    sim.debug_store16(0x8026, 0x4e0d);      // ldr r6, [pc, #52]
    sim.debug_store16(0x8028, 0x82be);      // strh r6, [r7, #20]
    sim.debug_store16(0x802a, 0x2701);      // movs r7, #1
    sim.debug_store16(0x802c, 0xdf00);      // svc 0
    sim.debug_store32(0x8030, 0x00009060);
    sim.debug_store32(0x8034, 0x00001234);
    sim.debug_store32(0x8038, 0x00009068);
    sim.debug_store32(0x803c, 0x00002345);
    sim.debug_store32(0x8040, 0x00009070);
    sim.debug_store32(0x8044, 0x00003456);
    sim.debug_store32(0x8048, 0x00009064);
    sim.debug_store32(0x804c, 0x00004567);
    sim.debug_store32(0x8050, 0x00005678);
    sim.debug_store32(0x8054, 0x00006789);
    sim.debug_store32(0x8058, 0x00009084);
    sim.debug_store32(0x805c, 0x0000789a);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 23);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.debug_load16(0x9060 + 62), 0x1234);
    EXPECT_EQ(sim.debug_load16(0x9060 + 58), 0x2345);
    EXPECT_EQ(sim.debug_load16(0x9060 + 46), 0x3456);
    EXPECT_EQ(sim.debug_load16(0x9060 + 34), 0x4567);
    EXPECT_EQ(sim.debug_load16(0x9060 + 18), 0x5678);
    EXPECT_EQ(sim.debug_load16(0x9060 + 0),  0x6789);
    EXPECT_EQ(sim.debug_load16(0x9060 + 56), 0x789a);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

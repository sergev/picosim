#include "util.h"

//
// Check STRH instruction, with register plus register.
//
TEST(opcode, strh_reg_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x490e);      // ldr r1, [pc, #56]
    sim.debug_store16(0x8002, 0x223e);      // movs r2, #62
    sim.debug_store16(0x8004, 0x480e);      // ldr r0, [pc, #56]
    sim.debug_store16(0x8006, 0x5288);      // strh r0, [r1, r2]
    sim.debug_store16(0x8008, 0x4a0e);      // ldr r2, [pc, #56]
    sim.debug_store16(0x800a, 0x2332);      // movs r3, #50
    sim.debug_store16(0x800c, 0x490e);      // ldr r1, [pc, #56]
    sim.debug_store16(0x800e, 0x52d1);      // strh r1, [r2, r3]
    sim.debug_store16(0x8010, 0x4b0e);      // ldr r3, [pc, #56]
    sim.debug_store16(0x8012, 0x241e);      // movs r4, #30
    sim.debug_store16(0x8014, 0x4a0e);      // ldr r2, [pc, #56]
    sim.debug_store16(0x8016, 0x531a);      // strh r2, [r3, r4]
    sim.debug_store16(0x8018, 0x4c0e);      // ldr r4, [pc, #56]
    sim.debug_store16(0x801a, 0x251e);      // movs r5, #30
    sim.debug_store16(0x801c, 0x4b0e);      // ldr r3, [pc, #56]
    sim.debug_store16(0x801e, 0x5363);      // strh r3, [r4, r5]
    sim.debug_store16(0x8020, 0x4d06);      // ldr r5, [pc, #24]
    sim.debug_store16(0x8022, 0x2612);      // movs r6, #18
    sim.debug_store16(0x8024, 0x4c0d);      // ldr r4, [pc, #52]
    sim.debug_store16(0x8026, 0x53ac);      // strh r4, [r5, r6]
    sim.debug_store16(0x8028, 0x4e04);      // ldr r6, [pc, #16]
    sim.debug_store16(0x802a, 0x2700);      // movs r7, #0
    sim.debug_store16(0x802c, 0x4d0c);      // ldr r5, [pc, #48]
    sim.debug_store16(0x802e, 0x53f5);      // strh r5, [r6, r7]
    sim.debug_store16(0x8030, 0x4f0c);      // ldr r7, [pc, #48]
    sim.debug_store16(0x8032, 0x2014);      // movs r0, #20
    sim.debug_store16(0x8034, 0x4e0c);      // ldr r6, [pc, #48]
    sim.debug_store16(0x8036, 0x523e);      // strh r6, [r7, r0]
    sim.debug_store16(0x8038, 0x2701);      // movs r7, #1
    sim.debug_store16(0x803a, 0xdf00);      // svc 0
    sim.debug_store32(0x803c, 0x0000906c);
    sim.debug_store32(0x8040, 0x00001234);
    sim.debug_store32(0x8044, 0x00009074);
    sim.debug_store32(0x8048, 0x00002345);
    sim.debug_store32(0x804c, 0x0000907c);
    sim.debug_store32(0x8050, 0x00003456);
    sim.debug_store32(0x8054, 0x00009070);
    sim.debug_store32(0x8058, 0x00004567);
    sim.debug_store32(0x805c, 0x00005678);
    sim.debug_store32(0x8060, 0x00006789);
    sim.debug_store32(0x8064, 0x00009090);
    sim.debug_store32(0x8068, 0x0000789a);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 30);
    EXPECT_EQ(sim.get_pc(), 0x803c);
    EXPECT_EQ(sim.debug_load16(0x906c + 62), 0x1234);
    EXPECT_EQ(sim.debug_load16(0x906c + 58), 0x2345);
    EXPECT_EQ(sim.debug_load16(0x906c + 46), 0x3456);
    EXPECT_EQ(sim.debug_load16(0x906c + 34), 0x4567);
    EXPECT_EQ(sim.debug_load16(0x906c + 18), 0x5678);
    EXPECT_EQ(sim.debug_load16(0x906c + 0),  0x6789);
    EXPECT_EQ(sim.debug_load16(0x906c + 56), 0x789a);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

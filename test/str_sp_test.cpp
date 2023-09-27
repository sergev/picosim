#include "util.h"

//
// Check STR instruction, SP-relative.
//
TEST(opcode, str_sp)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4808);      // ldr r0, [pc, #32]
    sim.debug_store16(0x8002, 0x4685);      // mov sp, r0
    sim.debug_store16(0x8004, 0x4808);      // ldr r0, [pc, #32]
    sim.debug_store16(0x8006, 0x901f);      // str r0, [sp, #124]
    sim.debug_store16(0x8008, 0x4908);      // ldr r1, [pc, #32]
    sim.debug_store16(0x800a, 0x911c);      // str r1, [sp, #112]
    sim.debug_store16(0x800c, 0x4a08);      // ldr r2, [pc, #32]
    sim.debug_store16(0x800e, 0x9216);      // str r2, [sp, #88]
    sim.debug_store16(0x8010, 0x4b08);      // ldr r3, [pc, #32]
    sim.debug_store16(0x8012, 0x9310);      // str r3, [sp, #64]
    sim.debug_store16(0x8014, 0x4c08);      // ldr r4, [pc, #32]
    sim.debug_store16(0x8016, 0x9409);      // str r4, [sp, #36]
    sim.debug_store16(0x8018, 0x4d08);      // ldr r5, [pc, #32]
    sim.debug_store16(0x801a, 0x9500);      // str r5, [sp, #0]
    sim.debug_store16(0x801c, 0x4e08);      // ldr r6, [pc, #32]
    sim.debug_store16(0x801e, 0x9613);      // str r6, [sp, #76]
    sim.debug_store16(0x8020, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8022, 0xdf00);      // svc 0
    sim.debug_store32(0x8024, 0x00009044);
    sim.debug_store32(0x8028, 0x12345678);
    sim.debug_store32(0x802c, 0x23456789);
    sim.debug_store32(0x8030, 0x3456789a);
    sim.debug_store32(0x8034, 0x456789ab);
    sim.debug_store32(0x8038, 0x56789abc);
    sim.debug_store32(0x803c, 0x6789abcd);
    sim.debug_store32(0x8040, 0x789abcde);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 18);
    EXPECT_EQ(sim.get_pc(), 0x8024);
    EXPECT_EQ(sim.debug_load32(0x9044 + 124), 0x12345678);
    EXPECT_EQ(sim.debug_load32(0x9044 + 112), 0x23456789);
    EXPECT_EQ(sim.debug_load32(0x9044 + 88),  0x3456789a);
    EXPECT_EQ(sim.debug_load32(0x9044 + 64),  0x456789ab);
    EXPECT_EQ(sim.debug_load32(0x9044 + 36),  0x56789abc);
    EXPECT_EQ(sim.debug_load32(0x9044 + 0),   0x6789abcd);
    EXPECT_EQ(sim.debug_load32(0x9044 + 76),  0x789abcde);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

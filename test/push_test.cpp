#include "util.h"

//
// Check PUSH instruction.
//
TEST(opcode, push)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4807);      // ldr r0, [pc, #28]
    sim.debug_store16(0x8002, 0x4686);      // mov lr, r0
    sim.debug_store16(0x8004, 0x4807);      // ldr r0, [pc, #28]
    sim.debug_store16(0x8006, 0x4685);      // mov sp, r0
    sim.debug_store16(0x8008, 0x4807);      // ldr r0, [pc, #28]
    sim.debug_store16(0x800a, 0x4908);      // ldr r1, [pc, #32]
    sim.debug_store16(0x800c, 0x4a08);      // ldr r2, [pc, #32]
    sim.debug_store16(0x800e, 0x4b09);      // ldr r3, [pc, #36]
    sim.debug_store16(0x8010, 0x4c09);      // ldr r4, [pc, #36]
    sim.debug_store16(0x8012, 0x4d0a);      // ldr r5, [pc, #40]
    sim.debug_store16(0x8014, 0x4e0a);      // ldr r6, [pc, #40]
    sim.debug_store16(0x8016, 0x4f0b);      // ldr r7, [pc, #44]
    sim.debug_store16(0x8018, 0xb403);      // push {r0, r1}
    sim.debug_store16(0x801a, 0xb5dc);      // push {r2, r3, r4, r6, r7, lr}
    sim.debug_store16(0x801c, 0x2701);      // movs r7, #1
    sim.debug_store16(0x801e, 0xdf00);      // svc 0
    sim.debug_store32(0x8020, 0x9abcdef1);
    sim.debug_store32(0x8024, 0x00009068);
    sim.debug_store32(0x8028, 0x12345678);
    sim.debug_store32(0x802c, 0x23456789);
    sim.debug_store32(0x8030, 0x3456789a);
    sim.debug_store32(0x8034, 0x456789ab);
    sim.debug_store32(0x8038, 0x56789abc);
    sim.debug_store32(0x803c, 0x6789abcd);
    sim.debug_store32(0x8040, 0x789abcde);
    sim.debug_store32(0x8044, 0x89abcdef);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 16);
    EXPECT_EQ(sim.get_pc(), 0x8020);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_reg(13), 0x9068 - 32);              // new SP
    EXPECT_EQ(sim.debug_load32(0x9068 - 32), 0x3456789a); // r2
    EXPECT_EQ(sim.debug_load32(0x9068 - 28), 0x456789ab); // r3
    EXPECT_EQ(sim.debug_load32(0x9068 - 24), 0x56789abc); // r4
    EXPECT_EQ(sim.debug_load32(0x9068 - 20), 0x789abcde); // r6
    EXPECT_EQ(sim.debug_load32(0x9068 - 16), 0x89abcdef); // r7
    EXPECT_EQ(sim.debug_load32(0x9068 - 12), 0x9abcdef1); // LR
    EXPECT_EQ(sim.debug_load32(0x9068 - 8),  0x12345678); // r0
    EXPECT_EQ(sim.debug_load32(0x9068 - 4),  0x23456789); // r1
}

#include "sc_main.cpp"

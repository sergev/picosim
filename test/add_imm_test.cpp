#include "util.h"

//
// Check ADD instruction with 8-bit immediate.
//
TEST(opcode, add_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4809);      // ldr r0, [pc, #36]
    sim.debug_store16(0x8002, 0x3042);      // add r0, #66
    sim.debug_store16(0x8004, 0xf3ef);      // mrs r1, CPSR
    sim.debug_store16(0x8006, 0x8100);
    sim.debug_store16(0x8008, 0x4a08);      // ldr r2, [pc, #32]
    sim.debug_store16(0x800a, 0x325b);      // add r2, #91
    sim.debug_store16(0x800c, 0xf3ef);      // mrs r3, CPSR
    sim.debug_store16(0x800e, 0x8300);
    sim.debug_store16(0x8010, 0x4c07);      // ldr r4, [pc, #28]
    sim.debug_store16(0x8012, 0x348c);      // add r4, #140
    sim.debug_store16(0x8014, 0xf3ef);      // mrs r5, CPSR
    sim.debug_store16(0x8016, 0x8500);
    sim.debug_store16(0x8018, 0x4e06);      // ldr r6, [pc, #24]
    sim.debug_store16(0x801a, 0x36a5);      // add r6, #165
    sim.debug_store16(0x801c, 0xf3ef);      // mrs r7, CPSR
    sim.debug_store16(0x801e, 0x8700);
    sim.debug_store16(0x8020, 0x46b8);      // mov r8, r7
    sim.debug_store16(0x8022, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8024, 0xdf00);      // svc 0
    sim.debug_store32(0x8028, 0x7fffffff);
    sim.debug_store32(0x802c, 0xffffffff);
    sim.debug_store32(0x8030, 0x00000001);
    sim.debug_store32(0x8034, 0x00000000);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 15);
    EXPECT_EQ(sim.get_pc(), 0x8026);
    EXPECT_EQ(sim.get_reg(0), 0x80000041);
    EXPECT_EQ(sim.get_reg(1), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0x0000005a);
    EXPECT_EQ(sim.get_reg(3), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(4), 0x0000008d);
    EXPECT_EQ(sim.get_reg(5), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(6), 0x000000a5);
    EXPECT_EQ(sim.get_reg(8), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

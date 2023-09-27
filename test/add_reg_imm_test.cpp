#include "util.h"

//
// Check ADD instruction with register + immediate.
//
TEST(opcode, add_reg_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4b09);      // ldr r3, [pc, #36]
    sim.debug_store16(0x8002, 0x1d18);      // adds r0, r3, #4
    sim.debug_store16(0x8004, 0xf3ef);      // mrs r1, CPSR
    sim.debug_store16(0x8006, 0x8100);
    sim.debug_store16(0x8008, 0x4d08);      // ldr r5, [pc, #32]
    sim.debug_store16(0x800a, 0x1cea);      // adds r2, r5, #3
    sim.debug_store16(0x800c, 0xf3ef);      // mrs r3, CPSR
    sim.debug_store16(0x800e, 0x8300);
    sim.debug_store16(0x8010, 0x4e07);      // ldr r6, [pc, #28]
    sim.debug_store16(0x8012, 0x1db4);      // adds r4, r6, #6
    sim.debug_store16(0x8014, 0xf3ef);      // mrs r5, CPSR
    sim.debug_store16(0x8016, 0x8500);
    sim.debug_store16(0x8018, 0x4f06);      // ldr r7, [pc, #24]
    sim.debug_store16(0x801a, 0x1dfe);      // adds r6, r7, #7
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
    EXPECT_EQ(sim.get_reg(0), 0x80000003);
    EXPECT_EQ(sim.get_reg(1), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0x00000002);
    EXPECT_EQ(sim.get_reg(3), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(4), 0x00000007);
    EXPECT_EQ(sim.get_reg(5), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(6), 0x00000007);
    EXPECT_EQ(sim.get_reg(8), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

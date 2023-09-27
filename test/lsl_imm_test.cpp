#include "util.h"

//
// Check LSL instruction with immediate.
//
TEST(opcode, lsl_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4b09);      // ldr r3, [pc, #36]
    sim.debug_store16(0x8002, 0x0018);      // movs r0, r3
    sim.debug_store16(0x8004, 0xf3ef);      // mrs r1, CPSR
    sim.debug_store16(0x8006, 0x8100);
    sim.debug_store16(0x8008, 0x4c08);      // ldr r4, [pc, #32]
    sim.debug_store16(0x800a, 0x07e2);      // lsls r2, r4, #31
    sim.debug_store16(0x800c, 0xf3ef);      // mrs r3, CPSR
    sim.debug_store16(0x800e, 0x8300);
    sim.debug_store16(0x8010, 0x4d07);      // ldr r5, [pc, #28]
    sim.debug_store16(0x8012, 0x052c);      // lsls r4, r5, #20
    sim.debug_store16(0x8014, 0xf3ef);      // mrs r5, CPSR
    sim.debug_store16(0x8016, 0x8500);
    sim.debug_store16(0x8018, 0x4f06);      // ldr r7, [pc, #24]
    sim.debug_store16(0x801a, 0x01fe);      // lsls r6, r7, #7
    sim.debug_store16(0x801c, 0xf3ef);      // mrs r7, CPSR
    sim.debug_store16(0x801e, 0x8700);
    sim.debug_store16(0x8020, 0x46b8);      // mov r8, r7
    sim.debug_store16(0x8022, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8024, 0xdf00);      // svc 0
    sim.debug_store32(0x8028, 0xc015a134);
    sim.debug_store32(0x802c, 0xd306fde3);
    sim.debug_store32(0x8030, 0x776dd37e);
    sim.debug_store32(0x8034, 0x549c13ba);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 15);
    EXPECT_EQ(sim.get_pc(), 0x8026);
    EXPECT_EQ(sim.get_reg(0), 0xc015a134);
    EXPECT_EQ(sim.get_reg(1), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(2), 0x80000000);
    EXPECT_EQ(sim.get_reg(3), 0xa0000000); // Negative+Carry flags
    EXPECT_EQ(sim.get_reg(4), 0x37e00000);
    EXPECT_EQ(sim.get_reg(5), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(6), 0x4e09dd00);
    EXPECT_EQ(sim.get_reg(8), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

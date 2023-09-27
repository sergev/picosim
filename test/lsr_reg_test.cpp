#include "util.h"

//
// Check LSR instruction with register.
//
TEST(opcode, lsr_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x480b);      // ldr r0, [pc, #44]
    sim.debug_store16(0x8002, 0x2300);      // movs r3, #0
    sim.debug_store16(0x8004, 0x40d8);      // lsrs r0, r3
    sim.debug_store16(0x8006, 0xf3ef);      // mrs r1, CPSR
    sim.debug_store16(0x8008, 0x8100);
    sim.debug_store16(0x800a, 0x4a0a);      // ldr r2, [pc, #40]
    sim.debug_store16(0x800c, 0x2420);      // movs r4, #32
    sim.debug_store16(0x800e, 0x40e2);      // lsrs r2, r4
    sim.debug_store16(0x8010, 0xf3ef);      // mrs r3, CPSR
    sim.debug_store16(0x8012, 0x8300);
    sim.debug_store16(0x8014, 0x4c08);      // ldr r4, [pc, #32]
    sim.debug_store16(0x8016, 0x2514);      // movs r5, #20
    sim.debug_store16(0x8018, 0x40ec);      // lsrs r4, r5
    sim.debug_store16(0x801a, 0xf3ef);      // mrs r5, CPSR
    sim.debug_store16(0x801c, 0x8500);
    sim.debug_store16(0x801e, 0x4e07);      // ldr r6, [pc, #28]
    sim.debug_store16(0x8020, 0x2707);      // movs r7, #7
    sim.debug_store16(0x8022, 0x40fe);      // lsrs r6, r7
    sim.debug_store16(0x8024, 0xf3ef);      // mrs r7, CPSR
    sim.debug_store16(0x8026, 0x8700);
    sim.debug_store16(0x8028, 0x46b8);      // mov r8, r7
    sim.debug_store16(0x802a, 0x2701);      // movs r7, #1
    sim.debug_store16(0x802c, 0xdf00);      // svc 0
    sim.debug_store32(0x8030, 0xc015a134);
    sim.debug_store32(0x8034, 0xd306fde3);
    sim.debug_store32(0x8038, 0x776dd37e);
    sim.debug_store32(0x803c, 0x549c13ba);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 19);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.get_reg(0), 0xc015a134);
    EXPECT_EQ(sim.get_reg(1), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(2), 0x00000000);
    EXPECT_EQ(sim.get_reg(3), 0x60000000); // Zero+Carry flags
    EXPECT_EQ(sim.get_reg(4), 0x00000776);
    EXPECT_EQ(sim.get_reg(5), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(6), 0x00a93827);
    EXPECT_EQ(sim.get_reg(8), 0x00000000); // No flags
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

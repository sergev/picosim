#include "util.h"

//
// Check CMP instruction with registers.
//
TEST(opcode, cmp_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x480b);      // ldr r0, [pc, #44]
    sim.debug_store16(0x8002, 0x4b0c);      // ldr r3, [pc, #48]
    sim.debug_store16(0x8004, 0x4298);      // cmp r0, r3
    sim.debug_store16(0x8006, 0xf3ef);      // mrs r1, CPSR
    sim.debug_store16(0x8008, 0x8100);
    sim.debug_store16(0x800a, 0x4a0b);      // ldr r2, [pc, #44]
    sim.debug_store16(0x800c, 0x4c0b);      // ldr r4, [pc, #44]
    sim.debug_store16(0x800e, 0x42a2);      // cmp r2, r4
    sim.debug_store16(0x8010, 0xf3ef);      // mrs r3, CPSR
    sim.debug_store16(0x8012, 0x8300);
    sim.debug_store16(0x8014, 0x4c0a);      // ldr r4, [pc, #40]
    sim.debug_store16(0x8016, 0x4d0b);      // ldr r5, [pc, #44]
    sim.debug_store16(0x8018, 0x42ac);      // cmp r4, r5
    sim.debug_store16(0x801a, 0xf3ef);      // mrs r5, CPSR
    sim.debug_store16(0x801c, 0x8500);
    sim.debug_store16(0x801e, 0x4e0a);      // ldr r6, [pc, #40]
    sim.debug_store16(0x8020, 0x4f0a);      // ldr r7, [pc, #40]
    sim.debug_store16(0x8022, 0x42be);      // cmp r6, r7
    sim.debug_store16(0x8024, 0xf3ef);      // mrs r7, CPSR
    sim.debug_store16(0x8026, 0x8700);
    sim.debug_store16(0x8028, 0x46b8);      // mov r8, r7
    sim.debug_store16(0x802a, 0x2701);      // movs r7, #1
    sim.debug_store16(0x802c, 0xdf00);      // svc 0
    sim.debug_store32(0x8030, 0x7502fe1f);
    sim.debug_store32(0x8034, 0xc015a134);
    sim.debug_store32(0x8038, 0x8c832ed2);
    sim.debug_store32(0x803c, 0xd306fde3);
    sim.debug_store32(0x8040, 0x9b74a3db);
    sim.debug_store32(0x8044, 0x776dd37e);
    sim.debug_store32(0x8048, 0xce671cdd);
    sim.debug_store32(0x804c, 0x549c13ba);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 19);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.get_reg(0), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(1), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(4), 0x9b74a3db);
    EXPECT_EQ(sim.get_reg(5), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(6), 0xce671cdd);
    EXPECT_EQ(sim.get_reg(8), 0x30000000); // Carry+Overflow flags
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

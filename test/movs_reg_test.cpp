#include "util.h"

//
// Check MOVS instruction with registers.
//
TEST(opcode, movs_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4d04);      // ldr r5, [pc, #16]
    sim.debug_store16(0x8002, 0x1c29);      // movs r1, r5
    sim.debug_store16(0x8004, 0x4f04);      // ldr r7, [pc, #16]
    sim.debug_store16(0x8006, 0x1c3b);      // movs r3, r7
    sim.debug_store16(0x8008, 0x4804);      // ldr r0, [pc, #16]
    sim.debug_store16(0x800a, 0x1c02);      // movs r2, r0
    sim.debug_store16(0x800c, 0x4e04);      // ldr r6, [pc, #16]
    sim.debug_store16(0x800e, 0x1c34);      // movs r4, r6
    sim.debug_store16(0x8010, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8012, 0xdf00);      // svc 0
    sim.debug_store32(0x8014, 0x7502fe1f);
    sim.debug_store32(0x8018, 0xc015a134);
    sim.debug_store32(0x801c, 0x8c832ed2);
    sim.debug_store32(0x8020, 0xd306fde3);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 10);
    EXPECT_EQ(sim.get_reg(0), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(1), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0xc015a134);
    EXPECT_EQ(sim.get_reg(4), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(5), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(6), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_pc(), 0x8014);
}

#include "sc_main.cpp"

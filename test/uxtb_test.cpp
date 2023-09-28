#include "util.h"

//
// Check UXTB instruction.
//
TEST(opcode, uxtb)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4b04);      // ldr r3, [pc, #16]
    sim.debug_store16(0x8002, 0xb2d8);      // uxtb r0, r3
    sim.debug_store16(0x8004, 0x4c04);      // ldr r4, [pc, #16]
    sim.debug_store16(0x8006, 0xb2e2);      // uxtb r2, r4
    sim.debug_store16(0x8008, 0x4d04);      // ldr r5, [pc, #16]
    sim.debug_store16(0x800a, 0xb2ec);      // uxtb r4, r5
    sim.debug_store16(0x800c, 0x4f04);      // ldr r7, [pc, #16]
    sim.debug_store16(0x800e, 0xb2fe);      // uxtb r6, r7
    sim.debug_store16(0x8010, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8012, 0xdf00);      // svc 0
    sim.debug_store32(0x8014, 0xc015a134);
    sim.debug_store32(0x8018, 0xd306fde3);
    sim.debug_store32(0x801c, 0x776dd37e);
    sim.debug_store32(0x8020, 0x549c13ba);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 10);
    EXPECT_EQ(sim.get_pc(), 0x8014);
    EXPECT_EQ(sim.get_reg(0), 0x00000034);
    EXPECT_EQ(sim.get_reg(2), 0x000000e3);
    EXPECT_EQ(sim.get_reg(4), 0x0000007e);
    EXPECT_EQ(sim.get_reg(6), 0x000000ba);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

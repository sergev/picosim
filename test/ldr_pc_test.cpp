#include "util.h"

//
// Check LDR instruction, PC-relative.
//
TEST(opcode, ldr_pc)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4804);      // ldr r0, [pc, #16]
    sim.debug_store16(0x8002, 0x4905);      // ldr r1, [pc, #20]
    sim.debug_store16(0x8004, 0x4a05);      // ldr r2, [pc, #20]
    sim.debug_store16(0x8006, 0x4b06);      // ldr r3, [pc, #24]
    sim.debug_store16(0x8008, 0x4c06);      // ldr r4, [pc, #24]
    sim.debug_store16(0x800a, 0x4d07);      // ldr r5, [pc, #28]
    sim.debug_store16(0x800c, 0x4e07);      // ldr r6, [pc, #28]
    sim.debug_store16(0x800e, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8010, 0xdf00);      // svc 0
    sim.debug_store32(0x8014, 0x7502fe1f);
    sim.debug_store32(0x8018, 0xc015a134);
    sim.debug_store32(0x801c, 0x8c832ed2);
    sim.debug_store32(0x8020, 0xd306fde3);
    sim.debug_store32(0x8024, 0xd965247d);
    sim.debug_store32(0x8028, 0xcf097d2e);
    sim.debug_store32(0x802c, 0x36204518);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_reg(0), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(1), 0xc015a134);
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(4), 0xd965247d);
    EXPECT_EQ(sim.get_reg(5), 0xcf097d2e);
    EXPECT_EQ(sim.get_reg(6), 0x36204518);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_pc(), 0x8012);
}

#include "sc_main.cpp"

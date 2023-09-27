#include "util.h"

//
// Check LDMIA instruction.
//
TEST(opcode, ldmia)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa002);      // add r0, pc, #8 @ (adr r0, 800c <data0>)
    sim.debug_store16(0x8002, 0xc80a);      // ldmia r0!, {r1, r3}
    sim.debug_store16(0x8004, 0xa403);      // add r4, pc, #12 @ (adr r4, 8014 <data4>)
    sim.debug_store16(0x8006, 0xcc74);      // ldmia r4, {r2, r4, r5, r6}
    sim.debug_store16(0x8008, 0x2701);      // movs r7, #1
    sim.debug_store16(0x800a, 0xdf00);      // svc 0
    sim.debug_store32(0x800c, 0x7502fe1f);
    sim.debug_store32(0x8010, 0xc015a134);
    sim.debug_store32(0x8014, 0x8c832ed2);
    sim.debug_store32(0x8018, 0xd306fde3);
    sim.debug_store32(0x801c, 0xd965247d);
    sim.debug_store32(0x8020, 0xcf097d2e);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 6);
    EXPECT_EQ(sim.get_pc(), 0x800c);
    EXPECT_EQ(sim.get_reg(0), 0x8014);
    EXPECT_EQ(sim.get_reg(1), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0xc015a134);
    EXPECT_EQ(sim.get_reg(4), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(5), 0xd965247d);
    EXPECT_EQ(sim.get_reg(6), 0xcf097d2e);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

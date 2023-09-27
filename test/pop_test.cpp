#include "util.h"

//
// Check POP instruction.
//
TEST(opcode, pop)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa003);      // add r0, pc, #12
    sim.debug_store16(0x8002, 0x4685);      // mov sp, r0
    sim.debug_store16(0x8004, 0xbd0a);      // pop {r1, r3, pc}
    sim.debug_store16(0x8006, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8008, 0xdf00);      // svc 0
    sim.debug_store16(0x800a, 0xbc75);      // pop {r0, r2, r4, r5, r6}
    sim.debug_store16(0x800c, 0x2701);      // movs r7, #1
    sim.debug_store16(0x800e, 0xdf00);      // svc 0
    sim.debug_store32(0x8010, 0x7502fe1f);
    sim.debug_store32(0x8014, 0xc015a134);
    sim.debug_store32(0x8018, 0x0000800a);
    sim.debug_store32(0x801c, 0x36204518);
    sim.debug_store32(0x8020, 0x8c832ed2);
    sim.debug_store32(0x8024, 0xd306fde3);
    sim.debug_store32(0x8028, 0xd965247d);
    sim.debug_store32(0x802c, 0xcf097d2e);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 6);
    EXPECT_EQ(sim.get_pc(), 0x8010);
    EXPECT_EQ(sim.get_reg(0), 0x36204518);
    EXPECT_EQ(sim.get_reg(1), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(2), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(3), 0xc015a134);
    EXPECT_EQ(sim.get_reg(4), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(5), 0xd965247d);
    EXPECT_EQ(sim.get_reg(6), 0xcf097d2e);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_reg(13), 0x8010 + 32); // new SP
}

#include "sc_main.cpp"

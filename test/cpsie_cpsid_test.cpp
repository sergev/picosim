#include "util.h"

//
// Check CPSIE/CPSID instructions.
//
TEST(opcode, cpsie_cpsid)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xb662);      // cpsie i
    sim.debug_store32(0x8002, 0x8010f3ef);  // mrs r0, PRIMASK - expect 0000_0000
    sim.debug_store16(0x8006, 0xb672);      // cpsid i
    sim.debug_store32(0x8008, 0x8110f3ef);  // mrs r1, PRIMASK - expect 0000_0001
    sim.debug_store16(0x800c, 0xb662);      // cpsie i
    sim.debug_store32(0x800e, 0x8210f3ef);  // mrs r2, PRIMASK - expect 0000_0000
    sim.debug_store16(0x8012, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8014, 0xdf00);      // svc 0

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 8);
    EXPECT_EQ(sim.get_pc(), 0x8016);
    EXPECT_EQ(sim.get_reg(0), 0);           // after cpsie
    EXPECT_EQ(sim.get_reg(1), 1);           // after cpsid
    EXPECT_EQ(sim.get_reg(2), 0);           // after cpsie
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

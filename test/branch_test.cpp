#include "util.h"

//
// Check B instruction.
//
TEST(opcode, branch)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8002, 0xe002);      // b.n 800a <_start+0xa>
    sim.debug_store16(0x8004, 0xdf00);      // svc 0
    sim.debug_store16(0x8006, 0xe002);      // b.n 800e <_start+0xe>
    sim.debug_store16(0x8008, 0xdf00);      // svc 0
    sim.debug_store16(0x800a, 0xe7fc);      // b.n 8006 <_start+0x6>
    sim.debug_store16(0x800c, 0xdf00);      // svc 0
    sim.debug_store16(0x800e, 0xdf00);      // svc 0

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 5);
    EXPECT_EQ(sim.get_pc(), 0x8010);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

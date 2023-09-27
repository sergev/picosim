#include "util.h"

//
// Check NOP instruction.
//
TEST(opcode, nop)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x46c0);      // nop
    sim.debug_store16(0x8002, 0x46c0);      // nop
    sim.debug_store16(0x8004, 0x46c0);      // nop
    sim.debug_store16(0x8006, 0x46c0);      // nop
    sim.debug_store16(0x8008, 0x2701);      // movs r7, #1
    sim.debug_store16(0x800a, 0xdf00);      // svc 0

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 6);
    EXPECT_EQ(sim.get_pc(), 0x800c);
}

#include "sc_main.cpp"

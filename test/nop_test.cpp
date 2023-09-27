#include "util.h"

//
// Check NOP instruction.
// Also check DSB, DMB and ISB opcodes.
//
TEST(opcode, nop)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x46c0);      // nop
    sim.debug_store16(0x8002, 0xf3bf);      // dsb sy
    sim.debug_store16(0x8004, 0x8f4f);
    sim.debug_store16(0x8006, 0xf3bf);      // dmb sy
    sim.debug_store16(0x8008, 0x8f5f);
    sim.debug_store16(0x800a, 0xf3bf);      // isb sy
    sim.debug_store16(0x800c, 0x8f6f);
    sim.debug_store16(0x800e, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8010, 0xdf00);      // svc 0

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 6);
    EXPECT_EQ(sim.get_pc(), 0x8012);
}

#include "sc_main.cpp"

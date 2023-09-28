#include "util.h"

//
// Check BL instruction.
//
TEST(opcode, branch_link)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8002, 0xf000);      // bl 8010 <_start+0x10>
    sim.debug_store16(0x8004, 0xf805);
    sim.debug_store16(0x8006, 0xdf00);      // svc 0
    sim.debug_store16(0x8008, 0x4672);      // mov r2, lr
    sim.debug_store16(0x800a, 0xf000);      // bl 8018 <_start+0x18>
    sim.debug_store16(0x800c, 0xf805);
    sim.debug_store16(0x800e, 0xdf00);      // svc 0
    sim.debug_store16(0x8010, 0x4671);      // mov r1, lr
    sim.debug_store16(0x8012, 0xf7ff);      // bl 8008 <_start+0x8>
    sim.debug_store16(0x8014, 0xfff9);
    sim.debug_store16(0x8016, 0xdf00);      // svc 0
    sim.debug_store16(0x8018, 0x4673);      // mov r3, lr
    sim.debug_store16(0x801a, 0xdf00);      // svc 0

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 8);
    EXPECT_EQ(sim.get_pc(), 0x801c);
    EXPECT_EQ(sim.get_reg(1), 0x8006);
    EXPECT_EQ(sim.get_reg(2), 0x8016);
    EXPECT_EQ(sim.get_reg(3), 0x800e);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

#include "util.h"

//
// Check BX instruction.
//
TEST(opcode, branch_exc)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8002, 0x4905);      // ldr r1, [pc, #20]
    sim.debug_store16(0x8004, 0x4708);      // bx r1
    sim.debug_store16(0x8006, 0xdf00);      // svc 0
    sim.debug_store16(0x8008, 0x4b04);      // ldr r3, [pc, #16]
    sim.debug_store16(0x800a, 0x4718);      // bx r3
    sim.debug_store16(0x800c, 0xdf00);      // svc 0
    sim.debug_store16(0x800e, 0x4a04);      // ldr r2, [pc, #16]
    sim.debug_store16(0x8010, 0x4710);      // bx r2
    sim.debug_store16(0x8012, 0xdf00);      // svc 0
    sim.debug_store16(0x8014, 0xdf00);      // svc 0
    sim.debug_store16(0x8018, 0x0000800e);
    sim.debug_store16(0x801c, 0x00008014);
    sim.debug_store16(0x8020, 0x00008008);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 8);
    EXPECT_EQ(sim.get_pc(), 0x8016);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

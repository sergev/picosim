#include "util.h"

//
// Check BLX instruction.
//
TEST(opcode, branch_link_exch)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x2701);      //       movs r7, #1
    sim.debug_store16(0x8002, 0x4907);      //       ldr r1, [pc, #28]
    sim.debug_store16(0x8004, 0x4788);      //       blx r1
    sim.debug_store16(0x8006, 0xdf00);      //       svc 0
    sim.debug_store16(0x8008, 0x4672);      //       mov r2, lr
    sim.debug_store16(0x800a, 0x4b06);      //       ldr r3, [pc, #24]
    sim.debug_store16(0x800c, 0x469e);      //       mov lr, r3
    sim.debug_store16(0x800e, 0x47f0);      //       blx lr
    sim.debug_store16(0x8010, 0xdf00);      //       svc 0
    sim.debug_store16(0x8012, 0x4671);      //       mov r1, lr
    sim.debug_store16(0x8014, 0x4a04);      //       ldr r2, [pc, #16]
    sim.debug_store16(0x8016, 0x4790);      //       blx r2
    sim.debug_store16(0x8018, 0xdf00);      //       svc 0
    sim.debug_store16(0x801a, 0x4673);      //       mov r3, lr
    sim.debug_store16(0x801c, 0xdf00);      //       svc 0
    sim.debug_store32(0x8020, 0x00008012);
    sim.debug_store32(0x8024, 0x0000801a);
    sim.debug_store32(0x8028, 0x00008008);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 12);
    EXPECT_EQ(sim.get_pc(), 0x801e);
    EXPECT_EQ(sim.get_reg(1), 0x8006);
    EXPECT_EQ(sim.get_reg(2), 0x8018);
    EXPECT_EQ(sim.get_reg(3), 0x8010);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

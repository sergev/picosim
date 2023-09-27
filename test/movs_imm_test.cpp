#include <gtest/gtest.h>
#include <systemc.h>
#include "simulator.h"

//
// Make sure the SystemC library links correctly.
//
TEST(opcode, movs_imm)
{
    Simulator sim;

    sim.debug_store16(0x8000, 0x2080);  // movs r0, #128
    sim.debug_store16(0x8002, 0x2140);  // movs r1, #64
    sim.debug_store16(0x8004, 0x2220);  // movs r2, #32
    sim.debug_store16(0x8006, 0x2310);  // movs r3, #16
    sim.debug_store16(0x8008, 0x2408);  // movs r4, #8
    sim.debug_store16(0x800a, 0x2504);  // movs r5, #4
    sim.debug_store16(0x800c, 0x2602);  // movs r6, #2
    sim.debug_store16(0x800e, 0x2701);  // movs r7, #1
    sim.debug_store16(0x8010, 0xdf00);  // svc  0

    sim.run(0x8000);

    EXPECT_EQ(sim.get_instructions_executed(), 9);
    EXPECT_EQ(sim.get_reg(0), 128);
    EXPECT_EQ(sim.get_reg(1), 64);
    EXPECT_EQ(sim.get_reg(2), 32);
    EXPECT_EQ(sim.get_reg(3), 16);
    EXPECT_EQ(sim.get_reg(4), 8);
    EXPECT_EQ(sim.get_reg(5), 4);
    EXPECT_EQ(sim.get_reg(6), 2);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_pc(), 0x8012);
}

#include "sc_main.cpp"

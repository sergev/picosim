#include "util.h"

//
// Check SUB instruction, with SP plus immediate.
//
TEST(opcode, sub_sp_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4807);      // ldr r0, [pc, #28]
    sim.debug_store16(0x8002, 0x4685);      // mov sp, r0
    sim.debug_store16(0x8004, 0xb080);      // sub sp, #0
    sim.debug_store16(0x8006, 0x4669);      // mov r1, sp
    sim.debug_store16(0x8008, 0xb0eb);      // sub sp, #428
    sim.debug_store16(0x800a, 0x466a);      // mov r2, sp
    sim.debug_store16(0x800c, 0xb0c6);      // sub sp, #280
    sim.debug_store16(0x800e, 0x466b);      // mov r3, sp
    sim.debug_store16(0x8010, 0xb08d);      // sub sp, #52
    sim.debug_store16(0x8012, 0x466c);      // mov r4, sp
    sim.debug_store16(0x8014, 0xb0d7);      // sub sp, #348
    sim.debug_store16(0x8016, 0x466d);      // mov r5, sp
    sim.debug_store16(0x8018, 0xb0ff);      // sub sp, #508
    sim.debug_store16(0x801a, 0x466e);      // mov r6, sp
    sim.debug_store16(0x801c, 0x2701);      // movs r7, #1
    sim.debug_store16(0x801e, 0xdf00);      // svc 0
    sim.debug_store32(0x8020, 0x499602d2);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 16);
    EXPECT_EQ(sim.get_pc(), 0x8020);
    EXPECT_EQ(sim.get_reg(0), 1234567890);
    EXPECT_EQ(sim.get_reg(1), 1234567890);
    EXPECT_EQ(sim.get_reg(2), 1234567462);
    EXPECT_EQ(sim.get_reg(3), 1234567182);
    EXPECT_EQ(sim.get_reg(4), 1234567130);
    EXPECT_EQ(sim.get_reg(5), 1234566782);
    EXPECT_EQ(sim.get_reg(6), 1234566274);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

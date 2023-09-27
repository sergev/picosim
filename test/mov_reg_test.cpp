#include "util.h"

//
// Check MOV instruction with registers.
//
TEST(opcode, mov_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x490c);      // ldr r1, [pc, #48]
    sim.debug_store16(0x8002, 0x4669);      // mov r1, sp
    sim.debug_store16(0x8004, 0x46ad);      // mov sp, r5
    sim.debug_store16(0x8006, 0x4a0c);      // ldr r2, [pc, #48]
    sim.debug_store16(0x8008, 0x4672);      // mov r2, lr
    sim.debug_store16(0x800a, 0x469e);      // mov lr, r3
    sim.debug_store16(0x800c, 0x4c0b);      // ldr r4, [pc, #44]
    sim.debug_store16(0x800e, 0x466c);      // mov r4, sp
    sim.debug_store16(0x8010, 0x46b5);      // mov sp, r6
    sim.debug_store16(0x8012, 0x480b);      // ldr r0, [pc, #44]
    sim.debug_store16(0x8014, 0x4660);      // mov r0, ip
    sim.debug_store16(0x8016, 0x468c);      // mov ip, r1
    sim.debug_store16(0x8018, 0x4f0a);      // ldr r7, [pc, #40]
    sim.debug_store16(0x801a, 0x465f);      // mov r7, fp
    sim.debug_store16(0x801c, 0x4693);      // mov fp, r2
    sim.debug_store16(0x801e, 0x4f0a);      // ldr r7, [pc, #40]
    sim.debug_store16(0x8020, 0x4657);      // mov r7, sl
    sim.debug_store16(0x8022, 0x4682);      // mov sl, r0
    sim.debug_store16(0x8024, 0x4f09);      // ldr r7, [pc, #36]
    sim.debug_store16(0x8026, 0x464f);      // mov r7, r9
    sim.debug_store16(0x8028, 0x46a1);      // mov r9, r4
    sim.debug_store16(0x802a, 0x4f09);      // ldr r7, [pc, #36]
    sim.debug_store16(0x802c, 0x4647);      // mov r7, r8
    sim.debug_store16(0x802e, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8030, 0xdf00);      // svc 0
    sim.debug_store32(0x8034, 0x7502fe1f);
    sim.debug_store32(0x8038, 0xc015a134);
    sim.debug_store32(0x803c, 0xd306fde3);
    sim.debug_store32(0x8040, 0x43f705a9);
    sim.debug_store32(0x8044, 0x8c832ed2);
    sim.debug_store32(0x8048, 0xf83a2582);
    sim.debug_store32(0x804c, 0xabe76d49);
    sim.debug_store32(0x8050, 0xc5e3fe7d);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 25);
    EXPECT_EQ(sim.get_reg(15), 0x7502fe1f);
    EXPECT_EQ(sim.get_reg(5),  0x7502fe1f);
    EXPECT_EQ(sim.get_reg(14), 0xc015a134);
    EXPECT_EQ(sim.get_reg(3),  0xc015a134);
    EXPECT_EQ(sim.get_reg(13), 0xd306fde3);
    EXPECT_EQ(sim.get_reg(6),  0xd306fde3);
    EXPECT_EQ(sim.get_reg(12), 0x43f705a9);
    EXPECT_EQ(sim.get_reg(1),  0x43f705a9);
    EXPECT_EQ(sim.get_reg(11), 0x8c832ed2);
    EXPECT_EQ(sim.get_reg(2),  0x8c832ed2);
    EXPECT_EQ(sim.get_reg(10), 0xf83a2582);
    EXPECT_EQ(sim.get_reg(0),  0xf83a2582);
    EXPECT_EQ(sim.get_reg(9),  0xabe76d49);
    EXPECT_EQ(sim.get_reg(4),  0xabe76d49);
    EXPECT_EQ(sim.get_reg(8),  0xc5e3fe7d);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_pc(), 0x8032);
}

#include "sc_main.cpp"

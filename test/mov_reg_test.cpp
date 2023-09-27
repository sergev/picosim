#include "util.h"

//
// Check MOV instruction with registers.
//
TEST(opcode, mov_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x467d);       // mov r5, pc
    sim.debug_store16(0x8002, 0x490b);       // ldr r1, [pc, #44]
    sim.debug_store16(0x8004, 0x468e);       // mov lr, r1
    sim.debug_store16(0x8006, 0x4673);       // mov r3, lr
    sim.debug_store16(0x8008, 0x4c0a);       // ldr r4, [pc, #40]
    sim.debug_store16(0x800a, 0x46a5);       // mov sp, r4
    sim.debug_store16(0x800c, 0x466e);       // mov r6, sp
    sim.debug_store16(0x800e, 0x4a0a);       // ldr r2, [pc, #40]
    sim.debug_store16(0x8010, 0x4694);       // mov ip, r2
    sim.debug_store16(0x8012, 0x4661);       // mov r1, ip
    sim.debug_store16(0x8014, 0x4809);       // ldr r0, [pc, #36]
    sim.debug_store16(0x8016, 0x4683);       // mov fp, r0
    sim.debug_store16(0x8018, 0x465a);       // mov r2, fp
    sim.debug_store16(0x801a, 0x4f09);       // ldr r7, [pc, #36]
    sim.debug_store16(0x801c, 0x46ba);       // mov sl, r7
    sim.debug_store16(0x801e, 0x4650);       // mov r0, sl
    sim.debug_store16(0x8020, 0x4f08);       // ldr r7, [pc, #32]
    sim.debug_store16(0x8022, 0x46b9);       // mov r9, r7
    sim.debug_store16(0x8024, 0x464c);       // mov r4, r9
    sim.debug_store16(0x8026, 0x4f08);       // ldr r7, [pc, #32]
    sim.debug_store16(0x8028, 0x46b8);       // mov r8, r7
    sim.debug_store16(0x802a, 0x2701);       // movs r7, #1
    sim.debug_store16(0x802c, 0xdf00);       // svc 0
    sim.debug_store32(0x8030, 0xc015a134);
    sim.debug_store32(0x8034, 0xd306fde3);
    sim.debug_store32(0x8038, 0x43f705a9);
    sim.debug_store32(0x803c, 0x8c832ed2);
    sim.debug_store32(0x8040, 0xf83a2582);
    sim.debug_store32(0x8044, 0xabe76d49);
    sim.debug_store32(0x8048, 0xc5e3fe7d);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 23);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.get_reg(15), 0x802e);
    EXPECT_EQ(sim.get_reg(5),  0x8004);
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
}

#include "sc_main.cpp"

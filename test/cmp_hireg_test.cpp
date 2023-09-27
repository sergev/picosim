#include "util.h"

//
// Check CMP instruction with high registers.
//
TEST(opcode, cmp_hireg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4818);      // ldr r0, [pc, #96]
    sim.debug_store16(0x8002, 0x4b19);      // ldr r3, [pc, #100]
    sim.debug_store16(0x8004, 0x4680);      // mov r8, r0
    sim.debug_store16(0x8006, 0x4598);      // cmp r8, r3
    sim.debug_store16(0x8008, 0xf3ef);      // mrs r0, CPSR
    sim.debug_store16(0x800a, 0x8000);
    sim.debug_store16(0x800c, 0x4917);      // ldr r1, [pc, #92]
    sim.debug_store16(0x800e, 0x4c18);      // ldr r4, [pc, #96]
    sim.debug_store16(0x8010, 0x4689);      // mov r9, r1
    sim.debug_store16(0x8012, 0x45a1);      // cmp r9, r4
    sim.debug_store16(0x8014, 0xf3ef);      // mrs r1, CPSR
    sim.debug_store16(0x8016, 0x8100);
    sim.debug_store16(0x8018, 0x4a16);      // ldr r2, [pc, #88]
    sim.debug_store16(0x801a, 0x4d17);      // ldr r5, [pc, #92]
    sim.debug_store16(0x801c, 0x4692);      // mov sl, r2
    sim.debug_store16(0x801e, 0x45aa);      // cmp sl, r5
    sim.debug_store16(0x8020, 0xf3ef);      // mrs r2, CPSR
    sim.debug_store16(0x8022, 0x8200);
    sim.debug_store16(0x8024, 0x4b15);      // ldr r3, [pc, #84]
    sim.debug_store16(0x8026, 0x4f16);      // ldr r7, [pc, #88]
    sim.debug_store16(0x8028, 0x469b);      // mov fp, r3
    sim.debug_store16(0x802a, 0x45bb);      // cmp fp, r7
    sim.debug_store16(0x802c, 0xf3ef);      // mrs r3, CPSR
    sim.debug_store16(0x802e, 0x8300);
    sim.debug_store16(0x8030, 0x4c14);      // ldr r4, [pc, #80]
    sim.debug_store16(0x8032, 0x4d15);      // ldr r5, [pc, #84]
    sim.debug_store16(0x8034, 0x46a4);      // mov ip, r4
    sim.debug_store16(0x8036, 0x45ac);      // cmp ip, r5
    sim.debug_store16(0x8038, 0xf3ef);      // mrs r4, CPSR
    sim.debug_store16(0x803a, 0x8400);
    sim.debug_store16(0x803c, 0x4d13);      // ldr r5, [pc, #76]
    sim.debug_store16(0x803e, 0x4e14);      // ldr r6, [pc, #80]
    sim.debug_store16(0x8040, 0x46ad);      // mov sp, r5
    sim.debug_store16(0x8042, 0x45b5);      // cmp sp, r6
    sim.debug_store16(0x8044, 0xf3ef);      // mrs r5, CPSR
    sim.debug_store16(0x8046, 0x8500);
    sim.debug_store16(0x8048, 0x4e12);      // ldr r6, [pc, #72]
    sim.debug_store16(0x804a, 0x4f13);      // ldr r7, [pc, #76]
    sim.debug_store16(0x804c, 0x46b6);      // mov lr, r6
    sim.debug_store16(0x804e, 0x45be);      // cmp lr, r7
    sim.debug_store16(0x8050, 0xf3ef);      // mrs r6, CPSR
    sim.debug_store16(0x8052, 0x8600);
    sim.debug_store16(0x8054, 0x4f11);      // ldr r7, [pc, #68]
    sim.debug_store16(0x8056, 0x45bf);      // cmp pc, r7
    sim.debug_store16(0x8058, 0xf3ef);      // mrs r7, CPSR
    sim.debug_store16(0x805a, 0x8700);
    sim.debug_store16(0x805c, 0x46b8);      // mov r8, r7
    sim.debug_store16(0x805e, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8060, 0xdf00);      // svc 0
    sim.debug_store32(0x8064, 0x7502fe1f);
    sim.debug_store32(0x8068, 0xc015a134);
    sim.debug_store32(0x806c, 0x8c832ed2);
    sim.debug_store32(0x8070, 0xd306fde3);
    sim.debug_store32(0x8074, 0x9b74a3db);
    sim.debug_store32(0x8078, 0x776dd37e);
    sim.debug_store32(0x807c, 0xce671cdd);
    sim.debug_store32(0x8080, 0x549c13ba);
    sim.debug_store32(0x8084, 0xe22a7d31);
    sim.debug_store32(0x8088, 0x13d01f65);
    sim.debug_store32(0x808c, 0xeb514512);
    sim.debug_store32(0x8090, 0x1bc420c2);
    sim.debug_store32(0x8094, 0xd3b288b8);
    sim.debug_store32(0x8098, 0x8e22e5dc);
    sim.debug_store32(0x809c, 0x00008062);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 41);
    EXPECT_EQ(sim.get_pc(), 0x8062);
    EXPECT_EQ(sim.get_reg(0), 0x90000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(1), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(2), 0x30000000); // Carry+Overflow flag
    EXPECT_EQ(sim.get_reg(3), 0x30000000); // Carry+Overflow flag
    EXPECT_EQ(sim.get_reg(4), 0xa0000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(5), 0xa0000000); // Negative+Overflow flags
    EXPECT_EQ(sim.get_reg(6), 0x20000000); // Carry flag
    EXPECT_EQ(sim.get_reg(8), 0x80000000); // Negative flag
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

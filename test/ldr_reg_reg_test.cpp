#include "util.h"

//
// Check LDR instruction, with register plus register.
//
TEST(opcode, ldr_reg_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa10b);      // add r1, pc, #44
    sim.debug_store16(0x8002, 0x227c);      // movs r2, #124
    sim.debug_store16(0x8004, 0x5888);      // ldr r0, [r1, r2]
    sim.debug_store16(0x8006, 0xa20d);      // add r2, pc, #52
    sim.debug_store16(0x8008, 0x2364);      // movs r3, #100
    sim.debug_store16(0x800a, 0x58d1);      // ldr r1, [r2, r3]
    sim.debug_store16(0x800c, 0xa30f);      // add r3, pc, #60
    sim.debug_store16(0x800e, 0x243c);      // movs r4, #60
    sim.debug_store16(0x8010, 0x591a);      // ldr r2, [r3, r4]
    sim.debug_store16(0x8012, 0xa408);      // add r4, pc, #32
    sim.debug_store16(0x8014, 0x253c);      // movs r5, #60
    sim.debug_store16(0x8016, 0x5963);      // ldr r3, [r4, r5]
    sim.debug_store16(0x8018, 0xa505);      // add r5, pc, #20
    sim.debug_store16(0x801a, 0x2624);      // movs r6, #36
    sim.debug_store16(0x801c, 0x59ac);      // ldr r4, [r5, r6]
    sim.debug_store16(0x801e, 0xa604);      // add r6, pc, #16
    sim.debug_store16(0x8020, 0x2700);      // movs r7, #0
    sim.debug_store16(0x8022, 0x59f5);      // ldr r5, [r6, r7]
    sim.debug_store16(0x8024, 0xa60b);      // add r6, pc, #44
    sim.debug_store16(0x8026, 0x2728);      // movs r7, #40
    sim.debug_store16(0x8028, 0x59f6);      // ldr r6, [r6, r7]
    sim.debug_store16(0x802a, 0x2701);      // movs r7, #1
    sim.debug_store16(0x802c, 0xdf00);      // svc 0
    sim.debug_store32(0x8030, 0x9b74a3db);
    sim.debug_store32(0x8034, 0x776dd37e);
    sim.debug_store32(0x8038, 0x5fed565c);
    sim.debug_store32(0x803c, 0x751b4f33);
    sim.debug_store32(0x8040, 0x0173b5c5);
    sim.debug_store32(0x8044, 0xce671cdd);
    sim.debug_store32(0x8048, 0x549c13ba);
    sim.debug_store32(0x804c, 0xd933cd91);
    sim.debug_store32(0x8050, 0xf8f45bb2);
    sim.debug_store32(0x8054, 0x494fa207);
    sim.debug_store32(0x8058, 0x9c36aaf6);
    sim.debug_store32(0x805c, 0x8ce521d1);
    sim.debug_store32(0x8060, 0xcaa5267a);
    sim.debug_store32(0x8064, 0x740a57d7);
    sim.debug_store32(0x8068, 0xe0d87fa2);
    sim.debug_store32(0x806c, 0x67c594f8);
    sim.debug_store32(0x8070, 0x4e6c6ac2);
    sim.debug_store32(0x8074, 0x108d20e9);
    sim.debug_store32(0x8078, 0x847c96ca);
    sim.debug_store32(0x807c, 0x6c94ee62);
    sim.debug_store32(0x8080, 0xd19e5e4d);
    sim.debug_store32(0x8084, 0x0ecf11eb);
    sim.debug_store32(0x8088, 0x561469da);
    sim.debug_store32(0x808c, 0xa64a41a1);
    sim.debug_store32(0x8090, 0x3983f0ba);
    sim.debug_store32(0x8094, 0x096d513a);
    sim.debug_store32(0x8098, 0x326dac09);
    sim.debug_store32(0x809c, 0x83beceab);
    sim.debug_store32(0x80a0, 0x3903762c);
    sim.debug_store32(0x80a4, 0x34ea4ace);
    sim.debug_store32(0x80a8, 0x28c38ee0);
    sim.debug_store32(0x80ac, 0x573d213c);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 23);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.get_reg(0), 0x573d213c);
    EXPECT_EQ(sim.get_reg(1), 0x3903762c);
    EXPECT_EQ(sim.get_reg(2), 0x561469da);
    EXPECT_EQ(sim.get_reg(3), 0x4e6c6ac2);
    EXPECT_EQ(sim.get_reg(4), 0x494fa207);
    EXPECT_EQ(sim.get_reg(5), 0x9b74a3db);
    EXPECT_EQ(sim.get_reg(6), 0x6c94ee62);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

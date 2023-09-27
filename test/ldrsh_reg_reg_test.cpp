#include "util.h"

//
// Check LDRSH instruction, with register plus register.
//
TEST(opcode, ldrsh_reg_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa10b);      // add r1, pc, #44
    sim.debug_store16(0x8002, 0x223e);      // movs r2, #62
    sim.debug_store16(0x8004, 0x5e88);      // ldrsh r0, [r1, r2]
    sim.debug_store16(0x8006, 0xa20c);      // add r2, pc, #48
    sim.debug_store16(0x8008, 0x2332);      // movs r3, #50
    sim.debug_store16(0x800a, 0x5ed1);      // ldrsh r1, [r2, r3]
    sim.debug_store16(0x800c, 0xa30c);      // add r3, pc, #48
    sim.debug_store16(0x800e, 0x241e);      // movs r4, #30
    sim.debug_store16(0x8010, 0x5f1a);      // ldrsh r2, [r3, r4]
    sim.debug_store16(0x8012, 0xa408);      // add r4, pc, #32
    sim.debug_store16(0x8014, 0x251e);      // movs r5, #30
    sim.debug_store16(0x8016, 0x5f63);      // ldrsh r3, [r4, r5]
    sim.debug_store16(0x8018, 0xa505);      // add r5, pc, #20
    sim.debug_store16(0x801a, 0x2612);      // movs r6, #18
    sim.debug_store16(0x801c, 0x5fac);      // ldrsh r4, [r5, r6]
    sim.debug_store16(0x801e, 0xa604);      // add r6, pc, #16
    sim.debug_store16(0x8020, 0x2700);      // movs r7, #0
    sim.debug_store16(0x8022, 0x5ff5);      // ldrsh r5, [r6, r7]
    sim.debug_store16(0x8024, 0xa60b);      // add r6, pc, #44
    sim.debug_store16(0x8026, 0x2714);      // movs r7, #20
    sim.debug_store16(0x8028, 0x5ff6);      // ldrsh r6, [r6, r7]
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

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 23);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.get_reg(0), 0x67c5);
    EXPECT_EQ(sim.get_reg(1), 0xffffe0d8);
    EXPECT_EQ(sim.get_reg(2), 0xffff8ce5);
    EXPECT_EQ(sim.get_reg(3), 0xfffff8f4);
    EXPECT_EQ(sim.get_reg(4), 0x0173);
    EXPECT_EQ(sim.get_reg(5), 0xffffa3db);
    EXPECT_EQ(sim.get_reg(6), 0x7fa2);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

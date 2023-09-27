#include "util.h"

//
// Check LDRH instruction, with register plus immediate.
//
TEST(opcode, ldrh_reg_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa107);      // add r1, pc, #28
    sim.debug_store16(0x8002, 0x8fc8);      // ldrh r0, [r1, #62]
    sim.debug_store16(0x8004, 0xa208);      // add r2, pc, #32
    sim.debug_store16(0x8006, 0x8e51);      // ldrh r1, [r2, #50]
    sim.debug_store16(0x8008, 0xa309);      // add r3, pc, #36
    sim.debug_store16(0x800a, 0x8bda);      // ldrh r2, [r3, #30]
    sim.debug_store16(0x800c, 0xa405);      // add r4, pc, #20
    sim.debug_store16(0x800e, 0x8be3);      // ldrh r3, [r4, #30]
    sim.debug_store16(0x8010, 0xa503);      // add r5, pc, #12
    sim.debug_store16(0x8012, 0x8a6c);      // ldrh r4, [r5, #18]
    sim.debug_store16(0x8014, 0xa602);      // add r6, pc, #8
    sim.debug_store16(0x8016, 0x8835);      // ldrh r5, [r6, #0]
    sim.debug_store16(0x8018, 0xa70a);      // add r7, pc, #40
    sim.debug_store16(0x801a, 0x8abe);      // ldrh r6, [r7, #20]
    sim.debug_store16(0x801c, 0x2701);      // movs r7, #1
    sim.debug_store16(0x801e, 0xdf00);      // svc 0
    sim.debug_store32(0x8020, 0x9b74a3db);
    sim.debug_store32(0x8024, 0x776dd37e);
    sim.debug_store32(0x8028, 0x5fed565c);
    sim.debug_store32(0x802c, 0x751b4f33);
    sim.debug_store32(0x8030, 0x0173b5c5);
    sim.debug_store32(0x8034, 0xce671cdd);
    sim.debug_store32(0x8038, 0x549c13ba);
    sim.debug_store32(0x803c, 0xd933cd91);
    sim.debug_store32(0x8040, 0xf8f45bb2);
    sim.debug_store32(0x8044, 0x494fa207);
    sim.debug_store32(0x8048, 0x9c36aaf6);
    sim.debug_store32(0x804c, 0x8ce521d1);
    sim.debug_store32(0x8050, 0xcaa5267a);
    sim.debug_store32(0x8054, 0x740a57d7);
    sim.debug_store32(0x8058, 0xe0d87fa2);
    sim.debug_store32(0x805c, 0x67c594f8);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 16);
    EXPECT_EQ(sim.get_pc(), 0x8020);
    EXPECT_EQ(sim.get_reg(0), 0x67c5);
    EXPECT_EQ(sim.get_reg(1), 0xe0d8);
    EXPECT_EQ(sim.get_reg(2), 0x8ce5);
    EXPECT_EQ(sim.get_reg(3), 0xf8f4);
    EXPECT_EQ(sim.get_reg(4), 0x0173);
    EXPECT_EQ(sim.get_reg(5), 0xa3db);
    EXPECT_EQ(sim.get_reg(6), 0x7fa2);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

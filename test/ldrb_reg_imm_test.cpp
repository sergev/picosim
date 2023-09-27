#include "util.h"

//
// Check LDRB instruction, with register plus immediate.
//
TEST(opcode, ldrb_reg_imm)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa707);      // add r7, pc, #28
    sim.debug_store16(0x8002, 0x7ff8);      // ldrb r0, [r7, #31]
    sim.debug_store16(0x8004, 0xa207);      // add r2, pc, #28
    sim.debug_store16(0x8006, 0x7e51);      // ldrb r1, [r2, #25]
    sim.debug_store16(0x8008, 0xa308);      // add r3, pc, #32
    sim.debug_store16(0x800a, 0x7bda);      // ldrb r2, [r3, #15]
    sim.debug_store16(0x800c, 0xa405);      // add r4, pc, #20
    sim.debug_store16(0x800e, 0x7be3);      // ldrb r3, [r4, #15]
    sim.debug_store16(0x8010, 0xa505);      // add r5, pc, #20
    sim.debug_store16(0x8012, 0x786c);      // ldrb r4, [r5, #1]
    sim.debug_store16(0x8014, 0xa602);      // add r6, pc, #8
    sim.debug_store16(0x8016, 0x7835);      // ldrb r5, [r6, #0]
    sim.debug_store16(0x8018, 0xa706);      // add r7, pc, #24
    sim.debug_store16(0x801a, 0x7abe);      // ldrb r6, [r7, #10]
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

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 16);
    EXPECT_EQ(sim.get_pc(), 0x8020);
    EXPECT_EQ(sim.get_reg(0), 0xd9);
    EXPECT_EQ(sim.get_reg(1), 0xcd);
    EXPECT_EQ(sim.get_reg(2), 0x54);
    EXPECT_EQ(sim.get_reg(3), 0x01);
    EXPECT_EQ(sim.get_reg(4), 0x56);
    EXPECT_EQ(sim.get_reg(5), 0xdb);
    EXPECT_EQ(sim.get_reg(6), 0x33);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

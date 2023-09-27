#include "util.h"

//
// Check LDRSB instruction, with register plus register.
//
TEST(opcode, ldrsb_reg_reg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0xa10b);      // add r1, pc, #44
    sim.debug_store16(0x8002, 0x221f);      // movs r2, #31
    sim.debug_store16(0x8004, 0x5688);      // ldrsb r0, [r1, r2]
    sim.debug_store16(0x8006, 0xa20b);      // add r2, pc, #44
    sim.debug_store16(0x8008, 0x2319);      // movs r3, #25
    sim.debug_store16(0x800a, 0x56d1);      // ldrsb r1, [r2, r3]
    sim.debug_store16(0x800c, 0xa30b);      // add r3, pc, #44
    sim.debug_store16(0x800e, 0x240f);      // movs r4, #15
    sim.debug_store16(0x8010, 0x571a);      // ldrsb r2, [r3, r4]
    sim.debug_store16(0x8012, 0xa408);      // add r4, pc, #32
    sim.debug_store16(0x8014, 0x250f);      // movs r5, #15
    sim.debug_store16(0x8016, 0x5763);      // ldrsb r3, [r4, r5]
    sim.debug_store16(0x8018, 0xa507);      // add r5, pc, #28
    sim.debug_store16(0x801a, 0x2601);      // movs r6, #1
    sim.debug_store16(0x801c, 0x57ac);      // ldrsb r4, [r5, r6]
    sim.debug_store16(0x801e, 0xa604);      // add r6, pc, #16
    sim.debug_store16(0x8020, 0x2700);      // movs r7, #0
    sim.debug_store16(0x8022, 0x57f5);      // ldrsb r5, [r6, r7]
    sim.debug_store16(0x8024, 0xa607);      // add r6, pc, #28
    sim.debug_store16(0x8026, 0x270a);      // movs r7, #10
    sim.debug_store16(0x8028, 0x57f6);      // ldrsb r6, [r6, r7]
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

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 23);
    EXPECT_EQ(sim.get_pc(), 0x802e);
    EXPECT_EQ(sim.get_reg(0), 0xffffffd9);
    EXPECT_EQ(sim.get_reg(1), 0xffffffcd);
    EXPECT_EQ(sim.get_reg(2), 0x54);
    EXPECT_EQ(sim.get_reg(3), 0x01);
    EXPECT_EQ(sim.get_reg(4), 0x56);
    EXPECT_EQ(sim.get_reg(5), 0xffffffdb);
    EXPECT_EQ(sim.get_reg(6), 0x33);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

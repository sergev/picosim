#include "util.h"

//
// Check STMIA instruction.
//
TEST(opcode, stmia)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4805);      // ldr r0, [pc, #20]
    sim.debug_store16(0x8002, 0x4906);      // ldr r1, [pc, #24]
    sim.debug_store16(0x8004, 0xc003);      // stmia r0!, {r0, r1}
    sim.debug_store16(0x8006, 0x4a06);      // ldr r2, [pc, #24]
    sim.debug_store16(0x8008, 0x4b06);      // ldr r3, [pc, #24]
    sim.debug_store16(0x800a, 0x4c07);      // ldr r4, [pc, #28]
    sim.debug_store16(0x800c, 0x4d07);      // ldr r5, [pc, #28]
    sim.debug_store16(0x800e, 0x4e08);      // ldr r6, [pc, #32]
    sim.debug_store16(0x8010, 0x4f08);      // ldr r7, [pc, #32]
    sim.debug_store16(0x8012, 0xc5dc);      // stmia r5!, {r2, r3, r4, r6, r7}
    sim.debug_store16(0x8014, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8016, 0xdf00);      // svc 0
    sim.debug_store32(0x8018, 0x00009038);
    sim.debug_store32(0x801c, 0x23456789);
    sim.debug_store32(0x8020, 0x3456789a);
    sim.debug_store32(0x8024, 0x456789ab);
    sim.debug_store32(0x8028, 0x56789abc);
    sim.debug_store32(0x802c, 0x00009040);
    sim.debug_store32(0x8030, 0x789abcde);
    sim.debug_store32(0x8034, 0x89abcdef);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 12);
    EXPECT_EQ(sim.get_pc(), 0x8018);
    EXPECT_EQ(sim.debug_load32(0x9038 + 0),  0x9038);     // r0
    EXPECT_EQ(sim.debug_load32(0x9038 + 4),  0x23456789); // r1
    EXPECT_EQ(sim.get_reg(0), 0x9038 + 8);                // new r0
    EXPECT_EQ(sim.debug_load32(0x9038 + 8),  0x3456789a); // r2
    EXPECT_EQ(sim.debug_load32(0x9038 + 12), 0x456789ab); // r3
    EXPECT_EQ(sim.debug_load32(0x9038 + 16), 0x56789abc); // r4
    EXPECT_EQ(sim.debug_load32(0x9038 + 20), 0x789abcde); // r6
    EXPECT_EQ(sim.debug_load32(0x9038 + 24), 0x89abcdef); // r7
    EXPECT_EQ(sim.get_reg(5), 0x9038 + 28);               // new r5
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

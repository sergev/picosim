#include "util.h"

//
// Check MRS/MSR instructions with PSR registers.
//
TEST(opcode, mrs_msr_psr)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4f0f);      // ldr r7, [pc, #60]
    sim.debug_store32(0x8002, 0x8800f387);  // msr CPSR_f, r7
    sim.debug_store32(0x8006, 0x8000f3ef);  // mrs r0, CPSR
    sim.debug_store32(0x800a, 0x8801f387);  // msr IAPSR, r7
    sim.debug_store32(0x800e, 0x8101f3ef);  // mrs r1, IAPSR
    sim.debug_store32(0x8012, 0x8802f387);  // msr EAPSR, r7
    sim.debug_store32(0x8016, 0x8202f3ef);  // mrs r2, EAPSR
    sim.debug_store32(0x801a, 0x8803f387);  // msr PSR, r7
    sim.debug_store32(0x801e, 0x8303f3ef);  // mrs r3, PSR
    sim.debug_store32(0x8022, 0x8805f387);  // msr IPSR, r7
    sim.debug_store32(0x8026, 0x8405f3ef);  // mrs r4, IPSR
    sim.debug_store32(0x802a, 0x8806f387);  // msr EPSR, r7
    sim.debug_store32(0x802e, 0x8506f3ef);  // mrs r5, EPSR
    sim.debug_store32(0x8032, 0x8807f387);  // msr IEPSR, r7
    sim.debug_store32(0x8036, 0x8607f3ef);  // mrs r6, IEPSR
    sim.debug_store16(0x803a, 0x2701);      // movs r7, #1
    sim.debug_store16(0x803c, 0xdf00);      // svc 0
    sim.debug_store32(0x8040, 0xffffffff);  //.word 0xffffffff

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 17);
    EXPECT_EQ(sim.get_reg(0), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(1), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(2), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(3), 0xf000'0000);
    EXPECT_EQ(sim.get_reg(4), 0x0000'0000);
    EXPECT_EQ(sim.get_reg(5), 0x0000'0000);
    EXPECT_EQ(sim.get_reg(6), 0x0000'0000);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_pc(), 0x803e);
}

#include "sc_main.cpp"

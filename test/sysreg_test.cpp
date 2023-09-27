#include "util.h"

//
// Check MRS/MSR instructions with MSP/PSP/PRIMASK/COMTROL registers.
//
TEST(opcode, mrs_msr_sysreg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4f12);      // ldr r7, [pc, #72] @ (804c <_start+0x4c>)
    sim.debug_store32(0x8002, 0x8008f3ef);  // mrs r0, MSP
    sim.debug_store32(0x8006, 0x8808f387);  // msr MSP, r7
    sim.debug_store32(0x800a, 0x8108f3ef);  // mrs r1, MSP
    sim.debug_store32(0x800e, 0x8808f380);  // msr MSP, r0
    sim.debug_store32(0x8012, 0x8009f3ef);  // mrs r0, PSP
    sim.debug_store32(0x8016, 0x8809f387);  // msr PSP, r7
    sim.debug_store32(0x801a, 0x8209f3ef);  // mrs r2, PSP
    sim.debug_store32(0x801e, 0x8809f380);  // msr PSP, r0
    sim.debug_store16(0x8022, 0x2000);      // movs r0, #0
    sim.debug_store32(0x8024, 0x8810f387);  // msr PRIMASK, r7
    sim.debug_store32(0x8028, 0x8310f3ef);  // mrs r3, PRIMASK
    sim.debug_store32(0x802c, 0x8810f380);  // msr PRIMASK, r0
    sim.debug_store32(0x8030, 0x8410f3ef);  // mrs r4, PRIMASK
    sim.debug_store16(0x8034, 0x4f06);      // ldr r7, [pc, #24] @ (8050 <_start+0x50>)
    sim.debug_store32(0x8036, 0x8814f387);  // msr CONTROL, r7
    sim.debug_store32(0x803a, 0x8514f3ef);  // mrs r5, CONTROL
    sim.debug_store32(0x803e, 0x8814f380);  // msr CONTROL, r0
    sim.debug_store32(0x8042, 0x8614f3ef);  // mrs r6, CONTROL
    sim.debug_store16(0x8046, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8048, 0xdf00);      // svc 0
    sim.debug_store32(0x804c, 0xffffffff);  // .word 0xffffffff
    sim.debug_store32(0x8050, 0xfffffffe);  // .word 0xfffffffe

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 21);
    EXPECT_EQ(sim.get_reg(0), 0);
    EXPECT_EQ(sim.get_reg(1), 0xfffffffc);  // MSP all ones
    EXPECT_EQ(sim.get_reg(2), 0xfffffffc);  // PSP all ones
    EXPECT_EQ(sim.get_reg(3), 0x00000001);  // PRIMASK all ones
    EXPECT_EQ(sim.get_reg(4), 0x00000000);  // PRIMASK cleared
    EXPECT_EQ(sim.get_reg(5), 0x00000002);  // CONTROL all ones (except nPRIV bit)
    EXPECT_EQ(sim.get_reg(6), 0x00000000);  // CONTROL cleared
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_pc(), 0x804a);
}

#include "sc_main.cpp"

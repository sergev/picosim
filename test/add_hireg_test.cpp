#include "util.h"

//
// Check ADD instruction with high registers.
//
TEST(opcode, add_hireg)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x4814);      // ldr r0, [pc, #80]
    sim.debug_store16(0x8002, 0x4b15);      // ldr r3, [pc, #84]
    sim.debug_store16(0x8004, 0x4680);      // mov r8, r0
    sim.debug_store16(0x8006, 0x4498);      // add r8, r3
    sim.debug_store16(0x8008, 0x4814);      // ldr r0, [pc, #80]
    sim.debug_store16(0x800a, 0x4c15);      // ldr r4, [pc, #84]
    sim.debug_store16(0x800c, 0x4681);      // mov r9, r0
    sim.debug_store16(0x800e, 0x44a1);      // add r9, r4
    sim.debug_store16(0x8010, 0x4814);      // ldr r0, [pc, #80]
    sim.debug_store16(0x8012, 0x4d15);      // ldr r5, [pc, #84]
    sim.debug_store16(0x8014, 0x4682);      // mov sl, r0
    sim.debug_store16(0x8016, 0x44aa);      // add sl, r5
    sim.debug_store16(0x8018, 0x4814);      // ldr r0, [pc, #80]
    sim.debug_store16(0x801a, 0x4f15);      // ldr r7, [pc, #84]
    sim.debug_store16(0x801c, 0x4683);      // mov fp, r0
    sim.debug_store16(0x801e, 0x44bb);      // add fp, r7
    sim.debug_store16(0x8020, 0x4814);      // ldr r0, [pc, #80]
    sim.debug_store16(0x8022, 0x4a15);      // ldr r2, [pc, #84]
    sim.debug_store16(0x8024, 0x4684);      // mov ip, r0
    sim.debug_store16(0x8026, 0x4494);      // add ip, r2
    sim.debug_store16(0x8028, 0x4814);      // ldr r0, [pc, #80]
    sim.debug_store16(0x802a, 0x4915);      // ldr r1, [pc, #84]
    sim.debug_store16(0x802c, 0x4685);      // mov sp, r0
    sim.debug_store16(0x802e, 0x448d);      // add sp, r1
    sim.debug_store16(0x8030, 0x4814);      // ldr r0, [pc, #80]
    sim.debug_store16(0x8032, 0x4e15);      // ldr r6, [pc, #84]
    sim.debug_store16(0x8034, 0x4686);      // mov lr, r0
    sim.debug_store16(0x8036, 0x44b6);      // add lr, r6
    sim.debug_store16(0x8038, 0x2002);      // movs r0, #2
    sim.debug_store16(0x803a, 0x4487);      // add pc, r0
    sim.debug_store16(0x803c, 0x2701);      // movs r7, #1
    sim.debug_store16(0x803e, 0xdf00);      // svc 0
    sim.debug_store16(0x8040, 0x44c0);      // add r8, r8
    sim.debug_store16(0x8042, 0x444e);      // add r6, r9
    sim.debug_store16(0x8044, 0x4455);      // add r5, sl
    sim.debug_store16(0x8046, 0x445c);      // add r4, fp
    sim.debug_store16(0x8048, 0x4463);      // add r3, ip
    sim.debug_store16(0x804a, 0x446a);      // add r2, sp
    sim.debug_store16(0x804c, 0x4471);      // add r1, lr
    sim.debug_store16(0x804e, 0x4478);      // add r0, pc
    sim.debug_store16(0x8050, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8052, 0xdf00);      // svc 0
    sim.debug_store32(0x8054, 0x7502fe1f);
    sim.debug_store32(0x8058, 0xc015a134);
    sim.debug_store32(0x805c, 0x8c832ed2);
    sim.debug_store32(0x8060, 0xd306fde3);
    sim.debug_store32(0x8064, 0x9b74a3db);
    sim.debug_store32(0x8068, 0x776dd37e);
    sim.debug_store32(0x806c, 0xce671cdd);
    sim.debug_store32(0x8070, 0x549c13ba);
    sim.debug_store32(0x8074, 0xe22a7d31);
    sim.debug_store32(0x8078, 0x13d01f65);
    sim.debug_store32(0x807c, 0xeb514512);
    sim.debug_store32(0x8080, 0x1bc420c2);
    sim.debug_store32(0x8084, 0xd3b288b8);
    sim.debug_store32(0x8088, 0x8e22e5dc);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 40);
    EXPECT_EQ(sim.get_pc(), 0x8054);
    EXPECT_EQ(sim.get_reg(0), 0x8054);
    EXPECT_EQ(sim.get_reg(1), 0x7d998f56);
    EXPECT_EQ(sim.get_reg(2), 0x1ae58539);
    EXPECT_EQ(sim.get_reg(3), 0xb6103dca);
    EXPECT_EQ(sim.get_reg(4), 0xf60a2e7a);
    EXPECT_EQ(sim.get_reg(5), 0x8a504ad7);
    EXPECT_EQ(sim.get_reg(6), 0xedad1291);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_reg(8), 0x6a313ea6);
    EXPECT_EQ(sim.get_reg(9), 0x5f8a2cb5);
    EXPECT_EQ(sim.get_reg(10), 0x12e27759); // SL
    EXPECT_EQ(sim.get_reg(11), 0x23033097); // FP
    EXPECT_EQ(sim.get_reg(12), 0xf5fa9c96); // IP
    EXPECT_EQ(sim.get_reg(13), 0x071565d4); // SP
    EXPECT_EQ(sim.get_reg(14), 0x61d56e94); // LR
}

#include "sc_main.cpp"

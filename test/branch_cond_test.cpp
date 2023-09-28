#include "util.h"

//
// Check Bxx instructions.
//
TEST(opcode, branch_cond)
{
    Simulator sim;
    enable_trace();

    sim.debug_store16(0x8000, 0x2701);      // movs r7, #1
    sim.debug_store16(0x8002, 0x48c1);      // ldr r0, [pc, #772]
    sim.debug_store16(0x8004, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8006, 0x8800);
    sim.debug_store16(0x8008, 0xd000);      // beq.n 800c <fail1>
    sim.debug_store16(0x800a, 0xd100);      // bne.n 800e <fail1+0x2>
    sim.debug_store16(0x800c, 0xdf00);      // svc 0
    sim.debug_store16(0x800e, 0xd2fd);      // bcs.n 800c <fail1>
    sim.debug_store16(0x8010, 0xd300);      // bcc.n 8014 <fail1+0x8>
    sim.debug_store16(0x8012, 0xdf00);      // svc 0
    sim.debug_store16(0x8014, 0xd4fa);      // bmi.n 800c <fail1>
    sim.debug_store16(0x8016, 0xd500);      // bpl.n 801a <fail1+0xe>
    sim.debug_store16(0x8018, 0xdf00);      // svc 0
    sim.debug_store16(0x801a, 0xd6f7);      // bvs.n 800c <fail1>
    sim.debug_store16(0x801c, 0xd700);      // bvc.n 8020 <fail1+0x14>
    sim.debug_store16(0x801e, 0xdf00);      // svc 0
    sim.debug_store16(0x8020, 0xd8f4);      // bhi.n 800c <fail1>
    sim.debug_store16(0x8022, 0xd900);      // bls.n 8026 <fail1+0x1a>
    sim.debug_store16(0x8024, 0xdf00);      // svc 0
    sim.debug_store16(0x8026, 0xda00);      // bge.n 802a <fail1+0x1e>
    sim.debug_store16(0x8028, 0xdf00);      // svc 0
    sim.debug_store16(0x802a, 0xdbef);      // blt.n 800c <fail1>
    sim.debug_store16(0x802c, 0xdc00);      // bgt.n 8030 <fail1+0x24>
    sim.debug_store16(0x802e, 0xdf00);      // svc 0
    sim.debug_store16(0x8030, 0xddec);      // ble.n 800c <fail1>
    sim.debug_store16(0x8032, 0x48b6);      // ldr r0, [pc, #728]
    sim.debug_store16(0x8034, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8036, 0x8800);
    sim.debug_store16(0x8038, 0xd0e8);      // beq.n 800c <fail1>
    sim.debug_store16(0x803a, 0xd100);      // bne.n 803e <fail1+0x32>
    sim.debug_store16(0x803c, 0xdf00);      // svc 0
    sim.debug_store16(0x803e, 0xd2e5);      // bcs.n 800c <fail1>
    sim.debug_store16(0x8040, 0xd300);      // bcc.n 8044 <fail1+0x38>
    sim.debug_store16(0x8042, 0xdf00);      // svc 0
    sim.debug_store16(0x8044, 0xd4e2);      // bmi.n 800c <fail1>
    sim.debug_store16(0x8046, 0xd500);      // bpl.n 804a <fail1+0x3e>
    sim.debug_store16(0x8048, 0xdf00);      // svc 0
    sim.debug_store16(0x804a, 0xd600);      // bvs.n 804e <fail1+0x42>
    sim.debug_store16(0x804c, 0xdf00);      // svc 0
    sim.debug_store16(0x804e, 0xd7dd);      // bvc.n 800c <fail1>
    sim.debug_store16(0x8050, 0xd8dc);      // bhi.n 800c <fail1>
    sim.debug_store16(0x8052, 0xd900);      // bls.n 8056 <fail1+0x4a>
    sim.debug_store16(0x8054, 0xdf00);      // svc 0
    sim.debug_store16(0x8056, 0xdad9);      // bge.n 800c <fail1>
    sim.debug_store16(0x8058, 0xdb00);      // blt.n 805c <fail1+0x50>
    sim.debug_store16(0x805a, 0xdf00);      // svc 0
    sim.debug_store16(0x805c, 0xdcd6);      // bgt.n 800c <fail1>
    sim.debug_store16(0x805e, 0xdd00);      // ble.n 8062 <fail1+0x56>
    sim.debug_store16(0x8060, 0xdf00);      // svc 0
    sim.debug_store16(0x8062, 0x48ab);      // ldr r0, [pc, #684]
    sim.debug_store16(0x8064, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8066, 0x8800);
    sim.debug_store16(0x8068, 0xd0d0);      // beq.n 800c <fail1>
    sim.debug_store16(0x806a, 0xd100);      // bne.n 806e <fail1+0x62>
    sim.debug_store16(0x806c, 0xdf00);      // svc 0
    sim.debug_store16(0x806e, 0xd200);      // bcs.n 8072 <fail1+0x66>
    sim.debug_store16(0x8070, 0xdf00);      // svc 0
    sim.debug_store16(0x8072, 0xd3cb);      // bcc.n 800c <fail1>
    sim.debug_store16(0x8074, 0xd4ca);      // bmi.n 800c <fail1>
    sim.debug_store16(0x8076, 0xd500);      // bpl.n 807a <fail1+0x6e>
    sim.debug_store16(0x8078, 0xdf00);      // svc 0
    sim.debug_store16(0x807a, 0xd6c7);      // bvs.n 800c <fail1>
    sim.debug_store16(0x807c, 0xd700);      // bvc.n 8080 <fail1+0x74>
    sim.debug_store16(0x807e, 0xdf00);      // svc 0
    sim.debug_store16(0x8080, 0xd800);      // bhi.n 8084 <fail1+0x78>
    sim.debug_store16(0x8082, 0xdf00);      // svc 0
    sim.debug_store16(0x8084, 0xd9c2);      // bls.n 800c <fail1>
    sim.debug_store16(0x8086, 0xda00);      // bge.n 808a <fail1+0x7e>
    sim.debug_store16(0x8088, 0xdf00);      // svc 0
    sim.debug_store16(0x808a, 0xdbbf);      // blt.n 800c <fail1>
    sim.debug_store16(0x808c, 0xdc00);      // bgt.n 8090 <fail1+0x84>
    sim.debug_store16(0x808e, 0xdf00);      // svc 0
    sim.debug_store16(0x8090, 0xddbc);      // ble.n 800c <fail1>
    sim.debug_store16(0x8092, 0x48a0);      // ldr r0, [pc, #640]
    sim.debug_store16(0x8094, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8096, 0x8800);
    sim.debug_store16(0x8098, 0xd0b8);      // beq.n 800c <fail1>
    sim.debug_store16(0x809a, 0xd100);      // bne.n 809e <fail1+0x92>
    sim.debug_store16(0x809c, 0xdf00);      // svc 0
    sim.debug_store16(0x809e, 0xd200);      // bcs.n 80a2 <fail1+0x96>
    sim.debug_store16(0x80a0, 0xdf00);      // svc 0
    sim.debug_store16(0x80a2, 0xd3b3);      // bcc.n 800c <fail1>
    sim.debug_store16(0x80a4, 0xd4b2);      // bmi.n 800c <fail1>
    sim.debug_store16(0x80a6, 0xd500);      // bpl.n 80aa <fail1+0x9e>
    sim.debug_store16(0x80a8, 0xdf00);      // svc 0
    sim.debug_store16(0x80aa, 0xd600);      // bvs.n 80ae <fail1+0xa2>
    sim.debug_store16(0x80ac, 0xdf00);      // svc 0
    sim.debug_store16(0x80ae, 0xd7ad);      // bvc.n 800c <fail1>
    sim.debug_store16(0x80b0, 0xd800);      // bhi.n 80b4 <fail1+0xa8>
    sim.debug_store16(0x80b2, 0xdf00);      // svc 0
    sim.debug_store16(0x80b4, 0xd9aa);      // bls.n 800c <fail1>
    sim.debug_store16(0x80b6, 0xdaa9);      // bge.n 800c <fail1>
    sim.debug_store16(0x80b8, 0xdb00);      // blt.n 80bc <fail1+0xb0>
    sim.debug_store16(0x80ba, 0xdf00);      // svc 0
    sim.debug_store16(0x80bc, 0xdca6);      // bgt.n 800c <fail1>
    sim.debug_store16(0x80be, 0xdd00);      // ble.n 80c2 <fail1+0xb6>
    sim.debug_store16(0x80c0, 0xdf00);      // svc 0
    sim.debug_store16(0x80c2, 0x4895);      // ldr r0, [pc, #596]
    sim.debug_store16(0x80c4, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x80c6, 0x8800);
    sim.debug_store16(0x80c8, 0xd000);      // beq.n 80cc <fail1+0xc0>
    sim.debug_store16(0x80ca, 0xdf00);      // svc 0
    sim.debug_store16(0x80cc, 0xd19e);      // bne.n 800c <fail1>
    sim.debug_store16(0x80ce, 0xd29d);      // bcs.n 800c <fail1>
    sim.debug_store16(0x80d0, 0xd300);      // bcc.n 80d4 <fail1+0xc8>
    sim.debug_store16(0x80d2, 0xdf00);      // svc 0
    sim.debug_store16(0x80d4, 0xd49a);      // bmi.n 800c <fail1>
    sim.debug_store16(0x80d6, 0xd500);      // bpl.n 80da <fail1+0xce>
    sim.debug_store16(0x80d8, 0xdf00);      // svc 0
    sim.debug_store16(0x80da, 0xd697);      // bvs.n 800c <fail1>
    sim.debug_store16(0x80dc, 0xd700);      // bvc.n 80e0 <fail1+0xd4>
    sim.debug_store16(0x80de, 0xdf00);      // svc 0
    sim.debug_store16(0x80e0, 0xd894);      // bhi.n 800c <fail1>
    sim.debug_store16(0x80e2, 0xd900);      // bls.n 80e6 <fail1+0xda>
    sim.debug_store16(0x80e4, 0xdf00);      // svc 0
    sim.debug_store16(0x80e6, 0xda00);      // bge.n 80ea <fail1+0xde>
    sim.debug_store16(0x80e8, 0xdf00);      // svc 0
    sim.debug_store16(0x80ea, 0xdb8f);      // blt.n 800c <fail1>
    sim.debug_store16(0x80ec, 0xdc8e);      // bgt.n 800c <fail1>
    sim.debug_store16(0x80ee, 0xdd00);      // ble.n 80f2 <fail1+0xe6>
    sim.debug_store16(0x80f0, 0xdf00);      // svc 0
    sim.debug_store16(0x80f2, 0x488a);      // ldr r0, [pc, #552]
    sim.debug_store16(0x80f4, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x80f6, 0x8800);
    sim.debug_store16(0x80f8, 0xd000);      // beq.n 80fc <fail1+0xf0>
    sim.debug_store16(0x80fa, 0xdf00);      // svc 0
    sim.debug_store16(0x80fc, 0xd101);      // bne.n 8102 <fail2>
    sim.debug_store16(0x80fe, 0xd200);      // bcs.n 8102 <fail2>
    sim.debug_store16(0x8100, 0xd300);      // bcc.n 8104 <fail2+0x2>
    sim.debug_store16(0x8102, 0xdf00);      // svc 0
    sim.debug_store16(0x8104, 0xd4fd);      // bmi.n 8102 <fail2>
    sim.debug_store16(0x8106, 0xd500);      // bpl.n 810a <fail2+0x8>
    sim.debug_store16(0x8108, 0xdf00);      // svc 0
    sim.debug_store16(0x810a, 0xd600);      // bvs.n 810e <fail2+0xc>
    sim.debug_store16(0x810c, 0xdf00);      // svc 0
    sim.debug_store16(0x810e, 0xd7f8);      // bvc.n 8102 <fail2>
    sim.debug_store16(0x8110, 0xd8f7);      // bhi.n 8102 <fail2>
    sim.debug_store16(0x8112, 0xd900);      // bls.n 8116 <fail2+0x14>
    sim.debug_store16(0x8114, 0xdf00);      // svc 0
    sim.debug_store16(0x8116, 0xdaf4);      // bge.n 8102 <fail2>
    sim.debug_store16(0x8118, 0xdb00);      // blt.n 811c <fail2+0x1a>
    sim.debug_store16(0x811a, 0xdf00);      // svc 0
    sim.debug_store16(0x811c, 0xdcf1);      // bgt.n 8102 <fail2>
    sim.debug_store16(0x811e, 0xdd00);      // ble.n 8122 <fail2+0x20>
    sim.debug_store16(0x8120, 0xdf00);      // svc 0
    sim.debug_store16(0x8122, 0x487f);      // ldr r0, [pc, #508]
    sim.debug_store16(0x8124, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8126, 0x8800);
    sim.debug_store16(0x8128, 0xd000);      // beq.n 812c <fail2+0x2a>
    sim.debug_store16(0x812a, 0xdf00);      // svc 0
    sim.debug_store16(0x812c, 0xd1e9);      // bne.n 8102 <fail2>
    sim.debug_store16(0x812e, 0xd200);      // bcs.n 8132 <fail2+0x30>
    sim.debug_store16(0x8130, 0xdf00);      // svc 0
    sim.debug_store16(0x8132, 0xd3e6);      // bcc.n 8102 <fail2>
    sim.debug_store16(0x8134, 0xd4e5);      // bmi.n 8102 <fail2>
    sim.debug_store16(0x8136, 0xd500);      // bpl.n 813a <fail2+0x38>
    sim.debug_store16(0x8138, 0xdf00);      // svc 0
    sim.debug_store16(0x813a, 0xd6e2);      // bvs.n 8102 <fail2>
    sim.debug_store16(0x813c, 0xd700);      // bvc.n 8140 <fail2+0x3e>
    sim.debug_store16(0x813e, 0xdf00);      // svc 0
    sim.debug_store16(0x8140, 0xd8df);      // bhi.n 8102 <fail2>
    sim.debug_store16(0x8142, 0xd900);      // bls.n 8146 <fail2+0x44>
    sim.debug_store16(0x8144, 0xdf00);      // svc 0
    sim.debug_store16(0x8146, 0xda00);      // bge.n 814a <fail2+0x48>
    sim.debug_store16(0x8148, 0xdf00);      // svc 0
    sim.debug_store16(0x814a, 0xdbda);      // blt.n 8102 <fail2>
    sim.debug_store16(0x814c, 0xdcd9);      // bgt.n 8102 <fail2>
    sim.debug_store16(0x814e, 0xdd00);      // ble.n 8152 <fail2+0x50>
    sim.debug_store16(0x8150, 0xdf00);      // svc 0
    sim.debug_store16(0x8152, 0x4874);      // ldr r0, [pc, #464]
    sim.debug_store16(0x8154, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8156, 0x8800);
    sim.debug_store16(0x8158, 0xd000);      // beq.n 815c <fail2+0x5a>
    sim.debug_store16(0x815a, 0xdf00);      // svc 0
    sim.debug_store16(0x815c, 0xd1d1);      // bne.n 8102 <fail2>
    sim.debug_store16(0x815e, 0xd200);      // bcs.n 8162 <fail2+0x60>
    sim.debug_store16(0x8160, 0xdf00);      // svc 0
    sim.debug_store16(0x8162, 0xd3ce);      // bcc.n 8102 <fail2>
    sim.debug_store16(0x8164, 0xd4cd);      // bmi.n 8102 <fail2>
    sim.debug_store16(0x8166, 0xd500);      // bpl.n 816a <fail2+0x68>
    sim.debug_store16(0x8168, 0xdf00);      // svc 0
    sim.debug_store16(0x816a, 0xd600);      // bvs.n 816e <fail2+0x6c>
    sim.debug_store16(0x816c, 0xdf00);      // svc 0
    sim.debug_store16(0x816e, 0xd7c8);      // bvc.n 8102 <fail2>
    sim.debug_store16(0x8170, 0xd8c7);      // bhi.n 8102 <fail2>
    sim.debug_store16(0x8172, 0xd900);      // bls.n 8176 <fail2+0x74>
    sim.debug_store16(0x8174, 0xdf00);      // svc 0
    sim.debug_store16(0x8176, 0xdac4);      // bge.n 8102 <fail2>
    sim.debug_store16(0x8178, 0xdb00);      // blt.n 817c <fail2+0x7a>
    sim.debug_store16(0x817a, 0xdf00);      // svc 0
    sim.debug_store16(0x817c, 0xdcc1);      // bgt.n 8102 <fail2>
    sim.debug_store16(0x817e, 0xdd00);      // ble.n 8182 <fail2+0x80>
    sim.debug_store16(0x8180, 0xdf00);      // svc 0
    sim.debug_store16(0x8182, 0x4869);      // ldr r0, [pc, #420]
    sim.debug_store16(0x8184, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8186, 0x8800);
    sim.debug_store16(0x8188, 0xd0bb);      // beq.n 8102 <fail2>
    sim.debug_store16(0x818a, 0xd100);      // bne.n 818e <fail2+0x8c>
    sim.debug_store16(0x818c, 0xdf00);      // svc 0
    sim.debug_store16(0x818e, 0xd2b8);      // bcs.n 8102 <fail2>
    sim.debug_store16(0x8190, 0xd300);      // bcc.n 8194 <fail2+0x92>
    sim.debug_store16(0x8192, 0xdf00);      // svc 0
    sim.debug_store16(0x8194, 0xd400);      // bmi.n 8198 <fail2+0x96>
    sim.debug_store16(0x8196, 0xdf00);      // svc 0
    sim.debug_store16(0x8198, 0xd5b3);      // bpl.n 8102 <fail2>
    sim.debug_store16(0x819a, 0xd6b2);      // bvs.n 8102 <fail2>
    sim.debug_store16(0x819c, 0xd700);      // bvc.n 81a0 <fail2+0x9e>
    sim.debug_store16(0x819e, 0xdf00);      // svc 0
    sim.debug_store16(0x81a0, 0xd8af);      // bhi.n 8102 <fail2>
    sim.debug_store16(0x81a2, 0xd900);      // bls.n 81a6 <fail2+0xa4>
    sim.debug_store16(0x81a4, 0xdf00);      // svc 0
    sim.debug_store16(0x81a6, 0xdaac);      // bge.n 8102 <fail2>
    sim.debug_store16(0x81a8, 0xdb00);      // blt.n 81ac <fail2+0xaa>
    sim.debug_store16(0x81aa, 0xdf00);      // svc 0
    sim.debug_store16(0x81ac, 0xdca9);      // bgt.n 8102 <fail2>
    sim.debug_store16(0x81ae, 0xdd00);      // ble.n 81b2 <fail2+0xb0>
    sim.debug_store16(0x81b0, 0xdf00);      // svc 0
    sim.debug_store16(0x81b2, 0x485e);      // ldr r0, [pc, #376]
    sim.debug_store16(0x81b4, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x81b6, 0x8800);
    sim.debug_store16(0x81b8, 0xd0a3);      // beq.n 8102 <fail2>
    sim.debug_store16(0x81ba, 0xd100);      // bne.n 81be <fail2+0xbc>
    sim.debug_store16(0x81bc, 0xdf00);      // svc 0
    sim.debug_store16(0x81be, 0xd2a0);      // bcs.n 8102 <fail2>
    sim.debug_store16(0x81c0, 0xd300);      // bcc.n 81c4 <fail2+0xc2>
    sim.debug_store16(0x81c2, 0xdf00);      // svc 0
    sim.debug_store16(0x81c4, 0xd400);      // bmi.n 81c8 <fail2+0xc6>
    sim.debug_store16(0x81c6, 0xdf00);      // svc 0
    sim.debug_store16(0x81c8, 0xd59b);      // bpl.n 8102 <fail2>
    sim.debug_store16(0x81ca, 0xd600);      // bvs.n 81ce <fail2+0xcc>
    sim.debug_store16(0x81cc, 0xdf00);      // svc 0
    sim.debug_store16(0x81ce, 0xd798);      // bvc.n 8102 <fail2>
    sim.debug_store16(0x81d0, 0xd897);      // bhi.n 8102 <fail2>
    sim.debug_store16(0x81d2, 0xd900);      // bls.n 81d6 <fail2+0xd4>
    sim.debug_store16(0x81d4, 0xdf00);      // svc 0
    sim.debug_store16(0x81d6, 0xda00);      // bge.n 81da <fail2+0xd8>
    sim.debug_store16(0x81d8, 0xdf00);      // svc 0
    sim.debug_store16(0x81da, 0xdb92);      // blt.n 8102 <fail2>
    sim.debug_store16(0x81dc, 0xdc00);      // bgt.n 81e0 <fail2+0xde>
    sim.debug_store16(0x81de, 0xdf00);      // svc 0
    sim.debug_store16(0x81e0, 0xdd8f);      // ble.n 8102 <fail2>
    sim.debug_store16(0x81e2, 0x4853);      // ldr r0, [pc, #332]
    sim.debug_store16(0x81e4, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x81e6, 0x8800);
    sim.debug_store16(0x81e8, 0xd000);      // beq.n 81ec <fail3>
    sim.debug_store16(0x81ea, 0xd100);      // bne.n 81ee <fail3+0x2>
    sim.debug_store16(0x81ec, 0xdf00);      // svc 0
    sim.debug_store16(0x81ee, 0xd200);      // bcs.n 81f2 <fail3+0x6>
    sim.debug_store16(0x81f0, 0xdf00);      // svc 0
    sim.debug_store16(0x81f2, 0xd3fb);      // bcc.n 81ec <fail3>
    sim.debug_store16(0x81f4, 0xd400);      // bmi.n 81f8 <fail3+0xc>
    sim.debug_store16(0x81f6, 0xdf00);      // svc 0
    sim.debug_store16(0x81f8, 0xd5f8);      // bpl.n 81ec <fail3>
    sim.debug_store16(0x81fa, 0xd6f7);      // bvs.n 81ec <fail3>
    sim.debug_store16(0x81fc, 0xd700);      // bvc.n 8200 <fail3+0x14>
    sim.debug_store16(0x81fe, 0xdf00);      // svc 0
    sim.debug_store16(0x8200, 0xd800);      // bhi.n 8204 <fail3+0x18>
    sim.debug_store16(0x8202, 0xdf00);      // svc 0
    sim.debug_store16(0x8204, 0xd9f2);      // bls.n 81ec <fail3>
    sim.debug_store16(0x8206, 0xdaf1);      // bge.n 81ec <fail3>
    sim.debug_store16(0x8208, 0xdb00);      // blt.n 820c <fail3+0x20>
    sim.debug_store16(0x820a, 0xdf00);      // svc 0
    sim.debug_store16(0x820c, 0xdcee);      // bgt.n 81ec <fail3>
    sim.debug_store16(0x820e, 0xdd00);      // ble.n 8212 <fail3+0x26>
    sim.debug_store16(0x8210, 0xdf00);      // svc 0
    sim.debug_store16(0x8212, 0x4848);      // ldr r0, [pc, #288]
    sim.debug_store16(0x8214, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8216, 0x8800);
    sim.debug_store16(0x8218, 0xd074);      // beq.n 8304 <fail>
    sim.debug_store16(0x821a, 0xd100);      // bne.n 821e <fail3+0x32>
    sim.debug_store16(0x821c, 0xdf00);      // svc 0
    sim.debug_store16(0x821e, 0xd200);      // bcs.n 8222 <fail3+0x36>
    sim.debug_store16(0x8220, 0xdf00);      // svc 0
    sim.debug_store16(0x8222, 0xd36f);      // bcc.n 8304 <fail>
    sim.debug_store16(0x8224, 0xd400);      // bmi.n 8228 <fail3+0x3c>
    sim.debug_store16(0x8226, 0xdf00);      // svc 0
    sim.debug_store16(0x8228, 0xd56c);      // bpl.n 8304 <fail>
    sim.debug_store16(0x822a, 0xd600);      // bvs.n 822e <fail3+0x42>
    sim.debug_store16(0x822c, 0xdf00);      // svc 0
    sim.debug_store16(0x822e, 0xd769);      // bvc.n 8304 <fail>
    sim.debug_store16(0x8230, 0xd800);      // bhi.n 8234 <fail3+0x48>
    sim.debug_store16(0x8232, 0xdf00);      // svc 0
    sim.debug_store16(0x8234, 0xd966);      // bls.n 8304 <fail>
    sim.debug_store16(0x8236, 0xda00);      // bge.n 823a <fail3+0x4e>
    sim.debug_store16(0x8238, 0xdf00);      // svc 0
    sim.debug_store16(0x823a, 0xdb63);      // blt.n 8304 <fail>
    sim.debug_store16(0x823c, 0xdc00);      // bgt.n 8240 <fail3+0x54>
    sim.debug_store16(0x823e, 0xdf00);      // svc 0
    sim.debug_store16(0x8240, 0xdd60);      // ble.n 8304 <fail>
    sim.debug_store16(0x8242, 0x483d);      // ldr r0, [pc, #244]
    sim.debug_store16(0x8244, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8246, 0x8800);
    sim.debug_store16(0x8248, 0xd000);      // beq.n 824c <fail3+0x60>
    sim.debug_store16(0x824a, 0xdf00);      // svc 0
    sim.debug_store16(0x824c, 0xd15a);      // bne.n 8304 <fail>
    sim.debug_store16(0x824e, 0xd259);      // bcs.n 8304 <fail>
    sim.debug_store16(0x8250, 0xd300);      // bcc.n 8254 <fail3+0x68>
    sim.debug_store16(0x8252, 0xdf00);      // svc 0
    sim.debug_store16(0x8254, 0xd400);      // bmi.n 8258 <fail3+0x6c>
    sim.debug_store16(0x8256, 0xdf00);      // svc 0
    sim.debug_store16(0x8258, 0xd554);      // bpl.n 8304 <fail>
    sim.debug_store16(0x825a, 0xd653);      // bvs.n 8304 <fail>
    sim.debug_store16(0x825c, 0xd700);      // bvc.n 8260 <fail3+0x74>
    sim.debug_store16(0x825e, 0xdf00);      // svc 0
    sim.debug_store16(0x8260, 0xd850);      // bhi.n 8304 <fail>
    sim.debug_store16(0x8262, 0xd900);      // bls.n 8266 <fail3+0x7a>
    sim.debug_store16(0x8264, 0xdf00);      // svc 0
    sim.debug_store16(0x8266, 0xda4d);      // bge.n 8304 <fail>
    sim.debug_store16(0x8268, 0xdb00);      // blt.n 826c <fail3+0x80>
    sim.debug_store16(0x826a, 0xdf00);      // svc 0
    sim.debug_store16(0x826c, 0xdc4a);      // bgt.n 8304 <fail>
    sim.debug_store16(0x826e, 0xdd00);      // ble.n 8272 <fail3+0x86>
    sim.debug_store16(0x8270, 0xdf00);      // svc 0
    sim.debug_store16(0x8272, 0x4832);      // ldr r0, [pc, #200]
    sim.debug_store16(0x8274, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x8276, 0x8800);
    sim.debug_store16(0x8278, 0xd000);      // beq.n 827c <fail3+0x90>
    sim.debug_store16(0x827a, 0xdf00);      // svc 0
    sim.debug_store16(0x827c, 0xd142);      // bne.n 8304 <fail>
    sim.debug_store16(0x827e, 0xd241);      // bcs.n 8304 <fail>
    sim.debug_store16(0x8280, 0xd300);      // bcc.n 8284 <fail3+0x98>
    sim.debug_store16(0x8282, 0xdf00);      // svc 0
    sim.debug_store16(0x8284, 0xd400);      // bmi.n 8288 <fail3+0x9c>
    sim.debug_store16(0x8286, 0xdf00);      // svc 0
    sim.debug_store16(0x8288, 0xd53c);      // bpl.n 8304 <fail>
    sim.debug_store16(0x828a, 0xd600);      // bvs.n 828e <fail3+0xa2>
    sim.debug_store16(0x828c, 0xdf00);      // svc 0
    sim.debug_store16(0x828e, 0xd739);      // bvc.n 8304 <fail>
    sim.debug_store16(0x8290, 0xd838);      // bhi.n 8304 <fail>
    sim.debug_store16(0x8292, 0xd900);      // bls.n 8296 <fail3+0xaa>
    sim.debug_store16(0x8294, 0xdf00);      // svc 0
    sim.debug_store16(0x8296, 0xda00);      // bge.n 829a <fail3+0xae>
    sim.debug_store16(0x8298, 0xdf00);      // svc 0
    sim.debug_store16(0x829a, 0xdb33);      // blt.n 8304 <fail>
    sim.debug_store16(0x829c, 0xdc32);      // bgt.n 8304 <fail>
    sim.debug_store16(0x829e, 0xdd00);      // ble.n 82a2 <fail3+0xb6>
    sim.debug_store16(0x82a0, 0xdf00);      // svc 0
    sim.debug_store16(0x82a2, 0x4827);      // ldr r0, [pc, #156]
    sim.debug_store16(0x82a4, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x82a6, 0x8800);
    sim.debug_store16(0x82a8, 0xd000);      // beq.n 82ac <fail3+0xc0>
    sim.debug_store16(0x82aa, 0xdf00);      // svc 0
    sim.debug_store16(0x82ac, 0xd12a);      // bne.n 8304 <fail>
    sim.debug_store16(0x82ae, 0xd200);      // bcs.n 82b2 <fail3+0xc6>
    sim.debug_store16(0x82b0, 0xdf00);      // svc 0
    sim.debug_store16(0x82b2, 0xd327);      // bcc.n 8304 <fail>
    sim.debug_store16(0x82b4, 0xd400);      // bmi.n 82b8 <fail3+0xcc>
    sim.debug_store16(0x82b6, 0xdf00);      // svc 0
    sim.debug_store16(0x82b8, 0xd524);      // bpl.n 8304 <fail>
    sim.debug_store16(0x82ba, 0xd623);      // bvs.n 8304 <fail>
    sim.debug_store16(0x82bc, 0xd700);      // bvc.n 82c0 <fail3+0xd4>
    sim.debug_store16(0x82be, 0xdf00);      // svc 0
    sim.debug_store16(0x82c0, 0xd820);      // bhi.n 8304 <fail>
    sim.debug_store16(0x82c2, 0xd900);      // bls.n 82c6 <fail3+0xda>
    sim.debug_store16(0x82c4, 0xdf00);      // svc 0
    sim.debug_store16(0x82c6, 0xda1d);      // bge.n 8304 <fail>
    sim.debug_store16(0x82c8, 0xdb00);      // blt.n 82cc <fail3+0xe0>
    sim.debug_store16(0x82ca, 0xdf00);      // svc 0
    sim.debug_store16(0x82cc, 0xdc1a);      // bgt.n 8304 <fail>
    sim.debug_store16(0x82ce, 0xdd00);      // ble.n 82d2 <fail3+0xe6>
    sim.debug_store16(0x82d0, 0xdf00);      // svc 0
    sim.debug_store16(0x82d2, 0x481c);      // ldr r0, [pc, #112]
    sim.debug_store16(0x82d4, 0xf380);      // msr CPSR_f, r0
    sim.debug_store16(0x82d6, 0x8800);
    sim.debug_store16(0x82d8, 0xd000);      // beq.n 82dc <fail3+0xf0>
    sim.debug_store16(0x82da, 0xdf00);      // svc 0
    sim.debug_store16(0x82dc, 0xd112);      // bne.n 8304 <fail>
    sim.debug_store16(0x82de, 0xd200);      // bcs.n 82e2 <fail3+0xf6>
    sim.debug_store16(0x82e0, 0xdf00);      // svc 0
    sim.debug_store16(0x82e2, 0xd30f);      // bcc.n 8304 <fail>
    sim.debug_store16(0x82e4, 0xd400);      // bmi.n 82e8 <fail3+0xfc>
    sim.debug_store16(0x82e6, 0xdf00);      // svc 0
    sim.debug_store16(0x82e8, 0xd50c);      // bpl.n 8304 <fail>
    sim.debug_store16(0x82ea, 0xd600);      // bvs.n 82ee <fail3+0x102>
    sim.debug_store16(0x82ec, 0xdf00);      // svc 0
    sim.debug_store16(0x82ee, 0xd709);      // bvc.n 8304 <fail>
    sim.debug_store16(0x82f0, 0xd808);      // bhi.n 8304 <fail>
    sim.debug_store16(0x82f2, 0xd900);      // bls.n 82f6 <fail3+0x10a>
    sim.debug_store16(0x82f4, 0xdf00);      // svc 0
    sim.debug_store16(0x82f6, 0xda00);      // bge.n 82fa <fail3+0x10e>
    sim.debug_store16(0x82f8, 0xdf00);      // svc 0
    sim.debug_store16(0x82fa, 0xdb03);      // blt.n 8304 <fail>
    sim.debug_store16(0x82fc, 0xdc02);      // bgt.n 8304 <fail>
    sim.debug_store16(0x82fe, 0xdd00);      // ble.n 8302 <fail3+0x116>
    sim.debug_store16(0x8300, 0xdf00);      // svc 0
    sim.debug_store16(0x8302, 0xdf00);      // svc 0 - test passed
    sim.debug_store16(0x8304, 0xdf00);      // svc 0
    sim.debug_store32(0x8308, 0x00000000);
    sim.debug_store32(0x830c, 0x10000000);
    sim.debug_store32(0x8310, 0x20000000);
    sim.debug_store32(0x8314, 0x30000000);
    sim.debug_store32(0x8318, 0x40000000);
    sim.debug_store32(0x831c, 0x50000000);
    sim.debug_store32(0x8320, 0x60000000);
    sim.debug_store32(0x8324, 0x70000000);
    sim.debug_store32(0x8328, 0x80000000);
    sim.debug_store32(0x832c, 0x90000000);
    sim.debug_store32(0x8330, 0xa0000000);
    sim.debug_store32(0x8334, 0xb0000000);
    sim.debug_store32(0x8338, 0xc0000000);
    sim.debug_store32(0x833c, 0xd0000000);
    sim.debug_store32(0x8340, 0xe0000000);
    sim.debug_store32(0x8344, 0xf0000000);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 258);
    EXPECT_EQ(sim.get_pc(), 0x8304);
    EXPECT_EQ(sim.get_reg(7), 1);
}

#include "sc_main.cpp"

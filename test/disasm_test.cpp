#include <gtest/gtest.h>

#include "disassemble.h"

//
// Disassemble the opcode and compare result.
//
void test_disasm(unsigned opcode, const std::string &expect)
{
    unsigned const address = 0x12345678;
    EXPECT_EQ(arm_disassemble(opcode, address), expect);
}

TEST(disasm, opcode32)
{
    test_disasm(0xf000d000, "bl 0x12f4567c");
    test_disasm(0xf000d001, "bl 0x12f4567e");
    test_disasm(0xf000d002, "bl 0x12f45680");
    test_disasm(0xf000d004, "bl 0x12f45684");
    test_disasm(0xf000d008, "bl 0x12f4568c");
    test_disasm(0xf000d010, "bl 0x12f4569c");
    test_disasm(0xf000d020, "bl 0x12f456bc");
    test_disasm(0xf000d040, "bl 0x12f456fc");
    test_disasm(0xf000d080, "bl 0x12f4577c");
    test_disasm(0xf000d100, "bl 0x12f4587c");
    test_disasm(0xf000d200, "bl 0x12f45a7c");
    test_disasm(0xf000d400, "bl 0x12f45e7c");
    test_disasm(0xf000d800, "bl 0x12b4567c");
    test_disasm(0xf001d000, "bl 0x12f4667c");
    test_disasm(0xf002d000, "bl 0x12f4767c");
    test_disasm(0xf004d000, "bl 0x12f4967c");
    test_disasm(0xf008d000, "bl 0x12f4d67c");
    test_disasm(0xf010d000, "bl 0x12f5567c");
    test_disasm(0xf020d000, "bl 0x12f6567c");
    test_disasm(0xf040d000, "bl 0x12f8567c");
    test_disasm(0xf080d000, "bl 0x12fc567c");
    test_disasm(0xf100d000, "bl 0x1304567c");
    test_disasm(0xf200d000, "bl 0x1314567c");
    test_disasm(0xf400d000, "bl 0x1134567c");
    test_disasm(0xf000f000, "bl 0x1274567c");
    test_disasm(0xf000f001, "bl 0x1274567e");
    test_disasm(0xf000f002, "bl 0x12745680");
    test_disasm(0xf000f004, "bl 0x12745684");
    test_disasm(0xf000f008, "bl 0x1274568c");
    test_disasm(0xf000f010, "bl 0x1274569c");
    test_disasm(0xf000f020, "bl 0x127456bc");
    test_disasm(0xf000f040, "bl 0x127456fc");
    test_disasm(0xf000f080, "bl 0x1274577c");
    test_disasm(0xf000f100, "bl 0x1274587c");
    test_disasm(0xf000f200, "bl 0x12745a7c");
    test_disasm(0xf000f400, "bl 0x12745e7c");
    test_disasm(0xf000f800, "bl 0x1234567c");
    test_disasm(0xf001f000, "bl 0x1274667c");
    test_disasm(0xf002f000, "bl 0x1274767c");
    test_disasm(0xf004f000, "bl 0x1274967c");
    test_disasm(0xf008f000, "bl 0x1274d67c");
    test_disasm(0xf010f000, "bl 0x1275567c");
    test_disasm(0xf020f000, "bl 0x1276567c");
    test_disasm(0xf040f000, "bl 0x1278567c");
    test_disasm(0xf080f000, "bl 0x127c567c");
    test_disasm(0xf100f000, "bl 0x1284567c");
    test_disasm(0xf200f000, "bl 0x1294567c");
    test_disasm(0xf400f000, "bl 0x11b4567c");

    test_disasm(0xf3808000, "msr APSR, r0");
    test_disasm(0xf3808001, "msr IAPSR, r0");
    test_disasm(0xf3808002, "msr EAPSR, r0");
    test_disasm(0xf3808003, "msr PSR, r0");
    test_disasm(0xf3808005, "msr IPSR, r0");
    test_disasm(0xf3808006, "msr EPSR, r0");
    test_disasm(0xf3808007, "msr IEPSR, r0");
    test_disasm(0xf3808008, "msr MSP, r0");
    test_disasm(0xf3808009, "msr PSP, r0");
    test_disasm(0xf380800a, "msr MSPLIM, r0");
    test_disasm(0xf380800b, "msr PSPLIM, r0");
    test_disasm(0xf3808010, "msr PRIMASK, r0");
    test_disasm(0xf3808011, "msr BASEPRI, r0");
    test_disasm(0xf3808012, "msr BASEPRI_MAX, r0");
    test_disasm(0xf3808013, "msr FAULTMASK, r0");
    test_disasm(0xf3808014, "msr CONTROL, r0");
    test_disasm(0xf3808088, "msr MSP_NS, r0");
    test_disasm(0xf3808089, "msr PSP_NS, r0");
    test_disasm(0xf380808a, "msr MSPLIM_NS, r0");
    test_disasm(0xf380808b, "msr PSPLIM_NS, r0");
    test_disasm(0xf3808090, "msr PRIMASK_NS, r0");
    test_disasm(0xf3808091, "msr BASEPRI_NS, r0");
    test_disasm(0xf3808093, "msr FAULTMASK_NS, r0");
    test_disasm(0xf3808094, "msr CONTROL_NS, r0");
    test_disasm(0xf3808098, "msr SP_NS, r0");
    test_disasm(0xf3818000, "msr APSR, r1");
    test_disasm(0xf3828000, "msr APSR, r2");
    test_disasm(0xf3838000, "msr APSR, r3");
    test_disasm(0xf3848000, "msr APSR, r4");
    test_disasm(0xf3858000, "msr APSR, r5");
    test_disasm(0xf3868000, "msr APSR, r6");
    test_disasm(0xf3878000, "msr APSR, r7");
    test_disasm(0xf3888000, "msr APSR, r8");
    test_disasm(0xf3898000, "msr APSR, r9");
    test_disasm(0xf38a8000, "msr APSR, sl");
    test_disasm(0xf38b8000, "msr APSR, fp");
    test_disasm(0xf38c8000, "msr APSR, ip");
    test_disasm(0xf38e8000, "msr APSR, lr");

    test_disasm(0xf3ef8000, "mrs r0, APSR");
    test_disasm(0xf3ef8001, "mrs r0, IAPSR");
    test_disasm(0xf3ef8002, "mrs r0, EAPSR");
    test_disasm(0xf3ef8003, "mrs r0, PSR");
    test_disasm(0xf3ef8005, "mrs r0, IPSR");
    test_disasm(0xf3ef8006, "mrs r0, EPSR");
    test_disasm(0xf3ef8007, "mrs r0, IEPSR");
    test_disasm(0xf3ef8008, "mrs r0, MSP");
    test_disasm(0xf3ef8009, "mrs r0, PSP");
    test_disasm(0xf3ef800a, "mrs r0, MSPLIM");
    test_disasm(0xf3ef800b, "mrs r0, PSPLIM");
    test_disasm(0xf3ef8010, "mrs r0, PRIMASK");
    test_disasm(0xf3ef8011, "mrs r0, BASEPRI");
    test_disasm(0xf3ef8012, "mrs r0, BASEPRI_MAX");
    test_disasm(0xf3ef8013, "mrs r0, FAULTMASK");
    test_disasm(0xf3ef8014, "mrs r0, CONTROL");
    test_disasm(0xf3ef8088, "mrs r0, MSP_NS");
    test_disasm(0xf3ef8089, "mrs r0, PSP_NS");
    test_disasm(0xf3ef808a, "mrs r0, MSPLIM_NS");
    test_disasm(0xf3ef808b, "mrs r0, PSPLIM_NS");
    test_disasm(0xf3ef8090, "mrs r0, PRIMASK_NS");
    test_disasm(0xf3ef8091, "mrs r0, BASEPRI_NS");
    test_disasm(0xf3ef8093, "mrs r0, FAULTMASK_NS");
    test_disasm(0xf3ef8094, "mrs r0, CONTROL_NS");
    test_disasm(0xf3ef8098, "mrs r0, SP_NS");
    test_disasm(0xf3ef8100, "mrs r1, APSR");
    test_disasm(0xf3ef8200, "mrs r2, APSR");
    test_disasm(0xf3ef8300, "mrs r3, APSR");
    test_disasm(0xf3ef8400, "mrs r4, APSR");
    test_disasm(0xf3ef8500, "mrs r5, APSR");
    test_disasm(0xf3ef8600, "mrs r6, APSR");
    test_disasm(0xf3ef8700, "mrs r7, APSR");
    test_disasm(0xf3ef8800, "mrs r8, APSR");
    test_disasm(0xf3ef8900, "mrs r9, APSR");
    test_disasm(0xf3ef8a00, "mrs sl, APSR");
    test_disasm(0xf3ef8b00, "mrs fp, APSR");
    test_disasm(0xf3ef8c00, "mrs ip, APSR");
    test_disasm(0xf3ef8e00, "mrs lr, APSR");

    test_disasm(0xf3bf8f40, "dsb");         // ssbb
    test_disasm(0xf3bf8f41, "dsb #1");
    test_disasm(0xf3bf8f42, "dsb #2");      // dsb oshst
    test_disasm(0xf3bf8f43, "dsb #3");      // dsb osh
    test_disasm(0xf3bf8f44, "dsb #4");
    test_disasm(0xf3bf8f45, "dsb #5");
    test_disasm(0xf3bf8f46, "dsb #6");      // dsb unst
    test_disasm(0xf3bf8f47, "dsb #7");      // dsb un
    test_disasm(0xf3bf8f48, "dsb #8");
    test_disasm(0xf3bf8f49, "dsb #9");
    test_disasm(0xf3bf8f4a, "dsb #10");     // dsb ishst
    test_disasm(0xf3bf8f4b, "dsb #11");     // dsb ish
    test_disasm(0xf3bf8f4c, "dsb #12");
    test_disasm(0xf3bf8f4d, "dsb #13");
    test_disasm(0xf3bf8f4e, "dsb #14");     // dsb st
    test_disasm(0xf3bf8f4f, "dsb #15");     // dsb sy

    test_disasm(0xf3bf8f50, "dmb");
    test_disasm(0xf3bf8f51, "dmb #1");
    test_disasm(0xf3bf8f52, "dmb #2");      // dmb oshst
    test_disasm(0xf3bf8f53, "dmb #3");      // dmb osh
    test_disasm(0xf3bf8f54, "dmb #4");
    test_disasm(0xf3bf8f55, "dmb #5");
    test_disasm(0xf3bf8f56, "dmb #6");      // dmb unst
    test_disasm(0xf3bf8f57, "dmb #7");      // dmb un
    test_disasm(0xf3bf8f58, "dmb #8");
    test_disasm(0xf3bf8f59, "dmb #9");
    test_disasm(0xf3bf8f5a, "dmb #10");     // dmb ishst
    test_disasm(0xf3bf8f5b, "dmb #11");     // dmb ish
    test_disasm(0xf3bf8f5c, "dmb #12");
    test_disasm(0xf3bf8f5d, "dmb #13");
    test_disasm(0xf3bf8f5e, "dmb #14");     // dmb st
    test_disasm(0xf3bf8f5f, "dmb #15");     // dmb sy

    test_disasm(0xf3bf8f60, "isb");
    test_disasm(0xf3bf8f61, "isb #1");
    test_disasm(0xf3bf8f62, "isb #2");
    test_disasm(0xf3bf8f63, "isb #3");
    test_disasm(0xf3bf8f64, "isb #4");
    test_disasm(0xf3bf8f65, "isb #5");
    test_disasm(0xf3bf8f66, "isb #6");
    test_disasm(0xf3bf8f67, "isb #7");
    test_disasm(0xf3bf8f68, "isb #8");
    test_disasm(0xf3bf8f69, "isb #9");
    test_disasm(0xf3bf8f6a, "isb #10");
    test_disasm(0xf3bf8f6b, "isb #11");
    test_disasm(0xf3bf8f6c, "isb #12");
    test_disasm(0xf3bf8f6d, "isb #13");
    test_disasm(0xf3bf8f6e, "isb #14");
    test_disasm(0xf3bf8f6f, "isb #15");     // isb sy
}

TEST(disasm, opcode16)
{
    test_disasm(0x0000, "movs r0, r0");
    test_disasm(0x0001, "movs r1, r0");
    test_disasm(0x0007, "movs r7, r0");
    test_disasm(0x0008, "movs r0, r1");
    test_disasm(0x0009, "movs r1, r1");
    test_disasm(0x000f, "movs r7, r1");
    test_disasm(0x0038, "movs r0, r7");
    test_disasm(0x0039, "movs r1, r7");
    test_disasm(0x003f, "movs r7, r7");

    test_disasm(0x0040, "lsls r0, r0, #1");
    test_disasm(0x0041, "lsls r1, r0, #1");
    test_disasm(0x0047, "lsls r7, r0, #1");
    test_disasm(0x0048, "lsls r0, r1, #1");
    test_disasm(0x0049, "lsls r1, r1, #1");
    test_disasm(0x004f, "lsls r7, r1, #1");
    test_disasm(0x0078, "lsls r0, r7, #1");
    test_disasm(0x0079, "lsls r1, r7, #1");
    test_disasm(0x007f, "lsls r7, r7, #1");
    test_disasm(0x07c0, "lsls r0, r0, #31");
    test_disasm(0x07c1, "lsls r1, r0, #31");
    test_disasm(0x07c7, "lsls r7, r0, #31");
    test_disasm(0x07c8, "lsls r0, r1, #31");
    test_disasm(0x07c9, "lsls r1, r1, #31");
    test_disasm(0x07cf, "lsls r7, r1, #31");
    test_disasm(0x07f8, "lsls r0, r7, #31");
    test_disasm(0x07f9, "lsls r1, r7, #31");
    test_disasm(0x07ff, "lsls r7, r7, #31");

    test_disasm(0x0800, "lsrs r0, r0, #32");
    test_disasm(0x0801, "lsrs r1, r0, #32");
    test_disasm(0x0807, "lsrs r7, r0, #32");
    test_disasm(0x0808, "lsrs r0, r1, #32");
    test_disasm(0x0809, "lsrs r1, r1, #32");
    test_disasm(0x080f, "lsrs r7, r1, #32");
    test_disasm(0x0838, "lsrs r0, r7, #32");
    test_disasm(0x0839, "lsrs r1, r7, #32");
    test_disasm(0x083f, "lsrs r7, r7, #32");
    test_disasm(0x0840, "lsrs r0, r0, #1");
    test_disasm(0x0841, "lsrs r1, r0, #1");
    test_disasm(0x0847, "lsrs r7, r0, #1");
    test_disasm(0x0848, "lsrs r0, r1, #1");
    test_disasm(0x0849, "lsrs r1, r1, #1");
    test_disasm(0x084f, "lsrs r7, r1, #1");
    test_disasm(0x0878, "lsrs r0, r7, #1");
    test_disasm(0x0879, "lsrs r1, r7, #1");
    test_disasm(0x087f, "lsrs r7, r7, #1");
    test_disasm(0x0fc0, "lsrs r0, r0, #31");
    test_disasm(0x0fc1, "lsrs r1, r0, #31");
    test_disasm(0x0fc7, "lsrs r7, r0, #31");
    test_disasm(0x0fc8, "lsrs r0, r1, #31");
    test_disasm(0x0fc9, "lsrs r1, r1, #31");
    test_disasm(0x0fcf, "lsrs r7, r1, #31");
    test_disasm(0x0ff8, "lsrs r0, r7, #31");
    test_disasm(0x0ff9, "lsrs r1, r7, #31");
    test_disasm(0x0fff, "lsrs r7, r7, #31");

    test_disasm(0x1000, "asrs r0, r0, #32");
    test_disasm(0x1001, "asrs r1, r0, #32");
    test_disasm(0x1007, "asrs r7, r0, #32");
    test_disasm(0x1008, "asrs r0, r1, #32");
    test_disasm(0x1009, "asrs r1, r1, #32");
    test_disasm(0x100f, "asrs r7, r1, #32");
    test_disasm(0x1038, "asrs r0, r7, #32");
    test_disasm(0x1039, "asrs r1, r7, #32");
    test_disasm(0x103f, "asrs r7, r7, #32");
    test_disasm(0x1040, "asrs r0, r0, #1");
    test_disasm(0x1041, "asrs r1, r0, #1");
    test_disasm(0x1047, "asrs r7, r0, #1");
    test_disasm(0x1048, "asrs r0, r1, #1");
    test_disasm(0x1049, "asrs r1, r1, #1");
    test_disasm(0x104f, "asrs r7, r1, #1");
    test_disasm(0x1078, "asrs r0, r7, #1");
    test_disasm(0x1079, "asrs r1, r7, #1");
    test_disasm(0x107f, "asrs r7, r7, #1");
    test_disasm(0x17c0, "asrs r0, r0, #31");
    test_disasm(0x17c1, "asrs r1, r0, #31");
    test_disasm(0x17c7, "asrs r7, r0, #31");
    test_disasm(0x17c8, "asrs r0, r1, #31");
    test_disasm(0x17c9, "asrs r1, r1, #31");
    test_disasm(0x17cf, "asrs r7, r1, #31");
    test_disasm(0x17f8, "asrs r0, r7, #31");
    test_disasm(0x17f9, "asrs r1, r7, #31");
    test_disasm(0x17ff, "asrs r7, r7, #31");

    test_disasm(0x1800, "adds r0, r0, r0");
    test_disasm(0x1801, "adds r1, r0, r0");
    test_disasm(0x1807, "adds r7, r0, r0");
    test_disasm(0x1808, "adds r0, r1, r0");
    test_disasm(0x1809, "adds r1, r1, r0");
    test_disasm(0x180f, "adds r7, r1, r0");
    test_disasm(0x1838, "adds r0, r7, r0");
    test_disasm(0x1839, "adds r1, r7, r0");
    test_disasm(0x183f, "adds r7, r7, r0");
    test_disasm(0x1840, "adds r0, r0, r1");
    test_disasm(0x1841, "adds r1, r0, r1");
    test_disasm(0x1847, "adds r7, r0, r1");
    test_disasm(0x1848, "adds r0, r1, r1");
    test_disasm(0x1849, "adds r1, r1, r1");
    test_disasm(0x184f, "adds r7, r1, r1");
    test_disasm(0x1878, "adds r0, r7, r1");
    test_disasm(0x1879, "adds r1, r7, r1");
    test_disasm(0x187f, "adds r7, r7, r1");
    test_disasm(0x19c0, "adds r0, r0, r7");
    test_disasm(0x19c1, "adds r1, r0, r7");
    test_disasm(0x19c7, "adds r7, r0, r7");
    test_disasm(0x19c8, "adds r0, r1, r7");
    test_disasm(0x19c9, "adds r1, r1, r7");
    test_disasm(0x19cf, "adds r7, r1, r7");
    test_disasm(0x19f8, "adds r0, r7, r7");
    test_disasm(0x19f9, "adds r1, r7, r7");
    test_disasm(0x19ff, "adds r7, r7, r7");

    test_disasm(0x1a00, "subs r0, r0, r0");
    test_disasm(0x1a01, "subs r1, r0, r0");
    test_disasm(0x1a07, "subs r7, r0, r0");
    test_disasm(0x1a08, "subs r0, r1, r0");
    test_disasm(0x1a09, "subs r1, r1, r0");
    test_disasm(0x1a0f, "subs r7, r1, r0");
    test_disasm(0x1a38, "subs r0, r7, r0");
    test_disasm(0x1a39, "subs r1, r7, r0");
    test_disasm(0x1a3f, "subs r7, r7, r0");
    test_disasm(0x1a40, "subs r0, r0, r1");
    test_disasm(0x1a41, "subs r1, r0, r1");
    test_disasm(0x1a47, "subs r7, r0, r1");
    test_disasm(0x1a48, "subs r0, r1, r1");
    test_disasm(0x1a49, "subs r1, r1, r1");
    test_disasm(0x1a4f, "subs r7, r1, r1");
    test_disasm(0x1a78, "subs r0, r7, r1");
    test_disasm(0x1a79, "subs r1, r7, r1");
    test_disasm(0x1a7f, "subs r7, r7, r1");
    test_disasm(0x1bc0, "subs r0, r0, r7");
    test_disasm(0x1bc1, "subs r1, r0, r7");
    test_disasm(0x1bc7, "subs r7, r0, r7");
    test_disasm(0x1bc8, "subs r0, r1, r7");
    test_disasm(0x1bc9, "subs r1, r1, r7");
    test_disasm(0x1bcf, "subs r7, r1, r7");
    test_disasm(0x1bf8, "subs r0, r7, r7");
    test_disasm(0x1bf9, "subs r1, r7, r7");
    test_disasm(0x1bff, "subs r7, r7, r7");

    test_disasm(0x1c00, "adds r0, r0, #0");
    test_disasm(0x1c01, "adds r1, r0, #0");
    test_disasm(0x1c07, "adds r7, r0, #0");
    test_disasm(0x1c08, "adds r0, r1, #0");
    test_disasm(0x1c09, "adds r1, r1, #0");
    test_disasm(0x1c0f, "adds r7, r1, #0");
    test_disasm(0x1c38, "adds r0, r7, #0");
    test_disasm(0x1c39, "adds r1, r7, #0");
    test_disasm(0x1c3f, "adds r7, r7, #0");
    test_disasm(0x1c40, "adds r0, r0, #1");
    test_disasm(0x1c41, "adds r1, r0, #1");
    test_disasm(0x1c47, "adds r7, r0, #1");
    test_disasm(0x1c48, "adds r0, r1, #1");
    test_disasm(0x1c49, "adds r1, r1, #1");
    test_disasm(0x1c4f, "adds r7, r1, #1");
    test_disasm(0x1c78, "adds r0, r7, #1");
    test_disasm(0x1c79, "adds r1, r7, #1");
    test_disasm(0x1c7f, "adds r7, r7, #1");
    test_disasm(0x1dc0, "adds r0, r0, #7");
    test_disasm(0x1dc1, "adds r1, r0, #7");
    test_disasm(0x1dc7, "adds r7, r0, #7");
    test_disasm(0x1dc8, "adds r0, r1, #7");
    test_disasm(0x1dc9, "adds r1, r1, #7");
    test_disasm(0x1dcf, "adds r7, r1, #7");
    test_disasm(0x1df8, "adds r0, r7, #7");
    test_disasm(0x1df9, "adds r1, r7, #7");
    test_disasm(0x1dff, "adds r7, r7, #7");

    test_disasm(0x1e00, "subs r0, r0, #0");
    test_disasm(0x1e01, "subs r1, r0, #0");
    test_disasm(0x1e07, "subs r7, r0, #0");
    test_disasm(0x1e08, "subs r0, r1, #0");
    test_disasm(0x1e09, "subs r1, r1, #0");
    test_disasm(0x1e0f, "subs r7, r1, #0");
    test_disasm(0x1e38, "subs r0, r7, #0");
    test_disasm(0x1e39, "subs r1, r7, #0");
    test_disasm(0x1e3f, "subs r7, r7, #0");
    test_disasm(0x1e40, "subs r0, r0, #1");
    test_disasm(0x1e41, "subs r1, r0, #1");
    test_disasm(0x1e47, "subs r7, r0, #1");
    test_disasm(0x1e48, "subs r0, r1, #1");
    test_disasm(0x1e49, "subs r1, r1, #1");
    test_disasm(0x1e4f, "subs r7, r1, #1");
    test_disasm(0x1e78, "subs r0, r7, #1");
    test_disasm(0x1e79, "subs r1, r7, #1");
    test_disasm(0x1e7f, "subs r7, r7, #1");
    test_disasm(0x1fc0, "subs r0, r0, #7");
    test_disasm(0x1fc1, "subs r1, r0, #7");
    test_disasm(0x1fc7, "subs r7, r0, #7");
    test_disasm(0x1fc8, "subs r0, r1, #7");
    test_disasm(0x1fc9, "subs r1, r1, #7");
    test_disasm(0x1fcf, "subs r7, r1, #7");
    test_disasm(0x1ff8, "subs r0, r7, #7");
    test_disasm(0x1ff9, "subs r1, r7, #7");
    test_disasm(0x1fff, "subs r7, r7, #7");

    test_disasm(0x2000, "movs r0, #0");
    test_disasm(0x2001, "movs r0, #1");
    test_disasm(0x20ff, "movs r0, #255");
    test_disasm(0x2100, "movs r1, #0");
    test_disasm(0x2101, "movs r1, #1");
    test_disasm(0x21ff, "movs r1, #255");
    test_disasm(0x2700, "movs r7, #0");
    test_disasm(0x2701, "movs r7, #1");
    test_disasm(0x27ff, "movs r7, #255");

    test_disasm(0x2800, "cmp r0, #0");
    test_disasm(0x2801, "cmp r0, #1");
    test_disasm(0x28ff, "cmp r0, #255");
    test_disasm(0x2900, "cmp r1, #0");
    test_disasm(0x2901, "cmp r1, #1");
    test_disasm(0x29ff, "cmp r1, #255");
    test_disasm(0x2f00, "cmp r7, #0");
    test_disasm(0x2f01, "cmp r7, #1");
    test_disasm(0x2fff, "cmp r7, #255");

    test_disasm(0x3000, "adds r0, #0");
    test_disasm(0x3001, "adds r0, #1");
    test_disasm(0x30ff, "adds r0, #255");
    test_disasm(0x3100, "adds r1, #0");
    test_disasm(0x3101, "adds r1, #1");
    test_disasm(0x31ff, "adds r1, #255");
    test_disasm(0x3700, "adds r7, #0");
    test_disasm(0x3701, "adds r7, #1");
    test_disasm(0x37ff, "adds r7, #255");

    test_disasm(0x3800, "subs r0, #0");
    test_disasm(0x3801, "subs r0, #1");
    test_disasm(0x38ff, "subs r0, #255");
    test_disasm(0x3900, "subs r1, #0");
    test_disasm(0x3901, "subs r1, #1");
    test_disasm(0x39ff, "subs r1, #255");
    test_disasm(0x3f00, "subs r7, #0");
    test_disasm(0x3f01, "subs r7, #1");
    test_disasm(0x3fff, "subs r7, #255");

    test_disasm(0x4000, "ands r0, r0");
    test_disasm(0x4001, "ands r1, r0");
    test_disasm(0x4007, "ands r7, r0");
    test_disasm(0x4008, "ands r0, r1");
    test_disasm(0x4009, "ands r1, r1");
    test_disasm(0x400f, "ands r7, r1");
    test_disasm(0x4038, "ands r0, r7");
    test_disasm(0x4039, "ands r1, r7");
    test_disasm(0x403f, "ands r7, r7");

    test_disasm(0x4040, "eors r0, r0");
    test_disasm(0x4041, "eors r1, r0");
    test_disasm(0x4047, "eors r7, r0");
    test_disasm(0x4048, "eors r0, r1");
    test_disasm(0x4049, "eors r1, r1");
    test_disasm(0x404f, "eors r7, r1");
    test_disasm(0x4078, "eors r0, r7");
    test_disasm(0x4079, "eors r1, r7");
    test_disasm(0x407f, "eors r7, r7");

    test_disasm(0x4080, "lsls r0, r0");
    test_disasm(0x4081, "lsls r1, r0");
    test_disasm(0x4087, "lsls r7, r0");
    test_disasm(0x4088, "lsls r0, r1");
    test_disasm(0x4089, "lsls r1, r1");
    test_disasm(0x408f, "lsls r7, r1");
    test_disasm(0x40b8, "lsls r0, r7");
    test_disasm(0x40b9, "lsls r1, r7");
    test_disasm(0x40bf, "lsls r7, r7");

    test_disasm(0x40c0, "lsrs r0, r0");
    test_disasm(0x40c1, "lsrs r1, r0");
    test_disasm(0x40c7, "lsrs r7, r0");
    test_disasm(0x40c8, "lsrs r0, r1");
    test_disasm(0x40c9, "lsrs r1, r1");
    test_disasm(0x40cf, "lsrs r7, r1");
    test_disasm(0x40f8, "lsrs r0, r7");
    test_disasm(0x40f9, "lsrs r1, r7");
    test_disasm(0x40ff, "lsrs r7, r7");

    test_disasm(0x4100, "asrs r0, r0");
    test_disasm(0x4101, "asrs r1, r0");
    test_disasm(0x4107, "asrs r7, r0");
    test_disasm(0x4108, "asrs r0, r1");
    test_disasm(0x4109, "asrs r1, r1");
    test_disasm(0x410f, "asrs r7, r1");
    test_disasm(0x4138, "asrs r0, r7");
    test_disasm(0x4139, "asrs r1, r7");
    test_disasm(0x413f, "asrs r7, r7");

    test_disasm(0x4140, "adcs r0, r0");
    test_disasm(0x4141, "adcs r1, r0");
    test_disasm(0x4147, "adcs r7, r0");
    test_disasm(0x4148, "adcs r0, r1");
    test_disasm(0x4149, "adcs r1, r1");
    test_disasm(0x414f, "adcs r7, r1");
    test_disasm(0x4178, "adcs r0, r7");
    test_disasm(0x4179, "adcs r1, r7");
    test_disasm(0x417f, "adcs r7, r7");

    test_disasm(0x4180, "sbcs r0, r0");
    test_disasm(0x4181, "sbcs r1, r0");
    test_disasm(0x4187, "sbcs r7, r0");
    test_disasm(0x4188, "sbcs r0, r1");
    test_disasm(0x4189, "sbcs r1, r1");
    test_disasm(0x418f, "sbcs r7, r1");
    test_disasm(0x41b8, "sbcs r0, r7");
    test_disasm(0x41b9, "sbcs r1, r7");
    test_disasm(0x41bf, "sbcs r7, r7");

    test_disasm(0x41c0, "rors r0, r0");
    test_disasm(0x41c1, "rors r1, r0");
    test_disasm(0x41c7, "rors r7, r0");
    test_disasm(0x41c8, "rors r0, r1");
    test_disasm(0x41c9, "rors r1, r1");
    test_disasm(0x41cf, "rors r7, r1");
    test_disasm(0x41f8, "rors r0, r7");
    test_disasm(0x41f9, "rors r1, r7");
    test_disasm(0x41ff, "rors r7, r7");

    test_disasm(0x4200, "tst r0, r0");
    test_disasm(0x4201, "tst r1, r0");
    test_disasm(0x4207, "tst r7, r0");
    test_disasm(0x4208, "tst r0, r1");
    test_disasm(0x4209, "tst r1, r1");
    test_disasm(0x420f, "tst r7, r1");
    test_disasm(0x4238, "tst r0, r7");
    test_disasm(0x4239, "tst r1, r7");
    test_disasm(0x423f, "tst r7, r7");

    test_disasm(0x4240, "negs r0, r0");
    test_disasm(0x4241, "negs r1, r0");
    test_disasm(0x4247, "negs r7, r0");
    test_disasm(0x4248, "negs r0, r1");
    test_disasm(0x4249, "negs r1, r1");
    test_disasm(0x424f, "negs r7, r1");
    test_disasm(0x4278, "negs r0, r7");
    test_disasm(0x4279, "negs r1, r7");
    test_disasm(0x427f, "negs r7, r7");

    test_disasm(0x4280, "cmp r0, r0");
    test_disasm(0x4281, "cmp r1, r0");
    test_disasm(0x4287, "cmp r7, r0");
    test_disasm(0x4288, "cmp r0, r1");
    test_disasm(0x4289, "cmp r1, r1");
    test_disasm(0x428f, "cmp r7, r1");
    test_disasm(0x42b8, "cmp r0, r7");
    test_disasm(0x42b9, "cmp r1, r7");
    test_disasm(0x42bf, "cmp r7, r7");

    test_disasm(0x42c0, "cmn r0, r0");
    test_disasm(0x42c1, "cmn r1, r0");
    test_disasm(0x42c7, "cmn r7, r0");
    test_disasm(0x42c8, "cmn r0, r1");
    test_disasm(0x42c9, "cmn r1, r1");
    test_disasm(0x42cf, "cmn r7, r1");
    test_disasm(0x42f8, "cmn r0, r7");
    test_disasm(0x42f9, "cmn r1, r7");
    test_disasm(0x42ff, "cmn r7, r7");

    test_disasm(0x4300, "orrs r0, r0");
    test_disasm(0x4301, "orrs r1, r0");
    test_disasm(0x4307, "orrs r7, r0");
    test_disasm(0x4308, "orrs r0, r1");
    test_disasm(0x4309, "orrs r1, r1");
    test_disasm(0x430f, "orrs r7, r1");
    test_disasm(0x4338, "orrs r0, r7");
    test_disasm(0x4339, "orrs r1, r7");
    test_disasm(0x433f, "orrs r7, r7");

    test_disasm(0x4340, "muls r0, r0");
    test_disasm(0x4341, "muls r1, r0");
    test_disasm(0x4347, "muls r7, r0");
    test_disasm(0x4348, "muls r0, r1");
    test_disasm(0x4349, "muls r1, r1");
    test_disasm(0x434f, "muls r7, r1");
    test_disasm(0x4378, "muls r0, r7");
    test_disasm(0x4379, "muls r1, r7");
    test_disasm(0x437f, "muls r7, r7");

    test_disasm(0x4380, "bics r0, r0");
    test_disasm(0x4381, "bics r1, r0");
    test_disasm(0x4387, "bics r7, r0");
    test_disasm(0x4388, "bics r0, r1");
    test_disasm(0x4389, "bics r1, r1");
    test_disasm(0x438f, "bics r7, r1");
    test_disasm(0x43b8, "bics r0, r7");
    test_disasm(0x43b9, "bics r1, r7");
    test_disasm(0x43bf, "bics r7, r7");

    test_disasm(0x43c0, "mvns r0, r0");
    test_disasm(0x43c1, "mvns r1, r0");
    test_disasm(0x43c7, "mvns r7, r0");
    test_disasm(0x43c8, "mvns r0, r1");
    test_disasm(0x43c9, "mvns r1, r1");
    test_disasm(0x43cf, "mvns r7, r1");
    test_disasm(0x43f8, "mvns r0, r7");
    test_disasm(0x43f9, "mvns r1, r7");
    test_disasm(0x43ff, "mvns r7, r7");

#if 0
add r0, r0                   // 4400 add r0, r0
add r1, r0                   // 4401 add r1, r0
add r2, r0                   // 4402 add r2, r0
add r3, r0                   // 4403 add r3, r0
add r4, r0                   // 4404 add r4, r0
add r5, r0                   // 4405 add r5, r0
add r6, r0                   // 4406 add r6, r0
add r7, r0                   // 4407 add r7, r0
add r0, r1                   // 4408 add r0, r1
add r1, r1                   // 4409 add r1, r1
add r2, r1                   // 440a add r2, r1
add r3, r1                   // 440b add r3, r1
add r4, r1                   // 440c add r4, r1
add r5, r1                   // 440d add r5, r1
add r6, r1                   // 440e add r6, r1
add r7, r1                   // 440f add r7, r1
add r0, r2                   // 4410 add r0, r2
add r1, r2                   // 4411 add r1, r2
add r2, r2                   // 4412 add r2, r2
add r3, r2                   // 4413 add r3, r2
add r4, r2                   // 4414 add r4, r2
add r5, r2                   // 4415 add r5, r2
add r6, r2                   // 4416 add r6, r2
add r7, r2                   // 4417 add r7, r2
add r0, r3                   // 4418 add r0, r3
add r1, r3                   // 4419 add r1, r3
add r2, r3                   // 441a add r2, r3
add r3, r3                   // 441b add r3, r3
add r4, r3                   // 441c add r4, r3
add r5, r3                   // 441d add r5, r3
add r6, r3                   // 441e add r6, r3
add r7, r3                   // 441f add r7, r3
add r0, r4                   // 4420 add r0, r4
add r1, r4                   // 4421 add r1, r4
add r2, r4                   // 4422 add r2, r4
add r3, r4                   // 4423 add r3, r4
add r4, r4                   // 4424 add r4, r4
add r5, r4                   // 4425 add r5, r4
add r6, r4                   // 4426 add r6, r4
add r7, r4                   // 4427 add r7, r4
add r0, r5                   // 4428 add r0, r5
add r1, r5                   // 4429 add r1, r5
add r2, r5                   // 442a add r2, r5
add r3, r5                   // 442b add r3, r5
add r4, r5                   // 442c add r4, r5
add r5, r5                   // 442d add r5, r5
add r6, r5                   // 442e add r6, r5
add r7, r5                   // 442f add r7, r5
add r0, r6                   // 4430 add r0, r6
add r1, r6                   // 4431 add r1, r6
add r2, r6                   // 4432 add r2, r6
add r3, r6                   // 4433 add r3, r6
add r4, r6                   // 4434 add r4, r6
add r5, r6                   // 4435 add r5, r6
add r6, r6                   // 4436 add r6, r6
add r7, r6                   // 4437 add r7, r6
add r0, r7                   // 4438 add r0, r7
add r1, r7                   // 4439 add r1, r7
add r2, r7                   // 443a add r2, r7
add r3, r7                   // 443b add r3, r7
add r4, r7                   // 443c add r4, r7
add r5, r7                   // 443d add r5, r7
add r6, r7                   // 443e add r6, r7
add r7, r7                   // 443f add r7, r7
add r0, r8                   // 4440 add r0, r8
add r1, r8                   // 4441 add r1, r8
add r2, r8                   // 4442 add r2, r8
add r3, r8                   // 4443 add r3, r8
add r4, r8                   // 4444 add r4, r8
add r5, r8                   // 4445 add r5, r8
add r6, r8                   // 4446 add r6, r8
add r7, r8                   // 4447 add r7, r8
add r0, r9                   // 4448 add r0, r9
add r1, r9                   // 4449 add r1, r9
add r2, r9                   // 444a add r2, r9
add r3, r9                   // 444b add r3, r9
add r4, r9                   // 444c add r4, r9
add r5, r9                   // 444d add r5, r9
add r6, r9                   // 444e add r6, r9
add r7, r9                   // 444f add r7, r9
add r0, sl                   // 4450 add r0, sl
add r1, sl                   // 4451 add r1, sl
add r2, sl                   // 4452 add r2, sl
add r3, sl                   // 4453 add r3, sl
add r4, sl                   // 4454 add r4, sl
add r5, sl                   // 4455 add r5, sl
add r6, sl                   // 4456 add r6, sl
add r7, sl                   // 4457 add r7, sl
add r0, fp                   // 4458 add r0, fp
add r1, fp                   // 4459 add r1, fp
add r2, fp                   // 445a add r2, fp
add r3, fp                   // 445b add r3, fp
add r4, fp                   // 445c add r4, fp
add r5, fp                   // 445d add r5, fp
add r6, fp                   // 445e add r6, fp
add r7, fp                   // 445f add r7, fp
add r0, ip                   // 4460 add r0, ip
add r1, ip                   // 4461 add r1, ip
add r2, ip                   // 4462 add r2, ip
add r3, ip                   // 4463 add r3, ip
add r4, ip                   // 4464 add r4, ip
add r5, ip                   // 4465 add r5, ip
add r6, ip                   // 4466 add r6, ip
add r7, ip                   // 4467 add r7, ip
add r0, sp                   // 4468 add r0, sp
add r1, sp                   // 4469 add r1, sp
add r2, sp                   // 446a add r2, sp
add r3, sp                   // 446b add r3, sp
add r4, sp                   // 446c add r4, sp
add r5, sp                   // 446d add r5, sp
add r6, sp                   // 446e add r6, sp
add r7, sp                   // 446f add r7, sp
add r0, lr                   // 4470 add r0, lr
add r1, lr                   // 4471 add r1, lr
add r2, lr                   // 4472 add r2, lr
add r3, lr                   // 4473 add r3, lr
add r4, lr                   // 4474 add r4, lr
add r5, lr                   // 4475 add r5, lr
add r6, lr                   // 4476 add r6, lr
add r7, lr                   // 4477 add r7, lr
add r0, pc                   // 4478 add r0, pc
add r1, pc                   // 4479 add r1, pc
add r2, pc                   // 447a add r2, pc
add r3, pc                   // 447b add r3, pc
add r4, pc                   // 447c add r4, pc
add r5, pc                   // 447d add r5, pc
add r6, pc                   // 447e add r6, pc
add r7, pc                   // 447f add r7, pc
add r8, r0                   // 4480 add r8, r0
add r9, r0                   // 4481 add r9, r0
add sl, r0                   // 4482 add sl, r0
add fp, r0                   // 4483 add fp, r0
add ip, r0                   // 4484 add ip, r0
add sp, r0                   // 4485 add sp, r0
add lr, r0                   // 4486 add lr, r0
add pc, r0                   // 4487 add pc, r0
add r8, r1                   // 4488 add r8, r1
add r9, r1                   // 4489 add r9, r1
add sl, r1                   // 448a add sl, r1
add fp, r1                   // 448b add fp, r1
add ip, r1                   // 448c add ip, r1
add sp, r1                   // 448d add sp, r1
add lr, r1                   // 448e add lr, r1
add pc, r1                   // 448f add pc, r1
add r8, r2                   // 4490 add r8, r2
add r9, r2                   // 4491 add r9, r2
add sl, r2                   // 4492 add sl, r2
add fp, r2                   // 4493 add fp, r2
add ip, r2                   // 4494 add ip, r2
add sp, r2                   // 4495 add sp, r2
add lr, r2                   // 4496 add lr, r2
add pc, r2                   // 4497 add pc, r2
add r8, r3                   // 4498 add r8, r3
add r9, r3                   // 4499 add r9, r3
add sl, r3                   // 449a add sl, r3
add fp, r3                   // 449b add fp, r3
add ip, r3                   // 449c add ip, r3
add sp, r3                   // 449d add sp, r3
add lr, r3                   // 449e add lr, r3
add pc, r3                   // 449f add pc, r3
add r8, r4                   // 44a0 add r8, r4
add r9, r4                   // 44a1 add r9, r4
add sl, r4                   // 44a2 add sl, r4
add fp, r4                   // 44a3 add fp, r4
add ip, r4                   // 44a4 add ip, r4
add sp, r4                   // 44a5 add sp, r4
add lr, r4                   // 44a6 add lr, r4
add pc, r4                   // 44a7 add pc, r4
add r8, r5                   // 44a8 add r8, r5
add r9, r5                   // 44a9 add r9, r5
add sl, r5                   // 44aa add sl, r5
add fp, r5                   // 44ab add fp, r5
add ip, r5                   // 44ac add ip, r5
add sp, r5                   // 44ad add sp, r5
add lr, r5                   // 44ae add lr, r5
add pc, r5                   // 44af add pc, r5
add r8, r6                   // 44b0 add r8, r6
add r9, r6                   // 44b1 add r9, r6
add sl, r6                   // 44b2 add sl, r6
add fp, r6                   // 44b3 add fp, r6
add ip, r6                   // 44b4 add ip, r6
add sp, r6                   // 44b5 add sp, r6
add lr, r6                   // 44b6 add lr, r6
add pc, r6                   // 44b7 add pc, r6
add r8, r7                   // 44b8 add r8, r7
add r9, r7                   // 44b9 add r9, r7
add sl, r7                   // 44ba add sl, r7
add fp, r7                   // 44bb add fp, r7
add ip, r7                   // 44bc add ip, r7
add sp, r7                   // 44bd add sp, r7
add lr, r7                   // 44be add lr, r7
add pc, r7                   // 44bf add pc, r7
add r8, r8                   // 44c0 add r8, r8
add r9, r8                   // 44c1 add r9, r8
add sl, r8                   // 44c2 add sl, r8
add fp, r8                   // 44c3 add fp, r8
add ip, r8                   // 44c4 add ip, r8
add sp, r8                   // 44c5 add sp, r8
add lr, r8                   // 44c6 add lr, r8
add pc, r8                   // 44c7 add pc, r8
add r8, r9                   // 44c8 add r8, r9
add r9, r9                   // 44c9 add r9, r9
add sl, r9                   // 44ca add sl, r9
add fp, r9                   // 44cb add fp, r9
add ip, r9                   // 44cc add ip, r9
add sp, r9                   // 44cd add sp, r9
add lr, r9                   // 44ce add lr, r9
add pc, r9                   // 44cf add pc, r9
add r8, sl                   // 44d0 add r8, sl
add r9, sl                   // 44d1 add r9, sl
add sl, sl                   // 44d2 add sl, sl
add fp, sl                   // 44d3 add fp, sl
add ip, sl                   // 44d4 add ip, sl
add sp, sl                   // 44d5 add sp, sl
add lr, sl                   // 44d6 add lr, sl
add pc, sl                   // 44d7 add pc, sl
add r8, fp                   // 44d8 add r8, fp
add r9, fp                   // 44d9 add r9, fp
add sl, fp                   // 44da add sl, fp
add fp, fp                   // 44db add fp, fp
add ip, fp                   // 44dc add ip, fp
add sp, fp                   // 44dd add sp, fp
add lr, fp                   // 44de add lr, fp
add pc, fp                   // 44df add pc, fp
add r8, ip                   // 44e0 add r8, ip
add r9, ip                   // 44e1 add r9, ip
add sl, ip                   // 44e2 add sl, ip
add fp, ip                   // 44e3 add fp, ip
add ip, ip                   // 44e4 add ip, ip
add sp, ip                   // 44e5 add sp, ip
add lr, ip                   // 44e6 add lr, ip
add pc, ip                   // 44e7 add pc, ip
add r8, sp                   // 44e8 add r8, sp
add r9, sp                   // 44e9 add r9, sp
add sl, sp                   // 44ea add sl, sp
add fp, sp                   // 44eb add fp, sp
add ip, sp                   // 44ec add ip, sp
add sp, sp                   // 44ed add sp, sp
add lr, sp                   // 44ee add lr, sp
add pc, sp                   // 44ef add pc, sp
add r8, lr                   // 44f0 add r8, lr
add r9, lr                   // 44f1 add r9, lr
add sl, lr                   // 44f2 add sl, lr
add fp, lr                   // 44f3 add fp, lr
add ip, lr                   // 44f4 add ip, lr
add sp, lr                   // 44f5 add sp, lr
add lr, lr                   // 44f6 add lr, lr
add pc, lr                   // 44f7 add pc, lr
add r8, pc                   // 44f8 add r8, pc
add r9, pc                   // 44f9 add r9, pc
add sl, pc                   // 44fa add sl, pc
add fp, pc                   // 44fb add fp, pc
add ip, pc                   // 44fc add ip, pc
add sp, pc                   // 44fd add sp, pc
add lr, pc                   // 44fe add lr, pc
add pc, pc                   // 44ff add pc, pc

cmp r0, r0                   // 4500 cmp r0, r0
cmp r1, r0                   // 4501 cmp r1, r0
cmp r2, r0                   // 4502 cmp r2, r0
cmp r3, r0                   // 4503 cmp r3, r0
cmp r4, r0                   // 4504 cmp r4, r0
cmp r5, r0                   // 4505 cmp r5, r0
cmp r6, r0                   // 4506 cmp r6, r0
cmp r7, r0                   // 4507 cmp r7, r0
cmp r0, r1                   // 4508 cmp r0, r1
cmp r1, r1                   // 4509 cmp r1, r1
cmp r2, r1                   // 450a cmp r2, r1
cmp r3, r1                   // 450b cmp r3, r1
cmp r4, r1                   // 450c cmp r4, r1
cmp r5, r1                   // 450d cmp r5, r1
cmp r6, r1                   // 450e cmp r6, r1
cmp r7, r1                   // 450f cmp r7, r1
cmp r0, r2                   // 4510 cmp r0, r2
cmp r1, r2                   // 4511 cmp r1, r2
cmp r2, r2                   // 4512 cmp r2, r2
cmp r3, r2                   // 4513 cmp r3, r2
cmp r4, r2                   // 4514 cmp r4, r2
cmp r5, r2                   // 4515 cmp r5, r2
cmp r6, r2                   // 4516 cmp r6, r2
cmp r7, r2                   // 4517 cmp r7, r2
cmp r0, r3                   // 4518 cmp r0, r3
cmp r1, r3                   // 4519 cmp r1, r3
cmp r2, r3                   // 451a cmp r2, r3
cmp r3, r3                   // 451b cmp r3, r3
cmp r4, r3                   // 451c cmp r4, r3
cmp r5, r3                   // 451d cmp r5, r3
cmp r6, r3                   // 451e cmp r6, r3
cmp r7, r3                   // 451f cmp r7, r3
cmp r0, r4                   // 4520 cmp r0, r4
cmp r1, r4                   // 4521 cmp r1, r4
cmp r2, r4                   // 4522 cmp r2, r4
cmp r3, r4                   // 4523 cmp r3, r4
cmp r4, r4                   // 4524 cmp r4, r4
cmp r5, r4                   // 4525 cmp r5, r4
cmp r6, r4                   // 4526 cmp r6, r4
cmp r7, r4                   // 4527 cmp r7, r4
cmp r0, r5                   // 4528 cmp r0, r5
cmp r1, r5                   // 4529 cmp r1, r5
cmp r2, r5                   // 452a cmp r2, r5
cmp r3, r5                   // 452b cmp r3, r5
cmp r4, r5                   // 452c cmp r4, r5
cmp r5, r5                   // 452d cmp r5, r5
cmp r6, r5                   // 452e cmp r6, r5
cmp r7, r5                   // 452f cmp r7, r5
cmp r0, r6                   // 4530 cmp r0, r6
cmp r1, r6                   // 4531 cmp r1, r6
cmp r2, r6                   // 4532 cmp r2, r6
cmp r3, r6                   // 4533 cmp r3, r6
cmp r4, r6                   // 4534 cmp r4, r6
cmp r5, r6                   // 4535 cmp r5, r6
cmp r6, r6                   // 4536 cmp r6, r6
cmp r7, r6                   // 4537 cmp r7, r6
cmp r0, r7                   // 4538 cmp r0, r7
cmp r1, r7                   // 4539 cmp r1, r7
cmp r2, r7                   // 453a cmp r2, r7
cmp r3, r7                   // 453b cmp r3, r7
cmp r4, r7                   // 453c cmp r4, r7
cmp r5, r7                   // 453d cmp r5, r7
cmp r6, r7                   // 453e cmp r6, r7
cmp r7, r7                   // 453f cmp r7, r7
cmp r0, r8                   // 4540 cmp r0, r8
cmp r1, r8                   // 4541 cmp r1, r8
cmp r2, r8                   // 4542 cmp r2, r8
cmp r3, r8                   // 4543 cmp r3, r8
cmp r4, r8                   // 4544 cmp r4, r8
cmp r5, r8                   // 4545 cmp r5, r8
cmp r6, r8                   // 4546 cmp r6, r8
cmp r7, r8                   // 4547 cmp r7, r8
cmp r0, r9                   // 4548 cmp r0, r9
cmp r1, r9                   // 4549 cmp r1, r9
cmp r2, r9                   // 454a cmp r2, r9
cmp r3, r9                   // 454b cmp r3, r9
cmp r4, r9                   // 454c cmp r4, r9
cmp r5, r9                   // 454d cmp r5, r9
cmp r6, r9                   // 454e cmp r6, r9
cmp r7, r9                   // 454f cmp r7, r9
cmp r0, sl                   // 4550 cmp r0, sl
cmp r1, sl                   // 4551 cmp r1, sl
cmp r2, sl                   // 4552 cmp r2, sl
cmp r3, sl                   // 4553 cmp r3, sl
cmp r4, sl                   // 4554 cmp r4, sl
cmp r5, sl                   // 4555 cmp r5, sl
cmp r6, sl                   // 4556 cmp r6, sl
cmp r7, sl                   // 4557 cmp r7, sl
cmp r0, fp                   // 4558 cmp r0, fp
cmp r1, fp                   // 4559 cmp r1, fp
cmp r2, fp                   // 455a cmp r2, fp
cmp r3, fp                   // 455b cmp r3, fp
cmp r4, fp                   // 455c cmp r4, fp
cmp r5, fp                   // 455d cmp r5, fp
cmp r6, fp                   // 455e cmp r6, fp
cmp r7, fp                   // 455f cmp r7, fp
cmp r0, ip                   // 4560 cmp r0, ip
cmp r1, ip                   // 4561 cmp r1, ip
cmp r2, ip                   // 4562 cmp r2, ip
cmp r3, ip                   // 4563 cmp r3, ip
cmp r4, ip                   // 4564 cmp r4, ip
cmp r5, ip                   // 4565 cmp r5, ip
cmp r6, ip                   // 4566 cmp r6, ip
cmp r7, ip                   // 4567 cmp r7, ip
cmp r0, lr                   // 4570 cmp r0, lr
cmp r1, lr                   // 4571 cmp r1, lr
cmp r2, lr                   // 4572 cmp r2, lr
cmp r3, lr                   // 4573 cmp r3, lr
cmp r4, lr                   // 4574 cmp r4, lr
cmp r5, lr                   // 4575 cmp r5, lr
cmp r6, lr                   // 4576 cmp r6, lr
cmp r7, lr                   // 4577 cmp r7, lr
cmp r8, r0                   // 4580 cmp r8, r0
cmp r9, r0                   // 4581 cmp r9, r0
cmp sl, r0                   // 4582 cmp sl, r0
cmp fp, r0                   // 4583 cmp fp, r0
cmp ip, r0                   // 4584 cmp ip, r0
cmp sp, r0                   // 4585 cmp sp, r0
cmp lr, r0                   // 4586 cmp lr, r0
cmp r8, r1                   // 4588 cmp r8, r1
cmp r9, r1                   // 4589 cmp r9, r1
cmp sl, r1                   // 458a cmp sl, r1
cmp fp, r1                   // 458b cmp fp, r1
cmp ip, r1                   // 458c cmp ip, r1
cmp sp, r1                   // 458d cmp sp, r1
cmp lr, r1                   // 458e cmp lr, r1
cmp r8, r2                   // 4590 cmp r8, r2
cmp r9, r2                   // 4591 cmp r9, r2
cmp sl, r2                   // 4592 cmp sl, r2
cmp fp, r2                   // 4593 cmp fp, r2
cmp ip, r2                   // 4594 cmp ip, r2
cmp sp, r2                   // 4595 cmp sp, r2
cmp lr, r2                   // 4596 cmp lr, r2
cmp r8, r3                   // 4598 cmp r8, r3
cmp r9, r3                   // 4599 cmp r9, r3
cmp sl, r3                   // 459a cmp sl, r3
cmp fp, r3                   // 459b cmp fp, r3
cmp ip, r3                   // 459c cmp ip, r3
cmp sp, r3                   // 459d cmp sp, r3
cmp lr, r3                   // 459e cmp lr, r3
cmp r8, r4                   // 45a0 cmp r8, r4
cmp r9, r4                   // 45a1 cmp r9, r4
cmp sl, r4                   // 45a2 cmp sl, r4
cmp fp, r4                   // 45a3 cmp fp, r4
cmp ip, r4                   // 45a4 cmp ip, r4
cmp sp, r4                   // 45a5 cmp sp, r4
cmp lr, r4                   // 45a6 cmp lr, r4
cmp r8, r5                   // 45a8 cmp r8, r5
cmp r9, r5                   // 45a9 cmp r9, r5
cmp sl, r5                   // 45aa cmp sl, r5
cmp fp, r5                   // 45ab cmp fp, r5
cmp ip, r5                   // 45ac cmp ip, r5
cmp sp, r5                   // 45ad cmp sp, r5
cmp lr, r5                   // 45ae cmp lr, r5
cmp r8, r6                   // 45b0 cmp r8, r6
cmp r9, r6                   // 45b1 cmp r9, r6
cmp sl, r6                   // 45b2 cmp sl, r6
cmp fp, r6                   // 45b3 cmp fp, r6
cmp ip, r6                   // 45b4 cmp ip, r6
cmp sp, r6                   // 45b5 cmp sp, r6
cmp lr, r6                   // 45b6 cmp lr, r6
cmp r8, r7                   // 45b8 cmp r8, r7
cmp r9, r7                   // 45b9 cmp r9, r7
cmp sl, r7                   // 45ba cmp sl, r7
cmp fp, r7                   // 45bb cmp fp, r7
cmp ip, r7                   // 45bc cmp ip, r7
cmp sp, r7                   // 45bd cmp sp, r7
cmp lr, r7                   // 45be cmp lr, r7
cmp r8, r8                   // 45c0 cmp r8, r8
cmp r9, r8                   // 45c1 cmp r9, r8
cmp sl, r8                   // 45c2 cmp sl, r8
cmp fp, r8                   // 45c3 cmp fp, r8
cmp ip, r8                   // 45c4 cmp ip, r8
cmp sp, r8                   // 45c5 cmp sp, r8
cmp lr, r8                   // 45c6 cmp lr, r8
cmp r8, r9                   // 45c8 cmp r8, r9
cmp r9, r9                   // 45c9 cmp r9, r9
cmp sl, r9                   // 45ca cmp sl, r9
cmp fp, r9                   // 45cb cmp fp, r9
cmp ip, r9                   // 45cc cmp ip, r9
cmp sp, r9                   // 45cd cmp sp, r9
cmp lr, r9                   // 45ce cmp lr, r9
cmp r8, sl                   // 45d0 cmp r8, sl
cmp r9, sl                   // 45d1 cmp r9, sl
cmp sl, sl                   // 45d2 cmp sl, sl
cmp fp, sl                   // 45d3 cmp fp, sl
cmp ip, sl                   // 45d4 cmp ip, sl
cmp sp, sl                   // 45d5 cmp sp, sl
cmp lr, sl                   // 45d6 cmp lr, sl
cmp r8, fp                   // 45d8 cmp r8, fp
cmp r9, fp                   // 45d9 cmp r9, fp
cmp sl, fp                   // 45da cmp sl, fp
cmp fp, fp                   // 45db cmp fp, fp
cmp ip, fp                   // 45dc cmp ip, fp
cmp sp, fp                   // 45dd cmp sp, fp
cmp lr, fp                   // 45de cmp lr, fp
cmp r8, ip                   // 45e0 cmp r8, ip
cmp r9, ip                   // 45e1 cmp r9, ip
cmp sl, ip                   // 45e2 cmp sl, ip
cmp fp, ip                   // 45e3 cmp fp, ip
cmp ip, ip                   // 45e4 cmp ip, ip
cmp sp, ip                   // 45e5 cmp sp, ip
cmp lr, ip                   // 45e6 cmp lr, ip
cmp r8, lr                   // 45f0 cmp r8, lr
cmp r9, lr                   // 45f1 cmp r9, lr
cmp sl, lr                   // 45f2 cmp sl, lr
cmp fp, lr                   // 45f3 cmp fp, lr
cmp ip, lr                   // 45f4 cmp ip, lr
cmp sp, lr                   // 45f5 cmp sp, lr
cmp lr, lr                   // 45f6 cmp lr, lr

mov r0, r0                   // 4600 mov r0, r0
mov r1, r0                   // 4601 mov r1, r0
mov r2, r0                   // 4602 mov r2, r0
mov r3, r0                   // 4603 mov r3, r0
mov r4, r0                   // 4604 mov r4, r0
mov r5, r0                   // 4605 mov r5, r0
mov r6, r0                   // 4606 mov r6, r0
mov r7, r0                   // 4607 mov r7, r0
mov r0, r1                   // 4608 mov r0, r1
mov r1, r1                   // 4609 mov r1, r1
mov r2, r1                   // 460a mov r2, r1
mov r3, r1                   // 460b mov r3, r1
mov r4, r1                   // 460c mov r4, r1
mov r5, r1                   // 460d mov r5, r1
mov r6, r1                   // 460e mov r6, r1
mov r7, r1                   // 460f mov r7, r1
mov r0, r2                   // 4610 mov r0, r2
mov r1, r2                   // 4611 mov r1, r2
mov r2, r2                   // 4612 mov r2, r2
mov r3, r2                   // 4613 mov r3, r2
mov r4, r2                   // 4614 mov r4, r2
mov r5, r2                   // 4615 mov r5, r2
mov r6, r2                   // 4616 mov r6, r2
mov r7, r2                   // 4617 mov r7, r2
mov r0, r3                   // 4618 mov r0, r3
mov r1, r3                   // 4619 mov r1, r3
mov r2, r3                   // 461a mov r2, r3
mov r3, r3                   // 461b mov r3, r3
mov r4, r3                   // 461c mov r4, r3
mov r5, r3                   // 461d mov r5, r3
mov r6, r3                   // 461e mov r6, r3
mov r7, r3                   // 461f mov r7, r3
mov r0, r4                   // 4620 mov r0, r4
mov r1, r4                   // 4621 mov r1, r4
mov r2, r4                   // 4622 mov r2, r4
mov r3, r4                   // 4623 mov r3, r4
mov r4, r4                   // 4624 mov r4, r4
mov r5, r4                   // 4625 mov r5, r4
mov r6, r4                   // 4626 mov r6, r4
mov r7, r4                   // 4627 mov r7, r4
mov r0, r5                   // 4628 mov r0, r5
mov r1, r5                   // 4629 mov r1, r5
mov r2, r5                   // 462a mov r2, r5
mov r3, r5                   // 462b mov r3, r5
mov r4, r5                   // 462c mov r4, r5
mov r5, r5                   // 462d mov r5, r5
mov r6, r5                   // 462e mov r6, r5
mov r7, r5                   // 462f mov r7, r5
mov r0, r6                   // 4630 mov r0, r6
mov r1, r6                   // 4631 mov r1, r6
mov r2, r6                   // 4632 mov r2, r6
mov r3, r6                   // 4633 mov r3, r6
mov r4, r6                   // 4634 mov r4, r6
mov r5, r6                   // 4635 mov r5, r6
mov r6, r6                   // 4636 mov r6, r6
mov r7, r6                   // 4637 mov r7, r6
mov r0, r7                   // 4638 mov r0, r7
mov r1, r7                   // 4639 mov r1, r7
mov r2, r7                   // 463a mov r2, r7
mov r3, r7                   // 463b mov r3, r7
mov r4, r7                   // 463c mov r4, r7
mov r5, r7                   // 463d mov r5, r7
mov r6, r7                   // 463e mov r6, r7
mov r7, r7                   // 463f mov r7, r7
mov r0, r8                   // 4640 mov r0, r8
mov r1, r8                   // 4641 mov r1, r8
mov r2, r8                   // 4642 mov r2, r8
mov r3, r8                   // 4643 mov r3, r8
mov r4, r8                   // 4644 mov r4, r8
mov r5, r8                   // 4645 mov r5, r8
mov r6, r8                   // 4646 mov r6, r8
mov r7, r8                   // 4647 mov r7, r8
mov r0, r9                   // 4648 mov r0, r9
mov r1, r9                   // 4649 mov r1, r9
mov r2, r9                   // 464a mov r2, r9
mov r3, r9                   // 464b mov r3, r9
mov r4, r9                   // 464c mov r4, r9
mov r5, r9                   // 464d mov r5, r9
mov r6, r9                   // 464e mov r6, r9
mov r7, r9                   // 464f mov r7, r9
mov r0, sl                   // 4650 mov r0, sl
mov r1, sl                   // 4651 mov r1, sl
mov r2, sl                   // 4652 mov r2, sl
mov r3, sl                   // 4653 mov r3, sl
mov r4, sl                   // 4654 mov r4, sl
mov r5, sl                   // 4655 mov r5, sl
mov r6, sl                   // 4656 mov r6, sl
mov r7, sl                   // 4657 mov r7, sl
mov r0, fp                   // 4658 mov r0, fp
mov r1, fp                   // 4659 mov r1, fp
mov r2, fp                   // 465a mov r2, fp
mov r3, fp                   // 465b mov r3, fp
mov r4, fp                   // 465c mov r4, fp
mov r5, fp                   // 465d mov r5, fp
mov r6, fp                   // 465e mov r6, fp
mov r7, fp                   // 465f mov r7, fp
mov r0, ip                   // 4660 mov r0, ip
mov r1, ip                   // 4661 mov r1, ip
mov r2, ip                   // 4662 mov r2, ip
mov r3, ip                   // 4663 mov r3, ip
mov r4, ip                   // 4664 mov r4, ip
mov r5, ip                   // 4665 mov r5, ip
mov r6, ip                   // 4666 mov r6, ip
mov r7, ip                   // 4667 mov r7, ip
mov r0, sp                   // 4668 mov r0, sp
mov r1, sp                   // 4669 mov r1, sp
mov r2, sp                   // 466a mov r2, sp
mov r3, sp                   // 466b mov r3, sp
mov r4, sp                   // 466c mov r4, sp
mov r5, sp                   // 466d mov r5, sp
mov r6, sp                   // 466e mov r6, sp
mov r7, sp                   // 466f mov r7, sp
mov r0, lr                   // 4670 mov r0, lr
mov r1, lr                   // 4671 mov r1, lr
mov r2, lr                   // 4672 mov r2, lr
mov r3, lr                   // 4673 mov r3, lr
mov r4, lr                   // 4674 mov r4, lr
mov r5, lr                   // 4675 mov r5, lr
mov r6, lr                   // 4676 mov r6, lr
mov r7, lr                   // 4677 mov r7, lr
mov r0, pc                   // 4678 mov r0, pc
mov r1, pc                   // 4679 mov r1, pc
mov r2, pc                   // 467a mov r2, pc
mov r3, pc                   // 467b mov r3, pc
mov r4, pc                   // 467c mov r4, pc
mov r5, pc                   // 467d mov r5, pc
mov r6, pc                   // 467e mov r6, pc
mov r7, pc                   // 467f mov r7, pc
mov r8, r0                   // 4680 mov r8, r0
mov r9, r0                   // 4681 mov r9, r0
mov sl, r0                   // 4682 mov sl, r0
mov fp, r0                   // 4683 mov fp, r0
mov ip, r0                   // 4684 mov ip, r0
mov sp, r0                   // 4685 mov sp, r0
mov lr, r0                   // 4686 mov lr, r0
mov pc, r0                   // 4687 mov pc, r0
mov r8, r1                   // 4688 mov r8, r1
mov r9, r1                   // 4689 mov r9, r1
mov sl, r1                   // 468a mov sl, r1
mov fp, r1                   // 468b mov fp, r1
mov ip, r1                   // 468c mov ip, r1
mov sp, r1                   // 468d mov sp, r1
mov lr, r1                   // 468e mov lr, r1
mov pc, r1                   // 468f mov pc, r1
mov r8, r2                   // 4690 mov r8, r2
mov r9, r2                   // 4691 mov r9, r2
mov sl, r2                   // 4692 mov sl, r2
mov fp, r2                   // 4693 mov fp, r2
mov ip, r2                   // 4694 mov ip, r2
mov sp, r2                   // 4695 mov sp, r2
mov lr, r2                   // 4696 mov lr, r2
mov pc, r2                   // 4697 mov pc, r2
mov r8, r3                   // 4698 mov r8, r3
mov r9, r3                   // 4699 mov r9, r3
mov sl, r3                   // 469a mov sl, r3
mov fp, r3                   // 469b mov fp, r3
mov ip, r3                   // 469c mov ip, r3
mov sp, r3                   // 469d mov sp, r3
mov lr, r3                   // 469e mov lr, r3
mov pc, r3                   // 469f mov pc, r3
mov r8, r4                   // 46a0 mov r8, r4
mov r9, r4                   // 46a1 mov r9, r4
mov sl, r4                   // 46a2 mov sl, r4
mov fp, r4                   // 46a3 mov fp, r4
mov ip, r4                   // 46a4 mov ip, r4
mov sp, r4                   // 46a5 mov sp, r4
mov lr, r4                   // 46a6 mov lr, r4
mov pc, r4                   // 46a7 mov pc, r4
mov r8, r5                   // 46a8 mov r8, r5
mov r9, r5                   // 46a9 mov r9, r5
mov sl, r5                   // 46aa mov sl, r5
mov fp, r5                   // 46ab mov fp, r5
mov ip, r5                   // 46ac mov ip, r5
mov sp, r5                   // 46ad mov sp, r5
mov lr, r5                   // 46ae mov lr, r5
mov pc, r5                   // 46af mov pc, r5
mov r8, r6                   // 46b0 mov r8, r6
mov r9, r6                   // 46b1 mov r9, r6
mov sl, r6                   // 46b2 mov sl, r6
mov fp, r6                   // 46b3 mov fp, r6
mov ip, r6                   // 46b4 mov ip, r6
mov sp, r6                   // 46b5 mov sp, r6
mov lr, r6                   // 46b6 mov lr, r6
mov pc, r6                   // 46b7 mov pc, r6
mov r8, r7                   // 46b8 mov r8, r7
mov r9, r7                   // 46b9 mov r9, r7
mov sl, r7                   // 46ba mov sl, r7
mov fp, r7                   // 46bb mov fp, r7
mov ip, r7                   // 46bc mov ip, r7
mov sp, r7                   // 46bd mov sp, r7
mov lr, r7                   // 46be mov lr, r7
mov pc, r7                   // 46bf mov pc, r7
nop                          // 46c0 nop   // (mov r8, r8)
mov r9, r8                   // 46c1 mov r9, r8
mov sl, r8                   // 46c2 mov sl, r8
mov fp, r8                   // 46c3 mov fp, r8
mov ip, r8                   // 46c4 mov ip, r8
mov sp, r8                   // 46c5 mov sp, r8
mov lr, r8                   // 46c6 mov lr, r8
mov pc, r8                   // 46c7 mov pc, r8
mov r8, r9                   // 46c8 mov r8, r9
mov r9, r9                   // 46c9 mov r9, r9
mov sl, r9                   // 46ca mov sl, r9
mov fp, r9                   // 46cb mov fp, r9
mov ip, r9                   // 46cc mov ip, r9
mov sp, r9                   // 46cd mov sp, r9
mov lr, r9                   // 46ce mov lr, r9
mov pc, r9                   // 46cf mov pc, r9
mov r8, sl                   // 46d0 mov r8, sl
mov r9, sl                   // 46d1 mov r9, sl
mov sl, sl                   // 46d2 mov sl, sl
mov fp, sl                   // 46d3 mov fp, sl
mov ip, sl                   // 46d4 mov ip, sl
mov sp, sl                   // 46d5 mov sp, sl
mov lr, sl                   // 46d6 mov lr, sl
mov pc, sl                   // 46d7 mov pc, sl
mov r8, fp                   // 46d8 mov r8, fp
mov r9, fp                   // 46d9 mov r9, fp
mov sl, fp                   // 46da mov sl, fp
mov fp, fp                   // 46db mov fp, fp
mov ip, fp                   // 46dc mov ip, fp
mov sp, fp                   // 46dd mov sp, fp
mov lr, fp                   // 46de mov lr, fp
mov pc, fp                   // 46df mov pc, fp
mov r8, ip                   // 46e0 mov r8, ip
mov r9, ip                   // 46e1 mov r9, ip
mov sl, ip                   // 46e2 mov sl, ip
mov fp, ip                   // 46e3 mov fp, ip
mov ip, ip                   // 46e4 mov ip, ip
mov sp, ip                   // 46e5 mov sp, ip
mov lr, ip                   // 46e6 mov lr, ip
mov pc, ip                   // 46e7 mov pc, ip
mov r8, sp                   // 46e8 mov r8, sp
mov r9, sp                   // 46e9 mov r9, sp
mov sl, sp                   // 46ea mov sl, sp
mov fp, sp                   // 46eb mov fp, sp
mov ip, sp                   // 46ec mov ip, sp
mov lr, sp                   // 46ee mov lr, sp
mov r8, lr                   // 46f0 mov r8, lr
mov r9, lr                   // 46f1 mov r9, lr
mov sl, lr                   // 46f2 mov sl, lr
mov fp, lr                   // 46f3 mov fp, lr
mov ip, lr                   // 46f4 mov ip, lr
mov sp, lr                   // 46f5 mov sp, lr
mov lr, lr                   // 46f6 mov lr, lr
mov pc, lr                   // 46f7 mov pc, lr
mov r8, pc                   // 46f8 mov r8, pc
mov r9, pc                   // 46f9 mov r9, pc
mov sl, pc                   // 46fa mov sl, pc
mov fp, pc                   // 46fb mov fp, pc
mov ip, pc                   // 46fc mov ip, pc
mov lr, pc                   // 46fe mov lr, pc

bx r0                        // 4700 bx r0
bx r1                        // 4708 bx r1
bx r2                        // 4710 bx r2
bx r3                        // 4718 bx r3
bx r4                        // 4720 bx r4
bx r5                        // 4728 bx r5
bx r6                        // 4730 bx r6
bx r7                        // 4738 bx r7
bx r8                        // 4740 bx r8
bx r9                        // 4748 bx r9
bx sl                        // 4750 bx sl
bx fp                        // 4758 bx fp
bx ip                        // 4760 bx ip
bx sp                        // 4768 bx sp
bx lr                        // 4770 bx lr
bx pc                        // 4778 bx pc

.align 2
ldr r0, [pc, #0] // (0x0000900// 4800 ldr r0, [pc, #0] // (0x00009004)
ldr r0, [pc, #4] // (0x0000900// 4801 ldr r0, [pc, #4] // (0x00009008)
ldr r0, [pc, #1020] // (0x0000// 48ff ldr r0, [pc, #1020] // (0x000095fc)
ldr r1, [pc, #0] // (0x0000920// 4900 ldr r1, [pc, #0] // (0x00009204)
ldr r1, [pc, #4] // (0x0000920// 4901 ldr r1, [pc, #4] // (0x00009208)
ldr r1, [pc, #1020] // (0x0000// 49ff ldr r1, [pc, #1020] // (0x000097fc)
ldr r2, [pc, #0] // (0x0000940// 4a00 ldr r2, [pc, #0] // (0x00009404)
ldr r2, [pc, #4] // (0x0000940// 4a01 ldr r2, [pc, #4] // (0x00009408)
ldr r2, [pc, #1020] // (0x0000// 4aff ldr r2, [pc, #1020] // (0x000099fc)
ldr r3, [pc, #0] // (0x0000960// 4b00 ldr r3, [pc, #0] // (0x00009604)
ldr r3, [pc, #4] // (0x0000960// 4b01 ldr r3, [pc, #4] // (0x00009608)
ldr r3, [pc, #1020] // (0x0000// 4bff ldr r3, [pc, #1020] // (0x00009bfc)
ldr r4, [pc, #0] // (0x0000980// 4c00 ldr r4, [pc, #0] // (0x00009804)
ldr r4, [pc, #4] // (0x0000980// 4c01 ldr r4, [pc, #4] // (0x00009808)
ldr r4, [pc, #1020] // (0x0000// 4cff ldr r4, [pc, #1020] // (0x00009dfc)
ldr r5, [pc, #0] // (0x00009a0// 4d00 ldr r5, [pc, #0] // (0x00009a04)
ldr r5, [pc, #4] // (0x00009a0// 4d01 ldr r5, [pc, #4] // (0x00009a08)
ldr r5, [pc, #1020] // (0x0000// 4dff ldr r5, [pc, #1020] // (0x00009ffc)
ldr r6, [pc, #0] // (0x00009c0// 4e00 ldr r6, [pc, #0] // (0x00009c04)
ldr r6, [pc, #4] // (0x00009c0// 4e01 ldr r6, [pc, #4] // (0x00009c08)
ldr r6, [pc, #1020] // (0x0000// 4eff ldr r6, [pc, #1020] // (0x0000a1fc)
ldr r7, [pc, #0] // (0x00009e0// 4f00 ldr r7, [pc, #0] // (0x00009e04)
ldr r7, [pc, #4] // (0x00009e0// 4f01 ldr r7, [pc, #4] // (0x00009e08)
ldr r7, [pc, #1020] // (0x0000// 4fff ldr r7, [pc, #1020] // (0x0000a3fc)

str r0, [r0, r0]             // 5000 str r0, [r0, r0]
str r1, [r0, r0]             // 5001 str r1, [r0, r0]
str r2, [r0, r0]             // 5002 str r2, [r0, r0]
str r3, [r0, r0]             // 5003 str r3, [r0, r0]
str r4, [r0, r0]             // 5004 str r4, [r0, r0]
str r5, [r0, r0]             // 5005 str r5, [r0, r0]
str r6, [r0, r0]             // 5006 str r6, [r0, r0]
str r7, [r0, r0]             // 5007 str r7, [r0, r0]
str r0, [r1, r0]             // 5008 str r0, [r1, r0]
str r1, [r1, r0]             // 5009 str r1, [r1, r0]
str r2, [r1, r0]             // 500a str r2, [r1, r0]
str r3, [r1, r0]             // 500b str r3, [r1, r0]
str r4, [r1, r0]             // 500c str r4, [r1, r0]
str r5, [r1, r0]             // 500d str r5, [r1, r0]
str r6, [r1, r0]             // 500e str r6, [r1, r0]
str r7, [r1, r0]             // 500f str r7, [r1, r0]
str r0, [r2, r0]             // 5010 str r0, [r2, r0]
str r1, [r2, r0]             // 5011 str r1, [r2, r0]
str r2, [r2, r0]             // 5012 str r2, [r2, r0]
str r3, [r2, r0]             // 5013 str r3, [r2, r0]
str r4, [r2, r0]             // 5014 str r4, [r2, r0]
str r5, [r2, r0]             // 5015 str r5, [r2, r0]
str r6, [r2, r0]             // 5016 str r6, [r2, r0]
str r7, [r2, r0]             // 5017 str r7, [r2, r0]
str r0, [r3, r0]             // 5018 str r0, [r3, r0]
str r1, [r3, r0]             // 5019 str r1, [r3, r0]
str r2, [r3, r0]             // 501a str r2, [r3, r0]
str r3, [r3, r0]             // 501b str r3, [r3, r0]
str r4, [r3, r0]             // 501c str r4, [r3, r0]
str r5, [r3, r0]             // 501d str r5, [r3, r0]
str r6, [r3, r0]             // 501e str r6, [r3, r0]
str r7, [r3, r0]             // 501f str r7, [r3, r0]
str r0, [r4, r0]             // 5020 str r0, [r4, r0]
str r1, [r4, r0]             // 5021 str r1, [r4, r0]
str r2, [r4, r0]             // 5022 str r2, [r4, r0]
str r3, [r4, r0]             // 5023 str r3, [r4, r0]
str r4, [r4, r0]             // 5024 str r4, [r4, r0]
str r5, [r4, r0]             // 5025 str r5, [r4, r0]
str r6, [r4, r0]             // 5026 str r6, [r4, r0]
str r7, [r4, r0]             // 5027 str r7, [r4, r0]
str r0, [r5, r0]             // 5028 str r0, [r5, r0]
str r1, [r5, r0]             // 5029 str r1, [r5, r0]
str r2, [r5, r0]             // 502a str r2, [r5, r0]
str r3, [r5, r0]             // 502b str r3, [r5, r0]
str r4, [r5, r0]             // 502c str r4, [r5, r0]
str r5, [r5, r0]             // 502d str r5, [r5, r0]
str r6, [r5, r0]             // 502e str r6, [r5, r0]
str r7, [r5, r0]             // 502f str r7, [r5, r0]
str r0, [r6, r0]             // 5030 str r0, [r6, r0]
str r1, [r6, r0]             // 5031 str r1, [r6, r0]
str r2, [r6, r0]             // 5032 str r2, [r6, r0]
str r3, [r6, r0]             // 5033 str r3, [r6, r0]
str r4, [r6, r0]             // 5034 str r4, [r6, r0]
str r5, [r6, r0]             // 5035 str r5, [r6, r0]
str r6, [r6, r0]             // 5036 str r6, [r6, r0]
str r7, [r6, r0]             // 5037 str r7, [r6, r0]
str r0, [r7, r0]             // 5038 str r0, [r7, r0]
str r1, [r7, r0]             // 5039 str r1, [r7, r0]
str r2, [r7, r0]             // 503a str r2, [r7, r0]
str r3, [r7, r0]             // 503b str r3, [r7, r0]
str r4, [r7, r0]             // 503c str r4, [r7, r0]
str r5, [r7, r0]             // 503d str r5, [r7, r0]
str r6, [r7, r0]             // 503e str r6, [r7, r0]
str r7, [r7, r0]             // 503f str r7, [r7, r0]
str r0, [r0, r1]             // 5040 str r0, [r0, r1]
str r1, [r0, r1]             // 5041 str r1, [r0, r1]
str r2, [r0, r1]             // 5042 str r2, [r0, r1]
str r3, [r0, r1]             // 5043 str r3, [r0, r1]
str r4, [r0, r1]             // 5044 str r4, [r0, r1]
str r5, [r0, r1]             // 5045 str r5, [r0, r1]
str r6, [r0, r1]             // 5046 str r6, [r0, r1]
str r7, [r0, r1]             // 5047 str r7, [r0, r1]
str r0, [r1, r1]             // 5048 str r0, [r1, r1]
str r1, [r1, r1]             // 5049 str r1, [r1, r1]
str r2, [r1, r1]             // 504a str r2, [r1, r1]
str r3, [r1, r1]             // 504b str r3, [r1, r1]
str r4, [r1, r1]             // 504c str r4, [r1, r1]
str r5, [r1, r1]             // 504d str r5, [r1, r1]
str r6, [r1, r1]             // 504e str r6, [r1, r1]
str r7, [r1, r1]             // 504f str r7, [r1, r1]
str r0, [r2, r1]             // 5050 str r0, [r2, r1]
str r1, [r2, r1]             // 5051 str r1, [r2, r1]
str r2, [r2, r1]             // 5052 str r2, [r2, r1]
str r3, [r2, r1]             // 5053 str r3, [r2, r1]
str r4, [r2, r1]             // 5054 str r4, [r2, r1]
str r5, [r2, r1]             // 5055 str r5, [r2, r1]
str r6, [r2, r1]             // 5056 str r6, [r2, r1]
str r7, [r2, r1]             // 5057 str r7, [r2, r1]
str r0, [r3, r1]             // 5058 str r0, [r3, r1]
str r1, [r3, r1]             // 5059 str r1, [r3, r1]
str r2, [r3, r1]             // 505a str r2, [r3, r1]
str r3, [r3, r1]             // 505b str r3, [r3, r1]
str r4, [r3, r1]             // 505c str r4, [r3, r1]
str r5, [r3, r1]             // 505d str r5, [r3, r1]
str r6, [r3, r1]             // 505e str r6, [r3, r1]
str r7, [r3, r1]             // 505f str r7, [r3, r1]
str r0, [r4, r1]             // 5060 str r0, [r4, r1]
str r1, [r4, r1]             // 5061 str r1, [r4, r1]
str r2, [r4, r1]             // 5062 str r2, [r4, r1]
str r3, [r4, r1]             // 5063 str r3, [r4, r1]
str r4, [r4, r1]             // 5064 str r4, [r4, r1]
str r5, [r4, r1]             // 5065 str r5, [r4, r1]
str r6, [r4, r1]             // 5066 str r6, [r4, r1]
str r7, [r4, r1]             // 5067 str r7, [r4, r1]
str r0, [r5, r1]             // 5068 str r0, [r5, r1]
str r1, [r5, r1]             // 5069 str r1, [r5, r1]
str r2, [r5, r1]             // 506a str r2, [r5, r1]
str r3, [r5, r1]             // 506b str r3, [r5, r1]
str r4, [r5, r1]             // 506c str r4, [r5, r1]
str r5, [r5, r1]             // 506d str r5, [r5, r1]
str r6, [r5, r1]             // 506e str r6, [r5, r1]
str r7, [r5, r1]             // 506f str r7, [r5, r1]
str r0, [r6, r1]             // 5070 str r0, [r6, r1]
str r1, [r6, r1]             // 5071 str r1, [r6, r1]
str r2, [r6, r1]             // 5072 str r2, [r6, r1]
str r3, [r6, r1]             // 5073 str r3, [r6, r1]
str r4, [r6, r1]             // 5074 str r4, [r6, r1]
str r5, [r6, r1]             // 5075 str r5, [r6, r1]
str r6, [r6, r1]             // 5076 str r6, [r6, r1]
str r7, [r6, r1]             // 5077 str r7, [r6, r1]
str r0, [r7, r1]             // 5078 str r0, [r7, r1]
str r1, [r7, r1]             // 5079 str r1, [r7, r1]
str r2, [r7, r1]             // 507a str r2, [r7, r1]
str r3, [r7, r1]             // 507b str r3, [r7, r1]
str r4, [r7, r1]             // 507c str r4, [r7, r1]
str r5, [r7, r1]             // 507d str r5, [r7, r1]
str r6, [r7, r1]             // 507e str r6, [r7, r1]
str r7, [r7, r1]             // 507f str r7, [r7, r1]
str r0, [r0, r2]             // 5080 str r0, [r0, r2]
str r1, [r0, r2]             // 5081 str r1, [r0, r2]
str r2, [r0, r2]             // 5082 str r2, [r0, r2]
str r3, [r0, r2]             // 5083 str r3, [r0, r2]
str r4, [r0, r2]             // 5084 str r4, [r0, r2]
str r5, [r0, r2]             // 5085 str r5, [r0, r2]
str r6, [r0, r2]             // 5086 str r6, [r0, r2]
str r7, [r0, r2]             // 5087 str r7, [r0, r2]
str r0, [r1, r2]             // 5088 str r0, [r1, r2]
str r1, [r1, r2]             // 5089 str r1, [r1, r2]
str r2, [r1, r2]             // 508a str r2, [r1, r2]
str r3, [r1, r2]             // 508b str r3, [r1, r2]
str r4, [r1, r2]             // 508c str r4, [r1, r2]
str r5, [r1, r2]             // 508d str r5, [r1, r2]
str r6, [r1, r2]             // 508e str r6, [r1, r2]
str r7, [r1, r2]             // 508f str r7, [r1, r2]
str r0, [r2, r2]             // 5090 str r0, [r2, r2]
str r1, [r2, r2]             // 5091 str r1, [r2, r2]
str r2, [r2, r2]             // 5092 str r2, [r2, r2]
str r3, [r2, r2]             // 5093 str r3, [r2, r2]
str r4, [r2, r2]             // 5094 str r4, [r2, r2]
str r5, [r2, r2]             // 5095 str r5, [r2, r2]
str r6, [r2, r2]             // 5096 str r6, [r2, r2]
str r7, [r2, r2]             // 5097 str r7, [r2, r2]
str r0, [r3, r2]             // 5098 str r0, [r3, r2]
str r1, [r3, r2]             // 5099 str r1, [r3, r2]
str r2, [r3, r2]             // 509a str r2, [r3, r2]
str r3, [r3, r2]             // 509b str r3, [r3, r2]
str r4, [r3, r2]             // 509c str r4, [r3, r2]
str r5, [r3, r2]             // 509d str r5, [r3, r2]
str r6, [r3, r2]             // 509e str r6, [r3, r2]
str r7, [r3, r2]             // 509f str r7, [r3, r2]
str r0, [r4, r2]             // 50a0 str r0, [r4, r2]
str r1, [r4, r2]             // 50a1 str r1, [r4, r2]
str r2, [r4, r2]             // 50a2 str r2, [r4, r2]
str r3, [r4, r2]             // 50a3 str r3, [r4, r2]
str r4, [r4, r2]             // 50a4 str r4, [r4, r2]
str r5, [r4, r2]             // 50a5 str r5, [r4, r2]
str r6, [r4, r2]             // 50a6 str r6, [r4, r2]
str r7, [r4, r2]             // 50a7 str r7, [r4, r2]
str r0, [r5, r2]             // 50a8 str r0, [r5, r2]
str r1, [r5, r2]             // 50a9 str r1, [r5, r2]
str r2, [r5, r2]             // 50aa str r2, [r5, r2]
str r3, [r5, r2]             // 50ab str r3, [r5, r2]
str r4, [r5, r2]             // 50ac str r4, [r5, r2]
str r5, [r5, r2]             // 50ad str r5, [r5, r2]
str r6, [r5, r2]             // 50ae str r6, [r5, r2]
str r7, [r5, r2]             // 50af str r7, [r5, r2]
str r0, [r6, r2]             // 50b0 str r0, [r6, r2]
str r1, [r6, r2]             // 50b1 str r1, [r6, r2]
str r2, [r6, r2]             // 50b2 str r2, [r6, r2]
str r3, [r6, r2]             // 50b3 str r3, [r6, r2]
str r4, [r6, r2]             // 50b4 str r4, [r6, r2]
str r5, [r6, r2]             // 50b5 str r5, [r6, r2]
str r6, [r6, r2]             // 50b6 str r6, [r6, r2]
str r7, [r6, r2]             // 50b7 str r7, [r6, r2]
str r0, [r7, r2]             // 50b8 str r0, [r7, r2]
str r1, [r7, r2]             // 50b9 str r1, [r7, r2]
str r2, [r7, r2]             // 50ba str r2, [r7, r2]
str r3, [r7, r2]             // 50bb str r3, [r7, r2]
str r4, [r7, r2]             // 50bc str r4, [r7, r2]
str r5, [r7, r2]             // 50bd str r5, [r7, r2]
str r6, [r7, r2]             // 50be str r6, [r7, r2]
str r7, [r7, r2]             // 50bf str r7, [r7, r2]
str r0, [r0, r3]             // 50c0 str r0, [r0, r3]
str r1, [r0, r3]             // 50c1 str r1, [r0, r3]
str r2, [r0, r3]             // 50c2 str r2, [r0, r3]
str r3, [r0, r3]             // 50c3 str r3, [r0, r3]
str r4, [r0, r3]             // 50c4 str r4, [r0, r3]
str r5, [r0, r3]             // 50c5 str r5, [r0, r3]
str r6, [r0, r3]             // 50c6 str r6, [r0, r3]
str r7, [r0, r3]             // 50c7 str r7, [r0, r3]
str r0, [r1, r3]             // 50c8 str r0, [r1, r3]
str r1, [r1, r3]             // 50c9 str r1, [r1, r3]
str r2, [r1, r3]             // 50ca str r2, [r1, r3]
str r3, [r1, r3]             // 50cb str r3, [r1, r3]
str r4, [r1, r3]             // 50cc str r4, [r1, r3]
str r5, [r1, r3]             // 50cd str r5, [r1, r3]
str r6, [r1, r3]             // 50ce str r6, [r1, r3]
str r7, [r1, r3]             // 50cf str r7, [r1, r3]
str r0, [r2, r3]             // 50d0 str r0, [r2, r3]
str r1, [r2, r3]             // 50d1 str r1, [r2, r3]
str r2, [r2, r3]             // 50d2 str r2, [r2, r3]
str r3, [r2, r3]             // 50d3 str r3, [r2, r3]
str r4, [r2, r3]             // 50d4 str r4, [r2, r3]
str r5, [r2, r3]             // 50d5 str r5, [r2, r3]
str r6, [r2, r3]             // 50d6 str r6, [r2, r3]
str r7, [r2, r3]             // 50d7 str r7, [r2, r3]
str r0, [r3, r3]             // 50d8 str r0, [r3, r3]
str r1, [r3, r3]             // 50d9 str r1, [r3, r3]
str r2, [r3, r3]             // 50da str r2, [r3, r3]
str r3, [r3, r3]             // 50db str r3, [r3, r3]
str r4, [r3, r3]             // 50dc str r4, [r3, r3]
str r5, [r3, r3]             // 50dd str r5, [r3, r3]
str r6, [r3, r3]             // 50de str r6, [r3, r3]
str r7, [r3, r3]             // 50df str r7, [r3, r3]
str r0, [r4, r3]             // 50e0 str r0, [r4, r3]
str r1, [r4, r3]             // 50e1 str r1, [r4, r3]
str r2, [r4, r3]             // 50e2 str r2, [r4, r3]
str r3, [r4, r3]             // 50e3 str r3, [r4, r3]
str r4, [r4, r3]             // 50e4 str r4, [r4, r3]
str r5, [r4, r3]             // 50e5 str r5, [r4, r3]
str r6, [r4, r3]             // 50e6 str r6, [r4, r3]
str r7, [r4, r3]             // 50e7 str r7, [r4, r3]
str r0, [r5, r3]             // 50e8 str r0, [r5, r3]
str r1, [r5, r3]             // 50e9 str r1, [r5, r3]
str r2, [r5, r3]             // 50ea str r2, [r5, r3]
str r3, [r5, r3]             // 50eb str r3, [r5, r3]
str r4, [r5, r3]             // 50ec str r4, [r5, r3]
str r5, [r5, r3]             // 50ed str r5, [r5, r3]
str r6, [r5, r3]             // 50ee str r6, [r5, r3]
str r7, [r5, r3]             // 50ef str r7, [r5, r3]
str r0, [r6, r3]             // 50f0 str r0, [r6, r3]
str r1, [r6, r3]             // 50f1 str r1, [r6, r3]
str r2, [r6, r3]             // 50f2 str r2, [r6, r3]
str r3, [r6, r3]             // 50f3 str r3, [r6, r3]
str r4, [r6, r3]             // 50f4 str r4, [r6, r3]
str r5, [r6, r3]             // 50f5 str r5, [r6, r3]
str r6, [r6, r3]             // 50f6 str r6, [r6, r3]
str r7, [r6, r3]             // 50f7 str r7, [r6, r3]
str r0, [r7, r3]             // 50f8 str r0, [r7, r3]
str r1, [r7, r3]             // 50f9 str r1, [r7, r3]
str r2, [r7, r3]             // 50fa str r2, [r7, r3]
str r3, [r7, r3]             // 50fb str r3, [r7, r3]
str r4, [r7, r3]             // 50fc str r4, [r7, r3]
str r5, [r7, r3]             // 50fd str r5, [r7, r3]
str r6, [r7, r3]             // 50fe str r6, [r7, r3]
str r7, [r7, r3]             // 50ff str r7, [r7, r3]
str r0, [r0, r4]             // 5100 str r0, [r0, r4]
str r1, [r0, r4]             // 5101 str r1, [r0, r4]
str r2, [r0, r4]             // 5102 str r2, [r0, r4]
str r3, [r0, r4]             // 5103 str r3, [r0, r4]
str r4, [r0, r4]             // 5104 str r4, [r0, r4]
str r5, [r0, r4]             // 5105 str r5, [r0, r4]
str r6, [r0, r4]             // 5106 str r6, [r0, r4]
str r7, [r0, r4]             // 5107 str r7, [r0, r4]
str r0, [r1, r4]             // 5108 str r0, [r1, r4]
str r1, [r1, r4]             // 5109 str r1, [r1, r4]
str r2, [r1, r4]             // 510a str r2, [r1, r4]
str r3, [r1, r4]             // 510b str r3, [r1, r4]
str r4, [r1, r4]             // 510c str r4, [r1, r4]
str r5, [r1, r4]             // 510d str r5, [r1, r4]
str r6, [r1, r4]             // 510e str r6, [r1, r4]
str r7, [r1, r4]             // 510f str r7, [r1, r4]
str r0, [r2, r4]             // 5110 str r0, [r2, r4]
str r1, [r2, r4]             // 5111 str r1, [r2, r4]
str r2, [r2, r4]             // 5112 str r2, [r2, r4]
str r3, [r2, r4]             // 5113 str r3, [r2, r4]
str r4, [r2, r4]             // 5114 str r4, [r2, r4]
str r5, [r2, r4]             // 5115 str r5, [r2, r4]
str r6, [r2, r4]             // 5116 str r6, [r2, r4]
str r7, [r2, r4]             // 5117 str r7, [r2, r4]
str r0, [r3, r4]             // 5118 str r0, [r3, r4]
str r1, [r3, r4]             // 5119 str r1, [r3, r4]
str r2, [r3, r4]             // 511a str r2, [r3, r4]
str r3, [r3, r4]             // 511b str r3, [r3, r4]
str r4, [r3, r4]             // 511c str r4, [r3, r4]
str r5, [r3, r4]             // 511d str r5, [r3, r4]
str r6, [r3, r4]             // 511e str r6, [r3, r4]
str r7, [r3, r4]             // 511f str r7, [r3, r4]
str r0, [r4, r4]             // 5120 str r0, [r4, r4]
str r1, [r4, r4]             // 5121 str r1, [r4, r4]
str r2, [r4, r4]             // 5122 str r2, [r4, r4]
str r3, [r4, r4]             // 5123 str r3, [r4, r4]
str r4, [r4, r4]             // 5124 str r4, [r4, r4]
str r5, [r4, r4]             // 5125 str r5, [r4, r4]
str r6, [r4, r4]             // 5126 str r6, [r4, r4]
str r7, [r4, r4]             // 5127 str r7, [r4, r4]
str r0, [r5, r4]             // 5128 str r0, [r5, r4]
str r1, [r5, r4]             // 5129 str r1, [r5, r4]
str r2, [r5, r4]             // 512a str r2, [r5, r4]
str r3, [r5, r4]             // 512b str r3, [r5, r4]
str r4, [r5, r4]             // 512c str r4, [r5, r4]
str r5, [r5, r4]             // 512d str r5, [r5, r4]
str r6, [r5, r4]             // 512e str r6, [r5, r4]
str r7, [r5, r4]             // 512f str r7, [r5, r4]
str r0, [r6, r4]             // 5130 str r0, [r6, r4]
str r1, [r6, r4]             // 5131 str r1, [r6, r4]
str r2, [r6, r4]             // 5132 str r2, [r6, r4]
str r3, [r6, r4]             // 5133 str r3, [r6, r4]
str r4, [r6, r4]             // 5134 str r4, [r6, r4]
str r5, [r6, r4]             // 5135 str r5, [r6, r4]
str r6, [r6, r4]             // 5136 str r6, [r6, r4]
str r7, [r6, r4]             // 5137 str r7, [r6, r4]
str r0, [r7, r4]             // 5138 str r0, [r7, r4]
str r1, [r7, r4]             // 5139 str r1, [r7, r4]
str r2, [r7, r4]             // 513a str r2, [r7, r4]
str r3, [r7, r4]             // 513b str r3, [r7, r4]
str r4, [r7, r4]             // 513c str r4, [r7, r4]
str r5, [r7, r4]             // 513d str r5, [r7, r4]
str r6, [r7, r4]             // 513e str r6, [r7, r4]
str r7, [r7, r4]             // 513f str r7, [r7, r4]
str r0, [r0, r5]             // 5140 str r0, [r0, r5]
str r1, [r0, r5]             // 5141 str r1, [r0, r5]
str r2, [r0, r5]             // 5142 str r2, [r0, r5]
str r3, [r0, r5]             // 5143 str r3, [r0, r5]
str r4, [r0, r5]             // 5144 str r4, [r0, r5]
str r5, [r0, r5]             // 5145 str r5, [r0, r5]
str r6, [r0, r5]             // 5146 str r6, [r0, r5]
str r7, [r0, r5]             // 5147 str r7, [r0, r5]
str r0, [r1, r5]             // 5148 str r0, [r1, r5]
str r1, [r1, r5]             // 5149 str r1, [r1, r5]
str r2, [r1, r5]             // 514a str r2, [r1, r5]
str r3, [r1, r5]             // 514b str r3, [r1, r5]
str r4, [r1, r5]             // 514c str r4, [r1, r5]
str r5, [r1, r5]             // 514d str r5, [r1, r5]
str r6, [r1, r5]             // 514e str r6, [r1, r5]
str r7, [r1, r5]             // 514f str r7, [r1, r5]
str r0, [r2, r5]             // 5150 str r0, [r2, r5]
str r1, [r2, r5]             // 5151 str r1, [r2, r5]
str r2, [r2, r5]             // 5152 str r2, [r2, r5]
str r3, [r2, r5]             // 5153 str r3, [r2, r5]
str r4, [r2, r5]             // 5154 str r4, [r2, r5]
str r5, [r2, r5]             // 5155 str r5, [r2, r5]
str r6, [r2, r5]             // 5156 str r6, [r2, r5]
str r7, [r2, r5]             // 5157 str r7, [r2, r5]
str r0, [r3, r5]             // 5158 str r0, [r3, r5]
str r1, [r3, r5]             // 5159 str r1, [r3, r5]
str r2, [r3, r5]             // 515a str r2, [r3, r5]
str r3, [r3, r5]             // 515b str r3, [r3, r5]
str r4, [r3, r5]             // 515c str r4, [r3, r5]
str r5, [r3, r5]             // 515d str r5, [r3, r5]
str r6, [r3, r5]             // 515e str r6, [r3, r5]
str r7, [r3, r5]             // 515f str r7, [r3, r5]
str r0, [r4, r5]             // 5160 str r0, [r4, r5]
str r1, [r4, r5]             // 5161 str r1, [r4, r5]
str r2, [r4, r5]             // 5162 str r2, [r4, r5]
str r3, [r4, r5]             // 5163 str r3, [r4, r5]
str r4, [r4, r5]             // 5164 str r4, [r4, r5]
str r5, [r4, r5]             // 5165 str r5, [r4, r5]
str r6, [r4, r5]             // 5166 str r6, [r4, r5]
str r7, [r4, r5]             // 5167 str r7, [r4, r5]
str r0, [r5, r5]             // 5168 str r0, [r5, r5]
str r1, [r5, r5]             // 5169 str r1, [r5, r5]
str r2, [r5, r5]             // 516a str r2, [r5, r5]
str r3, [r5, r5]             // 516b str r3, [r5, r5]
str r4, [r5, r5]             // 516c str r4, [r5, r5]
str r5, [r5, r5]             // 516d str r5, [r5, r5]
str r6, [r5, r5]             // 516e str r6, [r5, r5]
str r7, [r5, r5]             // 516f str r7, [r5, r5]
str r0, [r6, r5]             // 5170 str r0, [r6, r5]
str r1, [r6, r5]             // 5171 str r1, [r6, r5]
str r2, [r6, r5]             // 5172 str r2, [r6, r5]
str r3, [r6, r5]             // 5173 str r3, [r6, r5]
str r4, [r6, r5]             // 5174 str r4, [r6, r5]
str r5, [r6, r5]             // 5175 str r5, [r6, r5]
str r6, [r6, r5]             // 5176 str r6, [r6, r5]
str r7, [r6, r5]             // 5177 str r7, [r6, r5]
str r0, [r7, r5]             // 5178 str r0, [r7, r5]
str r1, [r7, r5]             // 5179 str r1, [r7, r5]
str r2, [r7, r5]             // 517a str r2, [r7, r5]
str r3, [r7, r5]             // 517b str r3, [r7, r5]
str r4, [r7, r5]             // 517c str r4, [r7, r5]
str r5, [r7, r5]             // 517d str r5, [r7, r5]
str r6, [r7, r5]             // 517e str r6, [r7, r5]
str r7, [r7, r5]             // 517f str r7, [r7, r5]
str r0, [r0, r6]             // 5180 str r0, [r0, r6]
str r1, [r0, r6]             // 5181 str r1, [r0, r6]
str r2, [r0, r6]             // 5182 str r2, [r0, r6]
str r3, [r0, r6]             // 5183 str r3, [r0, r6]
str r4, [r0, r6]             // 5184 str r4, [r0, r6]
str r5, [r0, r6]             // 5185 str r5, [r0, r6]
str r6, [r0, r6]             // 5186 str r6, [r0, r6]
str r7, [r0, r6]             // 5187 str r7, [r0, r6]
str r0, [r1, r6]             // 5188 str r0, [r1, r6]
str r1, [r1, r6]             // 5189 str r1, [r1, r6]
str r2, [r1, r6]             // 518a str r2, [r1, r6]
str r3, [r1, r6]             // 518b str r3, [r1, r6]
str r4, [r1, r6]             // 518c str r4, [r1, r6]
str r5, [r1, r6]             // 518d str r5, [r1, r6]
str r6, [r1, r6]             // 518e str r6, [r1, r6]
str r7, [r1, r6]             // 518f str r7, [r1, r6]
str r0, [r2, r6]             // 5190 str r0, [r2, r6]
str r1, [r2, r6]             // 5191 str r1, [r2, r6]
str r2, [r2, r6]             // 5192 str r2, [r2, r6]
str r3, [r2, r6]             // 5193 str r3, [r2, r6]
str r4, [r2, r6]             // 5194 str r4, [r2, r6]
str r5, [r2, r6]             // 5195 str r5, [r2, r6]
str r6, [r2, r6]             // 5196 str r6, [r2, r6]
str r7, [r2, r6]             // 5197 str r7, [r2, r6]
str r0, [r3, r6]             // 5198 str r0, [r3, r6]
str r1, [r3, r6]             // 5199 str r1, [r3, r6]
str r2, [r3, r6]             // 519a str r2, [r3, r6]
str r3, [r3, r6]             // 519b str r3, [r3, r6]
str r4, [r3, r6]             // 519c str r4, [r3, r6]
str r5, [r3, r6]             // 519d str r5, [r3, r6]
str r6, [r3, r6]             // 519e str r6, [r3, r6]
str r7, [r3, r6]             // 519f str r7, [r3, r6]
str r0, [r4, r6]             // 51a0 str r0, [r4, r6]
str r1, [r4, r6]             // 51a1 str r1, [r4, r6]
str r2, [r4, r6]             // 51a2 str r2, [r4, r6]
str r3, [r4, r6]             // 51a3 str r3, [r4, r6]
str r4, [r4, r6]             // 51a4 str r4, [r4, r6]
str r5, [r4, r6]             // 51a5 str r5, [r4, r6]
str r6, [r4, r6]             // 51a6 str r6, [r4, r6]
str r7, [r4, r6]             // 51a7 str r7, [r4, r6]
str r0, [r5, r6]             // 51a8 str r0, [r5, r6]
str r1, [r5, r6]             // 51a9 str r1, [r5, r6]
str r2, [r5, r6]             // 51aa str r2, [r5, r6]
str r3, [r5, r6]             // 51ab str r3, [r5, r6]
str r4, [r5, r6]             // 51ac str r4, [r5, r6]
str r5, [r5, r6]             // 51ad str r5, [r5, r6]
str r6, [r5, r6]             // 51ae str r6, [r5, r6]
str r7, [r5, r6]             // 51af str r7, [r5, r6]
str r0, [r6, r6]             // 51b0 str r0, [r6, r6]
str r1, [r6, r6]             // 51b1 str r1, [r6, r6]
str r2, [r6, r6]             // 51b2 str r2, [r6, r6]
str r3, [r6, r6]             // 51b3 str r3, [r6, r6]
str r4, [r6, r6]             // 51b4 str r4, [r6, r6]
str r5, [r6, r6]             // 51b5 str r5, [r6, r6]
str r6, [r6, r6]             // 51b6 str r6, [r6, r6]
str r7, [r6, r6]             // 51b7 str r7, [r6, r6]
str r0, [r7, r6]             // 51b8 str r0, [r7, r6]
str r1, [r7, r6]             // 51b9 str r1, [r7, r6]
str r2, [r7, r6]             // 51ba str r2, [r7, r6]
str r3, [r7, r6]             // 51bb str r3, [r7, r6]
str r4, [r7, r6]             // 51bc str r4, [r7, r6]
str r5, [r7, r6]             // 51bd str r5, [r7, r6]
str r6, [r7, r6]             // 51be str r6, [r7, r6]
str r7, [r7, r6]             // 51bf str r7, [r7, r6]
str r0, [r0, r7]             // 51c0 str r0, [r0, r7]
str r1, [r0, r7]             // 51c1 str r1, [r0, r7]
str r2, [r0, r7]             // 51c2 str r2, [r0, r7]
str r3, [r0, r7]             // 51c3 str r3, [r0, r7]
str r4, [r0, r7]             // 51c4 str r4, [r0, r7]
str r5, [r0, r7]             // 51c5 str r5, [r0, r7]
str r6, [r0, r7]             // 51c6 str r6, [r0, r7]
str r7, [r0, r7]             // 51c7 str r7, [r0, r7]
str r0, [r1, r7]             // 51c8 str r0, [r1, r7]
str r1, [r1, r7]             // 51c9 str r1, [r1, r7]
str r2, [r1, r7]             // 51ca str r2, [r1, r7]
str r3, [r1, r7]             // 51cb str r3, [r1, r7]
str r4, [r1, r7]             // 51cc str r4, [r1, r7]
str r5, [r1, r7]             // 51cd str r5, [r1, r7]
str r6, [r1, r7]             // 51ce str r6, [r1, r7]
str r7, [r1, r7]             // 51cf str r7, [r1, r7]
str r0, [r2, r7]             // 51d0 str r0, [r2, r7]
str r1, [r2, r7]             // 51d1 str r1, [r2, r7]
str r2, [r2, r7]             // 51d2 str r2, [r2, r7]
str r3, [r2, r7]             // 51d3 str r3, [r2, r7]
str r4, [r2, r7]             // 51d4 str r4, [r2, r7]
str r5, [r2, r7]             // 51d5 str r5, [r2, r7]
str r6, [r2, r7]             // 51d6 str r6, [r2, r7]
str r7, [r2, r7]             // 51d7 str r7, [r2, r7]
str r0, [r3, r7]             // 51d8 str r0, [r3, r7]
str r1, [r3, r7]             // 51d9 str r1, [r3, r7]
str r2, [r3, r7]             // 51da str r2, [r3, r7]
str r3, [r3, r7]             // 51db str r3, [r3, r7]
str r4, [r3, r7]             // 51dc str r4, [r3, r7]
str r5, [r3, r7]             // 51dd str r5, [r3, r7]
str r6, [r3, r7]             // 51de str r6, [r3, r7]
str r7, [r3, r7]             // 51df str r7, [r3, r7]
str r0, [r4, r7]             // 51e0 str r0, [r4, r7]
str r1, [r4, r7]             // 51e1 str r1, [r4, r7]
str r2, [r4, r7]             // 51e2 str r2, [r4, r7]
str r3, [r4, r7]             // 51e3 str r3, [r4, r7]
str r4, [r4, r7]             // 51e4 str r4, [r4, r7]
str r5, [r4, r7]             // 51e5 str r5, [r4, r7]
str r6, [r4, r7]             // 51e6 str r6, [r4, r7]
str r7, [r4, r7]             // 51e7 str r7, [r4, r7]
str r0, [r5, r7]             // 51e8 str r0, [r5, r7]
str r1, [r5, r7]             // 51e9 str r1, [r5, r7]
str r2, [r5, r7]             // 51ea str r2, [r5, r7]
str r3, [r5, r7]             // 51eb str r3, [r5, r7]
str r4, [r5, r7]             // 51ec str r4, [r5, r7]
str r5, [r5, r7]             // 51ed str r5, [r5, r7]
str r6, [r5, r7]             // 51ee str r6, [r5, r7]
str r7, [r5, r7]             // 51ef str r7, [r5, r7]
str r0, [r6, r7]             // 51f0 str r0, [r6, r7]
str r1, [r6, r7]             // 51f1 str r1, [r6, r7]
str r2, [r6, r7]             // 51f2 str r2, [r6, r7]
str r3, [r6, r7]             // 51f3 str r3, [r6, r7]
str r4, [r6, r7]             // 51f4 str r4, [r6, r7]
str r5, [r6, r7]             // 51f5 str r5, [r6, r7]
str r6, [r6, r7]             // 51f6 str r6, [r6, r7]
str r7, [r6, r7]             // 51f7 str r7, [r6, r7]
str r0, [r7, r7]             // 51f8 str r0, [r7, r7]
str r1, [r7, r7]             // 51f9 str r1, [r7, r7]
str r2, [r7, r7]             // 51fa str r2, [r7, r7]
str r3, [r7, r7]             // 51fb str r3, [r7, r7]
str r4, [r7, r7]             // 51fc str r4, [r7, r7]
str r5, [r7, r7]             // 51fd str r5, [r7, r7]
str r6, [r7, r7]             // 51fe str r6, [r7, r7]
str r7, [r7, r7]             // 51ff str r7, [r7, r7]

strh r0, [r0, r0]            // 5200 strh r0, [r0, r0]
strh r1, [r0, r0]            // 5201 strh r1, [r0, r0]
strh r2, [r0, r0]            // 5202 strh r2, [r0, r0]
strh r3, [r0, r0]            // 5203 strh r3, [r0, r0]
strh r4, [r0, r0]            // 5204 strh r4, [r0, r0]
strh r5, [r0, r0]            // 5205 strh r5, [r0, r0]
strh r6, [r0, r0]            // 5206 strh r6, [r0, r0]
strh r7, [r0, r0]            // 5207 strh r7, [r0, r0]
strh r0, [r1, r0]            // 5208 strh r0, [r1, r0]
strh r1, [r1, r0]            // 5209 strh r1, [r1, r0]
strh r2, [r1, r0]            // 520a strh r2, [r1, r0]
strh r3, [r1, r0]            // 520b strh r3, [r1, r0]
strh r4, [r1, r0]            // 520c strh r4, [r1, r0]
strh r5, [r1, r0]            // 520d strh r5, [r1, r0]
strh r6, [r1, r0]            // 520e strh r6, [r1, r0]
strh r7, [r1, r0]            // 520f strh r7, [r1, r0]
strh r0, [r2, r0]            // 5210 strh r0, [r2, r0]
strh r1, [r2, r0]            // 5211 strh r1, [r2, r0]
strh r2, [r2, r0]            // 5212 strh r2, [r2, r0]
strh r3, [r2, r0]            // 5213 strh r3, [r2, r0]
strh r4, [r2, r0]            // 5214 strh r4, [r2, r0]
strh r5, [r2, r0]            // 5215 strh r5, [r2, r0]
strh r6, [r2, r0]            // 5216 strh r6, [r2, r0]
strh r7, [r2, r0]            // 5217 strh r7, [r2, r0]
strh r0, [r3, r0]            // 5218 strh r0, [r3, r0]
strh r1, [r3, r0]            // 5219 strh r1, [r3, r0]
strh r2, [r3, r0]            // 521a strh r2, [r3, r0]
strh r3, [r3, r0]            // 521b strh r3, [r3, r0]
strh r4, [r3, r0]            // 521c strh r4, [r3, r0]
strh r5, [r3, r0]            // 521d strh r5, [r3, r0]
strh r6, [r3, r0]            // 521e strh r6, [r3, r0]
strh r7, [r3, r0]            // 521f strh r7, [r3, r0]
strh r0, [r4, r0]            // 5220 strh r0, [r4, r0]
strh r1, [r4, r0]            // 5221 strh r1, [r4, r0]
strh r2, [r4, r0]            // 5222 strh r2, [r4, r0]
strh r3, [r4, r0]            // 5223 strh r3, [r4, r0]
strh r4, [r4, r0]            // 5224 strh r4, [r4, r0]
strh r5, [r4, r0]            // 5225 strh r5, [r4, r0]
strh r6, [r4, r0]            // 5226 strh r6, [r4, r0]
strh r7, [r4, r0]            // 5227 strh r7, [r4, r0]
strh r0, [r5, r0]            // 5228 strh r0, [r5, r0]
strh r1, [r5, r0]            // 5229 strh r1, [r5, r0]
strh r2, [r5, r0]            // 522a strh r2, [r5, r0]
strh r3, [r5, r0]            // 522b strh r3, [r5, r0]
strh r4, [r5, r0]            // 522c strh r4, [r5, r0]
strh r5, [r5, r0]            // 522d strh r5, [r5, r0]
strh r6, [r5, r0]            // 522e strh r6, [r5, r0]
strh r7, [r5, r0]            // 522f strh r7, [r5, r0]
strh r0, [r6, r0]            // 5230 strh r0, [r6, r0]
strh r1, [r6, r0]            // 5231 strh r1, [r6, r0]
strh r2, [r6, r0]            // 5232 strh r2, [r6, r0]
strh r3, [r6, r0]            // 5233 strh r3, [r6, r0]
strh r4, [r6, r0]            // 5234 strh r4, [r6, r0]
strh r5, [r6, r0]            // 5235 strh r5, [r6, r0]
strh r6, [r6, r0]            // 5236 strh r6, [r6, r0]
strh r7, [r6, r0]            // 5237 strh r7, [r6, r0]
strh r0, [r7, r0]            // 5238 strh r0, [r7, r0]
strh r1, [r7, r0]            // 5239 strh r1, [r7, r0]
strh r2, [r7, r0]            // 523a strh r2, [r7, r0]
strh r3, [r7, r0]            // 523b strh r3, [r7, r0]
strh r4, [r7, r0]            // 523c strh r4, [r7, r0]
strh r5, [r7, r0]            // 523d strh r5, [r7, r0]
strh r6, [r7, r0]            // 523e strh r6, [r7, r0]
strh r7, [r7, r0]            // 523f strh r7, [r7, r0]
strh r0, [r0, r1]            // 5240 strh r0, [r0, r1]
strh r1, [r0, r1]            // 5241 strh r1, [r0, r1]
strh r2, [r0, r1]            // 5242 strh r2, [r0, r1]
strh r3, [r0, r1]            // 5243 strh r3, [r0, r1]
strh r4, [r0, r1]            // 5244 strh r4, [r0, r1]
strh r5, [r0, r1]            // 5245 strh r5, [r0, r1]
strh r6, [r0, r1]            // 5246 strh r6, [r0, r1]
strh r7, [r0, r1]            // 5247 strh r7, [r0, r1]
strh r0, [r1, r1]            // 5248 strh r0, [r1, r1]
strh r1, [r1, r1]            // 5249 strh r1, [r1, r1]
strh r2, [r1, r1]            // 524a strh r2, [r1, r1]
strh r3, [r1, r1]            // 524b strh r3, [r1, r1]
strh r4, [r1, r1]            // 524c strh r4, [r1, r1]
strh r5, [r1, r1]            // 524d strh r5, [r1, r1]
strh r6, [r1, r1]            // 524e strh r6, [r1, r1]
strh r7, [r1, r1]            // 524f strh r7, [r1, r1]
strh r0, [r2, r1]            // 5250 strh r0, [r2, r1]
strh r1, [r2, r1]            // 5251 strh r1, [r2, r1]
strh r2, [r2, r1]            // 5252 strh r2, [r2, r1]
strh r3, [r2, r1]            // 5253 strh r3, [r2, r1]
strh r4, [r2, r1]            // 5254 strh r4, [r2, r1]
strh r5, [r2, r1]            // 5255 strh r5, [r2, r1]
strh r6, [r2, r1]            // 5256 strh r6, [r2, r1]
strh r7, [r2, r1]            // 5257 strh r7, [r2, r1]
strh r0, [r3, r1]            // 5258 strh r0, [r3, r1]
strh r1, [r3, r1]            // 5259 strh r1, [r3, r1]
strh r2, [r3, r1]            // 525a strh r2, [r3, r1]
strh r3, [r3, r1]            // 525b strh r3, [r3, r1]
strh r4, [r3, r1]            // 525c strh r4, [r3, r1]
strh r5, [r3, r1]            // 525d strh r5, [r3, r1]
strh r6, [r3, r1]            // 525e strh r6, [r3, r1]
strh r7, [r3, r1]            // 525f strh r7, [r3, r1]
strh r0, [r4, r1]            // 5260 strh r0, [r4, r1]
strh r1, [r4, r1]            // 5261 strh r1, [r4, r1]
strh r2, [r4, r1]            // 5262 strh r2, [r4, r1]
strh r3, [r4, r1]            // 5263 strh r3, [r4, r1]
strh r4, [r4, r1]            // 5264 strh r4, [r4, r1]
strh r5, [r4, r1]            // 5265 strh r5, [r4, r1]
strh r6, [r4, r1]            // 5266 strh r6, [r4, r1]
strh r7, [r4, r1]            // 5267 strh r7, [r4, r1]
strh r0, [r5, r1]            // 5268 strh r0, [r5, r1]
strh r1, [r5, r1]            // 5269 strh r1, [r5, r1]
strh r2, [r5, r1]            // 526a strh r2, [r5, r1]
strh r3, [r5, r1]            // 526b strh r3, [r5, r1]
strh r4, [r5, r1]            // 526c strh r4, [r5, r1]
strh r5, [r5, r1]            // 526d strh r5, [r5, r1]
strh r6, [r5, r1]            // 526e strh r6, [r5, r1]
strh r7, [r5, r1]            // 526f strh r7, [r5, r1]
strh r0, [r6, r1]            // 5270 strh r0, [r6, r1]
strh r1, [r6, r1]            // 5271 strh r1, [r6, r1]
strh r2, [r6, r1]            // 5272 strh r2, [r6, r1]
strh r3, [r6, r1]            // 5273 strh r3, [r6, r1]
strh r4, [r6, r1]            // 5274 strh r4, [r6, r1]
strh r5, [r6, r1]            // 5275 strh r5, [r6, r1]
strh r6, [r6, r1]            // 5276 strh r6, [r6, r1]
strh r7, [r6, r1]            // 5277 strh r7, [r6, r1]
strh r0, [r7, r1]            // 5278 strh r0, [r7, r1]
strh r1, [r7, r1]            // 5279 strh r1, [r7, r1]
strh r2, [r7, r1]            // 527a strh r2, [r7, r1]
strh r3, [r7, r1]            // 527b strh r3, [r7, r1]
strh r4, [r7, r1]            // 527c strh r4, [r7, r1]
strh r5, [r7, r1]            // 527d strh r5, [r7, r1]
strh r6, [r7, r1]            // 527e strh r6, [r7, r1]
strh r7, [r7, r1]            // 527f strh r7, [r7, r1]
strh r0, [r0, r2]            // 5280 strh r0, [r0, r2]
strh r1, [r0, r2]            // 5281 strh r1, [r0, r2]
strh r2, [r0, r2]            // 5282 strh r2, [r0, r2]
strh r3, [r0, r2]            // 5283 strh r3, [r0, r2]
strh r4, [r0, r2]            // 5284 strh r4, [r0, r2]
strh r5, [r0, r2]            // 5285 strh r5, [r0, r2]
strh r6, [r0, r2]            // 5286 strh r6, [r0, r2]
strh r7, [r0, r2]            // 5287 strh r7, [r0, r2]
strh r0, [r1, r2]            // 5288 strh r0, [r1, r2]
strh r1, [r1, r2]            // 5289 strh r1, [r1, r2]
strh r2, [r1, r2]            // 528a strh r2, [r1, r2]
strh r3, [r1, r2]            // 528b strh r3, [r1, r2]
strh r4, [r1, r2]            // 528c strh r4, [r1, r2]
strh r5, [r1, r2]            // 528d strh r5, [r1, r2]
strh r6, [r1, r2]            // 528e strh r6, [r1, r2]
strh r7, [r1, r2]            // 528f strh r7, [r1, r2]
strh r0, [r2, r2]            // 5290 strh r0, [r2, r2]
strh r1, [r2, r2]            // 5291 strh r1, [r2, r2]
strh r2, [r2, r2]            // 5292 strh r2, [r2, r2]
strh r3, [r2, r2]            // 5293 strh r3, [r2, r2]
strh r4, [r2, r2]            // 5294 strh r4, [r2, r2]
strh r5, [r2, r2]            // 5295 strh r5, [r2, r2]
strh r6, [r2, r2]            // 5296 strh r6, [r2, r2]
strh r7, [r2, r2]            // 5297 strh r7, [r2, r2]
strh r0, [r3, r2]            // 5298 strh r0, [r3, r2]
strh r1, [r3, r2]            // 5299 strh r1, [r3, r2]
strh r2, [r3, r2]            // 529a strh r2, [r3, r2]
strh r3, [r3, r2]            // 529b strh r3, [r3, r2]
strh r4, [r3, r2]            // 529c strh r4, [r3, r2]
strh r5, [r3, r2]            // 529d strh r5, [r3, r2]
strh r6, [r3, r2]            // 529e strh r6, [r3, r2]
strh r7, [r3, r2]            // 529f strh r7, [r3, r2]
strh r0, [r4, r2]            // 52a0 strh r0, [r4, r2]
strh r1, [r4, r2]            // 52a1 strh r1, [r4, r2]
strh r2, [r4, r2]            // 52a2 strh r2, [r4, r2]
strh r3, [r4, r2]            // 52a3 strh r3, [r4, r2]
strh r4, [r4, r2]            // 52a4 strh r4, [r4, r2]
strh r5, [r4, r2]            // 52a5 strh r5, [r4, r2]
strh r6, [r4, r2]            // 52a6 strh r6, [r4, r2]
strh r7, [r4, r2]            // 52a7 strh r7, [r4, r2]
strh r0, [r5, r2]            // 52a8 strh r0, [r5, r2]
strh r1, [r5, r2]            // 52a9 strh r1, [r5, r2]
strh r2, [r5, r2]            // 52aa strh r2, [r5, r2]
strh r3, [r5, r2]            // 52ab strh r3, [r5, r2]
strh r4, [r5, r2]            // 52ac strh r4, [r5, r2]
strh r5, [r5, r2]            // 52ad strh r5, [r5, r2]
strh r6, [r5, r2]            // 52ae strh r6, [r5, r2]
strh r7, [r5, r2]            // 52af strh r7, [r5, r2]
strh r0, [r6, r2]            // 52b0 strh r0, [r6, r2]
strh r1, [r6, r2]            // 52b1 strh r1, [r6, r2]
strh r2, [r6, r2]            // 52b2 strh r2, [r6, r2]
strh r3, [r6, r2]            // 52b3 strh r3, [r6, r2]
strh r4, [r6, r2]            // 52b4 strh r4, [r6, r2]
strh r5, [r6, r2]            // 52b5 strh r5, [r6, r2]
strh r6, [r6, r2]            // 52b6 strh r6, [r6, r2]
strh r7, [r6, r2]            // 52b7 strh r7, [r6, r2]
strh r0, [r7, r2]            // 52b8 strh r0, [r7, r2]
strh r1, [r7, r2]            // 52b9 strh r1, [r7, r2]
strh r2, [r7, r2]            // 52ba strh r2, [r7, r2]
strh r3, [r7, r2]            // 52bb strh r3, [r7, r2]
strh r4, [r7, r2]            // 52bc strh r4, [r7, r2]
strh r5, [r7, r2]            // 52bd strh r5, [r7, r2]
strh r6, [r7, r2]            // 52be strh r6, [r7, r2]
strh r7, [r7, r2]            // 52bf strh r7, [r7, r2]
strh r0, [r0, r3]            // 52c0 strh r0, [r0, r3]
strh r1, [r0, r3]            // 52c1 strh r1, [r0, r3]
strh r2, [r0, r3]            // 52c2 strh r2, [r0, r3]
strh r3, [r0, r3]            // 52c3 strh r3, [r0, r3]
strh r4, [r0, r3]            // 52c4 strh r4, [r0, r3]
strh r5, [r0, r3]            // 52c5 strh r5, [r0, r3]
strh r6, [r0, r3]            // 52c6 strh r6, [r0, r3]
strh r7, [r0, r3]            // 52c7 strh r7, [r0, r3]
strh r0, [r1, r3]            // 52c8 strh r0, [r1, r3]
strh r1, [r1, r3]            // 52c9 strh r1, [r1, r3]
strh r2, [r1, r3]            // 52ca strh r2, [r1, r3]
strh r3, [r1, r3]            // 52cb strh r3, [r1, r3]
strh r4, [r1, r3]            // 52cc strh r4, [r1, r3]
strh r5, [r1, r3]            // 52cd strh r5, [r1, r3]
strh r6, [r1, r3]            // 52ce strh r6, [r1, r3]
strh r7, [r1, r3]            // 52cf strh r7, [r1, r3]
strh r0, [r2, r3]            // 52d0 strh r0, [r2, r3]
strh r1, [r2, r3]            // 52d1 strh r1, [r2, r3]
strh r2, [r2, r3]            // 52d2 strh r2, [r2, r3]
strh r3, [r2, r3]            // 52d3 strh r3, [r2, r3]
strh r4, [r2, r3]            // 52d4 strh r4, [r2, r3]
strh r5, [r2, r3]            // 52d5 strh r5, [r2, r3]
strh r6, [r2, r3]            // 52d6 strh r6, [r2, r3]
strh r7, [r2, r3]            // 52d7 strh r7, [r2, r3]
strh r0, [r3, r3]            // 52d8 strh r0, [r3, r3]
strh r1, [r3, r3]            // 52d9 strh r1, [r3, r3]
strh r2, [r3, r3]            // 52da strh r2, [r3, r3]
strh r3, [r3, r3]            // 52db strh r3, [r3, r3]
strh r4, [r3, r3]            // 52dc strh r4, [r3, r3]
strh r5, [r3, r3]            // 52dd strh r5, [r3, r3]
strh r6, [r3, r3]            // 52de strh r6, [r3, r3]
strh r7, [r3, r3]            // 52df strh r7, [r3, r3]
strh r0, [r4, r3]            // 52e0 strh r0, [r4, r3]
strh r1, [r4, r3]            // 52e1 strh r1, [r4, r3]
strh r2, [r4, r3]            // 52e2 strh r2, [r4, r3]
strh r3, [r4, r3]            // 52e3 strh r3, [r4, r3]
strh r4, [r4, r3]            // 52e4 strh r4, [r4, r3]
strh r5, [r4, r3]            // 52e5 strh r5, [r4, r3]
strh r6, [r4, r3]            // 52e6 strh r6, [r4, r3]
strh r7, [r4, r3]            // 52e7 strh r7, [r4, r3]
strh r0, [r5, r3]            // 52e8 strh r0, [r5, r3]
strh r1, [r5, r3]            // 52e9 strh r1, [r5, r3]
strh r2, [r5, r3]            // 52ea strh r2, [r5, r3]
strh r3, [r5, r3]            // 52eb strh r3, [r5, r3]
strh r4, [r5, r3]            // 52ec strh r4, [r5, r3]
strh r5, [r5, r3]            // 52ed strh r5, [r5, r3]
strh r6, [r5, r3]            // 52ee strh r6, [r5, r3]
strh r7, [r5, r3]            // 52ef strh r7, [r5, r3]
strh r0, [r6, r3]            // 52f0 strh r0, [r6, r3]
strh r1, [r6, r3]            // 52f1 strh r1, [r6, r3]
strh r2, [r6, r3]            // 52f2 strh r2, [r6, r3]
strh r3, [r6, r3]            // 52f3 strh r3, [r6, r3]
strh r4, [r6, r3]            // 52f4 strh r4, [r6, r3]
strh r5, [r6, r3]            // 52f5 strh r5, [r6, r3]
strh r6, [r6, r3]            // 52f6 strh r6, [r6, r3]
strh r7, [r6, r3]            // 52f7 strh r7, [r6, r3]
strh r0, [r7, r3]            // 52f8 strh r0, [r7, r3]
strh r1, [r7, r3]            // 52f9 strh r1, [r7, r3]
strh r2, [r7, r3]            // 52fa strh r2, [r7, r3]
strh r3, [r7, r3]            // 52fb strh r3, [r7, r3]
strh r4, [r7, r3]            // 52fc strh r4, [r7, r3]
strh r5, [r7, r3]            // 52fd strh r5, [r7, r3]
strh r6, [r7, r3]            // 52fe strh r6, [r7, r3]
strh r7, [r7, r3]            // 52ff strh r7, [r7, r3]
strh r0, [r0, r4]            // 5300 strh r0, [r0, r4]
strh r1, [r0, r4]            // 5301 strh r1, [r0, r4]
strh r2, [r0, r4]            // 5302 strh r2, [r0, r4]
strh r3, [r0, r4]            // 5303 strh r3, [r0, r4]
strh r4, [r0, r4]            // 5304 strh r4, [r0, r4]
strh r5, [r0, r4]            // 5305 strh r5, [r0, r4]
strh r6, [r0, r4]            // 5306 strh r6, [r0, r4]
strh r7, [r0, r4]            // 5307 strh r7, [r0, r4]
strh r0, [r1, r4]            // 5308 strh r0, [r1, r4]
strh r1, [r1, r4]            // 5309 strh r1, [r1, r4]
strh r2, [r1, r4]            // 530a strh r2, [r1, r4]
strh r3, [r1, r4]            // 530b strh r3, [r1, r4]
strh r4, [r1, r4]            // 530c strh r4, [r1, r4]
strh r5, [r1, r4]            // 530d strh r5, [r1, r4]
strh r6, [r1, r4]            // 530e strh r6, [r1, r4]
strh r7, [r1, r4]            // 530f strh r7, [r1, r4]
strh r0, [r2, r4]            // 5310 strh r0, [r2, r4]
strh r1, [r2, r4]            // 5311 strh r1, [r2, r4]
strh r2, [r2, r4]            // 5312 strh r2, [r2, r4]
strh r3, [r2, r4]            // 5313 strh r3, [r2, r4]
strh r4, [r2, r4]            // 5314 strh r4, [r2, r4]
strh r5, [r2, r4]            // 5315 strh r5, [r2, r4]
strh r6, [r2, r4]            // 5316 strh r6, [r2, r4]
strh r7, [r2, r4]            // 5317 strh r7, [r2, r4]
strh r0, [r3, r4]            // 5318 strh r0, [r3, r4]
strh r1, [r3, r4]            // 5319 strh r1, [r3, r4]
strh r2, [r3, r4]            // 531a strh r2, [r3, r4]
strh r3, [r3, r4]            // 531b strh r3, [r3, r4]
strh r4, [r3, r4]            // 531c strh r4, [r3, r4]
strh r5, [r3, r4]            // 531d strh r5, [r3, r4]
strh r6, [r3, r4]            // 531e strh r6, [r3, r4]
strh r7, [r3, r4]            // 531f strh r7, [r3, r4]
strh r0, [r4, r4]            // 5320 strh r0, [r4, r4]
strh r1, [r4, r4]            // 5321 strh r1, [r4, r4]
strh r2, [r4, r4]            // 5322 strh r2, [r4, r4]
strh r3, [r4, r4]            // 5323 strh r3, [r4, r4]
strh r4, [r4, r4]            // 5324 strh r4, [r4, r4]
strh r5, [r4, r4]            // 5325 strh r5, [r4, r4]
strh r6, [r4, r4]            // 5326 strh r6, [r4, r4]
strh r7, [r4, r4]            // 5327 strh r7, [r4, r4]
strh r0, [r5, r4]            // 5328 strh r0, [r5, r4]
strh r1, [r5, r4]            // 5329 strh r1, [r5, r4]
strh r2, [r5, r4]            // 532a strh r2, [r5, r4]
strh r3, [r5, r4]            // 532b strh r3, [r5, r4]
strh r4, [r5, r4]            // 532c strh r4, [r5, r4]
strh r5, [r5, r4]            // 532d strh r5, [r5, r4]
strh r6, [r5, r4]            // 532e strh r6, [r5, r4]
strh r7, [r5, r4]            // 532f strh r7, [r5, r4]
strh r0, [r6, r4]            // 5330 strh r0, [r6, r4]
strh r1, [r6, r4]            // 5331 strh r1, [r6, r4]
strh r2, [r6, r4]            // 5332 strh r2, [r6, r4]
strh r3, [r6, r4]            // 5333 strh r3, [r6, r4]
strh r4, [r6, r4]            // 5334 strh r4, [r6, r4]
strh r5, [r6, r4]            // 5335 strh r5, [r6, r4]
strh r6, [r6, r4]            // 5336 strh r6, [r6, r4]
strh r7, [r6, r4]            // 5337 strh r7, [r6, r4]
strh r0, [r7, r4]            // 5338 strh r0, [r7, r4]
strh r1, [r7, r4]            // 5339 strh r1, [r7, r4]
strh r2, [r7, r4]            // 533a strh r2, [r7, r4]
strh r3, [r7, r4]            // 533b strh r3, [r7, r4]
strh r4, [r7, r4]            // 533c strh r4, [r7, r4]
strh r5, [r7, r4]            // 533d strh r5, [r7, r4]
strh r6, [r7, r4]            // 533e strh r6, [r7, r4]
strh r7, [r7, r4]            // 533f strh r7, [r7, r4]
strh r0, [r0, r5]            // 5340 strh r0, [r0, r5]
strh r1, [r0, r5]            // 5341 strh r1, [r0, r5]
strh r2, [r0, r5]            // 5342 strh r2, [r0, r5]
strh r3, [r0, r5]            // 5343 strh r3, [r0, r5]
strh r4, [r0, r5]            // 5344 strh r4, [r0, r5]
strh r5, [r0, r5]            // 5345 strh r5, [r0, r5]
strh r6, [r0, r5]            // 5346 strh r6, [r0, r5]
strh r7, [r0, r5]            // 5347 strh r7, [r0, r5]
strh r0, [r1, r5]            // 5348 strh r0, [r1, r5]
strh r1, [r1, r5]            // 5349 strh r1, [r1, r5]
strh r2, [r1, r5]            // 534a strh r2, [r1, r5]
strh r3, [r1, r5]            // 534b strh r3, [r1, r5]
strh r4, [r1, r5]            // 534c strh r4, [r1, r5]
strh r5, [r1, r5]            // 534d strh r5, [r1, r5]
strh r6, [r1, r5]            // 534e strh r6, [r1, r5]
strh r7, [r1, r5]            // 534f strh r7, [r1, r5]
strh r0, [r2, r5]            // 5350 strh r0, [r2, r5]
strh r1, [r2, r5]            // 5351 strh r1, [r2, r5]
strh r2, [r2, r5]            // 5352 strh r2, [r2, r5]
strh r3, [r2, r5]            // 5353 strh r3, [r2, r5]
strh r4, [r2, r5]            // 5354 strh r4, [r2, r5]
strh r5, [r2, r5]            // 5355 strh r5, [r2, r5]
strh r6, [r2, r5]            // 5356 strh r6, [r2, r5]
strh r7, [r2, r5]            // 5357 strh r7, [r2, r5]
strh r0, [r3, r5]            // 5358 strh r0, [r3, r5]
strh r1, [r3, r5]            // 5359 strh r1, [r3, r5]
strh r2, [r3, r5]            // 535a strh r2, [r3, r5]
strh r3, [r3, r5]            // 535b strh r3, [r3, r5]
strh r4, [r3, r5]            // 535c strh r4, [r3, r5]
strh r5, [r3, r5]            // 535d strh r5, [r3, r5]
strh r6, [r3, r5]            // 535e strh r6, [r3, r5]
strh r7, [r3, r5]            // 535f strh r7, [r3, r5]
strh r0, [r4, r5]            // 5360 strh r0, [r4, r5]
strh r1, [r4, r5]            // 5361 strh r1, [r4, r5]
strh r2, [r4, r5]            // 5362 strh r2, [r4, r5]
strh r3, [r4, r5]            // 5363 strh r3, [r4, r5]
strh r4, [r4, r5]            // 5364 strh r4, [r4, r5]
strh r5, [r4, r5]            // 5365 strh r5, [r4, r5]
strh r6, [r4, r5]            // 5366 strh r6, [r4, r5]
strh r7, [r4, r5]            // 5367 strh r7, [r4, r5]
strh r0, [r5, r5]            // 5368 strh r0, [r5, r5]
strh r1, [r5, r5]            // 5369 strh r1, [r5, r5]
strh r2, [r5, r5]            // 536a strh r2, [r5, r5]
strh r3, [r5, r5]            // 536b strh r3, [r5, r5]
strh r4, [r5, r5]            // 536c strh r4, [r5, r5]
strh r5, [r5, r5]            // 536d strh r5, [r5, r5]
strh r6, [r5, r5]            // 536e strh r6, [r5, r5]
strh r7, [r5, r5]            // 536f strh r7, [r5, r5]
strh r0, [r6, r5]            // 5370 strh r0, [r6, r5]
strh r1, [r6, r5]            // 5371 strh r1, [r6, r5]
strh r2, [r6, r5]            // 5372 strh r2, [r6, r5]
strh r3, [r6, r5]            // 5373 strh r3, [r6, r5]
strh r4, [r6, r5]            // 5374 strh r4, [r6, r5]
strh r5, [r6, r5]            // 5375 strh r5, [r6, r5]
strh r6, [r6, r5]            // 5376 strh r6, [r6, r5]
strh r7, [r6, r5]            // 5377 strh r7, [r6, r5]
strh r0, [r7, r5]            // 5378 strh r0, [r7, r5]
strh r1, [r7, r5]            // 5379 strh r1, [r7, r5]
strh r2, [r7, r5]            // 537a strh r2, [r7, r5]
strh r3, [r7, r5]            // 537b strh r3, [r7, r5]
strh r4, [r7, r5]            // 537c strh r4, [r7, r5]
strh r5, [r7, r5]            // 537d strh r5, [r7, r5]
strh r6, [r7, r5]            // 537e strh r6, [r7, r5]
strh r7, [r7, r5]            // 537f strh r7, [r7, r5]
strh r0, [r0, r6]            // 5380 strh r0, [r0, r6]
strh r1, [r0, r6]            // 5381 strh r1, [r0, r6]
strh r2, [r0, r6]            // 5382 strh r2, [r0, r6]
strh r3, [r0, r6]            // 5383 strh r3, [r0, r6]
strh r4, [r0, r6]            // 5384 strh r4, [r0, r6]
strh r5, [r0, r6]            // 5385 strh r5, [r0, r6]
strh r6, [r0, r6]            // 5386 strh r6, [r0, r6]
strh r7, [r0, r6]            // 5387 strh r7, [r0, r6]
strh r0, [r1, r6]            // 5388 strh r0, [r1, r6]
strh r1, [r1, r6]            // 5389 strh r1, [r1, r6]
strh r2, [r1, r6]            // 538a strh r2, [r1, r6]
strh r3, [r1, r6]            // 538b strh r3, [r1, r6]
strh r4, [r1, r6]            // 538c strh r4, [r1, r6]
strh r5, [r1, r6]            // 538d strh r5, [r1, r6]
strh r6, [r1, r6]            // 538e strh r6, [r1, r6]
strh r7, [r1, r6]            // 538f strh r7, [r1, r6]
strh r0, [r2, r6]            // 5390 strh r0, [r2, r6]
strh r1, [r2, r6]            // 5391 strh r1, [r2, r6]
strh r2, [r2, r6]            // 5392 strh r2, [r2, r6]
strh r3, [r2, r6]            // 5393 strh r3, [r2, r6]
strh r4, [r2, r6]            // 5394 strh r4, [r2, r6]
strh r5, [r2, r6]            // 5395 strh r5, [r2, r6]
strh r6, [r2, r6]            // 5396 strh r6, [r2, r6]
strh r7, [r2, r6]            // 5397 strh r7, [r2, r6]
strh r0, [r3, r6]            // 5398 strh r0, [r3, r6]
strh r1, [r3, r6]            // 5399 strh r1, [r3, r6]
strh r2, [r3, r6]            // 539a strh r2, [r3, r6]
strh r3, [r3, r6]            // 539b strh r3, [r3, r6]
strh r4, [r3, r6]            // 539c strh r4, [r3, r6]
strh r5, [r3, r6]            // 539d strh r5, [r3, r6]
strh r6, [r3, r6]            // 539e strh r6, [r3, r6]
strh r7, [r3, r6]            // 539f strh r7, [r3, r6]
strh r0, [r4, r6]            // 53a0 strh r0, [r4, r6]
strh r1, [r4, r6]            // 53a1 strh r1, [r4, r6]
strh r2, [r4, r6]            // 53a2 strh r2, [r4, r6]
strh r3, [r4, r6]            // 53a3 strh r3, [r4, r6]
strh r4, [r4, r6]            // 53a4 strh r4, [r4, r6]
strh r5, [r4, r6]            // 53a5 strh r5, [r4, r6]
strh r6, [r4, r6]            // 53a6 strh r6, [r4, r6]
strh r7, [r4, r6]            // 53a7 strh r7, [r4, r6]
strh r0, [r5, r6]            // 53a8 strh r0, [r5, r6]
strh r1, [r5, r6]            // 53a9 strh r1, [r5, r6]
strh r2, [r5, r6]            // 53aa strh r2, [r5, r6]
strh r3, [r5, r6]            // 53ab strh r3, [r5, r6]
strh r4, [r5, r6]            // 53ac strh r4, [r5, r6]
strh r5, [r5, r6]            // 53ad strh r5, [r5, r6]
strh r6, [r5, r6]            // 53ae strh r6, [r5, r6]
strh r7, [r5, r6]            // 53af strh r7, [r5, r6]
strh r0, [r6, r6]            // 53b0 strh r0, [r6, r6]
strh r1, [r6, r6]            // 53b1 strh r1, [r6, r6]
strh r2, [r6, r6]            // 53b2 strh r2, [r6, r6]
strh r3, [r6, r6]            // 53b3 strh r3, [r6, r6]
strh r4, [r6, r6]            // 53b4 strh r4, [r6, r6]
strh r5, [r6, r6]            // 53b5 strh r5, [r6, r6]
strh r6, [r6, r6]            // 53b6 strh r6, [r6, r6]
strh r7, [r6, r6]            // 53b7 strh r7, [r6, r6]
strh r0, [r7, r6]            // 53b8 strh r0, [r7, r6]
strh r1, [r7, r6]            // 53b9 strh r1, [r7, r6]
strh r2, [r7, r6]            // 53ba strh r2, [r7, r6]
strh r3, [r7, r6]            // 53bb strh r3, [r7, r6]
strh r4, [r7, r6]            // 53bc strh r4, [r7, r6]
strh r5, [r7, r6]            // 53bd strh r5, [r7, r6]
strh r6, [r7, r6]            // 53be strh r6, [r7, r6]
strh r7, [r7, r6]            // 53bf strh r7, [r7, r6]
strh r0, [r0, r7]            // 53c0 strh r0, [r0, r7]
strh r1, [r0, r7]            // 53c1 strh r1, [r0, r7]
strh r2, [r0, r7]            // 53c2 strh r2, [r0, r7]
strh r3, [r0, r7]            // 53c3 strh r3, [r0, r7]
strh r4, [r0, r7]            // 53c4 strh r4, [r0, r7]
strh r5, [r0, r7]            // 53c5 strh r5, [r0, r7]
strh r6, [r0, r7]            // 53c6 strh r6, [r0, r7]
strh r7, [r0, r7]            // 53c7 strh r7, [r0, r7]
strh r0, [r1, r7]            // 53c8 strh r0, [r1, r7]
strh r1, [r1, r7]            // 53c9 strh r1, [r1, r7]
strh r2, [r1, r7]            // 53ca strh r2, [r1, r7]
strh r3, [r1, r7]            // 53cb strh r3, [r1, r7]
strh r4, [r1, r7]            // 53cc strh r4, [r1, r7]
strh r5, [r1, r7]            // 53cd strh r5, [r1, r7]
strh r6, [r1, r7]            // 53ce strh r6, [r1, r7]
strh r7, [r1, r7]            // 53cf strh r7, [r1, r7]
strh r0, [r2, r7]            // 53d0 strh r0, [r2, r7]
strh r1, [r2, r7]            // 53d1 strh r1, [r2, r7]
strh r2, [r2, r7]            // 53d2 strh r2, [r2, r7]
strh r3, [r2, r7]            // 53d3 strh r3, [r2, r7]
strh r4, [r2, r7]            // 53d4 strh r4, [r2, r7]
strh r5, [r2, r7]            // 53d5 strh r5, [r2, r7]
strh r6, [r2, r7]            // 53d6 strh r6, [r2, r7]
strh r7, [r2, r7]            // 53d7 strh r7, [r2, r7]
strh r0, [r3, r7]            // 53d8 strh r0, [r3, r7]
strh r1, [r3, r7]            // 53d9 strh r1, [r3, r7]
strh r2, [r3, r7]            // 53da strh r2, [r3, r7]
strh r3, [r3, r7]            // 53db strh r3, [r3, r7]
strh r4, [r3, r7]            // 53dc strh r4, [r3, r7]
strh r5, [r3, r7]            // 53dd strh r5, [r3, r7]
strh r6, [r3, r7]            // 53de strh r6, [r3, r7]
strh r7, [r3, r7]            // 53df strh r7, [r3, r7]
strh r0, [r4, r7]            // 53e0 strh r0, [r4, r7]
strh r1, [r4, r7]            // 53e1 strh r1, [r4, r7]
strh r2, [r4, r7]            // 53e2 strh r2, [r4, r7]
strh r3, [r4, r7]            // 53e3 strh r3, [r4, r7]
strh r4, [r4, r7]            // 53e4 strh r4, [r4, r7]
strh r5, [r4, r7]            // 53e5 strh r5, [r4, r7]
strh r6, [r4, r7]            // 53e6 strh r6, [r4, r7]
strh r7, [r4, r7]            // 53e7 strh r7, [r4, r7]
strh r0, [r5, r7]            // 53e8 strh r0, [r5, r7]
strh r1, [r5, r7]            // 53e9 strh r1, [r5, r7]
strh r2, [r5, r7]            // 53ea strh r2, [r5, r7]
strh r3, [r5, r7]            // 53eb strh r3, [r5, r7]
strh r4, [r5, r7]            // 53ec strh r4, [r5, r7]
strh r5, [r5, r7]            // 53ed strh r5, [r5, r7]
strh r6, [r5, r7]            // 53ee strh r6, [r5, r7]
strh r7, [r5, r7]            // 53ef strh r7, [r5, r7]
strh r0, [r6, r7]            // 53f0 strh r0, [r6, r7]
strh r1, [r6, r7]            // 53f1 strh r1, [r6, r7]
strh r2, [r6, r7]            // 53f2 strh r2, [r6, r7]
strh r3, [r6, r7]            // 53f3 strh r3, [r6, r7]
strh r4, [r6, r7]            // 53f4 strh r4, [r6, r7]
strh r5, [r6, r7]            // 53f5 strh r5, [r6, r7]
strh r6, [r6, r7]            // 53f6 strh r6, [r6, r7]
strh r7, [r6, r7]            // 53f7 strh r7, [r6, r7]
strh r0, [r7, r7]            // 53f8 strh r0, [r7, r7]
strh r1, [r7, r7]            // 53f9 strh r1, [r7, r7]
strh r2, [r7, r7]            // 53fa strh r2, [r7, r7]
strh r3, [r7, r7]            // 53fb strh r3, [r7, r7]
strh r4, [r7, r7]            // 53fc strh r4, [r7, r7]
strh r5, [r7, r7]            // 53fd strh r5, [r7, r7]
strh r6, [r7, r7]            // 53fe strh r6, [r7, r7]
strh r7, [r7, r7]            // 53ff strh r7, [r7, r7]

strb r0, [r0, r0]            // 5400 strb r0, [r0, r0]
strb r1, [r0, r0]            // 5401 strb r1, [r0, r0]
strb r2, [r0, r0]            // 5402 strb r2, [r0, r0]
strb r3, [r0, r0]            // 5403 strb r3, [r0, r0]
strb r4, [r0, r0]            // 5404 strb r4, [r0, r0]
strb r5, [r0, r0]            // 5405 strb r5, [r0, r0]
strb r6, [r0, r0]            // 5406 strb r6, [r0, r0]
strb r7, [r0, r0]            // 5407 strb r7, [r0, r0]
strb r0, [r1, r0]            // 5408 strb r0, [r1, r0]
strb r1, [r1, r0]            // 5409 strb r1, [r1, r0]
strb r2, [r1, r0]            // 540a strb r2, [r1, r0]
strb r3, [r1, r0]            // 540b strb r3, [r1, r0]
strb r4, [r1, r0]            // 540c strb r4, [r1, r0]
strb r5, [r1, r0]            // 540d strb r5, [r1, r0]
strb r6, [r1, r0]            // 540e strb r6, [r1, r0]
strb r7, [r1, r0]            // 540f strb r7, [r1, r0]
strb r0, [r2, r0]            // 5410 strb r0, [r2, r0]
strb r1, [r2, r0]            // 5411 strb r1, [r2, r0]
strb r2, [r2, r0]            // 5412 strb r2, [r2, r0]
strb r3, [r2, r0]            // 5413 strb r3, [r2, r0]
strb r4, [r2, r0]            // 5414 strb r4, [r2, r0]
strb r5, [r2, r0]            // 5415 strb r5, [r2, r0]
strb r6, [r2, r0]            // 5416 strb r6, [r2, r0]
strb r7, [r2, r0]            // 5417 strb r7, [r2, r0]
strb r0, [r3, r0]            // 5418 strb r0, [r3, r0]
strb r1, [r3, r0]            // 5419 strb r1, [r3, r0]
strb r2, [r3, r0]            // 541a strb r2, [r3, r0]
strb r3, [r3, r0]            // 541b strb r3, [r3, r0]
strb r4, [r3, r0]            // 541c strb r4, [r3, r0]
strb r5, [r3, r0]            // 541d strb r5, [r3, r0]
strb r6, [r3, r0]            // 541e strb r6, [r3, r0]
strb r7, [r3, r0]            // 541f strb r7, [r3, r0]
strb r0, [r4, r0]            // 5420 strb r0, [r4, r0]
strb r1, [r4, r0]            // 5421 strb r1, [r4, r0]
strb r2, [r4, r0]            // 5422 strb r2, [r4, r0]
strb r3, [r4, r0]            // 5423 strb r3, [r4, r0]
strb r4, [r4, r0]            // 5424 strb r4, [r4, r0]
strb r5, [r4, r0]            // 5425 strb r5, [r4, r0]
strb r6, [r4, r0]            // 5426 strb r6, [r4, r0]
strb r7, [r4, r0]            // 5427 strb r7, [r4, r0]
strb r0, [r5, r0]            // 5428 strb r0, [r5, r0]
strb r1, [r5, r0]            // 5429 strb r1, [r5, r0]
strb r2, [r5, r0]            // 542a strb r2, [r5, r0]
strb r3, [r5, r0]            // 542b strb r3, [r5, r0]
strb r4, [r5, r0]            // 542c strb r4, [r5, r0]
strb r5, [r5, r0]            // 542d strb r5, [r5, r0]
strb r6, [r5, r0]            // 542e strb r6, [r5, r0]
strb r7, [r5, r0]            // 542f strb r7, [r5, r0]
strb r0, [r6, r0]            // 5430 strb r0, [r6, r0]
strb r1, [r6, r0]            // 5431 strb r1, [r6, r0]
strb r2, [r6, r0]            // 5432 strb r2, [r6, r0]
strb r3, [r6, r0]            // 5433 strb r3, [r6, r0]
strb r4, [r6, r0]            // 5434 strb r4, [r6, r0]
strb r5, [r6, r0]            // 5435 strb r5, [r6, r0]
strb r6, [r6, r0]            // 5436 strb r6, [r6, r0]
strb r7, [r6, r0]            // 5437 strb r7, [r6, r0]
strb r0, [r7, r0]            // 5438 strb r0, [r7, r0]
strb r1, [r7, r0]            // 5439 strb r1, [r7, r0]
strb r2, [r7, r0]            // 543a strb r2, [r7, r0]
strb r3, [r7, r0]            // 543b strb r3, [r7, r0]
strb r4, [r7, r0]            // 543c strb r4, [r7, r0]
strb r5, [r7, r0]            // 543d strb r5, [r7, r0]
strb r6, [r7, r0]            // 543e strb r6, [r7, r0]
strb r7, [r7, r0]            // 543f strb r7, [r7, r0]
strb r0, [r0, r1]            // 5440 strb r0, [r0, r1]
strb r1, [r0, r1]            // 5441 strb r1, [r0, r1]
strb r2, [r0, r1]            // 5442 strb r2, [r0, r1]
strb r3, [r0, r1]            // 5443 strb r3, [r0, r1]
strb r4, [r0, r1]            // 5444 strb r4, [r0, r1]
strb r5, [r0, r1]            // 5445 strb r5, [r0, r1]
strb r6, [r0, r1]            // 5446 strb r6, [r0, r1]
strb r7, [r0, r1]            // 5447 strb r7, [r0, r1]
strb r0, [r1, r1]            // 5448 strb r0, [r1, r1]
strb r1, [r1, r1]            // 5449 strb r1, [r1, r1]
strb r2, [r1, r1]            // 544a strb r2, [r1, r1]
strb r3, [r1, r1]            // 544b strb r3, [r1, r1]
strb r4, [r1, r1]            // 544c strb r4, [r1, r1]
strb r5, [r1, r1]            // 544d strb r5, [r1, r1]
strb r6, [r1, r1]            // 544e strb r6, [r1, r1]
strb r7, [r1, r1]            // 544f strb r7, [r1, r1]
strb r0, [r2, r1]            // 5450 strb r0, [r2, r1]
strb r1, [r2, r1]            // 5451 strb r1, [r2, r1]
strb r2, [r2, r1]            // 5452 strb r2, [r2, r1]
strb r3, [r2, r1]            // 5453 strb r3, [r2, r1]
strb r4, [r2, r1]            // 5454 strb r4, [r2, r1]
strb r5, [r2, r1]            // 5455 strb r5, [r2, r1]
strb r6, [r2, r1]            // 5456 strb r6, [r2, r1]
strb r7, [r2, r1]            // 5457 strb r7, [r2, r1]
strb r0, [r3, r1]            // 5458 strb r0, [r3, r1]
strb r1, [r3, r1]            // 5459 strb r1, [r3, r1]
strb r2, [r3, r1]            // 545a strb r2, [r3, r1]
strb r3, [r3, r1]            // 545b strb r3, [r3, r1]
strb r4, [r3, r1]            // 545c strb r4, [r3, r1]
strb r5, [r3, r1]            // 545d strb r5, [r3, r1]
strb r6, [r3, r1]            // 545e strb r6, [r3, r1]
strb r7, [r3, r1]            // 545f strb r7, [r3, r1]
strb r0, [r4, r1]            // 5460 strb r0, [r4, r1]
strb r1, [r4, r1]            // 5461 strb r1, [r4, r1]
strb r2, [r4, r1]            // 5462 strb r2, [r4, r1]
strb r3, [r4, r1]            // 5463 strb r3, [r4, r1]
strb r4, [r4, r1]            // 5464 strb r4, [r4, r1]
strb r5, [r4, r1]            // 5465 strb r5, [r4, r1]
strb r6, [r4, r1]            // 5466 strb r6, [r4, r1]
strb r7, [r4, r1]            // 5467 strb r7, [r4, r1]
strb r0, [r5, r1]            // 5468 strb r0, [r5, r1]
strb r1, [r5, r1]            // 5469 strb r1, [r5, r1]
strb r2, [r5, r1]            // 546a strb r2, [r5, r1]
strb r3, [r5, r1]            // 546b strb r3, [r5, r1]
strb r4, [r5, r1]            // 546c strb r4, [r5, r1]
strb r5, [r5, r1]            // 546d strb r5, [r5, r1]
strb r6, [r5, r1]            // 546e strb r6, [r5, r1]
strb r7, [r5, r1]            // 546f strb r7, [r5, r1]
strb r0, [r6, r1]            // 5470 strb r0, [r6, r1]
strb r1, [r6, r1]            // 5471 strb r1, [r6, r1]
strb r2, [r6, r1]            // 5472 strb r2, [r6, r1]
strb r3, [r6, r1]            // 5473 strb r3, [r6, r1]
strb r4, [r6, r1]            // 5474 strb r4, [r6, r1]
strb r5, [r6, r1]            // 5475 strb r5, [r6, r1]
strb r6, [r6, r1]            // 5476 strb r6, [r6, r1]
strb r7, [r6, r1]            // 5477 strb r7, [r6, r1]
strb r0, [r7, r1]            // 5478 strb r0, [r7, r1]
strb r1, [r7, r1]            // 5479 strb r1, [r7, r1]
strb r2, [r7, r1]            // 547a strb r2, [r7, r1]
strb r3, [r7, r1]            // 547b strb r3, [r7, r1]
strb r4, [r7, r1]            // 547c strb r4, [r7, r1]
strb r5, [r7, r1]            // 547d strb r5, [r7, r1]
strb r6, [r7, r1]            // 547e strb r6, [r7, r1]
strb r7, [r7, r1]            // 547f strb r7, [r7, r1]
strb r0, [r0, r2]            // 5480 strb r0, [r0, r2]
strb r1, [r0, r2]            // 5481 strb r1, [r0, r2]
strb r2, [r0, r2]            // 5482 strb r2, [r0, r2]
strb r3, [r0, r2]            // 5483 strb r3, [r0, r2]
strb r4, [r0, r2]            // 5484 strb r4, [r0, r2]
strb r5, [r0, r2]            // 5485 strb r5, [r0, r2]
strb r6, [r0, r2]            // 5486 strb r6, [r0, r2]
strb r7, [r0, r2]            // 5487 strb r7, [r0, r2]
strb r0, [r1, r2]            // 5488 strb r0, [r1, r2]
strb r1, [r1, r2]            // 5489 strb r1, [r1, r2]
strb r2, [r1, r2]            // 548a strb r2, [r1, r2]
strb r3, [r1, r2]            // 548b strb r3, [r1, r2]
strb r4, [r1, r2]            // 548c strb r4, [r1, r2]
strb r5, [r1, r2]            // 548d strb r5, [r1, r2]
strb r6, [r1, r2]            // 548e strb r6, [r1, r2]
strb r7, [r1, r2]            // 548f strb r7, [r1, r2]
strb r0, [r2, r2]            // 5490 strb r0, [r2, r2]
strb r1, [r2, r2]            // 5491 strb r1, [r2, r2]
strb r2, [r2, r2]            // 5492 strb r2, [r2, r2]
strb r3, [r2, r2]            // 5493 strb r3, [r2, r2]
strb r4, [r2, r2]            // 5494 strb r4, [r2, r2]
strb r5, [r2, r2]            // 5495 strb r5, [r2, r2]
strb r6, [r2, r2]            // 5496 strb r6, [r2, r2]
strb r7, [r2, r2]            // 5497 strb r7, [r2, r2]
strb r0, [r3, r2]            // 5498 strb r0, [r3, r2]
strb r1, [r3, r2]            // 5499 strb r1, [r3, r2]
strb r2, [r3, r2]            // 549a strb r2, [r3, r2]
strb r3, [r3, r2]            // 549b strb r3, [r3, r2]
strb r4, [r3, r2]            // 549c strb r4, [r3, r2]
strb r5, [r3, r2]            // 549d strb r5, [r3, r2]
strb r6, [r3, r2]            // 549e strb r6, [r3, r2]
strb r7, [r3, r2]            // 549f strb r7, [r3, r2]
strb r0, [r4, r2]            // 54a0 strb r0, [r4, r2]
strb r1, [r4, r2]            // 54a1 strb r1, [r4, r2]
strb r2, [r4, r2]            // 54a2 strb r2, [r4, r2]
strb r3, [r4, r2]            // 54a3 strb r3, [r4, r2]
strb r4, [r4, r2]            // 54a4 strb r4, [r4, r2]
strb r5, [r4, r2]            // 54a5 strb r5, [r4, r2]
strb r6, [r4, r2]            // 54a6 strb r6, [r4, r2]
strb r7, [r4, r2]            // 54a7 strb r7, [r4, r2]
strb r0, [r5, r2]            // 54a8 strb r0, [r5, r2]
strb r1, [r5, r2]            // 54a9 strb r1, [r5, r2]
strb r2, [r5, r2]            // 54aa strb r2, [r5, r2]
strb r3, [r5, r2]            // 54ab strb r3, [r5, r2]
strb r4, [r5, r2]            // 54ac strb r4, [r5, r2]
strb r5, [r5, r2]            // 54ad strb r5, [r5, r2]
strb r6, [r5, r2]            // 54ae strb r6, [r5, r2]
strb r7, [r5, r2]            // 54af strb r7, [r5, r2]
strb r0, [r6, r2]            // 54b0 strb r0, [r6, r2]
strb r1, [r6, r2]            // 54b1 strb r1, [r6, r2]
strb r2, [r6, r2]            // 54b2 strb r2, [r6, r2]
strb r3, [r6, r2]            // 54b3 strb r3, [r6, r2]
strb r4, [r6, r2]            // 54b4 strb r4, [r6, r2]
strb r5, [r6, r2]            // 54b5 strb r5, [r6, r2]
strb r6, [r6, r2]            // 54b6 strb r6, [r6, r2]
strb r7, [r6, r2]            // 54b7 strb r7, [r6, r2]
strb r0, [r7, r2]            // 54b8 strb r0, [r7, r2]
strb r1, [r7, r2]            // 54b9 strb r1, [r7, r2]
strb r2, [r7, r2]            // 54ba strb r2, [r7, r2]
strb r3, [r7, r2]            // 54bb strb r3, [r7, r2]
strb r4, [r7, r2]            // 54bc strb r4, [r7, r2]
strb r5, [r7, r2]            // 54bd strb r5, [r7, r2]
strb r6, [r7, r2]            // 54be strb r6, [r7, r2]
strb r7, [r7, r2]            // 54bf strb r7, [r7, r2]
strb r0, [r0, r3]            // 54c0 strb r0, [r0, r3]
strb r1, [r0, r3]            // 54c1 strb r1, [r0, r3]
strb r2, [r0, r3]            // 54c2 strb r2, [r0, r3]
strb r3, [r0, r3]            // 54c3 strb r3, [r0, r3]
strb r4, [r0, r3]            // 54c4 strb r4, [r0, r3]
strb r5, [r0, r3]            // 54c5 strb r5, [r0, r3]
strb r6, [r0, r3]            // 54c6 strb r6, [r0, r3]
strb r7, [r0, r3]            // 54c7 strb r7, [r0, r3]
strb r0, [r1, r3]            // 54c8 strb r0, [r1, r3]
strb r1, [r1, r3]            // 54c9 strb r1, [r1, r3]
strb r2, [r1, r3]            // 54ca strb r2, [r1, r3]
strb r3, [r1, r3]            // 54cb strb r3, [r1, r3]
strb r4, [r1, r3]            // 54cc strb r4, [r1, r3]
strb r5, [r1, r3]            // 54cd strb r5, [r1, r3]
strb r6, [r1, r3]            // 54ce strb r6, [r1, r3]
strb r7, [r1, r3]            // 54cf strb r7, [r1, r3]
strb r0, [r2, r3]            // 54d0 strb r0, [r2, r3]
strb r1, [r2, r3]            // 54d1 strb r1, [r2, r3]
strb r2, [r2, r3]            // 54d2 strb r2, [r2, r3]
strb r3, [r2, r3]            // 54d3 strb r3, [r2, r3]
strb r4, [r2, r3]            // 54d4 strb r4, [r2, r3]
strb r5, [r2, r3]            // 54d5 strb r5, [r2, r3]
strb r6, [r2, r3]            // 54d6 strb r6, [r2, r3]
strb r7, [r2, r3]            // 54d7 strb r7, [r2, r3]
strb r0, [r3, r3]            // 54d8 strb r0, [r3, r3]
strb r1, [r3, r3]            // 54d9 strb r1, [r3, r3]
strb r2, [r3, r3]            // 54da strb r2, [r3, r3]
strb r3, [r3, r3]            // 54db strb r3, [r3, r3]
strb r4, [r3, r3]            // 54dc strb r4, [r3, r3]
strb r5, [r3, r3]            // 54dd strb r5, [r3, r3]
strb r6, [r3, r3]            // 54de strb r6, [r3, r3]
strb r7, [r3, r3]            // 54df strb r7, [r3, r3]
strb r0, [r4, r3]            // 54e0 strb r0, [r4, r3]
strb r1, [r4, r3]            // 54e1 strb r1, [r4, r3]
strb r2, [r4, r3]            // 54e2 strb r2, [r4, r3]
strb r3, [r4, r3]            // 54e3 strb r3, [r4, r3]
strb r4, [r4, r3]            // 54e4 strb r4, [r4, r3]
strb r5, [r4, r3]            // 54e5 strb r5, [r4, r3]
strb r6, [r4, r3]            // 54e6 strb r6, [r4, r3]
strb r7, [r4, r3]            // 54e7 strb r7, [r4, r3]
strb r0, [r5, r3]            // 54e8 strb r0, [r5, r3]
strb r1, [r5, r3]            // 54e9 strb r1, [r5, r3]
strb r2, [r5, r3]            // 54ea strb r2, [r5, r3]
strb r3, [r5, r3]            // 54eb strb r3, [r5, r3]
strb r4, [r5, r3]            // 54ec strb r4, [r5, r3]
strb r5, [r5, r3]            // 54ed strb r5, [r5, r3]
strb r6, [r5, r3]            // 54ee strb r6, [r5, r3]
strb r7, [r5, r3]            // 54ef strb r7, [r5, r3]
strb r0, [r6, r3]            // 54f0 strb r0, [r6, r3]
strb r1, [r6, r3]            // 54f1 strb r1, [r6, r3]
strb r2, [r6, r3]            // 54f2 strb r2, [r6, r3]
strb r3, [r6, r3]            // 54f3 strb r3, [r6, r3]
strb r4, [r6, r3]            // 54f4 strb r4, [r6, r3]
strb r5, [r6, r3]            // 54f5 strb r5, [r6, r3]
strb r6, [r6, r3]            // 54f6 strb r6, [r6, r3]
strb r7, [r6, r3]            // 54f7 strb r7, [r6, r3]
strb r0, [r7, r3]            // 54f8 strb r0, [r7, r3]
strb r1, [r7, r3]            // 54f9 strb r1, [r7, r3]
strb r2, [r7, r3]            // 54fa strb r2, [r7, r3]
strb r3, [r7, r3]            // 54fb strb r3, [r7, r3]
strb r4, [r7, r3]            // 54fc strb r4, [r7, r3]
strb r5, [r7, r3]            // 54fd strb r5, [r7, r3]
strb r6, [r7, r3]            // 54fe strb r6, [r7, r3]
strb r7, [r7, r3]            // 54ff strb r7, [r7, r3]
strb r0, [r0, r4]            // 5500 strb r0, [r0, r4]
strb r1, [r0, r4]            // 5501 strb r1, [r0, r4]
strb r2, [r0, r4]            // 5502 strb r2, [r0, r4]
strb r3, [r0, r4]            // 5503 strb r3, [r0, r4]
strb r4, [r0, r4]            // 5504 strb r4, [r0, r4]
strb r5, [r0, r4]            // 5505 strb r5, [r0, r4]
strb r6, [r0, r4]            // 5506 strb r6, [r0, r4]
strb r7, [r0, r4]            // 5507 strb r7, [r0, r4]
strb r0, [r1, r4]            // 5508 strb r0, [r1, r4]
strb r1, [r1, r4]            // 5509 strb r1, [r1, r4]
strb r2, [r1, r4]            // 550a strb r2, [r1, r4]
strb r3, [r1, r4]            // 550b strb r3, [r1, r4]
strb r4, [r1, r4]            // 550c strb r4, [r1, r4]
strb r5, [r1, r4]            // 550d strb r5, [r1, r4]
strb r6, [r1, r4]            // 550e strb r6, [r1, r4]
strb r7, [r1, r4]            // 550f strb r7, [r1, r4]
strb r0, [r2, r4]            // 5510 strb r0, [r2, r4]
strb r1, [r2, r4]            // 5511 strb r1, [r2, r4]
strb r2, [r2, r4]            // 5512 strb r2, [r2, r4]
strb r3, [r2, r4]            // 5513 strb r3, [r2, r4]
strb r4, [r2, r4]            // 5514 strb r4, [r2, r4]
strb r5, [r2, r4]            // 5515 strb r5, [r2, r4]
strb r6, [r2, r4]            // 5516 strb r6, [r2, r4]
strb r7, [r2, r4]            // 5517 strb r7, [r2, r4]
strb r0, [r3, r4]            // 5518 strb r0, [r3, r4]
strb r1, [r3, r4]            // 5519 strb r1, [r3, r4]
strb r2, [r3, r4]            // 551a strb r2, [r3, r4]
strb r3, [r3, r4]            // 551b strb r3, [r3, r4]
strb r4, [r3, r4]            // 551c strb r4, [r3, r4]
strb r5, [r3, r4]            // 551d strb r5, [r3, r4]
strb r6, [r3, r4]            // 551e strb r6, [r3, r4]
strb r7, [r3, r4]            // 551f strb r7, [r3, r4]
strb r0, [r4, r4]            // 5520 strb r0, [r4, r4]
strb r1, [r4, r4]            // 5521 strb r1, [r4, r4]
strb r2, [r4, r4]            // 5522 strb r2, [r4, r4]
strb r3, [r4, r4]            // 5523 strb r3, [r4, r4]
strb r4, [r4, r4]            // 5524 strb r4, [r4, r4]
strb r5, [r4, r4]            // 5525 strb r5, [r4, r4]
strb r6, [r4, r4]            // 5526 strb r6, [r4, r4]
strb r7, [r4, r4]            // 5527 strb r7, [r4, r4]
strb r0, [r5, r4]            // 5528 strb r0, [r5, r4]
strb r1, [r5, r4]            // 5529 strb r1, [r5, r4]
strb r2, [r5, r4]            // 552a strb r2, [r5, r4]
strb r3, [r5, r4]            // 552b strb r3, [r5, r4]
strb r4, [r5, r4]            // 552c strb r4, [r5, r4]
strb r5, [r5, r4]            // 552d strb r5, [r5, r4]
strb r6, [r5, r4]            // 552e strb r6, [r5, r4]
strb r7, [r5, r4]            // 552f strb r7, [r5, r4]
strb r0, [r6, r4]            // 5530 strb r0, [r6, r4]
strb r1, [r6, r4]            // 5531 strb r1, [r6, r4]
strb r2, [r6, r4]            // 5532 strb r2, [r6, r4]
strb r3, [r6, r4]            // 5533 strb r3, [r6, r4]
strb r4, [r6, r4]            // 5534 strb r4, [r6, r4]
strb r5, [r6, r4]            // 5535 strb r5, [r6, r4]
strb r6, [r6, r4]            // 5536 strb r6, [r6, r4]
strb r7, [r6, r4]            // 5537 strb r7, [r6, r4]
strb r0, [r7, r4]            // 5538 strb r0, [r7, r4]
strb r1, [r7, r4]            // 5539 strb r1, [r7, r4]
strb r2, [r7, r4]            // 553a strb r2, [r7, r4]
strb r3, [r7, r4]            // 553b strb r3, [r7, r4]
strb r4, [r7, r4]            // 553c strb r4, [r7, r4]
strb r5, [r7, r4]            // 553d strb r5, [r7, r4]
strb r6, [r7, r4]            // 553e strb r6, [r7, r4]
strb r7, [r7, r4]            // 553f strb r7, [r7, r4]
strb r0, [r0, r5]            // 5540 strb r0, [r0, r5]
strb r1, [r0, r5]            // 5541 strb r1, [r0, r5]
strb r2, [r0, r5]            // 5542 strb r2, [r0, r5]
strb r3, [r0, r5]            // 5543 strb r3, [r0, r5]
strb r4, [r0, r5]            // 5544 strb r4, [r0, r5]
strb r5, [r0, r5]            // 5545 strb r5, [r0, r5]
strb r6, [r0, r5]            // 5546 strb r6, [r0, r5]
strb r7, [r0, r5]            // 5547 strb r7, [r0, r5]
strb r0, [r1, r5]            // 5548 strb r0, [r1, r5]
strb r1, [r1, r5]            // 5549 strb r1, [r1, r5]
strb r2, [r1, r5]            // 554a strb r2, [r1, r5]
strb r3, [r1, r5]            // 554b strb r3, [r1, r5]
strb r4, [r1, r5]            // 554c strb r4, [r1, r5]
strb r5, [r1, r5]            // 554d strb r5, [r1, r5]
strb r6, [r1, r5]            // 554e strb r6, [r1, r5]
strb r7, [r1, r5]            // 554f strb r7, [r1, r5]
strb r0, [r2, r5]            // 5550 strb r0, [r2, r5]
strb r1, [r2, r5]            // 5551 strb r1, [r2, r5]
strb r2, [r2, r5]            // 5552 strb r2, [r2, r5]
strb r3, [r2, r5]            // 5553 strb r3, [r2, r5]
strb r4, [r2, r5]            // 5554 strb r4, [r2, r5]
strb r5, [r2, r5]            // 5555 strb r5, [r2, r5]
strb r6, [r2, r5]            // 5556 strb r6, [r2, r5]
strb r7, [r2, r5]            // 5557 strb r7, [r2, r5]
strb r0, [r3, r5]            // 5558 strb r0, [r3, r5]
strb r1, [r3, r5]            // 5559 strb r1, [r3, r5]
strb r2, [r3, r5]            // 555a strb r2, [r3, r5]
strb r3, [r3, r5]            // 555b strb r3, [r3, r5]
strb r4, [r3, r5]            // 555c strb r4, [r3, r5]
strb r5, [r3, r5]            // 555d strb r5, [r3, r5]
strb r6, [r3, r5]            // 555e strb r6, [r3, r5]
strb r7, [r3, r5]            // 555f strb r7, [r3, r5]
strb r0, [r4, r5]            // 5560 strb r0, [r4, r5]
strb r1, [r4, r5]            // 5561 strb r1, [r4, r5]
strb r2, [r4, r5]            // 5562 strb r2, [r4, r5]
strb r3, [r4, r5]            // 5563 strb r3, [r4, r5]
strb r4, [r4, r5]            // 5564 strb r4, [r4, r5]
strb r5, [r4, r5]            // 5565 strb r5, [r4, r5]
strb r6, [r4, r5]            // 5566 strb r6, [r4, r5]
strb r7, [r4, r5]            // 5567 strb r7, [r4, r5]
strb r0, [r5, r5]            // 5568 strb r0, [r5, r5]
strb r1, [r5, r5]            // 5569 strb r1, [r5, r5]
strb r2, [r5, r5]            // 556a strb r2, [r5, r5]
strb r3, [r5, r5]            // 556b strb r3, [r5, r5]
strb r4, [r5, r5]            // 556c strb r4, [r5, r5]
strb r5, [r5, r5]            // 556d strb r5, [r5, r5]
strb r6, [r5, r5]            // 556e strb r6, [r5, r5]
strb r7, [r5, r5]            // 556f strb r7, [r5, r5]
strb r0, [r6, r5]            // 5570 strb r0, [r6, r5]
strb r1, [r6, r5]            // 5571 strb r1, [r6, r5]
strb r2, [r6, r5]            // 5572 strb r2, [r6, r5]
strb r3, [r6, r5]            // 5573 strb r3, [r6, r5]
strb r4, [r6, r5]            // 5574 strb r4, [r6, r5]
strb r5, [r6, r5]            // 5575 strb r5, [r6, r5]
strb r6, [r6, r5]            // 5576 strb r6, [r6, r5]
strb r7, [r6, r5]            // 5577 strb r7, [r6, r5]
strb r0, [r7, r5]            // 5578 strb r0, [r7, r5]
strb r1, [r7, r5]            // 5579 strb r1, [r7, r5]
strb r2, [r7, r5]            // 557a strb r2, [r7, r5]
strb r3, [r7, r5]            // 557b strb r3, [r7, r5]
strb r4, [r7, r5]            // 557c strb r4, [r7, r5]
strb r5, [r7, r5]            // 557d strb r5, [r7, r5]
strb r6, [r7, r5]            // 557e strb r6, [r7, r5]
strb r7, [r7, r5]            // 557f strb r7, [r7, r5]
strb r0, [r0, r6]            // 5580 strb r0, [r0, r6]
strb r1, [r0, r6]            // 5581 strb r1, [r0, r6]
strb r2, [r0, r6]            // 5582 strb r2, [r0, r6]
strb r3, [r0, r6]            // 5583 strb r3, [r0, r6]
strb r4, [r0, r6]            // 5584 strb r4, [r0, r6]
strb r5, [r0, r6]            // 5585 strb r5, [r0, r6]
strb r6, [r0, r6]            // 5586 strb r6, [r0, r6]
strb r7, [r0, r6]            // 5587 strb r7, [r0, r6]
strb r0, [r1, r6]            // 5588 strb r0, [r1, r6]
strb r1, [r1, r6]            // 5589 strb r1, [r1, r6]
strb r2, [r1, r6]            // 558a strb r2, [r1, r6]
strb r3, [r1, r6]            // 558b strb r3, [r1, r6]
strb r4, [r1, r6]            // 558c strb r4, [r1, r6]
strb r5, [r1, r6]            // 558d strb r5, [r1, r6]
strb r6, [r1, r6]            // 558e strb r6, [r1, r6]
strb r7, [r1, r6]            // 558f strb r7, [r1, r6]
strb r0, [r2, r6]            // 5590 strb r0, [r2, r6]
strb r1, [r2, r6]            // 5591 strb r1, [r2, r6]
strb r2, [r2, r6]            // 5592 strb r2, [r2, r6]
strb r3, [r2, r6]            // 5593 strb r3, [r2, r6]
strb r4, [r2, r6]            // 5594 strb r4, [r2, r6]
strb r5, [r2, r6]            // 5595 strb r5, [r2, r6]
strb r6, [r2, r6]            // 5596 strb r6, [r2, r6]
strb r7, [r2, r6]            // 5597 strb r7, [r2, r6]
strb r0, [r3, r6]            // 5598 strb r0, [r3, r6]
strb r1, [r3, r6]            // 5599 strb r1, [r3, r6]
strb r2, [r3, r6]            // 559a strb r2, [r3, r6]
strb r3, [r3, r6]            // 559b strb r3, [r3, r6]
strb r4, [r3, r6]            // 559c strb r4, [r3, r6]
strb r5, [r3, r6]            // 559d strb r5, [r3, r6]
strb r6, [r3, r6]            // 559e strb r6, [r3, r6]
strb r7, [r3, r6]            // 559f strb r7, [r3, r6]
strb r0, [r4, r6]            // 55a0 strb r0, [r4, r6]
strb r1, [r4, r6]            // 55a1 strb r1, [r4, r6]
strb r2, [r4, r6]            // 55a2 strb r2, [r4, r6]
strb r3, [r4, r6]            // 55a3 strb r3, [r4, r6]
strb r4, [r4, r6]            // 55a4 strb r4, [r4, r6]
strb r5, [r4, r6]            // 55a5 strb r5, [r4, r6]
strb r6, [r4, r6]            // 55a6 strb r6, [r4, r6]
strb r7, [r4, r6]            // 55a7 strb r7, [r4, r6]
strb r0, [r5, r6]            // 55a8 strb r0, [r5, r6]
strb r1, [r5, r6]            // 55a9 strb r1, [r5, r6]
strb r2, [r5, r6]            // 55aa strb r2, [r5, r6]
strb r3, [r5, r6]            // 55ab strb r3, [r5, r6]
strb r4, [r5, r6]            // 55ac strb r4, [r5, r6]
strb r5, [r5, r6]            // 55ad strb r5, [r5, r6]
strb r6, [r5, r6]            // 55ae strb r6, [r5, r6]
strb r7, [r5, r6]            // 55af strb r7, [r5, r6]
strb r0, [r6, r6]            // 55b0 strb r0, [r6, r6]
strb r1, [r6, r6]            // 55b1 strb r1, [r6, r6]
strb r2, [r6, r6]            // 55b2 strb r2, [r6, r6]
strb r3, [r6, r6]            // 55b3 strb r3, [r6, r6]
strb r4, [r6, r6]            // 55b4 strb r4, [r6, r6]
strb r5, [r6, r6]            // 55b5 strb r5, [r6, r6]
strb r6, [r6, r6]            // 55b6 strb r6, [r6, r6]
strb r7, [r6, r6]            // 55b7 strb r7, [r6, r6]
strb r0, [r7, r6]            // 55b8 strb r0, [r7, r6]
strb r1, [r7, r6]            // 55b9 strb r1, [r7, r6]
strb r2, [r7, r6]            // 55ba strb r2, [r7, r6]
strb r3, [r7, r6]            // 55bb strb r3, [r7, r6]
strb r4, [r7, r6]            // 55bc strb r4, [r7, r6]
strb r5, [r7, r6]            // 55bd strb r5, [r7, r6]
strb r6, [r7, r6]            // 55be strb r6, [r7, r6]
strb r7, [r7, r6]            // 55bf strb r7, [r7, r6]
strb r0, [r0, r7]            // 55c0 strb r0, [r0, r7]
strb r1, [r0, r7]            // 55c1 strb r1, [r0, r7]
strb r2, [r0, r7]            // 55c2 strb r2, [r0, r7]
strb r3, [r0, r7]            // 55c3 strb r3, [r0, r7]
strb r4, [r0, r7]            // 55c4 strb r4, [r0, r7]
strb r5, [r0, r7]            // 55c5 strb r5, [r0, r7]
strb r6, [r0, r7]            // 55c6 strb r6, [r0, r7]
strb r7, [r0, r7]            // 55c7 strb r7, [r0, r7]
strb r0, [r1, r7]            // 55c8 strb r0, [r1, r7]
strb r1, [r1, r7]            // 55c9 strb r1, [r1, r7]
strb r2, [r1, r7]            // 55ca strb r2, [r1, r7]
strb r3, [r1, r7]            // 55cb strb r3, [r1, r7]
strb r4, [r1, r7]            // 55cc strb r4, [r1, r7]
strb r5, [r1, r7]            // 55cd strb r5, [r1, r7]
strb r6, [r1, r7]            // 55ce strb r6, [r1, r7]
strb r7, [r1, r7]            // 55cf strb r7, [r1, r7]
strb r0, [r2, r7]            // 55d0 strb r0, [r2, r7]
strb r1, [r2, r7]            // 55d1 strb r1, [r2, r7]
strb r2, [r2, r7]            // 55d2 strb r2, [r2, r7]
strb r3, [r2, r7]            // 55d3 strb r3, [r2, r7]
strb r4, [r2, r7]            // 55d4 strb r4, [r2, r7]
strb r5, [r2, r7]            // 55d5 strb r5, [r2, r7]
strb r6, [r2, r7]            // 55d6 strb r6, [r2, r7]
strb r7, [r2, r7]            // 55d7 strb r7, [r2, r7]
strb r0, [r3, r7]            // 55d8 strb r0, [r3, r7]
strb r1, [r3, r7]            // 55d9 strb r1, [r3, r7]
strb r2, [r3, r7]            // 55da strb r2, [r3, r7]
strb r3, [r3, r7]            // 55db strb r3, [r3, r7]
strb r4, [r3, r7]            // 55dc strb r4, [r3, r7]
strb r5, [r3, r7]            // 55dd strb r5, [r3, r7]
strb r6, [r3, r7]            // 55de strb r6, [r3, r7]
strb r7, [r3, r7]            // 55df strb r7, [r3, r7]
strb r0, [r4, r7]            // 55e0 strb r0, [r4, r7]
strb r1, [r4, r7]            // 55e1 strb r1, [r4, r7]
strb r2, [r4, r7]            // 55e2 strb r2, [r4, r7]
strb r3, [r4, r7]            // 55e3 strb r3, [r4, r7]
strb r4, [r4, r7]            // 55e4 strb r4, [r4, r7]
strb r5, [r4, r7]            // 55e5 strb r5, [r4, r7]
strb r6, [r4, r7]            // 55e6 strb r6, [r4, r7]
strb r7, [r4, r7]            // 55e7 strb r7, [r4, r7]
strb r0, [r5, r7]            // 55e8 strb r0, [r5, r7]
strb r1, [r5, r7]            // 55e9 strb r1, [r5, r7]
strb r2, [r5, r7]            // 55ea strb r2, [r5, r7]
strb r3, [r5, r7]            // 55eb strb r3, [r5, r7]
strb r4, [r5, r7]            // 55ec strb r4, [r5, r7]
strb r5, [r5, r7]            // 55ed strb r5, [r5, r7]
strb r6, [r5, r7]            // 55ee strb r6, [r5, r7]
strb r7, [r5, r7]            // 55ef strb r7, [r5, r7]
strb r0, [r6, r7]            // 55f0 strb r0, [r6, r7]
strb r1, [r6, r7]            // 55f1 strb r1, [r6, r7]
strb r2, [r6, r7]            // 55f2 strb r2, [r6, r7]
strb r3, [r6, r7]            // 55f3 strb r3, [r6, r7]
strb r4, [r6, r7]            // 55f4 strb r4, [r6, r7]
strb r5, [r6, r7]            // 55f5 strb r5, [r6, r7]
strb r6, [r6, r7]            // 55f6 strb r6, [r6, r7]
strb r7, [r6, r7]            // 55f7 strb r7, [r6, r7]
strb r0, [r7, r7]            // 55f8 strb r0, [r7, r7]
strb r1, [r7, r7]            // 55f9 strb r1, [r7, r7]
strb r2, [r7, r7]            // 55fa strb r2, [r7, r7]
strb r3, [r7, r7]            // 55fb strb r3, [r7, r7]
strb r4, [r7, r7]            // 55fc strb r4, [r7, r7]
strb r5, [r7, r7]            // 55fd strb r5, [r7, r7]
strb r6, [r7, r7]            // 55fe strb r6, [r7, r7]
strb r7, [r7, r7]            // 55ff strb r7, [r7, r7]

ldrsb r0, [r0, r0]           // 5600 ldrsb r0, [r0, r0]
ldrsb r1, [r0, r0]           // 5601 ldrsb r1, [r0, r0]
ldrsb r2, [r0, r0]           // 5602 ldrsb r2, [r0, r0]
ldrsb r3, [r0, r0]           // 5603 ldrsb r3, [r0, r0]
ldrsb r4, [r0, r0]           // 5604 ldrsb r4, [r0, r0]
ldrsb r5, [r0, r0]           // 5605 ldrsb r5, [r0, r0]
ldrsb r6, [r0, r0]           // 5606 ldrsb r6, [r0, r0]
ldrsb r7, [r0, r0]           // 5607 ldrsb r7, [r0, r0]
ldrsb r0, [r1, r0]           // 5608 ldrsb r0, [r1, r0]
ldrsb r1, [r1, r0]           // 5609 ldrsb r1, [r1, r0]
ldrsb r2, [r1, r0]           // 560a ldrsb r2, [r1, r0]
ldrsb r3, [r1, r0]           // 560b ldrsb r3, [r1, r0]
ldrsb r4, [r1, r0]           // 560c ldrsb r4, [r1, r0]
ldrsb r5, [r1, r0]           // 560d ldrsb r5, [r1, r0]
ldrsb r6, [r1, r0]           // 560e ldrsb r6, [r1, r0]
ldrsb r7, [r1, r0]           // 560f ldrsb r7, [r1, r0]
ldrsb r0, [r2, r0]           // 5610 ldrsb r0, [r2, r0]
ldrsb r1, [r2, r0]           // 5611 ldrsb r1, [r2, r0]
ldrsb r2, [r2, r0]           // 5612 ldrsb r2, [r2, r0]
ldrsb r3, [r2, r0]           // 5613 ldrsb r3, [r2, r0]
ldrsb r4, [r2, r0]           // 5614 ldrsb r4, [r2, r0]
ldrsb r5, [r2, r0]           // 5615 ldrsb r5, [r2, r0]
ldrsb r6, [r2, r0]           // 5616 ldrsb r6, [r2, r0]
ldrsb r7, [r2, r0]           // 5617 ldrsb r7, [r2, r0]
ldrsb r0, [r3, r0]           // 5618 ldrsb r0, [r3, r0]
ldrsb r1, [r3, r0]           // 5619 ldrsb r1, [r3, r0]
ldrsb r2, [r3, r0]           // 561a ldrsb r2, [r3, r0]
ldrsb r3, [r3, r0]           // 561b ldrsb r3, [r3, r0]
ldrsb r4, [r3, r0]           // 561c ldrsb r4, [r3, r0]
ldrsb r5, [r3, r0]           // 561d ldrsb r5, [r3, r0]
ldrsb r6, [r3, r0]           // 561e ldrsb r6, [r3, r0]
ldrsb r7, [r3, r0]           // 561f ldrsb r7, [r3, r0]
ldrsb r0, [r4, r0]           // 5620 ldrsb r0, [r4, r0]
ldrsb r1, [r4, r0]           // 5621 ldrsb r1, [r4, r0]
ldrsb r2, [r4, r0]           // 5622 ldrsb r2, [r4, r0]
ldrsb r3, [r4, r0]           // 5623 ldrsb r3, [r4, r0]
ldrsb r4, [r4, r0]           // 5624 ldrsb r4, [r4, r0]
ldrsb r5, [r4, r0]           // 5625 ldrsb r5, [r4, r0]
ldrsb r6, [r4, r0]           // 5626 ldrsb r6, [r4, r0]
ldrsb r7, [r4, r0]           // 5627 ldrsb r7, [r4, r0]
ldrsb r0, [r5, r0]           // 5628 ldrsb r0, [r5, r0]
ldrsb r1, [r5, r0]           // 5629 ldrsb r1, [r5, r0]
ldrsb r2, [r5, r0]           // 562a ldrsb r2, [r5, r0]
ldrsb r3, [r5, r0]           // 562b ldrsb r3, [r5, r0]
ldrsb r4, [r5, r0]           // 562c ldrsb r4, [r5, r0]
ldrsb r5, [r5, r0]           // 562d ldrsb r5, [r5, r0]
ldrsb r6, [r5, r0]           // 562e ldrsb r6, [r5, r0]
ldrsb r7, [r5, r0]           // 562f ldrsb r7, [r5, r0]
ldrsb r0, [r6, r0]           // 5630 ldrsb r0, [r6, r0]
ldrsb r1, [r6, r0]           // 5631 ldrsb r1, [r6, r0]
ldrsb r2, [r6, r0]           // 5632 ldrsb r2, [r6, r0]
ldrsb r3, [r6, r0]           // 5633 ldrsb r3, [r6, r0]
ldrsb r4, [r6, r0]           // 5634 ldrsb r4, [r6, r0]
ldrsb r5, [r6, r0]           // 5635 ldrsb r5, [r6, r0]
ldrsb r6, [r6, r0]           // 5636 ldrsb r6, [r6, r0]
ldrsb r7, [r6, r0]           // 5637 ldrsb r7, [r6, r0]
ldrsb r0, [r7, r0]           // 5638 ldrsb r0, [r7, r0]
ldrsb r1, [r7, r0]           // 5639 ldrsb r1, [r7, r0]
ldrsb r2, [r7, r0]           // 563a ldrsb r2, [r7, r0]
ldrsb r3, [r7, r0]           // 563b ldrsb r3, [r7, r0]
ldrsb r4, [r7, r0]           // 563c ldrsb r4, [r7, r0]
ldrsb r5, [r7, r0]           // 563d ldrsb r5, [r7, r0]
ldrsb r6, [r7, r0]           // 563e ldrsb r6, [r7, r0]
ldrsb r7, [r7, r0]           // 563f ldrsb r7, [r7, r0]
ldrsb r0, [r0, r1]           // 5640 ldrsb r0, [r0, r1]
ldrsb r1, [r0, r1]           // 5641 ldrsb r1, [r0, r1]
ldrsb r2, [r0, r1]           // 5642 ldrsb r2, [r0, r1]
ldrsb r3, [r0, r1]           // 5643 ldrsb r3, [r0, r1]
ldrsb r4, [r0, r1]           // 5644 ldrsb r4, [r0, r1]
ldrsb r5, [r0, r1]           // 5645 ldrsb r5, [r0, r1]
ldrsb r6, [r0, r1]           // 5646 ldrsb r6, [r0, r1]
ldrsb r7, [r0, r1]           // 5647 ldrsb r7, [r0, r1]
ldrsb r0, [r1, r1]           // 5648 ldrsb r0, [r1, r1]
ldrsb r1, [r1, r1]           // 5649 ldrsb r1, [r1, r1]
ldrsb r2, [r1, r1]           // 564a ldrsb r2, [r1, r1]
ldrsb r3, [r1, r1]           // 564b ldrsb r3, [r1, r1]
ldrsb r4, [r1, r1]           // 564c ldrsb r4, [r1, r1]
ldrsb r5, [r1, r1]           // 564d ldrsb r5, [r1, r1]
ldrsb r6, [r1, r1]           // 564e ldrsb r6, [r1, r1]
ldrsb r7, [r1, r1]           // 564f ldrsb r7, [r1, r1]
ldrsb r0, [r2, r1]           // 5650 ldrsb r0, [r2, r1]
ldrsb r1, [r2, r1]           // 5651 ldrsb r1, [r2, r1]
ldrsb r2, [r2, r1]           // 5652 ldrsb r2, [r2, r1]
ldrsb r3, [r2, r1]           // 5653 ldrsb r3, [r2, r1]
ldrsb r4, [r2, r1]           // 5654 ldrsb r4, [r2, r1]
ldrsb r5, [r2, r1]           // 5655 ldrsb r5, [r2, r1]
ldrsb r6, [r2, r1]           // 5656 ldrsb r6, [r2, r1]
ldrsb r7, [r2, r1]           // 5657 ldrsb r7, [r2, r1]
ldrsb r0, [r3, r1]           // 5658 ldrsb r0, [r3, r1]
ldrsb r1, [r3, r1]           // 5659 ldrsb r1, [r3, r1]
ldrsb r2, [r3, r1]           // 565a ldrsb r2, [r3, r1]
ldrsb r3, [r3, r1]           // 565b ldrsb r3, [r3, r1]
ldrsb r4, [r3, r1]           // 565c ldrsb r4, [r3, r1]
ldrsb r5, [r3, r1]           // 565d ldrsb r5, [r3, r1]
ldrsb r6, [r3, r1]           // 565e ldrsb r6, [r3, r1]
ldrsb r7, [r3, r1]           // 565f ldrsb r7, [r3, r1]
ldrsb r0, [r4, r1]           // 5660 ldrsb r0, [r4, r1]
ldrsb r1, [r4, r1]           // 5661 ldrsb r1, [r4, r1]
ldrsb r2, [r4, r1]           // 5662 ldrsb r2, [r4, r1]
ldrsb r3, [r4, r1]           // 5663 ldrsb r3, [r4, r1]
ldrsb r4, [r4, r1]           // 5664 ldrsb r4, [r4, r1]
ldrsb r5, [r4, r1]           // 5665 ldrsb r5, [r4, r1]
ldrsb r6, [r4, r1]           // 5666 ldrsb r6, [r4, r1]
ldrsb r7, [r4, r1]           // 5667 ldrsb r7, [r4, r1]
ldrsb r0, [r5, r1]           // 5668 ldrsb r0, [r5, r1]
ldrsb r1, [r5, r1]           // 5669 ldrsb r1, [r5, r1]
ldrsb r2, [r5, r1]           // 566a ldrsb r2, [r5, r1]
ldrsb r3, [r5, r1]           // 566b ldrsb r3, [r5, r1]
ldrsb r4, [r5, r1]           // 566c ldrsb r4, [r5, r1]
ldrsb r5, [r5, r1]           // 566d ldrsb r5, [r5, r1]
ldrsb r6, [r5, r1]           // 566e ldrsb r6, [r5, r1]
ldrsb r7, [r5, r1]           // 566f ldrsb r7, [r5, r1]
ldrsb r0, [r6, r1]           // 5670 ldrsb r0, [r6, r1]
ldrsb r1, [r6, r1]           // 5671 ldrsb r1, [r6, r1]
ldrsb r2, [r6, r1]           // 5672 ldrsb r2, [r6, r1]
ldrsb r3, [r6, r1]           // 5673 ldrsb r3, [r6, r1]
ldrsb r4, [r6, r1]           // 5674 ldrsb r4, [r6, r1]
ldrsb r5, [r6, r1]           // 5675 ldrsb r5, [r6, r1]
ldrsb r6, [r6, r1]           // 5676 ldrsb r6, [r6, r1]
ldrsb r7, [r6, r1]           // 5677 ldrsb r7, [r6, r1]
ldrsb r0, [r7, r1]           // 5678 ldrsb r0, [r7, r1]
ldrsb r1, [r7, r1]           // 5679 ldrsb r1, [r7, r1]
ldrsb r2, [r7, r1]           // 567a ldrsb r2, [r7, r1]
ldrsb r3, [r7, r1]           // 567b ldrsb r3, [r7, r1]
ldrsb r4, [r7, r1]           // 567c ldrsb r4, [r7, r1]
ldrsb r5, [r7, r1]           // 567d ldrsb r5, [r7, r1]
ldrsb r6, [r7, r1]           // 567e ldrsb r6, [r7, r1]
ldrsb r7, [r7, r1]           // 567f ldrsb r7, [r7, r1]
ldrsb r0, [r0, r2]           // 5680 ldrsb r0, [r0, r2]
ldrsb r1, [r0, r2]           // 5681 ldrsb r1, [r0, r2]
ldrsb r2, [r0, r2]           // 5682 ldrsb r2, [r0, r2]
ldrsb r3, [r0, r2]           // 5683 ldrsb r3, [r0, r2]
ldrsb r4, [r0, r2]           // 5684 ldrsb r4, [r0, r2]
ldrsb r5, [r0, r2]           // 5685 ldrsb r5, [r0, r2]
ldrsb r6, [r0, r2]           // 5686 ldrsb r6, [r0, r2]
ldrsb r7, [r0, r2]           // 5687 ldrsb r7, [r0, r2]
ldrsb r0, [r1, r2]           // 5688 ldrsb r0, [r1, r2]
ldrsb r1, [r1, r2]           // 5689 ldrsb r1, [r1, r2]
ldrsb r2, [r1, r2]           // 568a ldrsb r2, [r1, r2]
ldrsb r3, [r1, r2]           // 568b ldrsb r3, [r1, r2]
ldrsb r4, [r1, r2]           // 568c ldrsb r4, [r1, r2]
ldrsb r5, [r1, r2]           // 568d ldrsb r5, [r1, r2]
ldrsb r6, [r1, r2]           // 568e ldrsb r6, [r1, r2]
ldrsb r7, [r1, r2]           // 568f ldrsb r7, [r1, r2]
ldrsb r0, [r2, r2]           // 5690 ldrsb r0, [r2, r2]
ldrsb r1, [r2, r2]           // 5691 ldrsb r1, [r2, r2]
ldrsb r2, [r2, r2]           // 5692 ldrsb r2, [r2, r2]
ldrsb r3, [r2, r2]           // 5693 ldrsb r3, [r2, r2]
ldrsb r4, [r2, r2]           // 5694 ldrsb r4, [r2, r2]
ldrsb r5, [r2, r2]           // 5695 ldrsb r5, [r2, r2]
ldrsb r6, [r2, r2]           // 5696 ldrsb r6, [r2, r2]
ldrsb r7, [r2, r2]           // 5697 ldrsb r7, [r2, r2]
ldrsb r0, [r3, r2]           // 5698 ldrsb r0, [r3, r2]
ldrsb r1, [r3, r2]           // 5699 ldrsb r1, [r3, r2]
ldrsb r2, [r3, r2]           // 569a ldrsb r2, [r3, r2]
ldrsb r3, [r3, r2]           // 569b ldrsb r3, [r3, r2]
ldrsb r4, [r3, r2]           // 569c ldrsb r4, [r3, r2]
ldrsb r5, [r3, r2]           // 569d ldrsb r5, [r3, r2]
ldrsb r6, [r3, r2]           // 569e ldrsb r6, [r3, r2]
ldrsb r7, [r3, r2]           // 569f ldrsb r7, [r3, r2]
ldrsb r0, [r4, r2]           // 56a0 ldrsb r0, [r4, r2]
ldrsb r1, [r4, r2]           // 56a1 ldrsb r1, [r4, r2]
ldrsb r2, [r4, r2]           // 56a2 ldrsb r2, [r4, r2]
ldrsb r3, [r4, r2]           // 56a3 ldrsb r3, [r4, r2]
ldrsb r4, [r4, r2]           // 56a4 ldrsb r4, [r4, r2]
ldrsb r5, [r4, r2]           // 56a5 ldrsb r5, [r4, r2]
ldrsb r6, [r4, r2]           // 56a6 ldrsb r6, [r4, r2]
ldrsb r7, [r4, r2]           // 56a7 ldrsb r7, [r4, r2]
ldrsb r0, [r5, r2]           // 56a8 ldrsb r0, [r5, r2]
ldrsb r1, [r5, r2]           // 56a9 ldrsb r1, [r5, r2]
ldrsb r2, [r5, r2]           // 56aa ldrsb r2, [r5, r2]
ldrsb r3, [r5, r2]           // 56ab ldrsb r3, [r5, r2]
ldrsb r4, [r5, r2]           // 56ac ldrsb r4, [r5, r2]
ldrsb r5, [r5, r2]           // 56ad ldrsb r5, [r5, r2]
ldrsb r6, [r5, r2]           // 56ae ldrsb r6, [r5, r2]
ldrsb r7, [r5, r2]           // 56af ldrsb r7, [r5, r2]
ldrsb r0, [r6, r2]           // 56b0 ldrsb r0, [r6, r2]
ldrsb r1, [r6, r2]           // 56b1 ldrsb r1, [r6, r2]
ldrsb r2, [r6, r2]           // 56b2 ldrsb r2, [r6, r2]
ldrsb r3, [r6, r2]           // 56b3 ldrsb r3, [r6, r2]
ldrsb r4, [r6, r2]           // 56b4 ldrsb r4, [r6, r2]
ldrsb r5, [r6, r2]           // 56b5 ldrsb r5, [r6, r2]
ldrsb r6, [r6, r2]           // 56b6 ldrsb r6, [r6, r2]
ldrsb r7, [r6, r2]           // 56b7 ldrsb r7, [r6, r2]
ldrsb r0, [r7, r2]           // 56b8 ldrsb r0, [r7, r2]
ldrsb r1, [r7, r2]           // 56b9 ldrsb r1, [r7, r2]
ldrsb r2, [r7, r2]           // 56ba ldrsb r2, [r7, r2]
ldrsb r3, [r7, r2]           // 56bb ldrsb r3, [r7, r2]
ldrsb r4, [r7, r2]           // 56bc ldrsb r4, [r7, r2]
ldrsb r5, [r7, r2]           // 56bd ldrsb r5, [r7, r2]
ldrsb r6, [r7, r2]           // 56be ldrsb r6, [r7, r2]
ldrsb r7, [r7, r2]           // 56bf ldrsb r7, [r7, r2]
ldrsb r0, [r0, r3]           // 56c0 ldrsb r0, [r0, r3]
ldrsb r1, [r0, r3]           // 56c1 ldrsb r1, [r0, r3]
ldrsb r2, [r0, r3]           // 56c2 ldrsb r2, [r0, r3]
ldrsb r3, [r0, r3]           // 56c3 ldrsb r3, [r0, r3]
ldrsb r4, [r0, r3]           // 56c4 ldrsb r4, [r0, r3]
ldrsb r5, [r0, r3]           // 56c5 ldrsb r5, [r0, r3]
ldrsb r6, [r0, r3]           // 56c6 ldrsb r6, [r0, r3]
ldrsb r7, [r0, r3]           // 56c7 ldrsb r7, [r0, r3]
ldrsb r0, [r1, r3]           // 56c8 ldrsb r0, [r1, r3]
ldrsb r1, [r1, r3]           // 56c9 ldrsb r1, [r1, r3]
ldrsb r2, [r1, r3]           // 56ca ldrsb r2, [r1, r3]
ldrsb r3, [r1, r3]           // 56cb ldrsb r3, [r1, r3]
ldrsb r4, [r1, r3]           // 56cc ldrsb r4, [r1, r3]
ldrsb r5, [r1, r3]           // 56cd ldrsb r5, [r1, r3]
ldrsb r6, [r1, r3]           // 56ce ldrsb r6, [r1, r3]
ldrsb r7, [r1, r3]           // 56cf ldrsb r7, [r1, r3]
ldrsb r0, [r2, r3]           // 56d0 ldrsb r0, [r2, r3]
ldrsb r1, [r2, r3]           // 56d1 ldrsb r1, [r2, r3]
ldrsb r2, [r2, r3]           // 56d2 ldrsb r2, [r2, r3]
ldrsb r3, [r2, r3]           // 56d3 ldrsb r3, [r2, r3]
ldrsb r4, [r2, r3]           // 56d4 ldrsb r4, [r2, r3]
ldrsb r5, [r2, r3]           // 56d5 ldrsb r5, [r2, r3]
ldrsb r6, [r2, r3]           // 56d6 ldrsb r6, [r2, r3]
ldrsb r7, [r2, r3]           // 56d7 ldrsb r7, [r2, r3]
ldrsb r0, [r3, r3]           // 56d8 ldrsb r0, [r3, r3]
ldrsb r1, [r3, r3]           // 56d9 ldrsb r1, [r3, r3]
ldrsb r2, [r3, r3]           // 56da ldrsb r2, [r3, r3]
ldrsb r3, [r3, r3]           // 56db ldrsb r3, [r3, r3]
ldrsb r4, [r3, r3]           // 56dc ldrsb r4, [r3, r3]
ldrsb r5, [r3, r3]           // 56dd ldrsb r5, [r3, r3]
ldrsb r6, [r3, r3]           // 56de ldrsb r6, [r3, r3]
ldrsb r7, [r3, r3]           // 56df ldrsb r7, [r3, r3]
ldrsb r0, [r4, r3]           // 56e0 ldrsb r0, [r4, r3]
ldrsb r1, [r4, r3]           // 56e1 ldrsb r1, [r4, r3]
ldrsb r2, [r4, r3]           // 56e2 ldrsb r2, [r4, r3]
ldrsb r3, [r4, r3]           // 56e3 ldrsb r3, [r4, r3]
ldrsb r4, [r4, r3]           // 56e4 ldrsb r4, [r4, r3]
ldrsb r5, [r4, r3]           // 56e5 ldrsb r5, [r4, r3]
ldrsb r6, [r4, r3]           // 56e6 ldrsb r6, [r4, r3]
ldrsb r7, [r4, r3]           // 56e7 ldrsb r7, [r4, r3]
ldrsb r0, [r5, r3]           // 56e8 ldrsb r0, [r5, r3]
ldrsb r1, [r5, r3]           // 56e9 ldrsb r1, [r5, r3]
ldrsb r2, [r5, r3]           // 56ea ldrsb r2, [r5, r3]
ldrsb r3, [r5, r3]           // 56eb ldrsb r3, [r5, r3]
ldrsb r4, [r5, r3]           // 56ec ldrsb r4, [r5, r3]
ldrsb r5, [r5, r3]           // 56ed ldrsb r5, [r5, r3]
ldrsb r6, [r5, r3]           // 56ee ldrsb r6, [r5, r3]
ldrsb r7, [r5, r3]           // 56ef ldrsb r7, [r5, r3]
ldrsb r0, [r6, r3]           // 56f0 ldrsb r0, [r6, r3]
ldrsb r1, [r6, r3]           // 56f1 ldrsb r1, [r6, r3]
ldrsb r2, [r6, r3]           // 56f2 ldrsb r2, [r6, r3]
ldrsb r3, [r6, r3]           // 56f3 ldrsb r3, [r6, r3]
ldrsb r4, [r6, r3]           // 56f4 ldrsb r4, [r6, r3]
ldrsb r5, [r6, r3]           // 56f5 ldrsb r5, [r6, r3]
ldrsb r6, [r6, r3]           // 56f6 ldrsb r6, [r6, r3]
ldrsb r7, [r6, r3]           // 56f7 ldrsb r7, [r6, r3]
ldrsb r0, [r7, r3]           // 56f8 ldrsb r0, [r7, r3]
ldrsb r1, [r7, r3]           // 56f9 ldrsb r1, [r7, r3]
ldrsb r2, [r7, r3]           // 56fa ldrsb r2, [r7, r3]
ldrsb r3, [r7, r3]           // 56fb ldrsb r3, [r7, r3]
ldrsb r4, [r7, r3]           // 56fc ldrsb r4, [r7, r3]
ldrsb r5, [r7, r3]           // 56fd ldrsb r5, [r7, r3]
ldrsb r6, [r7, r3]           // 56fe ldrsb r6, [r7, r3]
ldrsb r7, [r7, r3]           // 56ff ldrsb r7, [r7, r3]
ldrsb r0, [r0, r4]           // 5700 ldrsb r0, [r0, r4]
ldrsb r1, [r0, r4]           // 5701 ldrsb r1, [r0, r4]
ldrsb r2, [r0, r4]           // 5702 ldrsb r2, [r0, r4]
ldrsb r3, [r0, r4]           // 5703 ldrsb r3, [r0, r4]
ldrsb r4, [r0, r4]           // 5704 ldrsb r4, [r0, r4]
ldrsb r5, [r0, r4]           // 5705 ldrsb r5, [r0, r4]
ldrsb r6, [r0, r4]           // 5706 ldrsb r6, [r0, r4]
ldrsb r7, [r0, r4]           // 5707 ldrsb r7, [r0, r4]
ldrsb r0, [r1, r4]           // 5708 ldrsb r0, [r1, r4]
ldrsb r1, [r1, r4]           // 5709 ldrsb r1, [r1, r4]
ldrsb r2, [r1, r4]           // 570a ldrsb r2, [r1, r4]
ldrsb r3, [r1, r4]           // 570b ldrsb r3, [r1, r4]
ldrsb r4, [r1, r4]           // 570c ldrsb r4, [r1, r4]
ldrsb r5, [r1, r4]           // 570d ldrsb r5, [r1, r4]
ldrsb r6, [r1, r4]           // 570e ldrsb r6, [r1, r4]
ldrsb r7, [r1, r4]           // 570f ldrsb r7, [r1, r4]
ldrsb r0, [r2, r4]           // 5710 ldrsb r0, [r2, r4]
ldrsb r1, [r2, r4]           // 5711 ldrsb r1, [r2, r4]
ldrsb r2, [r2, r4]           // 5712 ldrsb r2, [r2, r4]
ldrsb r3, [r2, r4]           // 5713 ldrsb r3, [r2, r4]
ldrsb r4, [r2, r4]           // 5714 ldrsb r4, [r2, r4]
ldrsb r5, [r2, r4]           // 5715 ldrsb r5, [r2, r4]
ldrsb r6, [r2, r4]           // 5716 ldrsb r6, [r2, r4]
ldrsb r7, [r2, r4]           // 5717 ldrsb r7, [r2, r4]
ldrsb r0, [r3, r4]           // 5718 ldrsb r0, [r3, r4]
ldrsb r1, [r3, r4]           // 5719 ldrsb r1, [r3, r4]
ldrsb r2, [r3, r4]           // 571a ldrsb r2, [r3, r4]
ldrsb r3, [r3, r4]           // 571b ldrsb r3, [r3, r4]
ldrsb r4, [r3, r4]           // 571c ldrsb r4, [r3, r4]
ldrsb r5, [r3, r4]           // 571d ldrsb r5, [r3, r4]
ldrsb r6, [r3, r4]           // 571e ldrsb r6, [r3, r4]
ldrsb r7, [r3, r4]           // 571f ldrsb r7, [r3, r4]
ldrsb r0, [r4, r4]           // 5720 ldrsb r0, [r4, r4]
ldrsb r1, [r4, r4]           // 5721 ldrsb r1, [r4, r4]
ldrsb r2, [r4, r4]           // 5722 ldrsb r2, [r4, r4]
ldrsb r3, [r4, r4]           // 5723 ldrsb r3, [r4, r4]
ldrsb r4, [r4, r4]           // 5724 ldrsb r4, [r4, r4]
ldrsb r5, [r4, r4]           // 5725 ldrsb r5, [r4, r4]
ldrsb r6, [r4, r4]           // 5726 ldrsb r6, [r4, r4]
ldrsb r7, [r4, r4]           // 5727 ldrsb r7, [r4, r4]
ldrsb r0, [r5, r4]           // 5728 ldrsb r0, [r5, r4]
ldrsb r1, [r5, r4]           // 5729 ldrsb r1, [r5, r4]
ldrsb r2, [r5, r4]           // 572a ldrsb r2, [r5, r4]
ldrsb r3, [r5, r4]           // 572b ldrsb r3, [r5, r4]
ldrsb r4, [r5, r4]           // 572c ldrsb r4, [r5, r4]
ldrsb r5, [r5, r4]           // 572d ldrsb r5, [r5, r4]
ldrsb r6, [r5, r4]           // 572e ldrsb r6, [r5, r4]
ldrsb r7, [r5, r4]           // 572f ldrsb r7, [r5, r4]
ldrsb r0, [r6, r4]           // 5730 ldrsb r0, [r6, r4]
ldrsb r1, [r6, r4]           // 5731 ldrsb r1, [r6, r4]
ldrsb r2, [r6, r4]           // 5732 ldrsb r2, [r6, r4]
ldrsb r3, [r6, r4]           // 5733 ldrsb r3, [r6, r4]
ldrsb r4, [r6, r4]           // 5734 ldrsb r4, [r6, r4]
ldrsb r5, [r6, r4]           // 5735 ldrsb r5, [r6, r4]
ldrsb r6, [r6, r4]           // 5736 ldrsb r6, [r6, r4]
ldrsb r7, [r6, r4]           // 5737 ldrsb r7, [r6, r4]
ldrsb r0, [r7, r4]           // 5738 ldrsb r0, [r7, r4]
ldrsb r1, [r7, r4]           // 5739 ldrsb r1, [r7, r4]
ldrsb r2, [r7, r4]           // 573a ldrsb r2, [r7, r4]
ldrsb r3, [r7, r4]           // 573b ldrsb r3, [r7, r4]
ldrsb r4, [r7, r4]           // 573c ldrsb r4, [r7, r4]
ldrsb r5, [r7, r4]           // 573d ldrsb r5, [r7, r4]
ldrsb r6, [r7, r4]           // 573e ldrsb r6, [r7, r4]
ldrsb r7, [r7, r4]           // 573f ldrsb r7, [r7, r4]
ldrsb r0, [r0, r5]           // 5740 ldrsb r0, [r0, r5]
ldrsb r1, [r0, r5]           // 5741 ldrsb r1, [r0, r5]
ldrsb r2, [r0, r5]           // 5742 ldrsb r2, [r0, r5]
ldrsb r3, [r0, r5]           // 5743 ldrsb r3, [r0, r5]
ldrsb r4, [r0, r5]           // 5744 ldrsb r4, [r0, r5]
ldrsb r5, [r0, r5]           // 5745 ldrsb r5, [r0, r5]
ldrsb r6, [r0, r5]           // 5746 ldrsb r6, [r0, r5]
ldrsb r7, [r0, r5]           // 5747 ldrsb r7, [r0, r5]
ldrsb r0, [r1, r5]           // 5748 ldrsb r0, [r1, r5]
ldrsb r1, [r1, r5]           // 5749 ldrsb r1, [r1, r5]
ldrsb r2, [r1, r5]           // 574a ldrsb r2, [r1, r5]
ldrsb r3, [r1, r5]           // 574b ldrsb r3, [r1, r5]
ldrsb r4, [r1, r5]           // 574c ldrsb r4, [r1, r5]
ldrsb r5, [r1, r5]           // 574d ldrsb r5, [r1, r5]
ldrsb r6, [r1, r5]           // 574e ldrsb r6, [r1, r5]
ldrsb r7, [r1, r5]           // 574f ldrsb r7, [r1, r5]
ldrsb r0, [r2, r5]           // 5750 ldrsb r0, [r2, r5]
ldrsb r1, [r2, r5]           // 5751 ldrsb r1, [r2, r5]
ldrsb r2, [r2, r5]           // 5752 ldrsb r2, [r2, r5]
ldrsb r3, [r2, r5]           // 5753 ldrsb r3, [r2, r5]
ldrsb r4, [r2, r5]           // 5754 ldrsb r4, [r2, r5]
ldrsb r5, [r2, r5]           // 5755 ldrsb r5, [r2, r5]
ldrsb r6, [r2, r5]           // 5756 ldrsb r6, [r2, r5]
ldrsb r7, [r2, r5]           // 5757 ldrsb r7, [r2, r5]
ldrsb r0, [r3, r5]           // 5758 ldrsb r0, [r3, r5]
ldrsb r1, [r3, r5]           // 5759 ldrsb r1, [r3, r5]
ldrsb r2, [r3, r5]           // 575a ldrsb r2, [r3, r5]
ldrsb r3, [r3, r5]           // 575b ldrsb r3, [r3, r5]
ldrsb r4, [r3, r5]           // 575c ldrsb r4, [r3, r5]
ldrsb r5, [r3, r5]           // 575d ldrsb r5, [r3, r5]
ldrsb r6, [r3, r5]           // 575e ldrsb r6, [r3, r5]
ldrsb r7, [r3, r5]           // 575f ldrsb r7, [r3, r5]
ldrsb r0, [r4, r5]           // 5760 ldrsb r0, [r4, r5]
ldrsb r1, [r4, r5]           // 5761 ldrsb r1, [r4, r5]
ldrsb r2, [r4, r5]           // 5762 ldrsb r2, [r4, r5]
ldrsb r3, [r4, r5]           // 5763 ldrsb r3, [r4, r5]
ldrsb r4, [r4, r5]           // 5764 ldrsb r4, [r4, r5]
ldrsb r5, [r4, r5]           // 5765 ldrsb r5, [r4, r5]
ldrsb r6, [r4, r5]           // 5766 ldrsb r6, [r4, r5]
ldrsb r7, [r4, r5]           // 5767 ldrsb r7, [r4, r5]
ldrsb r0, [r5, r5]           // 5768 ldrsb r0, [r5, r5]
ldrsb r1, [r5, r5]           // 5769 ldrsb r1, [r5, r5]
ldrsb r2, [r5, r5]           // 576a ldrsb r2, [r5, r5]
ldrsb r3, [r5, r5]           // 576b ldrsb r3, [r5, r5]
ldrsb r4, [r5, r5]           // 576c ldrsb r4, [r5, r5]
ldrsb r5, [r5, r5]           // 576d ldrsb r5, [r5, r5]
ldrsb r6, [r5, r5]           // 576e ldrsb r6, [r5, r5]
ldrsb r7, [r5, r5]           // 576f ldrsb r7, [r5, r5]
ldrsb r0, [r6, r5]           // 5770 ldrsb r0, [r6, r5]
ldrsb r1, [r6, r5]           // 5771 ldrsb r1, [r6, r5]
ldrsb r2, [r6, r5]           // 5772 ldrsb r2, [r6, r5]
ldrsb r3, [r6, r5]           // 5773 ldrsb r3, [r6, r5]
ldrsb r4, [r6, r5]           // 5774 ldrsb r4, [r6, r5]
ldrsb r5, [r6, r5]           // 5775 ldrsb r5, [r6, r5]
ldrsb r6, [r6, r5]           // 5776 ldrsb r6, [r6, r5]
ldrsb r7, [r6, r5]           // 5777 ldrsb r7, [r6, r5]
ldrsb r0, [r7, r5]           // 5778 ldrsb r0, [r7, r5]
ldrsb r1, [r7, r5]           // 5779 ldrsb r1, [r7, r5]
ldrsb r2, [r7, r5]           // 577a ldrsb r2, [r7, r5]
ldrsb r3, [r7, r5]           // 577b ldrsb r3, [r7, r5]
ldrsb r4, [r7, r5]           // 577c ldrsb r4, [r7, r5]
ldrsb r5, [r7, r5]           // 577d ldrsb r5, [r7, r5]
ldrsb r6, [r7, r5]           // 577e ldrsb r6, [r7, r5]
ldrsb r7, [r7, r5]           // 577f ldrsb r7, [r7, r5]
ldrsb r0, [r0, r6]           // 5780 ldrsb r0, [r0, r6]
ldrsb r1, [r0, r6]           // 5781 ldrsb r1, [r0, r6]
ldrsb r2, [r0, r6]           // 5782 ldrsb r2, [r0, r6]
ldrsb r3, [r0, r6]           // 5783 ldrsb r3, [r0, r6]
ldrsb r4, [r0, r6]           // 5784 ldrsb r4, [r0, r6]
ldrsb r5, [r0, r6]           // 5785 ldrsb r5, [r0, r6]
ldrsb r6, [r0, r6]           // 5786 ldrsb r6, [r0, r6]
ldrsb r7, [r0, r6]           // 5787 ldrsb r7, [r0, r6]
ldrsb r0, [r1, r6]           // 5788 ldrsb r0, [r1, r6]
ldrsb r1, [r1, r6]           // 5789 ldrsb r1, [r1, r6]
ldrsb r2, [r1, r6]           // 578a ldrsb r2, [r1, r6]
ldrsb r3, [r1, r6]           // 578b ldrsb r3, [r1, r6]
ldrsb r4, [r1, r6]           // 578c ldrsb r4, [r1, r6]
ldrsb r5, [r1, r6]           // 578d ldrsb r5, [r1, r6]
ldrsb r6, [r1, r6]           // 578e ldrsb r6, [r1, r6]
ldrsb r7, [r1, r6]           // 578f ldrsb r7, [r1, r6]
ldrsb r0, [r2, r6]           // 5790 ldrsb r0, [r2, r6]
ldrsb r1, [r2, r6]           // 5791 ldrsb r1, [r2, r6]
ldrsb r2, [r2, r6]           // 5792 ldrsb r2, [r2, r6]
ldrsb r3, [r2, r6]           // 5793 ldrsb r3, [r2, r6]
ldrsb r4, [r2, r6]           // 5794 ldrsb r4, [r2, r6]
ldrsb r5, [r2, r6]           // 5795 ldrsb r5, [r2, r6]
ldrsb r6, [r2, r6]           // 5796 ldrsb r6, [r2, r6]
ldrsb r7, [r2, r6]           // 5797 ldrsb r7, [r2, r6]
ldrsb r0, [r3, r6]           // 5798 ldrsb r0, [r3, r6]
ldrsb r1, [r3, r6]           // 5799 ldrsb r1, [r3, r6]
ldrsb r2, [r3, r6]           // 579a ldrsb r2, [r3, r6]
ldrsb r3, [r3, r6]           // 579b ldrsb r3, [r3, r6]
ldrsb r4, [r3, r6]           // 579c ldrsb r4, [r3, r6]
ldrsb r5, [r3, r6]           // 579d ldrsb r5, [r3, r6]
ldrsb r6, [r3, r6]           // 579e ldrsb r6, [r3, r6]
ldrsb r7, [r3, r6]           // 579f ldrsb r7, [r3, r6]
ldrsb r0, [r4, r6]           // 57a0 ldrsb r0, [r4, r6]
ldrsb r1, [r4, r6]           // 57a1 ldrsb r1, [r4, r6]
ldrsb r2, [r4, r6]           // 57a2 ldrsb r2, [r4, r6]
ldrsb r3, [r4, r6]           // 57a3 ldrsb r3, [r4, r6]
ldrsb r4, [r4, r6]           // 57a4 ldrsb r4, [r4, r6]
ldrsb r5, [r4, r6]           // 57a5 ldrsb r5, [r4, r6]
ldrsb r6, [r4, r6]           // 57a6 ldrsb r6, [r4, r6]
ldrsb r7, [r4, r6]           // 57a7 ldrsb r7, [r4, r6]
ldrsb r0, [r5, r6]           // 57a8 ldrsb r0, [r5, r6]
ldrsb r1, [r5, r6]           // 57a9 ldrsb r1, [r5, r6]
ldrsb r2, [r5, r6]           // 57aa ldrsb r2, [r5, r6]
ldrsb r3, [r5, r6]           // 57ab ldrsb r3, [r5, r6]
ldrsb r4, [r5, r6]           // 57ac ldrsb r4, [r5, r6]
ldrsb r5, [r5, r6]           // 57ad ldrsb r5, [r5, r6]
ldrsb r6, [r5, r6]           // 57ae ldrsb r6, [r5, r6]
ldrsb r7, [r5, r6]           // 57af ldrsb r7, [r5, r6]
ldrsb r0, [r6, r6]           // 57b0 ldrsb r0, [r6, r6]
ldrsb r1, [r6, r6]           // 57b1 ldrsb r1, [r6, r6]
ldrsb r2, [r6, r6]           // 57b2 ldrsb r2, [r6, r6]
ldrsb r3, [r6, r6]           // 57b3 ldrsb r3, [r6, r6]
ldrsb r4, [r6, r6]           // 57b4 ldrsb r4, [r6, r6]
ldrsb r5, [r6, r6]           // 57b5 ldrsb r5, [r6, r6]
ldrsb r6, [r6, r6]           // 57b6 ldrsb r6, [r6, r6]
ldrsb r7, [r6, r6]           // 57b7 ldrsb r7, [r6, r6]
ldrsb r0, [r7, r6]           // 57b8 ldrsb r0, [r7, r6]
ldrsb r1, [r7, r6]           // 57b9 ldrsb r1, [r7, r6]
ldrsb r2, [r7, r6]           // 57ba ldrsb r2, [r7, r6]
ldrsb r3, [r7, r6]           // 57bb ldrsb r3, [r7, r6]
ldrsb r4, [r7, r6]           // 57bc ldrsb r4, [r7, r6]
ldrsb r5, [r7, r6]           // 57bd ldrsb r5, [r7, r6]
ldrsb r6, [r7, r6]           // 57be ldrsb r6, [r7, r6]
ldrsb r7, [r7, r6]           // 57bf ldrsb r7, [r7, r6]
ldrsb r0, [r0, r7]           // 57c0 ldrsb r0, [r0, r7]
ldrsb r1, [r0, r7]           // 57c1 ldrsb r1, [r0, r7]
ldrsb r2, [r0, r7]           // 57c2 ldrsb r2, [r0, r7]
ldrsb r3, [r0, r7]           // 57c3 ldrsb r3, [r0, r7]
ldrsb r4, [r0, r7]           // 57c4 ldrsb r4, [r0, r7]
ldrsb r5, [r0, r7]           // 57c5 ldrsb r5, [r0, r7]
ldrsb r6, [r0, r7]           // 57c6 ldrsb r6, [r0, r7]
ldrsb r7, [r0, r7]           // 57c7 ldrsb r7, [r0, r7]
ldrsb r0, [r1, r7]           // 57c8 ldrsb r0, [r1, r7]
ldrsb r1, [r1, r7]           // 57c9 ldrsb r1, [r1, r7]
ldrsb r2, [r1, r7]           // 57ca ldrsb r2, [r1, r7]
ldrsb r3, [r1, r7]           // 57cb ldrsb r3, [r1, r7]
ldrsb r4, [r1, r7]           // 57cc ldrsb r4, [r1, r7]
ldrsb r5, [r1, r7]           // 57cd ldrsb r5, [r1, r7]
ldrsb r6, [r1, r7]           // 57ce ldrsb r6, [r1, r7]
ldrsb r7, [r1, r7]           // 57cf ldrsb r7, [r1, r7]
ldrsb r0, [r2, r7]           // 57d0 ldrsb r0, [r2, r7]
ldrsb r1, [r2, r7]           // 57d1 ldrsb r1, [r2, r7]
ldrsb r2, [r2, r7]           // 57d2 ldrsb r2, [r2, r7]
ldrsb r3, [r2, r7]           // 57d3 ldrsb r3, [r2, r7]
ldrsb r4, [r2, r7]           // 57d4 ldrsb r4, [r2, r7]
ldrsb r5, [r2, r7]           // 57d5 ldrsb r5, [r2, r7]
ldrsb r6, [r2, r7]           // 57d6 ldrsb r6, [r2, r7]
ldrsb r7, [r2, r7]           // 57d7 ldrsb r7, [r2, r7]
ldrsb r0, [r3, r7]           // 57d8 ldrsb r0, [r3, r7]
ldrsb r1, [r3, r7]           // 57d9 ldrsb r1, [r3, r7]
ldrsb r2, [r3, r7]           // 57da ldrsb r2, [r3, r7]
ldrsb r3, [r3, r7]           // 57db ldrsb r3, [r3, r7]
ldrsb r4, [r3, r7]           // 57dc ldrsb r4, [r3, r7]
ldrsb r5, [r3, r7]           // 57dd ldrsb r5, [r3, r7]
ldrsb r6, [r3, r7]           // 57de ldrsb r6, [r3, r7]
ldrsb r7, [r3, r7]           // 57df ldrsb r7, [r3, r7]
ldrsb r0, [r4, r7]           // 57e0 ldrsb r0, [r4, r7]
ldrsb r1, [r4, r7]           // 57e1 ldrsb r1, [r4, r7]
ldrsb r2, [r4, r7]           // 57e2 ldrsb r2, [r4, r7]
ldrsb r3, [r4, r7]           // 57e3 ldrsb r3, [r4, r7]
ldrsb r4, [r4, r7]           // 57e4 ldrsb r4, [r4, r7]
ldrsb r5, [r4, r7]           // 57e5 ldrsb r5, [r4, r7]
ldrsb r6, [r4, r7]           // 57e6 ldrsb r6, [r4, r7]
ldrsb r7, [r4, r7]           // 57e7 ldrsb r7, [r4, r7]
ldrsb r0, [r5, r7]           // 57e8 ldrsb r0, [r5, r7]
ldrsb r1, [r5, r7]           // 57e9 ldrsb r1, [r5, r7]
ldrsb r2, [r5, r7]           // 57ea ldrsb r2, [r5, r7]
ldrsb r3, [r5, r7]           // 57eb ldrsb r3, [r5, r7]
ldrsb r4, [r5, r7]           // 57ec ldrsb r4, [r5, r7]
ldrsb r5, [r5, r7]           // 57ed ldrsb r5, [r5, r7]
ldrsb r6, [r5, r7]           // 57ee ldrsb r6, [r5, r7]
ldrsb r7, [r5, r7]           // 57ef ldrsb r7, [r5, r7]
ldrsb r0, [r6, r7]           // 57f0 ldrsb r0, [r6, r7]
ldrsb r1, [r6, r7]           // 57f1 ldrsb r1, [r6, r7]
ldrsb r2, [r6, r7]           // 57f2 ldrsb r2, [r6, r7]
ldrsb r3, [r6, r7]           // 57f3 ldrsb r3, [r6, r7]
ldrsb r4, [r6, r7]           // 57f4 ldrsb r4, [r6, r7]
ldrsb r5, [r6, r7]           // 57f5 ldrsb r5, [r6, r7]
ldrsb r6, [r6, r7]           // 57f6 ldrsb r6, [r6, r7]
ldrsb r7, [r6, r7]           // 57f7 ldrsb r7, [r6, r7]
ldrsb r0, [r7, r7]           // 57f8 ldrsb r0, [r7, r7]
ldrsb r1, [r7, r7]           // 57f9 ldrsb r1, [r7, r7]
ldrsb r2, [r7, r7]           // 57fa ldrsb r2, [r7, r7]
ldrsb r3, [r7, r7]           // 57fb ldrsb r3, [r7, r7]
ldrsb r4, [r7, r7]           // 57fc ldrsb r4, [r7, r7]
ldrsb r5, [r7, r7]           // 57fd ldrsb r5, [r7, r7]
ldrsb r6, [r7, r7]           // 57fe ldrsb r6, [r7, r7]
ldrsb r7, [r7, r7]           // 57ff ldrsb r7, [r7, r7]

ldr r0, [r0, r0]             // 5800 ldr r0, [r0, r0]
ldr r1, [r0, r0]             // 5801 ldr r1, [r0, r0]
ldr r2, [r0, r0]             // 5802 ldr r2, [r0, r0]
ldr r3, [r0, r0]             // 5803 ldr r3, [r0, r0]
ldr r4, [r0, r0]             // 5804 ldr r4, [r0, r0]
ldr r5, [r0, r0]             // 5805 ldr r5, [r0, r0]
ldr r6, [r0, r0]             // 5806 ldr r6, [r0, r0]
ldr r7, [r0, r0]             // 5807 ldr r7, [r0, r0]
ldr r0, [r1, r0]             // 5808 ldr r0, [r1, r0]
ldr r1, [r1, r0]             // 5809 ldr r1, [r1, r0]
ldr r2, [r1, r0]             // 580a ldr r2, [r1, r0]
ldr r3, [r1, r0]             // 580b ldr r3, [r1, r0]
ldr r4, [r1, r0]             // 580c ldr r4, [r1, r0]
ldr r5, [r1, r0]             // 580d ldr r5, [r1, r0]
ldr r6, [r1, r0]             // 580e ldr r6, [r1, r0]
ldr r7, [r1, r0]             // 580f ldr r7, [r1, r0]
ldr r0, [r2, r0]             // 5810 ldr r0, [r2, r0]
ldr r1, [r2, r0]             // 5811 ldr r1, [r2, r0]
ldr r2, [r2, r0]             // 5812 ldr r2, [r2, r0]
ldr r3, [r2, r0]             // 5813 ldr r3, [r2, r0]
ldr r4, [r2, r0]             // 5814 ldr r4, [r2, r0]
ldr r5, [r2, r0]             // 5815 ldr r5, [r2, r0]
ldr r6, [r2, r0]             // 5816 ldr r6, [r2, r0]
ldr r7, [r2, r0]             // 5817 ldr r7, [r2, r0]
ldr r0, [r3, r0]             // 5818 ldr r0, [r3, r0]
ldr r1, [r3, r0]             // 5819 ldr r1, [r3, r0]
ldr r2, [r3, r0]             // 581a ldr r2, [r3, r0]
ldr r3, [r3, r0]             // 581b ldr r3, [r3, r0]
ldr r4, [r3, r0]             // 581c ldr r4, [r3, r0]
ldr r5, [r3, r0]             // 581d ldr r5, [r3, r0]
ldr r6, [r3, r0]             // 581e ldr r6, [r3, r0]
ldr r7, [r3, r0]             // 581f ldr r7, [r3, r0]
ldr r0, [r4, r0]             // 5820 ldr r0, [r4, r0]
ldr r1, [r4, r0]             // 5821 ldr r1, [r4, r0]
ldr r2, [r4, r0]             // 5822 ldr r2, [r4, r0]
ldr r3, [r4, r0]             // 5823 ldr r3, [r4, r0]
ldr r4, [r4, r0]             // 5824 ldr r4, [r4, r0]
ldr r5, [r4, r0]             // 5825 ldr r5, [r4, r0]
ldr r6, [r4, r0]             // 5826 ldr r6, [r4, r0]
ldr r7, [r4, r0]             // 5827 ldr r7, [r4, r0]
ldr r0, [r5, r0]             // 5828 ldr r0, [r5, r0]
ldr r1, [r5, r0]             // 5829 ldr r1, [r5, r0]
ldr r2, [r5, r0]             // 582a ldr r2, [r5, r0]
ldr r3, [r5, r0]             // 582b ldr r3, [r5, r0]
ldr r4, [r5, r0]             // 582c ldr r4, [r5, r0]
ldr r5, [r5, r0]             // 582d ldr r5, [r5, r0]
ldr r6, [r5, r0]             // 582e ldr r6, [r5, r0]
ldr r7, [r5, r0]             // 582f ldr r7, [r5, r0]
ldr r0, [r6, r0]             // 5830 ldr r0, [r6, r0]
ldr r1, [r6, r0]             // 5831 ldr r1, [r6, r0]
ldr r2, [r6, r0]             // 5832 ldr r2, [r6, r0]
ldr r3, [r6, r0]             // 5833 ldr r3, [r6, r0]
ldr r4, [r6, r0]             // 5834 ldr r4, [r6, r0]
ldr r5, [r6, r0]             // 5835 ldr r5, [r6, r0]
ldr r6, [r6, r0]             // 5836 ldr r6, [r6, r0]
ldr r7, [r6, r0]             // 5837 ldr r7, [r6, r0]
ldr r0, [r7, r0]             // 5838 ldr r0, [r7, r0]
ldr r1, [r7, r0]             // 5839 ldr r1, [r7, r0]
ldr r2, [r7, r0]             // 583a ldr r2, [r7, r0]
ldr r3, [r7, r0]             // 583b ldr r3, [r7, r0]
ldr r4, [r7, r0]             // 583c ldr r4, [r7, r0]
ldr r5, [r7, r0]             // 583d ldr r5, [r7, r0]
ldr r6, [r7, r0]             // 583e ldr r6, [r7, r0]
ldr r7, [r7, r0]             // 583f ldr r7, [r7, r0]
ldr r0, [r0, r1]             // 5840 ldr r0, [r0, r1]
ldr r1, [r0, r1]             // 5841 ldr r1, [r0, r1]
ldr r2, [r0, r1]             // 5842 ldr r2, [r0, r1]
ldr r3, [r0, r1]             // 5843 ldr r3, [r0, r1]
ldr r4, [r0, r1]             // 5844 ldr r4, [r0, r1]
ldr r5, [r0, r1]             // 5845 ldr r5, [r0, r1]
ldr r6, [r0, r1]             // 5846 ldr r6, [r0, r1]
ldr r7, [r0, r1]             // 5847 ldr r7, [r0, r1]
ldr r0, [r1, r1]             // 5848 ldr r0, [r1, r1]
ldr r1, [r1, r1]             // 5849 ldr r1, [r1, r1]
ldr r2, [r1, r1]             // 584a ldr r2, [r1, r1]
ldr r3, [r1, r1]             // 584b ldr r3, [r1, r1]
ldr r4, [r1, r1]             // 584c ldr r4, [r1, r1]
ldr r5, [r1, r1]             // 584d ldr r5, [r1, r1]
ldr r6, [r1, r1]             // 584e ldr r6, [r1, r1]
ldr r7, [r1, r1]             // 584f ldr r7, [r1, r1]
ldr r0, [r2, r1]             // 5850 ldr r0, [r2, r1]
ldr r1, [r2, r1]             // 5851 ldr r1, [r2, r1]
ldr r2, [r2, r1]             // 5852 ldr r2, [r2, r1]
ldr r3, [r2, r1]             // 5853 ldr r3, [r2, r1]
ldr r4, [r2, r1]             // 5854 ldr r4, [r2, r1]
ldr r5, [r2, r1]             // 5855 ldr r5, [r2, r1]
ldr r6, [r2, r1]             // 5856 ldr r6, [r2, r1]
ldr r7, [r2, r1]             // 5857 ldr r7, [r2, r1]
ldr r0, [r3, r1]             // 5858 ldr r0, [r3, r1]
ldr r1, [r3, r1]             // 5859 ldr r1, [r3, r1]
ldr r2, [r3, r1]             // 585a ldr r2, [r3, r1]
ldr r3, [r3, r1]             // 585b ldr r3, [r3, r1]
ldr r4, [r3, r1]             // 585c ldr r4, [r3, r1]
ldr r5, [r3, r1]             // 585d ldr r5, [r3, r1]
ldr r6, [r3, r1]             // 585e ldr r6, [r3, r1]
ldr r7, [r3, r1]             // 585f ldr r7, [r3, r1]
ldr r0, [r4, r1]             // 5860 ldr r0, [r4, r1]
ldr r1, [r4, r1]             // 5861 ldr r1, [r4, r1]
ldr r2, [r4, r1]             // 5862 ldr r2, [r4, r1]
ldr r3, [r4, r1]             // 5863 ldr r3, [r4, r1]
ldr r4, [r4, r1]             // 5864 ldr r4, [r4, r1]
ldr r5, [r4, r1]             // 5865 ldr r5, [r4, r1]
ldr r6, [r4, r1]             // 5866 ldr r6, [r4, r1]
ldr r7, [r4, r1]             // 5867 ldr r7, [r4, r1]
ldr r0, [r5, r1]             // 5868 ldr r0, [r5, r1]
ldr r1, [r5, r1]             // 5869 ldr r1, [r5, r1]
ldr r2, [r5, r1]             // 586a ldr r2, [r5, r1]
ldr r3, [r5, r1]             // 586b ldr r3, [r5, r1]
ldr r4, [r5, r1]             // 586c ldr r4, [r5, r1]
ldr r5, [r5, r1]             // 586d ldr r5, [r5, r1]
ldr r6, [r5, r1]             // 586e ldr r6, [r5, r1]
ldr r7, [r5, r1]             // 586f ldr r7, [r5, r1]
ldr r0, [r6, r1]             // 5870 ldr r0, [r6, r1]
ldr r1, [r6, r1]             // 5871 ldr r1, [r6, r1]
ldr r2, [r6, r1]             // 5872 ldr r2, [r6, r1]
ldr r3, [r6, r1]             // 5873 ldr r3, [r6, r1]
ldr r4, [r6, r1]             // 5874 ldr r4, [r6, r1]
ldr r5, [r6, r1]             // 5875 ldr r5, [r6, r1]
ldr r6, [r6, r1]             // 5876 ldr r6, [r6, r1]
ldr r7, [r6, r1]             // 5877 ldr r7, [r6, r1]
ldr r0, [r7, r1]             // 5878 ldr r0, [r7, r1]
ldr r1, [r7, r1]             // 5879 ldr r1, [r7, r1]
ldr r2, [r7, r1]             // 587a ldr r2, [r7, r1]
ldr r3, [r7, r1]             // 587b ldr r3, [r7, r1]
ldr r4, [r7, r1]             // 587c ldr r4, [r7, r1]
ldr r5, [r7, r1]             // 587d ldr r5, [r7, r1]
ldr r6, [r7, r1]             // 587e ldr r6, [r7, r1]
ldr r7, [r7, r1]             // 587f ldr r7, [r7, r1]
ldr r0, [r0, r2]             // 5880 ldr r0, [r0, r2]
ldr r1, [r0, r2]             // 5881 ldr r1, [r0, r2]
ldr r2, [r0, r2]             // 5882 ldr r2, [r0, r2]
ldr r3, [r0, r2]             // 5883 ldr r3, [r0, r2]
ldr r4, [r0, r2]             // 5884 ldr r4, [r0, r2]
ldr r5, [r0, r2]             // 5885 ldr r5, [r0, r2]
ldr r6, [r0, r2]             // 5886 ldr r6, [r0, r2]
ldr r7, [r0, r2]             // 5887 ldr r7, [r0, r2]
ldr r0, [r1, r2]             // 5888 ldr r0, [r1, r2]
ldr r1, [r1, r2]             // 5889 ldr r1, [r1, r2]
ldr r2, [r1, r2]             // 588a ldr r2, [r1, r2]
ldr r3, [r1, r2]             // 588b ldr r3, [r1, r2]
ldr r4, [r1, r2]             // 588c ldr r4, [r1, r2]
ldr r5, [r1, r2]             // 588d ldr r5, [r1, r2]
ldr r6, [r1, r2]             // 588e ldr r6, [r1, r2]
ldr r7, [r1, r2]             // 588f ldr r7, [r1, r2]
ldr r0, [r2, r2]             // 5890 ldr r0, [r2, r2]
ldr r1, [r2, r2]             // 5891 ldr r1, [r2, r2]
ldr r2, [r2, r2]             // 5892 ldr r2, [r2, r2]
ldr r3, [r2, r2]             // 5893 ldr r3, [r2, r2]
ldr r4, [r2, r2]             // 5894 ldr r4, [r2, r2]
ldr r5, [r2, r2]             // 5895 ldr r5, [r2, r2]
ldr r6, [r2, r2]             // 5896 ldr r6, [r2, r2]
ldr r7, [r2, r2]             // 5897 ldr r7, [r2, r2]
ldr r0, [r3, r2]             // 5898 ldr r0, [r3, r2]
ldr r1, [r3, r2]             // 5899 ldr r1, [r3, r2]
ldr r2, [r3, r2]             // 589a ldr r2, [r3, r2]
ldr r3, [r3, r2]             // 589b ldr r3, [r3, r2]
ldr r4, [r3, r2]             // 589c ldr r4, [r3, r2]
ldr r5, [r3, r2]             // 589d ldr r5, [r3, r2]
ldr r6, [r3, r2]             // 589e ldr r6, [r3, r2]
ldr r7, [r3, r2]             // 589f ldr r7, [r3, r2]
ldr r0, [r4, r2]             // 58a0 ldr r0, [r4, r2]
ldr r1, [r4, r2]             // 58a1 ldr r1, [r4, r2]
ldr r2, [r4, r2]             // 58a2 ldr r2, [r4, r2]
ldr r3, [r4, r2]             // 58a3 ldr r3, [r4, r2]
ldr r4, [r4, r2]             // 58a4 ldr r4, [r4, r2]
ldr r5, [r4, r2]             // 58a5 ldr r5, [r4, r2]
ldr r6, [r4, r2]             // 58a6 ldr r6, [r4, r2]
ldr r7, [r4, r2]             // 58a7 ldr r7, [r4, r2]
ldr r0, [r5, r2]             // 58a8 ldr r0, [r5, r2]
ldr r1, [r5, r2]             // 58a9 ldr r1, [r5, r2]
ldr r2, [r5, r2]             // 58aa ldr r2, [r5, r2]
ldr r3, [r5, r2]             // 58ab ldr r3, [r5, r2]
ldr r4, [r5, r2]             // 58ac ldr r4, [r5, r2]
ldr r5, [r5, r2]             // 58ad ldr r5, [r5, r2]
ldr r6, [r5, r2]             // 58ae ldr r6, [r5, r2]
ldr r7, [r5, r2]             // 58af ldr r7, [r5, r2]
ldr r0, [r6, r2]             // 58b0 ldr r0, [r6, r2]
ldr r1, [r6, r2]             // 58b1 ldr r1, [r6, r2]
ldr r2, [r6, r2]             // 58b2 ldr r2, [r6, r2]
ldr r3, [r6, r2]             // 58b3 ldr r3, [r6, r2]
ldr r4, [r6, r2]             // 58b4 ldr r4, [r6, r2]
ldr r5, [r6, r2]             // 58b5 ldr r5, [r6, r2]
ldr r6, [r6, r2]             // 58b6 ldr r6, [r6, r2]
ldr r7, [r6, r2]             // 58b7 ldr r7, [r6, r2]
ldr r0, [r7, r2]             // 58b8 ldr r0, [r7, r2]
ldr r1, [r7, r2]             // 58b9 ldr r1, [r7, r2]
ldr r2, [r7, r2]             // 58ba ldr r2, [r7, r2]
ldr r3, [r7, r2]             // 58bb ldr r3, [r7, r2]
ldr r4, [r7, r2]             // 58bc ldr r4, [r7, r2]
ldr r5, [r7, r2]             // 58bd ldr r5, [r7, r2]
ldr r6, [r7, r2]             // 58be ldr r6, [r7, r2]
ldr r7, [r7, r2]             // 58bf ldr r7, [r7, r2]
ldr r0, [r0, r3]             // 58c0 ldr r0, [r0, r3]
ldr r1, [r0, r3]             // 58c1 ldr r1, [r0, r3]
ldr r2, [r0, r3]             // 58c2 ldr r2, [r0, r3]
ldr r3, [r0, r3]             // 58c3 ldr r3, [r0, r3]
ldr r4, [r0, r3]             // 58c4 ldr r4, [r0, r3]
ldr r5, [r0, r3]             // 58c5 ldr r5, [r0, r3]
ldr r6, [r0, r3]             // 58c6 ldr r6, [r0, r3]
ldr r7, [r0, r3]             // 58c7 ldr r7, [r0, r3]
ldr r0, [r1, r3]             // 58c8 ldr r0, [r1, r3]
ldr r1, [r1, r3]             // 58c9 ldr r1, [r1, r3]
ldr r2, [r1, r3]             // 58ca ldr r2, [r1, r3]
ldr r3, [r1, r3]             // 58cb ldr r3, [r1, r3]
ldr r4, [r1, r3]             // 58cc ldr r4, [r1, r3]
ldr r5, [r1, r3]             // 58cd ldr r5, [r1, r3]
ldr r6, [r1, r3]             // 58ce ldr r6, [r1, r3]
ldr r7, [r1, r3]             // 58cf ldr r7, [r1, r3]
ldr r0, [r2, r3]             // 58d0 ldr r0, [r2, r3]
ldr r1, [r2, r3]             // 58d1 ldr r1, [r2, r3]
ldr r2, [r2, r3]             // 58d2 ldr r2, [r2, r3]
ldr r3, [r2, r3]             // 58d3 ldr r3, [r2, r3]
ldr r4, [r2, r3]             // 58d4 ldr r4, [r2, r3]
ldr r5, [r2, r3]             // 58d5 ldr r5, [r2, r3]
ldr r6, [r2, r3]             // 58d6 ldr r6, [r2, r3]
ldr r7, [r2, r3]             // 58d7 ldr r7, [r2, r3]
ldr r0, [r3, r3]             // 58d8 ldr r0, [r3, r3]
ldr r1, [r3, r3]             // 58d9 ldr r1, [r3, r3]
ldr r2, [r3, r3]             // 58da ldr r2, [r3, r3]
ldr r3, [r3, r3]             // 58db ldr r3, [r3, r3]
ldr r4, [r3, r3]             // 58dc ldr r4, [r3, r3]
ldr r5, [r3, r3]             // 58dd ldr r5, [r3, r3]
ldr r6, [r3, r3]             // 58de ldr r6, [r3, r3]
ldr r7, [r3, r3]             // 58df ldr r7, [r3, r3]
ldr r0, [r4, r3]             // 58e0 ldr r0, [r4, r3]
ldr r1, [r4, r3]             // 58e1 ldr r1, [r4, r3]
ldr r2, [r4, r3]             // 58e2 ldr r2, [r4, r3]
ldr r3, [r4, r3]             // 58e3 ldr r3, [r4, r3]
ldr r4, [r4, r3]             // 58e4 ldr r4, [r4, r3]
ldr r5, [r4, r3]             // 58e5 ldr r5, [r4, r3]
ldr r6, [r4, r3]             // 58e6 ldr r6, [r4, r3]
ldr r7, [r4, r3]             // 58e7 ldr r7, [r4, r3]
ldr r0, [r5, r3]             // 58e8 ldr r0, [r5, r3]
ldr r1, [r5, r3]             // 58e9 ldr r1, [r5, r3]
ldr r2, [r5, r3]             // 58ea ldr r2, [r5, r3]
ldr r3, [r5, r3]             // 58eb ldr r3, [r5, r3]
ldr r4, [r5, r3]             // 58ec ldr r4, [r5, r3]
ldr r5, [r5, r3]             // 58ed ldr r5, [r5, r3]
ldr r6, [r5, r3]             // 58ee ldr r6, [r5, r3]
ldr r7, [r5, r3]             // 58ef ldr r7, [r5, r3]
ldr r0, [r6, r3]             // 58f0 ldr r0, [r6, r3]
ldr r1, [r6, r3]             // 58f1 ldr r1, [r6, r3]
ldr r2, [r6, r3]             // 58f2 ldr r2, [r6, r3]
ldr r3, [r6, r3]             // 58f3 ldr r3, [r6, r3]
ldr r4, [r6, r3]             // 58f4 ldr r4, [r6, r3]
ldr r5, [r6, r3]             // 58f5 ldr r5, [r6, r3]
ldr r6, [r6, r3]             // 58f6 ldr r6, [r6, r3]
ldr r7, [r6, r3]             // 58f7 ldr r7, [r6, r3]
ldr r0, [r7, r3]             // 58f8 ldr r0, [r7, r3]
ldr r1, [r7, r3]             // 58f9 ldr r1, [r7, r3]
ldr r2, [r7, r3]             // 58fa ldr r2, [r7, r3]
ldr r3, [r7, r3]             // 58fb ldr r3, [r7, r3]
ldr r4, [r7, r3]             // 58fc ldr r4, [r7, r3]
ldr r5, [r7, r3]             // 58fd ldr r5, [r7, r3]
ldr r6, [r7, r3]             // 58fe ldr r6, [r7, r3]
ldr r7, [r7, r3]             // 58ff ldr r7, [r7, r3]
ldr r0, [r0, r4]             // 5900 ldr r0, [r0, r4]
ldr r1, [r0, r4]             // 5901 ldr r1, [r0, r4]
ldr r2, [r0, r4]             // 5902 ldr r2, [r0, r4]
ldr r3, [r0, r4]             // 5903 ldr r3, [r0, r4]
ldr r4, [r0, r4]             // 5904 ldr r4, [r0, r4]
ldr r5, [r0, r4]             // 5905 ldr r5, [r0, r4]
ldr r6, [r0, r4]             // 5906 ldr r6, [r0, r4]
ldr r7, [r0, r4]             // 5907 ldr r7, [r0, r4]
ldr r0, [r1, r4]             // 5908 ldr r0, [r1, r4]
ldr r1, [r1, r4]             // 5909 ldr r1, [r1, r4]
ldr r2, [r1, r4]             // 590a ldr r2, [r1, r4]
ldr r3, [r1, r4]             // 590b ldr r3, [r1, r4]
ldr r4, [r1, r4]             // 590c ldr r4, [r1, r4]
ldr r5, [r1, r4]             // 590d ldr r5, [r1, r4]
ldr r6, [r1, r4]             // 590e ldr r6, [r1, r4]
ldr r7, [r1, r4]             // 590f ldr r7, [r1, r4]
ldr r0, [r2, r4]             // 5910 ldr r0, [r2, r4]
ldr r1, [r2, r4]             // 5911 ldr r1, [r2, r4]
ldr r2, [r2, r4]             // 5912 ldr r2, [r2, r4]
ldr r3, [r2, r4]             // 5913 ldr r3, [r2, r4]
ldr r4, [r2, r4]             // 5914 ldr r4, [r2, r4]
ldr r5, [r2, r4]             // 5915 ldr r5, [r2, r4]
ldr r6, [r2, r4]             // 5916 ldr r6, [r2, r4]
ldr r7, [r2, r4]             // 5917 ldr r7, [r2, r4]
ldr r0, [r3, r4]             // 5918 ldr r0, [r3, r4]
ldr r1, [r3, r4]             // 5919 ldr r1, [r3, r4]
ldr r2, [r3, r4]             // 591a ldr r2, [r3, r4]
ldr r3, [r3, r4]             // 591b ldr r3, [r3, r4]
ldr r4, [r3, r4]             // 591c ldr r4, [r3, r4]
ldr r5, [r3, r4]             // 591d ldr r5, [r3, r4]
ldr r6, [r3, r4]             // 591e ldr r6, [r3, r4]
ldr r7, [r3, r4]             // 591f ldr r7, [r3, r4]
ldr r0, [r4, r4]             // 5920 ldr r0, [r4, r4]
ldr r1, [r4, r4]             // 5921 ldr r1, [r4, r4]
ldr r2, [r4, r4]             // 5922 ldr r2, [r4, r4]
ldr r3, [r4, r4]             // 5923 ldr r3, [r4, r4]
ldr r4, [r4, r4]             // 5924 ldr r4, [r4, r4]
ldr r5, [r4, r4]             // 5925 ldr r5, [r4, r4]
ldr r6, [r4, r4]             // 5926 ldr r6, [r4, r4]
ldr r7, [r4, r4]             // 5927 ldr r7, [r4, r4]
ldr r0, [r5, r4]             // 5928 ldr r0, [r5, r4]
ldr r1, [r5, r4]             // 5929 ldr r1, [r5, r4]
ldr r2, [r5, r4]             // 592a ldr r2, [r5, r4]
ldr r3, [r5, r4]             // 592b ldr r3, [r5, r4]
ldr r4, [r5, r4]             // 592c ldr r4, [r5, r4]
ldr r5, [r5, r4]             // 592d ldr r5, [r5, r4]
ldr r6, [r5, r4]             // 592e ldr r6, [r5, r4]
ldr r7, [r5, r4]             // 592f ldr r7, [r5, r4]
ldr r0, [r6, r4]             // 5930 ldr r0, [r6, r4]
ldr r1, [r6, r4]             // 5931 ldr r1, [r6, r4]
ldr r2, [r6, r4]             // 5932 ldr r2, [r6, r4]
ldr r3, [r6, r4]             // 5933 ldr r3, [r6, r4]
ldr r4, [r6, r4]             // 5934 ldr r4, [r6, r4]
ldr r5, [r6, r4]             // 5935 ldr r5, [r6, r4]
ldr r6, [r6, r4]             // 5936 ldr r6, [r6, r4]
ldr r7, [r6, r4]             // 5937 ldr r7, [r6, r4]
ldr r0, [r7, r4]             // 5938 ldr r0, [r7, r4]
ldr r1, [r7, r4]             // 5939 ldr r1, [r7, r4]
ldr r2, [r7, r4]             // 593a ldr r2, [r7, r4]
ldr r3, [r7, r4]             // 593b ldr r3, [r7, r4]
ldr r4, [r7, r4]             // 593c ldr r4, [r7, r4]
ldr r5, [r7, r4]             // 593d ldr r5, [r7, r4]
ldr r6, [r7, r4]             // 593e ldr r6, [r7, r4]
ldr r7, [r7, r4]             // 593f ldr r7, [r7, r4]
ldr r0, [r0, r5]             // 5940 ldr r0, [r0, r5]
ldr r1, [r0, r5]             // 5941 ldr r1, [r0, r5]
ldr r2, [r0, r5]             // 5942 ldr r2, [r0, r5]
ldr r3, [r0, r5]             // 5943 ldr r3, [r0, r5]
ldr r4, [r0, r5]             // 5944 ldr r4, [r0, r5]
ldr r5, [r0, r5]             // 5945 ldr r5, [r0, r5]
ldr r6, [r0, r5]             // 5946 ldr r6, [r0, r5]
ldr r7, [r0, r5]             // 5947 ldr r7, [r0, r5]
ldr r0, [r1, r5]             // 5948 ldr r0, [r1, r5]
ldr r1, [r1, r5]             // 5949 ldr r1, [r1, r5]
ldr r2, [r1, r5]             // 594a ldr r2, [r1, r5]
ldr r3, [r1, r5]             // 594b ldr r3, [r1, r5]
ldr r4, [r1, r5]             // 594c ldr r4, [r1, r5]
ldr r5, [r1, r5]             // 594d ldr r5, [r1, r5]
ldr r6, [r1, r5]             // 594e ldr r6, [r1, r5]
ldr r7, [r1, r5]             // 594f ldr r7, [r1, r5]
ldr r0, [r2, r5]             // 5950 ldr r0, [r2, r5]
ldr r1, [r2, r5]             // 5951 ldr r1, [r2, r5]
ldr r2, [r2, r5]             // 5952 ldr r2, [r2, r5]
ldr r3, [r2, r5]             // 5953 ldr r3, [r2, r5]
ldr r4, [r2, r5]             // 5954 ldr r4, [r2, r5]
ldr r5, [r2, r5]             // 5955 ldr r5, [r2, r5]
ldr r6, [r2, r5]             // 5956 ldr r6, [r2, r5]
ldr r7, [r2, r5]             // 5957 ldr r7, [r2, r5]
ldr r0, [r3, r5]             // 5958 ldr r0, [r3, r5]
ldr r1, [r3, r5]             // 5959 ldr r1, [r3, r5]
ldr r2, [r3, r5]             // 595a ldr r2, [r3, r5]
ldr r3, [r3, r5]             // 595b ldr r3, [r3, r5]
ldr r4, [r3, r5]             // 595c ldr r4, [r3, r5]
ldr r5, [r3, r5]             // 595d ldr r5, [r3, r5]
ldr r6, [r3, r5]             // 595e ldr r6, [r3, r5]
ldr r7, [r3, r5]             // 595f ldr r7, [r3, r5]
ldr r0, [r4, r5]             // 5960 ldr r0, [r4, r5]
ldr r1, [r4, r5]             // 5961 ldr r1, [r4, r5]
ldr r2, [r4, r5]             // 5962 ldr r2, [r4, r5]
ldr r3, [r4, r5]             // 5963 ldr r3, [r4, r5]
ldr r4, [r4, r5]             // 5964 ldr r4, [r4, r5]
ldr r5, [r4, r5]             // 5965 ldr r5, [r4, r5]
ldr r6, [r4, r5]             // 5966 ldr r6, [r4, r5]
ldr r7, [r4, r5]             // 5967 ldr r7, [r4, r5]
ldr r0, [r5, r5]             // 5968 ldr r0, [r5, r5]
ldr r1, [r5, r5]             // 5969 ldr r1, [r5, r5]
ldr r2, [r5, r5]             // 596a ldr r2, [r5, r5]
ldr r3, [r5, r5]             // 596b ldr r3, [r5, r5]
ldr r4, [r5, r5]             // 596c ldr r4, [r5, r5]
ldr r5, [r5, r5]             // 596d ldr r5, [r5, r5]
ldr r6, [r5, r5]             // 596e ldr r6, [r5, r5]
ldr r7, [r5, r5]             // 596f ldr r7, [r5, r5]
ldr r0, [r6, r5]             // 5970 ldr r0, [r6, r5]
ldr r1, [r6, r5]             // 5971 ldr r1, [r6, r5]
ldr r2, [r6, r5]             // 5972 ldr r2, [r6, r5]
ldr r3, [r6, r5]             // 5973 ldr r3, [r6, r5]
ldr r4, [r6, r5]             // 5974 ldr r4, [r6, r5]
ldr r5, [r6, r5]             // 5975 ldr r5, [r6, r5]
ldr r6, [r6, r5]             // 5976 ldr r6, [r6, r5]
ldr r7, [r6, r5]             // 5977 ldr r7, [r6, r5]
ldr r0, [r7, r5]             // 5978 ldr r0, [r7, r5]
ldr r1, [r7, r5]             // 5979 ldr r1, [r7, r5]
ldr r2, [r7, r5]             // 597a ldr r2, [r7, r5]
ldr r3, [r7, r5]             // 597b ldr r3, [r7, r5]
ldr r4, [r7, r5]             // 597c ldr r4, [r7, r5]
ldr r5, [r7, r5]             // 597d ldr r5, [r7, r5]
ldr r6, [r7, r5]             // 597e ldr r6, [r7, r5]
ldr r7, [r7, r5]             // 597f ldr r7, [r7, r5]
ldr r0, [r0, r6]             // 5980 ldr r0, [r0, r6]
ldr r1, [r0, r6]             // 5981 ldr r1, [r0, r6]
ldr r2, [r0, r6]             // 5982 ldr r2, [r0, r6]
ldr r3, [r0, r6]             // 5983 ldr r3, [r0, r6]
ldr r4, [r0, r6]             // 5984 ldr r4, [r0, r6]
ldr r5, [r0, r6]             // 5985 ldr r5, [r0, r6]
ldr r6, [r0, r6]             // 5986 ldr r6, [r0, r6]
ldr r7, [r0, r6]             // 5987 ldr r7, [r0, r6]
ldr r0, [r1, r6]             // 5988 ldr r0, [r1, r6]
ldr r1, [r1, r6]             // 5989 ldr r1, [r1, r6]
ldr r2, [r1, r6]             // 598a ldr r2, [r1, r6]
ldr r3, [r1, r6]             // 598b ldr r3, [r1, r6]
ldr r4, [r1, r6]             // 598c ldr r4, [r1, r6]
ldr r5, [r1, r6]             // 598d ldr r5, [r1, r6]
ldr r6, [r1, r6]             // 598e ldr r6, [r1, r6]
ldr r7, [r1, r6]             // 598f ldr r7, [r1, r6]
ldr r0, [r2, r6]             // 5990 ldr r0, [r2, r6]
ldr r1, [r2, r6]             // 5991 ldr r1, [r2, r6]
ldr r2, [r2, r6]             // 5992 ldr r2, [r2, r6]
ldr r3, [r2, r6]             // 5993 ldr r3, [r2, r6]
ldr r4, [r2, r6]             // 5994 ldr r4, [r2, r6]
ldr r5, [r2, r6]             // 5995 ldr r5, [r2, r6]
ldr r6, [r2, r6]             // 5996 ldr r6, [r2, r6]
ldr r7, [r2, r6]             // 5997 ldr r7, [r2, r6]
ldr r0, [r3, r6]             // 5998 ldr r0, [r3, r6]
ldr r1, [r3, r6]             // 5999 ldr r1, [r3, r6]
ldr r2, [r3, r6]             // 599a ldr r2, [r3, r6]
ldr r3, [r3, r6]             // 599b ldr r3, [r3, r6]
ldr r4, [r3, r6]             // 599c ldr r4, [r3, r6]
ldr r5, [r3, r6]             // 599d ldr r5, [r3, r6]
ldr r6, [r3, r6]             // 599e ldr r6, [r3, r6]
ldr r7, [r3, r6]             // 599f ldr r7, [r3, r6]
ldr r0, [r4, r6]             // 59a0 ldr r0, [r4, r6]
ldr r1, [r4, r6]             // 59a1 ldr r1, [r4, r6]
ldr r2, [r4, r6]             // 59a2 ldr r2, [r4, r6]
ldr r3, [r4, r6]             // 59a3 ldr r3, [r4, r6]
ldr r4, [r4, r6]             // 59a4 ldr r4, [r4, r6]
ldr r5, [r4, r6]             // 59a5 ldr r5, [r4, r6]
ldr r6, [r4, r6]             // 59a6 ldr r6, [r4, r6]
ldr r7, [r4, r6]             // 59a7 ldr r7, [r4, r6]
ldr r0, [r5, r6]             // 59a8 ldr r0, [r5, r6]
ldr r1, [r5, r6]             // 59a9 ldr r1, [r5, r6]
ldr r2, [r5, r6]             // 59aa ldr r2, [r5, r6]
ldr r3, [r5, r6]             // 59ab ldr r3, [r5, r6]
ldr r4, [r5, r6]             // 59ac ldr r4, [r5, r6]
ldr r5, [r5, r6]             // 59ad ldr r5, [r5, r6]
ldr r6, [r5, r6]             // 59ae ldr r6, [r5, r6]
ldr r7, [r5, r6]             // 59af ldr r7, [r5, r6]
ldr r0, [r6, r6]             // 59b0 ldr r0, [r6, r6]
ldr r1, [r6, r6]             // 59b1 ldr r1, [r6, r6]
ldr r2, [r6, r6]             // 59b2 ldr r2, [r6, r6]
ldr r3, [r6, r6]             // 59b3 ldr r3, [r6, r6]
ldr r4, [r6, r6]             // 59b4 ldr r4, [r6, r6]
ldr r5, [r6, r6]             // 59b5 ldr r5, [r6, r6]
ldr r6, [r6, r6]             // 59b6 ldr r6, [r6, r6]
ldr r7, [r6, r6]             // 59b7 ldr r7, [r6, r6]
ldr r0, [r7, r6]             // 59b8 ldr r0, [r7, r6]
ldr r1, [r7, r6]             // 59b9 ldr r1, [r7, r6]
ldr r2, [r7, r6]             // 59ba ldr r2, [r7, r6]
ldr r3, [r7, r6]             // 59bb ldr r3, [r7, r6]
ldr r4, [r7, r6]             // 59bc ldr r4, [r7, r6]
ldr r5, [r7, r6]             // 59bd ldr r5, [r7, r6]
ldr r6, [r7, r6]             // 59be ldr r6, [r7, r6]
ldr r7, [r7, r6]             // 59bf ldr r7, [r7, r6]
ldr r0, [r0, r7]             // 59c0 ldr r0, [r0, r7]
ldr r1, [r0, r7]             // 59c1 ldr r1, [r0, r7]
ldr r2, [r0, r7]             // 59c2 ldr r2, [r0, r7]
ldr r3, [r0, r7]             // 59c3 ldr r3, [r0, r7]
ldr r4, [r0, r7]             // 59c4 ldr r4, [r0, r7]
ldr r5, [r0, r7]             // 59c5 ldr r5, [r0, r7]
ldr r6, [r0, r7]             // 59c6 ldr r6, [r0, r7]
ldr r7, [r0, r7]             // 59c7 ldr r7, [r0, r7]
ldr r0, [r1, r7]             // 59c8 ldr r0, [r1, r7]
ldr r1, [r1, r7]             // 59c9 ldr r1, [r1, r7]
ldr r2, [r1, r7]             // 59ca ldr r2, [r1, r7]
ldr r3, [r1, r7]             // 59cb ldr r3, [r1, r7]
ldr r4, [r1, r7]             // 59cc ldr r4, [r1, r7]
ldr r5, [r1, r7]             // 59cd ldr r5, [r1, r7]
ldr r6, [r1, r7]             // 59ce ldr r6, [r1, r7]
ldr r7, [r1, r7]             // 59cf ldr r7, [r1, r7]
ldr r0, [r2, r7]             // 59d0 ldr r0, [r2, r7]
ldr r1, [r2, r7]             // 59d1 ldr r1, [r2, r7]
ldr r2, [r2, r7]             // 59d2 ldr r2, [r2, r7]
ldr r3, [r2, r7]             // 59d3 ldr r3, [r2, r7]
ldr r4, [r2, r7]             // 59d4 ldr r4, [r2, r7]
ldr r5, [r2, r7]             // 59d5 ldr r5, [r2, r7]
ldr r6, [r2, r7]             // 59d6 ldr r6, [r2, r7]
ldr r7, [r2, r7]             // 59d7 ldr r7, [r2, r7]
ldr r0, [r3, r7]             // 59d8 ldr r0, [r3, r7]
ldr r1, [r3, r7]             // 59d9 ldr r1, [r3, r7]
ldr r2, [r3, r7]             // 59da ldr r2, [r3, r7]
ldr r3, [r3, r7]             // 59db ldr r3, [r3, r7]
ldr r4, [r3, r7]             // 59dc ldr r4, [r3, r7]
ldr r5, [r3, r7]             // 59dd ldr r5, [r3, r7]
ldr r6, [r3, r7]             // 59de ldr r6, [r3, r7]
ldr r7, [r3, r7]             // 59df ldr r7, [r3, r7]
ldr r0, [r4, r7]             // 59e0 ldr r0, [r4, r7]
ldr r1, [r4, r7]             // 59e1 ldr r1, [r4, r7]
ldr r2, [r4, r7]             // 59e2 ldr r2, [r4, r7]
ldr r3, [r4, r7]             // 59e3 ldr r3, [r4, r7]
ldr r4, [r4, r7]             // 59e4 ldr r4, [r4, r7]
ldr r5, [r4, r7]             // 59e5 ldr r5, [r4, r7]
ldr r6, [r4, r7]             // 59e6 ldr r6, [r4, r7]
ldr r7, [r4, r7]             // 59e7 ldr r7, [r4, r7]
ldr r0, [r5, r7]             // 59e8 ldr r0, [r5, r7]
ldr r1, [r5, r7]             // 59e9 ldr r1, [r5, r7]
ldr r2, [r5, r7]             // 59ea ldr r2, [r5, r7]
ldr r3, [r5, r7]             // 59eb ldr r3, [r5, r7]
ldr r4, [r5, r7]             // 59ec ldr r4, [r5, r7]
ldr r5, [r5, r7]             // 59ed ldr r5, [r5, r7]
ldr r6, [r5, r7]             // 59ee ldr r6, [r5, r7]
ldr r7, [r5, r7]             // 59ef ldr r7, [r5, r7]
ldr r0, [r6, r7]             // 59f0 ldr r0, [r6, r7]
ldr r1, [r6, r7]             // 59f1 ldr r1, [r6, r7]
ldr r2, [r6, r7]             // 59f2 ldr r2, [r6, r7]
ldr r3, [r6, r7]             // 59f3 ldr r3, [r6, r7]
ldr r4, [r6, r7]             // 59f4 ldr r4, [r6, r7]
ldr r5, [r6, r7]             // 59f5 ldr r5, [r6, r7]
ldr r6, [r6, r7]             // 59f6 ldr r6, [r6, r7]
ldr r7, [r6, r7]             // 59f7 ldr r7, [r6, r7]
ldr r0, [r7, r7]             // 59f8 ldr r0, [r7, r7]
ldr r1, [r7, r7]             // 59f9 ldr r1, [r7, r7]
ldr r2, [r7, r7]             // 59fa ldr r2, [r7, r7]
ldr r3, [r7, r7]             // 59fb ldr r3, [r7, r7]
ldr r4, [r7, r7]             // 59fc ldr r4, [r7, r7]
ldr r5, [r7, r7]             // 59fd ldr r5, [r7, r7]
ldr r6, [r7, r7]             // 59fe ldr r6, [r7, r7]
ldr r7, [r7, r7]             // 59ff ldr r7, [r7, r7]

ldrh r0, [r0, r0]            // 5a00 ldrh r0, [r0, r0]
ldrh r1, [r0, r0]            // 5a01 ldrh r1, [r0, r0]
ldrh r2, [r0, r0]            // 5a02 ldrh r2, [r0, r0]
ldrh r3, [r0, r0]            // 5a03 ldrh r3, [r0, r0]
ldrh r4, [r0, r0]            // 5a04 ldrh r4, [r0, r0]
ldrh r5, [r0, r0]            // 5a05 ldrh r5, [r0, r0]
ldrh r6, [r0, r0]            // 5a06 ldrh r6, [r0, r0]
ldrh r7, [r0, r0]            // 5a07 ldrh r7, [r0, r0]
ldrh r0, [r1, r0]            // 5a08 ldrh r0, [r1, r0]
ldrh r1, [r1, r0]            // 5a09 ldrh r1, [r1, r0]
ldrh r2, [r1, r0]            // 5a0a ldrh r2, [r1, r0]
ldrh r3, [r1, r0]            // 5a0b ldrh r3, [r1, r0]
ldrh r4, [r1, r0]            // 5a0c ldrh r4, [r1, r0]
ldrh r5, [r1, r0]            // 5a0d ldrh r5, [r1, r0]
ldrh r6, [r1, r0]            // 5a0e ldrh r6, [r1, r0]
ldrh r7, [r1, r0]            // 5a0f ldrh r7, [r1, r0]
ldrh r0, [r2, r0]            // 5a10 ldrh r0, [r2, r0]
ldrh r1, [r2, r0]            // 5a11 ldrh r1, [r2, r0]
ldrh r2, [r2, r0]            // 5a12 ldrh r2, [r2, r0]
ldrh r3, [r2, r0]            // 5a13 ldrh r3, [r2, r0]
ldrh r4, [r2, r0]            // 5a14 ldrh r4, [r2, r0]
ldrh r5, [r2, r0]            // 5a15 ldrh r5, [r2, r0]
ldrh r6, [r2, r0]            // 5a16 ldrh r6, [r2, r0]
ldrh r7, [r2, r0]            // 5a17 ldrh r7, [r2, r0]
ldrh r0, [r3, r0]            // 5a18 ldrh r0, [r3, r0]
ldrh r1, [r3, r0]            // 5a19 ldrh r1, [r3, r0]
ldrh r2, [r3, r0]            // 5a1a ldrh r2, [r3, r0]
ldrh r3, [r3, r0]            // 5a1b ldrh r3, [r3, r0]
ldrh r4, [r3, r0]            // 5a1c ldrh r4, [r3, r0]
ldrh r5, [r3, r0]            // 5a1d ldrh r5, [r3, r0]
ldrh r6, [r3, r0]            // 5a1e ldrh r6, [r3, r0]
ldrh r7, [r3, r0]            // 5a1f ldrh r7, [r3, r0]
ldrh r0, [r4, r0]            // 5a20 ldrh r0, [r4, r0]
ldrh r1, [r4, r0]            // 5a21 ldrh r1, [r4, r0]
ldrh r2, [r4, r0]            // 5a22 ldrh r2, [r4, r0]
ldrh r3, [r4, r0]            // 5a23 ldrh r3, [r4, r0]
ldrh r4, [r4, r0]            // 5a24 ldrh r4, [r4, r0]
ldrh r5, [r4, r0]            // 5a25 ldrh r5, [r4, r0]
ldrh r6, [r4, r0]            // 5a26 ldrh r6, [r4, r0]
ldrh r7, [r4, r0]            // 5a27 ldrh r7, [r4, r0]
ldrh r0, [r5, r0]            // 5a28 ldrh r0, [r5, r0]
ldrh r1, [r5, r0]            // 5a29 ldrh r1, [r5, r0]
ldrh r2, [r5, r0]            // 5a2a ldrh r2, [r5, r0]
ldrh r3, [r5, r0]            // 5a2b ldrh r3, [r5, r0]
ldrh r4, [r5, r0]            // 5a2c ldrh r4, [r5, r0]
ldrh r5, [r5, r0]            // 5a2d ldrh r5, [r5, r0]
ldrh r6, [r5, r0]            // 5a2e ldrh r6, [r5, r0]
ldrh r7, [r5, r0]            // 5a2f ldrh r7, [r5, r0]
ldrh r0, [r6, r0]            // 5a30 ldrh r0, [r6, r0]
ldrh r1, [r6, r0]            // 5a31 ldrh r1, [r6, r0]
ldrh r2, [r6, r0]            // 5a32 ldrh r2, [r6, r0]
ldrh r3, [r6, r0]            // 5a33 ldrh r3, [r6, r0]
ldrh r4, [r6, r0]            // 5a34 ldrh r4, [r6, r0]
ldrh r5, [r6, r0]            // 5a35 ldrh r5, [r6, r0]
ldrh r6, [r6, r0]            // 5a36 ldrh r6, [r6, r0]
ldrh r7, [r6, r0]            // 5a37 ldrh r7, [r6, r0]
ldrh r0, [r7, r0]            // 5a38 ldrh r0, [r7, r0]
ldrh r1, [r7, r0]            // 5a39 ldrh r1, [r7, r0]
ldrh r2, [r7, r0]            // 5a3a ldrh r2, [r7, r0]
ldrh r3, [r7, r0]            // 5a3b ldrh r3, [r7, r0]
ldrh r4, [r7, r0]            // 5a3c ldrh r4, [r7, r0]
ldrh r5, [r7, r0]            // 5a3d ldrh r5, [r7, r0]
ldrh r6, [r7, r0]            // 5a3e ldrh r6, [r7, r0]
ldrh r7, [r7, r0]            // 5a3f ldrh r7, [r7, r0]
ldrh r0, [r0, r1]            // 5a40 ldrh r0, [r0, r1]
ldrh r1, [r0, r1]            // 5a41 ldrh r1, [r0, r1]
ldrh r2, [r0, r1]            // 5a42 ldrh r2, [r0, r1]
ldrh r3, [r0, r1]            // 5a43 ldrh r3, [r0, r1]
ldrh r4, [r0, r1]            // 5a44 ldrh r4, [r0, r1]
ldrh r5, [r0, r1]            // 5a45 ldrh r5, [r0, r1]
ldrh r6, [r0, r1]            // 5a46 ldrh r6, [r0, r1]
ldrh r7, [r0, r1]            // 5a47 ldrh r7, [r0, r1]
ldrh r0, [r1, r1]            // 5a48 ldrh r0, [r1, r1]
ldrh r1, [r1, r1]            // 5a49 ldrh r1, [r1, r1]
ldrh r2, [r1, r1]            // 5a4a ldrh r2, [r1, r1]
ldrh r3, [r1, r1]            // 5a4b ldrh r3, [r1, r1]
ldrh r4, [r1, r1]            // 5a4c ldrh r4, [r1, r1]
ldrh r5, [r1, r1]            // 5a4d ldrh r5, [r1, r1]
ldrh r6, [r1, r1]            // 5a4e ldrh r6, [r1, r1]
ldrh r7, [r1, r1]            // 5a4f ldrh r7, [r1, r1]
ldrh r0, [r2, r1]            // 5a50 ldrh r0, [r2, r1]
ldrh r1, [r2, r1]            // 5a51 ldrh r1, [r2, r1]
ldrh r2, [r2, r1]            // 5a52 ldrh r2, [r2, r1]
ldrh r3, [r2, r1]            // 5a53 ldrh r3, [r2, r1]
ldrh r4, [r2, r1]            // 5a54 ldrh r4, [r2, r1]
ldrh r5, [r2, r1]            // 5a55 ldrh r5, [r2, r1]
ldrh r6, [r2, r1]            // 5a56 ldrh r6, [r2, r1]
ldrh r7, [r2, r1]            // 5a57 ldrh r7, [r2, r1]
ldrh r0, [r3, r1]            // 5a58 ldrh r0, [r3, r1]
ldrh r1, [r3, r1]            // 5a59 ldrh r1, [r3, r1]
ldrh r2, [r3, r1]            // 5a5a ldrh r2, [r3, r1]
ldrh r3, [r3, r1]            // 5a5b ldrh r3, [r3, r1]
ldrh r4, [r3, r1]            // 5a5c ldrh r4, [r3, r1]
ldrh r5, [r3, r1]            // 5a5d ldrh r5, [r3, r1]
ldrh r6, [r3, r1]            // 5a5e ldrh r6, [r3, r1]
ldrh r7, [r3, r1]            // 5a5f ldrh r7, [r3, r1]
ldrh r0, [r4, r1]            // 5a60 ldrh r0, [r4, r1]
ldrh r1, [r4, r1]            // 5a61 ldrh r1, [r4, r1]
ldrh r2, [r4, r1]            // 5a62 ldrh r2, [r4, r1]
ldrh r3, [r4, r1]            // 5a63 ldrh r3, [r4, r1]
ldrh r4, [r4, r1]            // 5a64 ldrh r4, [r4, r1]
ldrh r5, [r4, r1]            // 5a65 ldrh r5, [r4, r1]
ldrh r6, [r4, r1]            // 5a66 ldrh r6, [r4, r1]
ldrh r7, [r4, r1]            // 5a67 ldrh r7, [r4, r1]
ldrh r0, [r5, r1]            // 5a68 ldrh r0, [r5, r1]
ldrh r1, [r5, r1]            // 5a69 ldrh r1, [r5, r1]
ldrh r2, [r5, r1]            // 5a6a ldrh r2, [r5, r1]
ldrh r3, [r5, r1]            // 5a6b ldrh r3, [r5, r1]
ldrh r4, [r5, r1]            // 5a6c ldrh r4, [r5, r1]
ldrh r5, [r5, r1]            // 5a6d ldrh r5, [r5, r1]
ldrh r6, [r5, r1]            // 5a6e ldrh r6, [r5, r1]
ldrh r7, [r5, r1]            // 5a6f ldrh r7, [r5, r1]
ldrh r0, [r6, r1]            // 5a70 ldrh r0, [r6, r1]
ldrh r1, [r6, r1]            // 5a71 ldrh r1, [r6, r1]
ldrh r2, [r6, r1]            // 5a72 ldrh r2, [r6, r1]
ldrh r3, [r6, r1]            // 5a73 ldrh r3, [r6, r1]
ldrh r4, [r6, r1]            // 5a74 ldrh r4, [r6, r1]
ldrh r5, [r6, r1]            // 5a75 ldrh r5, [r6, r1]
ldrh r6, [r6, r1]            // 5a76 ldrh r6, [r6, r1]
ldrh r7, [r6, r1]            // 5a77 ldrh r7, [r6, r1]
ldrh r0, [r7, r1]            // 5a78 ldrh r0, [r7, r1]
ldrh r1, [r7, r1]            // 5a79 ldrh r1, [r7, r1]
ldrh r2, [r7, r1]            // 5a7a ldrh r2, [r7, r1]
ldrh r3, [r7, r1]            // 5a7b ldrh r3, [r7, r1]
ldrh r4, [r7, r1]            // 5a7c ldrh r4, [r7, r1]
ldrh r5, [r7, r1]            // 5a7d ldrh r5, [r7, r1]
ldrh r6, [r7, r1]            // 5a7e ldrh r6, [r7, r1]
ldrh r7, [r7, r1]            // 5a7f ldrh r7, [r7, r1]
ldrh r0, [r0, r2]            // 5a80 ldrh r0, [r0, r2]
ldrh r1, [r0, r2]            // 5a81 ldrh r1, [r0, r2]
ldrh r2, [r0, r2]            // 5a82 ldrh r2, [r0, r2]
ldrh r3, [r0, r2]            // 5a83 ldrh r3, [r0, r2]
ldrh r4, [r0, r2]            // 5a84 ldrh r4, [r0, r2]
ldrh r5, [r0, r2]            // 5a85 ldrh r5, [r0, r2]
ldrh r6, [r0, r2]            // 5a86 ldrh r6, [r0, r2]
ldrh r7, [r0, r2]            // 5a87 ldrh r7, [r0, r2]
ldrh r0, [r1, r2]            // 5a88 ldrh r0, [r1, r2]
ldrh r1, [r1, r2]            // 5a89 ldrh r1, [r1, r2]
ldrh r2, [r1, r2]            // 5a8a ldrh r2, [r1, r2]
ldrh r3, [r1, r2]            // 5a8b ldrh r3, [r1, r2]
ldrh r4, [r1, r2]            // 5a8c ldrh r4, [r1, r2]
ldrh r5, [r1, r2]            // 5a8d ldrh r5, [r1, r2]
ldrh r6, [r1, r2]            // 5a8e ldrh r6, [r1, r2]
ldrh r7, [r1, r2]            // 5a8f ldrh r7, [r1, r2]
ldrh r0, [r2, r2]            // 5a90 ldrh r0, [r2, r2]
ldrh r1, [r2, r2]            // 5a91 ldrh r1, [r2, r2]
ldrh r2, [r2, r2]            // 5a92 ldrh r2, [r2, r2]
ldrh r3, [r2, r2]            // 5a93 ldrh r3, [r2, r2]
ldrh r4, [r2, r2]            // 5a94 ldrh r4, [r2, r2]
ldrh r5, [r2, r2]            // 5a95 ldrh r5, [r2, r2]
ldrh r6, [r2, r2]            // 5a96 ldrh r6, [r2, r2]
ldrh r7, [r2, r2]            // 5a97 ldrh r7, [r2, r2]
ldrh r0, [r3, r2]            // 5a98 ldrh r0, [r3, r2]
ldrh r1, [r3, r2]            // 5a99 ldrh r1, [r3, r2]
ldrh r2, [r3, r2]            // 5a9a ldrh r2, [r3, r2]
ldrh r3, [r3, r2]            // 5a9b ldrh r3, [r3, r2]
ldrh r4, [r3, r2]            // 5a9c ldrh r4, [r3, r2]
ldrh r5, [r3, r2]            // 5a9d ldrh r5, [r3, r2]
ldrh r6, [r3, r2]            // 5a9e ldrh r6, [r3, r2]
ldrh r7, [r3, r2]            // 5a9f ldrh r7, [r3, r2]
ldrh r0, [r4, r2]            // 5aa0 ldrh r0, [r4, r2]
ldrh r1, [r4, r2]            // 5aa1 ldrh r1, [r4, r2]
ldrh r2, [r4, r2]            // 5aa2 ldrh r2, [r4, r2]
ldrh r3, [r4, r2]            // 5aa3 ldrh r3, [r4, r2]
ldrh r4, [r4, r2]            // 5aa4 ldrh r4, [r4, r2]
ldrh r5, [r4, r2]            // 5aa5 ldrh r5, [r4, r2]
ldrh r6, [r4, r2]            // 5aa6 ldrh r6, [r4, r2]
ldrh r7, [r4, r2]            // 5aa7 ldrh r7, [r4, r2]
ldrh r0, [r5, r2]            // 5aa8 ldrh r0, [r5, r2]
ldrh r1, [r5, r2]            // 5aa9 ldrh r1, [r5, r2]
ldrh r2, [r5, r2]            // 5aaa ldrh r2, [r5, r2]
ldrh r3, [r5, r2]            // 5aab ldrh r3, [r5, r2]
ldrh r4, [r5, r2]            // 5aac ldrh r4, [r5, r2]
ldrh r5, [r5, r2]            // 5aad ldrh r5, [r5, r2]
ldrh r6, [r5, r2]            // 5aae ldrh r6, [r5, r2]
ldrh r7, [r5, r2]            // 5aaf ldrh r7, [r5, r2]
ldrh r0, [r6, r2]            // 5ab0 ldrh r0, [r6, r2]
ldrh r1, [r6, r2]            // 5ab1 ldrh r1, [r6, r2]
ldrh r2, [r6, r2]            // 5ab2 ldrh r2, [r6, r2]
ldrh r3, [r6, r2]            // 5ab3 ldrh r3, [r6, r2]
ldrh r4, [r6, r2]            // 5ab4 ldrh r4, [r6, r2]
ldrh r5, [r6, r2]            // 5ab5 ldrh r5, [r6, r2]
ldrh r6, [r6, r2]            // 5ab6 ldrh r6, [r6, r2]
ldrh r7, [r6, r2]            // 5ab7 ldrh r7, [r6, r2]
ldrh r0, [r7, r2]            // 5ab8 ldrh r0, [r7, r2]
ldrh r1, [r7, r2]            // 5ab9 ldrh r1, [r7, r2]
ldrh r2, [r7, r2]            // 5aba ldrh r2, [r7, r2]
ldrh r3, [r7, r2]            // 5abb ldrh r3, [r7, r2]
ldrh r4, [r7, r2]            // 5abc ldrh r4, [r7, r2]
ldrh r5, [r7, r2]            // 5abd ldrh r5, [r7, r2]
ldrh r6, [r7, r2]            // 5abe ldrh r6, [r7, r2]
ldrh r7, [r7, r2]            // 5abf ldrh r7, [r7, r2]
ldrh r0, [r0, r3]            // 5ac0 ldrh r0, [r0, r3]
ldrh r1, [r0, r3]            // 5ac1 ldrh r1, [r0, r3]
ldrh r2, [r0, r3]            // 5ac2 ldrh r2, [r0, r3]
ldrh r3, [r0, r3]            // 5ac3 ldrh r3, [r0, r3]
ldrh r4, [r0, r3]            // 5ac4 ldrh r4, [r0, r3]
ldrh r5, [r0, r3]            // 5ac5 ldrh r5, [r0, r3]
ldrh r6, [r0, r3]            // 5ac6 ldrh r6, [r0, r3]
ldrh r7, [r0, r3]            // 5ac7 ldrh r7, [r0, r3]
ldrh r0, [r1, r3]            // 5ac8 ldrh r0, [r1, r3]
ldrh r1, [r1, r3]            // 5ac9 ldrh r1, [r1, r3]
ldrh r2, [r1, r3]            // 5aca ldrh r2, [r1, r3]
ldrh r3, [r1, r3]            // 5acb ldrh r3, [r1, r3]
ldrh r4, [r1, r3]            // 5acc ldrh r4, [r1, r3]
ldrh r5, [r1, r3]            // 5acd ldrh r5, [r1, r3]
ldrh r6, [r1, r3]            // 5ace ldrh r6, [r1, r3]
ldrh r7, [r1, r3]            // 5acf ldrh r7, [r1, r3]
ldrh r0, [r2, r3]            // 5ad0 ldrh r0, [r2, r3]
ldrh r1, [r2, r3]            // 5ad1 ldrh r1, [r2, r3]
ldrh r2, [r2, r3]            // 5ad2 ldrh r2, [r2, r3]
ldrh r3, [r2, r3]            // 5ad3 ldrh r3, [r2, r3]
ldrh r4, [r2, r3]            // 5ad4 ldrh r4, [r2, r3]
ldrh r5, [r2, r3]            // 5ad5 ldrh r5, [r2, r3]
ldrh r6, [r2, r3]            // 5ad6 ldrh r6, [r2, r3]
ldrh r7, [r2, r3]            // 5ad7 ldrh r7, [r2, r3]
ldrh r0, [r3, r3]            // 5ad8 ldrh r0, [r3, r3]
ldrh r1, [r3, r3]            // 5ad9 ldrh r1, [r3, r3]
ldrh r2, [r3, r3]            // 5ada ldrh r2, [r3, r3]
ldrh r3, [r3, r3]            // 5adb ldrh r3, [r3, r3]
ldrh r4, [r3, r3]            // 5adc ldrh r4, [r3, r3]
ldrh r5, [r3, r3]            // 5add ldrh r5, [r3, r3]
ldrh r6, [r3, r3]            // 5ade ldrh r6, [r3, r3]
ldrh r7, [r3, r3]            // 5adf ldrh r7, [r3, r3]
ldrh r0, [r4, r3]            // 5ae0 ldrh r0, [r4, r3]
ldrh r1, [r4, r3]            // 5ae1 ldrh r1, [r4, r3]
ldrh r2, [r4, r3]            // 5ae2 ldrh r2, [r4, r3]
ldrh r3, [r4, r3]            // 5ae3 ldrh r3, [r4, r3]
ldrh r4, [r4, r3]            // 5ae4 ldrh r4, [r4, r3]
ldrh r5, [r4, r3]            // 5ae5 ldrh r5, [r4, r3]
ldrh r6, [r4, r3]            // 5ae6 ldrh r6, [r4, r3]
ldrh r7, [r4, r3]            // 5ae7 ldrh r7, [r4, r3]
ldrh r0, [r5, r3]            // 5ae8 ldrh r0, [r5, r3]
ldrh r1, [r5, r3]            // 5ae9 ldrh r1, [r5, r3]
ldrh r2, [r5, r3]            // 5aea ldrh r2, [r5, r3]
ldrh r3, [r5, r3]            // 5aeb ldrh r3, [r5, r3]
ldrh r4, [r5, r3]            // 5aec ldrh r4, [r5, r3]
ldrh r5, [r5, r3]            // 5aed ldrh r5, [r5, r3]
ldrh r6, [r5, r3]            // 5aee ldrh r6, [r5, r3]
ldrh r7, [r5, r3]            // 5aef ldrh r7, [r5, r3]
ldrh r0, [r6, r3]            // 5af0 ldrh r0, [r6, r3]
ldrh r1, [r6, r3]            // 5af1 ldrh r1, [r6, r3]
ldrh r2, [r6, r3]            // 5af2 ldrh r2, [r6, r3]
ldrh r3, [r6, r3]            // 5af3 ldrh r3, [r6, r3]
ldrh r4, [r6, r3]            // 5af4 ldrh r4, [r6, r3]
ldrh r5, [r6, r3]            // 5af5 ldrh r5, [r6, r3]
ldrh r6, [r6, r3]            // 5af6 ldrh r6, [r6, r3]
ldrh r7, [r6, r3]            // 5af7 ldrh r7, [r6, r3]
ldrh r0, [r7, r3]            // 5af8 ldrh r0, [r7, r3]
ldrh r1, [r7, r3]            // 5af9 ldrh r1, [r7, r3]
ldrh r2, [r7, r3]            // 5afa ldrh r2, [r7, r3]
ldrh r3, [r7, r3]            // 5afb ldrh r3, [r7, r3]
ldrh r4, [r7, r3]            // 5afc ldrh r4, [r7, r3]
ldrh r5, [r7, r3]            // 5afd ldrh r5, [r7, r3]
ldrh r6, [r7, r3]            // 5afe ldrh r6, [r7, r3]
ldrh r7, [r7, r3]            // 5aff ldrh r7, [r7, r3]
ldrh r0, [r0, r4]            // 5b00 ldrh r0, [r0, r4]
ldrh r1, [r0, r4]            // 5b01 ldrh r1, [r0, r4]
ldrh r2, [r0, r4]            // 5b02 ldrh r2, [r0, r4]
ldrh r3, [r0, r4]            // 5b03 ldrh r3, [r0, r4]
ldrh r4, [r0, r4]            // 5b04 ldrh r4, [r0, r4]
ldrh r5, [r0, r4]            // 5b05 ldrh r5, [r0, r4]
ldrh r6, [r0, r4]            // 5b06 ldrh r6, [r0, r4]
ldrh r7, [r0, r4]            // 5b07 ldrh r7, [r0, r4]
ldrh r0, [r1, r4]            // 5b08 ldrh r0, [r1, r4]
ldrh r1, [r1, r4]            // 5b09 ldrh r1, [r1, r4]
ldrh r2, [r1, r4]            // 5b0a ldrh r2, [r1, r4]
ldrh r3, [r1, r4]            // 5b0b ldrh r3, [r1, r4]
ldrh r4, [r1, r4]            // 5b0c ldrh r4, [r1, r4]
ldrh r5, [r1, r4]            // 5b0d ldrh r5, [r1, r4]
ldrh r6, [r1, r4]            // 5b0e ldrh r6, [r1, r4]
ldrh r7, [r1, r4]            // 5b0f ldrh r7, [r1, r4]
ldrh r0, [r2, r4]            // 5b10 ldrh r0, [r2, r4]
ldrh r1, [r2, r4]            // 5b11 ldrh r1, [r2, r4]
ldrh r2, [r2, r4]            // 5b12 ldrh r2, [r2, r4]
ldrh r3, [r2, r4]            // 5b13 ldrh r3, [r2, r4]
ldrh r4, [r2, r4]            // 5b14 ldrh r4, [r2, r4]
ldrh r5, [r2, r4]            // 5b15 ldrh r5, [r2, r4]
ldrh r6, [r2, r4]            // 5b16 ldrh r6, [r2, r4]
ldrh r7, [r2, r4]            // 5b17 ldrh r7, [r2, r4]
ldrh r0, [r3, r4]            // 5b18 ldrh r0, [r3, r4]
ldrh r1, [r3, r4]            // 5b19 ldrh r1, [r3, r4]
ldrh r2, [r3, r4]            // 5b1a ldrh r2, [r3, r4]
ldrh r3, [r3, r4]            // 5b1b ldrh r3, [r3, r4]
ldrh r4, [r3, r4]            // 5b1c ldrh r4, [r3, r4]
ldrh r5, [r3, r4]            // 5b1d ldrh r5, [r3, r4]
ldrh r6, [r3, r4]            // 5b1e ldrh r6, [r3, r4]
ldrh r7, [r3, r4]            // 5b1f ldrh r7, [r3, r4]
ldrh r0, [r4, r4]            // 5b20 ldrh r0, [r4, r4]
ldrh r1, [r4, r4]            // 5b21 ldrh r1, [r4, r4]
ldrh r2, [r4, r4]            // 5b22 ldrh r2, [r4, r4]
ldrh r3, [r4, r4]            // 5b23 ldrh r3, [r4, r4]
ldrh r4, [r4, r4]            // 5b24 ldrh r4, [r4, r4]
ldrh r5, [r4, r4]            // 5b25 ldrh r5, [r4, r4]
ldrh r6, [r4, r4]            // 5b26 ldrh r6, [r4, r4]
ldrh r7, [r4, r4]            // 5b27 ldrh r7, [r4, r4]
ldrh r0, [r5, r4]            // 5b28 ldrh r0, [r5, r4]
ldrh r1, [r5, r4]            // 5b29 ldrh r1, [r5, r4]
ldrh r2, [r5, r4]            // 5b2a ldrh r2, [r5, r4]
ldrh r3, [r5, r4]            // 5b2b ldrh r3, [r5, r4]
ldrh r4, [r5, r4]            // 5b2c ldrh r4, [r5, r4]
ldrh r5, [r5, r4]            // 5b2d ldrh r5, [r5, r4]
ldrh r6, [r5, r4]            // 5b2e ldrh r6, [r5, r4]
ldrh r7, [r5, r4]            // 5b2f ldrh r7, [r5, r4]
ldrh r0, [r6, r4]            // 5b30 ldrh r0, [r6, r4]
ldrh r1, [r6, r4]            // 5b31 ldrh r1, [r6, r4]
ldrh r2, [r6, r4]            // 5b32 ldrh r2, [r6, r4]
ldrh r3, [r6, r4]            // 5b33 ldrh r3, [r6, r4]
ldrh r4, [r6, r4]            // 5b34 ldrh r4, [r6, r4]
ldrh r5, [r6, r4]            // 5b35 ldrh r5, [r6, r4]
ldrh r6, [r6, r4]            // 5b36 ldrh r6, [r6, r4]
ldrh r7, [r6, r4]            // 5b37 ldrh r7, [r6, r4]
ldrh r0, [r7, r4]            // 5b38 ldrh r0, [r7, r4]
ldrh r1, [r7, r4]            // 5b39 ldrh r1, [r7, r4]
ldrh r2, [r7, r4]            // 5b3a ldrh r2, [r7, r4]
ldrh r3, [r7, r4]            // 5b3b ldrh r3, [r7, r4]
ldrh r4, [r7, r4]            // 5b3c ldrh r4, [r7, r4]
ldrh r5, [r7, r4]            // 5b3d ldrh r5, [r7, r4]
ldrh r6, [r7, r4]            // 5b3e ldrh r6, [r7, r4]
ldrh r7, [r7, r4]            // 5b3f ldrh r7, [r7, r4]
ldrh r0, [r0, r5]            // 5b40 ldrh r0, [r0, r5]
ldrh r1, [r0, r5]            // 5b41 ldrh r1, [r0, r5]
ldrh r2, [r0, r5]            // 5b42 ldrh r2, [r0, r5]
ldrh r3, [r0, r5]            // 5b43 ldrh r3, [r0, r5]
ldrh r4, [r0, r5]            // 5b44 ldrh r4, [r0, r5]
ldrh r5, [r0, r5]            // 5b45 ldrh r5, [r0, r5]
ldrh r6, [r0, r5]            // 5b46 ldrh r6, [r0, r5]
ldrh r7, [r0, r5]            // 5b47 ldrh r7, [r0, r5]
ldrh r0, [r1, r5]            // 5b48 ldrh r0, [r1, r5]
ldrh r1, [r1, r5]            // 5b49 ldrh r1, [r1, r5]
ldrh r2, [r1, r5]            // 5b4a ldrh r2, [r1, r5]
ldrh r3, [r1, r5]            // 5b4b ldrh r3, [r1, r5]
ldrh r4, [r1, r5]            // 5b4c ldrh r4, [r1, r5]
ldrh r5, [r1, r5]            // 5b4d ldrh r5, [r1, r5]
ldrh r6, [r1, r5]            // 5b4e ldrh r6, [r1, r5]
ldrh r7, [r1, r5]            // 5b4f ldrh r7, [r1, r5]
ldrh r0, [r2, r5]            // 5b50 ldrh r0, [r2, r5]
ldrh r1, [r2, r5]            // 5b51 ldrh r1, [r2, r5]
ldrh r2, [r2, r5]            // 5b52 ldrh r2, [r2, r5]
ldrh r3, [r2, r5]            // 5b53 ldrh r3, [r2, r5]
ldrh r4, [r2, r5]            // 5b54 ldrh r4, [r2, r5]
ldrh r5, [r2, r5]            // 5b55 ldrh r5, [r2, r5]
ldrh r6, [r2, r5]            // 5b56 ldrh r6, [r2, r5]
ldrh r7, [r2, r5]            // 5b57 ldrh r7, [r2, r5]
ldrh r0, [r3, r5]            // 5b58 ldrh r0, [r3, r5]
ldrh r1, [r3, r5]            // 5b59 ldrh r1, [r3, r5]
ldrh r2, [r3, r5]            // 5b5a ldrh r2, [r3, r5]
ldrh r3, [r3, r5]            // 5b5b ldrh r3, [r3, r5]
ldrh r4, [r3, r5]            // 5b5c ldrh r4, [r3, r5]
ldrh r5, [r3, r5]            // 5b5d ldrh r5, [r3, r5]
ldrh r6, [r3, r5]            // 5b5e ldrh r6, [r3, r5]
ldrh r7, [r3, r5]            // 5b5f ldrh r7, [r3, r5]
ldrh r0, [r4, r5]            // 5b60 ldrh r0, [r4, r5]
ldrh r1, [r4, r5]            // 5b61 ldrh r1, [r4, r5]
ldrh r2, [r4, r5]            // 5b62 ldrh r2, [r4, r5]
ldrh r3, [r4, r5]            // 5b63 ldrh r3, [r4, r5]
ldrh r4, [r4, r5]            // 5b64 ldrh r4, [r4, r5]
ldrh r5, [r4, r5]            // 5b65 ldrh r5, [r4, r5]
ldrh r6, [r4, r5]            // 5b66 ldrh r6, [r4, r5]
ldrh r7, [r4, r5]            // 5b67 ldrh r7, [r4, r5]
ldrh r0, [r5, r5]            // 5b68 ldrh r0, [r5, r5]
ldrh r1, [r5, r5]            // 5b69 ldrh r1, [r5, r5]
ldrh r2, [r5, r5]            // 5b6a ldrh r2, [r5, r5]
ldrh r3, [r5, r5]            // 5b6b ldrh r3, [r5, r5]
ldrh r4, [r5, r5]            // 5b6c ldrh r4, [r5, r5]
ldrh r5, [r5, r5]            // 5b6d ldrh r5, [r5, r5]
ldrh r6, [r5, r5]            // 5b6e ldrh r6, [r5, r5]
ldrh r7, [r5, r5]            // 5b6f ldrh r7, [r5, r5]
ldrh r0, [r6, r5]            // 5b70 ldrh r0, [r6, r5]
ldrh r1, [r6, r5]            // 5b71 ldrh r1, [r6, r5]
ldrh r2, [r6, r5]            // 5b72 ldrh r2, [r6, r5]
ldrh r3, [r6, r5]            // 5b73 ldrh r3, [r6, r5]
ldrh r4, [r6, r5]            // 5b74 ldrh r4, [r6, r5]
ldrh r5, [r6, r5]            // 5b75 ldrh r5, [r6, r5]
ldrh r6, [r6, r5]            // 5b76 ldrh r6, [r6, r5]
ldrh r7, [r6, r5]            // 5b77 ldrh r7, [r6, r5]
ldrh r0, [r7, r5]            // 5b78 ldrh r0, [r7, r5]
ldrh r1, [r7, r5]            // 5b79 ldrh r1, [r7, r5]
ldrh r2, [r7, r5]            // 5b7a ldrh r2, [r7, r5]
ldrh r3, [r7, r5]            // 5b7b ldrh r3, [r7, r5]
ldrh r4, [r7, r5]            // 5b7c ldrh r4, [r7, r5]
ldrh r5, [r7, r5]            // 5b7d ldrh r5, [r7, r5]
ldrh r6, [r7, r5]            // 5b7e ldrh r6, [r7, r5]
ldrh r7, [r7, r5]            // 5b7f ldrh r7, [r7, r5]
ldrh r0, [r0, r6]            // 5b80 ldrh r0, [r0, r6]
ldrh r1, [r0, r6]            // 5b81 ldrh r1, [r0, r6]
ldrh r2, [r0, r6]            // 5b82 ldrh r2, [r0, r6]
ldrh r3, [r0, r6]            // 5b83 ldrh r3, [r0, r6]
ldrh r4, [r0, r6]            // 5b84 ldrh r4, [r0, r6]
ldrh r5, [r0, r6]            // 5b85 ldrh r5, [r0, r6]
ldrh r6, [r0, r6]            // 5b86 ldrh r6, [r0, r6]
ldrh r7, [r0, r6]            // 5b87 ldrh r7, [r0, r6]
ldrh r0, [r1, r6]            // 5b88 ldrh r0, [r1, r6]
ldrh r1, [r1, r6]            // 5b89 ldrh r1, [r1, r6]
ldrh r2, [r1, r6]            // 5b8a ldrh r2, [r1, r6]
ldrh r3, [r1, r6]            // 5b8b ldrh r3, [r1, r6]
ldrh r4, [r1, r6]            // 5b8c ldrh r4, [r1, r6]
ldrh r5, [r1, r6]            // 5b8d ldrh r5, [r1, r6]
ldrh r6, [r1, r6]            // 5b8e ldrh r6, [r1, r6]
ldrh r7, [r1, r6]            // 5b8f ldrh r7, [r1, r6]
ldrh r0, [r2, r6]            // 5b90 ldrh r0, [r2, r6]
ldrh r1, [r2, r6]            // 5b91 ldrh r1, [r2, r6]
ldrh r2, [r2, r6]            // 5b92 ldrh r2, [r2, r6]
ldrh r3, [r2, r6]            // 5b93 ldrh r3, [r2, r6]
ldrh r4, [r2, r6]            // 5b94 ldrh r4, [r2, r6]
ldrh r5, [r2, r6]            // 5b95 ldrh r5, [r2, r6]
ldrh r6, [r2, r6]            // 5b96 ldrh r6, [r2, r6]
ldrh r7, [r2, r6]            // 5b97 ldrh r7, [r2, r6]
ldrh r0, [r3, r6]            // 5b98 ldrh r0, [r3, r6]
ldrh r1, [r3, r6]            // 5b99 ldrh r1, [r3, r6]
ldrh r2, [r3, r6]            // 5b9a ldrh r2, [r3, r6]
ldrh r3, [r3, r6]            // 5b9b ldrh r3, [r3, r6]
ldrh r4, [r3, r6]            // 5b9c ldrh r4, [r3, r6]
ldrh r5, [r3, r6]            // 5b9d ldrh r5, [r3, r6]
ldrh r6, [r3, r6]            // 5b9e ldrh r6, [r3, r6]
ldrh r7, [r3, r6]            // 5b9f ldrh r7, [r3, r6]
ldrh r0, [r4, r6]            // 5ba0 ldrh r0, [r4, r6]
ldrh r1, [r4, r6]            // 5ba1 ldrh r1, [r4, r6]
ldrh r2, [r4, r6]            // 5ba2 ldrh r2, [r4, r6]
ldrh r3, [r4, r6]            // 5ba3 ldrh r3, [r4, r6]
ldrh r4, [r4, r6]            // 5ba4 ldrh r4, [r4, r6]
ldrh r5, [r4, r6]            // 5ba5 ldrh r5, [r4, r6]
ldrh r6, [r4, r6]            // 5ba6 ldrh r6, [r4, r6]
ldrh r7, [r4, r6]            // 5ba7 ldrh r7, [r4, r6]
ldrh r0, [r5, r6]            // 5ba8 ldrh r0, [r5, r6]
ldrh r1, [r5, r6]            // 5ba9 ldrh r1, [r5, r6]
ldrh r2, [r5, r6]            // 5baa ldrh r2, [r5, r6]
ldrh r3, [r5, r6]            // 5bab ldrh r3, [r5, r6]
ldrh r4, [r5, r6]            // 5bac ldrh r4, [r5, r6]
ldrh r5, [r5, r6]            // 5bad ldrh r5, [r5, r6]
ldrh r6, [r5, r6]            // 5bae ldrh r6, [r5, r6]
ldrh r7, [r5, r6]            // 5baf ldrh r7, [r5, r6]
ldrh r0, [r6, r6]            // 5bb0 ldrh r0, [r6, r6]
ldrh r1, [r6, r6]            // 5bb1 ldrh r1, [r6, r6]
ldrh r2, [r6, r6]            // 5bb2 ldrh r2, [r6, r6]
ldrh r3, [r6, r6]            // 5bb3 ldrh r3, [r6, r6]
ldrh r4, [r6, r6]            // 5bb4 ldrh r4, [r6, r6]
ldrh r5, [r6, r6]            // 5bb5 ldrh r5, [r6, r6]
ldrh r6, [r6, r6]            // 5bb6 ldrh r6, [r6, r6]
ldrh r7, [r6, r6]            // 5bb7 ldrh r7, [r6, r6]
ldrh r0, [r7, r6]            // 5bb8 ldrh r0, [r7, r6]
ldrh r1, [r7, r6]            // 5bb9 ldrh r1, [r7, r6]
ldrh r2, [r7, r6]            // 5bba ldrh r2, [r7, r6]
ldrh r3, [r7, r6]            // 5bbb ldrh r3, [r7, r6]
ldrh r4, [r7, r6]            // 5bbc ldrh r4, [r7, r6]
ldrh r5, [r7, r6]            // 5bbd ldrh r5, [r7, r6]
ldrh r6, [r7, r6]            // 5bbe ldrh r6, [r7, r6]
ldrh r7, [r7, r6]            // 5bbf ldrh r7, [r7, r6]
ldrh r0, [r0, r7]            // 5bc0 ldrh r0, [r0, r7]
ldrh r1, [r0, r7]            // 5bc1 ldrh r1, [r0, r7]
ldrh r2, [r0, r7]            // 5bc2 ldrh r2, [r0, r7]
ldrh r3, [r0, r7]            // 5bc3 ldrh r3, [r0, r7]
ldrh r4, [r0, r7]            // 5bc4 ldrh r4, [r0, r7]
ldrh r5, [r0, r7]            // 5bc5 ldrh r5, [r0, r7]
ldrh r6, [r0, r7]            // 5bc6 ldrh r6, [r0, r7]
ldrh r7, [r0, r7]            // 5bc7 ldrh r7, [r0, r7]
ldrh r0, [r1, r7]            // 5bc8 ldrh r0, [r1, r7]
ldrh r1, [r1, r7]            // 5bc9 ldrh r1, [r1, r7]
ldrh r2, [r1, r7]            // 5bca ldrh r2, [r1, r7]
ldrh r3, [r1, r7]            // 5bcb ldrh r3, [r1, r7]
ldrh r4, [r1, r7]            // 5bcc ldrh r4, [r1, r7]
ldrh r5, [r1, r7]            // 5bcd ldrh r5, [r1, r7]
ldrh r6, [r1, r7]            // 5bce ldrh r6, [r1, r7]
ldrh r7, [r1, r7]            // 5bcf ldrh r7, [r1, r7]
ldrh r0, [r2, r7]            // 5bd0 ldrh r0, [r2, r7]
ldrh r1, [r2, r7]            // 5bd1 ldrh r1, [r2, r7]
ldrh r2, [r2, r7]            // 5bd2 ldrh r2, [r2, r7]
ldrh r3, [r2, r7]            // 5bd3 ldrh r3, [r2, r7]
ldrh r4, [r2, r7]            // 5bd4 ldrh r4, [r2, r7]
ldrh r5, [r2, r7]            // 5bd5 ldrh r5, [r2, r7]
ldrh r6, [r2, r7]            // 5bd6 ldrh r6, [r2, r7]
ldrh r7, [r2, r7]            // 5bd7 ldrh r7, [r2, r7]
ldrh r0, [r3, r7]            // 5bd8 ldrh r0, [r3, r7]
ldrh r1, [r3, r7]            // 5bd9 ldrh r1, [r3, r7]
ldrh r2, [r3, r7]            // 5bda ldrh r2, [r3, r7]
ldrh r3, [r3, r7]            // 5bdb ldrh r3, [r3, r7]
ldrh r4, [r3, r7]            // 5bdc ldrh r4, [r3, r7]
ldrh r5, [r3, r7]            // 5bdd ldrh r5, [r3, r7]
ldrh r6, [r3, r7]            // 5bde ldrh r6, [r3, r7]
ldrh r7, [r3, r7]            // 5bdf ldrh r7, [r3, r7]
ldrh r0, [r4, r7]            // 5be0 ldrh r0, [r4, r7]
ldrh r1, [r4, r7]            // 5be1 ldrh r1, [r4, r7]
ldrh r2, [r4, r7]            // 5be2 ldrh r2, [r4, r7]
ldrh r3, [r4, r7]            // 5be3 ldrh r3, [r4, r7]
ldrh r4, [r4, r7]            // 5be4 ldrh r4, [r4, r7]
ldrh r5, [r4, r7]            // 5be5 ldrh r5, [r4, r7]
ldrh r6, [r4, r7]            // 5be6 ldrh r6, [r4, r7]
ldrh r7, [r4, r7]            // 5be7 ldrh r7, [r4, r7]
ldrh r0, [r5, r7]            // 5be8 ldrh r0, [r5, r7]
ldrh r1, [r5, r7]            // 5be9 ldrh r1, [r5, r7]
ldrh r2, [r5, r7]            // 5bea ldrh r2, [r5, r7]
ldrh r3, [r5, r7]            // 5beb ldrh r3, [r5, r7]
ldrh r4, [r5, r7]            // 5bec ldrh r4, [r5, r7]
ldrh r5, [r5, r7]            // 5bed ldrh r5, [r5, r7]
ldrh r6, [r5, r7]            // 5bee ldrh r6, [r5, r7]
ldrh r7, [r5, r7]            // 5bef ldrh r7, [r5, r7]
ldrh r0, [r6, r7]            // 5bf0 ldrh r0, [r6, r7]
ldrh r1, [r6, r7]            // 5bf1 ldrh r1, [r6, r7]
ldrh r2, [r6, r7]            // 5bf2 ldrh r2, [r6, r7]
ldrh r3, [r6, r7]            // 5bf3 ldrh r3, [r6, r7]
ldrh r4, [r6, r7]            // 5bf4 ldrh r4, [r6, r7]
ldrh r5, [r6, r7]            // 5bf5 ldrh r5, [r6, r7]
ldrh r6, [r6, r7]            // 5bf6 ldrh r6, [r6, r7]
ldrh r7, [r6, r7]            // 5bf7 ldrh r7, [r6, r7]
ldrh r0, [r7, r7]            // 5bf8 ldrh r0, [r7, r7]
ldrh r1, [r7, r7]            // 5bf9 ldrh r1, [r7, r7]
ldrh r2, [r7, r7]            // 5bfa ldrh r2, [r7, r7]
ldrh r3, [r7, r7]            // 5bfb ldrh r3, [r7, r7]
ldrh r4, [r7, r7]            // 5bfc ldrh r4, [r7, r7]
ldrh r5, [r7, r7]            // 5bfd ldrh r5, [r7, r7]
ldrh r6, [r7, r7]            // 5bfe ldrh r6, [r7, r7]
ldrh r7, [r7, r7]            // 5bff ldrh r7, [r7, r7]

ldrb r0, [r0, r0]            // 5c00 ldrb r0, [r0, r0]
ldrb r1, [r0, r0]            // 5c01 ldrb r1, [r0, r0]
ldrb r2, [r0, r0]            // 5c02 ldrb r2, [r0, r0]
ldrb r3, [r0, r0]            // 5c03 ldrb r3, [r0, r0]
ldrb r4, [r0, r0]            // 5c04 ldrb r4, [r0, r0]
ldrb r5, [r0, r0]            // 5c05 ldrb r5, [r0, r0]
ldrb r6, [r0, r0]            // 5c06 ldrb r6, [r0, r0]
ldrb r7, [r0, r0]            // 5c07 ldrb r7, [r0, r0]
ldrb r0, [r1, r0]            // 5c08 ldrb r0, [r1, r0]
ldrb r1, [r1, r0]            // 5c09 ldrb r1, [r1, r0]
ldrb r2, [r1, r0]            // 5c0a ldrb r2, [r1, r0]
ldrb r3, [r1, r0]            // 5c0b ldrb r3, [r1, r0]
ldrb r4, [r1, r0]            // 5c0c ldrb r4, [r1, r0]
ldrb r5, [r1, r0]            // 5c0d ldrb r5, [r1, r0]
ldrb r6, [r1, r0]            // 5c0e ldrb r6, [r1, r0]
ldrb r7, [r1, r0]            // 5c0f ldrb r7, [r1, r0]
ldrb r0, [r2, r0]            // 5c10 ldrb r0, [r2, r0]
ldrb r1, [r2, r0]            // 5c11 ldrb r1, [r2, r0]
ldrb r2, [r2, r0]            // 5c12 ldrb r2, [r2, r0]
ldrb r3, [r2, r0]            // 5c13 ldrb r3, [r2, r0]
ldrb r4, [r2, r0]            // 5c14 ldrb r4, [r2, r0]
ldrb r5, [r2, r0]            // 5c15 ldrb r5, [r2, r0]
ldrb r6, [r2, r0]            // 5c16 ldrb r6, [r2, r0]
ldrb r7, [r2, r0]            // 5c17 ldrb r7, [r2, r0]
ldrb r0, [r3, r0]            // 5c18 ldrb r0, [r3, r0]
ldrb r1, [r3, r0]            // 5c19 ldrb r1, [r3, r0]
ldrb r2, [r3, r0]            // 5c1a ldrb r2, [r3, r0]
ldrb r3, [r3, r0]            // 5c1b ldrb r3, [r3, r0]
ldrb r4, [r3, r0]            // 5c1c ldrb r4, [r3, r0]
ldrb r5, [r3, r0]            // 5c1d ldrb r5, [r3, r0]
ldrb r6, [r3, r0]            // 5c1e ldrb r6, [r3, r0]
ldrb r7, [r3, r0]            // 5c1f ldrb r7, [r3, r0]
ldrb r0, [r4, r0]            // 5c20 ldrb r0, [r4, r0]
ldrb r1, [r4, r0]            // 5c21 ldrb r1, [r4, r0]
ldrb r2, [r4, r0]            // 5c22 ldrb r2, [r4, r0]
ldrb r3, [r4, r0]            // 5c23 ldrb r3, [r4, r0]
ldrb r4, [r4, r0]            // 5c24 ldrb r4, [r4, r0]
ldrb r5, [r4, r0]            // 5c25 ldrb r5, [r4, r0]
ldrb r6, [r4, r0]            // 5c26 ldrb r6, [r4, r0]
ldrb r7, [r4, r0]            // 5c27 ldrb r7, [r4, r0]
ldrb r0, [r5, r0]            // 5c28 ldrb r0, [r5, r0]
ldrb r1, [r5, r0]            // 5c29 ldrb r1, [r5, r0]
ldrb r2, [r5, r0]            // 5c2a ldrb r2, [r5, r0]
ldrb r3, [r5, r0]            // 5c2b ldrb r3, [r5, r0]
ldrb r4, [r5, r0]            // 5c2c ldrb r4, [r5, r0]
ldrb r5, [r5, r0]            // 5c2d ldrb r5, [r5, r0]
ldrb r6, [r5, r0]            // 5c2e ldrb r6, [r5, r0]
ldrb r7, [r5, r0]            // 5c2f ldrb r7, [r5, r0]
ldrb r0, [r6, r0]            // 5c30 ldrb r0, [r6, r0]
ldrb r1, [r6, r0]            // 5c31 ldrb r1, [r6, r0]
ldrb r2, [r6, r0]            // 5c32 ldrb r2, [r6, r0]
ldrb r3, [r6, r0]            // 5c33 ldrb r3, [r6, r0]
ldrb r4, [r6, r0]            // 5c34 ldrb r4, [r6, r0]
ldrb r5, [r6, r0]            // 5c35 ldrb r5, [r6, r0]
ldrb r6, [r6, r0]            // 5c36 ldrb r6, [r6, r0]
ldrb r7, [r6, r0]            // 5c37 ldrb r7, [r6, r0]
ldrb r0, [r7, r0]            // 5c38 ldrb r0, [r7, r0]
ldrb r1, [r7, r0]            // 5c39 ldrb r1, [r7, r0]
ldrb r2, [r7, r0]            // 5c3a ldrb r2, [r7, r0]
ldrb r3, [r7, r0]            // 5c3b ldrb r3, [r7, r0]
ldrb r4, [r7, r0]            // 5c3c ldrb r4, [r7, r0]
ldrb r5, [r7, r0]            // 5c3d ldrb r5, [r7, r0]
ldrb r6, [r7, r0]            // 5c3e ldrb r6, [r7, r0]
ldrb r7, [r7, r0]            // 5c3f ldrb r7, [r7, r0]
ldrb r0, [r0, r1]            // 5c40 ldrb r0, [r0, r1]
ldrb r1, [r0, r1]            // 5c41 ldrb r1, [r0, r1]
ldrb r2, [r0, r1]            // 5c42 ldrb r2, [r0, r1]
ldrb r3, [r0, r1]            // 5c43 ldrb r3, [r0, r1]
ldrb r4, [r0, r1]            // 5c44 ldrb r4, [r0, r1]
ldrb r5, [r0, r1]            // 5c45 ldrb r5, [r0, r1]
ldrb r6, [r0, r1]            // 5c46 ldrb r6, [r0, r1]
ldrb r7, [r0, r1]            // 5c47 ldrb r7, [r0, r1]
ldrb r0, [r1, r1]            // 5c48 ldrb r0, [r1, r1]
ldrb r1, [r1, r1]            // 5c49 ldrb r1, [r1, r1]
ldrb r2, [r1, r1]            // 5c4a ldrb r2, [r1, r1]
ldrb r3, [r1, r1]            // 5c4b ldrb r3, [r1, r1]
ldrb r4, [r1, r1]            // 5c4c ldrb r4, [r1, r1]
ldrb r5, [r1, r1]            // 5c4d ldrb r5, [r1, r1]
ldrb r6, [r1, r1]            // 5c4e ldrb r6, [r1, r1]
ldrb r7, [r1, r1]            // 5c4f ldrb r7, [r1, r1]
ldrb r0, [r2, r1]            // 5c50 ldrb r0, [r2, r1]
ldrb r1, [r2, r1]            // 5c51 ldrb r1, [r2, r1]
ldrb r2, [r2, r1]            // 5c52 ldrb r2, [r2, r1]
ldrb r3, [r2, r1]            // 5c53 ldrb r3, [r2, r1]
ldrb r4, [r2, r1]            // 5c54 ldrb r4, [r2, r1]
ldrb r5, [r2, r1]            // 5c55 ldrb r5, [r2, r1]
ldrb r6, [r2, r1]            // 5c56 ldrb r6, [r2, r1]
ldrb r7, [r2, r1]            // 5c57 ldrb r7, [r2, r1]
ldrb r0, [r3, r1]            // 5c58 ldrb r0, [r3, r1]
ldrb r1, [r3, r1]            // 5c59 ldrb r1, [r3, r1]
ldrb r2, [r3, r1]            // 5c5a ldrb r2, [r3, r1]
ldrb r3, [r3, r1]            // 5c5b ldrb r3, [r3, r1]
ldrb r4, [r3, r1]            // 5c5c ldrb r4, [r3, r1]
ldrb r5, [r3, r1]            // 5c5d ldrb r5, [r3, r1]
ldrb r6, [r3, r1]            // 5c5e ldrb r6, [r3, r1]
ldrb r7, [r3, r1]            // 5c5f ldrb r7, [r3, r1]
ldrb r0, [r4, r1]            // 5c60 ldrb r0, [r4, r1]
ldrb r1, [r4, r1]            // 5c61 ldrb r1, [r4, r1]
ldrb r2, [r4, r1]            // 5c62 ldrb r2, [r4, r1]
ldrb r3, [r4, r1]            // 5c63 ldrb r3, [r4, r1]
ldrb r4, [r4, r1]            // 5c64 ldrb r4, [r4, r1]
ldrb r5, [r4, r1]            // 5c65 ldrb r5, [r4, r1]
ldrb r6, [r4, r1]            // 5c66 ldrb r6, [r4, r1]
ldrb r7, [r4, r1]            // 5c67 ldrb r7, [r4, r1]
ldrb r0, [r5, r1]            // 5c68 ldrb r0, [r5, r1]
ldrb r1, [r5, r1]            // 5c69 ldrb r1, [r5, r1]
ldrb r2, [r5, r1]            // 5c6a ldrb r2, [r5, r1]
ldrb r3, [r5, r1]            // 5c6b ldrb r3, [r5, r1]
ldrb r4, [r5, r1]            // 5c6c ldrb r4, [r5, r1]
ldrb r5, [r5, r1]            // 5c6d ldrb r5, [r5, r1]
ldrb r6, [r5, r1]            // 5c6e ldrb r6, [r5, r1]
ldrb r7, [r5, r1]            // 5c6f ldrb r7, [r5, r1]
ldrb r0, [r6, r1]            // 5c70 ldrb r0, [r6, r1]
ldrb r1, [r6, r1]            // 5c71 ldrb r1, [r6, r1]
ldrb r2, [r6, r1]            // 5c72 ldrb r2, [r6, r1]
ldrb r3, [r6, r1]            // 5c73 ldrb r3, [r6, r1]
ldrb r4, [r6, r1]            // 5c74 ldrb r4, [r6, r1]
ldrb r5, [r6, r1]            // 5c75 ldrb r5, [r6, r1]
ldrb r6, [r6, r1]            // 5c76 ldrb r6, [r6, r1]
ldrb r7, [r6, r1]            // 5c77 ldrb r7, [r6, r1]
ldrb r0, [r7, r1]            // 5c78 ldrb r0, [r7, r1]
ldrb r1, [r7, r1]            // 5c79 ldrb r1, [r7, r1]
ldrb r2, [r7, r1]            // 5c7a ldrb r2, [r7, r1]
ldrb r3, [r7, r1]            // 5c7b ldrb r3, [r7, r1]
ldrb r4, [r7, r1]            // 5c7c ldrb r4, [r7, r1]
ldrb r5, [r7, r1]            // 5c7d ldrb r5, [r7, r1]
ldrb r6, [r7, r1]            // 5c7e ldrb r6, [r7, r1]
ldrb r7, [r7, r1]            // 5c7f ldrb r7, [r7, r1]
ldrb r0, [r0, r2]            // 5c80 ldrb r0, [r0, r2]
ldrb r1, [r0, r2]            // 5c81 ldrb r1, [r0, r2]
ldrb r2, [r0, r2]            // 5c82 ldrb r2, [r0, r2]
ldrb r3, [r0, r2]            // 5c83 ldrb r3, [r0, r2]
ldrb r4, [r0, r2]            // 5c84 ldrb r4, [r0, r2]
ldrb r5, [r0, r2]            // 5c85 ldrb r5, [r0, r2]
ldrb r6, [r0, r2]            // 5c86 ldrb r6, [r0, r2]
ldrb r7, [r0, r2]            // 5c87 ldrb r7, [r0, r2]
ldrb r0, [r1, r2]            // 5c88 ldrb r0, [r1, r2]
ldrb r1, [r1, r2]            // 5c89 ldrb r1, [r1, r2]
ldrb r2, [r1, r2]            // 5c8a ldrb r2, [r1, r2]
ldrb r3, [r1, r2]            // 5c8b ldrb r3, [r1, r2]
ldrb r4, [r1, r2]            // 5c8c ldrb r4, [r1, r2]
ldrb r5, [r1, r2]            // 5c8d ldrb r5, [r1, r2]
ldrb r6, [r1, r2]            // 5c8e ldrb r6, [r1, r2]
ldrb r7, [r1, r2]            // 5c8f ldrb r7, [r1, r2]
ldrb r0, [r2, r2]            // 5c90 ldrb r0, [r2, r2]
ldrb r1, [r2, r2]            // 5c91 ldrb r1, [r2, r2]
ldrb r2, [r2, r2]            // 5c92 ldrb r2, [r2, r2]
ldrb r3, [r2, r2]            // 5c93 ldrb r3, [r2, r2]
ldrb r4, [r2, r2]            // 5c94 ldrb r4, [r2, r2]
ldrb r5, [r2, r2]            // 5c95 ldrb r5, [r2, r2]
ldrb r6, [r2, r2]            // 5c96 ldrb r6, [r2, r2]
ldrb r7, [r2, r2]            // 5c97 ldrb r7, [r2, r2]
ldrb r0, [r3, r2]            // 5c98 ldrb r0, [r3, r2]
ldrb r1, [r3, r2]            // 5c99 ldrb r1, [r3, r2]
ldrb r2, [r3, r2]            // 5c9a ldrb r2, [r3, r2]
ldrb r3, [r3, r2]            // 5c9b ldrb r3, [r3, r2]
ldrb r4, [r3, r2]            // 5c9c ldrb r4, [r3, r2]
ldrb r5, [r3, r2]            // 5c9d ldrb r5, [r3, r2]
ldrb r6, [r3, r2]            // 5c9e ldrb r6, [r3, r2]
ldrb r7, [r3, r2]            // 5c9f ldrb r7, [r3, r2]
ldrb r0, [r4, r2]            // 5ca0 ldrb r0, [r4, r2]
ldrb r1, [r4, r2]            // 5ca1 ldrb r1, [r4, r2]
ldrb r2, [r4, r2]            // 5ca2 ldrb r2, [r4, r2]
ldrb r3, [r4, r2]            // 5ca3 ldrb r3, [r4, r2]
ldrb r4, [r4, r2]            // 5ca4 ldrb r4, [r4, r2]
ldrb r5, [r4, r2]            // 5ca5 ldrb r5, [r4, r2]
ldrb r6, [r4, r2]            // 5ca6 ldrb r6, [r4, r2]
ldrb r7, [r4, r2]            // 5ca7 ldrb r7, [r4, r2]
ldrb r0, [r5, r2]            // 5ca8 ldrb r0, [r5, r2]
ldrb r1, [r5, r2]            // 5ca9 ldrb r1, [r5, r2]
ldrb r2, [r5, r2]            // 5caa ldrb r2, [r5, r2]
ldrb r3, [r5, r2]            // 5cab ldrb r3, [r5, r2]
ldrb r4, [r5, r2]            // 5cac ldrb r4, [r5, r2]
ldrb r5, [r5, r2]            // 5cad ldrb r5, [r5, r2]
ldrb r6, [r5, r2]            // 5cae ldrb r6, [r5, r2]
ldrb r7, [r5, r2]            // 5caf ldrb r7, [r5, r2]
ldrb r0, [r6, r2]            // 5cb0 ldrb r0, [r6, r2]
ldrb r1, [r6, r2]            // 5cb1 ldrb r1, [r6, r2]
ldrb r2, [r6, r2]            // 5cb2 ldrb r2, [r6, r2]
ldrb r3, [r6, r2]            // 5cb3 ldrb r3, [r6, r2]
ldrb r4, [r6, r2]            // 5cb4 ldrb r4, [r6, r2]
ldrb r5, [r6, r2]            // 5cb5 ldrb r5, [r6, r2]
ldrb r6, [r6, r2]            // 5cb6 ldrb r6, [r6, r2]
ldrb r7, [r6, r2]            // 5cb7 ldrb r7, [r6, r2]
ldrb r0, [r7, r2]            // 5cb8 ldrb r0, [r7, r2]
ldrb r1, [r7, r2]            // 5cb9 ldrb r1, [r7, r2]
ldrb r2, [r7, r2]            // 5cba ldrb r2, [r7, r2]
ldrb r3, [r7, r2]            // 5cbb ldrb r3, [r7, r2]
ldrb r4, [r7, r2]            // 5cbc ldrb r4, [r7, r2]
ldrb r5, [r7, r2]            // 5cbd ldrb r5, [r7, r2]
ldrb r6, [r7, r2]            // 5cbe ldrb r6, [r7, r2]
ldrb r7, [r7, r2]            // 5cbf ldrb r7, [r7, r2]
ldrb r0, [r0, r3]            // 5cc0 ldrb r0, [r0, r3]
ldrb r1, [r0, r3]            // 5cc1 ldrb r1, [r0, r3]
ldrb r2, [r0, r3]            // 5cc2 ldrb r2, [r0, r3]
ldrb r3, [r0, r3]            // 5cc3 ldrb r3, [r0, r3]
ldrb r4, [r0, r3]            // 5cc4 ldrb r4, [r0, r3]
ldrb r5, [r0, r3]            // 5cc5 ldrb r5, [r0, r3]
ldrb r6, [r0, r3]            // 5cc6 ldrb r6, [r0, r3]
ldrb r7, [r0, r3]            // 5cc7 ldrb r7, [r0, r3]
ldrb r0, [r1, r3]            // 5cc8 ldrb r0, [r1, r3]
ldrb r1, [r1, r3]            // 5cc9 ldrb r1, [r1, r3]
ldrb r2, [r1, r3]            // 5cca ldrb r2, [r1, r3]
ldrb r3, [r1, r3]            // 5ccb ldrb r3, [r1, r3]
ldrb r4, [r1, r3]            // 5ccc ldrb r4, [r1, r3]
ldrb r5, [r1, r3]            // 5ccd ldrb r5, [r1, r3]
ldrb r6, [r1, r3]            // 5cce ldrb r6, [r1, r3]
ldrb r7, [r1, r3]            // 5ccf ldrb r7, [r1, r3]
ldrb r0, [r2, r3]            // 5cd0 ldrb r0, [r2, r3]
ldrb r1, [r2, r3]            // 5cd1 ldrb r1, [r2, r3]
ldrb r2, [r2, r3]            // 5cd2 ldrb r2, [r2, r3]
ldrb r3, [r2, r3]            // 5cd3 ldrb r3, [r2, r3]
ldrb r4, [r2, r3]            // 5cd4 ldrb r4, [r2, r3]
ldrb r5, [r2, r3]            // 5cd5 ldrb r5, [r2, r3]
ldrb r6, [r2, r3]            // 5cd6 ldrb r6, [r2, r3]
ldrb r7, [r2, r3]            // 5cd7 ldrb r7, [r2, r3]
ldrb r0, [r3, r3]            // 5cd8 ldrb r0, [r3, r3]
ldrb r1, [r3, r3]            // 5cd9 ldrb r1, [r3, r3]
ldrb r2, [r3, r3]            // 5cda ldrb r2, [r3, r3]
ldrb r3, [r3, r3]            // 5cdb ldrb r3, [r3, r3]
ldrb r4, [r3, r3]            // 5cdc ldrb r4, [r3, r3]
ldrb r5, [r3, r3]            // 5cdd ldrb r5, [r3, r3]
ldrb r6, [r3, r3]            // 5cde ldrb r6, [r3, r3]
ldrb r7, [r3, r3]            // 5cdf ldrb r7, [r3, r3]
ldrb r0, [r4, r3]            // 5ce0 ldrb r0, [r4, r3]
ldrb r1, [r4, r3]            // 5ce1 ldrb r1, [r4, r3]
ldrb r2, [r4, r3]            // 5ce2 ldrb r2, [r4, r3]
ldrb r3, [r4, r3]            // 5ce3 ldrb r3, [r4, r3]
ldrb r4, [r4, r3]            // 5ce4 ldrb r4, [r4, r3]
ldrb r5, [r4, r3]            // 5ce5 ldrb r5, [r4, r3]
ldrb r6, [r4, r3]            // 5ce6 ldrb r6, [r4, r3]
ldrb r7, [r4, r3]            // 5ce7 ldrb r7, [r4, r3]
ldrb r0, [r5, r3]            // 5ce8 ldrb r0, [r5, r3]
ldrb r1, [r5, r3]            // 5ce9 ldrb r1, [r5, r3]
ldrb r2, [r5, r3]            // 5cea ldrb r2, [r5, r3]
ldrb r3, [r5, r3]            // 5ceb ldrb r3, [r5, r3]
ldrb r4, [r5, r3]            // 5cec ldrb r4, [r5, r3]
ldrb r5, [r5, r3]            // 5ced ldrb r5, [r5, r3]
ldrb r6, [r5, r3]            // 5cee ldrb r6, [r5, r3]
ldrb r7, [r5, r3]            // 5cef ldrb r7, [r5, r3]
ldrb r0, [r6, r3]            // 5cf0 ldrb r0, [r6, r3]
ldrb r1, [r6, r3]            // 5cf1 ldrb r1, [r6, r3]
ldrb r2, [r6, r3]            // 5cf2 ldrb r2, [r6, r3]
ldrb r3, [r6, r3]            // 5cf3 ldrb r3, [r6, r3]
ldrb r4, [r6, r3]            // 5cf4 ldrb r4, [r6, r3]
ldrb r5, [r6, r3]            // 5cf5 ldrb r5, [r6, r3]
ldrb r6, [r6, r3]            // 5cf6 ldrb r6, [r6, r3]
ldrb r7, [r6, r3]            // 5cf7 ldrb r7, [r6, r3]
ldrb r0, [r7, r3]            // 5cf8 ldrb r0, [r7, r3]
ldrb r1, [r7, r3]            // 5cf9 ldrb r1, [r7, r3]
ldrb r2, [r7, r3]            // 5cfa ldrb r2, [r7, r3]
ldrb r3, [r7, r3]            // 5cfb ldrb r3, [r7, r3]
ldrb r4, [r7, r3]            // 5cfc ldrb r4, [r7, r3]
ldrb r5, [r7, r3]            // 5cfd ldrb r5, [r7, r3]
ldrb r6, [r7, r3]            // 5cfe ldrb r6, [r7, r3]
ldrb r7, [r7, r3]            // 5cff ldrb r7, [r7, r3]
ldrb r0, [r0, r4]            // 5d00 ldrb r0, [r0, r4]
ldrb r1, [r0, r4]            // 5d01 ldrb r1, [r0, r4]
ldrb r2, [r0, r4]            // 5d02 ldrb r2, [r0, r4]
ldrb r3, [r0, r4]            // 5d03 ldrb r3, [r0, r4]
ldrb r4, [r0, r4]            // 5d04 ldrb r4, [r0, r4]
ldrb r5, [r0, r4]            // 5d05 ldrb r5, [r0, r4]
ldrb r6, [r0, r4]            // 5d06 ldrb r6, [r0, r4]
ldrb r7, [r0, r4]            // 5d07 ldrb r7, [r0, r4]
ldrb r0, [r1, r4]            // 5d08 ldrb r0, [r1, r4]
ldrb r1, [r1, r4]            // 5d09 ldrb r1, [r1, r4]
ldrb r2, [r1, r4]            // 5d0a ldrb r2, [r1, r4]
ldrb r3, [r1, r4]            // 5d0b ldrb r3, [r1, r4]
ldrb r4, [r1, r4]            // 5d0c ldrb r4, [r1, r4]
ldrb r5, [r1, r4]            // 5d0d ldrb r5, [r1, r4]
ldrb r6, [r1, r4]            // 5d0e ldrb r6, [r1, r4]
ldrb r7, [r1, r4]            // 5d0f ldrb r7, [r1, r4]
ldrb r0, [r2, r4]            // 5d10 ldrb r0, [r2, r4]
ldrb r1, [r2, r4]            // 5d11 ldrb r1, [r2, r4]
ldrb r2, [r2, r4]            // 5d12 ldrb r2, [r2, r4]
ldrb r3, [r2, r4]            // 5d13 ldrb r3, [r2, r4]
ldrb r4, [r2, r4]            // 5d14 ldrb r4, [r2, r4]
ldrb r5, [r2, r4]            // 5d15 ldrb r5, [r2, r4]
ldrb r6, [r2, r4]            // 5d16 ldrb r6, [r2, r4]
ldrb r7, [r2, r4]            // 5d17 ldrb r7, [r2, r4]
ldrb r0, [r3, r4]            // 5d18 ldrb r0, [r3, r4]
ldrb r1, [r3, r4]            // 5d19 ldrb r1, [r3, r4]
ldrb r2, [r3, r4]            // 5d1a ldrb r2, [r3, r4]
ldrb r3, [r3, r4]            // 5d1b ldrb r3, [r3, r4]
ldrb r4, [r3, r4]            // 5d1c ldrb r4, [r3, r4]
ldrb r5, [r3, r4]            // 5d1d ldrb r5, [r3, r4]
ldrb r6, [r3, r4]            // 5d1e ldrb r6, [r3, r4]
ldrb r7, [r3, r4]            // 5d1f ldrb r7, [r3, r4]
ldrb r0, [r4, r4]            // 5d20 ldrb r0, [r4, r4]
ldrb r1, [r4, r4]            // 5d21 ldrb r1, [r4, r4]
ldrb r2, [r4, r4]            // 5d22 ldrb r2, [r4, r4]
ldrb r3, [r4, r4]            // 5d23 ldrb r3, [r4, r4]
ldrb r4, [r4, r4]            // 5d24 ldrb r4, [r4, r4]
ldrb r5, [r4, r4]            // 5d25 ldrb r5, [r4, r4]
ldrb r6, [r4, r4]            // 5d26 ldrb r6, [r4, r4]
ldrb r7, [r4, r4]            // 5d27 ldrb r7, [r4, r4]
ldrb r0, [r5, r4]            // 5d28 ldrb r0, [r5, r4]
ldrb r1, [r5, r4]            // 5d29 ldrb r1, [r5, r4]
ldrb r2, [r5, r4]            // 5d2a ldrb r2, [r5, r4]
ldrb r3, [r5, r4]            // 5d2b ldrb r3, [r5, r4]
ldrb r4, [r5, r4]            // 5d2c ldrb r4, [r5, r4]
ldrb r5, [r5, r4]            // 5d2d ldrb r5, [r5, r4]
ldrb r6, [r5, r4]            // 5d2e ldrb r6, [r5, r4]
ldrb r7, [r5, r4]            // 5d2f ldrb r7, [r5, r4]
ldrb r0, [r6, r4]            // 5d30 ldrb r0, [r6, r4]
ldrb r1, [r6, r4]            // 5d31 ldrb r1, [r6, r4]
ldrb r2, [r6, r4]            // 5d32 ldrb r2, [r6, r4]
ldrb r3, [r6, r4]            // 5d33 ldrb r3, [r6, r4]
ldrb r4, [r6, r4]            // 5d34 ldrb r4, [r6, r4]
ldrb r5, [r6, r4]            // 5d35 ldrb r5, [r6, r4]
ldrb r6, [r6, r4]            // 5d36 ldrb r6, [r6, r4]
ldrb r7, [r6, r4]            // 5d37 ldrb r7, [r6, r4]
ldrb r0, [r7, r4]            // 5d38 ldrb r0, [r7, r4]
ldrb r1, [r7, r4]            // 5d39 ldrb r1, [r7, r4]
ldrb r2, [r7, r4]            // 5d3a ldrb r2, [r7, r4]
ldrb r3, [r7, r4]            // 5d3b ldrb r3, [r7, r4]
ldrb r4, [r7, r4]            // 5d3c ldrb r4, [r7, r4]
ldrb r5, [r7, r4]            // 5d3d ldrb r5, [r7, r4]
ldrb r6, [r7, r4]            // 5d3e ldrb r6, [r7, r4]
ldrb r7, [r7, r4]            // 5d3f ldrb r7, [r7, r4]
ldrb r0, [r0, r5]            // 5d40 ldrb r0, [r0, r5]
ldrb r1, [r0, r5]            // 5d41 ldrb r1, [r0, r5]
ldrb r2, [r0, r5]            // 5d42 ldrb r2, [r0, r5]
ldrb r3, [r0, r5]            // 5d43 ldrb r3, [r0, r5]
ldrb r4, [r0, r5]            // 5d44 ldrb r4, [r0, r5]
ldrb r5, [r0, r5]            // 5d45 ldrb r5, [r0, r5]
ldrb r6, [r0, r5]            // 5d46 ldrb r6, [r0, r5]
ldrb r7, [r0, r5]            // 5d47 ldrb r7, [r0, r5]
ldrb r0, [r1, r5]            // 5d48 ldrb r0, [r1, r5]
ldrb r1, [r1, r5]            // 5d49 ldrb r1, [r1, r5]
ldrb r2, [r1, r5]            // 5d4a ldrb r2, [r1, r5]
ldrb r3, [r1, r5]            // 5d4b ldrb r3, [r1, r5]
ldrb r4, [r1, r5]            // 5d4c ldrb r4, [r1, r5]
ldrb r5, [r1, r5]            // 5d4d ldrb r5, [r1, r5]
ldrb r6, [r1, r5]            // 5d4e ldrb r6, [r1, r5]
ldrb r7, [r1, r5]            // 5d4f ldrb r7, [r1, r5]
ldrb r0, [r2, r5]            // 5d50 ldrb r0, [r2, r5]
ldrb r1, [r2, r5]            // 5d51 ldrb r1, [r2, r5]
ldrb r2, [r2, r5]            // 5d52 ldrb r2, [r2, r5]
ldrb r3, [r2, r5]            // 5d53 ldrb r3, [r2, r5]
ldrb r4, [r2, r5]            // 5d54 ldrb r4, [r2, r5]
ldrb r5, [r2, r5]            // 5d55 ldrb r5, [r2, r5]
ldrb r6, [r2, r5]            // 5d56 ldrb r6, [r2, r5]
ldrb r7, [r2, r5]            // 5d57 ldrb r7, [r2, r5]
ldrb r0, [r3, r5]            // 5d58 ldrb r0, [r3, r5]
ldrb r1, [r3, r5]            // 5d59 ldrb r1, [r3, r5]
ldrb r2, [r3, r5]            // 5d5a ldrb r2, [r3, r5]
ldrb r3, [r3, r5]            // 5d5b ldrb r3, [r3, r5]
ldrb r4, [r3, r5]            // 5d5c ldrb r4, [r3, r5]
ldrb r5, [r3, r5]            // 5d5d ldrb r5, [r3, r5]
ldrb r6, [r3, r5]            // 5d5e ldrb r6, [r3, r5]
ldrb r7, [r3, r5]            // 5d5f ldrb r7, [r3, r5]
ldrb r0, [r4, r5]            // 5d60 ldrb r0, [r4, r5]
ldrb r1, [r4, r5]            // 5d61 ldrb r1, [r4, r5]
ldrb r2, [r4, r5]            // 5d62 ldrb r2, [r4, r5]
ldrb r3, [r4, r5]            // 5d63 ldrb r3, [r4, r5]
ldrb r4, [r4, r5]            // 5d64 ldrb r4, [r4, r5]
ldrb r5, [r4, r5]            // 5d65 ldrb r5, [r4, r5]
ldrb r6, [r4, r5]            // 5d66 ldrb r6, [r4, r5]
ldrb r7, [r4, r5]            // 5d67 ldrb r7, [r4, r5]
ldrb r0, [r5, r5]            // 5d68 ldrb r0, [r5, r5]
ldrb r1, [r5, r5]            // 5d69 ldrb r1, [r5, r5]
ldrb r2, [r5, r5]            // 5d6a ldrb r2, [r5, r5]
ldrb r3, [r5, r5]            // 5d6b ldrb r3, [r5, r5]
ldrb r4, [r5, r5]            // 5d6c ldrb r4, [r5, r5]
ldrb r5, [r5, r5]            // 5d6d ldrb r5, [r5, r5]
ldrb r6, [r5, r5]            // 5d6e ldrb r6, [r5, r5]
ldrb r7, [r5, r5]            // 5d6f ldrb r7, [r5, r5]
ldrb r0, [r6, r5]            // 5d70 ldrb r0, [r6, r5]
ldrb r1, [r6, r5]            // 5d71 ldrb r1, [r6, r5]
ldrb r2, [r6, r5]            // 5d72 ldrb r2, [r6, r5]
ldrb r3, [r6, r5]            // 5d73 ldrb r3, [r6, r5]
ldrb r4, [r6, r5]            // 5d74 ldrb r4, [r6, r5]
ldrb r5, [r6, r5]            // 5d75 ldrb r5, [r6, r5]
ldrb r6, [r6, r5]            // 5d76 ldrb r6, [r6, r5]
ldrb r7, [r6, r5]            // 5d77 ldrb r7, [r6, r5]
ldrb r0, [r7, r5]            // 5d78 ldrb r0, [r7, r5]
ldrb r1, [r7, r5]            // 5d79 ldrb r1, [r7, r5]
ldrb r2, [r7, r5]            // 5d7a ldrb r2, [r7, r5]
ldrb r3, [r7, r5]            // 5d7b ldrb r3, [r7, r5]
ldrb r4, [r7, r5]            // 5d7c ldrb r4, [r7, r5]
ldrb r5, [r7, r5]            // 5d7d ldrb r5, [r7, r5]
ldrb r6, [r7, r5]            // 5d7e ldrb r6, [r7, r5]
ldrb r7, [r7, r5]            // 5d7f ldrb r7, [r7, r5]
ldrb r0, [r0, r6]            // 5d80 ldrb r0, [r0, r6]
ldrb r1, [r0, r6]            // 5d81 ldrb r1, [r0, r6]
ldrb r2, [r0, r6]            // 5d82 ldrb r2, [r0, r6]
ldrb r3, [r0, r6]            // 5d83 ldrb r3, [r0, r6]
ldrb r4, [r0, r6]            // 5d84 ldrb r4, [r0, r6]
ldrb r5, [r0, r6]            // 5d85 ldrb r5, [r0, r6]
ldrb r6, [r0, r6]            // 5d86 ldrb r6, [r0, r6]
ldrb r7, [r0, r6]            // 5d87 ldrb r7, [r0, r6]
ldrb r0, [r1, r6]            // 5d88 ldrb r0, [r1, r6]
ldrb r1, [r1, r6]            // 5d89 ldrb r1, [r1, r6]
ldrb r2, [r1, r6]            // 5d8a ldrb r2, [r1, r6]
ldrb r3, [r1, r6]            // 5d8b ldrb r3, [r1, r6]
ldrb r4, [r1, r6]            // 5d8c ldrb r4, [r1, r6]
ldrb r5, [r1, r6]            // 5d8d ldrb r5, [r1, r6]
ldrb r6, [r1, r6]            // 5d8e ldrb r6, [r1, r6]
ldrb r7, [r1, r6]            // 5d8f ldrb r7, [r1, r6]
ldrb r0, [r2, r6]            // 5d90 ldrb r0, [r2, r6]
ldrb r1, [r2, r6]            // 5d91 ldrb r1, [r2, r6]
ldrb r2, [r2, r6]            // 5d92 ldrb r2, [r2, r6]
ldrb r3, [r2, r6]            // 5d93 ldrb r3, [r2, r6]
ldrb r4, [r2, r6]            // 5d94 ldrb r4, [r2, r6]
ldrb r5, [r2, r6]            // 5d95 ldrb r5, [r2, r6]
ldrb r6, [r2, r6]            // 5d96 ldrb r6, [r2, r6]
ldrb r7, [r2, r6]            // 5d97 ldrb r7, [r2, r6]
ldrb r0, [r3, r6]            // 5d98 ldrb r0, [r3, r6]
ldrb r1, [r3, r6]            // 5d99 ldrb r1, [r3, r6]
ldrb r2, [r3, r6]            // 5d9a ldrb r2, [r3, r6]
ldrb r3, [r3, r6]            // 5d9b ldrb r3, [r3, r6]
ldrb r4, [r3, r6]            // 5d9c ldrb r4, [r3, r6]
ldrb r5, [r3, r6]            // 5d9d ldrb r5, [r3, r6]
ldrb r6, [r3, r6]            // 5d9e ldrb r6, [r3, r6]
ldrb r7, [r3, r6]            // 5d9f ldrb r7, [r3, r6]
ldrb r0, [r4, r6]            // 5da0 ldrb r0, [r4, r6]
ldrb r1, [r4, r6]            // 5da1 ldrb r1, [r4, r6]
ldrb r2, [r4, r6]            // 5da2 ldrb r2, [r4, r6]
ldrb r3, [r4, r6]            // 5da3 ldrb r3, [r4, r6]
ldrb r4, [r4, r6]            // 5da4 ldrb r4, [r4, r6]
ldrb r5, [r4, r6]            // 5da5 ldrb r5, [r4, r6]
ldrb r6, [r4, r6]            // 5da6 ldrb r6, [r4, r6]
ldrb r7, [r4, r6]            // 5da7 ldrb r7, [r4, r6]
ldrb r0, [r5, r6]            // 5da8 ldrb r0, [r5, r6]
ldrb r1, [r5, r6]            // 5da9 ldrb r1, [r5, r6]
ldrb r2, [r5, r6]            // 5daa ldrb r2, [r5, r6]
ldrb r3, [r5, r6]            // 5dab ldrb r3, [r5, r6]
ldrb r4, [r5, r6]            // 5dac ldrb r4, [r5, r6]
ldrb r5, [r5, r6]            // 5dad ldrb r5, [r5, r6]
ldrb r6, [r5, r6]            // 5dae ldrb r6, [r5, r6]
ldrb r7, [r5, r6]            // 5daf ldrb r7, [r5, r6]
ldrb r0, [r6, r6]            // 5db0 ldrb r0, [r6, r6]
ldrb r1, [r6, r6]            // 5db1 ldrb r1, [r6, r6]
ldrb r2, [r6, r6]            // 5db2 ldrb r2, [r6, r6]
ldrb r3, [r6, r6]            // 5db3 ldrb r3, [r6, r6]
ldrb r4, [r6, r6]            // 5db4 ldrb r4, [r6, r6]
ldrb r5, [r6, r6]            // 5db5 ldrb r5, [r6, r6]
ldrb r6, [r6, r6]            // 5db6 ldrb r6, [r6, r6]
ldrb r7, [r6, r6]            // 5db7 ldrb r7, [r6, r6]
ldrb r0, [r7, r6]            // 5db8 ldrb r0, [r7, r6]
ldrb r1, [r7, r6]            // 5db9 ldrb r1, [r7, r6]
ldrb r2, [r7, r6]            // 5dba ldrb r2, [r7, r6]
ldrb r3, [r7, r6]            // 5dbb ldrb r3, [r7, r6]
ldrb r4, [r7, r6]            // 5dbc ldrb r4, [r7, r6]
ldrb r5, [r7, r6]            // 5dbd ldrb r5, [r7, r6]
ldrb r6, [r7, r6]            // 5dbe ldrb r6, [r7, r6]
ldrb r7, [r7, r6]            // 5dbf ldrb r7, [r7, r6]
ldrb r0, [r0, r7]            // 5dc0 ldrb r0, [r0, r7]
ldrb r1, [r0, r7]            // 5dc1 ldrb r1, [r0, r7]
ldrb r2, [r0, r7]            // 5dc2 ldrb r2, [r0, r7]
ldrb r3, [r0, r7]            // 5dc3 ldrb r3, [r0, r7]
ldrb r4, [r0, r7]            // 5dc4 ldrb r4, [r0, r7]
ldrb r5, [r0, r7]            // 5dc5 ldrb r5, [r0, r7]
ldrb r6, [r0, r7]            // 5dc6 ldrb r6, [r0, r7]
ldrb r7, [r0, r7]            // 5dc7 ldrb r7, [r0, r7]
ldrb r0, [r1, r7]            // 5dc8 ldrb r0, [r1, r7]
ldrb r1, [r1, r7]            // 5dc9 ldrb r1, [r1, r7]
ldrb r2, [r1, r7]            // 5dca ldrb r2, [r1, r7]
ldrb r3, [r1, r7]            // 5dcb ldrb r3, [r1, r7]
ldrb r4, [r1, r7]            // 5dcc ldrb r4, [r1, r7]
ldrb r5, [r1, r7]            // 5dcd ldrb r5, [r1, r7]
ldrb r6, [r1, r7]            // 5dce ldrb r6, [r1, r7]
ldrb r7, [r1, r7]            // 5dcf ldrb r7, [r1, r7]
ldrb r0, [r2, r7]            // 5dd0 ldrb r0, [r2, r7]
ldrb r1, [r2, r7]            // 5dd1 ldrb r1, [r2, r7]
ldrb r2, [r2, r7]            // 5dd2 ldrb r2, [r2, r7]
ldrb r3, [r2, r7]            // 5dd3 ldrb r3, [r2, r7]
ldrb r4, [r2, r7]            // 5dd4 ldrb r4, [r2, r7]
ldrb r5, [r2, r7]            // 5dd5 ldrb r5, [r2, r7]
ldrb r6, [r2, r7]            // 5dd6 ldrb r6, [r2, r7]
ldrb r7, [r2, r7]            // 5dd7 ldrb r7, [r2, r7]
ldrb r0, [r3, r7]            // 5dd8 ldrb r0, [r3, r7]
ldrb r1, [r3, r7]            // 5dd9 ldrb r1, [r3, r7]
ldrb r2, [r3, r7]            // 5dda ldrb r2, [r3, r7]
ldrb r3, [r3, r7]            // 5ddb ldrb r3, [r3, r7]
ldrb r4, [r3, r7]            // 5ddc ldrb r4, [r3, r7]
ldrb r5, [r3, r7]            // 5ddd ldrb r5, [r3, r7]
ldrb r6, [r3, r7]            // 5dde ldrb r6, [r3, r7]
ldrb r7, [r3, r7]            // 5ddf ldrb r7, [r3, r7]
ldrb r0, [r4, r7]            // 5de0 ldrb r0, [r4, r7]
ldrb r1, [r4, r7]            // 5de1 ldrb r1, [r4, r7]
ldrb r2, [r4, r7]            // 5de2 ldrb r2, [r4, r7]
ldrb r3, [r4, r7]            // 5de3 ldrb r3, [r4, r7]
ldrb r4, [r4, r7]            // 5de4 ldrb r4, [r4, r7]
ldrb r5, [r4, r7]            // 5de5 ldrb r5, [r4, r7]
ldrb r6, [r4, r7]            // 5de6 ldrb r6, [r4, r7]
ldrb r7, [r4, r7]            // 5de7 ldrb r7, [r4, r7]
ldrb r0, [r5, r7]            // 5de8 ldrb r0, [r5, r7]
ldrb r1, [r5, r7]            // 5de9 ldrb r1, [r5, r7]
ldrb r2, [r5, r7]            // 5dea ldrb r2, [r5, r7]
ldrb r3, [r5, r7]            // 5deb ldrb r3, [r5, r7]
ldrb r4, [r5, r7]            // 5dec ldrb r4, [r5, r7]
ldrb r5, [r5, r7]            // 5ded ldrb r5, [r5, r7]
ldrb r6, [r5, r7]            // 5dee ldrb r6, [r5, r7]
ldrb r7, [r5, r7]            // 5def ldrb r7, [r5, r7]
ldrb r0, [r6, r7]            // 5df0 ldrb r0, [r6, r7]
ldrb r1, [r6, r7]            // 5df1 ldrb r1, [r6, r7]
ldrb r2, [r6, r7]            // 5df2 ldrb r2, [r6, r7]
ldrb r3, [r6, r7]            // 5df3 ldrb r3, [r6, r7]
ldrb r4, [r6, r7]            // 5df4 ldrb r4, [r6, r7]
ldrb r5, [r6, r7]            // 5df5 ldrb r5, [r6, r7]
ldrb r6, [r6, r7]            // 5df6 ldrb r6, [r6, r7]
ldrb r7, [r6, r7]            // 5df7 ldrb r7, [r6, r7]
ldrb r0, [r7, r7]            // 5df8 ldrb r0, [r7, r7]
ldrb r1, [r7, r7]            // 5df9 ldrb r1, [r7, r7]
ldrb r2, [r7, r7]            // 5dfa ldrb r2, [r7, r7]
ldrb r3, [r7, r7]            // 5dfb ldrb r3, [r7, r7]
ldrb r4, [r7, r7]            // 5dfc ldrb r4, [r7, r7]
ldrb r5, [r7, r7]            // 5dfd ldrb r5, [r7, r7]
ldrb r6, [r7, r7]            // 5dfe ldrb r6, [r7, r7]
ldrb r7, [r7, r7]            // 5dff ldrb r7, [r7, r7]

ldrsh r0, [r0, r0]           // 5e00 ldrsh r0, [r0, r0]
ldrsh r1, [r0, r0]           // 5e01 ldrsh r1, [r0, r0]
ldrsh r2, [r0, r0]           // 5e02 ldrsh r2, [r0, r0]
ldrsh r3, [r0, r0]           // 5e03 ldrsh r3, [r0, r0]
ldrsh r4, [r0, r0]           // 5e04 ldrsh r4, [r0, r0]
ldrsh r5, [r0, r0]           // 5e05 ldrsh r5, [r0, r0]
ldrsh r6, [r0, r0]           // 5e06 ldrsh r6, [r0, r0]
ldrsh r7, [r0, r0]           // 5e07 ldrsh r7, [r0, r0]
ldrsh r0, [r1, r0]           // 5e08 ldrsh r0, [r1, r0]
ldrsh r1, [r1, r0]           // 5e09 ldrsh r1, [r1, r0]
ldrsh r2, [r1, r0]           // 5e0a ldrsh r2, [r1, r0]
ldrsh r3, [r1, r0]           // 5e0b ldrsh r3, [r1, r0]
ldrsh r4, [r1, r0]           // 5e0c ldrsh r4, [r1, r0]
ldrsh r5, [r1, r0]           // 5e0d ldrsh r5, [r1, r0]
ldrsh r6, [r1, r0]           // 5e0e ldrsh r6, [r1, r0]
ldrsh r7, [r1, r0]           // 5e0f ldrsh r7, [r1, r0]
ldrsh r0, [r2, r0]           // 5e10 ldrsh r0, [r2, r0]
ldrsh r1, [r2, r0]           // 5e11 ldrsh r1, [r2, r0]
ldrsh r2, [r2, r0]           // 5e12 ldrsh r2, [r2, r0]
ldrsh r3, [r2, r0]           // 5e13 ldrsh r3, [r2, r0]
ldrsh r4, [r2, r0]           // 5e14 ldrsh r4, [r2, r0]
ldrsh r5, [r2, r0]           // 5e15 ldrsh r5, [r2, r0]
ldrsh r6, [r2, r0]           // 5e16 ldrsh r6, [r2, r0]
ldrsh r7, [r2, r0]           // 5e17 ldrsh r7, [r2, r0]
ldrsh r0, [r3, r0]           // 5e18 ldrsh r0, [r3, r0]
ldrsh r1, [r3, r0]           // 5e19 ldrsh r1, [r3, r0]
ldrsh r2, [r3, r0]           // 5e1a ldrsh r2, [r3, r0]
ldrsh r3, [r3, r0]           // 5e1b ldrsh r3, [r3, r0]
ldrsh r4, [r3, r0]           // 5e1c ldrsh r4, [r3, r0]
ldrsh r5, [r3, r0]           // 5e1d ldrsh r5, [r3, r0]
ldrsh r6, [r3, r0]           // 5e1e ldrsh r6, [r3, r0]
ldrsh r7, [r3, r0]           // 5e1f ldrsh r7, [r3, r0]
ldrsh r0, [r4, r0]           // 5e20 ldrsh r0, [r4, r0]
ldrsh r1, [r4, r0]           // 5e21 ldrsh r1, [r4, r0]
ldrsh r2, [r4, r0]           // 5e22 ldrsh r2, [r4, r0]
ldrsh r3, [r4, r0]           // 5e23 ldrsh r3, [r4, r0]
ldrsh r4, [r4, r0]           // 5e24 ldrsh r4, [r4, r0]
ldrsh r5, [r4, r0]           // 5e25 ldrsh r5, [r4, r0]
ldrsh r6, [r4, r0]           // 5e26 ldrsh r6, [r4, r0]
ldrsh r7, [r4, r0]           // 5e27 ldrsh r7, [r4, r0]
ldrsh r0, [r5, r0]           // 5e28 ldrsh r0, [r5, r0]
ldrsh r1, [r5, r0]           // 5e29 ldrsh r1, [r5, r0]
ldrsh r2, [r5, r0]           // 5e2a ldrsh r2, [r5, r0]
ldrsh r3, [r5, r0]           // 5e2b ldrsh r3, [r5, r0]
ldrsh r4, [r5, r0]           // 5e2c ldrsh r4, [r5, r0]
ldrsh r5, [r5, r0]           // 5e2d ldrsh r5, [r5, r0]
ldrsh r6, [r5, r0]           // 5e2e ldrsh r6, [r5, r0]
ldrsh r7, [r5, r0]           // 5e2f ldrsh r7, [r5, r0]
ldrsh r0, [r6, r0]           // 5e30 ldrsh r0, [r6, r0]
ldrsh r1, [r6, r0]           // 5e31 ldrsh r1, [r6, r0]
ldrsh r2, [r6, r0]           // 5e32 ldrsh r2, [r6, r0]
ldrsh r3, [r6, r0]           // 5e33 ldrsh r3, [r6, r0]
ldrsh r4, [r6, r0]           // 5e34 ldrsh r4, [r6, r0]
ldrsh r5, [r6, r0]           // 5e35 ldrsh r5, [r6, r0]
ldrsh r6, [r6, r0]           // 5e36 ldrsh r6, [r6, r0]
ldrsh r7, [r6, r0]           // 5e37 ldrsh r7, [r6, r0]
ldrsh r0, [r7, r0]           // 5e38 ldrsh r0, [r7, r0]
ldrsh r1, [r7, r0]           // 5e39 ldrsh r1, [r7, r0]
ldrsh r2, [r7, r0]           // 5e3a ldrsh r2, [r7, r0]
ldrsh r3, [r7, r0]           // 5e3b ldrsh r3, [r7, r0]
ldrsh r4, [r7, r0]           // 5e3c ldrsh r4, [r7, r0]
ldrsh r5, [r7, r0]           // 5e3d ldrsh r5, [r7, r0]
ldrsh r6, [r7, r0]           // 5e3e ldrsh r6, [r7, r0]
ldrsh r7, [r7, r0]           // 5e3f ldrsh r7, [r7, r0]
ldrsh r0, [r0, r1]           // 5e40 ldrsh r0, [r0, r1]
ldrsh r1, [r0, r1]           // 5e41 ldrsh r1, [r0, r1]
ldrsh r2, [r0, r1]           // 5e42 ldrsh r2, [r0, r1]
ldrsh r3, [r0, r1]           // 5e43 ldrsh r3, [r0, r1]
ldrsh r4, [r0, r1]           // 5e44 ldrsh r4, [r0, r1]
ldrsh r5, [r0, r1]           // 5e45 ldrsh r5, [r0, r1]
ldrsh r6, [r0, r1]           // 5e46 ldrsh r6, [r0, r1]
ldrsh r7, [r0, r1]           // 5e47 ldrsh r7, [r0, r1]
ldrsh r0, [r1, r1]           // 5e48 ldrsh r0, [r1, r1]
ldrsh r1, [r1, r1]           // 5e49 ldrsh r1, [r1, r1]
ldrsh r2, [r1, r1]           // 5e4a ldrsh r2, [r1, r1]
ldrsh r3, [r1, r1]           // 5e4b ldrsh r3, [r1, r1]
ldrsh r4, [r1, r1]           // 5e4c ldrsh r4, [r1, r1]
ldrsh r5, [r1, r1]           // 5e4d ldrsh r5, [r1, r1]
ldrsh r6, [r1, r1]           // 5e4e ldrsh r6, [r1, r1]
ldrsh r7, [r1, r1]           // 5e4f ldrsh r7, [r1, r1]
ldrsh r0, [r2, r1]           // 5e50 ldrsh r0, [r2, r1]
ldrsh r1, [r2, r1]           // 5e51 ldrsh r1, [r2, r1]
ldrsh r2, [r2, r1]           // 5e52 ldrsh r2, [r2, r1]
ldrsh r3, [r2, r1]           // 5e53 ldrsh r3, [r2, r1]
ldrsh r4, [r2, r1]           // 5e54 ldrsh r4, [r2, r1]
ldrsh r5, [r2, r1]           // 5e55 ldrsh r5, [r2, r1]
ldrsh r6, [r2, r1]           // 5e56 ldrsh r6, [r2, r1]
ldrsh r7, [r2, r1]           // 5e57 ldrsh r7, [r2, r1]
ldrsh r0, [r3, r1]           // 5e58 ldrsh r0, [r3, r1]
ldrsh r1, [r3, r1]           // 5e59 ldrsh r1, [r3, r1]
ldrsh r2, [r3, r1]           // 5e5a ldrsh r2, [r3, r1]
ldrsh r3, [r3, r1]           // 5e5b ldrsh r3, [r3, r1]
ldrsh r4, [r3, r1]           // 5e5c ldrsh r4, [r3, r1]
ldrsh r5, [r3, r1]           // 5e5d ldrsh r5, [r3, r1]
ldrsh r6, [r3, r1]           // 5e5e ldrsh r6, [r3, r1]
ldrsh r7, [r3, r1]           // 5e5f ldrsh r7, [r3, r1]
ldrsh r0, [r4, r1]           // 5e60 ldrsh r0, [r4, r1]
ldrsh r1, [r4, r1]           // 5e61 ldrsh r1, [r4, r1]
ldrsh r2, [r4, r1]           // 5e62 ldrsh r2, [r4, r1]
ldrsh r3, [r4, r1]           // 5e63 ldrsh r3, [r4, r1]
ldrsh r4, [r4, r1]           // 5e64 ldrsh r4, [r4, r1]
ldrsh r5, [r4, r1]           // 5e65 ldrsh r5, [r4, r1]
ldrsh r6, [r4, r1]           // 5e66 ldrsh r6, [r4, r1]
ldrsh r7, [r4, r1]           // 5e67 ldrsh r7, [r4, r1]
ldrsh r0, [r5, r1]           // 5e68 ldrsh r0, [r5, r1]
ldrsh r1, [r5, r1]           // 5e69 ldrsh r1, [r5, r1]
ldrsh r2, [r5, r1]           // 5e6a ldrsh r2, [r5, r1]
ldrsh r3, [r5, r1]           // 5e6b ldrsh r3, [r5, r1]
ldrsh r4, [r5, r1]           // 5e6c ldrsh r4, [r5, r1]
ldrsh r5, [r5, r1]           // 5e6d ldrsh r5, [r5, r1]
ldrsh r6, [r5, r1]           // 5e6e ldrsh r6, [r5, r1]
ldrsh r7, [r5, r1]           // 5e6f ldrsh r7, [r5, r1]
ldrsh r0, [r6, r1]           // 5e70 ldrsh r0, [r6, r1]
ldrsh r1, [r6, r1]           // 5e71 ldrsh r1, [r6, r1]
ldrsh r2, [r6, r1]           // 5e72 ldrsh r2, [r6, r1]
ldrsh r3, [r6, r1]           // 5e73 ldrsh r3, [r6, r1]
ldrsh r4, [r6, r1]           // 5e74 ldrsh r4, [r6, r1]
ldrsh r5, [r6, r1]           // 5e75 ldrsh r5, [r6, r1]
ldrsh r6, [r6, r1]           // 5e76 ldrsh r6, [r6, r1]
ldrsh r7, [r6, r1]           // 5e77 ldrsh r7, [r6, r1]
ldrsh r0, [r7, r1]           // 5e78 ldrsh r0, [r7, r1]
ldrsh r1, [r7, r1]           // 5e79 ldrsh r1, [r7, r1]
ldrsh r2, [r7, r1]           // 5e7a ldrsh r2, [r7, r1]
ldrsh r3, [r7, r1]           // 5e7b ldrsh r3, [r7, r1]
ldrsh r4, [r7, r1]           // 5e7c ldrsh r4, [r7, r1]
ldrsh r5, [r7, r1]           // 5e7d ldrsh r5, [r7, r1]
ldrsh r6, [r7, r1]           // 5e7e ldrsh r6, [r7, r1]
ldrsh r7, [r7, r1]           // 5e7f ldrsh r7, [r7, r1]
ldrsh r0, [r0, r2]           // 5e80 ldrsh r0, [r0, r2]
ldrsh r1, [r0, r2]           // 5e81 ldrsh r1, [r0, r2]
ldrsh r2, [r0, r2]           // 5e82 ldrsh r2, [r0, r2]
ldrsh r3, [r0, r2]           // 5e83 ldrsh r3, [r0, r2]
ldrsh r4, [r0, r2]           // 5e84 ldrsh r4, [r0, r2]
ldrsh r5, [r0, r2]           // 5e85 ldrsh r5, [r0, r2]
ldrsh r6, [r0, r2]           // 5e86 ldrsh r6, [r0, r2]
ldrsh r7, [r0, r2]           // 5e87 ldrsh r7, [r0, r2]
ldrsh r0, [r1, r2]           // 5e88 ldrsh r0, [r1, r2]
ldrsh r1, [r1, r2]           // 5e89 ldrsh r1, [r1, r2]
ldrsh r2, [r1, r2]           // 5e8a ldrsh r2, [r1, r2]
ldrsh r3, [r1, r2]           // 5e8b ldrsh r3, [r1, r2]
ldrsh r4, [r1, r2]           // 5e8c ldrsh r4, [r1, r2]
ldrsh r5, [r1, r2]           // 5e8d ldrsh r5, [r1, r2]
ldrsh r6, [r1, r2]           // 5e8e ldrsh r6, [r1, r2]
ldrsh r7, [r1, r2]           // 5e8f ldrsh r7, [r1, r2]
ldrsh r0, [r2, r2]           // 5e90 ldrsh r0, [r2, r2]
ldrsh r1, [r2, r2]           // 5e91 ldrsh r1, [r2, r2]
ldrsh r2, [r2, r2]           // 5e92 ldrsh r2, [r2, r2]
ldrsh r3, [r2, r2]           // 5e93 ldrsh r3, [r2, r2]
ldrsh r4, [r2, r2]           // 5e94 ldrsh r4, [r2, r2]
ldrsh r5, [r2, r2]           // 5e95 ldrsh r5, [r2, r2]
ldrsh r6, [r2, r2]           // 5e96 ldrsh r6, [r2, r2]
ldrsh r7, [r2, r2]           // 5e97 ldrsh r7, [r2, r2]
ldrsh r0, [r3, r2]           // 5e98 ldrsh r0, [r3, r2]
ldrsh r1, [r3, r2]           // 5e99 ldrsh r1, [r3, r2]
ldrsh r2, [r3, r2]           // 5e9a ldrsh r2, [r3, r2]
ldrsh r3, [r3, r2]           // 5e9b ldrsh r3, [r3, r2]
ldrsh r4, [r3, r2]           // 5e9c ldrsh r4, [r3, r2]
ldrsh r5, [r3, r2]           // 5e9d ldrsh r5, [r3, r2]
ldrsh r6, [r3, r2]           // 5e9e ldrsh r6, [r3, r2]
ldrsh r7, [r3, r2]           // 5e9f ldrsh r7, [r3, r2]
ldrsh r0, [r4, r2]           // 5ea0 ldrsh r0, [r4, r2]
ldrsh r1, [r4, r2]           // 5ea1 ldrsh r1, [r4, r2]
ldrsh r2, [r4, r2]           // 5ea2 ldrsh r2, [r4, r2]
ldrsh r3, [r4, r2]           // 5ea3 ldrsh r3, [r4, r2]
ldrsh r4, [r4, r2]           // 5ea4 ldrsh r4, [r4, r2]
ldrsh r5, [r4, r2]           // 5ea5 ldrsh r5, [r4, r2]
ldrsh r6, [r4, r2]           // 5ea6 ldrsh r6, [r4, r2]
ldrsh r7, [r4, r2]           // 5ea7 ldrsh r7, [r4, r2]
ldrsh r0, [r5, r2]           // 5ea8 ldrsh r0, [r5, r2]
ldrsh r1, [r5, r2]           // 5ea9 ldrsh r1, [r5, r2]
ldrsh r2, [r5, r2]           // 5eaa ldrsh r2, [r5, r2]
ldrsh r3, [r5, r2]           // 5eab ldrsh r3, [r5, r2]
ldrsh r4, [r5, r2]           // 5eac ldrsh r4, [r5, r2]
ldrsh r5, [r5, r2]           // 5ead ldrsh r5, [r5, r2]
ldrsh r6, [r5, r2]           // 5eae ldrsh r6, [r5, r2]
ldrsh r7, [r5, r2]           // 5eaf ldrsh r7, [r5, r2]
ldrsh r0, [r6, r2]           // 5eb0 ldrsh r0, [r6, r2]
ldrsh r1, [r6, r2]           // 5eb1 ldrsh r1, [r6, r2]
ldrsh r2, [r6, r2]           // 5eb2 ldrsh r2, [r6, r2]
ldrsh r3, [r6, r2]           // 5eb3 ldrsh r3, [r6, r2]
ldrsh r4, [r6, r2]           // 5eb4 ldrsh r4, [r6, r2]
ldrsh r5, [r6, r2]           // 5eb5 ldrsh r5, [r6, r2]
ldrsh r6, [r6, r2]           // 5eb6 ldrsh r6, [r6, r2]
ldrsh r7, [r6, r2]           // 5eb7 ldrsh r7, [r6, r2]
ldrsh r0, [r7, r2]           // 5eb8 ldrsh r0, [r7, r2]
ldrsh r1, [r7, r2]           // 5eb9 ldrsh r1, [r7, r2]
ldrsh r2, [r7, r2]           // 5eba ldrsh r2, [r7, r2]
ldrsh r3, [r7, r2]           // 5ebb ldrsh r3, [r7, r2]
ldrsh r4, [r7, r2]           // 5ebc ldrsh r4, [r7, r2]
ldrsh r5, [r7, r2]           // 5ebd ldrsh r5, [r7, r2]
ldrsh r6, [r7, r2]           // 5ebe ldrsh r6, [r7, r2]
ldrsh r7, [r7, r2]           // 5ebf ldrsh r7, [r7, r2]
ldrsh r0, [r0, r3]           // 5ec0 ldrsh r0, [r0, r3]
ldrsh r1, [r0, r3]           // 5ec1 ldrsh r1, [r0, r3]
ldrsh r2, [r0, r3]           // 5ec2 ldrsh r2, [r0, r3]
ldrsh r3, [r0, r3]           // 5ec3 ldrsh r3, [r0, r3]
ldrsh r4, [r0, r3]           // 5ec4 ldrsh r4, [r0, r3]
ldrsh r5, [r0, r3]           // 5ec5 ldrsh r5, [r0, r3]
ldrsh r6, [r0, r3]           // 5ec6 ldrsh r6, [r0, r3]
ldrsh r7, [r0, r3]           // 5ec7 ldrsh r7, [r0, r3]
ldrsh r0, [r1, r3]           // 5ec8 ldrsh r0, [r1, r3]
ldrsh r1, [r1, r3]           // 5ec9 ldrsh r1, [r1, r3]
ldrsh r2, [r1, r3]           // 5eca ldrsh r2, [r1, r3]
ldrsh r3, [r1, r3]           // 5ecb ldrsh r3, [r1, r3]
ldrsh r4, [r1, r3]           // 5ecc ldrsh r4, [r1, r3]
ldrsh r5, [r1, r3]           // 5ecd ldrsh r5, [r1, r3]
ldrsh r6, [r1, r3]           // 5ece ldrsh r6, [r1, r3]
ldrsh r7, [r1, r3]           // 5ecf ldrsh r7, [r1, r3]
ldrsh r0, [r2, r3]           // 5ed0 ldrsh r0, [r2, r3]
ldrsh r1, [r2, r3]           // 5ed1 ldrsh r1, [r2, r3]
ldrsh r2, [r2, r3]           // 5ed2 ldrsh r2, [r2, r3]
ldrsh r3, [r2, r3]           // 5ed3 ldrsh r3, [r2, r3]
ldrsh r4, [r2, r3]           // 5ed4 ldrsh r4, [r2, r3]
ldrsh r5, [r2, r3]           // 5ed5 ldrsh r5, [r2, r3]
ldrsh r6, [r2, r3]           // 5ed6 ldrsh r6, [r2, r3]
ldrsh r7, [r2, r3]           // 5ed7 ldrsh r7, [r2, r3]
ldrsh r0, [r3, r3]           // 5ed8 ldrsh r0, [r3, r3]
ldrsh r1, [r3, r3]           // 5ed9 ldrsh r1, [r3, r3]
ldrsh r2, [r3, r3]           // 5eda ldrsh r2, [r3, r3]
ldrsh r3, [r3, r3]           // 5edb ldrsh r3, [r3, r3]
ldrsh r4, [r3, r3]           // 5edc ldrsh r4, [r3, r3]
ldrsh r5, [r3, r3]           // 5edd ldrsh r5, [r3, r3]
ldrsh r6, [r3, r3]           // 5ede ldrsh r6, [r3, r3]
ldrsh r7, [r3, r3]           // 5edf ldrsh r7, [r3, r3]
ldrsh r0, [r4, r3]           // 5ee0 ldrsh r0, [r4, r3]
ldrsh r1, [r4, r3]           // 5ee1 ldrsh r1, [r4, r3]
ldrsh r2, [r4, r3]           // 5ee2 ldrsh r2, [r4, r3]
ldrsh r3, [r4, r3]           // 5ee3 ldrsh r3, [r4, r3]
ldrsh r4, [r4, r3]           // 5ee4 ldrsh r4, [r4, r3]
ldrsh r5, [r4, r3]           // 5ee5 ldrsh r5, [r4, r3]
ldrsh r6, [r4, r3]           // 5ee6 ldrsh r6, [r4, r3]
ldrsh r7, [r4, r3]           // 5ee7 ldrsh r7, [r4, r3]
ldrsh r0, [r5, r3]           // 5ee8 ldrsh r0, [r5, r3]
ldrsh r1, [r5, r3]           // 5ee9 ldrsh r1, [r5, r3]
ldrsh r2, [r5, r3]           // 5eea ldrsh r2, [r5, r3]
ldrsh r3, [r5, r3]           // 5eeb ldrsh r3, [r5, r3]
ldrsh r4, [r5, r3]           // 5eec ldrsh r4, [r5, r3]
ldrsh r5, [r5, r3]           // 5eed ldrsh r5, [r5, r3]
ldrsh r6, [r5, r3]           // 5eee ldrsh r6, [r5, r3]
ldrsh r7, [r5, r3]           // 5eef ldrsh r7, [r5, r3]
ldrsh r0, [r6, r3]           // 5ef0 ldrsh r0, [r6, r3]
ldrsh r1, [r6, r3]           // 5ef1 ldrsh r1, [r6, r3]
ldrsh r2, [r6, r3]           // 5ef2 ldrsh r2, [r6, r3]
ldrsh r3, [r6, r3]           // 5ef3 ldrsh r3, [r6, r3]
ldrsh r4, [r6, r3]           // 5ef4 ldrsh r4, [r6, r3]
ldrsh r5, [r6, r3]           // 5ef5 ldrsh r5, [r6, r3]
ldrsh r6, [r6, r3]           // 5ef6 ldrsh r6, [r6, r3]
ldrsh r7, [r6, r3]           // 5ef7 ldrsh r7, [r6, r3]
ldrsh r0, [r7, r3]           // 5ef8 ldrsh r0, [r7, r3]
ldrsh r1, [r7, r3]           // 5ef9 ldrsh r1, [r7, r3]
ldrsh r2, [r7, r3]           // 5efa ldrsh r2, [r7, r3]
ldrsh r3, [r7, r3]           // 5efb ldrsh r3, [r7, r3]
ldrsh r4, [r7, r3]           // 5efc ldrsh r4, [r7, r3]
ldrsh r5, [r7, r3]           // 5efd ldrsh r5, [r7, r3]
ldrsh r6, [r7, r3]           // 5efe ldrsh r6, [r7, r3]
ldrsh r7, [r7, r3]           // 5eff ldrsh r7, [r7, r3]
ldrsh r0, [r0, r4]           // 5f00 ldrsh r0, [r0, r4]
ldrsh r1, [r0, r4]           // 5f01 ldrsh r1, [r0, r4]
ldrsh r2, [r0, r4]           // 5f02 ldrsh r2, [r0, r4]
ldrsh r3, [r0, r4]           // 5f03 ldrsh r3, [r0, r4]
ldrsh r4, [r0, r4]           // 5f04 ldrsh r4, [r0, r4]
ldrsh r5, [r0, r4]           // 5f05 ldrsh r5, [r0, r4]
ldrsh r6, [r0, r4]           // 5f06 ldrsh r6, [r0, r4]
ldrsh r7, [r0, r4]           // 5f07 ldrsh r7, [r0, r4]
ldrsh r0, [r1, r4]           // 5f08 ldrsh r0, [r1, r4]
ldrsh r1, [r1, r4]           // 5f09 ldrsh r1, [r1, r4]
ldrsh r2, [r1, r4]           // 5f0a ldrsh r2, [r1, r4]
ldrsh r3, [r1, r4]           // 5f0b ldrsh r3, [r1, r4]
ldrsh r4, [r1, r4]           // 5f0c ldrsh r4, [r1, r4]
ldrsh r5, [r1, r4]           // 5f0d ldrsh r5, [r1, r4]
ldrsh r6, [r1, r4]           // 5f0e ldrsh r6, [r1, r4]
ldrsh r7, [r1, r4]           // 5f0f ldrsh r7, [r1, r4]
ldrsh r0, [r2, r4]           // 5f10 ldrsh r0, [r2, r4]
ldrsh r1, [r2, r4]           // 5f11 ldrsh r1, [r2, r4]
ldrsh r2, [r2, r4]           // 5f12 ldrsh r2, [r2, r4]
ldrsh r3, [r2, r4]           // 5f13 ldrsh r3, [r2, r4]
ldrsh r4, [r2, r4]           // 5f14 ldrsh r4, [r2, r4]
ldrsh r5, [r2, r4]           // 5f15 ldrsh r5, [r2, r4]
ldrsh r6, [r2, r4]           // 5f16 ldrsh r6, [r2, r4]
ldrsh r7, [r2, r4]           // 5f17 ldrsh r7, [r2, r4]
ldrsh r0, [r3, r4]           // 5f18 ldrsh r0, [r3, r4]
ldrsh r1, [r3, r4]           // 5f19 ldrsh r1, [r3, r4]
ldrsh r2, [r3, r4]           // 5f1a ldrsh r2, [r3, r4]
ldrsh r3, [r3, r4]           // 5f1b ldrsh r3, [r3, r4]
ldrsh r4, [r3, r4]           // 5f1c ldrsh r4, [r3, r4]
ldrsh r5, [r3, r4]           // 5f1d ldrsh r5, [r3, r4]
ldrsh r6, [r3, r4]           // 5f1e ldrsh r6, [r3, r4]
ldrsh r7, [r3, r4]           // 5f1f ldrsh r7, [r3, r4]
ldrsh r0, [r4, r4]           // 5f20 ldrsh r0, [r4, r4]
ldrsh r1, [r4, r4]           // 5f21 ldrsh r1, [r4, r4]
ldrsh r2, [r4, r4]           // 5f22 ldrsh r2, [r4, r4]
ldrsh r3, [r4, r4]           // 5f23 ldrsh r3, [r4, r4]
ldrsh r4, [r4, r4]           // 5f24 ldrsh r4, [r4, r4]
ldrsh r5, [r4, r4]           // 5f25 ldrsh r5, [r4, r4]
ldrsh r6, [r4, r4]           // 5f26 ldrsh r6, [r4, r4]
ldrsh r7, [r4, r4]           // 5f27 ldrsh r7, [r4, r4]
ldrsh r0, [r5, r4]           // 5f28 ldrsh r0, [r5, r4]
ldrsh r1, [r5, r4]           // 5f29 ldrsh r1, [r5, r4]
ldrsh r2, [r5, r4]           // 5f2a ldrsh r2, [r5, r4]
ldrsh r3, [r5, r4]           // 5f2b ldrsh r3, [r5, r4]
ldrsh r4, [r5, r4]           // 5f2c ldrsh r4, [r5, r4]
ldrsh r5, [r5, r4]           // 5f2d ldrsh r5, [r5, r4]
ldrsh r6, [r5, r4]           // 5f2e ldrsh r6, [r5, r4]
ldrsh r7, [r5, r4]           // 5f2f ldrsh r7, [r5, r4]
ldrsh r0, [r6, r4]           // 5f30 ldrsh r0, [r6, r4]
ldrsh r1, [r6, r4]           // 5f31 ldrsh r1, [r6, r4]
ldrsh r2, [r6, r4]           // 5f32 ldrsh r2, [r6, r4]
ldrsh r3, [r6, r4]           // 5f33 ldrsh r3, [r6, r4]
ldrsh r4, [r6, r4]           // 5f34 ldrsh r4, [r6, r4]
ldrsh r5, [r6, r4]           // 5f35 ldrsh r5, [r6, r4]
ldrsh r6, [r6, r4]           // 5f36 ldrsh r6, [r6, r4]
ldrsh r7, [r6, r4]           // 5f37 ldrsh r7, [r6, r4]
ldrsh r0, [r7, r4]           // 5f38 ldrsh r0, [r7, r4]
ldrsh r1, [r7, r4]           // 5f39 ldrsh r1, [r7, r4]
ldrsh r2, [r7, r4]           // 5f3a ldrsh r2, [r7, r4]
ldrsh r3, [r7, r4]           // 5f3b ldrsh r3, [r7, r4]
ldrsh r4, [r7, r4]           // 5f3c ldrsh r4, [r7, r4]
ldrsh r5, [r7, r4]           // 5f3d ldrsh r5, [r7, r4]
ldrsh r6, [r7, r4]           // 5f3e ldrsh r6, [r7, r4]
ldrsh r7, [r7, r4]           // 5f3f ldrsh r7, [r7, r4]
ldrsh r0, [r0, r5]           // 5f40 ldrsh r0, [r0, r5]
ldrsh r1, [r0, r5]           // 5f41 ldrsh r1, [r0, r5]
ldrsh r2, [r0, r5]           // 5f42 ldrsh r2, [r0, r5]
ldrsh r3, [r0, r5]           // 5f43 ldrsh r3, [r0, r5]
ldrsh r4, [r0, r5]           // 5f44 ldrsh r4, [r0, r5]
ldrsh r5, [r0, r5]           // 5f45 ldrsh r5, [r0, r5]
ldrsh r6, [r0, r5]           // 5f46 ldrsh r6, [r0, r5]
ldrsh r7, [r0, r5]           // 5f47 ldrsh r7, [r0, r5]
ldrsh r0, [r1, r5]           // 5f48 ldrsh r0, [r1, r5]
ldrsh r1, [r1, r5]           // 5f49 ldrsh r1, [r1, r5]
ldrsh r2, [r1, r5]           // 5f4a ldrsh r2, [r1, r5]
ldrsh r3, [r1, r5]           // 5f4b ldrsh r3, [r1, r5]
ldrsh r4, [r1, r5]           // 5f4c ldrsh r4, [r1, r5]
ldrsh r5, [r1, r5]           // 5f4d ldrsh r5, [r1, r5]
ldrsh r6, [r1, r5]           // 5f4e ldrsh r6, [r1, r5]
ldrsh r7, [r1, r5]           // 5f4f ldrsh r7, [r1, r5]
ldrsh r0, [r2, r5]           // 5f50 ldrsh r0, [r2, r5]
ldrsh r1, [r2, r5]           // 5f51 ldrsh r1, [r2, r5]
ldrsh r2, [r2, r5]           // 5f52 ldrsh r2, [r2, r5]
ldrsh r3, [r2, r5]           // 5f53 ldrsh r3, [r2, r5]
ldrsh r4, [r2, r5]           // 5f54 ldrsh r4, [r2, r5]
ldrsh r5, [r2, r5]           // 5f55 ldrsh r5, [r2, r5]
ldrsh r6, [r2, r5]           // 5f56 ldrsh r6, [r2, r5]
ldrsh r7, [r2, r5]           // 5f57 ldrsh r7, [r2, r5]
ldrsh r0, [r3, r5]           // 5f58 ldrsh r0, [r3, r5]
ldrsh r1, [r3, r5]           // 5f59 ldrsh r1, [r3, r5]
ldrsh r2, [r3, r5]           // 5f5a ldrsh r2, [r3, r5]
ldrsh r3, [r3, r5]           // 5f5b ldrsh r3, [r3, r5]
ldrsh r4, [r3, r5]           // 5f5c ldrsh r4, [r3, r5]
ldrsh r5, [r3, r5]           // 5f5d ldrsh r5, [r3, r5]
ldrsh r6, [r3, r5]           // 5f5e ldrsh r6, [r3, r5]
ldrsh r7, [r3, r5]           // 5f5f ldrsh r7, [r3, r5]
ldrsh r0, [r4, r5]           // 5f60 ldrsh r0, [r4, r5]
ldrsh r1, [r4, r5]           // 5f61 ldrsh r1, [r4, r5]
ldrsh r2, [r4, r5]           // 5f62 ldrsh r2, [r4, r5]
ldrsh r3, [r4, r5]           // 5f63 ldrsh r3, [r4, r5]
ldrsh r4, [r4, r5]           // 5f64 ldrsh r4, [r4, r5]
ldrsh r5, [r4, r5]           // 5f65 ldrsh r5, [r4, r5]
ldrsh r6, [r4, r5]           // 5f66 ldrsh r6, [r4, r5]
ldrsh r7, [r4, r5]           // 5f67 ldrsh r7, [r4, r5]
ldrsh r0, [r5, r5]           // 5f68 ldrsh r0, [r5, r5]
ldrsh r1, [r5, r5]           // 5f69 ldrsh r1, [r5, r5]
ldrsh r2, [r5, r5]           // 5f6a ldrsh r2, [r5, r5]
ldrsh r3, [r5, r5]           // 5f6b ldrsh r3, [r5, r5]
ldrsh r4, [r5, r5]           // 5f6c ldrsh r4, [r5, r5]
ldrsh r5, [r5, r5]           // 5f6d ldrsh r5, [r5, r5]
ldrsh r6, [r5, r5]           // 5f6e ldrsh r6, [r5, r5]
ldrsh r7, [r5, r5]           // 5f6f ldrsh r7, [r5, r5]
ldrsh r0, [r6, r5]           // 5f70 ldrsh r0, [r6, r5]
ldrsh r1, [r6, r5]           // 5f71 ldrsh r1, [r6, r5]
ldrsh r2, [r6, r5]           // 5f72 ldrsh r2, [r6, r5]
ldrsh r3, [r6, r5]           // 5f73 ldrsh r3, [r6, r5]
ldrsh r4, [r6, r5]           // 5f74 ldrsh r4, [r6, r5]
ldrsh r5, [r6, r5]           // 5f75 ldrsh r5, [r6, r5]
ldrsh r6, [r6, r5]           // 5f76 ldrsh r6, [r6, r5]
ldrsh r7, [r6, r5]           // 5f77 ldrsh r7, [r6, r5]
ldrsh r0, [r7, r5]           // 5f78 ldrsh r0, [r7, r5]
ldrsh r1, [r7, r5]           // 5f79 ldrsh r1, [r7, r5]
ldrsh r2, [r7, r5]           // 5f7a ldrsh r2, [r7, r5]
ldrsh r3, [r7, r5]           // 5f7b ldrsh r3, [r7, r5]
ldrsh r4, [r7, r5]           // 5f7c ldrsh r4, [r7, r5]
ldrsh r5, [r7, r5]           // 5f7d ldrsh r5, [r7, r5]
ldrsh r6, [r7, r5]           // 5f7e ldrsh r6, [r7, r5]
ldrsh r7, [r7, r5]           // 5f7f ldrsh r7, [r7, r5]
ldrsh r0, [r0, r6]           // 5f80 ldrsh r0, [r0, r6]
ldrsh r1, [r0, r6]           // 5f81 ldrsh r1, [r0, r6]
ldrsh r2, [r0, r6]           // 5f82 ldrsh r2, [r0, r6]
ldrsh r3, [r0, r6]           // 5f83 ldrsh r3, [r0, r6]
ldrsh r4, [r0, r6]           // 5f84 ldrsh r4, [r0, r6]
ldrsh r5, [r0, r6]           // 5f85 ldrsh r5, [r0, r6]
ldrsh r6, [r0, r6]           // 5f86 ldrsh r6, [r0, r6]
ldrsh r7, [r0, r6]           // 5f87 ldrsh r7, [r0, r6]
ldrsh r0, [r1, r6]           // 5f88 ldrsh r0, [r1, r6]
ldrsh r1, [r1, r6]           // 5f89 ldrsh r1, [r1, r6]
ldrsh r2, [r1, r6]           // 5f8a ldrsh r2, [r1, r6]
ldrsh r3, [r1, r6]           // 5f8b ldrsh r3, [r1, r6]
ldrsh r4, [r1, r6]           // 5f8c ldrsh r4, [r1, r6]
ldrsh r5, [r1, r6]           // 5f8d ldrsh r5, [r1, r6]
ldrsh r6, [r1, r6]           // 5f8e ldrsh r6, [r1, r6]
ldrsh r7, [r1, r6]           // 5f8f ldrsh r7, [r1, r6]
ldrsh r0, [r2, r6]           // 5f90 ldrsh r0, [r2, r6]
ldrsh r1, [r2, r6]           // 5f91 ldrsh r1, [r2, r6]
ldrsh r2, [r2, r6]           // 5f92 ldrsh r2, [r2, r6]
ldrsh r3, [r2, r6]           // 5f93 ldrsh r3, [r2, r6]
ldrsh r4, [r2, r6]           // 5f94 ldrsh r4, [r2, r6]
ldrsh r5, [r2, r6]           // 5f95 ldrsh r5, [r2, r6]
ldrsh r6, [r2, r6]           // 5f96 ldrsh r6, [r2, r6]
ldrsh r7, [r2, r6]           // 5f97 ldrsh r7, [r2, r6]
ldrsh r0, [r3, r6]           // 5f98 ldrsh r0, [r3, r6]
ldrsh r1, [r3, r6]           // 5f99 ldrsh r1, [r3, r6]
ldrsh r2, [r3, r6]           // 5f9a ldrsh r2, [r3, r6]
ldrsh r3, [r3, r6]           // 5f9b ldrsh r3, [r3, r6]
ldrsh r4, [r3, r6]           // 5f9c ldrsh r4, [r3, r6]
ldrsh r5, [r3, r6]           // 5f9d ldrsh r5, [r3, r6]
ldrsh r6, [r3, r6]           // 5f9e ldrsh r6, [r3, r6]
ldrsh r7, [r3, r6]           // 5f9f ldrsh r7, [r3, r6]
ldrsh r0, [r4, r6]           // 5fa0 ldrsh r0, [r4, r6]
ldrsh r1, [r4, r6]           // 5fa1 ldrsh r1, [r4, r6]
ldrsh r2, [r4, r6]           // 5fa2 ldrsh r2, [r4, r6]
ldrsh r3, [r4, r6]           // 5fa3 ldrsh r3, [r4, r6]
ldrsh r4, [r4, r6]           // 5fa4 ldrsh r4, [r4, r6]
ldrsh r5, [r4, r6]           // 5fa5 ldrsh r5, [r4, r6]
ldrsh r6, [r4, r6]           // 5fa6 ldrsh r6, [r4, r6]
ldrsh r7, [r4, r6]           // 5fa7 ldrsh r7, [r4, r6]
ldrsh r0, [r5, r6]           // 5fa8 ldrsh r0, [r5, r6]
ldrsh r1, [r5, r6]           // 5fa9 ldrsh r1, [r5, r6]
ldrsh r2, [r5, r6]           // 5faa ldrsh r2, [r5, r6]
ldrsh r3, [r5, r6]           // 5fab ldrsh r3, [r5, r6]
ldrsh r4, [r5, r6]           // 5fac ldrsh r4, [r5, r6]
ldrsh r5, [r5, r6]           // 5fad ldrsh r5, [r5, r6]
ldrsh r6, [r5, r6]           // 5fae ldrsh r6, [r5, r6]
ldrsh r7, [r5, r6]           // 5faf ldrsh r7, [r5, r6]
ldrsh r0, [r6, r6]           // 5fb0 ldrsh r0, [r6, r6]
ldrsh r1, [r6, r6]           // 5fb1 ldrsh r1, [r6, r6]
ldrsh r2, [r6, r6]           // 5fb2 ldrsh r2, [r6, r6]
ldrsh r3, [r6, r6]           // 5fb3 ldrsh r3, [r6, r6]
ldrsh r4, [r6, r6]           // 5fb4 ldrsh r4, [r6, r6]
ldrsh r5, [r6, r6]           // 5fb5 ldrsh r5, [r6, r6]
ldrsh r6, [r6, r6]           // 5fb6 ldrsh r6, [r6, r6]
ldrsh r7, [r6, r6]           // 5fb7 ldrsh r7, [r6, r6]
ldrsh r0, [r7, r6]           // 5fb8 ldrsh r0, [r7, r6]
ldrsh r1, [r7, r6]           // 5fb9 ldrsh r1, [r7, r6]
ldrsh r2, [r7, r6]           // 5fba ldrsh r2, [r7, r6]
ldrsh r3, [r7, r6]           // 5fbb ldrsh r3, [r7, r6]
ldrsh r4, [r7, r6]           // 5fbc ldrsh r4, [r7, r6]
ldrsh r5, [r7, r6]           // 5fbd ldrsh r5, [r7, r6]
ldrsh r6, [r7, r6]           // 5fbe ldrsh r6, [r7, r6]
ldrsh r7, [r7, r6]           // 5fbf ldrsh r7, [r7, r6]
ldrsh r0, [r0, r7]           // 5fc0 ldrsh r0, [r0, r7]
ldrsh r1, [r0, r7]           // 5fc1 ldrsh r1, [r0, r7]
ldrsh r2, [r0, r7]           // 5fc2 ldrsh r2, [r0, r7]
ldrsh r3, [r0, r7]           // 5fc3 ldrsh r3, [r0, r7]
ldrsh r4, [r0, r7]           // 5fc4 ldrsh r4, [r0, r7]
ldrsh r5, [r0, r7]           // 5fc5 ldrsh r5, [r0, r7]
ldrsh r6, [r0, r7]           // 5fc6 ldrsh r6, [r0, r7]
ldrsh r7, [r0, r7]           // 5fc7 ldrsh r7, [r0, r7]
ldrsh r0, [r1, r7]           // 5fc8 ldrsh r0, [r1, r7]
ldrsh r1, [r1, r7]           // 5fc9 ldrsh r1, [r1, r7]
ldrsh r2, [r1, r7]           // 5fca ldrsh r2, [r1, r7]
ldrsh r3, [r1, r7]           // 5fcb ldrsh r3, [r1, r7]
ldrsh r4, [r1, r7]           // 5fcc ldrsh r4, [r1, r7]
ldrsh r5, [r1, r7]           // 5fcd ldrsh r5, [r1, r7]
ldrsh r6, [r1, r7]           // 5fce ldrsh r6, [r1, r7]
ldrsh r7, [r1, r7]           // 5fcf ldrsh r7, [r1, r7]
ldrsh r0, [r2, r7]           // 5fd0 ldrsh r0, [r2, r7]
ldrsh r1, [r2, r7]           // 5fd1 ldrsh r1, [r2, r7]
ldrsh r2, [r2, r7]           // 5fd2 ldrsh r2, [r2, r7]
ldrsh r3, [r2, r7]           // 5fd3 ldrsh r3, [r2, r7]
ldrsh r4, [r2, r7]           // 5fd4 ldrsh r4, [r2, r7]
ldrsh r5, [r2, r7]           // 5fd5 ldrsh r5, [r2, r7]
ldrsh r6, [r2, r7]           // 5fd6 ldrsh r6, [r2, r7]
ldrsh r7, [r2, r7]           // 5fd7 ldrsh r7, [r2, r7]
ldrsh r0, [r3, r7]           // 5fd8 ldrsh r0, [r3, r7]
ldrsh r1, [r3, r7]           // 5fd9 ldrsh r1, [r3, r7]
ldrsh r2, [r3, r7]           // 5fda ldrsh r2, [r3, r7]
ldrsh r3, [r3, r7]           // 5fdb ldrsh r3, [r3, r7]
ldrsh r4, [r3, r7]           // 5fdc ldrsh r4, [r3, r7]
ldrsh r5, [r3, r7]           // 5fdd ldrsh r5, [r3, r7]
ldrsh r6, [r3, r7]           // 5fde ldrsh r6, [r3, r7]
ldrsh r7, [r3, r7]           // 5fdf ldrsh r7, [r3, r7]
ldrsh r0, [r4, r7]           // 5fe0 ldrsh r0, [r4, r7]
ldrsh r1, [r4, r7]           // 5fe1 ldrsh r1, [r4, r7]
ldrsh r2, [r4, r7]           // 5fe2 ldrsh r2, [r4, r7]
ldrsh r3, [r4, r7]           // 5fe3 ldrsh r3, [r4, r7]
ldrsh r4, [r4, r7]           // 5fe4 ldrsh r4, [r4, r7]
ldrsh r5, [r4, r7]           // 5fe5 ldrsh r5, [r4, r7]
ldrsh r6, [r4, r7]           // 5fe6 ldrsh r6, [r4, r7]
ldrsh r7, [r4, r7]           // 5fe7 ldrsh r7, [r4, r7]
ldrsh r0, [r5, r7]           // 5fe8 ldrsh r0, [r5, r7]
ldrsh r1, [r5, r7]           // 5fe9 ldrsh r1, [r5, r7]
ldrsh r2, [r5, r7]           // 5fea ldrsh r2, [r5, r7]
ldrsh r3, [r5, r7]           // 5feb ldrsh r3, [r5, r7]
ldrsh r4, [r5, r7]           // 5fec ldrsh r4, [r5, r7]
ldrsh r5, [r5, r7]           // 5fed ldrsh r5, [r5, r7]
ldrsh r6, [r5, r7]           // 5fee ldrsh r6, [r5, r7]
ldrsh r7, [r5, r7]           // 5fef ldrsh r7, [r5, r7]
ldrsh r0, [r6, r7]           // 5ff0 ldrsh r0, [r6, r7]
ldrsh r1, [r6, r7]           // 5ff1 ldrsh r1, [r6, r7]
ldrsh r2, [r6, r7]           // 5ff2 ldrsh r2, [r6, r7]
ldrsh r3, [r6, r7]           // 5ff3 ldrsh r3, [r6, r7]
ldrsh r4, [r6, r7]           // 5ff4 ldrsh r4, [r6, r7]
ldrsh r5, [r6, r7]           // 5ff5 ldrsh r5, [r6, r7]
ldrsh r6, [r6, r7]           // 5ff6 ldrsh r6, [r6, r7]
ldrsh r7, [r6, r7]           // 5ff7 ldrsh r7, [r6, r7]
ldrsh r0, [r7, r7]           // 5ff8 ldrsh r0, [r7, r7]
ldrsh r1, [r7, r7]           // 5ff9 ldrsh r1, [r7, r7]
ldrsh r2, [r7, r7]           // 5ffa ldrsh r2, [r7, r7]
ldrsh r3, [r7, r7]           // 5ffb ldrsh r3, [r7, r7]
ldrsh r4, [r7, r7]           // 5ffc ldrsh r4, [r7, r7]
ldrsh r5, [r7, r7]           // 5ffd ldrsh r5, [r7, r7]
ldrsh r6, [r7, r7]           // 5ffe ldrsh r6, [r7, r7]
ldrsh r7, [r7, r7]           // 5fff ldrsh r7, [r7, r7]

str r0, [r0, #0]             // 6000 str r0, [r0, #0]
str r1, [r0, #0]             // 6001 str r1, [r0, #0]
str r2, [r0, #0]             // 6002 str r2, [r0, #0]
str r3, [r0, #0]             // 6003 str r3, [r0, #0]
str r4, [r0, #0]             // 6004 str r4, [r0, #0]
str r5, [r0, #0]             // 6005 str r5, [r0, #0]
str r6, [r0, #0]             // 6006 str r6, [r0, #0]
str r7, [r0, #0]             // 6007 str r7, [r0, #0]
str r0, [r1, #0]             // 6008 str r0, [r1, #0]
str r1, [r1, #0]             // 6009 str r1, [r1, #0]
str r2, [r1, #0]             // 600a str r2, [r1, #0]
str r3, [r1, #0]             // 600b str r3, [r1, #0]
str r4, [r1, #0]             // 600c str r4, [r1, #0]
str r5, [r1, #0]             // 600d str r5, [r1, #0]
str r6, [r1, #0]             // 600e str r6, [r1, #0]
str r7, [r1, #0]             // 600f str r7, [r1, #0]
str r0, [r2, #0]             // 6010 str r0, [r2, #0]
str r1, [r2, #0]             // 6011 str r1, [r2, #0]
str r2, [r2, #0]             // 6012 str r2, [r2, #0]
str r3, [r2, #0]             // 6013 str r3, [r2, #0]
str r4, [r2, #0]             // 6014 str r4, [r2, #0]
str r5, [r2, #0]             // 6015 str r5, [r2, #0]
str r6, [r2, #0]             // 6016 str r6, [r2, #0]
str r7, [r2, #0]             // 6017 str r7, [r2, #0]
str r0, [r3, #0]             // 6018 str r0, [r3, #0]
str r1, [r3, #0]             // 6019 str r1, [r3, #0]
str r2, [r3, #0]             // 601a str r2, [r3, #0]
str r3, [r3, #0]             // 601b str r3, [r3, #0]
str r4, [r3, #0]             // 601c str r4, [r3, #0]
str r5, [r3, #0]             // 601d str r5, [r3, #0]
str r6, [r3, #0]             // 601e str r6, [r3, #0]
str r7, [r3, #0]             // 601f str r7, [r3, #0]
str r0, [r4, #0]             // 6020 str r0, [r4, #0]
str r1, [r4, #0]             // 6021 str r1, [r4, #0]
str r2, [r4, #0]             // 6022 str r2, [r4, #0]
str r3, [r4, #0]             // 6023 str r3, [r4, #0]
str r4, [r4, #0]             // 6024 str r4, [r4, #0]
str r5, [r4, #0]             // 6025 str r5, [r4, #0]
str r6, [r4, #0]             // 6026 str r6, [r4, #0]
str r7, [r4, #0]             // 6027 str r7, [r4, #0]
str r0, [r5, #0]             // 6028 str r0, [r5, #0]
str r1, [r5, #0]             // 6029 str r1, [r5, #0]
str r2, [r5, #0]             // 602a str r2, [r5, #0]
str r3, [r5, #0]             // 602b str r3, [r5, #0]
str r4, [r5, #0]             // 602c str r4, [r5, #0]
str r5, [r5, #0]             // 602d str r5, [r5, #0]
str r6, [r5, #0]             // 602e str r6, [r5, #0]
str r7, [r5, #0]             // 602f str r7, [r5, #0]
str r0, [r6, #0]             // 6030 str r0, [r6, #0]
str r1, [r6, #0]             // 6031 str r1, [r6, #0]
str r2, [r6, #0]             // 6032 str r2, [r6, #0]
str r3, [r6, #0]             // 6033 str r3, [r6, #0]
str r4, [r6, #0]             // 6034 str r4, [r6, #0]
str r5, [r6, #0]             // 6035 str r5, [r6, #0]
str r6, [r6, #0]             // 6036 str r6, [r6, #0]
str r7, [r6, #0]             // 6037 str r7, [r6, #0]
str r0, [r7, #0]             // 6038 str r0, [r7, #0]
str r1, [r7, #0]             // 6039 str r1, [r7, #0]
str r2, [r7, #0]             // 603a str r2, [r7, #0]
str r3, [r7, #0]             // 603b str r3, [r7, #0]
str r4, [r7, #0]             // 603c str r4, [r7, #0]
str r5, [r7, #0]             // 603d str r5, [r7, #0]
str r6, [r7, #0]             // 603e str r6, [r7, #0]
str r7, [r7, #0]             // 603f str r7, [r7, #0]
str r0, [r0, #4]             // 6040 str r0, [r0, #4]
str r1, [r0, #4]             // 6041 str r1, [r0, #4]
str r2, [r0, #4]             // 6042 str r2, [r0, #4]
str r3, [r0, #4]             // 6043 str r3, [r0, #4]
str r4, [r0, #4]             // 6044 str r4, [r0, #4]
str r5, [r0, #4]             // 6045 str r5, [r0, #4]
str r6, [r0, #4]             // 6046 str r6, [r0, #4]
str r7, [r0, #4]             // 6047 str r7, [r0, #4]
str r0, [r1, #4]             // 6048 str r0, [r1, #4]
str r1, [r1, #4]             // 6049 str r1, [r1, #4]
str r2, [r1, #4]             // 604a str r2, [r1, #4]
str r3, [r1, #4]             // 604b str r3, [r1, #4]
str r4, [r1, #4]             // 604c str r4, [r1, #4]
str r5, [r1, #4]             // 604d str r5, [r1, #4]
str r6, [r1, #4]             // 604e str r6, [r1, #4]
str r7, [r1, #4]             // 604f str r7, [r1, #4]
str r0, [r2, #4]             // 6050 str r0, [r2, #4]
str r1, [r2, #4]             // 6051 str r1, [r2, #4]
str r2, [r2, #4]             // 6052 str r2, [r2, #4]
str r3, [r2, #4]             // 6053 str r3, [r2, #4]
str r4, [r2, #4]             // 6054 str r4, [r2, #4]
str r5, [r2, #4]             // 6055 str r5, [r2, #4]
str r6, [r2, #4]             // 6056 str r6, [r2, #4]
str r7, [r2, #4]             // 6057 str r7, [r2, #4]
str r0, [r3, #4]             // 6058 str r0, [r3, #4]
str r1, [r3, #4]             // 6059 str r1, [r3, #4]
str r2, [r3, #4]             // 605a str r2, [r3, #4]
str r3, [r3, #4]             // 605b str r3, [r3, #4]
str r4, [r3, #4]             // 605c str r4, [r3, #4]
str r5, [r3, #4]             // 605d str r5, [r3, #4]
str r6, [r3, #4]             // 605e str r6, [r3, #4]
str r7, [r3, #4]             // 605f str r7, [r3, #4]
str r0, [r4, #4]             // 6060 str r0, [r4, #4]
str r1, [r4, #4]             // 6061 str r1, [r4, #4]
str r2, [r4, #4]             // 6062 str r2, [r4, #4]
str r3, [r4, #4]             // 6063 str r3, [r4, #4]
str r4, [r4, #4]             // 6064 str r4, [r4, #4]
str r5, [r4, #4]             // 6065 str r5, [r4, #4]
str r6, [r4, #4]             // 6066 str r6, [r4, #4]
str r7, [r4, #4]             // 6067 str r7, [r4, #4]
str r0, [r5, #4]             // 6068 str r0, [r5, #4]
str r1, [r5, #4]             // 6069 str r1, [r5, #4]
str r2, [r5, #4]             // 606a str r2, [r5, #4]
str r3, [r5, #4]             // 606b str r3, [r5, #4]
str r4, [r5, #4]             // 606c str r4, [r5, #4]
str r5, [r5, #4]             // 606d str r5, [r5, #4]
str r6, [r5, #4]             // 606e str r6, [r5, #4]
str r7, [r5, #4]             // 606f str r7, [r5, #4]
str r0, [r6, #4]             // 6070 str r0, [r6, #4]
str r1, [r6, #4]             // 6071 str r1, [r6, #4]
str r2, [r6, #4]             // 6072 str r2, [r6, #4]
str r3, [r6, #4]             // 6073 str r3, [r6, #4]
str r4, [r6, #4]             // 6074 str r4, [r6, #4]
str r5, [r6, #4]             // 6075 str r5, [r6, #4]
str r6, [r6, #4]             // 6076 str r6, [r6, #4]
str r7, [r6, #4]             // 6077 str r7, [r6, #4]
str r0, [r7, #4]             // 6078 str r0, [r7, #4]
str r1, [r7, #4]             // 6079 str r1, [r7, #4]
str r2, [r7, #4]             // 607a str r2, [r7, #4]
str r3, [r7, #4]             // 607b str r3, [r7, #4]
str r4, [r7, #4]             // 607c str r4, [r7, #4]
str r5, [r7, #4]             // 607d str r5, [r7, #4]
str r6, [r7, #4]             // 607e str r6, [r7, #4]
str r7, [r7, #4]             // 607f str r7, [r7, #4]
str r0, [r0, #124] // 0x7c    // 67c0 str r0, [r0, #124] // 0x7c
str r1, [r0, #124] // 0x7c    // 67c1 str r1, [r0, #124] // 0x7c
str r2, [r0, #124] // 0x7c    // 67c2 str r2, [r0, #124] // 0x7c
str r3, [r0, #124] // 0x7c    // 67c3 str r3, [r0, #124] // 0x7c
str r4, [r0, #124] // 0x7c    // 67c4 str r4, [r0, #124] // 0x7c
str r5, [r0, #124] // 0x7c    // 67c5 str r5, [r0, #124] // 0x7c
str r6, [r0, #124] // 0x7c    // 67c6 str r6, [r0, #124] // 0x7c
str r7, [r0, #124] // 0x7c    // 67c7 str r7, [r0, #124] // 0x7c
str r0, [r1, #124] // 0x7c    // 67c8 str r0, [r1, #124] // 0x7c
str r1, [r1, #124] // 0x7c    // 67c9 str r1, [r1, #124] // 0x7c
str r2, [r1, #124] // 0x7c    // 67ca str r2, [r1, #124] // 0x7c
str r3, [r1, #124] // 0x7c    // 67cb str r3, [r1, #124] // 0x7c
str r4, [r1, #124] // 0x7c    // 67cc str r4, [r1, #124] // 0x7c
str r5, [r1, #124] // 0x7c    // 67cd str r5, [r1, #124] // 0x7c
str r6, [r1, #124] // 0x7c    // 67ce str r6, [r1, #124] // 0x7c
str r7, [r1, #124] // 0x7c    // 67cf str r7, [r1, #124] // 0x7c
str r0, [r2, #124] // 0x7c    // 67d0 str r0, [r2, #124] // 0x7c
str r1, [r2, #124] // 0x7c    // 67d1 str r1, [r2, #124] // 0x7c
str r2, [r2, #124] // 0x7c    // 67d2 str r2, [r2, #124] // 0x7c
str r3, [r2, #124] // 0x7c    // 67d3 str r3, [r2, #124] // 0x7c
str r4, [r2, #124] // 0x7c    // 67d4 str r4, [r2, #124] // 0x7c
str r5, [r2, #124] // 0x7c    // 67d5 str r5, [r2, #124] // 0x7c
str r6, [r2, #124] // 0x7c    // 67d6 str r6, [r2, #124] // 0x7c
str r7, [r2, #124] // 0x7c    // 67d7 str r7, [r2, #124] // 0x7c
str r0, [r3, #124] // 0x7c    // 67d8 str r0, [r3, #124] // 0x7c
str r1, [r3, #124] // 0x7c    // 67d9 str r1, [r3, #124] // 0x7c
str r2, [r3, #124] // 0x7c    // 67da str r2, [r3, #124] // 0x7c
str r3, [r3, #124] // 0x7c    // 67db str r3, [r3, #124] // 0x7c
str r4, [r3, #124] // 0x7c    // 67dc str r4, [r3, #124] // 0x7c
str r5, [r3, #124] // 0x7c    // 67dd str r5, [r3, #124] // 0x7c
str r6, [r3, #124] // 0x7c    // 67de str r6, [r3, #124] // 0x7c
str r7, [r3, #124] // 0x7c    // 67df str r7, [r3, #124] // 0x7c
str r0, [r4, #124] // 0x7c    // 67e0 str r0, [r4, #124] // 0x7c
str r1, [r4, #124] // 0x7c    // 67e1 str r1, [r4, #124] // 0x7c
str r2, [r4, #124] // 0x7c    // 67e2 str r2, [r4, #124] // 0x7c
str r3, [r4, #124] // 0x7c    // 67e3 str r3, [r4, #124] // 0x7c
str r4, [r4, #124] // 0x7c    // 67e4 str r4, [r4, #124] // 0x7c
str r5, [r4, #124] // 0x7c    // 67e5 str r5, [r4, #124] // 0x7c
str r6, [r4, #124] // 0x7c    // 67e6 str r6, [r4, #124] // 0x7c
str r7, [r4, #124] // 0x7c    // 67e7 str r7, [r4, #124] // 0x7c
str r0, [r5, #124] // 0x7c    // 67e8 str r0, [r5, #124] // 0x7c
str r1, [r5, #124] // 0x7c    // 67e9 str r1, [r5, #124] // 0x7c
str r2, [r5, #124] // 0x7c    // 67ea str r2, [r5, #124] // 0x7c
str r3, [r5, #124] // 0x7c    // 67eb str r3, [r5, #124] // 0x7c
str r4, [r5, #124] // 0x7c    // 67ec str r4, [r5, #124] // 0x7c
str r5, [r5, #124] // 0x7c    // 67ed str r5, [r5, #124] // 0x7c
str r6, [r5, #124] // 0x7c    // 67ee str r6, [r5, #124] // 0x7c
str r7, [r5, #124] // 0x7c    // 67ef str r7, [r5, #124] // 0x7c
str r0, [r6, #124] // 0x7c    // 67f0 str r0, [r6, #124] // 0x7c
str r1, [r6, #124] // 0x7c    // 67f1 str r1, [r6, #124] // 0x7c
str r2, [r6, #124] // 0x7c    // 67f2 str r2, [r6, #124] // 0x7c
str r3, [r6, #124] // 0x7c    // 67f3 str r3, [r6, #124] // 0x7c
str r4, [r6, #124] // 0x7c    // 67f4 str r4, [r6, #124] // 0x7c
str r5, [r6, #124] // 0x7c    // 67f5 str r5, [r6, #124] // 0x7c
str r6, [r6, #124] // 0x7c    // 67f6 str r6, [r6, #124] // 0x7c
str r7, [r6, #124] // 0x7c    // 67f7 str r7, [r6, #124] // 0x7c
str r0, [r7, #124] // 0x7c    // 67f8 str r0, [r7, #124] // 0x7c
str r1, [r7, #124] // 0x7c    // 67f9 str r1, [r7, #124] // 0x7c
str r2, [r7, #124] // 0x7c    // 67fa str r2, [r7, #124] // 0x7c
str r3, [r7, #124] // 0x7c    // 67fb str r3, [r7, #124] // 0x7c
str r4, [r7, #124] // 0x7c    // 67fc str r4, [r7, #124] // 0x7c
str r5, [r7, #124] // 0x7c    // 67fd str r5, [r7, #124] // 0x7c
str r6, [r7, #124] // 0x7c    // 67fe str r6, [r7, #124] // 0x7c
str r7, [r7, #124] // 0x7c    // 67ff str r7, [r7, #124] // 0x7c

ldr r0, [r0, #0]             // 6800 ldr r0, [r0, #0]
ldr r1, [r0, #0]             // 6801 ldr r1, [r0, #0]
ldr r2, [r0, #0]             // 6802 ldr r2, [r0, #0]
ldr r3, [r0, #0]             // 6803 ldr r3, [r0, #0]
ldr r4, [r0, #0]             // 6804 ldr r4, [r0, #0]
ldr r5, [r0, #0]             // 6805 ldr r5, [r0, #0]
ldr r6, [r0, #0]             // 6806 ldr r6, [r0, #0]
ldr r7, [r0, #0]             // 6807 ldr r7, [r0, #0]
ldr r0, [r1, #0]             // 6808 ldr r0, [r1, #0]
ldr r1, [r1, #0]             // 6809 ldr r1, [r1, #0]
ldr r2, [r1, #0]             // 680a ldr r2, [r1, #0]
ldr r3, [r1, #0]             // 680b ldr r3, [r1, #0]
ldr r4, [r1, #0]             // 680c ldr r4, [r1, #0]
ldr r5, [r1, #0]             // 680d ldr r5, [r1, #0]
ldr r6, [r1, #0]             // 680e ldr r6, [r1, #0]
ldr r7, [r1, #0]             // 680f ldr r7, [r1, #0]
ldr r0, [r2, #0]             // 6810 ldr r0, [r2, #0]
ldr r1, [r2, #0]             // 6811 ldr r1, [r2, #0]
ldr r2, [r2, #0]             // 6812 ldr r2, [r2, #0]
ldr r3, [r2, #0]             // 6813 ldr r3, [r2, #0]
ldr r4, [r2, #0]             // 6814 ldr r4, [r2, #0]
ldr r5, [r2, #0]             // 6815 ldr r5, [r2, #0]
ldr r6, [r2, #0]             // 6816 ldr r6, [r2, #0]
ldr r7, [r2, #0]             // 6817 ldr r7, [r2, #0]
ldr r0, [r3, #0]             // 6818 ldr r0, [r3, #0]
ldr r1, [r3, #0]             // 6819 ldr r1, [r3, #0]
ldr r2, [r3, #0]             // 681a ldr r2, [r3, #0]
ldr r3, [r3, #0]             // 681b ldr r3, [r3, #0]
ldr r4, [r3, #0]             // 681c ldr r4, [r3, #0]
ldr r5, [r3, #0]             // 681d ldr r5, [r3, #0]
ldr r6, [r3, #0]             // 681e ldr r6, [r3, #0]
ldr r7, [r3, #0]             // 681f ldr r7, [r3, #0]
ldr r0, [r4, #0]             // 6820 ldr r0, [r4, #0]
ldr r1, [r4, #0]             // 6821 ldr r1, [r4, #0]
ldr r2, [r4, #0]             // 6822 ldr r2, [r4, #0]
ldr r3, [r4, #0]             // 6823 ldr r3, [r4, #0]
ldr r4, [r4, #0]             // 6824 ldr r4, [r4, #0]
ldr r5, [r4, #0]             // 6825 ldr r5, [r4, #0]
ldr r6, [r4, #0]             // 6826 ldr r6, [r4, #0]
ldr r7, [r4, #0]             // 6827 ldr r7, [r4, #0]
ldr r0, [r5, #0]             // 6828 ldr r0, [r5, #0]
ldr r1, [r5, #0]             // 6829 ldr r1, [r5, #0]
ldr r2, [r5, #0]             // 682a ldr r2, [r5, #0]
ldr r3, [r5, #0]             // 682b ldr r3, [r5, #0]
ldr r4, [r5, #0]             // 682c ldr r4, [r5, #0]
ldr r5, [r5, #0]             // 682d ldr r5, [r5, #0]
ldr r6, [r5, #0]             // 682e ldr r6, [r5, #0]
ldr r7, [r5, #0]             // 682f ldr r7, [r5, #0]
ldr r0, [r6, #0]             // 6830 ldr r0, [r6, #0]
ldr r1, [r6, #0]             // 6831 ldr r1, [r6, #0]
ldr r2, [r6, #0]             // 6832 ldr r2, [r6, #0]
ldr r3, [r6, #0]             // 6833 ldr r3, [r6, #0]
ldr r4, [r6, #0]             // 6834 ldr r4, [r6, #0]
ldr r5, [r6, #0]             // 6835 ldr r5, [r6, #0]
ldr r6, [r6, #0]             // 6836 ldr r6, [r6, #0]
ldr r7, [r6, #0]             // 6837 ldr r7, [r6, #0]
ldr r0, [r7, #0]             // 6838 ldr r0, [r7, #0]
ldr r1, [r7, #0]             // 6839 ldr r1, [r7, #0]
ldr r2, [r7, #0]             // 683a ldr r2, [r7, #0]
ldr r3, [r7, #0]             // 683b ldr r3, [r7, #0]
ldr r4, [r7, #0]             // 683c ldr r4, [r7, #0]
ldr r5, [r7, #0]             // 683d ldr r5, [r7, #0]
ldr r6, [r7, #0]             // 683e ldr r6, [r7, #0]
ldr r7, [r7, #0]             // 683f ldr r7, [r7, #0]
ldr r0, [r0, #4]             // 6840 ldr r0, [r0, #4]
ldr r1, [r0, #4]             // 6841 ldr r1, [r0, #4]
ldr r2, [r0, #4]             // 6842 ldr r2, [r0, #4]
ldr r3, [r0, #4]             // 6843 ldr r3, [r0, #4]
ldr r4, [r0, #4]             // 6844 ldr r4, [r0, #4]
ldr r5, [r0, #4]             // 6845 ldr r5, [r0, #4]
ldr r6, [r0, #4]             // 6846 ldr r6, [r0, #4]
ldr r7, [r0, #4]             // 6847 ldr r7, [r0, #4]
ldr r0, [r1, #4]             // 6848 ldr r0, [r1, #4]
ldr r1, [r1, #4]             // 6849 ldr r1, [r1, #4]
ldr r2, [r1, #4]             // 684a ldr r2, [r1, #4]
ldr r3, [r1, #4]             // 684b ldr r3, [r1, #4]
ldr r4, [r1, #4]             // 684c ldr r4, [r1, #4]
ldr r5, [r1, #4]             // 684d ldr r5, [r1, #4]
ldr r6, [r1, #4]             // 684e ldr r6, [r1, #4]
ldr r7, [r1, #4]             // 684f ldr r7, [r1, #4]
ldr r0, [r2, #4]             // 6850 ldr r0, [r2, #4]
ldr r1, [r2, #4]             // 6851 ldr r1, [r2, #4]
ldr r2, [r2, #4]             // 6852 ldr r2, [r2, #4]
ldr r3, [r2, #4]             // 6853 ldr r3, [r2, #4]
ldr r4, [r2, #4]             // 6854 ldr r4, [r2, #4]
ldr r5, [r2, #4]             // 6855 ldr r5, [r2, #4]
ldr r6, [r2, #4]             // 6856 ldr r6, [r2, #4]
ldr r7, [r2, #4]             // 6857 ldr r7, [r2, #4]
ldr r0, [r3, #4]             // 6858 ldr r0, [r3, #4]
ldr r1, [r3, #4]             // 6859 ldr r1, [r3, #4]
ldr r2, [r3, #4]             // 685a ldr r2, [r3, #4]
ldr r3, [r3, #4]             // 685b ldr r3, [r3, #4]
ldr r4, [r3, #4]             // 685c ldr r4, [r3, #4]
ldr r5, [r3, #4]             // 685d ldr r5, [r3, #4]
ldr r6, [r3, #4]             // 685e ldr r6, [r3, #4]
ldr r7, [r3, #4]             // 685f ldr r7, [r3, #4]
ldr r0, [r4, #4]             // 6860 ldr r0, [r4, #4]
ldr r1, [r4, #4]             // 6861 ldr r1, [r4, #4]
ldr r2, [r4, #4]             // 6862 ldr r2, [r4, #4]
ldr r3, [r4, #4]             // 6863 ldr r3, [r4, #4]
ldr r4, [r4, #4]             // 6864 ldr r4, [r4, #4]
ldr r5, [r4, #4]             // 6865 ldr r5, [r4, #4]
ldr r6, [r4, #4]             // 6866 ldr r6, [r4, #4]
ldr r7, [r4, #4]             // 6867 ldr r7, [r4, #4]
ldr r0, [r5, #4]             // 6868 ldr r0, [r5, #4]
ldr r1, [r5, #4]             // 6869 ldr r1, [r5, #4]
ldr r2, [r5, #4]             // 686a ldr r2, [r5, #4]
ldr r3, [r5, #4]             // 686b ldr r3, [r5, #4]
ldr r4, [r5, #4]             // 686c ldr r4, [r5, #4]
ldr r5, [r5, #4]             // 686d ldr r5, [r5, #4]
ldr r6, [r5, #4]             // 686e ldr r6, [r5, #4]
ldr r7, [r5, #4]             // 686f ldr r7, [r5, #4]
ldr r0, [r6, #4]             // 6870 ldr r0, [r6, #4]
ldr r1, [r6, #4]             // 6871 ldr r1, [r6, #4]
ldr r2, [r6, #4]             // 6872 ldr r2, [r6, #4]
ldr r3, [r6, #4]             // 6873 ldr r3, [r6, #4]
ldr r4, [r6, #4]             // 6874 ldr r4, [r6, #4]
ldr r5, [r6, #4]             // 6875 ldr r5, [r6, #4]
ldr r6, [r6, #4]             // 6876 ldr r6, [r6, #4]
ldr r7, [r6, #4]             // 6877 ldr r7, [r6, #4]
ldr r0, [r7, #4]             // 6878 ldr r0, [r7, #4]
ldr r1, [r7, #4]             // 6879 ldr r1, [r7, #4]
ldr r2, [r7, #4]             // 687a ldr r2, [r7, #4]
ldr r3, [r7, #4]             // 687b ldr r3, [r7, #4]
ldr r4, [r7, #4]             // 687c ldr r4, [r7, #4]
ldr r5, [r7, #4]             // 687d ldr r5, [r7, #4]
ldr r6, [r7, #4]             // 687e ldr r6, [r7, #4]
ldr r7, [r7, #4]             // 687f ldr r7, [r7, #4]
ldr r0, [r0, #124] // 0x7c    // 6fc0 ldr r0, [r0, #124] // 0x7c
ldr r1, [r0, #124] // 0x7c    // 6fc1 ldr r1, [r0, #124] // 0x7c
ldr r2, [r0, #124] // 0x7c    // 6fc2 ldr r2, [r0, #124] // 0x7c
ldr r3, [r0, #124] // 0x7c    // 6fc3 ldr r3, [r0, #124] // 0x7c
ldr r4, [r0, #124] // 0x7c    // 6fc4 ldr r4, [r0, #124] // 0x7c
ldr r5, [r0, #124] // 0x7c    // 6fc5 ldr r5, [r0, #124] // 0x7c
ldr r6, [r0, #124] // 0x7c    // 6fc6 ldr r6, [r0, #124] // 0x7c
ldr r7, [r0, #124] // 0x7c    // 6fc7 ldr r7, [r0, #124] // 0x7c
ldr r0, [r1, #124] // 0x7c    // 6fc8 ldr r0, [r1, #124] // 0x7c
ldr r1, [r1, #124] // 0x7c    // 6fc9 ldr r1, [r1, #124] // 0x7c
ldr r2, [r1, #124] // 0x7c    // 6fca ldr r2, [r1, #124] // 0x7c
ldr r3, [r1, #124] // 0x7c    // 6fcb ldr r3, [r1, #124] // 0x7c
ldr r4, [r1, #124] // 0x7c    // 6fcc ldr r4, [r1, #124] // 0x7c
ldr r5, [r1, #124] // 0x7c    // 6fcd ldr r5, [r1, #124] // 0x7c
ldr r6, [r1, #124] // 0x7c    // 6fce ldr r6, [r1, #124] // 0x7c
ldr r7, [r1, #124] // 0x7c    // 6fcf ldr r7, [r1, #124] // 0x7c
ldr r0, [r2, #124] // 0x7c    // 6fd0 ldr r0, [r2, #124] // 0x7c
ldr r1, [r2, #124] // 0x7c    // 6fd1 ldr r1, [r2, #124] // 0x7c
ldr r2, [r2, #124] // 0x7c    // 6fd2 ldr r2, [r2, #124] // 0x7c
ldr r3, [r2, #124] // 0x7c    // 6fd3 ldr r3, [r2, #124] // 0x7c
ldr r4, [r2, #124] // 0x7c    // 6fd4 ldr r4, [r2, #124] // 0x7c
ldr r5, [r2, #124] // 0x7c    // 6fd5 ldr r5, [r2, #124] // 0x7c
ldr r6, [r2, #124] // 0x7c    // 6fd6 ldr r6, [r2, #124] // 0x7c
ldr r7, [r2, #124] // 0x7c    // 6fd7 ldr r7, [r2, #124] // 0x7c
ldr r0, [r3, #124] // 0x7c    // 6fd8 ldr r0, [r3, #124] // 0x7c
ldr r1, [r3, #124] // 0x7c    // 6fd9 ldr r1, [r3, #124] // 0x7c
ldr r2, [r3, #124] // 0x7c    // 6fda ldr r2, [r3, #124] // 0x7c
ldr r3, [r3, #124] // 0x7c    // 6fdb ldr r3, [r3, #124] // 0x7c
ldr r4, [r3, #124] // 0x7c    // 6fdc ldr r4, [r3, #124] // 0x7c
ldr r5, [r3, #124] // 0x7c    // 6fdd ldr r5, [r3, #124] // 0x7c
ldr r6, [r3, #124] // 0x7c    // 6fde ldr r6, [r3, #124] // 0x7c
ldr r7, [r3, #124] // 0x7c    // 6fdf ldr r7, [r3, #124] // 0x7c
ldr r0, [r4, #124] // 0x7c    // 6fe0 ldr r0, [r4, #124] // 0x7c
ldr r1, [r4, #124] // 0x7c    // 6fe1 ldr r1, [r4, #124] // 0x7c
ldr r2, [r4, #124] // 0x7c    // 6fe2 ldr r2, [r4, #124] // 0x7c
ldr r3, [r4, #124] // 0x7c    // 6fe3 ldr r3, [r4, #124] // 0x7c
ldr r4, [r4, #124] // 0x7c    // 6fe4 ldr r4, [r4, #124] // 0x7c
ldr r5, [r4, #124] // 0x7c    // 6fe5 ldr r5, [r4, #124] // 0x7c
ldr r6, [r4, #124] // 0x7c    // 6fe6 ldr r6, [r4, #124] // 0x7c
ldr r7, [r4, #124] // 0x7c    // 6fe7 ldr r7, [r4, #124] // 0x7c
ldr r0, [r5, #124] // 0x7c    // 6fe8 ldr r0, [r5, #124] // 0x7c
ldr r1, [r5, #124] // 0x7c    // 6fe9 ldr r1, [r5, #124] // 0x7c
ldr r2, [r5, #124] // 0x7c    // 6fea ldr r2, [r5, #124] // 0x7c
ldr r3, [r5, #124] // 0x7c    // 6feb ldr r3, [r5, #124] // 0x7c
ldr r4, [r5, #124] // 0x7c    // 6fec ldr r4, [r5, #124] // 0x7c
ldr r5, [r5, #124] // 0x7c    // 6fed ldr r5, [r5, #124] // 0x7c
ldr r6, [r5, #124] // 0x7c    // 6fee ldr r6, [r5, #124] // 0x7c
ldr r7, [r5, #124] // 0x7c    // 6fef ldr r7, [r5, #124] // 0x7c
ldr r0, [r6, #124] // 0x7c    // 6ff0 ldr r0, [r6, #124] // 0x7c
ldr r1, [r6, #124] // 0x7c    // 6ff1 ldr r1, [r6, #124] // 0x7c
ldr r2, [r6, #124] // 0x7c    // 6ff2 ldr r2, [r6, #124] // 0x7c
ldr r3, [r6, #124] // 0x7c    // 6ff3 ldr r3, [r6, #124] // 0x7c
ldr r4, [r6, #124] // 0x7c    // 6ff4 ldr r4, [r6, #124] // 0x7c
ldr r5, [r6, #124] // 0x7c    // 6ff5 ldr r5, [r6, #124] // 0x7c
ldr r6, [r6, #124] // 0x7c    // 6ff6 ldr r6, [r6, #124] // 0x7c
ldr r7, [r6, #124] // 0x7c    // 6ff7 ldr r7, [r6, #124] // 0x7c
ldr r0, [r7, #124] // 0x7c    // 6ff8 ldr r0, [r7, #124] // 0x7c
ldr r1, [r7, #124] // 0x7c    // 6ff9 ldr r1, [r7, #124] // 0x7c
ldr r2, [r7, #124] // 0x7c    // 6ffa ldr r2, [r7, #124] // 0x7c
ldr r3, [r7, #124] // 0x7c    // 6ffb ldr r3, [r7, #124] // 0x7c
ldr r4, [r7, #124] // 0x7c    // 6ffc ldr r4, [r7, #124] // 0x7c
ldr r5, [r7, #124] // 0x7c    // 6ffd ldr r5, [r7, #124] // 0x7c
ldr r6, [r7, #124] // 0x7c    // 6ffe ldr r6, [r7, #124] // 0x7c
ldr r7, [r7, #124] // 0x7c    // 6fff ldr r7, [r7, #124] // 0x7c

strb r0, [r0, #0]            // 7000 strb r0, [r0, #0]
strb r1, [r0, #0]            // 7001 strb r1, [r0, #0]
strb r2, [r0, #0]            // 7002 strb r2, [r0, #0]
strb r3, [r0, #0]            // 7003 strb r3, [r0, #0]
strb r4, [r0, #0]            // 7004 strb r4, [r0, #0]
strb r5, [r0, #0]            // 7005 strb r5, [r0, #0]
strb r6, [r0, #0]            // 7006 strb r6, [r0, #0]
strb r7, [r0, #0]            // 7007 strb r7, [r0, #0]
strb r0, [r1, #0]            // 7008 strb r0, [r1, #0]
strb r1, [r1, #0]            // 7009 strb r1, [r1, #0]
strb r2, [r1, #0]            // 700a strb r2, [r1, #0]
strb r3, [r1, #0]            // 700b strb r3, [r1, #0]
strb r4, [r1, #0]            // 700c strb r4, [r1, #0]
strb r5, [r1, #0]            // 700d strb r5, [r1, #0]
strb r6, [r1, #0]            // 700e strb r6, [r1, #0]
strb r7, [r1, #0]            // 700f strb r7, [r1, #0]
strb r0, [r2, #0]            // 7010 strb r0, [r2, #0]
strb r1, [r2, #0]            // 7011 strb r1, [r2, #0]
strb r2, [r2, #0]            // 7012 strb r2, [r2, #0]
strb r3, [r2, #0]            // 7013 strb r3, [r2, #0]
strb r4, [r2, #0]            // 7014 strb r4, [r2, #0]
strb r5, [r2, #0]            // 7015 strb r5, [r2, #0]
strb r6, [r2, #0]            // 7016 strb r6, [r2, #0]
strb r7, [r2, #0]            // 7017 strb r7, [r2, #0]
strb r0, [r3, #0]            // 7018 strb r0, [r3, #0]
strb r1, [r3, #0]            // 7019 strb r1, [r3, #0]
strb r2, [r3, #0]            // 701a strb r2, [r3, #0]
strb r3, [r3, #0]            // 701b strb r3, [r3, #0]
strb r4, [r3, #0]            // 701c strb r4, [r3, #0]
strb r5, [r3, #0]            // 701d strb r5, [r3, #0]
strb r6, [r3, #0]            // 701e strb r6, [r3, #0]
strb r7, [r3, #0]            // 701f strb r7, [r3, #0]
strb r0, [r4, #0]            // 7020 strb r0, [r4, #0]
strb r1, [r4, #0]            // 7021 strb r1, [r4, #0]
strb r2, [r4, #0]            // 7022 strb r2, [r4, #0]
strb r3, [r4, #0]            // 7023 strb r3, [r4, #0]
strb r4, [r4, #0]            // 7024 strb r4, [r4, #0]
strb r5, [r4, #0]            // 7025 strb r5, [r4, #0]
strb r6, [r4, #0]            // 7026 strb r6, [r4, #0]
strb r7, [r4, #0]            // 7027 strb r7, [r4, #0]
strb r0, [r5, #0]            // 7028 strb r0, [r5, #0]
strb r1, [r5, #0]            // 7029 strb r1, [r5, #0]
strb r2, [r5, #0]            // 702a strb r2, [r5, #0]
strb r3, [r5, #0]            // 702b strb r3, [r5, #0]
strb r4, [r5, #0]            // 702c strb r4, [r5, #0]
strb r5, [r5, #0]            // 702d strb r5, [r5, #0]
strb r6, [r5, #0]            // 702e strb r6, [r5, #0]
strb r7, [r5, #0]            // 702f strb r7, [r5, #0]
strb r0, [r6, #0]            // 7030 strb r0, [r6, #0]
strb r1, [r6, #0]            // 7031 strb r1, [r6, #0]
strb r2, [r6, #0]            // 7032 strb r2, [r6, #0]
strb r3, [r6, #0]            // 7033 strb r3, [r6, #0]
strb r4, [r6, #0]            // 7034 strb r4, [r6, #0]
strb r5, [r6, #0]            // 7035 strb r5, [r6, #0]
strb r6, [r6, #0]            // 7036 strb r6, [r6, #0]
strb r7, [r6, #0]            // 7037 strb r7, [r6, #0]
strb r0, [r7, #0]            // 7038 strb r0, [r7, #0]
strb r1, [r7, #0]            // 7039 strb r1, [r7, #0]
strb r2, [r7, #0]            // 703a strb r2, [r7, #0]
strb r3, [r7, #0]            // 703b strb r3, [r7, #0]
strb r4, [r7, #0]            // 703c strb r4, [r7, #0]
strb r5, [r7, #0]            // 703d strb r5, [r7, #0]
strb r6, [r7, #0]            // 703e strb r6, [r7, #0]
strb r7, [r7, #0]            // 703f strb r7, [r7, #0]
strb r0, [r0, #1]            // 7040 strb r0, [r0, #1]
strb r1, [r0, #1]            // 7041 strb r1, [r0, #1]
strb r2, [r0, #1]            // 7042 strb r2, [r0, #1]
strb r3, [r0, #1]            // 7043 strb r3, [r0, #1]
strb r4, [r0, #1]            // 7044 strb r4, [r0, #1]
strb r5, [r0, #1]            // 7045 strb r5, [r0, #1]
strb r6, [r0, #1]            // 7046 strb r6, [r0, #1]
strb r7, [r0, #1]            // 7047 strb r7, [r0, #1]
strb r0, [r1, #1]            // 7048 strb r0, [r1, #1]
strb r1, [r1, #1]            // 7049 strb r1, [r1, #1]
strb r2, [r1, #1]            // 704a strb r2, [r1, #1]
strb r3, [r1, #1]            // 704b strb r3, [r1, #1]
strb r4, [r1, #1]            // 704c strb r4, [r1, #1]
strb r5, [r1, #1]            // 704d strb r5, [r1, #1]
strb r6, [r1, #1]            // 704e strb r6, [r1, #1]
strb r7, [r1, #1]            // 704f strb r7, [r1, #1]
strb r0, [r2, #1]            // 7050 strb r0, [r2, #1]
strb r1, [r2, #1]            // 7051 strb r1, [r2, #1]
strb r2, [r2, #1]            // 7052 strb r2, [r2, #1]
strb r3, [r2, #1]            // 7053 strb r3, [r2, #1]
strb r4, [r2, #1]            // 7054 strb r4, [r2, #1]
strb r5, [r2, #1]            // 7055 strb r5, [r2, #1]
strb r6, [r2, #1]            // 7056 strb r6, [r2, #1]
strb r7, [r2, #1]            // 7057 strb r7, [r2, #1]
strb r0, [r3, #1]            // 7058 strb r0, [r3, #1]
strb r1, [r3, #1]            // 7059 strb r1, [r3, #1]
strb r2, [r3, #1]            // 705a strb r2, [r3, #1]
strb r3, [r3, #1]            // 705b strb r3, [r3, #1]
strb r4, [r3, #1]            // 705c strb r4, [r3, #1]
strb r5, [r3, #1]            // 705d strb r5, [r3, #1]
strb r6, [r3, #1]            // 705e strb r6, [r3, #1]
strb r7, [r3, #1]            // 705f strb r7, [r3, #1]
strb r0, [r4, #1]            // 7060 strb r0, [r4, #1]
strb r1, [r4, #1]            // 7061 strb r1, [r4, #1]
strb r2, [r4, #1]            // 7062 strb r2, [r4, #1]
strb r3, [r4, #1]            // 7063 strb r3, [r4, #1]
strb r4, [r4, #1]            // 7064 strb r4, [r4, #1]
strb r5, [r4, #1]            // 7065 strb r5, [r4, #1]
strb r6, [r4, #1]            // 7066 strb r6, [r4, #1]
strb r7, [r4, #1]            // 7067 strb r7, [r4, #1]
strb r0, [r5, #1]            // 7068 strb r0, [r5, #1]
strb r1, [r5, #1]            // 7069 strb r1, [r5, #1]
strb r2, [r5, #1]            // 706a strb r2, [r5, #1]
strb r3, [r5, #1]            // 706b strb r3, [r5, #1]
strb r4, [r5, #1]            // 706c strb r4, [r5, #1]
strb r5, [r5, #1]            // 706d strb r5, [r5, #1]
strb r6, [r5, #1]            // 706e strb r6, [r5, #1]
strb r7, [r5, #1]            // 706f strb r7, [r5, #1]
strb r0, [r6, #1]            // 7070 strb r0, [r6, #1]
strb r1, [r6, #1]            // 7071 strb r1, [r6, #1]
strb r2, [r6, #1]            // 7072 strb r2, [r6, #1]
strb r3, [r6, #1]            // 7073 strb r3, [r6, #1]
strb r4, [r6, #1]            // 7074 strb r4, [r6, #1]
strb r5, [r6, #1]            // 7075 strb r5, [r6, #1]
strb r6, [r6, #1]            // 7076 strb r6, [r6, #1]
strb r7, [r6, #1]            // 7077 strb r7, [r6, #1]
strb r0, [r7, #1]            // 7078 strb r0, [r7, #1]
strb r1, [r7, #1]            // 7079 strb r1, [r7, #1]
strb r2, [r7, #1]            // 707a strb r2, [r7, #1]
strb r3, [r7, #1]            // 707b strb r3, [r7, #1]
strb r4, [r7, #1]            // 707c strb r4, [r7, #1]
strb r5, [r7, #1]            // 707d strb r5, [r7, #1]
strb r6, [r7, #1]            // 707e strb r6, [r7, #1]
strb r7, [r7, #1]            // 707f strb r7, [r7, #1]
strb r0, [r0, #31]           // 77c0 strb r0, [r0, #31]
strb r1, [r0, #31]           // 77c1 strb r1, [r0, #31]
strb r2, [r0, #31]           // 77c2 strb r2, [r0, #31]
strb r3, [r0, #31]           // 77c3 strb r3, [r0, #31]
strb r4, [r0, #31]           // 77c4 strb r4, [r0, #31]
strb r5, [r0, #31]           // 77c5 strb r5, [r0, #31]
strb r6, [r0, #31]           // 77c6 strb r6, [r0, #31]
strb r7, [r0, #31]           // 77c7 strb r7, [r0, #31]
strb r0, [r1, #31]           // 77c8 strb r0, [r1, #31]
strb r1, [r1, #31]           // 77c9 strb r1, [r1, #31]
strb r2, [r1, #31]           // 77ca strb r2, [r1, #31]
strb r3, [r1, #31]           // 77cb strb r3, [r1, #31]
strb r4, [r1, #31]           // 77cc strb r4, [r1, #31]
strb r5, [r1, #31]           // 77cd strb r5, [r1, #31]
strb r6, [r1, #31]           // 77ce strb r6, [r1, #31]
strb r7, [r1, #31]           // 77cf strb r7, [r1, #31]
strb r0, [r2, #31]           // 77d0 strb r0, [r2, #31]
strb r1, [r2, #31]           // 77d1 strb r1, [r2, #31]
strb r2, [r2, #31]           // 77d2 strb r2, [r2, #31]
strb r3, [r2, #31]           // 77d3 strb r3, [r2, #31]
strb r4, [r2, #31]           // 77d4 strb r4, [r2, #31]
strb r5, [r2, #31]           // 77d5 strb r5, [r2, #31]
strb r6, [r2, #31]           // 77d6 strb r6, [r2, #31]
strb r7, [r2, #31]           // 77d7 strb r7, [r2, #31]
strb r0, [r3, #31]           // 77d8 strb r0, [r3, #31]
strb r1, [r3, #31]           // 77d9 strb r1, [r3, #31]
strb r2, [r3, #31]           // 77da strb r2, [r3, #31]
strb r3, [r3, #31]           // 77db strb r3, [r3, #31]
strb r4, [r3, #31]           // 77dc strb r4, [r3, #31]
strb r5, [r3, #31]           // 77dd strb r5, [r3, #31]
strb r6, [r3, #31]           // 77de strb r6, [r3, #31]
strb r7, [r3, #31]           // 77df strb r7, [r3, #31]
strb r0, [r4, #31]           // 77e0 strb r0, [r4, #31]
strb r1, [r4, #31]           // 77e1 strb r1, [r4, #31]
strb r2, [r4, #31]           // 77e2 strb r2, [r4, #31]
strb r3, [r4, #31]           // 77e3 strb r3, [r4, #31]
strb r4, [r4, #31]           // 77e4 strb r4, [r4, #31]
strb r5, [r4, #31]           // 77e5 strb r5, [r4, #31]
strb r6, [r4, #31]           // 77e6 strb r6, [r4, #31]
strb r7, [r4, #31]           // 77e7 strb r7, [r4, #31]
strb r0, [r5, #31]           // 77e8 strb r0, [r5, #31]
strb r1, [r5, #31]           // 77e9 strb r1, [r5, #31]
strb r2, [r5, #31]           // 77ea strb r2, [r5, #31]
strb r3, [r5, #31]           // 77eb strb r3, [r5, #31]
strb r4, [r5, #31]           // 77ec strb r4, [r5, #31]
strb r5, [r5, #31]           // 77ed strb r5, [r5, #31]
strb r6, [r5, #31]           // 77ee strb r6, [r5, #31]
strb r7, [r5, #31]           // 77ef strb r7, [r5, #31]
strb r0, [r6, #31]           // 77f0 strb r0, [r6, #31]
strb r1, [r6, #31]           // 77f1 strb r1, [r6, #31]
strb r2, [r6, #31]           // 77f2 strb r2, [r6, #31]
strb r3, [r6, #31]           // 77f3 strb r3, [r6, #31]
strb r4, [r6, #31]           // 77f4 strb r4, [r6, #31]
strb r5, [r6, #31]           // 77f5 strb r5, [r6, #31]
strb r6, [r6, #31]           // 77f6 strb r6, [r6, #31]
strb r7, [r6, #31]           // 77f7 strb r7, [r6, #31]
strb r0, [r7, #31]           // 77f8 strb r0, [r7, #31]
strb r1, [r7, #31]           // 77f9 strb r1, [r7, #31]
strb r2, [r7, #31]           // 77fa strb r2, [r7, #31]
strb r3, [r7, #31]           // 77fb strb r3, [r7, #31]
strb r4, [r7, #31]           // 77fc strb r4, [r7, #31]
strb r5, [r7, #31]           // 77fd strb r5, [r7, #31]
strb r6, [r7, #31]           // 77fe strb r6, [r7, #31]
strb r7, [r7, #31]           // 77ff strb r7, [r7, #31]

ldrb r0, [r0, #0]            // 7800 ldrb r0, [r0, #0]
ldrb r1, [r0, #0]            // 7801 ldrb r1, [r0, #0]
ldrb r2, [r0, #0]            // 7802 ldrb r2, [r0, #0]
ldrb r3, [r0, #0]            // 7803 ldrb r3, [r0, #0]
ldrb r4, [r0, #0]            // 7804 ldrb r4, [r0, #0]
ldrb r5, [r0, #0]            // 7805 ldrb r5, [r0, #0]
ldrb r6, [r0, #0]            // 7806 ldrb r6, [r0, #0]
ldrb r7, [r0, #0]            // 7807 ldrb r7, [r0, #0]
ldrb r0, [r1, #0]            // 7808 ldrb r0, [r1, #0]
ldrb r1, [r1, #0]            // 7809 ldrb r1, [r1, #0]
ldrb r2, [r1, #0]            // 780a ldrb r2, [r1, #0]
ldrb r3, [r1, #0]            // 780b ldrb r3, [r1, #0]
ldrb r4, [r1, #0]            // 780c ldrb r4, [r1, #0]
ldrb r5, [r1, #0]            // 780d ldrb r5, [r1, #0]
ldrb r6, [r1, #0]            // 780e ldrb r6, [r1, #0]
ldrb r7, [r1, #0]            // 780f ldrb r7, [r1, #0]
ldrb r0, [r2, #0]            // 7810 ldrb r0, [r2, #0]
ldrb r1, [r2, #0]            // 7811 ldrb r1, [r2, #0]
ldrb r2, [r2, #0]            // 7812 ldrb r2, [r2, #0]
ldrb r3, [r2, #0]            // 7813 ldrb r3, [r2, #0]
ldrb r4, [r2, #0]            // 7814 ldrb r4, [r2, #0]
ldrb r5, [r2, #0]            // 7815 ldrb r5, [r2, #0]
ldrb r6, [r2, #0]            // 7816 ldrb r6, [r2, #0]
ldrb r7, [r2, #0]            // 7817 ldrb r7, [r2, #0]
ldrb r0, [r3, #0]            // 7818 ldrb r0, [r3, #0]
ldrb r1, [r3, #0]            // 7819 ldrb r1, [r3, #0]
ldrb r2, [r3, #0]            // 781a ldrb r2, [r3, #0]
ldrb r3, [r3, #0]            // 781b ldrb r3, [r3, #0]
ldrb r4, [r3, #0]            // 781c ldrb r4, [r3, #0]
ldrb r5, [r3, #0]            // 781d ldrb r5, [r3, #0]
ldrb r6, [r3, #0]            // 781e ldrb r6, [r3, #0]
ldrb r7, [r3, #0]            // 781f ldrb r7, [r3, #0]
ldrb r0, [r4, #0]            // 7820 ldrb r0, [r4, #0]
ldrb r1, [r4, #0]            // 7821 ldrb r1, [r4, #0]
ldrb r2, [r4, #0]            // 7822 ldrb r2, [r4, #0]
ldrb r3, [r4, #0]            // 7823 ldrb r3, [r4, #0]
ldrb r4, [r4, #0]            // 7824 ldrb r4, [r4, #0]
ldrb r5, [r4, #0]            // 7825 ldrb r5, [r4, #0]
ldrb r6, [r4, #0]            // 7826 ldrb r6, [r4, #0]
ldrb r7, [r4, #0]            // 7827 ldrb r7, [r4, #0]
ldrb r0, [r5, #0]            // 7828 ldrb r0, [r5, #0]
ldrb r1, [r5, #0]            // 7829 ldrb r1, [r5, #0]
ldrb r2, [r5, #0]            // 782a ldrb r2, [r5, #0]
ldrb r3, [r5, #0]            // 782b ldrb r3, [r5, #0]
ldrb r4, [r5, #0]            // 782c ldrb r4, [r5, #0]
ldrb r5, [r5, #0]            // 782d ldrb r5, [r5, #0]
ldrb r6, [r5, #0]            // 782e ldrb r6, [r5, #0]
ldrb r7, [r5, #0]            // 782f ldrb r7, [r5, #0]
ldrb r0, [r6, #0]            // 7830 ldrb r0, [r6, #0]
ldrb r1, [r6, #0]            // 7831 ldrb r1, [r6, #0]
ldrb r2, [r6, #0]            // 7832 ldrb r2, [r6, #0]
ldrb r3, [r6, #0]            // 7833 ldrb r3, [r6, #0]
ldrb r4, [r6, #0]            // 7834 ldrb r4, [r6, #0]
ldrb r5, [r6, #0]            // 7835 ldrb r5, [r6, #0]
ldrb r6, [r6, #0]            // 7836 ldrb r6, [r6, #0]
ldrb r7, [r6, #0]            // 7837 ldrb r7, [r6, #0]
ldrb r0, [r7, #0]            // 7838 ldrb r0, [r7, #0]
ldrb r1, [r7, #0]            // 7839 ldrb r1, [r7, #0]
ldrb r2, [r7, #0]            // 783a ldrb r2, [r7, #0]
ldrb r3, [r7, #0]            // 783b ldrb r3, [r7, #0]
ldrb r4, [r7, #0]            // 783c ldrb r4, [r7, #0]
ldrb r5, [r7, #0]            // 783d ldrb r5, [r7, #0]
ldrb r6, [r7, #0]            // 783e ldrb r6, [r7, #0]
ldrb r7, [r7, #0]            // 783f ldrb r7, [r7, #0]
ldrb r0, [r0, #1]            // 7840 ldrb r0, [r0, #1]
ldrb r1, [r0, #1]            // 7841 ldrb r1, [r0, #1]
ldrb r2, [r0, #1]            // 7842 ldrb r2, [r0, #1]
ldrb r3, [r0, #1]            // 7843 ldrb r3, [r0, #1]
ldrb r4, [r0, #1]            // 7844 ldrb r4, [r0, #1]
ldrb r5, [r0, #1]            // 7845 ldrb r5, [r0, #1]
ldrb r6, [r0, #1]            // 7846 ldrb r6, [r0, #1]
ldrb r7, [r0, #1]            // 7847 ldrb r7, [r0, #1]
ldrb r0, [r1, #1]            // 7848 ldrb r0, [r1, #1]
ldrb r1, [r1, #1]            // 7849 ldrb r1, [r1, #1]
ldrb r2, [r1, #1]            // 784a ldrb r2, [r1, #1]
ldrb r3, [r1, #1]            // 784b ldrb r3, [r1, #1]
ldrb r4, [r1, #1]            // 784c ldrb r4, [r1, #1]
ldrb r5, [r1, #1]            // 784d ldrb r5, [r1, #1]
ldrb r6, [r1, #1]            // 784e ldrb r6, [r1, #1]
ldrb r7, [r1, #1]            // 784f ldrb r7, [r1, #1]
ldrb r0, [r2, #1]            // 7850 ldrb r0, [r2, #1]
ldrb r1, [r2, #1]            // 7851 ldrb r1, [r2, #1]
ldrb r2, [r2, #1]            // 7852 ldrb r2, [r2, #1]
ldrb r3, [r2, #1]            // 7853 ldrb r3, [r2, #1]
ldrb r4, [r2, #1]            // 7854 ldrb r4, [r2, #1]
ldrb r5, [r2, #1]            // 7855 ldrb r5, [r2, #1]
ldrb r6, [r2, #1]            // 7856 ldrb r6, [r2, #1]
ldrb r7, [r2, #1]            // 7857 ldrb r7, [r2, #1]
ldrb r0, [r3, #1]            // 7858 ldrb r0, [r3, #1]
ldrb r1, [r3, #1]            // 7859 ldrb r1, [r3, #1]
ldrb r2, [r3, #1]            // 785a ldrb r2, [r3, #1]
ldrb r3, [r3, #1]            // 785b ldrb r3, [r3, #1]
ldrb r4, [r3, #1]            // 785c ldrb r4, [r3, #1]
ldrb r5, [r3, #1]            // 785d ldrb r5, [r3, #1]
ldrb r6, [r3, #1]            // 785e ldrb r6, [r3, #1]
ldrb r7, [r3, #1]            // 785f ldrb r7, [r3, #1]
ldrb r0, [r4, #1]            // 7860 ldrb r0, [r4, #1]
ldrb r1, [r4, #1]            // 7861 ldrb r1, [r4, #1]
ldrb r2, [r4, #1]            // 7862 ldrb r2, [r4, #1]
ldrb r3, [r4, #1]            // 7863 ldrb r3, [r4, #1]
ldrb r4, [r4, #1]            // 7864 ldrb r4, [r4, #1]
ldrb r5, [r4, #1]            // 7865 ldrb r5, [r4, #1]
ldrb r6, [r4, #1]            // 7866 ldrb r6, [r4, #1]
ldrb r7, [r4, #1]            // 7867 ldrb r7, [r4, #1]
ldrb r0, [r5, #1]            // 7868 ldrb r0, [r5, #1]
ldrb r1, [r5, #1]            // 7869 ldrb r1, [r5, #1]
ldrb r2, [r5, #1]            // 786a ldrb r2, [r5, #1]
ldrb r3, [r5, #1]            // 786b ldrb r3, [r5, #1]
ldrb r4, [r5, #1]            // 786c ldrb r4, [r5, #1]
ldrb r5, [r5, #1]            // 786d ldrb r5, [r5, #1]
ldrb r6, [r5, #1]            // 786e ldrb r6, [r5, #1]
ldrb r7, [r5, #1]            // 786f ldrb r7, [r5, #1]
ldrb r0, [r6, #1]            // 7870 ldrb r0, [r6, #1]
ldrb r1, [r6, #1]            // 7871 ldrb r1, [r6, #1]
ldrb r2, [r6, #1]            // 7872 ldrb r2, [r6, #1]
ldrb r3, [r6, #1]            // 7873 ldrb r3, [r6, #1]
ldrb r4, [r6, #1]            // 7874 ldrb r4, [r6, #1]
ldrb r5, [r6, #1]            // 7875 ldrb r5, [r6, #1]
ldrb r6, [r6, #1]            // 7876 ldrb r6, [r6, #1]
ldrb r7, [r6, #1]            // 7877 ldrb r7, [r6, #1]
ldrb r0, [r7, #1]            // 7878 ldrb r0, [r7, #1]
ldrb r1, [r7, #1]            // 7879 ldrb r1, [r7, #1]
ldrb r2, [r7, #1]            // 787a ldrb r2, [r7, #1]
ldrb r3, [r7, #1]            // 787b ldrb r3, [r7, #1]
ldrb r4, [r7, #1]            // 787c ldrb r4, [r7, #1]
ldrb r5, [r7, #1]            // 787d ldrb r5, [r7, #1]
ldrb r6, [r7, #1]            // 787e ldrb r6, [r7, #1]
ldrb r7, [r7, #1]            // 787f ldrb r7, [r7, #1]
ldrb r0, [r0, #31]           // 7fc0 ldrb r0, [r0, #31]
ldrb r1, [r0, #31]           // 7fc1 ldrb r1, [r0, #31]
ldrb r2, [r0, #31]           // 7fc2 ldrb r2, [r0, #31]
ldrb r3, [r0, #31]           // 7fc3 ldrb r3, [r0, #31]
ldrb r4, [r0, #31]           // 7fc4 ldrb r4, [r0, #31]
ldrb r5, [r0, #31]           // 7fc5 ldrb r5, [r0, #31]
ldrb r6, [r0, #31]           // 7fc6 ldrb r6, [r0, #31]
ldrb r7, [r0, #31]           // 7fc7 ldrb r7, [r0, #31]
ldrb r0, [r1, #31]           // 7fc8 ldrb r0, [r1, #31]
ldrb r1, [r1, #31]           // 7fc9 ldrb r1, [r1, #31]
ldrb r2, [r1, #31]           // 7fca ldrb r2, [r1, #31]
ldrb r3, [r1, #31]           // 7fcb ldrb r3, [r1, #31]
ldrb r4, [r1, #31]           // 7fcc ldrb r4, [r1, #31]
ldrb r5, [r1, #31]           // 7fcd ldrb r5, [r1, #31]
ldrb r6, [r1, #31]           // 7fce ldrb r6, [r1, #31]
ldrb r7, [r1, #31]           // 7fcf ldrb r7, [r1, #31]
ldrb r0, [r2, #31]           // 7fd0 ldrb r0, [r2, #31]
ldrb r1, [r2, #31]           // 7fd1 ldrb r1, [r2, #31]
ldrb r2, [r2, #31]           // 7fd2 ldrb r2, [r2, #31]
ldrb r3, [r2, #31]           // 7fd3 ldrb r3, [r2, #31]
ldrb r4, [r2, #31]           // 7fd4 ldrb r4, [r2, #31]
ldrb r5, [r2, #31]           // 7fd5 ldrb r5, [r2, #31]
ldrb r6, [r2, #31]           // 7fd6 ldrb r6, [r2, #31]
ldrb r7, [r2, #31]           // 7fd7 ldrb r7, [r2, #31]
ldrb r0, [r3, #31]           // 7fd8 ldrb r0, [r3, #31]
ldrb r1, [r3, #31]           // 7fd9 ldrb r1, [r3, #31]
ldrb r2, [r3, #31]           // 7fda ldrb r2, [r3, #31]
ldrb r3, [r3, #31]           // 7fdb ldrb r3, [r3, #31]
ldrb r4, [r3, #31]           // 7fdc ldrb r4, [r3, #31]
ldrb r5, [r3, #31]           // 7fdd ldrb r5, [r3, #31]
ldrb r6, [r3, #31]           // 7fde ldrb r6, [r3, #31]
ldrb r7, [r3, #31]           // 7fdf ldrb r7, [r3, #31]
ldrb r0, [r4, #31]           // 7fe0 ldrb r0, [r4, #31]
ldrb r1, [r4, #31]           // 7fe1 ldrb r1, [r4, #31]
ldrb r2, [r4, #31]           // 7fe2 ldrb r2, [r4, #31]
ldrb r3, [r4, #31]           // 7fe3 ldrb r3, [r4, #31]
ldrb r4, [r4, #31]           // 7fe4 ldrb r4, [r4, #31]
ldrb r5, [r4, #31]           // 7fe5 ldrb r5, [r4, #31]
ldrb r6, [r4, #31]           // 7fe6 ldrb r6, [r4, #31]
ldrb r7, [r4, #31]           // 7fe7 ldrb r7, [r4, #31]
ldrb r0, [r5, #31]           // 7fe8 ldrb r0, [r5, #31]
ldrb r1, [r5, #31]           // 7fe9 ldrb r1, [r5, #31]
ldrb r2, [r5, #31]           // 7fea ldrb r2, [r5, #31]
ldrb r3, [r5, #31]           // 7feb ldrb r3, [r5, #31]
ldrb r4, [r5, #31]           // 7fec ldrb r4, [r5, #31]
ldrb r5, [r5, #31]           // 7fed ldrb r5, [r5, #31]
ldrb r6, [r5, #31]           // 7fee ldrb r6, [r5, #31]
ldrb r7, [r5, #31]           // 7fef ldrb r7, [r5, #31]
ldrb r0, [r6, #31]           // 7ff0 ldrb r0, [r6, #31]
ldrb r1, [r6, #31]           // 7ff1 ldrb r1, [r6, #31]
ldrb r2, [r6, #31]           // 7ff2 ldrb r2, [r6, #31]
ldrb r3, [r6, #31]           // 7ff3 ldrb r3, [r6, #31]
ldrb r4, [r6, #31]           // 7ff4 ldrb r4, [r6, #31]
ldrb r5, [r6, #31]           // 7ff5 ldrb r5, [r6, #31]
ldrb r6, [r6, #31]           // 7ff6 ldrb r6, [r6, #31]
ldrb r7, [r6, #31]           // 7ff7 ldrb r7, [r6, #31]
ldrb r0, [r7, #31]           // 7ff8 ldrb r0, [r7, #31]
ldrb r1, [r7, #31]           // 7ff9 ldrb r1, [r7, #31]
ldrb r2, [r7, #31]           // 7ffa ldrb r2, [r7, #31]
ldrb r3, [r7, #31]           // 7ffb ldrb r3, [r7, #31]
ldrb r4, [r7, #31]           // 7ffc ldrb r4, [r7, #31]
ldrb r5, [r7, #31]           // 7ffd ldrb r5, [r7, #31]
ldrb r6, [r7, #31]           // 7ffe ldrb r6, [r7, #31]
ldrb r7, [r7, #31]           // 7fff ldrb r7, [r7, #31]

strh r0, [r0, #0]            // 8000 strh r0, [r0, #0]
strh r1, [r0, #0]            // 8001 strh r1, [r0, #0]
strh r2, [r0, #0]            // 8002 strh r2, [r0, #0]
strh r3, [r0, #0]            // 8003 strh r3, [r0, #0]
strh r4, [r0, #0]            // 8004 strh r4, [r0, #0]
strh r5, [r0, #0]            // 8005 strh r5, [r0, #0]
strh r6, [r0, #0]            // 8006 strh r6, [r0, #0]
strh r7, [r0, #0]            // 8007 strh r7, [r0, #0]
strh r0, [r1, #0]            // 8008 strh r0, [r1, #0]
strh r1, [r1, #0]            // 8009 strh r1, [r1, #0]
strh r2, [r1, #0]            // 800a strh r2, [r1, #0]
strh r3, [r1, #0]            // 800b strh r3, [r1, #0]
strh r4, [r1, #0]            // 800c strh r4, [r1, #0]
strh r5, [r1, #0]            // 800d strh r5, [r1, #0]
strh r6, [r1, #0]            // 800e strh r6, [r1, #0]
strh r7, [r1, #0]            // 800f strh r7, [r1, #0]
strh r0, [r2, #0]            // 8010 strh r0, [r2, #0]
strh r1, [r2, #0]            // 8011 strh r1, [r2, #0]
strh r2, [r2, #0]            // 8012 strh r2, [r2, #0]
strh r3, [r2, #0]            // 8013 strh r3, [r2, #0]
strh r4, [r2, #0]            // 8014 strh r4, [r2, #0]
strh r5, [r2, #0]            // 8015 strh r5, [r2, #0]
strh r6, [r2, #0]            // 8016 strh r6, [r2, #0]
strh r7, [r2, #0]            // 8017 strh r7, [r2, #0]
strh r0, [r3, #0]            // 8018 strh r0, [r3, #0]
strh r1, [r3, #0]            // 8019 strh r1, [r3, #0]
strh r2, [r3, #0]            // 801a strh r2, [r3, #0]
strh r3, [r3, #0]            // 801b strh r3, [r3, #0]
strh r4, [r3, #0]            // 801c strh r4, [r3, #0]
strh r5, [r3, #0]            // 801d strh r5, [r3, #0]
strh r6, [r3, #0]            // 801e strh r6, [r3, #0]
strh r7, [r3, #0]            // 801f strh r7, [r3, #0]
strh r0, [r4, #0]            // 8020 strh r0, [r4, #0]
strh r1, [r4, #0]            // 8021 strh r1, [r4, #0]
strh r2, [r4, #0]            // 8022 strh r2, [r4, #0]
strh r3, [r4, #0]            // 8023 strh r3, [r4, #0]
strh r4, [r4, #0]            // 8024 strh r4, [r4, #0]
strh r5, [r4, #0]            // 8025 strh r5, [r4, #0]
strh r6, [r4, #0]            // 8026 strh r6, [r4, #0]
strh r7, [r4, #0]            // 8027 strh r7, [r4, #0]
strh r0, [r5, #0]            // 8028 strh r0, [r5, #0]
strh r1, [r5, #0]            // 8029 strh r1, [r5, #0]
strh r2, [r5, #0]            // 802a strh r2, [r5, #0]
strh r3, [r5, #0]            // 802b strh r3, [r5, #0]
strh r4, [r5, #0]            // 802c strh r4, [r5, #0]
strh r5, [r5, #0]            // 802d strh r5, [r5, #0]
strh r6, [r5, #0]            // 802e strh r6, [r5, #0]
strh r7, [r5, #0]            // 802f strh r7, [r5, #0]
strh r0, [r6, #0]            // 8030 strh r0, [r6, #0]
strh r1, [r6, #0]            // 8031 strh r1, [r6, #0]
strh r2, [r6, #0]            // 8032 strh r2, [r6, #0]
strh r3, [r6, #0]            // 8033 strh r3, [r6, #0]
strh r4, [r6, #0]            // 8034 strh r4, [r6, #0]
strh r5, [r6, #0]            // 8035 strh r5, [r6, #0]
strh r6, [r6, #0]            // 8036 strh r6, [r6, #0]
strh r7, [r6, #0]            // 8037 strh r7, [r6, #0]
strh r0, [r7, #0]            // 8038 strh r0, [r7, #0]
strh r1, [r7, #0]            // 8039 strh r1, [r7, #0]
strh r2, [r7, #0]            // 803a strh r2, [r7, #0]
strh r3, [r7, #0]            // 803b strh r3, [r7, #0]
strh r4, [r7, #0]            // 803c strh r4, [r7, #0]
strh r5, [r7, #0]            // 803d strh r5, [r7, #0]
strh r6, [r7, #0]            // 803e strh r6, [r7, #0]
strh r7, [r7, #0]            // 803f strh r7, [r7, #0]
strh r0, [r0, #2]            // 8040 strh r0, [r0, #2]
strh r1, [r0, #2]            // 8041 strh r1, [r0, #2]
strh r2, [r0, #2]            // 8042 strh r2, [r0, #2]
strh r3, [r0, #2]            // 8043 strh r3, [r0, #2]
strh r4, [r0, #2]            // 8044 strh r4, [r0, #2]
strh r5, [r0, #2]            // 8045 strh r5, [r0, #2]
strh r6, [r0, #2]            // 8046 strh r6, [r0, #2]
strh r7, [r0, #2]            // 8047 strh r7, [r0, #2]
strh r0, [r1, #2]            // 8048 strh r0, [r1, #2]
strh r1, [r1, #2]            // 8049 strh r1, [r1, #2]
strh r2, [r1, #2]            // 804a strh r2, [r1, #2]
strh r3, [r1, #2]            // 804b strh r3, [r1, #2]
strh r4, [r1, #2]            // 804c strh r4, [r1, #2]
strh r5, [r1, #2]            // 804d strh r5, [r1, #2]
strh r6, [r1, #2]            // 804e strh r6, [r1, #2]
strh r7, [r1, #2]            // 804f strh r7, [r1, #2]
strh r0, [r2, #2]            // 8050 strh r0, [r2, #2]
strh r1, [r2, #2]            // 8051 strh r1, [r2, #2]
strh r2, [r2, #2]            // 8052 strh r2, [r2, #2]
strh r3, [r2, #2]            // 8053 strh r3, [r2, #2]
strh r4, [r2, #2]            // 8054 strh r4, [r2, #2]
strh r5, [r2, #2]            // 8055 strh r5, [r2, #2]
strh r6, [r2, #2]            // 8056 strh r6, [r2, #2]
strh r7, [r2, #2]            // 8057 strh r7, [r2, #2]
strh r0, [r3, #2]            // 8058 strh r0, [r3, #2]
strh r1, [r3, #2]            // 8059 strh r1, [r3, #2]
strh r2, [r3, #2]            // 805a strh r2, [r3, #2]
strh r3, [r3, #2]            // 805b strh r3, [r3, #2]
strh r4, [r3, #2]            // 805c strh r4, [r3, #2]
strh r5, [r3, #2]            // 805d strh r5, [r3, #2]
strh r6, [r3, #2]            // 805e strh r6, [r3, #2]
strh r7, [r3, #2]            // 805f strh r7, [r3, #2]
strh r0, [r4, #2]            // 8060 strh r0, [r4, #2]
strh r1, [r4, #2]            // 8061 strh r1, [r4, #2]
strh r2, [r4, #2]            // 8062 strh r2, [r4, #2]
strh r3, [r4, #2]            // 8063 strh r3, [r4, #2]
strh r4, [r4, #2]            // 8064 strh r4, [r4, #2]
strh r5, [r4, #2]            // 8065 strh r5, [r4, #2]
strh r6, [r4, #2]            // 8066 strh r6, [r4, #2]
strh r7, [r4, #2]            // 8067 strh r7, [r4, #2]
strh r0, [r5, #2]            // 8068 strh r0, [r5, #2]
strh r1, [r5, #2]            // 8069 strh r1, [r5, #2]
strh r2, [r5, #2]            // 806a strh r2, [r5, #2]
strh r3, [r5, #2]            // 806b strh r3, [r5, #2]
strh r4, [r5, #2]            // 806c strh r4, [r5, #2]
strh r5, [r5, #2]            // 806d strh r5, [r5, #2]
strh r6, [r5, #2]            // 806e strh r6, [r5, #2]
strh r7, [r5, #2]            // 806f strh r7, [r5, #2]
strh r0, [r6, #2]            // 8070 strh r0, [r6, #2]
strh r1, [r6, #2]            // 8071 strh r1, [r6, #2]
strh r2, [r6, #2]            // 8072 strh r2, [r6, #2]
strh r3, [r6, #2]            // 8073 strh r3, [r6, #2]
strh r4, [r6, #2]            // 8074 strh r4, [r6, #2]
strh r5, [r6, #2]            // 8075 strh r5, [r6, #2]
strh r6, [r6, #2]            // 8076 strh r6, [r6, #2]
strh r7, [r6, #2]            // 8077 strh r7, [r6, #2]
strh r0, [r7, #2]            // 8078 strh r0, [r7, #2]
strh r1, [r7, #2]            // 8079 strh r1, [r7, #2]
strh r2, [r7, #2]            // 807a strh r2, [r7, #2]
strh r3, [r7, #2]            // 807b strh r3, [r7, #2]
strh r4, [r7, #2]            // 807c strh r4, [r7, #2]
strh r5, [r7, #2]            // 807d strh r5, [r7, #2]
strh r6, [r7, #2]            // 807e strh r6, [r7, #2]
strh r7, [r7, #2]            // 807f strh r7, [r7, #2]
strh r0, [r0, #62] // 0x3e    // 87c0 strh r0, [r0, #62] // 0x3e
strh r1, [r0, #62] // 0x3e    // 87c1 strh r1, [r0, #62] // 0x3e
strh r2, [r0, #62] // 0x3e    // 87c2 strh r2, [r0, #62] // 0x3e
strh r3, [r0, #62] // 0x3e    // 87c3 strh r3, [r0, #62] // 0x3e
strh r4, [r0, #62] // 0x3e    // 87c4 strh r4, [r0, #62] // 0x3e
strh r5, [r0, #62] // 0x3e    // 87c5 strh r5, [r0, #62] // 0x3e
strh r6, [r0, #62] // 0x3e    // 87c6 strh r6, [r0, #62] // 0x3e
strh r7, [r0, #62] // 0x3e    // 87c7 strh r7, [r0, #62] // 0x3e
strh r0, [r1, #62] // 0x3e    // 87c8 strh r0, [r1, #62] // 0x3e
strh r1, [r1, #62] // 0x3e    // 87c9 strh r1, [r1, #62] // 0x3e
strh r2, [r1, #62] // 0x3e    // 87ca strh r2, [r1, #62] // 0x3e
strh r3, [r1, #62] // 0x3e    // 87cb strh r3, [r1, #62] // 0x3e
strh r4, [r1, #62] // 0x3e    // 87cc strh r4, [r1, #62] // 0x3e
strh r5, [r1, #62] // 0x3e    // 87cd strh r5, [r1, #62] // 0x3e
strh r6, [r1, #62] // 0x3e    // 87ce strh r6, [r1, #62] // 0x3e
strh r7, [r1, #62] // 0x3e    // 87cf strh r7, [r1, #62] // 0x3e
strh r0, [r2, #62] // 0x3e    // 87d0 strh r0, [r2, #62] // 0x3e
strh r1, [r2, #62] // 0x3e    // 87d1 strh r1, [r2, #62] // 0x3e
strh r2, [r2, #62] // 0x3e    // 87d2 strh r2, [r2, #62] // 0x3e
strh r3, [r2, #62] // 0x3e    // 87d3 strh r3, [r2, #62] // 0x3e
strh r4, [r2, #62] // 0x3e    // 87d4 strh r4, [r2, #62] // 0x3e
strh r5, [r2, #62] // 0x3e    // 87d5 strh r5, [r2, #62] // 0x3e
strh r6, [r2, #62] // 0x3e    // 87d6 strh r6, [r2, #62] // 0x3e
strh r7, [r2, #62] // 0x3e    // 87d7 strh r7, [r2, #62] // 0x3e
strh r0, [r3, #62] // 0x3e    // 87d8 strh r0, [r3, #62] // 0x3e
strh r1, [r3, #62] // 0x3e    // 87d9 strh r1, [r3, #62] // 0x3e
strh r2, [r3, #62] // 0x3e    // 87da strh r2, [r3, #62] // 0x3e
strh r3, [r3, #62] // 0x3e    // 87db strh r3, [r3, #62] // 0x3e
strh r4, [r3, #62] // 0x3e    // 87dc strh r4, [r3, #62] // 0x3e
strh r5, [r3, #62] // 0x3e    // 87dd strh r5, [r3, #62] // 0x3e
strh r6, [r3, #62] // 0x3e    // 87de strh r6, [r3, #62] // 0x3e
strh r7, [r3, #62] // 0x3e    // 87df strh r7, [r3, #62] // 0x3e
strh r0, [r4, #62] // 0x3e    // 87e0 strh r0, [r4, #62] // 0x3e
strh r1, [r4, #62] // 0x3e    // 87e1 strh r1, [r4, #62] // 0x3e
strh r2, [r4, #62] // 0x3e    // 87e2 strh r2, [r4, #62] // 0x3e
strh r3, [r4, #62] // 0x3e    // 87e3 strh r3, [r4, #62] // 0x3e
strh r4, [r4, #62] // 0x3e    // 87e4 strh r4, [r4, #62] // 0x3e
strh r5, [r4, #62] // 0x3e    // 87e5 strh r5, [r4, #62] // 0x3e
strh r6, [r4, #62] // 0x3e    // 87e6 strh r6, [r4, #62] // 0x3e
strh r7, [r4, #62] // 0x3e    // 87e7 strh r7, [r4, #62] // 0x3e
strh r0, [r5, #62] // 0x3e    // 87e8 strh r0, [r5, #62] // 0x3e
strh r1, [r5, #62] // 0x3e    // 87e9 strh r1, [r5, #62] // 0x3e
strh r2, [r5, #62] // 0x3e    // 87ea strh r2, [r5, #62] // 0x3e
strh r3, [r5, #62] // 0x3e    // 87eb strh r3, [r5, #62] // 0x3e
strh r4, [r5, #62] // 0x3e    // 87ec strh r4, [r5, #62] // 0x3e
strh r5, [r5, #62] // 0x3e    // 87ed strh r5, [r5, #62] // 0x3e
strh r6, [r5, #62] // 0x3e    // 87ee strh r6, [r5, #62] // 0x3e
strh r7, [r5, #62] // 0x3e    // 87ef strh r7, [r5, #62] // 0x3e
strh r0, [r6, #62] // 0x3e    // 87f0 strh r0, [r6, #62] // 0x3e
strh r1, [r6, #62] // 0x3e    // 87f1 strh r1, [r6, #62] // 0x3e
strh r2, [r6, #62] // 0x3e    // 87f2 strh r2, [r6, #62] // 0x3e
strh r3, [r6, #62] // 0x3e    // 87f3 strh r3, [r6, #62] // 0x3e
strh r4, [r6, #62] // 0x3e    // 87f4 strh r4, [r6, #62] // 0x3e
strh r5, [r6, #62] // 0x3e    // 87f5 strh r5, [r6, #62] // 0x3e
strh r6, [r6, #62] // 0x3e    // 87f6 strh r6, [r6, #62] // 0x3e
strh r7, [r6, #62] // 0x3e    // 87f7 strh r7, [r6, #62] // 0x3e
strh r0, [r7, #62] // 0x3e    // 87f8 strh r0, [r7, #62] // 0x3e
strh r1, [r7, #62] // 0x3e    // 87f9 strh r1, [r7, #62] // 0x3e
strh r2, [r7, #62] // 0x3e    // 87fa strh r2, [r7, #62] // 0x3e
strh r3, [r7, #62] // 0x3e    // 87fb strh r3, [r7, #62] // 0x3e
strh r4, [r7, #62] // 0x3e    // 87fc strh r4, [r7, #62] // 0x3e
strh r5, [r7, #62] // 0x3e    // 87fd strh r5, [r7, #62] // 0x3e
strh r6, [r7, #62] // 0x3e    // 87fe strh r6, [r7, #62] // 0x3e
strh r7, [r7, #62] // 0x3e    // 87ff strh r7, [r7, #62] // 0x3e

ldrh r0, [r0, #0]            // 8800 ldrh r0, [r0, #0]
ldrh r1, [r0, #0]            // 8801 ldrh r1, [r0, #0]
ldrh r2, [r0, #0]            // 8802 ldrh r2, [r0, #0]
ldrh r3, [r0, #0]            // 8803 ldrh r3, [r0, #0]
ldrh r4, [r0, #0]            // 8804 ldrh r4, [r0, #0]
ldrh r5, [r0, #0]            // 8805 ldrh r5, [r0, #0]
ldrh r6, [r0, #0]            // 8806 ldrh r6, [r0, #0]
ldrh r7, [r0, #0]            // 8807 ldrh r7, [r0, #0]
ldrh r0, [r1, #0]            // 8808 ldrh r0, [r1, #0]
ldrh r1, [r1, #0]            // 8809 ldrh r1, [r1, #0]
ldrh r2, [r1, #0]            // 880a ldrh r2, [r1, #0]
ldrh r3, [r1, #0]            // 880b ldrh r3, [r1, #0]
ldrh r4, [r1, #0]            // 880c ldrh r4, [r1, #0]
ldrh r5, [r1, #0]            // 880d ldrh r5, [r1, #0]
ldrh r6, [r1, #0]            // 880e ldrh r6, [r1, #0]
ldrh r7, [r1, #0]            // 880f ldrh r7, [r1, #0]
ldrh r0, [r2, #0]            // 8810 ldrh r0, [r2, #0]
ldrh r1, [r2, #0]            // 8811 ldrh r1, [r2, #0]
ldrh r2, [r2, #0]            // 8812 ldrh r2, [r2, #0]
ldrh r3, [r2, #0]            // 8813 ldrh r3, [r2, #0]
ldrh r4, [r2, #0]            // 8814 ldrh r4, [r2, #0]
ldrh r5, [r2, #0]            // 8815 ldrh r5, [r2, #0]
ldrh r6, [r2, #0]            // 8816 ldrh r6, [r2, #0]
ldrh r7, [r2, #0]            // 8817 ldrh r7, [r2, #0]
ldrh r0, [r3, #0]            // 8818 ldrh r0, [r3, #0]
ldrh r1, [r3, #0]            // 8819 ldrh r1, [r3, #0]
ldrh r2, [r3, #0]            // 881a ldrh r2, [r3, #0]
ldrh r3, [r3, #0]            // 881b ldrh r3, [r3, #0]
ldrh r4, [r3, #0]            // 881c ldrh r4, [r3, #0]
ldrh r5, [r3, #0]            // 881d ldrh r5, [r3, #0]
ldrh r6, [r3, #0]            // 881e ldrh r6, [r3, #0]
ldrh r7, [r3, #0]            // 881f ldrh r7, [r3, #0]
ldrh r0, [r4, #0]            // 8820 ldrh r0, [r4, #0]
ldrh r1, [r4, #0]            // 8821 ldrh r1, [r4, #0]
ldrh r2, [r4, #0]            // 8822 ldrh r2, [r4, #0]
ldrh r3, [r4, #0]            // 8823 ldrh r3, [r4, #0]
ldrh r4, [r4, #0]            // 8824 ldrh r4, [r4, #0]
ldrh r5, [r4, #0]            // 8825 ldrh r5, [r4, #0]
ldrh r6, [r4, #0]            // 8826 ldrh r6, [r4, #0]
ldrh r7, [r4, #0]            // 8827 ldrh r7, [r4, #0]
ldrh r0, [r5, #0]            // 8828 ldrh r0, [r5, #0]
ldrh r1, [r5, #0]            // 8829 ldrh r1, [r5, #0]
ldrh r2, [r5, #0]            // 882a ldrh r2, [r5, #0]
ldrh r3, [r5, #0]            // 882b ldrh r3, [r5, #0]
ldrh r4, [r5, #0]            // 882c ldrh r4, [r5, #0]
ldrh r5, [r5, #0]            // 882d ldrh r5, [r5, #0]
ldrh r6, [r5, #0]            // 882e ldrh r6, [r5, #0]
ldrh r7, [r5, #0]            // 882f ldrh r7, [r5, #0]
ldrh r0, [r6, #0]            // 8830 ldrh r0, [r6, #0]
ldrh r1, [r6, #0]            // 8831 ldrh r1, [r6, #0]
ldrh r2, [r6, #0]            // 8832 ldrh r2, [r6, #0]
ldrh r3, [r6, #0]            // 8833 ldrh r3, [r6, #0]
ldrh r4, [r6, #0]            // 8834 ldrh r4, [r6, #0]
ldrh r5, [r6, #0]            // 8835 ldrh r5, [r6, #0]
ldrh r6, [r6, #0]            // 8836 ldrh r6, [r6, #0]
ldrh r7, [r6, #0]            // 8837 ldrh r7, [r6, #0]
ldrh r0, [r7, #0]            // 8838 ldrh r0, [r7, #0]
ldrh r1, [r7, #0]            // 8839 ldrh r1, [r7, #0]
ldrh r2, [r7, #0]            // 883a ldrh r2, [r7, #0]
ldrh r3, [r7, #0]            // 883b ldrh r3, [r7, #0]
ldrh r4, [r7, #0]            // 883c ldrh r4, [r7, #0]
ldrh r5, [r7, #0]            // 883d ldrh r5, [r7, #0]
ldrh r6, [r7, #0]            // 883e ldrh r6, [r7, #0]
ldrh r7, [r7, #0]            // 883f ldrh r7, [r7, #0]
ldrh r0, [r0, #2]            // 8840 ldrh r0, [r0, #2]
ldrh r1, [r0, #2]            // 8841 ldrh r1, [r0, #2]
ldrh r2, [r0, #2]            // 8842 ldrh r2, [r0, #2]
ldrh r3, [r0, #2]            // 8843 ldrh r3, [r0, #2]
ldrh r4, [r0, #2]            // 8844 ldrh r4, [r0, #2]
ldrh r5, [r0, #2]            // 8845 ldrh r5, [r0, #2]
ldrh r6, [r0, #2]            // 8846 ldrh r6, [r0, #2]
ldrh r7, [r0, #2]            // 8847 ldrh r7, [r0, #2]
ldrh r0, [r1, #2]            // 8848 ldrh r0, [r1, #2]
ldrh r1, [r1, #2]            // 8849 ldrh r1, [r1, #2]
ldrh r2, [r1, #2]            // 884a ldrh r2, [r1, #2]
ldrh r3, [r1, #2]            // 884b ldrh r3, [r1, #2]
ldrh r4, [r1, #2]            // 884c ldrh r4, [r1, #2]
ldrh r5, [r1, #2]            // 884d ldrh r5, [r1, #2]
ldrh r6, [r1, #2]            // 884e ldrh r6, [r1, #2]
ldrh r7, [r1, #2]            // 884f ldrh r7, [r1, #2]
ldrh r0, [r2, #2]            // 8850 ldrh r0, [r2, #2]
ldrh r1, [r2, #2]            // 8851 ldrh r1, [r2, #2]
ldrh r2, [r2, #2]            // 8852 ldrh r2, [r2, #2]
ldrh r3, [r2, #2]            // 8853 ldrh r3, [r2, #2]
ldrh r4, [r2, #2]            // 8854 ldrh r4, [r2, #2]
ldrh r5, [r2, #2]            // 8855 ldrh r5, [r2, #2]
ldrh r6, [r2, #2]            // 8856 ldrh r6, [r2, #2]
ldrh r7, [r2, #2]            // 8857 ldrh r7, [r2, #2]
ldrh r0, [r3, #2]            // 8858 ldrh r0, [r3, #2]
ldrh r1, [r3, #2]            // 8859 ldrh r1, [r3, #2]
ldrh r2, [r3, #2]            // 885a ldrh r2, [r3, #2]
ldrh r3, [r3, #2]            // 885b ldrh r3, [r3, #2]
ldrh r4, [r3, #2]            // 885c ldrh r4, [r3, #2]
ldrh r5, [r3, #2]            // 885d ldrh r5, [r3, #2]
ldrh r6, [r3, #2]            // 885e ldrh r6, [r3, #2]
ldrh r7, [r3, #2]            // 885f ldrh r7, [r3, #2]
ldrh r0, [r4, #2]            // 8860 ldrh r0, [r4, #2]
ldrh r1, [r4, #2]            // 8861 ldrh r1, [r4, #2]
ldrh r2, [r4, #2]            // 8862 ldrh r2, [r4, #2]
ldrh r3, [r4, #2]            // 8863 ldrh r3, [r4, #2]
ldrh r4, [r4, #2]            // 8864 ldrh r4, [r4, #2]
ldrh r5, [r4, #2]            // 8865 ldrh r5, [r4, #2]
ldrh r6, [r4, #2]            // 8866 ldrh r6, [r4, #2]
ldrh r7, [r4, #2]            // 8867 ldrh r7, [r4, #2]
ldrh r0, [r5, #2]            // 8868 ldrh r0, [r5, #2]
ldrh r1, [r5, #2]            // 8869 ldrh r1, [r5, #2]
ldrh r2, [r5, #2]            // 886a ldrh r2, [r5, #2]
ldrh r3, [r5, #2]            // 886b ldrh r3, [r5, #2]
ldrh r4, [r5, #2]            // 886c ldrh r4, [r5, #2]
ldrh r5, [r5, #2]            // 886d ldrh r5, [r5, #2]
ldrh r6, [r5, #2]            // 886e ldrh r6, [r5, #2]
ldrh r7, [r5, #2]            // 886f ldrh r7, [r5, #2]
ldrh r0, [r6, #2]            // 8870 ldrh r0, [r6, #2]
ldrh r1, [r6, #2]            // 8871 ldrh r1, [r6, #2]
ldrh r2, [r6, #2]            // 8872 ldrh r2, [r6, #2]
ldrh r3, [r6, #2]            // 8873 ldrh r3, [r6, #2]
ldrh r4, [r6, #2]            // 8874 ldrh r4, [r6, #2]
ldrh r5, [r6, #2]            // 8875 ldrh r5, [r6, #2]
ldrh r6, [r6, #2]            // 8876 ldrh r6, [r6, #2]
ldrh r7, [r6, #2]            // 8877 ldrh r7, [r6, #2]
ldrh r0, [r7, #2]            // 8878 ldrh r0, [r7, #2]
ldrh r1, [r7, #2]            // 8879 ldrh r1, [r7, #2]
ldrh r2, [r7, #2]            // 887a ldrh r2, [r7, #2]
ldrh r3, [r7, #2]            // 887b ldrh r3, [r7, #2]
ldrh r4, [r7, #2]            // 887c ldrh r4, [r7, #2]
ldrh r5, [r7, #2]            // 887d ldrh r5, [r7, #2]
ldrh r6, [r7, #2]            // 887e ldrh r6, [r7, #2]
ldrh r7, [r7, #2]            // 887f ldrh r7, [r7, #2]
ldrh r0, [r0, #62] // 0x3e    // 8fc0 ldrh r0, [r0, #62] // 0x3e
ldrh r1, [r0, #62] // 0x3e    // 8fc1 ldrh r1, [r0, #62] // 0x3e
ldrh r2, [r0, #62] // 0x3e    // 8fc2 ldrh r2, [r0, #62] // 0x3e
ldrh r3, [r0, #62] // 0x3e    // 8fc3 ldrh r3, [r0, #62] // 0x3e
ldrh r4, [r0, #62] // 0x3e    // 8fc4 ldrh r4, [r0, #62] // 0x3e
ldrh r5, [r0, #62] // 0x3e    // 8fc5 ldrh r5, [r0, #62] // 0x3e
ldrh r6, [r0, #62] // 0x3e    // 8fc6 ldrh r6, [r0, #62] // 0x3e
ldrh r7, [r0, #62] // 0x3e    // 8fc7 ldrh r7, [r0, #62] // 0x3e
ldrh r0, [r1, #62] // 0x3e    // 8fc8 ldrh r0, [r1, #62] // 0x3e
ldrh r1, [r1, #62] // 0x3e    // 8fc9 ldrh r1, [r1, #62] // 0x3e
ldrh r2, [r1, #62] // 0x3e    // 8fca ldrh r2, [r1, #62] // 0x3e
ldrh r3, [r1, #62] // 0x3e    // 8fcb ldrh r3, [r1, #62] // 0x3e
ldrh r4, [r1, #62] // 0x3e    // 8fcc ldrh r4, [r1, #62] // 0x3e
ldrh r5, [r1, #62] // 0x3e    // 8fcd ldrh r5, [r1, #62] // 0x3e
ldrh r6, [r1, #62] // 0x3e    // 8fce ldrh r6, [r1, #62] // 0x3e
ldrh r7, [r1, #62] // 0x3e    // 8fcf ldrh r7, [r1, #62] // 0x3e
ldrh r0, [r2, #62] // 0x3e    // 8fd0 ldrh r0, [r2, #62] // 0x3e
ldrh r1, [r2, #62] // 0x3e    // 8fd1 ldrh r1, [r2, #62] // 0x3e
ldrh r2, [r2, #62] // 0x3e    // 8fd2 ldrh r2, [r2, #62] // 0x3e
ldrh r3, [r2, #62] // 0x3e    // 8fd3 ldrh r3, [r2, #62] // 0x3e
ldrh r4, [r2, #62] // 0x3e    // 8fd4 ldrh r4, [r2, #62] // 0x3e
ldrh r5, [r2, #62] // 0x3e    // 8fd5 ldrh r5, [r2, #62] // 0x3e
ldrh r6, [r2, #62] // 0x3e    // 8fd6 ldrh r6, [r2, #62] // 0x3e
ldrh r7, [r2, #62] // 0x3e    // 8fd7 ldrh r7, [r2, #62] // 0x3e
ldrh r0, [r3, #62] // 0x3e    // 8fd8 ldrh r0, [r3, #62] // 0x3e
ldrh r1, [r3, #62] // 0x3e    // 8fd9 ldrh r1, [r3, #62] // 0x3e
ldrh r2, [r3, #62] // 0x3e    // 8fda ldrh r2, [r3, #62] // 0x3e
ldrh r3, [r3, #62] // 0x3e    // 8fdb ldrh r3, [r3, #62] // 0x3e
ldrh r4, [r3, #62] // 0x3e    // 8fdc ldrh r4, [r3, #62] // 0x3e
ldrh r5, [r3, #62] // 0x3e    // 8fdd ldrh r5, [r3, #62] // 0x3e
ldrh r6, [r3, #62] // 0x3e    // 8fde ldrh r6, [r3, #62] // 0x3e
ldrh r7, [r3, #62] // 0x3e    // 8fdf ldrh r7, [r3, #62] // 0x3e
ldrh r0, [r4, #62] // 0x3e    // 8fe0 ldrh r0, [r4, #62] // 0x3e
ldrh r1, [r4, #62] // 0x3e    // 8fe1 ldrh r1, [r4, #62] // 0x3e
ldrh r2, [r4, #62] // 0x3e    // 8fe2 ldrh r2, [r4, #62] // 0x3e
ldrh r3, [r4, #62] // 0x3e    // 8fe3 ldrh r3, [r4, #62] // 0x3e
ldrh r4, [r4, #62] // 0x3e    // 8fe4 ldrh r4, [r4, #62] // 0x3e
ldrh r5, [r4, #62] // 0x3e    // 8fe5 ldrh r5, [r4, #62] // 0x3e
ldrh r6, [r4, #62] // 0x3e    // 8fe6 ldrh r6, [r4, #62] // 0x3e
ldrh r7, [r4, #62] // 0x3e    // 8fe7 ldrh r7, [r4, #62] // 0x3e
ldrh r0, [r5, #62] // 0x3e    // 8fe8 ldrh r0, [r5, #62] // 0x3e
ldrh r1, [r5, #62] // 0x3e    // 8fe9 ldrh r1, [r5, #62] // 0x3e
ldrh r2, [r5, #62] // 0x3e    // 8fea ldrh r2, [r5, #62] // 0x3e
ldrh r3, [r5, #62] // 0x3e    // 8feb ldrh r3, [r5, #62] // 0x3e
ldrh r4, [r5, #62] // 0x3e    // 8fec ldrh r4, [r5, #62] // 0x3e
ldrh r5, [r5, #62] // 0x3e    // 8fed ldrh r5, [r5, #62] // 0x3e
ldrh r6, [r5, #62] // 0x3e    // 8fee ldrh r6, [r5, #62] // 0x3e
ldrh r7, [r5, #62] // 0x3e    // 8fef ldrh r7, [r5, #62] // 0x3e
ldrh r0, [r6, #62] // 0x3e    // 8ff0 ldrh r0, [r6, #62] // 0x3e
ldrh r1, [r6, #62] // 0x3e    // 8ff1 ldrh r1, [r6, #62] // 0x3e
ldrh r2, [r6, #62] // 0x3e    // 8ff2 ldrh r2, [r6, #62] // 0x3e
ldrh r3, [r6, #62] // 0x3e    // 8ff3 ldrh r3, [r6, #62] // 0x3e
ldrh r4, [r6, #62] // 0x3e    // 8ff4 ldrh r4, [r6, #62] // 0x3e
ldrh r5, [r6, #62] // 0x3e    // 8ff5 ldrh r5, [r6, #62] // 0x3e
ldrh r6, [r6, #62] // 0x3e    // 8ff6 ldrh r6, [r6, #62] // 0x3e
ldrh r7, [r6, #62] // 0x3e    // 8ff7 ldrh r7, [r6, #62] // 0x3e
ldrh r0, [r7, #62] // 0x3e    // 8ff8 ldrh r0, [r7, #62] // 0x3e
ldrh r1, [r7, #62] // 0x3e    // 8ff9 ldrh r1, [r7, #62] // 0x3e
ldrh r2, [r7, #62] // 0x3e    // 8ffa ldrh r2, [r7, #62] // 0x3e
ldrh r3, [r7, #62] // 0x3e    // 8ffb ldrh r3, [r7, #62] // 0x3e
ldrh r4, [r7, #62] // 0x3e    // 8ffc ldrh r4, [r7, #62] // 0x3e
ldrh r5, [r7, #62] // 0x3e    // 8ffd ldrh r5, [r7, #62] // 0x3e
ldrh r6, [r7, #62] // 0x3e    // 8ffe ldrh r6, [r7, #62] // 0x3e
ldrh r7, [r7, #62] // 0x3e    // 8fff ldrh r7, [r7, #62] // 0x3e

str r0, [sp, #0]             // 9000 str r0, [sp, #0]
str r0, [sp, #4]             // 9001 str r0, [sp, #4]
str r0, [sp, #1020] // 0x3fc  // 90ff str r0, [sp, #1020] // 0x3fc
str r1, [sp, #0]             // 9100 str r1, [sp, #0]
str r1, [sp, #4]             // 9101 str r1, [sp, #4]
str r1, [sp, #1020] // 0x3fc  // 91ff str r1, [sp, #1020] // 0x3fc
str r2, [sp, #0]             // 9200 str r2, [sp, #0]
str r2, [sp, #4]             // 9201 str r2, [sp, #4]
str r2, [sp, #1020] // 0x3fc  // 92ff str r2, [sp, #1020] // 0x3fc
str r3, [sp, #0]             // 9300 str r3, [sp, #0]
str r3, [sp, #4]             // 9301 str r3, [sp, #4]
str r3, [sp, #1020] // 0x3fc  // 93ff str r3, [sp, #1020] // 0x3fc
str r4, [sp, #0]             // 9400 str r4, [sp, #0]
str r4, [sp, #4]             // 9401 str r4, [sp, #4]
str r4, [sp, #1020] // 0x3fc  // 94ff str r4, [sp, #1020] // 0x3fc
str r5, [sp, #0]             // 9500 str r5, [sp, #0]
str r5, [sp, #4]             // 9501 str r5, [sp, #4]
str r5, [sp, #1020] // 0x3fc  // 95ff str r5, [sp, #1020] // 0x3fc
str r6, [sp, #0]             // 9600 str r6, [sp, #0]
str r6, [sp, #4]             // 9601 str r6, [sp, #4]
str r6, [sp, #1020] // 0x3fc  // 96ff str r6, [sp, #1020] // 0x3fc
str r7, [sp, #0]             // 9700 str r7, [sp, #0]
str r7, [sp, #4]             // 9701 str r7, [sp, #4]
str r7, [sp, #1020] // 0x3fc  // 97ff str r7, [sp, #1020] // 0x3fc

ldr r0, [sp, #0]             // 9800 ldr r0, [sp, #0]
ldr r0, [sp, #4]             // 9801 ldr r0, [sp, #4]
ldr r0, [sp, #1020] // 0x3fc  // 98ff ldr r0, [sp, #1020] // 0x3fc
ldr r1, [sp, #0]             // 9900 ldr r1, [sp, #0]
ldr r1, [sp, #4]             // 9901 ldr r1, [sp, #4]
ldr r1, [sp, #1020] // 0x3fc  // 99ff ldr r1, [sp, #1020] // 0x3fc
ldr r2, [sp, #0]             // 9a00 ldr r2, [sp, #0]
ldr r2, [sp, #4]             // 9a01 ldr r2, [sp, #4]
ldr r2, [sp, #1020] // 0x3fc  // 9aff ldr r2, [sp, #1020] // 0x3fc
ldr r3, [sp, #0]             // 9b00 ldr r3, [sp, #0]
ldr r3, [sp, #4]             // 9b01 ldr r3, [sp, #4]
ldr r3, [sp, #1020] // 0x3fc  // 9bff ldr r3, [sp, #1020] // 0x3fc
ldr r4, [sp, #0]             // 9c00 ldr r4, [sp, #0]
ldr r4, [sp, #4]             // 9c01 ldr r4, [sp, #4]
ldr r4, [sp, #1020] // 0x3fc  // 9cff ldr r4, [sp, #1020] // 0x3fc
ldr r5, [sp, #0]             // 9d00 ldr r5, [sp, #0]
ldr r5, [sp, #4]             // 9d01 ldr r5, [sp, #4]
ldr r5, [sp, #1020] // 0x3fc  // 9dff ldr r5, [sp, #1020] // 0x3fc
ldr r6, [sp, #0]             // 9e00 ldr r6, [sp, #0]
ldr r6, [sp, #4]             // 9e01 ldr r6, [sp, #4]
ldr r6, [sp, #1020] // 0x3fc  // 9eff ldr r6, [sp, #1020] // 0x3fc
ldr r7, [sp, #0]             // 9f00 ldr r7, [sp, #0]
ldr r7, [sp, #4]             // 9f01 ldr r7, [sp, #4]
ldr r7, [sp, #1020] // 0x3fc  // 9fff ldr r7, [sp, #1020] // 0x3fc

add r0, pc, #0 // (adr r0, 0x0// a000 add r0, pc, #0 // (adr r0, 0x00014004)
add r0, pc, #4 // (adr r0, 0x0// a001 add r0, pc, #4 // (adr r0, 0x00014008)
add r0, pc, #1020 // (adr r0, // a0ff add r0, pc, #1020 // (adr r0, 0x000145fc)
add r1, pc, #0 // (adr r1, 0x0// a100 add r1, pc, #0 // (adr r1, 0x00014204)
add r1, pc, #4 // (adr r1, 0x0// a101 add r1, pc, #4 // (adr r1, 0x00014208)
add r1, pc, #1020 // (adr r1, // a1ff add r1, pc, #1020 // (adr r1, 0x000147fc)
add r2, pc, #0 // (adr r2, 0x0// a200 add r2, pc, #0 // (adr r2, 0x00014404)
add r2, pc, #4 // (adr r2, 0x0// a201 add r2, pc, #4 // (adr r2, 0x00014408)
add r2, pc, #1020 // (adr r2, // a2ff add r2, pc, #1020 // (adr r2, 0x000149fc)
add r3, pc, #0 // (adr r3, 0x0// a300 add r3, pc, #0 // (adr r3, 0x00014604)
add r3, pc, #4 // (adr r3, 0x0// a301 add r3, pc, #4 // (adr r3, 0x00014608)
add r3, pc, #1020 // (adr r3, // a3ff add r3, pc, #1020 // (adr r3, 0x00014bfc)
add r4, pc, #0 // (adr r4, 0x0// a400 add r4, pc, #0 // (adr r4, 0x00014804)
add r4, pc, #4 // (adr r4, 0x0// a401 add r4, pc, #4 // (adr r4, 0x00014808)
add r4, pc, #1020 // (adr r4, // a4ff add r4, pc, #1020 // (adr r4, 0x00014dfc)
add r5, pc, #0 // (adr r5, 0x0// a500 add r5, pc, #0 // (adr r5, 0x00014a04)
add r5, pc, #4 // (adr r5, 0x0// a501 add r5, pc, #4 // (adr r5, 0x00014a08)
add r5, pc, #1020 // (adr r5, // a5ff add r5, pc, #1020 // (adr r5, 0x00014ffc)
add r6, pc, #0 // (adr r6, 0x0// a600 add r6, pc, #0 // (adr r6, 0x00014c04)
add r6, pc, #4 // (adr r6, 0x0// a601 add r6, pc, #4 // (adr r6, 0x00014c08)
add r6, pc, #1020 // (adr r6, // a6ff add r6, pc, #1020 // (adr r6, 0x000151fc)
add r7, pc, #0 // (adr r7, 0x0// a700 add r7, pc, #0 // (adr r7, 0x00014e04)
add r7, pc, #4 // (adr r7, 0x0// a701 add r7, pc, #4 // (adr r7, 0x00014e08)
add r7, pc, #1020 // (adr r7, // a7ff add r7, pc, #1020 // (adr r7, 0x000153fc)

add r0, sp, #0               // a800 add r0, sp, #0
add r0, sp, #4               // a801 add r0, sp, #4
add r0, sp, #1020 // 0x3fc    // a8ff add r0, sp, #1020 // 0x3fc
add r1, sp, #0               // a900 add r1, sp, #0
add r1, sp, #4               // a901 add r1, sp, #4
add r1, sp, #1020 // 0x3fc    // a9ff add r1, sp, #1020 // 0x3fc
add r2, sp, #0               // aa00 add r2, sp, #0
add r2, sp, #4               // aa01 add r2, sp, #4
add r2, sp, #1020 // 0x3fc    // aaff add r2, sp, #1020 // 0x3fc
add r3, sp, #0               // ab00 add r3, sp, #0
add r3, sp, #4               // ab01 add r3, sp, #4
add r3, sp, #1020 // 0x3fc    // abff add r3, sp, #1020 // 0x3fc
add r4, sp, #0               // ac00 add r4, sp, #0
add r4, sp, #4               // ac01 add r4, sp, #4
add r4, sp, #1020 // 0x3fc    // acff add r4, sp, #1020 // 0x3fc
add r5, sp, #0               // ad00 add r5, sp, #0
add r5, sp, #4               // ad01 add r5, sp, #4
add r5, sp, #1020 // 0x3fc    // adff add r5, sp, #1020 // 0x3fc
add r6, sp, #0               // ae00 add r6, sp, #0
add r6, sp, #4               // ae01 add r6, sp, #4
add r6, sp, #1020 // 0x3fc    // aeff add r6, sp, #1020 // 0x3fc
add r7, sp, #0               // af00 add r7, sp, #0
add r7, sp, #4               // af01 add r7, sp, #4
add r7, sp, #1020 // 0x3fc    // afff add r7, sp, #1020 // 0x3fc
add sp, #0                   // b000 add sp, #0
add sp, #4                   // b001 add sp, #4
add sp, #508 // 0x1fc         // b07f add sp, #508 // 0x1fc

sub sp, #0                   // b080 sub sp, #0
sub sp, #4                   // b081 sub sp, #4
sub sp, #508 // 0x1fc         // b0ff sub sp, #508 // 0x1fc

sxth r0, r0                  // b200 sxth r0, r0
sxth r1, r0                  // b201 sxth r1, r0
sxth r2, r0                  // b202 sxth r2, r0
sxth r3, r0                  // b203 sxth r3, r0
sxth r4, r0                  // b204 sxth r4, r0
sxth r5, r0                  // b205 sxth r5, r0
sxth r6, r0                  // b206 sxth r6, r0
sxth r7, r0                  // b207 sxth r7, r0
sxth r0, r1                  // b208 sxth r0, r1
sxth r1, r1                  // b209 sxth r1, r1
sxth r2, r1                  // b20a sxth r2, r1
sxth r3, r1                  // b20b sxth r3, r1
sxth r4, r1                  // b20c sxth r4, r1
sxth r5, r1                  // b20d sxth r5, r1
sxth r6, r1                  // b20e sxth r6, r1
sxth r7, r1                  // b20f sxth r7, r1
sxth r0, r2                  // b210 sxth r0, r2
sxth r1, r2                  // b211 sxth r1, r2
sxth r2, r2                  // b212 sxth r2, r2
sxth r3, r2                  // b213 sxth r3, r2
sxth r4, r2                  // b214 sxth r4, r2
sxth r5, r2                  // b215 sxth r5, r2
sxth r6, r2                  // b216 sxth r6, r2
sxth r7, r2                  // b217 sxth r7, r2
sxth r0, r3                  // b218 sxth r0, r3
sxth r1, r3                  // b219 sxth r1, r3
sxth r2, r3                  // b21a sxth r2, r3
sxth r3, r3                  // b21b sxth r3, r3
sxth r4, r3                  // b21c sxth r4, r3
sxth r5, r3                  // b21d sxth r5, r3
sxth r6, r3                  // b21e sxth r6, r3
sxth r7, r3                  // b21f sxth r7, r3
sxth r0, r4                  // b220 sxth r0, r4
sxth r1, r4                  // b221 sxth r1, r4
sxth r2, r4                  // b222 sxth r2, r4
sxth r3, r4                  // b223 sxth r3, r4
sxth r4, r4                  // b224 sxth r4, r4
sxth r5, r4                  // b225 sxth r5, r4
sxth r6, r4                  // b226 sxth r6, r4
sxth r7, r4                  // b227 sxth r7, r4
sxth r0, r5                  // b228 sxth r0, r5
sxth r1, r5                  // b229 sxth r1, r5
sxth r2, r5                  // b22a sxth r2, r5
sxth r3, r5                  // b22b sxth r3, r5
sxth r4, r5                  // b22c sxth r4, r5
sxth r5, r5                  // b22d sxth r5, r5
sxth r6, r5                  // b22e sxth r6, r5
sxth r7, r5                  // b22f sxth r7, r5
sxth r0, r6                  // b230 sxth r0, r6
sxth r1, r6                  // b231 sxth r1, r6
sxth r2, r6                  // b232 sxth r2, r6
sxth r3, r6                  // b233 sxth r3, r6
sxth r4, r6                  // b234 sxth r4, r6
sxth r5, r6                  // b235 sxth r5, r6
sxth r6, r6                  // b236 sxth r6, r6
sxth r7, r6                  // b237 sxth r7, r6
sxth r0, r7                  // b238 sxth r0, r7
sxth r1, r7                  // b239 sxth r1, r7
sxth r2, r7                  // b23a sxth r2, r7
sxth r3, r7                  // b23b sxth r3, r7
sxth r4, r7                  // b23c sxth r4, r7
sxth r5, r7                  // b23d sxth r5, r7
sxth r6, r7                  // b23e sxth r6, r7
sxth r7, r7                  // b23f sxth r7, r7

sxtb r0, r0                  // b240 sxtb r0, r0
sxtb r1, r0                  // b241 sxtb r1, r0
sxtb r2, r0                  // b242 sxtb r2, r0
sxtb r3, r0                  // b243 sxtb r3, r0
sxtb r4, r0                  // b244 sxtb r4, r0
sxtb r5, r0                  // b245 sxtb r5, r0
sxtb r6, r0                  // b246 sxtb r6, r0
sxtb r7, r0                  // b247 sxtb r7, r0
sxtb r0, r1                  // b248 sxtb r0, r1
sxtb r1, r1                  // b249 sxtb r1, r1
sxtb r2, r1                  // b24a sxtb r2, r1
sxtb r3, r1                  // b24b sxtb r3, r1
sxtb r4, r1                  // b24c sxtb r4, r1
sxtb r5, r1                  // b24d sxtb r5, r1
sxtb r6, r1                  // b24e sxtb r6, r1
sxtb r7, r1                  // b24f sxtb r7, r1
sxtb r0, r2                  // b250 sxtb r0, r2
sxtb r1, r2                  // b251 sxtb r1, r2
sxtb r2, r2                  // b252 sxtb r2, r2
sxtb r3, r2                  // b253 sxtb r3, r2
sxtb r4, r2                  // b254 sxtb r4, r2
sxtb r5, r2                  // b255 sxtb r5, r2
sxtb r6, r2                  // b256 sxtb r6, r2
sxtb r7, r2                  // b257 sxtb r7, r2
sxtb r0, r3                  // b258 sxtb r0, r3
sxtb r1, r3                  // b259 sxtb r1, r3
sxtb r2, r3                  // b25a sxtb r2, r3
sxtb r3, r3                  // b25b sxtb r3, r3
sxtb r4, r3                  // b25c sxtb r4, r3
sxtb r5, r3                  // b25d sxtb r5, r3
sxtb r6, r3                  // b25e sxtb r6, r3
sxtb r7, r3                  // b25f sxtb r7, r3
sxtb r0, r4                  // b260 sxtb r0, r4
sxtb r1, r4                  // b261 sxtb r1, r4
sxtb r2, r4                  // b262 sxtb r2, r4
sxtb r3, r4                  // b263 sxtb r3, r4
sxtb r4, r4                  // b264 sxtb r4, r4
sxtb r5, r4                  // b265 sxtb r5, r4
sxtb r6, r4                  // b266 sxtb r6, r4
sxtb r7, r4                  // b267 sxtb r7, r4
sxtb r0, r5                  // b268 sxtb r0, r5
sxtb r1, r5                  // b269 sxtb r1, r5
sxtb r2, r5                  // b26a sxtb r2, r5
sxtb r3, r5                  // b26b sxtb r3, r5
sxtb r4, r5                  // b26c sxtb r4, r5
sxtb r5, r5                  // b26d sxtb r5, r5
sxtb r6, r5                  // b26e sxtb r6, r5
sxtb r7, r5                  // b26f sxtb r7, r5
sxtb r0, r6                  // b270 sxtb r0, r6
sxtb r1, r6                  // b271 sxtb r1, r6
sxtb r2, r6                  // b272 sxtb r2, r6
sxtb r3, r6                  // b273 sxtb r3, r6
sxtb r4, r6                  // b274 sxtb r4, r6
sxtb r5, r6                  // b275 sxtb r5, r6
sxtb r6, r6                  // b276 sxtb r6, r6
sxtb r7, r6                  // b277 sxtb r7, r6
sxtb r0, r7                  // b278 sxtb r0, r7
sxtb r1, r7                  // b279 sxtb r1, r7
sxtb r2, r7                  // b27a sxtb r2, r7
sxtb r3, r7                  // b27b sxtb r3, r7
sxtb r4, r7                  // b27c sxtb r4, r7
sxtb r5, r7                  // b27d sxtb r5, r7
sxtb r6, r7                  // b27e sxtb r6, r7
sxtb r7, r7                  // b27f sxtb r7, r7
uxth r0, r0                  // b280 uxth r0, r0
uxth r1, r0                  // b281 uxth r1, r0
uxth r2, r0                  // b282 uxth r2, r0
uxth r3, r0                  // b283 uxth r3, r0
uxth r4, r0                  // b284 uxth r4, r0
uxth r5, r0                  // b285 uxth r5, r0
uxth r6, r0                  // b286 uxth r6, r0
uxth r7, r0                  // b287 uxth r7, r0
uxth r0, r1                  // b288 uxth r0, r1
uxth r1, r1                  // b289 uxth r1, r1
uxth r2, r1                  // b28a uxth r2, r1
uxth r3, r1                  // b28b uxth r3, r1
uxth r4, r1                  // b28c uxth r4, r1
uxth r5, r1                  // b28d uxth r5, r1
uxth r6, r1                  // b28e uxth r6, r1
uxth r7, r1                  // b28f uxth r7, r1
uxth r0, r2                  // b290 uxth r0, r2
uxth r1, r2                  // b291 uxth r1, r2
uxth r2, r2                  // b292 uxth r2, r2
uxth r3, r2                  // b293 uxth r3, r2
uxth r4, r2                  // b294 uxth r4, r2
uxth r5, r2                  // b295 uxth r5, r2
uxth r6, r2                  // b296 uxth r6, r2
uxth r7, r2                  // b297 uxth r7, r2
uxth r0, r3                  // b298 uxth r0, r3
uxth r1, r3                  // b299 uxth r1, r3
uxth r2, r3                  // b29a uxth r2, r3
uxth r3, r3                  // b29b uxth r3, r3
uxth r4, r3                  // b29c uxth r4, r3
uxth r5, r3                  // b29d uxth r5, r3
uxth r6, r3                  // b29e uxth r6, r3
uxth r7, r3                  // b29f uxth r7, r3
uxth r0, r4                  // b2a0 uxth r0, r4
uxth r1, r4                  // b2a1 uxth r1, r4
uxth r2, r4                  // b2a2 uxth r2, r4
uxth r3, r4                  // b2a3 uxth r3, r4
uxth r4, r4                  // b2a4 uxth r4, r4
uxth r5, r4                  // b2a5 uxth r5, r4
uxth r6, r4                  // b2a6 uxth r6, r4
uxth r7, r4                  // b2a7 uxth r7, r4
uxth r0, r5                  // b2a8 uxth r0, r5
uxth r1, r5                  // b2a9 uxth r1, r5
uxth r2, r5                  // b2aa uxth r2, r5
uxth r3, r5                  // b2ab uxth r3, r5
uxth r4, r5                  // b2ac uxth r4, r5
uxth r5, r5                  // b2ad uxth r5, r5
uxth r6, r5                  // b2ae uxth r6, r5
uxth r7, r5                  // b2af uxth r7, r5
uxth r0, r6                  // b2b0 uxth r0, r6
uxth r1, r6                  // b2b1 uxth r1, r6
uxth r2, r6                  // b2b2 uxth r2, r6
uxth r3, r6                  // b2b3 uxth r3, r6
uxth r4, r6                  // b2b4 uxth r4, r6
uxth r5, r6                  // b2b5 uxth r5, r6
uxth r6, r6                  // b2b6 uxth r6, r6
uxth r7, r6                  // b2b7 uxth r7, r6
uxth r0, r7                  // b2b8 uxth r0, r7
uxth r1, r7                  // b2b9 uxth r1, r7
uxth r2, r7                  // b2ba uxth r2, r7
uxth r3, r7                  // b2bb uxth r3, r7
uxth r4, r7                  // b2bc uxth r4, r7
uxth r5, r7                  // b2bd uxth r5, r7
uxth r6, r7                  // b2be uxth r6, r7
uxth r7, r7                  // b2bf uxth r7, r7
uxtb r0, r0                  // b2c0 uxtb r0, r0
uxtb r1, r0                  // b2c1 uxtb r1, r0
uxtb r2, r0                  // b2c2 uxtb r2, r0
uxtb r3, r0                  // b2c3 uxtb r3, r0
uxtb r4, r0                  // b2c4 uxtb r4, r0
uxtb r5, r0                  // b2c5 uxtb r5, r0
uxtb r6, r0                  // b2c6 uxtb r6, r0
uxtb r7, r0                  // b2c7 uxtb r7, r0
uxtb r0, r1                  // b2c8 uxtb r0, r1
uxtb r1, r1                  // b2c9 uxtb r1, r1
uxtb r2, r1                  // b2ca uxtb r2, r1
uxtb r3, r1                  // b2cb uxtb r3, r1
uxtb r4, r1                  // b2cc uxtb r4, r1
uxtb r5, r1                  // b2cd uxtb r5, r1
uxtb r6, r1                  // b2ce uxtb r6, r1
uxtb r7, r1                  // b2cf uxtb r7, r1
uxtb r0, r2                  // b2d0 uxtb r0, r2
uxtb r1, r2                  // b2d1 uxtb r1, r2
uxtb r2, r2                  // b2d2 uxtb r2, r2
uxtb r3, r2                  // b2d3 uxtb r3, r2
uxtb r4, r2                  // b2d4 uxtb r4, r2
uxtb r5, r2                  // b2d5 uxtb r5, r2
uxtb r6, r2                  // b2d6 uxtb r6, r2
uxtb r7, r2                  // b2d7 uxtb r7, r2
uxtb r0, r3                  // b2d8 uxtb r0, r3
uxtb r1, r3                  // b2d9 uxtb r1, r3
uxtb r2, r3                  // b2da uxtb r2, r3
uxtb r3, r3                  // b2db uxtb r3, r3
uxtb r4, r3                  // b2dc uxtb r4, r3
uxtb r5, r3                  // b2dd uxtb r5, r3
uxtb r6, r3                  // b2de uxtb r6, r3
uxtb r7, r3                  // b2df uxtb r7, r3
uxtb r0, r4                  // b2e0 uxtb r0, r4
uxtb r1, r4                  // b2e1 uxtb r1, r4
uxtb r2, r4                  // b2e2 uxtb r2, r4
uxtb r3, r4                  // b2e3 uxtb r3, r4
uxtb r4, r4                  // b2e4 uxtb r4, r4
uxtb r5, r4                  // b2e5 uxtb r5, r4
uxtb r6, r4                  // b2e6 uxtb r6, r4
uxtb r7, r4                  // b2e7 uxtb r7, r4
uxtb r0, r5                  // b2e8 uxtb r0, r5
uxtb r1, r5                  // b2e9 uxtb r1, r5
uxtb r2, r5                  // b2ea uxtb r2, r5
uxtb r3, r5                  // b2eb uxtb r3, r5
uxtb r4, r5                  // b2ec uxtb r4, r5
uxtb r5, r5                  // b2ed uxtb r5, r5
uxtb r6, r5                  // b2ee uxtb r6, r5
uxtb r7, r5                  // b2ef uxtb r7, r5
uxtb r0, r6                  // b2f0 uxtb r0, r6
uxtb r1, r6                  // b2f1 uxtb r1, r6
uxtb r2, r6                  // b2f2 uxtb r2, r6
uxtb r3, r6                  // b2f3 uxtb r3, r6
uxtb r4, r6                  // b2f4 uxtb r4, r6
uxtb r5, r6                  // b2f5 uxtb r5, r6
uxtb r6, r6                  // b2f6 uxtb r6, r6
uxtb r7, r6                  // b2f7 uxtb r7, r6
uxtb r0, r7                  // b2f8 uxtb r0, r7
uxtb r1, r7                  // b2f9 uxtb r1, r7
uxtb r2, r7                  // b2fa uxtb r2, r7
uxtb r3, r7                  // b2fb uxtb r3, r7
uxtb r4, r7                  // b2fc uxtb r4, r7
uxtb r5, r7                  // b2fd uxtb r5, r7
uxtb r6, r7                  // b2fe uxtb r6, r7
uxtb r7, r7                  // b2ff uxtb r7, r7

push {r0}                                    // b401 push {r0}
push {r1}                                    // b402 push {r1}
push {r2}                                    // b404 push {r2}
push {r3}                                    // b408 push {r3}
push {r4}                                    // b410 push {r4}
push {r5}                                    // b420 push {r5}
push {r6}                                    // b440 push {r6}
push {r7}                                    // b480 push {r7}
push {lr}                                    // b500 push {lr}
push {r0, r1, r2, r3, r4, r5, r6, r7, lr}    // b5ff push {r0, r1, r2, r3, r4, r5, r6, r7, lr}

rev r0, r0                   // ba00 rev r0, r0
rev r1, r0                   // ba01 rev r1, r0
rev r2, r0                   // ba02 rev r2, r0
rev r3, r0                   // ba03 rev r3, r0
rev r4, r0                   // ba04 rev r4, r0
rev r5, r0                   // ba05 rev r5, r0
rev r6, r0                   // ba06 rev r6, r0
rev r7, r0                   // ba07 rev r7, r0
rev r0, r1                   // ba08 rev r0, r1
rev r1, r1                   // ba09 rev r1, r1
rev r2, r1                   // ba0a rev r2, r1
rev r3, r1                   // ba0b rev r3, r1
rev r4, r1                   // ba0c rev r4, r1
rev r5, r1                   // ba0d rev r5, r1
rev r6, r1                   // ba0e rev r6, r1
rev r7, r1                   // ba0f rev r7, r1
rev r0, r2                   // ba10 rev r0, r2
rev r1, r2                   // ba11 rev r1, r2
rev r2, r2                   // ba12 rev r2, r2
rev r3, r2                   // ba13 rev r3, r2
rev r4, r2                   // ba14 rev r4, r2
rev r5, r2                   // ba15 rev r5, r2
rev r6, r2                   // ba16 rev r6, r2
rev r7, r2                   // ba17 rev r7, r2
rev r0, r3                   // ba18 rev r0, r3
rev r1, r3                   // ba19 rev r1, r3
rev r2, r3                   // ba1a rev r2, r3
rev r3, r3                   // ba1b rev r3, r3
rev r4, r3                   // ba1c rev r4, r3
rev r5, r3                   // ba1d rev r5, r3
rev r6, r3                   // ba1e rev r6, r3
rev r7, r3                   // ba1f rev r7, r3
rev r0, r4                   // ba20 rev r0, r4
rev r1, r4                   // ba21 rev r1, r4
rev r2, r4                   // ba22 rev r2, r4
rev r3, r4                   // ba23 rev r3, r4
rev r4, r4                   // ba24 rev r4, r4
rev r5, r4                   // ba25 rev r5, r4
rev r6, r4                   // ba26 rev r6, r4
rev r7, r4                   // ba27 rev r7, r4
rev r0, r5                   // ba28 rev r0, r5
rev r1, r5                   // ba29 rev r1, r5
rev r2, r5                   // ba2a rev r2, r5
rev r3, r5                   // ba2b rev r3, r5
rev r4, r5                   // ba2c rev r4, r5
rev r5, r5                   // ba2d rev r5, r5
rev r6, r5                   // ba2e rev r6, r5
rev r7, r5                   // ba2f rev r7, r5
rev r0, r6                   // ba30 rev r0, r6
rev r1, r6                   // ba31 rev r1, r6
rev r2, r6                   // ba32 rev r2, r6
rev r3, r6                   // ba33 rev r3, r6
rev r4, r6                   // ba34 rev r4, r6
rev r5, r6                   // ba35 rev r5, r6
rev r6, r6                   // ba36 rev r6, r6
rev r7, r6                   // ba37 rev r7, r6
rev r0, r7                   // ba38 rev r0, r7
rev r1, r7                   // ba39 rev r1, r7
rev r2, r7                   // ba3a rev r2, r7
rev r3, r7                   // ba3b rev r3, r7
rev r4, r7                   // ba3c rev r4, r7
rev r5, r7                   // ba3d rev r5, r7
rev r6, r7                   // ba3e rev r6, r7
rev r7, r7                   // ba3f rev r7, r7

rev16 r0, r0                 // ba40 rev16 r0, r0
rev16 r1, r0                 // ba41 rev16 r1, r0
rev16 r2, r0                 // ba42 rev16 r2, r0
rev16 r3, r0                 // ba43 rev16 r3, r0
rev16 r4, r0                 // ba44 rev16 r4, r0
rev16 r5, r0                 // ba45 rev16 r5, r0
rev16 r6, r0                 // ba46 rev16 r6, r0
rev16 r7, r0                 // ba47 rev16 r7, r0
rev16 r0, r1                 // ba48 rev16 r0, r1
rev16 r1, r1                 // ba49 rev16 r1, r1
rev16 r2, r1                 // ba4a rev16 r2, r1
rev16 r3, r1                 // ba4b rev16 r3, r1
rev16 r4, r1                 // ba4c rev16 r4, r1
rev16 r5, r1                 // ba4d rev16 r5, r1
rev16 r6, r1                 // ba4e rev16 r6, r1
rev16 r7, r1                 // ba4f rev16 r7, r1
rev16 r0, r2                 // ba50 rev16 r0, r2
rev16 r1, r2                 // ba51 rev16 r1, r2
rev16 r2, r2                 // ba52 rev16 r2, r2
rev16 r3, r2                 // ba53 rev16 r3, r2
rev16 r4, r2                 // ba54 rev16 r4, r2
rev16 r5, r2                 // ba55 rev16 r5, r2
rev16 r6, r2                 // ba56 rev16 r6, r2
rev16 r7, r2                 // ba57 rev16 r7, r2
rev16 r0, r3                 // ba58 rev16 r0, r3
rev16 r1, r3                 // ba59 rev16 r1, r3
rev16 r2, r3                 // ba5a rev16 r2, r3
rev16 r3, r3                 // ba5b rev16 r3, r3
rev16 r4, r3                 // ba5c rev16 r4, r3
rev16 r5, r3                 // ba5d rev16 r5, r3
rev16 r6, r3                 // ba5e rev16 r6, r3
rev16 r7, r3                 // ba5f rev16 r7, r3
rev16 r0, r4                 // ba60 rev16 r0, r4
rev16 r1, r4                 // ba61 rev16 r1, r4
rev16 r2, r4                 // ba62 rev16 r2, r4
rev16 r3, r4                 // ba63 rev16 r3, r4
rev16 r4, r4                 // ba64 rev16 r4, r4
rev16 r5, r4                 // ba65 rev16 r5, r4
rev16 r6, r4                 // ba66 rev16 r6, r4
rev16 r7, r4                 // ba67 rev16 r7, r4
rev16 r0, r5                 // ba68 rev16 r0, r5
rev16 r1, r5                 // ba69 rev16 r1, r5
rev16 r2, r5                 // ba6a rev16 r2, r5
rev16 r3, r5                 // ba6b rev16 r3, r5
rev16 r4, r5                 // ba6c rev16 r4, r5
rev16 r5, r5                 // ba6d rev16 r5, r5
rev16 r6, r5                 // ba6e rev16 r6, r5
rev16 r7, r5                 // ba6f rev16 r7, r5
rev16 r0, r6                 // ba70 rev16 r0, r6
rev16 r1, r6                 // ba71 rev16 r1, r6
rev16 r2, r6                 // ba72 rev16 r2, r6
rev16 r3, r6                 // ba73 rev16 r3, r6
rev16 r4, r6                 // ba74 rev16 r4, r6
rev16 r5, r6                 // ba75 rev16 r5, r6
rev16 r6, r6                 // ba76 rev16 r6, r6
rev16 r7, r6                 // ba77 rev16 r7, r6
rev16 r0, r7                 // ba78 rev16 r0, r7
rev16 r1, r7                 // ba79 rev16 r1, r7
rev16 r2, r7                 // ba7a rev16 r2, r7
rev16 r3, r7                 // ba7b rev16 r3, r7
rev16 r4, r7                 // ba7c rev16 r4, r7
rev16 r5, r7                 // ba7d rev16 r5, r7
rev16 r6, r7                 // ba7e rev16 r6, r7
rev16 r7, r7                 // ba7f rev16 r7, r7

revsh r0, r0                 // bac0 revsh r0, r0
revsh r1, r0                 // bac1 revsh r1, r0
revsh r2, r0                 // bac2 revsh r2, r0
revsh r3, r0                 // bac3 revsh r3, r0
revsh r4, r0                 // bac4 revsh r4, r0
revsh r5, r0                 // bac5 revsh r5, r0
revsh r6, r0                 // bac6 revsh r6, r0
revsh r7, r0                 // bac7 revsh r7, r0
revsh r0, r1                 // bac8 revsh r0, r1
revsh r1, r1                 // bac9 revsh r1, r1
revsh r2, r1                 // baca revsh r2, r1
revsh r3, r1                 // bacb revsh r3, r1
revsh r4, r1                 // bacc revsh r4, r1
revsh r5, r1                 // bacd revsh r5, r1
revsh r6, r1                 // bace revsh r6, r1
revsh r7, r1                 // bacf revsh r7, r1
revsh r0, r2                 // bad0 revsh r0, r2
revsh r1, r2                 // bad1 revsh r1, r2
revsh r2, r2                 // bad2 revsh r2, r2
revsh r3, r2                 // bad3 revsh r3, r2
revsh r4, r2                 // bad4 revsh r4, r2
revsh r5, r2                 // bad5 revsh r5, r2
revsh r6, r2                 // bad6 revsh r6, r2
revsh r7, r2                 // bad7 revsh r7, r2
revsh r0, r3                 // bad8 revsh r0, r3
revsh r1, r3                 // bad9 revsh r1, r3
revsh r2, r3                 // bada revsh r2, r3
revsh r3, r3                 // badb revsh r3, r3
revsh r4, r3                 // badc revsh r4, r3
revsh r5, r3                 // badd revsh r5, r3
revsh r6, r3                 // bade revsh r6, r3
revsh r7, r3                 // badf revsh r7, r3
revsh r0, r4                 // bae0 revsh r0, r4
revsh r1, r4                 // bae1 revsh r1, r4
revsh r2, r4                 // bae2 revsh r2, r4
revsh r3, r4                 // bae3 revsh r3, r4
revsh r4, r4                 // bae4 revsh r4, r4
revsh r5, r4                 // bae5 revsh r5, r4
revsh r6, r4                 // bae6 revsh r6, r4
revsh r7, r4                 // bae7 revsh r7, r4
revsh r0, r5                 // bae8 revsh r0, r5
revsh r1, r5                 // bae9 revsh r1, r5
revsh r2, r5                 // baea revsh r2, r5
revsh r3, r5                 // baeb revsh r3, r5
revsh r4, r5                 // baec revsh r4, r5
revsh r5, r5                 // baed revsh r5, r5
revsh r6, r5                 // baee revsh r6, r5
revsh r7, r5                 // baef revsh r7, r5
revsh r0, r6                 // baf0 revsh r0, r6
revsh r1, r6                 // baf1 revsh r1, r6
revsh r2, r6                 // baf2 revsh r2, r6
revsh r3, r6                 // baf3 revsh r3, r6
revsh r4, r6                 // baf4 revsh r4, r6
revsh r5, r6                 // baf5 revsh r5, r6
revsh r6, r6                 // baf6 revsh r6, r6
revsh r7, r6                 // baf7 revsh r7, r6
revsh r0, r7                 // baf8 revsh r0, r7
revsh r1, r7                 // baf9 revsh r1, r7
revsh r2, r7                 // bafa revsh r2, r7
revsh r3, r7                 // bafb revsh r3, r7
revsh r4, r7                 // bafc revsh r4, r7
revsh r5, r7                 // bafd revsh r5, r7
revsh r6, r7                 // bafe revsh r6, r7
revsh r7, r7                 // baff revsh r7, r7

pop {r0}                                    // bc01 pop {r0}
pop {r1}                                    // bc02 pop {r1}
pop {r2}                                    // bc04 pop {r2}
pop {r3}                                    // bc08 pop {r3}
pop {r4}                                    // bc10 pop {r4}
pop {r5}                                    // bc20 pop {r5}
pop {r6}                                    // bc40 pop {r6}
pop {r7}                                    // bc80 pop {r7}
pop {pc}                                    // bd00 pop {pc}
pop {r0, r1, r2, r3, r4, r5, r6, r7, pc}    // bdff pop {r0, r1, r2, r3, r4, r5, r6, r7, pc}

bkpt 0x0000                  // be00 bkpt 0x0000
bkpt 0x0001                  // be01 bkpt 0x0001
bkpt 0x00ff                  // beff bkpt 0x00ff

stmia r0!, {r2}                              // c004 stmia r0!, {r2}
stmia r0!, {r3}                              // c008 stmia r0!, {r3}
stmia r0!, {r4}                              // c010 stmia r0!, {r4}
stmia r0!, {r5}                              // c020 stmia r0!, {r5}
stmia r0!, {r6}                              // c040 stmia r0!, {r6}
stmia r0!, {r7}                              // c080 stmia r0!, {r7}
stmia r0!, {r0, r1, r2, r3, r4, r5, r6, r7}  // c0ff stmia r0!, {r0, r1, r2, r3, r4, r5, r6, r7}
stmia r1!, {r0}                              // c101 stmia r1!, {r0}
stmia r1!, {r1}                              // c102 stmia r1!, {r1}
stmia r1!, {r2}                              // c104 stmia r1!, {r2}
stmia r1!, {r3}                              // c108 stmia r1!, {r3}
stmia r1!, {r4}                              // c110 stmia r1!, {r4}
stmia r1!, {r5}                              // c120 stmia r1!, {r5}
stmia r1!, {r6}                              // c140 stmia r1!, {r6}
stmia r1!, {r7}                              // c180 stmia r1!, {r7}
stmia r1!, {r1, r2, r3, r4, r5, r6, r7}      // c1fe stmia r1!, {r1, r2, r3, r4, r5, r6, r7}
stmia r2!, {r0}                              // c201 stmia r2!, {r0}
stmia r2!, {r1}                              // c202 stmia r2!, {r1}
stmia r2!, {r2}                              // c204 stmia r2!, {r2}
stmia r2!, {r3}                              // c208 stmia r2!, {r3}
stmia r2!, {r4}                              // c210 stmia r2!, {r4}
stmia r2!, {r5}                              // c220 stmia r2!, {r5}
stmia r2!, {r6}                              // c240 stmia r2!, {r6}
stmia r2!, {r7}                              // c280 stmia r2!, {r7}
stmia r2!, {r0, r1, r3, r4, r5, r6, r7}      // c2fb stmia r2!, {r0, r1, r3, r4, r5, r6, r7}
stmia r3!, {r0}                              // c301 stmia r3!, {r0}
stmia r3!, {r1}                              // c302 stmia r3!, {r1}
stmia r3!, {r2}                              // c304 stmia r3!, {r2}
stmia r3!, {r3}                              // c308 stmia r3!, {r3}
stmia r3!, {r4}                              // c310 stmia r3!, {r4}
stmia r3!, {r5}                              // c320 stmia r3!, {r5}
stmia r3!, {r6}                              // c340 stmia r3!, {r6}
stmia r3!, {r7}                              // c380 stmia r3!, {r7}
stmia r3!, {r0, r1, r2, r4, r5, r6, r7}      // c3f7 stmia r3!, {r0, r1, r2, r4, r5, r6, r7}
stmia r4!, {r0}                              // c401 stmia r4!, {r0}
stmia r4!, {r1}                              // c402 stmia r4!, {r1}
stmia r4!, {r2}                              // c404 stmia r4!, {r2}
stmia r4!, {r3}                              // c408 stmia r4!, {r3}
stmia r4!, {r4}                              // c410 stmia r4!, {r4}
stmia r4!, {r5}                              // c420 stmia r4!, {r5}
stmia r4!, {r6}                              // c440 stmia r4!, {r6}
stmia r4!, {r0, r1, r2, r3, r5, r6, r7}      // c4ef stmia r4!, {r0, r1, r2, r3, r5, r6, r7}
stmia r5!, {r0}                              // c501 stmia r5!, {r0}
stmia r5!, {r1}                              // c502 stmia r5!, {r1}
stmia r5!, {r2}                              // c504 stmia r5!, {r2}
stmia r5!, {r3}                              // c508 stmia r5!, {r3}
stmia r5!, {r4}                              // c510 stmia r5!, {r4}
stmia r5!, {r5}                              // c520 stmia r5!, {r5}
stmia r5!, {r6}                              // c540 stmia r5!, {r6}
stmia r5!, {r7}                              // c580 stmia r5!, {r7}
stmia r5!, {r0, r1, r2, r3, r4, r6, r7}      // c5df stmia r5!, {r0, r1, r2, r3, r4, r6, r7}
stmia r6!, {r0}                              // c601 stmia r6!, {r0}
stmia r6!, {r1}                              // c602 stmia r6!, {r1}
stmia r6!, {r2}                              // c604 stmia r6!, {r2}
stmia r6!, {r3}                              // c608 stmia r6!, {r3}
stmia r6!, {r4}                              // c610 stmia r6!, {r4}
stmia r6!, {r5}                              // c620 stmia r6!, {r5}
stmia r6!, {r6}                              // c640 stmia r6!, {r6}
stmia r6!, {r7}                              // c680 stmia r6!, {r7}
stmia r6!, {r0, r1, r2, r3, r4, r5, r7}      // c6bf stmia r6!, {r0, r1, r2, r3, r4, r5, r7}
stmia r7!, {r0}                              // c701 stmia r7!, {r0}
stmia r7!, {r1}                              // c702 stmia r7!, {r1}
stmia r7!, {r2}                              // c704 stmia r7!, {r2}
stmia r7!, {r3}                              // c708 stmia r7!, {r3}
stmia r7!, {r4}                              // c710 stmia r7!, {r4}
stmia r7!, {r5}                              // c720 stmia r7!, {r5}
stmia r7!, {r6}                              // c740 stmia r7!, {r6}
stmia r7!, {r0, r1, r2, r3, r4, r5, r6}      // c77f stmia r7!, {r0, r1, r2, r3, r4, r5, r6}

ldmia r0, {r0}                               // c801 ldmia r0, {r0}
ldmia r0!, {r1}                              // c802 ldmia r0!, {r1}
ldmia r0!, {r2}                              // c804 ldmia r0!, {r2}
ldmia r0!, {r3}                              // c808 ldmia r0!, {r3}
ldmia r0!, {r4}                              // c810 ldmia r0!, {r4}
ldmia r0, {r0, r1, r2, r3, r4}               // c81f ldmia r0, {r0, r1, r2, r3, r4}
ldmia r0!, {r5}                              // c820 ldmia r0!, {r5}
ldmia r0, {r0, r5}                           // c821 ldmia r0, {r0, r5}
ldmia r0!, {r6}                              // c840 ldmia r0!, {r6}
ldmia r0!, {r7}                              // c880 ldmia r0!, {r7}
ldmia r0, {r0, r7}                           // c881 ldmia r0, {r0, r7}
ldmia r0!, {r1, r2, r3, r4, r5, r6, r7}      // c8fe ldmia r0!, {r1, r2, r3, r4, r5, r6, r7}
ldmia r0, {r0, r1, r2, r3, r4, r5, r6, r7}   // c8ff ldmia r0, {r0, r1, r2, r3, r4, r5, r6, r7}
ldmia r1!, {r0}                              // c901 ldmia r1!, {r0}
ldmia r1, {r1}                               // c902 ldmia r1, {r1}
ldmia r1!, {r2}                              // c904 ldmia r1!, {r2}
ldmia r1!, {r3}                              // c908 ldmia r1!, {r3}
ldmia r1!, {r4}                              // c910 ldmia r1!, {r4}
ldmia r1!, {r5}                              // c920 ldmia r1!, {r5}
ldmia r1!, {r6}                              // c940 ldmia r1!, {r6}
ldmia r1!, {r7}                              // c980 ldmia r1!, {r7}
ldmia r1, {r0, r1, r2, r3, r4, r5, r6, r7}   // c9ff ldmia r1, {r0, r1, r2, r3, r4, r5, r6, r7}
ldmia r2!, {r0}                              // ca01 ldmia r2!, {r0}
ldmia r2!, {r1}                              // ca02 ldmia r2!, {r1}
ldmia r2, {r2}                               // ca04 ldmia r2, {r2}
ldmia r2!, {r3}                              // ca08 ldmia r2!, {r3}
ldmia r2!, {r4}                              // ca10 ldmia r2!, {r4}
ldmia r2!, {r5}                              // ca20 ldmia r2!, {r5}
ldmia r2!, {r6}                              // ca40 ldmia r2!, {r6}
ldmia r2!, {r7}                              // ca80 ldmia r2!, {r7}
ldmia r2, {r0, r1, r2, r3, r4, r5, r6, r7}   // caff ldmia r2, {r0, r1, r2, r3, r4, r5, r6, r7}
ldmia r3!, {r0}                              // cb01 ldmia r3!, {r0}
ldmia r3!, {r1}                              // cb02 ldmia r3!, {r1}
ldmia r3!, {r2}                              // cb04 ldmia r3!, {r2}
ldmia r3, {r3}                               // cb08 ldmia r3, {r3}
ldmia r3!, {r4}                              // cb10 ldmia r3!, {r4}
ldmia r3!, {r5}                              // cb20 ldmia r3!, {r5}
ldmia r3!, {r6}                              // cb40 ldmia r3!, {r6}
ldmia r3!, {r7}                              // cb80 ldmia r3!, {r7}
ldmia r3, {r0, r1, r2, r3, r4, r5, r6, r7}   // cbff ldmia r3, {r0, r1, r2, r3, r4, r5, r6, r7}
ldmia r4!, {r0}                              // cc01 ldmia r4!, {r0}
ldmia r4!, {r1}                              // cc02 ldmia r4!, {r1}
ldmia r4!, {r2}                              // cc04 ldmia r4!, {r2}
ldmia r4!, {r3}                              // cc08 ldmia r4!, {r3}
ldmia r4, {r4}                               // cc10 ldmia r4, {r4}
ldmia r4!, {r5}                              // cc20 ldmia r4!, {r5}
ldmia r4!, {r6}                              // cc40 ldmia r4!, {r6}
ldmia r4!, {r7}                              // cc80 ldmia r4!, {r7}
ldmia r4, {r0, r1, r2, r3, r4, r5, r6, r7}   // ccff ldmia r4, {r0, r1, r2, r3, r4, r5, r6, r7}
ldmia r5!, {r0}                              // cd01 ldmia r5!, {r0}
ldmia r5!, {r1}                              // cd02 ldmia r5!, {r1}
ldmia r5!, {r2}                              // cd04 ldmia r5!, {r2}
ldmia r5!, {r3}                              // cd08 ldmia r5!, {r3}
ldmia r5!, {r4}                              // cd10 ldmia r5!, {r4}
ldmia r5, {r5}                               // cd20 ldmia r5, {r5}
ldmia r5!, {r6}                              // cd40 ldmia r5!, {r6}
ldmia r5!, {r7}                              // cd80 ldmia r5!, {r7}
ldmia r5, {r0, r1, r2, r3, r4, r5, r6, r7}   // cdff ldmia r5, {r0, r1, r2, r3, r4, r5, r6, r7}
ldmia r6!, {r0}                              // ce01 ldmia r6!, {r0}
ldmia r6!, {r1}                              // ce02 ldmia r6!, {r1}
ldmia r6!, {r2}                              // ce04 ldmia r6!, {r2}
ldmia r6!, {r3}                              // ce08 ldmia r6!, {r3}
ldmia r6!, {r4}                              // ce10 ldmia r6!, {r4}
ldmia r6!, {r5}                              // ce20 ldmia r6!, {r5}
ldmia r6, {r6}                               // ce40 ldmia r6, {r6}
ldmia r6!, {r7}                              // ce80 ldmia r6!, {r7}
ldmia r6, {r0, r1, r2, r3, r4, r5, r6, r7}   // ceff ldmia r6, {r0, r1, r2, r3, r4, r5, r6, r7}
ldmia r7!, {r0}                              // cf01 ldmia r7!, {r0}
ldmia r7!, {r1}                              // cf02 ldmia r7!, {r1}
ldmia r7!, {r2}                              // cf04 ldmia r7!, {r2}
ldmia r7!, {r3}                              // cf08 ldmia r7!, {r3}
ldmia r7!, {r4}                              // cf10 ldmia r7!, {r4}
ldmia r7!, {r5}                              // cf20 ldmia r7!, {r5}
ldmia r7!, {r6}                              // cf40 ldmia r7!, {r6}
ldmia r7, {r7}                               // cf80 ldmia r7, {r7}
ldmia r7, {r0, r1, r2, r3, r4, r5, r6, r7}   // cfff ldmia r7, {r0, r1, r2, r3, r4, r5, r6, r7}

beq.n 0x0001a004             // d000 beq.n 0x0001a004
beq.n 0x0001a008             // d001 beq.n 0x0001a008
beq.n 0x0001a200             // d0ff beq.n 0x0001a200

bne.n 0x0001a204             // d100 bne.n 0x0001a204
bne.n 0x0001a208             // d101 bne.n 0x0001a208
bne.n 0x0001a400             // d1ff bne.n 0x0001a400

bcs.n 0x0001a404             // d200 bcs.n 0x0001a404
bcs.n 0x0001a408             // d201 bcs.n 0x0001a408
bcs.n 0x0001a600             // d2ff bcs.n 0x0001a600

bcc.n 0x0001a604             // d300 bcc.n 0x0001a604
bcc.n 0x0001a608             // d301 bcc.n 0x0001a608
bcc.n 0x0001a800             // d3ff bcc.n 0x0001a800

bmi.n 0x0001a804             // d400 bmi.n 0x0001a804
bmi.n 0x0001a808             // d401 bmi.n 0x0001a808
bmi.n 0x0001aa00             // d4ff bmi.n 0x0001aa00

bpl.n 0x0001aa04             // d500 bpl.n 0x0001aa04
bpl.n 0x0001aa08             // d501 bpl.n 0x0001aa08
bpl.n 0x0001ac00             // d5ff bpl.n 0x0001ac00

bvs.n 0x0001ac04             // d600 bvs.n 0x0001ac04
bvs.n 0x0001ac08             // d601 bvs.n 0x0001ac08
bvs.n 0x0001ae00             // d6ff bvs.n 0x0001ae00

bvc.n 0x0001ae04             // d700 bvc.n 0x0001ae04
bvc.n 0x0001ae08             // d701 bvc.n 0x0001ae08
bvc.n 0x0001b000             // d7ff bvc.n 0x0001b000

bhi.n 0x0001b004             // d800 bhi.n 0x0001b004
bhi.n 0x0001b008             // d801 bhi.n 0x0001b008
bhi.n 0x0001b200             // d8ff bhi.n 0x0001b200

bls.n 0x0001b204             // d900 bls.n 0x0001b204
bls.n 0x0001b208             // d901 bls.n 0x0001b208
bls.n 0x0001b400             // d9ff bls.n 0x0001b400

bge.n 0x0001b404             // da00 bge.n 0x0001b404
bge.n 0x0001b408             // da01 bge.n 0x0001b408
bge.n 0x0001b600             // daff bge.n 0x0001b600

blt.n 0x0001b604             // db00 blt.n 0x0001b604
blt.n 0x0001b608             // db01 blt.n 0x0001b608
blt.n 0x0001b800             // dbff blt.n 0x0001b800

bgt.n 0x0001b804             // dc00 bgt.n 0x0001b804
bgt.n 0x0001b808             // dc01 bgt.n 0x0001b808
bgt.n 0x0001ba00             // dcff bgt.n 0x0001ba00

ble.n 0x0001ba04             // dd00 ble.n 0x0001ba04
ble.n 0x0001ba08             // dd01 ble.n 0x0001ba08
ble.n 0x0001bc00             // ddff ble.n 0x0001bc00

udf #0                       // de00 udf #0
udf #1                       // de01 udf #1
udf #255 // 0xff              // deff udf #255 // 0xff

svc 0                        // df00 svc 0
svc 1                        // df01 svc 1
svc 255 // 0xff               // dfff svc 255 // 0xff

b.n 0x0001c004               // e000 b.n 0x0001c004
b.n 0x0001c008               // e001 b.n 0x0001c008
b.n 0x0001d000               // e7ff b.n 0x0001d000
#endif
}

#include "gtest_main.cpp"

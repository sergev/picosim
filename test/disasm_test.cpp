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

    test_disasm(0x4400, "add r0, r0");
    test_disasm(0x4401, "add r1, r0");
    test_disasm(0x4407, "add r7, r0");
    test_disasm(0x4408, "add r0, r1");
    test_disasm(0x4409, "add r1, r1");
    test_disasm(0x440f, "add r7, r1");
    test_disasm(0x4438, "add r0, r7");
    test_disasm(0x4439, "add r1, r7");
    test_disasm(0x443f, "add r7, r7");
    test_disasm(0x4440, "add r0, r8");
    test_disasm(0x4441, "add r1, r8");
    test_disasm(0x4447, "add r7, r8");
    test_disasm(0x4448, "add r0, r9");
    test_disasm(0x4449, "add r1, r9");
    test_disasm(0x444f, "add r7, r9");
    test_disasm(0x4450, "add r0, sl");
    test_disasm(0x4451, "add r1, sl");
    test_disasm(0x4457, "add r7, sl");
    test_disasm(0x4458, "add r0, fp");
    test_disasm(0x4459, "add r1, fp");
    test_disasm(0x445f, "add r7, fp");
    test_disasm(0x4460, "add r0, ip");
    test_disasm(0x4461, "add r1, ip");
    test_disasm(0x4467, "add r7, ip");
    test_disasm(0x4468, "add r0, sp");
    test_disasm(0x4469, "add r1, sp");
    test_disasm(0x446f, "add r7, sp");
    test_disasm(0x4470, "add r0, lr");
    test_disasm(0x4471, "add r1, lr");
    test_disasm(0x4477, "add r7, lr");
    test_disasm(0x4478, "add r0, pc");
    test_disasm(0x4479, "add r1, pc");
    test_disasm(0x447f, "add r7, pc");
    test_disasm(0x4480, "add r8, r0");
    test_disasm(0x4481, "add r9, r0");
    test_disasm(0x4482, "add sl, r0");
    test_disasm(0x4483, "add fp, r0");
    test_disasm(0x4484, "add ip, r0");
    test_disasm(0x4485, "add sp, r0");
    test_disasm(0x4486, "add lr, r0");
    test_disasm(0x4487, "add pc, r0");
    test_disasm(0x4488, "add r8, r1");
    test_disasm(0x4489, "add r9, r1");
    test_disasm(0x448a, "add sl, r1");
    test_disasm(0x448b, "add fp, r1");
    test_disasm(0x448c, "add ip, r1");
    test_disasm(0x448d, "add sp, r1");
    test_disasm(0x448e, "add lr, r1");
    test_disasm(0x448f, "add pc, r1");
    test_disasm(0x44b8, "add r8, r7");
    test_disasm(0x44b9, "add r9, r7");
    test_disasm(0x44ba, "add sl, r7");
    test_disasm(0x44bb, "add fp, r7");
    test_disasm(0x44bc, "add ip, r7");
    test_disasm(0x44bd, "add sp, r7");
    test_disasm(0x44be, "add lr, r7");
    test_disasm(0x44bf, "add pc, r7");
    test_disasm(0x44c0, "add r8, r8");
    test_disasm(0x44c1, "add r9, r8");
    test_disasm(0x44c2, "add sl, r8");
    test_disasm(0x44c3, "add fp, r8");
    test_disasm(0x44c4, "add ip, r8");
    test_disasm(0x44c5, "add sp, r8");
    test_disasm(0x44c6, "add lr, r8");
    test_disasm(0x44c7, "add pc, r8");
    test_disasm(0x44c8, "add r8, r9");
    test_disasm(0x44c9, "add r9, r9");
    test_disasm(0x44ca, "add sl, r9");
    test_disasm(0x44cb, "add fp, r9");
    test_disasm(0x44cc, "add ip, r9");
    test_disasm(0x44cd, "add sp, r9");
    test_disasm(0x44ce, "add lr, r9");
    test_disasm(0x44cf, "add pc, r9");
    test_disasm(0x44d0, "add r8, sl");
    test_disasm(0x44d1, "add r9, sl");
    test_disasm(0x44d2, "add sl, sl");
    test_disasm(0x44d3, "add fp, sl");
    test_disasm(0x44d4, "add ip, sl");
    test_disasm(0x44d5, "add sp, sl");
    test_disasm(0x44d6, "add lr, sl");
    test_disasm(0x44d7, "add pc, sl");
    test_disasm(0x44d8, "add r8, fp");
    test_disasm(0x44d9, "add r9, fp");
    test_disasm(0x44da, "add sl, fp");
    test_disasm(0x44db, "add fp, fp");
    test_disasm(0x44dc, "add ip, fp");
    test_disasm(0x44dd, "add sp, fp");
    test_disasm(0x44de, "add lr, fp");
    test_disasm(0x44df, "add pc, fp");
    test_disasm(0x44e0, "add r8, ip");
    test_disasm(0x44e1, "add r9, ip");
    test_disasm(0x44e2, "add sl, ip");
    test_disasm(0x44e3, "add fp, ip");
    test_disasm(0x44e4, "add ip, ip");
    test_disasm(0x44e5, "add sp, ip");
    test_disasm(0x44e6, "add lr, ip");
    test_disasm(0x44e7, "add pc, ip");
    test_disasm(0x44e8, "add r8, sp");
    test_disasm(0x44e9, "add r9, sp");
    test_disasm(0x44ea, "add sl, sp");
    test_disasm(0x44eb, "add fp, sp");
    test_disasm(0x44ec, "add ip, sp");
    test_disasm(0x44ed, "add sp, sp");
    test_disasm(0x44ee, "add lr, sp");
    test_disasm(0x44ef, "add pc, sp");
    test_disasm(0x44f0, "add r8, lr");
    test_disasm(0x44f1, "add r9, lr");
    test_disasm(0x44f2, "add sl, lr");
    test_disasm(0x44f3, "add fp, lr");
    test_disasm(0x44f4, "add ip, lr");
    test_disasm(0x44f5, "add sp, lr");
    test_disasm(0x44f6, "add lr, lr");
    test_disasm(0x44f7, "add pc, lr");
    test_disasm(0x44f8, "add r8, pc");
    test_disasm(0x44f9, "add r9, pc");
    test_disasm(0x44fa, "add sl, pc");
    test_disasm(0x44fb, "add fp, pc");
    test_disasm(0x44fc, "add ip, pc");
    test_disasm(0x44fd, "add sp, pc");
    test_disasm(0x44fe, "add lr, pc");
    test_disasm(0x44ff, "add pc, pc");

    test_disasm(0x4500, "cmp r0, r0");
    test_disasm(0x4501, "cmp r1, r0");
    test_disasm(0x4507, "cmp r7, r0");
    test_disasm(0x4508, "cmp r0, r1");
    test_disasm(0x4509, "cmp r1, r1");
    test_disasm(0x450f, "cmp r7, r1");
    test_disasm(0x4538, "cmp r0, r7");
    test_disasm(0x4539, "cmp r1, r7");
    test_disasm(0x453f, "cmp r7, r7");
    test_disasm(0x4540, "cmp r0, r8");
    test_disasm(0x4541, "cmp r1, r8");
    test_disasm(0x4547, "cmp r7, r8");
    test_disasm(0x4548, "cmp r0, r9");
    test_disasm(0x4549, "cmp r1, r9");
    test_disasm(0x454f, "cmp r7, r9");
    test_disasm(0x4550, "cmp r0, sl");
    test_disasm(0x4551, "cmp r1, sl");
    test_disasm(0x4557, "cmp r7, sl");
    test_disasm(0x4558, "cmp r0, fp");
    test_disasm(0x4559, "cmp r1, fp");
    test_disasm(0x455f, "cmp r7, fp");
    test_disasm(0x4560, "cmp r0, ip");
    test_disasm(0x4561, "cmp r1, ip");
    test_disasm(0x4567, "cmp r7, ip");
    test_disasm(0x4570, "cmp r0, lr");
    test_disasm(0x4571, "cmp r1, lr");
    test_disasm(0x4577, "cmp r7, lr");
    test_disasm(0x4580, "cmp r8, r0");
    test_disasm(0x4581, "cmp r9, r0");
    test_disasm(0x4582, "cmp sl, r0");
    test_disasm(0x4583, "cmp fp, r0");
    test_disasm(0x4584, "cmp ip, r0");
    test_disasm(0x4585, "cmp sp, r0");
    test_disasm(0x4586, "cmp lr, r0");
    test_disasm(0x4588, "cmp r8, r1");
    test_disasm(0x4589, "cmp r9, r1");
    test_disasm(0x458a, "cmp sl, r1");
    test_disasm(0x458b, "cmp fp, r1");
    test_disasm(0x458c, "cmp ip, r1");
    test_disasm(0x458d, "cmp sp, r1");
    test_disasm(0x458e, "cmp lr, r1");
    test_disasm(0x45b8, "cmp r8, r7");
    test_disasm(0x45b9, "cmp r9, r7");
    test_disasm(0x45ba, "cmp sl, r7");
    test_disasm(0x45bb, "cmp fp, r7");
    test_disasm(0x45bc, "cmp ip, r7");
    test_disasm(0x45bd, "cmp sp, r7");
    test_disasm(0x45be, "cmp lr, r7");
    test_disasm(0x45c0, "cmp r8, r8");
    test_disasm(0x45c1, "cmp r9, r8");
    test_disasm(0x45c2, "cmp sl, r8");
    test_disasm(0x45c3, "cmp fp, r8");
    test_disasm(0x45c4, "cmp ip, r8");
    test_disasm(0x45c5, "cmp sp, r8");
    test_disasm(0x45c6, "cmp lr, r8");
    test_disasm(0x45c8, "cmp r8, r9");
    test_disasm(0x45c9, "cmp r9, r9");
    test_disasm(0x45ca, "cmp sl, r9");
    test_disasm(0x45cb, "cmp fp, r9");
    test_disasm(0x45cc, "cmp ip, r9");
    test_disasm(0x45cd, "cmp sp, r9");
    test_disasm(0x45ce, "cmp lr, r9");
    test_disasm(0x45d0, "cmp r8, sl");
    test_disasm(0x45d1, "cmp r9, sl");
    test_disasm(0x45d2, "cmp sl, sl");
    test_disasm(0x45d3, "cmp fp, sl");
    test_disasm(0x45d4, "cmp ip, sl");
    test_disasm(0x45d5, "cmp sp, sl");
    test_disasm(0x45d6, "cmp lr, sl");
    test_disasm(0x45d8, "cmp r8, fp");
    test_disasm(0x45d9, "cmp r9, fp");
    test_disasm(0x45da, "cmp sl, fp");
    test_disasm(0x45db, "cmp fp, fp");
    test_disasm(0x45dc, "cmp ip, fp");
    test_disasm(0x45dd, "cmp sp, fp");
    test_disasm(0x45de, "cmp lr, fp");
    test_disasm(0x45e0, "cmp r8, ip");
    test_disasm(0x45e1, "cmp r9, ip");
    test_disasm(0x45e2, "cmp sl, ip");
    test_disasm(0x45e3, "cmp fp, ip");
    test_disasm(0x45e4, "cmp ip, ip");
    test_disasm(0x45e5, "cmp sp, ip");
    test_disasm(0x45e6, "cmp lr, ip");
    test_disasm(0x45f0, "cmp r8, lr");
    test_disasm(0x45f1, "cmp r9, lr");
    test_disasm(0x45f2, "cmp sl, lr");
    test_disasm(0x45f3, "cmp fp, lr");
    test_disasm(0x45f4, "cmp ip, lr");
    test_disasm(0x45f5, "cmp sp, lr");
    test_disasm(0x45f6, "cmp lr, lr");

    test_disasm(0x4600, "mov r0, r0");
    test_disasm(0x4601, "mov r1, r0");
    test_disasm(0x4607, "mov r7, r0");
    test_disasm(0x4608, "mov r0, r1");
    test_disasm(0x4609, "mov r1, r1");
    test_disasm(0x460f, "mov r7, r1");
    test_disasm(0x4638, "mov r0, r7");
    test_disasm(0x4639, "mov r1, r7");
    test_disasm(0x463f, "mov r7, r7");
    test_disasm(0x4640, "mov r0, r8");
    test_disasm(0x4641, "mov r1, r8");
    test_disasm(0x4647, "mov r7, r8");
    test_disasm(0x4648, "mov r0, r9");
    test_disasm(0x4649, "mov r1, r9");
    test_disasm(0x464f, "mov r7, r9");
    test_disasm(0x4650, "mov r0, sl");
    test_disasm(0x4651, "mov r1, sl");
    test_disasm(0x4657, "mov r7, sl");
    test_disasm(0x4658, "mov r0, fp");
    test_disasm(0x4659, "mov r1, fp");
    test_disasm(0x465f, "mov r7, fp");
    test_disasm(0x4660, "mov r0, ip");
    test_disasm(0x4661, "mov r1, ip");
    test_disasm(0x4667, "mov r7, ip");
    test_disasm(0x4668, "mov r0, sp");
    test_disasm(0x4669, "mov r1, sp");
    test_disasm(0x466f, "mov r7, sp");
    test_disasm(0x4670, "mov r0, lr");
    test_disasm(0x4671, "mov r1, lr");
    test_disasm(0x4677, "mov r7, lr");
    test_disasm(0x4678, "mov r0, pc");
    test_disasm(0x4679, "mov r1, pc");
    test_disasm(0x467f, "mov r7, pc");
    test_disasm(0x4680, "mov r8, r0");
    test_disasm(0x4681, "mov r9, r0");
    test_disasm(0x4682, "mov sl, r0");
    test_disasm(0x4683, "mov fp, r0");
    test_disasm(0x4684, "mov ip, r0");
    test_disasm(0x4685, "mov sp, r0");
    test_disasm(0x4686, "mov lr, r0");
    test_disasm(0x4687, "mov pc, r0");
    test_disasm(0x4688, "mov r8, r1");
    test_disasm(0x4689, "mov r9, r1");
    test_disasm(0x468a, "mov sl, r1");
    test_disasm(0x468b, "mov fp, r1");
    test_disasm(0x468c, "mov ip, r1");
    test_disasm(0x468d, "mov sp, r1");
    test_disasm(0x468e, "mov lr, r1");
    test_disasm(0x468f, "mov pc, r1");
    test_disasm(0x46b8, "mov r8, r7");
    test_disasm(0x46b9, "mov r9, r7");
    test_disasm(0x46ba, "mov sl, r7");
    test_disasm(0x46bb, "mov fp, r7");
    test_disasm(0x46bc, "mov ip, r7");
    test_disasm(0x46bd, "mov sp, r7");
    test_disasm(0x46be, "mov lr, r7");
    test_disasm(0x46bf, "mov pc, r7");
    test_disasm(0x46c0, "nop");         // mov r8, r8
    test_disasm(0x46c1, "mov r9, r8");
    test_disasm(0x46c2, "mov sl, r8");
    test_disasm(0x46c3, "mov fp, r8");
    test_disasm(0x46c4, "mov ip, r8");
    test_disasm(0x46c5, "mov sp, r8");
    test_disasm(0x46c6, "mov lr, r8");
    test_disasm(0x46c7, "mov pc, r8");
    test_disasm(0x46c8, "mov r8, r9");
    test_disasm(0x46c9, "mov r9, r9");
    test_disasm(0x46ca, "mov sl, r9");
    test_disasm(0x46cb, "mov fp, r9");
    test_disasm(0x46cc, "mov ip, r9");
    test_disasm(0x46cd, "mov sp, r9");
    test_disasm(0x46ce, "mov lr, r9");
    test_disasm(0x46cf, "mov pc, r9");
    test_disasm(0x46d0, "mov r8, sl");
    test_disasm(0x46d1, "mov r9, sl");
    test_disasm(0x46d2, "mov sl, sl");
    test_disasm(0x46d3, "mov fp, sl");
    test_disasm(0x46d4, "mov ip, sl");
    test_disasm(0x46d5, "mov sp, sl");
    test_disasm(0x46d6, "mov lr, sl");
    test_disasm(0x46d7, "mov pc, sl");
    test_disasm(0x46d8, "mov r8, fp");
    test_disasm(0x46d9, "mov r9, fp");
    test_disasm(0x46da, "mov sl, fp");
    test_disasm(0x46db, "mov fp, fp");
    test_disasm(0x46dc, "mov ip, fp");
    test_disasm(0x46dd, "mov sp, fp");
    test_disasm(0x46de, "mov lr, fp");
    test_disasm(0x46df, "mov pc, fp");
    test_disasm(0x46e0, "mov r8, ip");
    test_disasm(0x46e1, "mov r9, ip");
    test_disasm(0x46e2, "mov sl, ip");
    test_disasm(0x46e3, "mov fp, ip");
    test_disasm(0x46e4, "mov ip, ip");
    test_disasm(0x46e5, "mov sp, ip");
    test_disasm(0x46e6, "mov lr, ip");
    test_disasm(0x46e7, "mov pc, ip");
    test_disasm(0x46e8, "mov r8, sp");
    test_disasm(0x46e9, "mov r9, sp");
    test_disasm(0x46ea, "mov sl, sp");
    test_disasm(0x46eb, "mov fp, sp");
    test_disasm(0x46ec, "mov ip, sp");
    test_disasm(0x46ee, "mov lr, sp");
    test_disasm(0x46f0, "mov r8, lr");
    test_disasm(0x46f1, "mov r9, lr");
    test_disasm(0x46f2, "mov sl, lr");
    test_disasm(0x46f3, "mov fp, lr");
    test_disasm(0x46f4, "mov ip, lr");
    test_disasm(0x46f5, "mov sp, lr");
    test_disasm(0x46f6, "mov lr, lr");
    test_disasm(0x46f7, "mov pc, lr");
    test_disasm(0x46f8, "mov r8, pc");
    test_disasm(0x46f9, "mov r9, pc");
    test_disasm(0x46fa, "mov sl, pc");
    test_disasm(0x46fb, "mov fp, pc");
    test_disasm(0x46fc, "mov ip, pc");
    test_disasm(0x46fe, "mov lr, pc");

    test_disasm(0x4700, "bx r0");
    test_disasm(0x4708, "bx r1");
    test_disasm(0x4710, "bx r2");
    test_disasm(0x4718, "bx r3");
    test_disasm(0x4720, "bx r4");
    test_disasm(0x4728, "bx r5");
    test_disasm(0x4730, "bx r6");
    test_disasm(0x4738, "bx r7");
    test_disasm(0x4740, "bx r8");
    test_disasm(0x4748, "bx r9");
    test_disasm(0x4750, "bx sl");
    test_disasm(0x4758, "bx fp");
    test_disasm(0x4760, "bx ip");
    test_disasm(0x4768, "bx sp");
    test_disasm(0x4770, "bx lr");
    test_disasm(0x4778, "bx pc");

    test_disasm(0x4800, "ldr r0, [pc, #0]");
    test_disasm(0x4801, "ldr r0, [pc, #4]");
    test_disasm(0x48ff, "ldr r0, [pc, #1020]");
    test_disasm(0x4900, "ldr r1, [pc, #0]");
    test_disasm(0x4901, "ldr r1, [pc, #4]");
    test_disasm(0x49ff, "ldr r1, [pc, #1020]");
    test_disasm(0x4f00, "ldr r7, [pc, #0]");
    test_disasm(0x4f01, "ldr r7, [pc, #4]");
    test_disasm(0x4fff, "ldr r7, [pc, #1020]");

    test_disasm(0x5000, "str r0, [r0, r0]");
    test_disasm(0x5001, "str r1, [r0, r0]");
    test_disasm(0x5007, "str r7, [r0, r0]");
    test_disasm(0x5008, "str r0, [r1, r0]");
    test_disasm(0x5009, "str r1, [r1, r0]");
    test_disasm(0x500f, "str r7, [r1, r0]");
    test_disasm(0x5038, "str r0, [r7, r0]");
    test_disasm(0x5039, "str r1, [r7, r0]");
    test_disasm(0x503f, "str r7, [r7, r0]");
    test_disasm(0x5040, "str r0, [r0, r1]");
    test_disasm(0x5041, "str r1, [r0, r1]");
    test_disasm(0x5047, "str r7, [r0, r1]");
    test_disasm(0x5048, "str r0, [r1, r1]");
    test_disasm(0x5049, "str r1, [r1, r1]");
    test_disasm(0x504f, "str r7, [r1, r1]");
    test_disasm(0x5078, "str r0, [r7, r1]");
    test_disasm(0x5079, "str r1, [r7, r1]");
    test_disasm(0x507f, "str r7, [r7, r1]");
    test_disasm(0x51c0, "str r0, [r0, r7]");
    test_disasm(0x51c1, "str r1, [r0, r7]");
    test_disasm(0x51c7, "str r7, [r0, r7]");
    test_disasm(0x51c8, "str r0, [r1, r7]");
    test_disasm(0x51c9, "str r1, [r1, r7]");
    test_disasm(0x51cf, "str r7, [r1, r7]");
    test_disasm(0x51f8, "str r0, [r7, r7]");
    test_disasm(0x51f9, "str r1, [r7, r7]");
    test_disasm(0x51ff, "str r7, [r7, r7]");

    test_disasm(0x5200, "strh r0, [r0, r0]");
    test_disasm(0x5201, "strh r1, [r0, r0]");
    test_disasm(0x5207, "strh r7, [r0, r0]");
    test_disasm(0x5208, "strh r0, [r1, r0]");
    test_disasm(0x5209, "strh r1, [r1, r0]");
    test_disasm(0x520f, "strh r7, [r1, r0]");
    test_disasm(0x5238, "strh r0, [r7, r0]");
    test_disasm(0x5239, "strh r1, [r7, r0]");
    test_disasm(0x523f, "strh r7, [r7, r0]");
    test_disasm(0x5240, "strh r0, [r0, r1]");
    test_disasm(0x5241, "strh r1, [r0, r1]");
    test_disasm(0x5247, "strh r7, [r0, r1]");
    test_disasm(0x5248, "strh r0, [r1, r1]");
    test_disasm(0x5249, "strh r1, [r1, r1]");
    test_disasm(0x524f, "strh r7, [r1, r1]");
    test_disasm(0x5278, "strh r0, [r7, r1]");
    test_disasm(0x5279, "strh r1, [r7, r1]");
    test_disasm(0x527f, "strh r7, [r7, r1]");
    test_disasm(0x53c0, "strh r0, [r0, r7]");
    test_disasm(0x53c1, "strh r1, [r0, r7]");
    test_disasm(0x53c7, "strh r7, [r0, r7]");
    test_disasm(0x53c8, "strh r0, [r1, r7]");
    test_disasm(0x53c9, "strh r1, [r1, r7]");
    test_disasm(0x53cf, "strh r7, [r1, r7]");
    test_disasm(0x53f8, "strh r0, [r7, r7]");
    test_disasm(0x53f9, "strh r1, [r7, r7]");
    test_disasm(0x53ff, "strh r7, [r7, r7]");

    test_disasm(0x5400, "strb r0, [r0, r0]");
    test_disasm(0x5401, "strb r1, [r0, r0]");
    test_disasm(0x5407, "strb r7, [r0, r0]");
    test_disasm(0x5408, "strb r0, [r1, r0]");
    test_disasm(0x5409, "strb r1, [r1, r0]");
    test_disasm(0x540f, "strb r7, [r1, r0]");
    test_disasm(0x5438, "strb r0, [r7, r0]");
    test_disasm(0x5439, "strb r1, [r7, r0]");
    test_disasm(0x543f, "strb r7, [r7, r0]");
    test_disasm(0x5440, "strb r0, [r0, r1]");
    test_disasm(0x5441, "strb r1, [r0, r1]");
    test_disasm(0x5447, "strb r7, [r0, r1]");
    test_disasm(0x5448, "strb r0, [r1, r1]");
    test_disasm(0x5449, "strb r1, [r1, r1]");
    test_disasm(0x544f, "strb r7, [r1, r1]");
    test_disasm(0x5478, "strb r0, [r7, r1]");
    test_disasm(0x5479, "strb r1, [r7, r1]");
    test_disasm(0x547f, "strb r7, [r7, r1]");
    test_disasm(0x55c0, "strb r0, [r0, r7]");
    test_disasm(0x55c1, "strb r1, [r0, r7]");
    test_disasm(0x55c7, "strb r7, [r0, r7]");
    test_disasm(0x55c8, "strb r0, [r1, r7]");
    test_disasm(0x55c9, "strb r1, [r1, r7]");
    test_disasm(0x55cf, "strb r7, [r1, r7]");
    test_disasm(0x55f8, "strb r0, [r7, r7]");
    test_disasm(0x55f9, "strb r1, [r7, r7]");
    test_disasm(0x55ff, "strb r7, [r7, r7]");

    test_disasm(0x5600, "ldrsb r0, [r0, r0]");
    test_disasm(0x5601, "ldrsb r1, [r0, r0]");
    test_disasm(0x5607, "ldrsb r7, [r0, r0]");
    test_disasm(0x5608, "ldrsb r0, [r1, r0]");
    test_disasm(0x5609, "ldrsb r1, [r1, r0]");
    test_disasm(0x560f, "ldrsb r7, [r1, r0]");
    test_disasm(0x5638, "ldrsb r0, [r7, r0]");
    test_disasm(0x5639, "ldrsb r1, [r7, r0]");
    test_disasm(0x563f, "ldrsb r7, [r7, r0]");
    test_disasm(0x5640, "ldrsb r0, [r0, r1]");
    test_disasm(0x5641, "ldrsb r1, [r0, r1]");
    test_disasm(0x5647, "ldrsb r7, [r0, r1]");
    test_disasm(0x5648, "ldrsb r0, [r1, r1]");
    test_disasm(0x5649, "ldrsb r1, [r1, r1]");
    test_disasm(0x564f, "ldrsb r7, [r1, r1]");
    test_disasm(0x5678, "ldrsb r0, [r7, r1]");
    test_disasm(0x5679, "ldrsb r1, [r7, r1]");
    test_disasm(0x567f, "ldrsb r7, [r7, r1]");
    test_disasm(0x57c0, "ldrsb r0, [r0, r7]");
    test_disasm(0x57c1, "ldrsb r1, [r0, r7]");
    test_disasm(0x57c7, "ldrsb r7, [r0, r7]");
    test_disasm(0x57c8, "ldrsb r0, [r1, r7]");
    test_disasm(0x57c9, "ldrsb r1, [r1, r7]");
    test_disasm(0x57cf, "ldrsb r7, [r1, r7]");
    test_disasm(0x57f8, "ldrsb r0, [r7, r7]");
    test_disasm(0x57f9, "ldrsb r1, [r7, r7]");
    test_disasm(0x57ff, "ldrsb r7, [r7, r7]");

    test_disasm(0x5800, "ldr r0, [r0, r0]");
    test_disasm(0x5801, "ldr r1, [r0, r0]");
    test_disasm(0x5807, "ldr r7, [r0, r0]");
    test_disasm(0x5808, "ldr r0, [r1, r0]");
    test_disasm(0x5809, "ldr r1, [r1, r0]");
    test_disasm(0x580f, "ldr r7, [r1, r0]");
    test_disasm(0x5838, "ldr r0, [r7, r0]");
    test_disasm(0x5839, "ldr r1, [r7, r0]");
    test_disasm(0x583f, "ldr r7, [r7, r0]");
    test_disasm(0x5840, "ldr r0, [r0, r1]");
    test_disasm(0x5841, "ldr r1, [r0, r1]");
    test_disasm(0x5847, "ldr r7, [r0, r1]");
    test_disasm(0x5848, "ldr r0, [r1, r1]");
    test_disasm(0x5849, "ldr r1, [r1, r1]");
    test_disasm(0x584f, "ldr r7, [r1, r1]");
    test_disasm(0x5878, "ldr r0, [r7, r1]");
    test_disasm(0x5879, "ldr r1, [r7, r1]");
    test_disasm(0x587f, "ldr r7, [r7, r1]");
    test_disasm(0x59c0, "ldr r0, [r0, r7]");
    test_disasm(0x59c1, "ldr r1, [r0, r7]");
    test_disasm(0x59c7, "ldr r7, [r0, r7]");
    test_disasm(0x59c8, "ldr r0, [r1, r7]");
    test_disasm(0x59c9, "ldr r1, [r1, r7]");
    test_disasm(0x59cf, "ldr r7, [r1, r7]");
    test_disasm(0x59f8, "ldr r0, [r7, r7]");
    test_disasm(0x59f9, "ldr r1, [r7, r7]");
    test_disasm(0x59ff, "ldr r7, [r7, r7]");

    test_disasm(0x5a00, "ldrh r0, [r0, r0]");
    test_disasm(0x5a01, "ldrh r1, [r0, r0]");
    test_disasm(0x5a07, "ldrh r7, [r0, r0]");
    test_disasm(0x5a08, "ldrh r0, [r1, r0]");
    test_disasm(0x5a09, "ldrh r1, [r1, r0]");
    test_disasm(0x5a0f, "ldrh r7, [r1, r0]");
    test_disasm(0x5a38, "ldrh r0, [r7, r0]");
    test_disasm(0x5a39, "ldrh r1, [r7, r0]");
    test_disasm(0x5a3f, "ldrh r7, [r7, r0]");
    test_disasm(0x5a40, "ldrh r0, [r0, r1]");
    test_disasm(0x5a41, "ldrh r1, [r0, r1]");
    test_disasm(0x5a47, "ldrh r7, [r0, r1]");
    test_disasm(0x5a48, "ldrh r0, [r1, r1]");
    test_disasm(0x5a49, "ldrh r1, [r1, r1]");
    test_disasm(0x5a4f, "ldrh r7, [r1, r1]");
    test_disasm(0x5a78, "ldrh r0, [r7, r1]");
    test_disasm(0x5a79, "ldrh r1, [r7, r1]");
    test_disasm(0x5a7f, "ldrh r7, [r7, r1]");
    test_disasm(0x5bc0, "ldrh r0, [r0, r7]");
    test_disasm(0x5bc1, "ldrh r1, [r0, r7]");
    test_disasm(0x5bc7, "ldrh r7, [r0, r7]");
    test_disasm(0x5bc8, "ldrh r0, [r1, r7]");
    test_disasm(0x5bc9, "ldrh r1, [r1, r7]");
    test_disasm(0x5bcf, "ldrh r7, [r1, r7]");
    test_disasm(0x5bf8, "ldrh r0, [r7, r7]");
    test_disasm(0x5bf9, "ldrh r1, [r7, r7]");
    test_disasm(0x5bff, "ldrh r7, [r7, r7]");

    test_disasm(0x5c00, "ldrb r0, [r0, r0]");
    test_disasm(0x5c01, "ldrb r1, [r0, r0]");
    test_disasm(0x5c07, "ldrb r7, [r0, r0]");
    test_disasm(0x5c08, "ldrb r0, [r1, r0]");
    test_disasm(0x5c09, "ldrb r1, [r1, r0]");
    test_disasm(0x5c0f, "ldrb r7, [r1, r0]");
    test_disasm(0x5c38, "ldrb r0, [r7, r0]");
    test_disasm(0x5c39, "ldrb r1, [r7, r0]");
    test_disasm(0x5c3f, "ldrb r7, [r7, r0]");
    test_disasm(0x5c40, "ldrb r0, [r0, r1]");
    test_disasm(0x5c41, "ldrb r1, [r0, r1]");
    test_disasm(0x5c47, "ldrb r7, [r0, r1]");
    test_disasm(0x5c48, "ldrb r0, [r1, r1]");
    test_disasm(0x5c49, "ldrb r1, [r1, r1]");
    test_disasm(0x5c4f, "ldrb r7, [r1, r1]");
    test_disasm(0x5c78, "ldrb r0, [r7, r1]");
    test_disasm(0x5c79, "ldrb r1, [r7, r1]");
    test_disasm(0x5c7f, "ldrb r7, [r7, r1]");
    test_disasm(0x5dc0, "ldrb r0, [r0, r7]");
    test_disasm(0x5dc1, "ldrb r1, [r0, r7]");
    test_disasm(0x5dc7, "ldrb r7, [r0, r7]");
    test_disasm(0x5dc8, "ldrb r0, [r1, r7]");
    test_disasm(0x5dc9, "ldrb r1, [r1, r7]");
    test_disasm(0x5dcf, "ldrb r7, [r1, r7]");
    test_disasm(0x5df8, "ldrb r0, [r7, r7]");
    test_disasm(0x5df9, "ldrb r1, [r7, r7]");
    test_disasm(0x5dff, "ldrb r7, [r7, r7]");

    test_disasm(0x5e00, "ldrsh r0, [r0, r0]");
    test_disasm(0x5e01, "ldrsh r1, [r0, r0]");
    test_disasm(0x5e07, "ldrsh r7, [r0, r0]");
    test_disasm(0x5e08, "ldrsh r0, [r1, r0]");
    test_disasm(0x5e09, "ldrsh r1, [r1, r0]");
    test_disasm(0x5e0f, "ldrsh r7, [r1, r0]");
    test_disasm(0x5e38, "ldrsh r0, [r7, r0]");
    test_disasm(0x5e39, "ldrsh r1, [r7, r0]");
    test_disasm(0x5e3f, "ldrsh r7, [r7, r0]");
    test_disasm(0x5e40, "ldrsh r0, [r0, r1]");
    test_disasm(0x5e41, "ldrsh r1, [r0, r1]");
    test_disasm(0x5e47, "ldrsh r7, [r0, r1]");
    test_disasm(0x5e48, "ldrsh r0, [r1, r1]");
    test_disasm(0x5e49, "ldrsh r1, [r1, r1]");
    test_disasm(0x5e4f, "ldrsh r7, [r1, r1]");
    test_disasm(0x5e78, "ldrsh r0, [r7, r1]");
    test_disasm(0x5e79, "ldrsh r1, [r7, r1]");
    test_disasm(0x5e7f, "ldrsh r7, [r7, r1]");
    test_disasm(0x5fc0, "ldrsh r0, [r0, r7]");
    test_disasm(0x5fc1, "ldrsh r1, [r0, r7]");
    test_disasm(0x5fc7, "ldrsh r7, [r0, r7]");
    test_disasm(0x5fc8, "ldrsh r0, [r1, r7]");
    test_disasm(0x5fc9, "ldrsh r1, [r1, r7]");
    test_disasm(0x5fcf, "ldrsh r7, [r1, r7]");
    test_disasm(0x5ff8, "ldrsh r0, [r7, r7]");
    test_disasm(0x5ff9, "ldrsh r1, [r7, r7]");
    test_disasm(0x5fff, "ldrsh r7, [r7, r7]");

    test_disasm(0x6000, "str r0, [r0, #0]");
    test_disasm(0x6001, "str r1, [r0, #0]");
    test_disasm(0x6007, "str r7, [r0, #0]");
    test_disasm(0x6008, "str r0, [r1, #0]");
    test_disasm(0x6009, "str r1, [r1, #0]");
    test_disasm(0x600f, "str r7, [r1, #0]");
    test_disasm(0x6038, "str r0, [r7, #0]");
    test_disasm(0x6039, "str r1, [r7, #0]");
    test_disasm(0x603f, "str r7, [r7, #0]");
    test_disasm(0x6040, "str r0, [r0, #4]");
    test_disasm(0x6041, "str r1, [r0, #4]");
    test_disasm(0x6047, "str r7, [r0, #4]");
    test_disasm(0x6048, "str r0, [r1, #4]");
    test_disasm(0x6049, "str r1, [r1, #4]");
    test_disasm(0x604f, "str r7, [r1, #4]");
    test_disasm(0x6078, "str r0, [r7, #4]");
    test_disasm(0x6079, "str r1, [r7, #4]");
    test_disasm(0x607f, "str r7, [r7, #4]");
    test_disasm(0x67c0, "str r0, [r0, #124]");
    test_disasm(0x67c1, "str r1, [r0, #124]");
    test_disasm(0x67c7, "str r7, [r0, #124]");
    test_disasm(0x67c8, "str r0, [r1, #124]");
    test_disasm(0x67c9, "str r1, [r1, #124]");
    test_disasm(0x67cf, "str r7, [r1, #124]");
    test_disasm(0x67f8, "str r0, [r7, #124]");
    test_disasm(0x67f9, "str r1, [r7, #124]");
    test_disasm(0x67ff, "str r7, [r7, #124]");

    test_disasm(0x6800, "ldr r0, [r0, #0]");
    test_disasm(0x6801, "ldr r1, [r0, #0]");
    test_disasm(0x6807, "ldr r7, [r0, #0]");
    test_disasm(0x6808, "ldr r0, [r1, #0]");
    test_disasm(0x6809, "ldr r1, [r1, #0]");
    test_disasm(0x680f, "ldr r7, [r1, #0]");
    test_disasm(0x6838, "ldr r0, [r7, #0]");
    test_disasm(0x6839, "ldr r1, [r7, #0]");
    test_disasm(0x683f, "ldr r7, [r7, #0]");
    test_disasm(0x6840, "ldr r0, [r0, #4]");
    test_disasm(0x6841, "ldr r1, [r0, #4]");
    test_disasm(0x6847, "ldr r7, [r0, #4]");
    test_disasm(0x6848, "ldr r0, [r1, #4]");
    test_disasm(0x6849, "ldr r1, [r1, #4]");
    test_disasm(0x684f, "ldr r7, [r1, #4]");
    test_disasm(0x6878, "ldr r0, [r7, #4]");
    test_disasm(0x6879, "ldr r1, [r7, #4]");
    test_disasm(0x687f, "ldr r7, [r7, #4]");
    test_disasm(0x6fc0, "ldr r0, [r0, #124]");
    test_disasm(0x6fc1, "ldr r1, [r0, #124]");
    test_disasm(0x6fc7, "ldr r7, [r0, #124]");
    test_disasm(0x6fc8, "ldr r0, [r1, #124]");
    test_disasm(0x6fc9, "ldr r1, [r1, #124]");
    test_disasm(0x6fcf, "ldr r7, [r1, #124]");
    test_disasm(0x6ff8, "ldr r0, [r7, #124]");
    test_disasm(0x6ff9, "ldr r1, [r7, #124]");
    test_disasm(0x6fff, "ldr r7, [r7, #124]");

    test_disasm(0x7000, "strb r0, [r0, #0]");
    test_disasm(0x7001, "strb r1, [r0, #0]");
    test_disasm(0x7007, "strb r7, [r0, #0]");
    test_disasm(0x7008, "strb r0, [r1, #0]");
    test_disasm(0x7009, "strb r1, [r1, #0]");
    test_disasm(0x700f, "strb r7, [r1, #0]");
    test_disasm(0x7038, "strb r0, [r7, #0]");
    test_disasm(0x7039, "strb r1, [r7, #0]");
    test_disasm(0x703f, "strb r7, [r7, #0]");
    test_disasm(0x7040, "strb r0, [r0, #1]");
    test_disasm(0x7041, "strb r1, [r0, #1]");
    test_disasm(0x7047, "strb r7, [r0, #1]");
    test_disasm(0x7048, "strb r0, [r1, #1]");
    test_disasm(0x7049, "strb r1, [r1, #1]");
    test_disasm(0x704f, "strb r7, [r1, #1]");
    test_disasm(0x7078, "strb r0, [r7, #1]");
    test_disasm(0x7079, "strb r1, [r7, #1]");
    test_disasm(0x707f, "strb r7, [r7, #1]");
    test_disasm(0x77c0, "strb r0, [r0, #31]");
    test_disasm(0x77c1, "strb r1, [r0, #31]");
    test_disasm(0x77c7, "strb r7, [r0, #31]");
    test_disasm(0x77c8, "strb r0, [r1, #31]");
    test_disasm(0x77c9, "strb r1, [r1, #31]");
    test_disasm(0x77cf, "strb r7, [r1, #31]");
    test_disasm(0x77f8, "strb r0, [r7, #31]");
    test_disasm(0x77f9, "strb r1, [r7, #31]");
    test_disasm(0x77ff, "strb r7, [r7, #31]");

    test_disasm(0x7800, "ldrb r0, [r0, #0]");
    test_disasm(0x7801, "ldrb r1, [r0, #0]");
    test_disasm(0x7807, "ldrb r7, [r0, #0]");
    test_disasm(0x7808, "ldrb r0, [r1, #0]");
    test_disasm(0x7809, "ldrb r1, [r1, #0]");
    test_disasm(0x780f, "ldrb r7, [r1, #0]");
    test_disasm(0x7838, "ldrb r0, [r7, #0]");
    test_disasm(0x7839, "ldrb r1, [r7, #0]");
    test_disasm(0x783f, "ldrb r7, [r7, #0]");
    test_disasm(0x7840, "ldrb r0, [r0, #1]");
    test_disasm(0x7841, "ldrb r1, [r0, #1]");
    test_disasm(0x7847, "ldrb r7, [r0, #1]");
    test_disasm(0x7848, "ldrb r0, [r1, #1]");
    test_disasm(0x7849, "ldrb r1, [r1, #1]");
    test_disasm(0x784f, "ldrb r7, [r1, #1]");
    test_disasm(0x7878, "ldrb r0, [r7, #1]");
    test_disasm(0x7879, "ldrb r1, [r7, #1]");
    test_disasm(0x787f, "ldrb r7, [r7, #1]");
    test_disasm(0x7fc0, "ldrb r0, [r0, #31]");
    test_disasm(0x7fc1, "ldrb r1, [r0, #31]");
    test_disasm(0x7fc7, "ldrb r7, [r0, #31]");
    test_disasm(0x7fc8, "ldrb r0, [r1, #31]");
    test_disasm(0x7fc9, "ldrb r1, [r1, #31]");
    test_disasm(0x7fcf, "ldrb r7, [r1, #31]");
    test_disasm(0x7ff8, "ldrb r0, [r7, #31]");
    test_disasm(0x7ff9, "ldrb r1, [r7, #31]");
    test_disasm(0x7fff, "ldrb r7, [r7, #31]");

    test_disasm(0x8000, "strh r0, [r0, #0]");
    test_disasm(0x8001, "strh r1, [r0, #0]");
    test_disasm(0x8007, "strh r7, [r0, #0]");
    test_disasm(0x8008, "strh r0, [r1, #0]");
    test_disasm(0x8009, "strh r1, [r1, #0]");
    test_disasm(0x800f, "strh r7, [r1, #0]");
    test_disasm(0x8038, "strh r0, [r7, #0]");
    test_disasm(0x8039, "strh r1, [r7, #0]");
    test_disasm(0x803f, "strh r7, [r7, #0]");
    test_disasm(0x8040, "strh r0, [r0, #2]");
    test_disasm(0x8041, "strh r1, [r0, #2]");
    test_disasm(0x8047, "strh r7, [r0, #2]");
    test_disasm(0x8048, "strh r0, [r1, #2]");
    test_disasm(0x8049, "strh r1, [r1, #2]");
    test_disasm(0x804f, "strh r7, [r1, #2]");
    test_disasm(0x8078, "strh r0, [r7, #2]");
    test_disasm(0x8079, "strh r1, [r7, #2]");
    test_disasm(0x807f, "strh r7, [r7, #2]");
    test_disasm(0x87c0, "strh r0, [r0, #62]");
    test_disasm(0x87c1, "strh r1, [r0, #62]");
    test_disasm(0x87c7, "strh r7, [r0, #62]");
    test_disasm(0x87c8, "strh r0, [r1, #62]");
    test_disasm(0x87c9, "strh r1, [r1, #62]");
    test_disasm(0x87cf, "strh r7, [r1, #62]");
    test_disasm(0x87f8, "strh r0, [r7, #62]");
    test_disasm(0x87f9, "strh r1, [r7, #62]");
    test_disasm(0x87ff, "strh r7, [r7, #62]");

    test_disasm(0x8800, "ldrh r0, [r0, #0]");
    test_disasm(0x8801, "ldrh r1, [r0, #0]");
    test_disasm(0x8807, "ldrh r7, [r0, #0]");
    test_disasm(0x8808, "ldrh r0, [r1, #0]");
    test_disasm(0x8809, "ldrh r1, [r1, #0]");
    test_disasm(0x880f, "ldrh r7, [r1, #0]");
    test_disasm(0x8838, "ldrh r0, [r7, #0]");
    test_disasm(0x8839, "ldrh r1, [r7, #0]");
    test_disasm(0x883f, "ldrh r7, [r7, #0]");
    test_disasm(0x8840, "ldrh r0, [r0, #2]");
    test_disasm(0x8841, "ldrh r1, [r0, #2]");
    test_disasm(0x8847, "ldrh r7, [r0, #2]");
    test_disasm(0x8848, "ldrh r0, [r1, #2]");
    test_disasm(0x8849, "ldrh r1, [r1, #2]");
    test_disasm(0x884f, "ldrh r7, [r1, #2]");
    test_disasm(0x8878, "ldrh r0, [r7, #2]");
    test_disasm(0x8879, "ldrh r1, [r7, #2]");
    test_disasm(0x887f, "ldrh r7, [r7, #2]");
    test_disasm(0x8fc0, "ldrh r0, [r0, #62]");
    test_disasm(0x8fc1, "ldrh r1, [r0, #62]");
    test_disasm(0x8fc7, "ldrh r7, [r0, #62]");
    test_disasm(0x8fc8, "ldrh r0, [r1, #62]");
    test_disasm(0x8fc9, "ldrh r1, [r1, #62]");
    test_disasm(0x8fcf, "ldrh r7, [r1, #62]");
    test_disasm(0x8ff8, "ldrh r0, [r7, #62]");
    test_disasm(0x8ff9, "ldrh r1, [r7, #62]");
    test_disasm(0x8fff, "ldrh r7, [r7, #62]");

    test_disasm(0x9000, "str r0, [sp, #0]");
    test_disasm(0x9001, "str r0, [sp, #4]");
    test_disasm(0x90ff, "str r0, [sp, #1020]");
    test_disasm(0x9100, "str r1, [sp, #0]");
    test_disasm(0x9101, "str r1, [sp, #4]");
    test_disasm(0x91ff, "str r1, [sp, #1020]");
    test_disasm(0x9700, "str r7, [sp, #0]");
    test_disasm(0x9701, "str r7, [sp, #4]");
    test_disasm(0x97ff, "str r7, [sp, #1020]");

    test_disasm(0x9800, "ldr r0, [sp, #0]");
    test_disasm(0x9801, "ldr r0, [sp, #4]");
    test_disasm(0x98ff, "ldr r0, [sp, #1020]");
    test_disasm(0x9900, "ldr r1, [sp, #0]");
    test_disasm(0x9901, "ldr r1, [sp, #4]");
    test_disasm(0x99ff, "ldr r1, [sp, #1020]");
    test_disasm(0x9f00, "ldr r7, [sp, #0]");
    test_disasm(0x9f01, "ldr r7, [sp, #4]");
    test_disasm(0x9fff, "ldr r7, [sp, #1020]");

    test_disasm(0xa000, "add r0, pc, #0");
    test_disasm(0xa001, "add r0, pc, #4");
    test_disasm(0xa0ff, "add r0, pc, #1020");
    test_disasm(0xa100, "add r1, pc, #0");
    test_disasm(0xa101, "add r1, pc, #4");
    test_disasm(0xa1ff, "add r1, pc, #1020");
    test_disasm(0xa700, "add r7, pc, #0");
    test_disasm(0xa701, "add r7, pc, #4");
    test_disasm(0xa7ff, "add r7, pc, #1020");

    test_disasm(0xa800, "add r0, sp, #0");
    test_disasm(0xa801, "add r0, sp, #4");
    test_disasm(0xa8ff, "add r0, sp, #1020");
    test_disasm(0xa900, "add r1, sp, #0");
    test_disasm(0xa901, "add r1, sp, #4");
    test_disasm(0xa9ff, "add r1, sp, #1020");
    test_disasm(0xaf00, "add r7, sp, #0");
    test_disasm(0xaf01, "add r7, sp, #4");
    test_disasm(0xafff, "add r7, sp, #1020");

    test_disasm(0xb000, "add sp, #0");
    test_disasm(0xb001, "add sp, #4");
    test_disasm(0xb07f, "add sp, #508");

    test_disasm(0xb080, "sub sp, #0");
    test_disasm(0xb081, "sub sp, #4");
    test_disasm(0xb0ff, "sub sp, #508");

#if 0
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

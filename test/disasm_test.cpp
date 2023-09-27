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

#include "gtest_main.cpp"

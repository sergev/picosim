        .section .text
        .global _start
_start:

// XPSR - combined Program Status Register
//
// 31_30_29_28_________________________5_4_3_2_1_0
//  n  z  c  v                          exception
// ---APSR----                         ---IPSR----

        ldr r7, =0xffffffff
        msr APSR_nzcvq, r7
        mrs r0, APSR        // expect f000_0000

        msr IAPSR_nzcvq, r7
        mrs r1, IAPSR       // expect f000_0000

        msr EAPSR_nzcvq, r7
        mrs r2, EAPSR       // expect f000_0000

        msr XPSR_nzcvq, r7
        mrs r3, XPSR        // expect f000_0000

        msr IPSR, r7
        mrs r4, IPSR        // expect 0000_0000

        msr EPSR, r7
        mrs r5, EPSR        // expect 0000_0000

        msr IEPSR, r7
        mrs r6, IEPSR       // expect 0000_0000

        movs r7, #1         // syscall exit(status)
        svc #0

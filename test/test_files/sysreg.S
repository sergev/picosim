        .section .text
        .global _start
_start:

// MSP register.

        ldr r7, =0xffffffff

        mrs r0, MSP         // save old value
        msr MSP, r7         // write all ones
        mrs r1, MSP         // expect ffff_fffc
        msr MSP, r0         // restore old value

// PSP register.

        mrs r0, PSP         // save old value
        msr PSP, r7         // write all ones
        mrs r2, PSP         // expect ffff_fffc
        msr PSP, r0         // restore old value

// PRIMASK register.
//
// 31_______________________________1__0
// -----------reserved--------------- pm
//
        movs r0, #0

        msr PRIMASK, r7
        mrs r3, PRIMASK     // expect 0000_0001

        msr PRIMASK, r0
        mrs r4, PRIMASK     // expect 0000_0000

// CONTROL register.
//
// 31___________________________2___1_____0
// -----------reserved----------- spsel npriv

        ldr r7, =0xfffffffe // avoid nPRIV bit

        msr CONTROL, r7
        mrs r5, CONTROL     // expect 0000_0002

        msr CONTROL, r0
        mrs r6, CONTROL     // expect 0000_0000

        movs r7, #1         // syscall exit(status)
        svc #0

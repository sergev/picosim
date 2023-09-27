        .section .text
        .global _start
_start:

// XPSR - combined Program Status Register
//
// 31_30_29_28_________________________5_4_3_2_1_0
//  n  z  c  v                          exception
// ---APSR----                         ---IPSR----


        movs r0, #0x80

        movs r1, #0x40
        movs r2, #0x20
        movs r3, #0x10
        movs r4, #8
        movs r5, #4
        movs r6, #2

        movs r7, #1      // syscall exit(status)
        svc #0



APSR    = 20000000
IAPSR   = 20000000
EAPSR   = 20000000
XPSR    = 20000000
IPSR    = 00000000
EPSR    = 00000000
IEPSR   = 00000000
MSP     = 20041F68
PSP     = FFFFFFFC
PRIMASK = 00000000
CONTROL = 00000000

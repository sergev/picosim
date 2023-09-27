        .section .text
        .global _start
_start:
        ldr r1, =0x7502fe1f
        movs r1, sp         // r15
        movs sp, r5

        ldr r2, =0xc015a134
        movs r2, lr         // r14
        movs lr, r3

        ldr r4, =0xd306fde3
        movs r4, sp         // r13
        movs sp, r6

        ldr r0, =0x43f705a9
        movs r0, ip         // r12
        movs ip, r1

        ldr r7, =0x8c832ed2
        movs r7, fp         // r11
        movs fp, r2

        ldr r7, =0xf83a2582
        movs r7, sl         // r10
        movs sl, r0

        ldr r7, =0xabe76d49
        movs r7, r9
        movs r9, r4

        ldr r7, =0xc5e3fe7d
        movs r7, r8

        movs r7, #1             // syscall exit(status)
        svc #0

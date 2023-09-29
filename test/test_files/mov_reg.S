        .section .text
        .global _start
_start:
        mov r5, pc

        ldr r1, =0xc015a134
        mov lr, r1          // r14
        mov r3, lr

        ldr r4, =0xd306fde3
        mov sp, r4          // r13
        mov r6, sp

        ldr r2, =0x43f705a9
        mov ip, r2          // r12
        mov r1, ip

        ldr r0, =0x8c832ed2
        mov fp, r0          // r11
        mov r2, fp

        ldr r7, =0xf83a2582
        mov sl, r7          // r10
        mov r0, sl

        ldr r7, =0xabe76d49
        mov r9, r7
        mov r4, r9

        ldr r7, =0xc5e3fe7d
        mov r8, r7

        svc #1              // syscall exit(status)

        .section .text
        .global _start
_start:
        ldr r5, =0x7502fe1f
        movs r1, r5

        ldr r7, =0xc015a134
        movs r3, r7

        ldr r0, =0x8c832ed2
        movs r2, r0

        ldr r6, =0xd306fde3
        movs r4, r6

        svc #1              // syscall exit(status)

        .section .text
        .global _start
_start:
        ldr r3, =0xc015a134
        rev16 r0, r3

        ldr r4, =0xd306fde3
        rev16 r2, r4

        ldr r5, =0x776dd37e
        rev16 r4, r5

        ldr r7, =0x549c13ba
        rev16 r6, r7

        movs r7, #1         // syscall exit(status)
        svc #0

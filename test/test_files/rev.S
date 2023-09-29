        .section .text
        .global _start
_start:
        ldr r3, =0xc015a134
        rev r0, r3

        ldr r4, =0xd306fde3
        rev r2, r4

        ldr r5, =0x776dd37e
        rev r4, r5

        ldr r7, =0x549c13ba
        rev r6, r7

        svc #1              // syscall exit()

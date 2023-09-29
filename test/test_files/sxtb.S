        .section .text
        .global _start
_start:
        ldr r3, =0xc015a134
        sxtb r0, r3

        ldr r4, =0xd306fde3
        sxtb r2, r4

        ldr r5, =0x776dd37e
        sxtb r4, r5

        ldr r7, =0x549c13ba
        sxtb r6, r7

        svc #1              // syscall exit()

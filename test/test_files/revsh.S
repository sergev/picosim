        .section .text
        .global _start
_start:
        ldr r3, =0xc015a134
        revsh r0, r3

        ldr r4, =0xd306fde3
        revsh r2, r4

        ldr r5, =0x776dd37e
        revsh r4, r5

        ldr r7, =0x549c13ba
        revsh r6, r7

        svc #1              // syscall exit()

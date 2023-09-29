        .section .text
        .global _start
_start:
        ldr r0, =0x7502fe1f
        ldr r1, =0xc015a134
        ldr r2, =0x8c832ed2
        ldr r3, =0xd306fde3
        ldr r4, =0xd965247d
        ldr r5, =0xcf097d2e
        ldr r6, =0x36204518

        svc #1              // syscall exit(status)

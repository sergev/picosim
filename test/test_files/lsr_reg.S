        .section .text
        .global _start
_start:
        ldr r0, =0xc015a134
        movs r3, #0
        lsr r0, r3
        mrs r1, APSR

        ldr r2, =0xd306fde3
        movs r4, #32
        lsr r2, r4
        mrs r3, APSR

        ldr r4, =0x776dd37e
        movs r5, #20
        lsr r4, r5
        mrs r5, APSR

        ldr r6, =0x549c13ba
        movs r7, #7
        lsr r6, r7
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit()

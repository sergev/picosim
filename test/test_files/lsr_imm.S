        .section .text
        .global _start
_start:
        ldr r3, =0xc015a134
        lsr r0, r3, #0
        mrs r1, APSR

        ldr r4, =0xd306fde3
        lsr r2, r4, #32
        mrs r3, APSR

        ldr r5, =0x776dd37e
        lsr r4, r5, #20
        mrs r5, APSR

        ldr r7, =0x549c13ba
        lsr r6, r7, #7
        mrs r7, APSR
        mov r8, r7

        movs r7, #1         // syscall exit(status)
        svc #0

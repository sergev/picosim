        .section .text
        .global _start
_start:
        ldr r3, =0xc015a134
        lsl r0, r3, #0
        mrs r1, APSR

        ldr r4, =0xd306fde3
        lsl r2, r4, #31
        mrs r3, APSR

        ldr r5, =0x776dd37e
        lsl r4, r5, #20
        mrs r5, APSR

        ldr r7, =0x549c13ba
        lsl r6, r7, #7
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit()

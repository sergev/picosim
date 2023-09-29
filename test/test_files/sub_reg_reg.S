        .section .text
        .global _start
_start:
        ldr r5, =0x7502fe1f
        ldr r3, =0xc015a134
        sub r0, r5, r3
        mrs r1, APSR

        ldr r7, =0x8c832ed2
        ldr r4, =0xd306fde3
        sub r2, r7, r4
        mrs r3, APSR

        ldr r6, =0x9b74a3db
        ldr r5, =0x776dd37e
        sub r4, r6, r5
        mrs r5, APSR

        ldr r6, =0xce671cdd
        ldr r7, =0x549c13ba
        sub r6, r6, r7
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit(status)

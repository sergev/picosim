        .section .text
        .global _start
_start:
        ldr r0, =0x7502f000
        ldr r3, =0xc0100000
        mul r0, r3
        mrs r1, APSR

        ldr r2, =0x8c832ed2
        ldr r4, =0xd306fde3
        mul r2, r4
        mrs r3, APSR

        ldr r4, =0x9b74a3db
        ldr r5, =0x776dd37e
        mul r4, r5
        mrs r5, APSR

        ldr r6, =0xce671cdd
        ldr r7, =0x549c13ba
        mul r6, r7
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit(status)

        .section .text
        .global _start
_start:
        ldr r0, =0x7502fe1f
        ldr r3, =0xc015a134
        bic r0, r3
        mrs r1, APSR

        ldr r2, =0x8c832ed2
        ldr r4, =0xd306fde3
        bic r2, r4
        mrs r3, APSR

        ldr r4, =0x9b74a3db
        ldr r5, =0x776dd37e
        bic r4, r5
        mrs r5, APSR

        ldr r6, =0xce671cdd
        ldr r7, =0xffff0000
        bic r6, r7
        mrs r7, APSR
        mov r8, r7

        movs r7, #1         // syscall exit(status)
        svc #0

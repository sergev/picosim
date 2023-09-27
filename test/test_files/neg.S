        .section .text
        .global _start
_start:
        movs r3, #0
        neg r0, r3
        mrs r1, APSR

        ldr r4, =0xd306fde3
        neg r2, r4
        mrs r3, APSR

        ldr r5, =0x776dd37e
        neg r4, r5
        mrs r5, APSR

        ldr r7, =0x549c13ba
        neg r6, r7
        mrs r7, APSR
        mov r8, r7

        movs r7, #1         // syscall exit(status)
        svc #0

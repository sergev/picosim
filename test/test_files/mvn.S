        .section .text
        .global _start
_start:
        ldr r3, =0xc015a134
        mvn r0, r3
        mrs r1, APSR

        ldr r4, =0xd306fde3
        mvn r2, r4
        mrs r3, APSR

        ldr r5, =0x776dd37e
        mvn r4, r5
        mrs r5, APSR

        ldr r7, =0x549c13ba
        mvn r6, r7
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit()

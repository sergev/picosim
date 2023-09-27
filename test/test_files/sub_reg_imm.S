        .section .text
        .global _start
_start:
        ldr r3, =0x80000000
        sub r0, r3, #4
        mrs r1, APSR

        ldr r5, =1
        sub r2, r5, #3
        mrs r3, APSR

        ldr r6, =-1
        sub r4, r6, #6
        mrs r5, APSR

        ldr r7, =0
        sub r6, r7, #7
        mrs r7, APSR
        mov r8, r7

        movs r7, #1         // syscall exit(status)
        svc #0

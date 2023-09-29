        .section .text
        .global _start
_start:
        ldr r3, =0x7fffffff
        add r0, r3, #4
        mrs r1, APSR

        ldr r5, =-1
        add r2, r5, #3
        mrs r3, APSR

        ldr r6, =1
        add r4, r6, #6
        mrs r5, APSR

        ldr r7, =0
        add r6, r7, #7
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit(status)

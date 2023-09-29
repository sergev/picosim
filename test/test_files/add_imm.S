        .section .text
        .global _start
_start:
        ldr r0, =0x7fffffff
        add r0, #66
        mrs r1, APSR

        ldr r2, =-1
        add r2, #91
        mrs r3, APSR

        ldr r4, =1
        add r4, #140
        mrs r5, APSR

        ldr r6, =0
        add r6, #165
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit(status)

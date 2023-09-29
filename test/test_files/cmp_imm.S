        .section .text
        .global _start
_start:
        ldr r0, =0x80000000
        cmp r0, #66
        mrs r1, APSR

        ldr r2, =100
        cmp r2, #91
        mrs r3, APSR

        ldr r4, =-1
        cmp r4, #140
        mrs r5, APSR

        ldr r6, =0
        cmp r6, #165
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit(status)

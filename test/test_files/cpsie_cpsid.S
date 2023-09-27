        .section .text
        .global _start
_start:

        cpsie i
        mrs r0, PRIMASK     // expect 0000_0000

        cpsid i
        mrs r1, PRIMASK     // expect 0000_0001

        cpsie i
        mrs r2, PRIMASK     // expect 0000_0000

        movs r7, #1         // syscall exit(status)
        svc #0

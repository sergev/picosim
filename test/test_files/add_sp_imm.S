        .section .text
        .global _start
_start:
        ldr r0, =1234567890
        mov sp, r0          // 1234567890

        add sp, #0
        mov r1, sp          // 1234567890

        add sp, #428
        mov r2, sp          // 1234568318

        add sp, #280
        mov r3, sp          // 1234568598

        add sp, #52
        mov r4, sp          // 1234568650

        add sp, #348
        mov r5, sp          // 1234568998

        add sp, #508
        mov r6, sp          // 1234569506

        movs r7, #1         // syscall exit(status)
        svc #0

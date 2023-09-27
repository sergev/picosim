        .section .text
        .global _start
_start:
        ldr r0, =1234567890
        mov sp, r0          // 1234567890

        sub sp, #0
        mov r1, sp          // 1234567890

        sub sp, #428
        mov r2, sp          // 1234567462

        sub sp, #280
        mov r3, sp          // 1234567182

        sub sp, #52
        mov r4, sp          // 1234567130

        sub sp, #348
        mov r5, sp          // 1234566782

        sub sp, #508
        mov r6, sp          // 1234566274

        movs r7, #1         // syscall exit(status)
        svc #0

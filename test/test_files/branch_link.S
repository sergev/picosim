        .section .text
        .global _start
_start:
        movs r7, #1         // syscall exit(status)

        bl 1f
        svc #0              // fail
2:
        mov r2, lr
        bl 3f
        svc #0              // fail
1:
        mov r1, lr
        bl 2b
        svc #0              // fail
3:
        mov r3, lr
        svc #0              // pass

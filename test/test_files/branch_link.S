        .section .text
        .global _start
_start:
        bl 1f
        svc #1              // syscall exit() - fail
2:
        mov r2, lr
        bl 3f
        svc #1              // fail
1:
        mov r1, lr
        bl 2b
        svc #1              // fail
3:
        mov r3, lr
        svc #1              // syscall exit() - pass

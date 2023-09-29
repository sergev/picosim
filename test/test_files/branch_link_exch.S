        .section .text
        .global _start
_start:
        ldr r1, =1f
        blx r1
        svc #1              // syscall exit() - fail
2:
        mov r2, lr
        ldr r3, =3f
        mov lr, r3
        blx lr
        svc #1              // fail
1:
        mov r1, lr
        ldr r2, =2b
        blx r2
        svc #1              // fail
3:
        mov r3, lr
        svc #1              // syscall exit() - pass

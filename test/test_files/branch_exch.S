        .section .text
        .global _start
_start:
        ldr r1, =1f
        bx r1
        svc #1              // syscall exit() - fail
2:
        ldr r3, =3f
        bx r3
        svc #1              // fail
1:
        ldr r2, =2b
        bx r2
        svc #1              // fail
3:
        svc #1              // syscall exit() - pass

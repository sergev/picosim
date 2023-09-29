        .section .text
        .global _start
_start:
        movs r7, #1         // syscall exit(status)

        ldr r1, =1f
        bx r1
        svc #0              // fail
2:
        ldr r3, =3f
        bx r3
        svc #0              // fail
1:
        ldr r2, =2b
        bx r2
        svc #0              // fail
3:
        svc #0              // pass

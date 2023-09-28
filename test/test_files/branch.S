        .section .text
        .global _start
_start:
        movs r7, #1         // syscall exit(status)

        b 1f
        svc #0              // fail
2:
        b 3f
        svc #0              // fail
1:
        b 2b
        svc #0              // fail
3:
        svc #0              // pass

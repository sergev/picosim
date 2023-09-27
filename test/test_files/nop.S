        .section .text
        .global _start
_start:
        nop
        nop
        nop
        nop

        movs r7, #1         // syscall exit(status)
        svc #0

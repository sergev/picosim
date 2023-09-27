        .section .text
        .global _start
_start:
        nop
        dsb
        dmb
        isb

        movs r7, #1         // syscall exit(status)
        svc #0

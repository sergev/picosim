        .section .text
        .global _start
_start:
        nop
        dsb
        dmb
        isb

        svc #1              // syscall exit(status)

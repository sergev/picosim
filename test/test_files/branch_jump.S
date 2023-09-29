        .section .text
        .global _start
_start:
        b 1f
        svc #1              // syscall exit() - FAIL
2:
        b 3f
        svc #1              // syscall exit() - FAIL
1:
        b 2b
        svc #1              // syscall exit() - FAIL
3:
        svc #1              // syscall exit() - PASS

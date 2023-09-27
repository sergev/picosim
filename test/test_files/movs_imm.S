        .section .text
        .global _start
_start:
        movs r0, #0x80
        movs r1, #0x40
        movs r2, #0x20
        movs r3, #0x10
        movs r4, #8
        movs r5, #4
        movs r6, #2
        movs r7, #1      // syscall exit(status)
        svc #0

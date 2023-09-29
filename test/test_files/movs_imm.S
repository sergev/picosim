        .section .text
        .global _start
_start:
        movs r0, #0xd3
        movs r1, #0x9d
        movs r2, #0x97
        movs r3, #0x1a
        movs r4, #0x91
        movs r5, #0xd7
        movs r6, #0x29
        movs r7, #0xab
        svc #1              // syscall exit(status)

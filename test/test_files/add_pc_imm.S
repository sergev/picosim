        .section .text
        .global _start
_start:
        add r0, pc, #0x178  // 0x8178
        add r1, pc, #0x320  // 0x8322
        add r2, pc, #0x1dc  // 0x81e0
        add r3, pc, #0x118  // 0x811e
        add r4, pc, #0x274  // 0x827c
        add r5, pc, #0x220  // 0x822a
        add r6, pc, #0x158  // 0x8164

        svc #1              // syscall exit(status)

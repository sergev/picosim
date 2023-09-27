        .section .text
        .global _start
_start:
        ldr r0, =1234567890
        mov sp, r0

        add r0, sp, #0      // 1234567890
        add r1, sp, #428    // 1234568318
        add r2, sp, #280    // 1234568170
        add r3, sp, #52     // 1234567942
        add r4, sp, #848    // 1234568738
        add r5, sp, #988    // 1234568878
        add r6, sp, #1020   // 1234568910

        movs r7, #1         // syscall exit(status)
        svc #0

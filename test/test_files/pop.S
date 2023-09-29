        .section .text
        .global _start
_start:
        adr r0, data0
        mov sp, r0
        pop {r1, r3, pc}    // note branch

        svc #1              // syscall exit() - FAIL

jump_here:
        pop {r0, r2, r4, r5, r6}

        svc #1              // syscall exit() - PASS

        .align 2
data0:  .long   0x7502fe1f  // r1
        .long   0xc015a134  // r3
        .long   jump_here   // pc
        .long   0x36204518  // r0
        .long   0x8c832ed2  // r2
        .long   0xd306fde3  // r4
        .long   0xd965247d  // r5
        .long   0xcf097d2e  // r6
                            // SP here

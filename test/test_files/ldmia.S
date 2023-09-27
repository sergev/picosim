        .section .text
        .global _start
_start:
        adr r0, data0
        ldmia r0!, {r1, r3}

        adr r4, data4
        ldmia r4, {r2, r4, r5, r6}

        movs r7, #1         // syscall exit(status)
        svc #0

        .align 2
data0:  .long   0x7502fe1f  // r1
        .long   0xc015a134  // r3
                            // r0 here
data4:
        .long   0x8c832ed2  // r2
        .long   0xd306fde3  // r4
        .long   0xd965247d  // r5
        .long   0xcf097d2e  // r6

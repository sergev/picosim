        .section .text
        .global _start
_start:
        ldr r0, =loc0
        ldr r1, =0x23456789
        stmia r0!, {r0, r1}

        ldr r2, =0x3456789a
        ldr r3, =0x456789ab
        ldr r4, =0x56789abc
        ldr r5, =loc8
        ldr r6, =0x789abcde
        ldr r7, =0x89abcdef
        stmia r5!, {r2, r3, r4, r6, r7}

        movs r7, #1         // syscall exit(status)
        svc #0

        .data
        .align 2
loc0:   .word 0x9b74a3db    // r0
loc4:   .word 0x776dd37e    // r1
                            // new r0 here
loc8:   .word 0x5fed565c    // r2
loc12:  .word 0x751b4f33    // r3
loc16:  .word 0x0173b5c5    // r4
loc20:  .word 0xce671cdd    // r6
loc24:  .word 0x549c13ba    // r7
                            // new r5 here
loc28:  .word 0xd933cd91

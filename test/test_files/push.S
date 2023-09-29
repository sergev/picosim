        .section .text
        .global _start
_start:
        ldr r0, =0x9abcdef1
        mov lr, r0
        ldr r0, =loc32
        mov sp, r0
        ldr r0, =0x12345678
        ldr r1, =0x23456789
        ldr r2, =0x3456789a
        ldr r3, =0x456789ab
        ldr r4, =0x56789abc
        ldr r5, =0x6789abcd
        ldr r6, =0x789abcde
        ldr r7, =0x89abcdef

        push {r0, r1}

        push {r2, r3, r4, r6, r7, lr}

        svc #1              // syscall exit(status)

        .data
        .align 2
loc0:   .word 0x9b74a3db    // r2
loc4:   .word 0x776dd37e    // r3
loc8:   .word 0x5fed565c    // r4
loc12:  .word 0x751b4f33    // r6
loc16:  .word 0x0173b5c5    // r7
loc20:  .word 0xce671cdd    // LR
loc24:  .word 0x549c13ba    // r0
loc28:  .word 0xd933cd91    // r1
loc32:  .word 0x1129f706    // initial SP

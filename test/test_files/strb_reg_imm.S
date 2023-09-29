        .section .text
        .global _start
_start:
        ldr r1, =imm0
        ldr r0, =0x12
        strb r0, [r1, #31]  // data + 31

        ldr r2, =imm4
        ldr r1, =0x23
        strb r1, [r2, #25]  // data + 29

        ldr r3, =imm12
        ldr r2, =0x34
        strb r2, [r3, #15]  // data + 27

        ldr r4, =imm4
        ldr r3, =0x45
        strb r3, [r4, #15]  // data + 19

        ldr r5, =imm8
        ldr r4, =0x56
        strb r4, [r5, #1]   // data + 9

        ldr r6, =imm0
        ldr r5, =0x67
        strb r5, [r6, #0]   // data + 0

        ldr r7, =imm20
        ldr r6, =0x78
        strb r6, [r7, #10]  // data + 30

        svc #1              // syscall exit(status)

        .data
imm0:   .word 0x9b74a3db
imm4:   .word 0x776dd37e
imm8:   .word 0x5fed565c
imm12:  .word 0x751b4f33
imm16:  .word 0x0173b5c5
imm20:  .word 0xce671cdd
imm24:  .word 0x549c13ba
imm28:  .word 0xd933cd91

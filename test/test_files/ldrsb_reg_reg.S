        .section .text
        .global _start
_start:
        adr r1, imm0
        movs r2, #31
        ldrsb r0, [r1, r2]  // 0xd9

        adr r2, imm4
        movs r3, #25
        ldrsb r1, [r2, r3]  // 0xcd

        adr r3, imm12
        movs r4, #15
        ldrsb r2, [r3, r4]  // 0x54

        adr r4, imm4
        movs r5, #15
        ldrsb r3, [r4, r5]  // 0x01

        adr r5, imm8
        movs r6, #1
        ldrsb r4, [r5, r6]  // 0x56

        adr r6, imm0
        movs r7, #0
        ldrsb r5, [r6, r7]  // 0xdb

        adr r6, imm20
        movs r7, #10
        ldrsb r6, [r6, r7]  // 0x33

        svc #1              // syscall exit(status)

        .align 2
imm0:   .word 0x9b74a3db
imm4:   .word 0x776dd37e
imm8:   .word 0x5fed565c
imm12:  .word 0x751b4f33
imm16:  .word 0x0173b5c5
imm20:  .word 0xce671cdd
imm24:  .word 0x549c13ba
imm28:  .word 0xd933cd91

        .section .text
        .global _start
_start:
        adr r1, imm0
        ldrh r0, [r1, #62]  // 0x67c5

        adr r2, imm8
        ldrh r1, [r2, #50]  // 0xe0d8

        adr r3, imm16
        ldrh r2, [r3, #30]  // 0x8ce5

        adr r4, imm4
        ldrh r3, [r4, #30]  // 0xf8f4

        adr r5, imm0
        ldrh r4, [r5, #18]  // 0x0173

        adr r6, imm0
        ldrh r5, [r6, #0]   // 0xa3db

        adr r7, imm36
        ldrh r6, [r7, #20]  // 0x7fa2

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
imm32:  .word 0xf8f45bb2
imm36:  .word 0x494fa207
imm40:  .word 0x9c36aaf6
imm44:  .word 0x8ce521d1
imm48:  .word 0xcaa5267a
imm52:  .word 0x740a57d7
imm56:  .word 0xe0d87fa2
imm60:  .word 0x67c594f8

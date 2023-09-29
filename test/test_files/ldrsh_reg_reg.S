        .section .text
        .global _start
_start:
        adr r1, imm0
        movs r2, #62
        ldrsh r0, [r1, r2]  // 0x67c5

        adr r2, imm8
        movs r3, #50
        ldrsh r1, [r2, r3]  // 0xffffe0d8

        adr r3, imm16
        movs r4, #30
        ldrsh r2, [r3, r4]  // 0xffff8ce5

        adr r4, imm4
        movs r5, #30
        ldrsh r3, [r4, r5]  // 0xfffff8f4

        adr r5, imm0
        movs r6, #18
        ldrsh r4, [r5, r6]  // 0x0173

        adr r6, imm0
        movs r7, #0
        ldrsh r5, [r6, r7]  // 0xffffa3db

        adr r6, imm36
        movs r7, #20
        ldrsh r6, [r6, r7]  // 0x7fa2

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

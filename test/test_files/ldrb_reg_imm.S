        .section .text
        .global _start
_start:
        adr r7, imm0
        ldrb r0, [r7, #31]  // 0xd9

        adr r2, imm4
        ldrb r1, [r2, #25]  // 0xcd

        adr r3, imm12
        ldrb r2, [r3, #15]  // 0x54

        adr r4, imm4
        ldrb r3, [r4, #15]  // 0x01

        adr r5, imm8
        ldrb r4, [r5, #1]   // 0x56

        adr r6, imm0
        ldrb r5, [r6, #0]   // 0xdb

        adr r7, imm20
        ldrb r6, [r7, #10]  // 0x33

        movs r7, #1         // syscall exit(status)
        svc #0

imm0:   .word 0x9b74a3db
imm4:   .word 0x776dd37e
imm8:   .word 0x5fed565c
imm12:  .word 0x751b4f33
imm16:  .word 0x0173b5c5
imm20:  .word 0xce671cdd
imm24:  .word 0x549c13ba
imm28:  .word 0xd933cd91

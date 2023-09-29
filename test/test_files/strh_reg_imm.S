        .section .text
        .global _start
_start:
        ldr r1, =imm0
        ldr r0, =0x1234
        strh r0, [r1, #62]  // data + 62

        ldr r2, =imm8
        ldr r1, =0x2345
        strh r1, [r2, #50]  // data + 58

        ldr r3, =imm16
        ldr r2, =0x3456
        strh r2, [r3, #30]  // data + 46

        ldr r4, =imm4
        ldr r3, =0x4567
        strh r3, [r4, #30]  // data + 34

        ldr r5, =imm0
        ldr r4, =0x5678
        strh r4, [r5, #18]  //  data + 18

        ldr r6, =imm0
        ldr r5, =0x6789
        strh r5, [r6, #0]   // data + 0

        ldr r7, =imm36
        ldr r6, =0x789a
        strh r6, [r7, #20]  // data + 56

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
imm32:  .word 0xf8f45bb2
imm36:  .word 0x494fa207
imm40:  .word 0x9c36aaf6
imm44:  .word 0x8ce521d1
imm48:  .word 0xcaa5267a
imm52:  .word 0x740a57d7
imm56:  .word 0xe0d87fa2
imm60:  .word 0x67c594f8

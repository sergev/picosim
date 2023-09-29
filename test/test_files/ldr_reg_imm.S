        .section .text
        .global _start
_start:
        adr r1, imm0
        ldr r0, [r1, #124]  // 0x573d213c

        adr r2, imm12
        ldr r1, [r2, #100]  // 0x3903762c

        adr r3, imm28
        ldr r2, [r3, #60]   // 0x561469da

        adr r4, imm4
        ldr r3, [r4, #60]   // 0x4e6c6ac2

        adr r5, imm0
        ldr r4, [r5, #36]   // 0x494fa207

        adr r6, imm0
        ldr r5, [r6, #0]    // 0x9b74a3db

        adr r7, imm36
        ldr r6, [r7, #40]   // 0x6c94ee62

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
imm64:  .word 0x4e6c6ac2
imm68:  .word 0x108d20e9
imm72:  .word 0x847c96ca
imm76:  .word 0x6c94ee62
imm80:  .word 0xd19e5e4d
imm84:  .word 0x0ecf11eb
imm88:  .word 0x561469da
imm92:  .word 0xa64a41a1
imm96:  .word 0x3983f0ba
imm100: .word 0x096d513a
imm104: .word 0x326dac09
imm108: .word 0x83beceab
imm112: .word 0x3903762c
imm116: .word 0x34ea4ace
imm120: .word 0x28c38ee0
imm124: .word 0x573d213c

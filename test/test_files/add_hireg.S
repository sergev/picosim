        .section .text
        .global _start
_start:
        // R8
        ldr r0, =0x7502fe1f
        ldr r3, =0xc015a134
        mov r8, r0
        add r8, r3

        // R9
        ldr r0, =0x8c832ed2
        ldr r4, =0xd306fde3
        mov r9, r0
        add r9, r4

        // SL = R10, Stack Limit
        ldr r0, =0x9b74a3db
        ldr r5, =0x776dd37e
        mov sl, r0
        add sl, r5

        // FP = R11, Frame Pointer
        ldr r0, =0xce671cdd
        ldr r7, =0x549c13ba
        mov fp, r0
        add fp, r7

        // IP = R12, Intra-Procedure scratch register
        ldr r0, =0xe22a7d31
        ldr r2, =0x13d01f65
        mov ip, r0
        add ip, r2

        // SP = R13, Main Stack Pointer
        ldr r0, =0xeb514512
        ldr r1, =0x1bc420c2
        mov sp, r0
        add sp, r1

        // LR = R14, Link Register
        ldr r0, =0xd3b288b8
        ldr r6, =0x8e22e5dc
        mov lr, r0
        add lr, r6

        // PC = R15, Program Counter
        movs r0, #0
        add pc, r0

        // Skip this instruction
        svc #1              // syscall exit() - FAIL

        add r8, r8
        add r6, r9
        add r5, sl
        add r4, fp
        add r3, ip
        add r2, sp
        add r1, lr
        add r0, pc

        svc #1              // syscall exit() - PASS

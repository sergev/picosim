        .section .text
        .global _start
_start:
        // R8
        ldr r0, =0x7502fe1f
        ldr r3, =0xc015a134
        mov r8, r0
        cmp r8, r3
        mrs r0, APSR

        // R9
        ldr r1, =0x8c832ed2
        ldr r4, =0xd306fde3
        mov r9, r1
        cmp r9, r4
        mrs r1, APSR

        // SL = R10, Stack Limit
        ldr r2, =0x9b74a3db
        ldr r5, =0x776dd37e
        mov sl, r2
        cmp sl, r5
        mrs r2, APSR

        // FP = R11, Frame Pointer
        ldr r3, =0xce671cdd
        ldr r7, =0x549c13ba
        mov fp, r3
        cmp fp, r7
        mrs r3, APSR

        // IP = R12, Intra-Procedure scratch register
        ldr r4, =0xe22a7d31
        ldr r5, =0x13d01f65
        mov ip, r4
        cmp ip, r5
        mrs r4, APSR

        // SP = R13, Main Stack Pointer
        ldr r5, =0xeb514512
        ldr r6, =0x1bc420c2
        mov sp, r5
        cmp sp, r6
        mrs r5, APSR

        // LR = R14, Link Register
        ldr r6, =0xd3b288b8
        ldr r7, =0x8e22e5dc
        mov lr, r6
        cmp lr, r7
        mrs r6, APSR

        // PC = R15, Program Counter
        ldr r7, =after_svc
        cmp pc, r7
        mrs r7, APSR
        mov r8, r7

        svc #1              // syscall exit()
after_svc:

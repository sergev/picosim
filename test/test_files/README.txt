Tests for instructions:

File                Instruction
------------------------------------------
        (Data Transfer)
movs_imm.S          movs r1, #255
movs_reg.S          movs r1, r2
mov_reg.S           mov r11, r12
psr.S               msr APSR, r1
sysreg.S            mrs r1, PRIMASK
cpsie_cpsid.S       cpsie i; cpsid i
nop.S               nop

        (Memory Load)
ldr_reg_imm.S       ldr r1, [r2, #124]
ldr_sp.S            ldr r1, [sp, #1020]
ldr_pc.S            ldr r1, [pc, #1020]
ldr_reg_reg.S       ldr r1, [r2, r3]
ldrb_reg_imm.S      ldrb r1, [r2, #31]
ldrb_reg_reg.S      ldrb r1, [r2, r3]
ldrsb_reg_reg.S     ldrsb r1, [r2, r3]
ldrh_reg_imm.S      ldrh r1, [r2, #62]
ldrh_reg_reg.S      ldrh r1, [r2, r3]
ldrsh_reg_reg.S     ldrsh r1, [r2, r3]
ldmia.S             ldmia r7, {r0, r1, r2, r3, r4, r5, r6, r7}

        (Memory Store)
str_reg_imm.S       str r1, [r2, #124]
str_sp.S            str r1, [sp, #1020]
str_reg_reg.S       str r1, [r2, r3]
strb_reg_imm.S      strb r1, [r2, #31]
strb_reg_reg.S      strb r1, [r2, r3]
strh_reg_imm.S      strh r1, [r2, #62]
strh_reg_reg.S      strh r1, [r2, r3]
stmia.S             stmia r7!, {r0, r1, r2, r3, r4, r5, r6}

        (Stack)
push.S              push {r1, r2, lr}
pop.S               pop {r1, r2, pc}

        (Arithmetic operations)
add_reg_reg.S       add r1, r2, r3
add_reg_imm.S       add r1, r2, #7
add_imm.S           add r1, #255
add_hireg.S         add r11, r12
add_pc_imm.S        add r1, pc, #1020
add_reg_sp_imm.S    add r1, sp, #1020
add_sp_imm.S        add sp, #508
adc.S               adc r1, r2
sub_reg_reg.S       sub r1, r2, r3
sub_reg_imm.S       sub r1, r2, #7
sub_imm.S           sub r1, #255
sub_sp_imm.S        sub sp, #508
sbc.S               sbc r1, r2
neg.S               neg r1, r2
mul.S               mul r1, r2
cmp_imm.S           cmp r1, #255
cmp_reg.S           cmp r1, r2
cmp_hireg.S         cmp r11, r12
cmn.S               cmn r1, r2

        (Logic operations)
and.S               and r1, r2
orr.S               orr r1, r2
eor.S               eor r1, r2
bic.S               bic r1, r2
mvn.S               mvn r1, r2
                    tst r1, r2

        (Shift operations)
                    asr r1, r2, #32
                    asr r1, r2
                    lsl r1, r2, #31
                    lsl r1, r2
                    lsr r1, r2, #32
                    lsr r1, r2
                    ror r1, r2

        (Bit Shuffle)
                    rev r1, r2
                    rev16 r1, r2
                    revsh r1, r2
                    sxth r1, r2
                    sxtb r1, r2
                    uxth r1, r2
                    uxtb r1, r2

        (Branching)
                    b.n 0x12345678
                    bXX.n 0x12345678
                    bl 0x12f45678
                    bx r1

        (Barriers)
                    dsb
                    dmb
                    isb

        (Events)
                    bkpt 0x00ff
                    udf #255
write.S             svc 255
                    wfi
                    wfe
                    sev
                    yield

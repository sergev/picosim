Tests for instructions:

File            Instruction or feature
--------------------------------------
movs_imm.S      movs r1, #255
movs_reg.S      movs r1, r2
mov_reg.S       mov r11, r12
msr.S           msr APSR, r1
mrs.S           mrs r1, PRIMASK

write.S         syscall write()

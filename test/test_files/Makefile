CC              = arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb
OBJDUMP         = arm-none-eabi-objdump
CFLAGS          = -O -Wall -Werror
LDFLAGS         = -nostdlib -static
PROG            = movs_imm.elf \
                  movs_reg.elf \
                  mov_reg.elf \
                  ldr_pc.elf \
                  ldr_reg_imm.elf \
                  ldr_sp.elf \
                  ldr_reg_reg.elf \
                  ldrb_reg_imm.elf \
                  ldrb_reg_reg.elf \
                  ldrsb_reg_reg.elf \
                  ldrh_reg_imm.elf \
                  ldrh_reg_reg.elf \
                  ldrsh_reg_reg.elf \
                  str_reg_imm.elf \
                  str_reg_reg.elf \
                  str_sp.elf \
                  strb_reg_imm.elf \
                  strb_reg_reg.elf \
                  strh_reg_imm.elf \
                  strh_reg_reg.elf \
                  add_reg_sp_imm.elf \
                  add_pc_imm.elf \
                  add_reg_reg.elf \
                  add_reg_imm.elf \
                  add_hireg.elf \
                  add_imm.elf \
                  add_sp_imm.elf \
                  sub_reg_reg.elf \
                  sub_reg_imm.elf \
                  sub_imm.elf \
                  sub_sp_imm.elf \
                  cmp_imm.elf \
                  cmp_reg.elf \
                  cmp_hireg.elf \
                  cmn.elf \
                  psr.elf \
                  sysreg.elf \
                  nop.elf \
                  cpsie_cpsid.elf \
                  ldmia.elf \
                  stmia.elf \
                  pop.elf \
                  push.elf \
                  adc.elf \
                  sbc.elf \
                  neg.elf \
                  mul.elf \
                  and.elf \
                  orr.elf \
                  eor.elf \
                  bic.elf \
                  mvn.elf \
                  write.elf \
                  hello.elf

all:            $(PROG)

clean:
		rm -f *.elf *.o *.dis

hello.elf:      hello.o
		$(CC) $< -lc -lgloss-linux -o $@
		$(OBJDUMP) -d -S $@ > hello.dis

%.elf:          %.o
		$(CC) $(LDFLAGS) $< -o $@
		$(OBJDUMP) -d -S $@ > $*.dis

CC              = arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb
OBJDUMP         = arm-none-eabi-objdump
CFLAGS          = -O -Wall -Werror
LDFLAGS         = -nostdlib -static
PROG            = movs_imm.elf \
                  ldr_pc.elf \
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

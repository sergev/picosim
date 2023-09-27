CC              = arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb
OBJDUMP         = arm-none-eabi-objdump
CFLAGS          = -O -Wall -Werror
LDFLAGS         =
LIBS            = -lc -lgloss-linux
OBJ             = hello.o

all:            hello.elf

clean:
		rm -f hello.elf *.o

hello.elf:      hello.o
		$(CC) $(LDFLAGS) $(CFLAGS) $< $(LIBS) -o $@
		$(OBJDUMP) -d -S $@ > hello.dis

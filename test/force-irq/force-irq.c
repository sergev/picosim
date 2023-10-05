#include <stdio.h>
#include <pico/stdlib.h>

static inline __attribute__((always_inline)) unsigned get_sp()
{
    unsigned result;
    asm volatile ("mov %0, sp" : "=r" (result) );
    return result;
}

void print_stack(unsigned sp, unsigned count)
{
    unsigned *stack = (unsigned*) sp;
    printf("SP    = %08x\n", sp);
    for (unsigned i = 0; i < count; i++) {
        printf("SP[%u] = %08x\n", i, stack[i]);
    }
}

void cb_interrupt()
{
    printf("Got interrupt.\n");
    print_stack(get_sp(), 12);

    for (;;) {
        asm volatile("svc #1");
    }
}

int main()
{
    stdio_init_all();

    printf("Setup interrupt handler.\n");
    irq_set_exclusive_handler(PIO0_IRQ_0, cb_interrupt);
    irq_set_enabled(PIO0_IRQ_0, true);
    print_stack(get_sp(), 2);

    printf("Force interrupt.\n");
    irq_set_pending(PIO0_IRQ_0);

    printf("Failed.\n");
    for (;;) {
        asm volatile("bkpt");
    }
}
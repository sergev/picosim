#include <stdio.h>
#include <pico/stdlib.h>

void cb_interrupt()
{
    printf("Got interrupt.\n");
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

    printf("Force interrupt.\n");
    irq_set_pending(PIO0_IRQ_0);

    printf("Failed.\n");
    for (;;) {
        asm volatile("bkpt");
    }
}

#include <stdio.h>
#include <pico/stdlib.h>

volatile bool irq_flag = false;

void wait_for_interrupt()
{
    for (unsigned count = 0; !irq_flag; count++) {
        if (count >= 1000) {
            printf("Failed.\n");
            for (;;) {
                asm volatile("bkpt");
            }
        }
    }
}

void handler_irq_26()
{
    printf("Got interrupt 26.\n");
    printf("Force interrupt 27.\n");
    irq_set_pending(27);
    wait_for_interrupt();
    printf("Exit interrupt 26.\n");
}

void handler_irq_27()
{
    printf("Got interrupt 27.\n");
    irq_flag = true;
    printf("Exit interrupt 27.\n");
}

int main()
{
    stdio_init_all();

    printf("Setup interrupt handlers.\n");
    irq_set_exclusive_handler(26, handler_irq_26);
    irq_set_exclusive_handler(27, handler_irq_27);
    irq_set_priority(26, 0x80);
    irq_set_priority(27, 0x40);
    irq_set_enabled(26, true);
    irq_set_enabled(27, true);

    printf("Force interrupt 26.\n");
    irq_set_pending(26);
    wait_for_interrupt();

    printf("Returned from interrupt.\n");
    for (;;) {
        asm volatile("svc #1");
    }
}

#include <stdio.h>
#include <pico/stdlib.h>

volatile bool alarm_flag[4] = { false };

void interrupt_alarm(unsigned alarm_num)
{
    alarm_flag[alarm_num] = true;
}

void wait_for_interrupt(unsigned alarm_num)
{
    for (unsigned count = 0; !alarm_flag[alarm_num]; count++) {
        if (count >= 1000) {
            printf("Failed.\n");
            for (;;) {
                asm volatile("bkpt");
            }
        }
        asm volatile("wfe");
    }
}

int main()
{
    stdio_init_all();

    // Setup all four alarms.
    hardware_alarm_set_callback(0, interrupt_alarm);
    hardware_alarm_set_callback(1, interrupt_alarm);
    hardware_alarm_set_callback(2, interrupt_alarm);
    hardware_alarm_set_callback(3, interrupt_alarm);

    // Activate alarms.
    uint64_t usec = time_us_64();
    absolute_time_t t;
    update_us_since_boot(&t, usec + 100);
    hardware_alarm_set_target(0, t);
    update_us_since_boot(&t, usec + 200);
    hardware_alarm_set_target(1, t);
    update_us_since_boot(&t, usec + 300);
    hardware_alarm_set_target(2, t);
    update_us_since_boot(&t, usec + 400);
    hardware_alarm_set_target(3, t);

    printf("Waiting for alarms, usec = %llu\n", time_us_64());
    wait_for_interrupt(0);
    printf("Got alarm #0, usec = %llu\n", time_us_64());
    wait_for_interrupt(1);
    printf("Got alarm #1, usec = %llu\n", time_us_64());
    wait_for_interrupt(2);
    printf("Got alarm #2, usec = %llu\n", time_us_64());
    wait_for_interrupt(3);
    printf("Got alarm #3, usec = %llu\n", time_us_64());

    printf("Done.\n");
    hardware_alarm_cancel(0);
    hardware_alarm_cancel(1);
    hardware_alarm_cancel(2);
    hardware_alarm_cancel(3);
    for (;;) {
        asm volatile("svc #1");
    }
}

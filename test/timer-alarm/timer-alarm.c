#include <stdio.h>
#include <pico/stdlib.h>

bool alarm_flag[4] = { false };

void cb_hardware_alarm(unsigned alarm_num)
{
    alarm_flag[alarm_num] = true;
}

int main()
{
    stdio_init_all();

    // Setup all four alarms.
    hardware_alarm_set_callback(0, cb_hardware_alarm);
    hardware_alarm_set_callback(1, cb_hardware_alarm);
    hardware_alarm_set_callback(2, cb_hardware_alarm);
    hardware_alarm_set_callback(3, cb_hardware_alarm);

    // Activate alarms.
    uint64_t usec = time_us_64();
    absolute_time_t t;
    update_us_since_boot(&t, usec + 1000);
    hardware_alarm_set_target(0, t);
    update_us_since_boot(&t, usec + 2000);
    hardware_alarm_set_target(1, t);
    update_us_since_boot(&t, usec + 3000);
    hardware_alarm_set_target(2, t);
    update_us_since_boot(&t, usec + 4000);
    hardware_alarm_set_target(3, t);

    printf("Waiting for alarms, usec = %llu\n", time_us_64());
    while (!alarm_flag[0]) {
        asm volatile("wfe");
    }
    printf("Got alarm #0, usec = %llu\n", time_us_64());
    while (!alarm_flag[1]) {
        asm volatile("wfe");
    }
    printf("Got alarm #1, usec = %llu\n", time_us_64());
    while (!alarm_flag[2]) {
        asm volatile("wfe");
    }
    printf("Got alarm #2, usec = %llu\n", time_us_64());
    while (!alarm_flag[3]) {
        asm volatile("wfe");
    }
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

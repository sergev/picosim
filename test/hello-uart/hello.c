#include <stdio.h>
#include <pico/stdlib.h>

int main()
{
    stdio_init_all();
    printf("Hello from UART!\n");
    for (;;) {
        asm volatile("svc #1");
    }
}

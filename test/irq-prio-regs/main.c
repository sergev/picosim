#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/divider.h>

void test_reg(const char *name, unsigned offset)
{
    io_rw_32 *ptr = (io_rw_32 *)(PPB_BASE + offset);

    *ptr = 0xffffffff;
    printf("%-5s = %08x\n", name, (unsigned) *ptr);
}

int main()
{
    stdio_init_all();

    test_reg("SHPR2", M0PLUS_SHPR2_OFFSET);
    test_reg("SHPR3", M0PLUS_SHPR3_OFFSET);
    test_reg("IPR0", M0PLUS_NVIC_IPR0_OFFSET);
    test_reg("IPR1", M0PLUS_NVIC_IPR1_OFFSET);
    test_reg("IPR2", M0PLUS_NVIC_IPR2_OFFSET);
    test_reg("IPR3", M0PLUS_NVIC_IPR3_OFFSET);
    test_reg("IPR4", M0PLUS_NVIC_IPR4_OFFSET);
    test_reg("IPR5", M0PLUS_NVIC_IPR5_OFFSET);
    test_reg("IPR6", M0PLUS_NVIC_IPR6_OFFSET);
    test_reg("IPR7", M0PLUS_NVIC_IPR7_OFFSET);
    for (;;) {
        asm volatile("svc #1");
    }
}

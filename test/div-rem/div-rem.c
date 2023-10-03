#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/divider.h>

void test_int_divmod(int32_t a, int32_t b)
{
    int32_t r = 12345678;
    int32_t q = divmod_s32s32_rem(a, b, &r);

    printf("    %ld / %ld -> %ld, rem %ld\n", a, b, q, r);
}

void test_uns_divmod(uint32_t a, uint32_t b)
{
    uint32_t r = 12345678;
    uint32_t q = divmod_u32u32_rem(a, b, &r);

    printf("    %lu / %lu -> %lu, rem %lu\n", a, b, q, r);
}

//
// Tested on Unix:
// Signed:
//     100 / 9 -> 11, rem 1
//     -100 / 9 -> -11, rem -1
//     100 / -9 -> -11, rem 1
//     -100 / -9 -> 11, rem -1
//     100 / 0 -> 0, rem 100
//     -100 / 0 -> 0, rem -100
//     0 / 0 -> 0, rem 0
//     -2147483648 / -1 -> -2147483648, rem 0
//     2147483647 / 3 -> 715827882, rem 1
// Unsigned:
//     100 / 9 -> 11, rem 1
//     100 / 0 -> 0, rem 100
//     0 / 0 -> 0, rem 0
//     4294967295 / 3 -> 1431655765, rem 0
//
int main()
{
    stdio_init_all();

    printf("Signed:\n");
    test_int_divmod(100, 9);         // divide positive by positive
    test_int_divmod(-100, 9);        // divide negative by positive
    test_int_divmod(100, -9);        // divide positive by negative
    test_int_divmod(-100, -9);       // divide negative by negative
    test_int_divmod(100, 0);         // divide positive by zero
    test_int_divmod(-100, 0);        // divide negative by zero
    test_int_divmod(0, 0);           // divide zero by zero
    test_int_divmod(0x80000000, -1); // divide INT_MIN by (overflow)
    test_int_divmod(0x7fffffff, 3);  // divide large by 3

    printf("Unsigned:\n");
    test_uns_divmod(100, 9);        // regular
    test_uns_divmod(100, 0);        // divide nonzero by zero
    test_uns_divmod(0, 0);          // divide zero by zero
    test_uns_divmod(0xffffffff, 3); // divide large by 3

    for (;;) {
        asm volatile("svc #1");
    }
}

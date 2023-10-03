#include "util.h"

//
// Check stdout.
//
TEST(sim, div_rem)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/div-rem/div_rem.elf");

    // Jump into _reset_handler, skip ROM.
    sim.run(0x100001f6);
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Signed:\r\n"
        "    100 / 9 -> 11, rem 1\r\n"
        "    -100 / 9 -> -11, rem -1\r\n"
        "    100 / -9 -> -11, rem 1\r\n"
        "    -100 / -9 -> 11, rem -1\r\n"
        "    100 / 0 -> -1, rem 100\r\n"
        "    -100 / 0 -> 1, rem -100\r\n"
        "    0 / 0 -> -1, rem 0\r\n"
        "    -2147483648 / -1 -> -2147483648, rem 0\r\n"
        "    2147483647 / 3 -> 715827882, rem 1\r\n"
        "Unsigned:\r\n"
        "    100 / 9 -> 11, rem 1\r\n"
        "    100 / 0 -> 4294967295, rem 100\r\n"
        "    0 / 0 -> 4294967295, rem 0\r\n"
        "    4294967295 / 3 -> 1431655765, rem 0\r\n");
}

#include "sc_main.cpp"

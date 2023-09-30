#include "util.h"

//
// Check stdout.
//
TEST(sim, uart)
{
    Simulator sim("pico");
    enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/hello-uart/hello_uart.elf");
    sim.run();
    show_trace();

    EXPECT_EQ(sim.get_stdout(), "Hello!\n");
}

#include "sc_main.cpp"

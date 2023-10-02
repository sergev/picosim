#include "util.h"

//
// Check stdout.
//
TEST(sim, uart)
{
    Simulator sim("pico");
    sim.read_elf_file(TEST_DIR "/hello-uart/hello_uart.elf");
    sim.capture_stdout();
    //enable_trace();
#if 1
    // TODO: remove this when Flash i/o is ready
    sim.run(0x1000020c); // jump into Flash, skip .data copying
#else
    sim.run();
#endif
    //show_trace();

    EXPECT_EQ(sim.get_stdout(), "Hello from UART!\r\n");
}

#include "sc_main.cpp"

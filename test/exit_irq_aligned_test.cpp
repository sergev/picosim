#include "util.h"

//
// Check stdout.
//
TEST(sim, exit_irq_aligned)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/exit-irq-aligned/exit_irq_aligned.elf");
    sim.run();
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Setup interrupt handler.\r\n"
        "SP    = 20041ff8\r\n"
        "SP[0] = 10000264\r\n"
        "SP[1] = 10000223\r\n"
        "Force interrupt.\r\n"
        "Got interrupt.\r\n"
        "SP    = 20041fc8\r\n"
        "SP[0] = 10000264\r\n"
        "SP[1] = 20041f01\r\n"
        "Returned from interrupt.\r\n"
        "SP    = 20041ff8\r\n"
        "SP[0] = 10000264\r\n"
        "SP[1] = 10000223\r\n");
}

#include "sc_main.cpp"

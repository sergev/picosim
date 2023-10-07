#include "util.h"

//
// Check stdout.
//
TEST(sim, exit_irq_unaligned)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/exit-irq-unaligned/exit_irq_unaligned.elf");
    sim.run();
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Setup interrupt handler.\r\n"
        "SP    = 20041ff4\r\n"
        "SP[0] = 100003d1\r\n"
        "SP[1] = 10000264\r\n"
        "Force interrupt.\r\n"
        "Got interrupt.\r\n"
        "SP    = 20041fc0\r\n"
        "SP[0] = 10000264\r\n"
        "SP[1] = 20041f01\r\n"
        "Returned from interrupt.\r\n"
        "SP    = 20041ff4\r\n"
        "SP[0] = 100003d1\r\n"
        "SP[1] = 10000264\r\n");
}

#include "sc_main.cpp"

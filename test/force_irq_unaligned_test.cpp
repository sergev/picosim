#include "util.h"

//
// Check stdout.
//
TEST(sim, force_irq_unaligned)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/force-irq-unaligned/force_irq_unaligned.elf");
    sim.run();
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Setup interrupt handler.\r\n"
        "SP    = 20041ff4\r\n"
        "SP[0] = 10000375\r\n"
        "SP[1] = 10000264\r\n"
        "Force interrupt.\r\n"
        "Got interrupt.\r\n"
        "SP    = 20041fc8\r\n"
        "SP[0] = 10000264\r\n"
        "SP[1] = fffffff9\r\n"
        "SP[2] = 00000007\r\n"
        "SP[3] = 00000000\r\n"
        "SP[4] = e000e200\r\n"
        "SP[5] = 00000080\r\n"
        "SP[6] = 20000149\r\n"
        "SP[7] = 1000038b\r\n"
        "SP[8] = 1000038a\r\n"
        "SP[9] = 01000200\r\n"
        "SP[10] = 10000385\r\n"
        "SP[11] = 10000375\r\n"
        "SP[12] = 10000264\r\n");
}

#include "sc_main.cpp"

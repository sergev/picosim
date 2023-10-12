#include "util.h"

//
// Check stdout.
//
TEST(sim, irq_same_prio)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/irq-same-prio/irq_same_prio.elf");

    // Jump into _reset_handler, skip ROM.
    sim.run(0x100001f6);
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Setup interrupt handlers.\r\n"
        "Force interrupt 26.\r\n"
        "Got interrupt 26.\r\n"
        "Force interrupt 27.\r\n"
        "Exit interrupt 26.\r\n"
        "Got interrupt 27.\r\n"
        "Exit interrupt 27.\r\n"
        "Returned from interrupt.\r\n");
}

#include "sc_main.cpp"

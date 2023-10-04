#include "util.h"

//
// Check stdout.
//
TEST(sim, force_irq)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/force-irq/force_irq.elf");

    // Jump into _reset_handler, skip ROM.
    sim.run(0x100001f6);
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Setup interrupt handler.\r\n"
        "Force interrupt.\r\n"
        "Got interrupt.\r\n");
}

#include "sc_main.cpp"

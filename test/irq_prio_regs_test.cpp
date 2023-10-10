#include "util.h"

//
// Check stdout.
//
TEST(sim, irq_prio_regs)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/irq-prio-regs/irq_prio_regs.elf");

    // Jump into _reset_handler, skip ROM.
    sim.run(0x100001f6);
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "SHPR2 = c0000000\r\n"
        "SHPR3 = c0c00000\r\n"
        "IPR0  = c0c0c0c0\r\n"
        "IPR1  = c0c0c0c0\r\n"
        "IPR2  = c0c0c0c0\r\n"
        "IPR3  = c0c0c0c0\r\n"
        "IPR4  = c0c0c0c0\r\n"
        "IPR5  = c0c0c0c0\r\n"
        "IPR6  = c0c0c0c0\r\n"
        "IPR7  = c0c0c0c0\r\n");
}

#include "sc_main.cpp"

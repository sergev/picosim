#include "util.h"

//
// Check stdout.
//
TEST(sim, timer_alarm)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/timer-alarm/timer_alarm.elf");
    sim.run();
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Waiting for alarms, usec = 0\r\n"
        "Got alarm #0, usec = 119\r\n"
        "Got alarm #1, usec = 202\r\n"
        "Got alarm #2, usec = 1797\r\n"
        "Got alarm #3, usec = 4141\r\n"
        "Done.\r\n");
}

#include "sc_main.cpp"

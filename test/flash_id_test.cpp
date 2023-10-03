#include "util.h"

//
// Check stdout.
//
TEST(sim, flash_id)
{
    Simulator sim("pico");
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/read-flash-id/read_flash_id.elf");

    // Jump into _reset_handler, skip .data copying.
    sim.run(0x1000020c);
    //show_trace();

    EXPECT_EQ(sim.get_stdout(),
        "Flash info:\r\n"
        "Manufacturer = 0xef\r\n"
        "Device = 0x4018\r\n"
        "Serial Number = 0x123456789abcdef0\r\n");
}

#include "sc_main.cpp"

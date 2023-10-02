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

    EXPECT_EQ(sim.get_stdout(), R"(Flash info:
Manufacturer = 0xef
Device = 0x4018
Serial Number = 0x123456789abcdef0
)");
}

#include "sc_main.cpp"

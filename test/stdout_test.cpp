#include "util.h"

//
// Check stdout.
//
TEST(syscall, write_stdout)
{
    Simulator sim;
    enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/test_files/stdout.elf");
    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 6);
    EXPECT_EQ(sim.get_pc(), 0x800c);
    EXPECT_EQ(sim.get_stdout(), "Hello!\n");
}

#include "sc_main.cpp"

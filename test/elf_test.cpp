#include "util.h"

//
// Check ELF load.
//
TEST(sim, read_elf)
{
    Simulator sim;
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/test_files/hello.elf");
    sim.run();
    //show_trace();

    EXPECT_EQ(sim.get_stdout(), "Hello, World!\n");
}

#include "sc_main.cpp"

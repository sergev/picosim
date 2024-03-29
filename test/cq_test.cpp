#include "util.h"

//
// Large test of C compiler.
//
TEST(sim, cq)
{
    Simulator sim;
    //enable_trace();
    sim.capture_stdout();
    sim.read_elf_file(TEST_DIR "/test_files/cq.elf");
    sim.run();
    //show_trace();

    static const std::string expect = R"(Section s22     returned 0.
Section s241    returned 0.
Section s243    returned 0.
Section s244    returned 0.
Section s25     returned 0.
  8 bits in chars.
 32 bits in ints.
 16 bits in shorts.
 32 bits in longs.
 32 bits in unsigneds.
 32 bits in floats.
 64 bits in doubles.
1.192093e-07 is the least number that can be added to 1. (float).
2.220446e-16 is the least number that can be added to 1. (double).
Section s26     returned 0.
Section s4      returned 0.
Section s61     returned 0.
Section s626    returned 0.
Section s71     returned 0.
Section s72     returned 0.
Section s757    returned 0.
Section s7813   returned 0.
Section s714    returned 0.
Section s715    returned 0.
Register count for char is unreliable.
Register count for pointer is unreliable.
Register count for int is unreliable.
Section s81     returned 0.
Section s84     returned 0.
char alignment: 1
short alignment: 2
int alignment: 4
long alignment: 4
unsigned alignment: 4
float alignment: 4
double alignment: 8
Section s85     returned 0.
Section s86     returned 0.
Section s88     returned 0.
Section s9      returned 0.

No errors detected.
)";
    EXPECT_EQ(sim.get_stdout(), expect);
}

#include "sc_main.cpp"

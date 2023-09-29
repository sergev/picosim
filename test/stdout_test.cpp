#include "util.h"

//
// Check ADC instruction.
//
TEST(opcode, adc)
{
    Simulator sim;
    enable_trace();
    sim.capture_stdout();

    sim.debug_store16(0x8000, 0x2001);      // movs r0, #1
    sim.debug_store16(0x8002, 0xa103);      // add r1, pc, #12
    sim.debug_store16(0x8004, 0x2207);      // movs r2, #7
    sim.debug_store16(0x8006, 0x2704);      // movs r7, #4
    sim.debug_store16(0x8008, 0xdf00);      // svc 0
    sim.debug_store16(0x800a, 0x2000);      // movs r0, #0
    sim.debug_store16(0x800c, 0x2701);      // movs r7, #1
    sim.debug_store16(0x800e, 0xdf00);      // svc 0
    sim.debug_store32(0x8010, 0x6c6c6548);
    sim.debug_store32(0x8014, 0x000a216f);

    sim.run(0x8000);
    show_trace();

    EXPECT_EQ(sim.get_instructions_executed(), 8);
    EXPECT_EQ(sim.get_pc(), 0x8010);
    EXPECT_EQ(sim.get_reg(7), 1);
    EXPECT_EQ(sim.get_stdout(), "Hello!\n");
}

#include "sc_main.cpp"

#include <gtest/gtest.h>
#include <systemc.h>

//
// Make sure the SystemC library links correctly.
//
TEST(tlm, smoke_test)
{
    // Nothing to run: should finish in zero time.
    sc_core::sc_start();
    EXPECT_EQ(sc_core::sc_time_stamp(), sc_core::SC_ZERO_TIME);
}

#include "sc_main.cpp"

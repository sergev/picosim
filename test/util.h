#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <gtest/gtest.h>
#include <systemc.h>
#include "simulator.h"

//
// Get current test name, as specified in TEST() macro.
//
std::string get_test_name();

//
// Enable trace to a file named as the current test, with ".trace" extension.
//
void enable_trace();

//
// Show contents of the trace file.
//
void show_trace();

#endif // TEST_UTIL_H

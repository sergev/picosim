#include "util.h"

//
// Get current test name, as specified in TEST() macro.
//
std::string get_test_name()
{
    std::string name = ::testing::UnitTest::GetInstance()->current_test_info()->name();

    // Remove the '/1' suffix.
    auto pos = name.find_last_of('/');
    if (pos != std::string::npos)
        name.erase(pos);

    return name;
}

void enable_trace()
{
    // Enable trace to a file named as the current test, with ".trace" extension.
    auto trace_file = get_test_name() + ".trace";
    Log::set_verbose(trace_file);
}

void show_trace()
{
    // Disable trace.
    Log::set_verbose("");

    // Show contents of the trace file.
    auto trace_file = get_test_name() + ".trace";
    std::ifstream input(trace_file);
    std::cout << input.rdbuf();
}

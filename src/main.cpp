/*!
 \file Simulator.cpp
 \brief Top level simulation entity
 \author Màrius Montón
 \date September 2018
 */
#include <unistd.h>

#include <chrono>
#include <csignal>

#include "simulator.h"

static const std::string version = "0.1"; // TODO
static std::string filename;
static bool debug_session = false;
static const char *prog_name;

void intHandler(int dummy)
{
    (void)dummy;
    exit(-1);
}

//
// Print usage message and exit with given status.
//
void usage(int exit_status)
{
    std::cout << "RP2040 Simulator, Version " << version << std::endl;
    std::cerr << "Usage:" << std::endl;
    std::cerr << "    " << prog_name << " [-L FILE] [-D] filename.elf" << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "    -L FILE   Enable log output to file" << std::endl;
    std::cerr << "    -D        Debug session" << std::endl;
    std::cerr << "    -h        Show usage" << std::endl;
    std::cerr << "    -V        Show version and finish" << std::endl;
    exit(exit_status);
}

void process_arguments(int argc, char *argv[])
{
    // Get program name for later use.
    prog_name = argv[0];

    // Parse command line options.
    for (;;) {
        switch (getopt(argc, argv, "hVDL:f:")) {
        case EOF:
            break;
        case 0:
            continue;
        case 'h':
            // Show usage message and exit.
            usage(EXIT_SUCCESS);
            break;
        case 'V':
            // Show version and exit.
            std::cout << "RP2040 Simulator Version " << version << std::endl;
            exit(EXIT_SUCCESS);
            break;
        case 'D':
            debug_session = true;
            continue;
        case 'L':
            Log::set_verbose(optarg);
            Log::out() << "RP2040 Simulator, Version " << version << std::endl;
            continue;
        default:
            usage(EXIT_FAILURE);
            break;
        }
        break;
    }
    argc -= optind;
    argv += optind;

    // Must specify a HEX file to run.
    if (argc != 1) {
        usage(EXIT_SUCCESS);
    }
    filename = std::string(argv[0]);
    std::cout << "file: " << filename << std::endl;
}

//
// Print statistics.
//
static void print_stats(std::ostream &out, double sec, uint64_t ncycles, uint64_t instr_count)
{
    auto instr_per_sec = int(std::round(instr_count / sec));
    double print_sec;
    if (sec < 0.01)
        print_sec = std::round(sec * 1000000) / 1000000;
    else if (sec < 1.0)
        print_sec = std::round(sec * 1000) / 1000;
    else if (sec < 20.0)
        print_sec = std::round(sec * 10) / 10;
    else
        print_sec = std::round(sec);

    out << "   Elapsed time: " << print_sec << " seconds" << std::endl;
    out << "   System clock: " << ncycles << " ticks" << std::endl;
    out << "      Simulated: " << instr_count << " instructions" << std::endl;
    if (sec > 0) {
        auto khz = int(std::round(ncycles / sec / 1000));
        out << "Simulation rate: " << khz << " kHz, " << instr_per_sec << " instructions/sec"
            << std::endl;
    }
}

int sc_main(int argc, char *argv[])
{
    /* Capture Ctrl+C and finish simulation */
    signal(SIGINT, intHandler);

    /* Parse and process program arguments. */
    process_arguments(argc, argv);

    /* SystemC time resolution set to 1 ns */
    sc_core::sc_set_time_resolution(1, sc_core::SC_NS);

    /* Instantiate simulator. */
    Simulator sim("pico", debug_session);
    if (!filename.empty()) {
        sim.read_elf_file(filename);
    }

    auto start = std::chrono::steady_clock::now();
    std::cout << "----- Start -----" << std::endl;
    sim.run();
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    uint64_t ncycles                              = sc_core::sc_time_stamp().value();
    uint64_t instr_count                          = sim.get_instructions_executed();

    std::cout << "----- Stop -----" << std::endl;
    print_stats(std::cout, elapsed_seconds.count(), ncycles, instr_count);
    if (Log::is_verbose()) {
        auto &out = Log::err();
        out << "Done" << std::endl;
        print_stats(out, elapsed_seconds.count(), ncycles, instr_count);
    }
    return 0;
}

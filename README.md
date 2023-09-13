# Simulator of RP2020 microcontroller

Picosim is a system level simulator of RP2040 based boards.
The simulator is based on SystemC framework.

# Usage

    $ picosim
    RP2040 Simulator, Version 0.1
    Usage:
        picosim [-L FILE] [-D] filename.elf
    Options:
        -L FILE   Enable log output to the specified file
        -D        Debug session
        -h        Show the usage
        -V        Show the version and finish

# Build

Build the SystemC library from sources for C++17 compiler:

    wget https://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz
    tar xzf systemc-2.3.3.tar.gz
    cd systemc-2.3.3
    mkdir build
    cd build
    cmake .. -DCMAKE_CXX_STANDARD=17 -DDISABLE_COPYRIGHT_MESSAGE=ON -DCMAKE_INSTALL_PREFIX=/usr/local
    make
    make install

The SystemC library is sensitive to the C++ standard.
It must be compiled with option -std=c++17, to match the simulator.
We cannot rely on a traditional install like 'apt install libsystemc-dev' or 'brew install systemc'.
It would not link with the simulator.

Configure and build the simulator

    $ cd picosim
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make install

# Testing

Run all tests:

    $ cd build
    $ make test
    Running tests...
          Start  1: tlm.smoke_test
     1/91 Test  #1: tlm.smoke_test ...................   Passed    0.00 sec
    ...
          Start 89: c_extension.cswsp_test
    89/91 Test #89: c_extension.cswsp_test ...........   Passed    0.00 sec
          Start 90: c_extension.cxor_test
    90/91 Test #90: c_extension.cxor_test ............   Passed    0.01 sec
          Start 91: disasm.disasm_test
    91/91 Test #91: disasm.disasm_test ...............   Passed    0.00 sec

    100% tests passed, 0 tests failed out of 91

    Total Test time (real) =   0.40 sec

Test run can be made faster by setting the variable `CTEST_PARALLEL_LEVEL` to the number of available processors
on your workstation. For example:

    $ export CTEST_PARALLEL_LEVEL=16

You can also start the tests with `ctest` utility. See `ctest --help` for options.
To run one specific test or a subset of tests, invoke `ctest` with `-R` option and a test name or a matching substring.
Add -V to show the full output.

# Links

TODO

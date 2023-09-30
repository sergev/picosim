/*!
 \file processor.h
 \brief Main CPU class
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "bus_controller.h"
#include "debug.h"
#include "peripherals.h"
#include "phys_memory.h"
#include "processor.h"
#include "systemc"
#include "timer.h"

/**
 * @class Simulator
 * This class instantiates all necessary modules, connects its ports and starts
 * the simulation.
 *
 * @brief Top simulation entity
 */
class Simulator : public sc_core::sc_module {
private:
    Processor cpu;
    Bus_Controller bus;

    // Optional components.
    std::unique_ptr<Memory> rom;
    std::unique_ptr<Memory> flash;
    std::unique_ptr<Memory> sram;
    std::unique_ptr<Peripherals> periph;
    std::unique_ptr<Timer> timer;
    std::unique_ptr<Debug> debug;

    // Entry address (PC) read from ELF file.
    uint32_t entry_address{ 0 };

public:
    Simulator(const sc_core::sc_module_name &config = "linux", bool debug_enable = false);

    // Run program.
    void run(uint32_t start_address = 0);

    // Debug access to the memory, 1 to 4 bytes.
    uint8_t debug_load8(uint32_t addr) { return debug_load(addr, 1); }
    uint16_t debug_load16(uint32_t addr) { return debug_load(addr, 2); }
    uint32_t debug_load32(uint32_t addr) { return debug_load(addr, 4); }
    uint32_t debug_load(uint32_t addr, unsigned nbytes);
    void debug_store8(uint32_t addr, uint8_t val) { debug_store(addr, val, 1); }
    void debug_store16(uint32_t addr, uint16_t val) { debug_store(addr, val, 2); }
    void debug_store32(uint32_t addr, uint32_t val) { debug_store(addr, val, 4); }
    void debug_store(uint32_t addr, uint32_t val, unsigned nbytes);

    // Debug access to the memory, arbitrary size.
    unsigned debug_read(uint8_t *buf, uint32_t addr, unsigned nbytes);
    unsigned debug_write(const uint8_t *buf, uint32_t addr, unsigned nbytes);

    // Figure out SoC configuration from ELF file.
    static std::string get_elf_config(const std::string &filename);

    // Read ELF binary file.
    void read_elf_file(const std::string &filename);

    // Return Program Counter read from executable image.
    uint32_t get_start_address() const { return entry_address; }

    // Get statistics counters.
    uint64_t get_instructions_executed() { return cpu.get_instructions_executed(); }

    // Get CPU register value.
    int32_t get_reg(int reg_num) { return cpu.get_reg(reg_num); }

    // Get PC value of core #0.
    uint32_t get_pc() { return cpu.get_pc(); }

    // Enable stdout buffering.
    void capture_stdout() { cpu.capture_stdout(); }

    // Get captured output.
    std::string get_stdout() { return cpu.get_stdout(); }
};

// Run test and compare to the reference.
// This routine is available only for tests.
void test_with_reference(std::string elf_name, std::string ref_name);

#endif // SIMULATOR_H

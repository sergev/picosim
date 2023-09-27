/*!
 \file processor.h
 \brief Main CPU class
 \author Màrius Montón
 \date August 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "systemc"
#include "phys_memory.h"
#include "processor.h"
#include "bus_controller.h"
#include "timer.h"
#include "debug.h"
#include "peripherals.h"

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
    Memory rom0;
    Memory rom1;
    Memory sram1;
    Memory flash;
    Memory rtc;
    Peripherals periph;
    Timer timer;
    Debug debug;

    // Entry address (PC) read from ELF file.
    uint32_t entry_address{ 0 };

    // Address of signature area.
    uint32_t begin_signature{ 0 };
    uint32_t end_signature{ 0 };

public:
    Simulator(sc_core::sc_module_name name, bool debug_enable = false);

    // Make Flash memory read only.
    void lock_flash_memory() { flash.set_read_only(); }

    // Get statistics counters.
    uint64_t get_instructions_executed() { return cpu.get_instructions_executed(); }

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

    // Compare the signature contents to the reference.
    // This method is available only for tests.
    void check_signature(const std::string &filename);

    // Read ELF binary file
    void read_elf_file(const std::string &filename);

    // Return Program Counter read from executable image.
    uint32_t get_start_address() const { return entry_address; }

    // Address of signature area.
    uint32_t get_begin_signature() { return begin_signature; }
    uint32_t get_end_signature() { return end_signature; };
};

// Run test and compare to the reference.
// This routine is available only for tests.
void test_with_reference(std::string elf_name, std::string ref_name);

#endif // SIMULATOR_H
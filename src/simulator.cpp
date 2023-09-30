#include "simulator.h"

//
// Address Map from RP2040 Datasheet, page 24.
//
#define RP2040_ROM_BASE 0x00000000 // ROM_BASE
#define RP2040_ROM_LAST 0x00003fff // 16 kbytes

#define RP2040_FLASH_BASE 0x10000000 // XIP_BASE
#define RP2040_FLASH_LAST 0x101fffff // 2 Mbytes

#define RP2040_SRAM_BASE 0x20000000 // SRAM_BASE
#define RP2040_SRAM_LAST 0x20041fff // 256 + 8 kbytes

#define RP2040_PERIPH_BASE 0x40000000 // SYSINFO_BASE
#define RP2040_PERIPH_LAST 0x4007ffff // 512 kbytes

//
// Address Map of binaries compiled for Linux with Newlib.
//
#define LINUX_SRAM_BASE 0x00008000 // skip 32 kbytes - newlib binary
#define LINUX_SRAM_LAST  0x0007ffff // 480 kbytes

//
// Initialize the chip.
//
Simulator::Simulator(const sc_core::sc_module_name &name, bool debug_enable)
    : sc_module(name), cpu("Processor", debug_enable), bus("BusCtrl"),
      config((const char*)name)
{
    // Connect CPU to the bus controller.
    cpu.instr_bus.bind(bus.cpu_instr_socket);
    cpu.data_bus.bind(bus.cpu_data_socket);

    if (debug_enable) {
        // Setup port for GDB.
        debug = std::make_unique<Debug>(*this, cpu);
    }

    //
    // Allocate optional components, per configuration.
    // Connect all slaves to the bus controller.
    //
    if (config == "linux") {
        //
        // Linux binary.
        //
        // Internal SRAM for Linux mode - 480 kbytes
        sram = std::make_unique<Memory>("SRAM", LINUX_SRAM_BASE, LINUX_SRAM_LAST);
        bus.sram_bind(sram->socket, LINUX_SRAM_BASE, LINUX_SRAM_LAST);

        cpu.set_linux_mode(true);

    } else if (config == "pico") {
        //
        // RP2040 microcontroller.
        //
        // Internal SRAM - 256+8 kbytes
        sram = std::make_unique<Memory>("SRAM", RP2040_SRAM_BASE, RP2040_SRAM_LAST);
        bus.sram_bind(sram->socket, RP2040_SRAM_BASE, RP2040_SRAM_LAST);

        // Internal ROM - 16 kbytes
        rom = std::make_unique<Memory>("ROM", RP2040_ROM_BASE, RP2040_ROM_LAST);
        bus.rom_bind(rom->socket, RP2040_ROM_BASE, RP2040_ROM_LAST);

        // Flash memory - 2048 kbytes
        flash = std::make_unique<Memory>("Flash", RP2040_FLASH_BASE, RP2040_FLASH_LAST);
        bus.flash_bind(flash->socket, RP2040_FLASH_BASE, RP2040_FLASH_LAST);

        // Peripherals - 512 kbytes
        periph = std::make_unique<Peripherals>("Peripherals", RP2040_PERIPH_BASE, RP2040_PERIPH_LAST);
        bus.periph_bind(periph->socket, RP2040_PERIPH_BASE, RP2040_PERIPH_LAST);

        // TODO: move timer to peripherals
        timer = std::make_unique<Timer>("Timer");
        bus.timer_bind(timer->socket);
        cpu.irq_bind(timer->irq_line);

        // Load ROM.
        // Keep Flash memory writable, until binary is loaded.
        extern const unsigned char pico_bootrom_b2_bin[];
        extern const unsigned int pico_bootrom_b2_bin_len;
        debug_write(pico_bootrom_b2_bin, RP2040_ROM_BASE, pico_bootrom_b2_bin_len);
        rom->set_read_only();

        // Start from ROM.
        entry_address = 0;
    }
}

//
// Run program.
//
void Simulator::run(uint32_t start_address)
{
    // Make Flash memory read only.
    if (flash) {
        flash->set_read_only();
    }

    if (start_address) {
        cpu.set_pc(start_address);
    } else if (config == "linux") {
        // Address from ELF file.
        cpu.set_pc(entry_address);
    } else {
        // Read MSP and PC values from ROM.
        // Must use debug i/o here, as we've not started yet.
        cpu.set_reg(Registers::SP, debug_load32(0));
        cpu.set_pc(debug_load32(4) & ~1);
    }
    sc_core::sc_start();
}

//
// Read 1/2/4 bytes from memory, via a backdoor.
//
uint32_t Simulator::debug_load(uint32_t addr, unsigned nbytes)
{
    tlm::tlm_generic_payload trans{};
    uint32_t val{};

    assert(nbytes <= sizeof(val));
    trans.set_data_ptr((uint8_t *)&val);
    trans.set_command(tlm::TLM_READ_COMMAND);
    trans.set_address(addr);
    trans.set_data_length(nbytes);
    cpu.data_bus->transport_dbg(trans);
    return val;
}

//
// Store 1/2/4 bytes to memory, via a backdoor.
//
void Simulator::debug_store(uint32_t addr, uint32_t val, unsigned nbytes)
{
    tlm::tlm_generic_payload trans{};

    assert(nbytes <= sizeof(val));
    trans.set_data_ptr((uint8_t *)&val);
    trans.set_command(tlm::TLM_WRITE_COMMAND);
    trans.set_address(addr);
    trans.set_data_length(nbytes);
    cpu.data_bus->transport_dbg(trans);
}

//
// Read memory, via a backdoor.
//
unsigned Simulator::debug_read(uint8_t *buf, uint32_t addr, unsigned nbytes)
{
    tlm::tlm_generic_payload trans{};

    assert(nbytes > 0);
    trans.set_data_ptr(buf);
    trans.set_command(tlm::TLM_READ_COMMAND);
    trans.set_address(addr);
    trans.set_data_length(nbytes);
    return cpu.data_bus->transport_dbg(trans);
}

//
// Write memory, via a backdoor.
//
unsigned Simulator::debug_write(const uint8_t *buf, uint32_t addr, unsigned nbytes)
{
    tlm::tlm_generic_payload trans{};

    assert(nbytes > 0);
    trans.set_data_ptr((uint8_t *)buf);
    trans.set_command(tlm::TLM_WRITE_COMMAND);
    trans.set_address(addr);
    trans.set_data_length(nbytes);
    return cpu.data_bus->transport_dbg(trans);
}

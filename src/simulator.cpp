#include "simulator.h"

//
// Initialize the chip.
//
Simulator::Simulator(const sc_core::sc_module_name &name, bool debug_enable)
    : sc_module(name), config((const char*)name), cpu("Processor", debug_enable, config),
      bus("BusCtrl", config)
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
        bus.sram_bind(sram->socket);

    } else if (config == "pico") {
        //
        // RP2040 microcontroller.
        //
        // Internal SRAM - 256+8 kbytes
        sram = std::make_unique<Memory>("SRAM", RP2040_SRAM_BASE, RP2040_SRAM_LAST);
        bus.sram_bind(sram->socket);

        // Internal ROM - 16 kbytes
        rom = std::make_unique<Memory>("ROM", RP2040_ROM_BASE, RP2040_ROM_LAST);
        bus.rom_bind(rom->socket);

        // Flash memory - 2048 kbytes
        flash = std::make_unique<Memory>("Flash", RP2040_FLASH_BASE, RP2040_FLASH_LAST);
        bus.flash_bind(flash->socket);

        // Peripherals
        periph = std::make_unique<Peripherals>(*this, "Periph");
        bus.periph_bind(periph->socket);

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
        // Address from user.
        cpu.set_pc(start_address);
    } else if (config == "linux") {
        // Address from ELF file.
        cpu.set_pc(entry_address);
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

#include "simulator.h"

Simulator::Simulator(const sc_core::sc_module_name &name, bool debug_enable)
    : sc_module(name), cpu("Processor", debug_enable), bus("BusCtrl")
{
    // Allocate optional components.
    rom    = std::make_unique<Memory>("ROM", 16);               // Internal ROM - 16 kbytes
    flash  = std::make_unique<Memory>("Flash", 2048);           // Flash memory - 2048 kbytes
//  sram   = std::make_unique<Memory>("SRAM", 256 + 8);         // Internal SRAM - 256+8 kbytes
    sram   = std::make_unique<Memory>("SRAM", 480);             // Internal SRAM for Linux mode - 480 kbytes
    periph = std::make_unique<Peripherals>("Peripherals", 512); // Peripherals - 512 kbytes
    timer  = std::make_unique<Timer>("Timer");                  // TODO: move to peripherals
    if (debug_enable) {
        debug = std::make_unique<Debug>(*this, cpu);
    }

    // Connect CPU to the bus controller.
    cpu.instr_bus.bind(bus.cpu_instr_socket);
    cpu.data_bus.bind(bus.cpu_data_socket);

    // Connect all slaves to the bus controller.
    bus.rom_socket.bind(rom->socket);
    bus.flash_socket.bind(flash->socket);
    bus.sram_socket.bind(sram->socket);
    bus.periph_socket.bind(periph->socket);

    // TODO: move timer to peripherals.
    bus.timer_socket.bind(timer->socket);
    timer->irq_line.bind(cpu.irq_line_socket);

    // Set base addresses.
    rom->set_base(ADDR_ROM_START);
    flash->set_base(ADDR_FLASH_START);
    sram->set_base(ADDR_SRAM_START);
    periph->set_base(ADDR_PERIPH_START);

    // Load ROM.
#if 0
    extern const unsigned char rom_bin[];
    extern const unsigned int rom_bin_len;
    debug_write(rom_bin, ADDR_ROM_START, rom_bin_len);
#endif

    // Make ROM read only.
    // Keep Flash memory still writable, until a binary image is loaded.
    rom->set_read_only();
}

//
// Run program.
//
void Simulator::run(uint32_t start_address)
{
    // Make Flash memory read only.
    flash->set_read_only();

    if (start_address) {
        cpu.set_pc(start_address);
        cpu.set_linux_mode(true);
    } else if (entry_address) {
        // Address from ELF file.
        cpu.set_pc(entry_address);
        if (entry_address < ADDR_FLASH_START) {
            cpu.set_linux_mode(true);
        }
    } else {
        // Read main_SP and PC values from ROM.
        cpu.set_reg(13, debug_load32(0));
        cpu.set_pc(debug_load32(4));
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

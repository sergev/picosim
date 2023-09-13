#include "simulator.h"

Simulator::Simulator(sc_core::sc_module_name name, bool debug_enable)
  : sc_module(name),
    cpu("Processor", debug_enable),
    bus("BusCtrl"),
    rom0("ROM0", 256),          // Internal ROM 0 - 256 kbytes
    rom1("ROM1", 128),          // Internal ROM 1 - 128 kbytes
    sram1("SRAM1", 384),        // Internal SRAM 1 - 384 kbytes
    flash("Flash", 8192),       // Flash memory - 8192 kbytes
    rtc("RTCMem", 8),           // RTC FAST memory - 8 kbytes
    periph("Peripherals", 836), // Peripherals - 836 kbytes
    timer("Timer"),             // TODO: move to peripherals
    debug(*this, cpu, debug_enable)
{
    // Connect CPU to the bus controller.
    cpu.instr_bus.bind(bus.cpu_instr_socket);
    cpu.data_bus.bind(bus.cpu_data_socket);

    // Connect all slaves to the bus controller.
    bus.rom0_socket.bind(rom0.socket);
    bus.rom1_socket.bind(rom1.socket);
    bus.sram1_socket.bind(sram1.socket);
    bus.flash_socket.bind(flash.socket);
    bus.rtc_mem_socket.bind(rtc.socket);
    bus.periph_socket.bind(periph.socket);

    // TODO: move the timer to peripherals.
    bus.timer_socket.bind(timer.socket);
    timer.irq_line.bind(cpu.irq_line_socket);

    // Load ROM.
#if 0
    extern const unsigned char esp32_c3_rev3_irom0_bin[], esp32_c3_rev3_drom1_bin[];
    extern const unsigned int esp32_c3_rev3_irom0_bin_len, esp32_c3_rev3_drom1_bin_len;
    debug_write(esp32_c3_rev3_irom0_bin, ADDR_FETCH_ROM0_START, esp32_c3_rev3_irom0_bin_len);
    debug_write(esp32_c3_rev3_drom1_bin, ADDR_DATA_ROM1_START, esp32_c3_rev3_drom1_bin_len);
#endif

    // Make ROMs read only.
    // Keep Flash memory still writable, until a binary image is loaded.
    rom0.set_read_only();
    rom1.set_read_only();
}

//
// Read 1/2/4 bytes from memory, via a backdoor.
//
uint32_t Simulator::debug_load(uint32_t addr, unsigned nbytes)
{
    tlm::tlm_generic_payload trans{};
    uint32_t val{};

    assert(nbytes <= sizeof(val));
    trans.set_data_ptr((uint8_t*) &val);
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
    trans.set_data_ptr((uint8_t*) &val);
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

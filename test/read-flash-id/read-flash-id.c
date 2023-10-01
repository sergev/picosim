#include <stdio.h>
#include <pico/stdlib.h>
#include "hardware/sync.h"
#include "hardware/flash.h"

//
// Read Flash manufacturer ID and device ID.
//
static void flash_read_mf_dev_id(uint8_t *mf_id, uint16_t *dev_id)
{
    // JEDEC ID instruction: 9Fh command prefix, 24 data bits.
    uint8_t txbuf[1 + 3] = { 0x9f };
    uint8_t rxbuf[1 + 3] = {};
    uint32_t irqsave = save_and_disable_interrupts();
    flash_do_cmd(txbuf, rxbuf, sizeof(txbuf));
    restore_interrupts(irqsave);

    *mf_id = rxbuf[1];
    *dev_id = rxbuf[2] << 8 | rxbuf[3];
}

//
// Read Flash unique ID as 64-bit integer value.
//
static uint64_t flash_read_unique_id()
{
    // Read Unique ID instruction: 4Bh command prefix, 32 dummy bits, 64 data bits.
    uint8_t txbuf[1 + 4 + 8] = { 0x4b };
    uint8_t rxbuf[1 + 4 + 8] = {};
    uint32_t irqsave = save_and_disable_interrupts();
    flash_do_cmd(txbuf, rxbuf, sizeof(txbuf));
    restore_interrupts(irqsave);

    return (uint64_t)rxbuf[5] << 56 | (uint64_t)rxbuf[6] << 48 |
           (uint64_t)rxbuf[7] << 40 | (uint64_t)rxbuf[8] << 32 |
           (uint64_t)rxbuf[9] << 24 | (uint64_t)rxbuf[10] << 16 |
           (uint64_t)rxbuf[11] << 8 | rxbuf[12];
}

int main()
{
    stdio_init_all();
    printf("Flash info:\n");

    // Manufacturer and Device ID.
    uint8_t mf_id;
    uint16_t dev_id;
    flash_read_mf_dev_id(&mf_id, &dev_id);
    printf("Manufacturer = 0x%02x\n", mf_id);
    printf("Device = 0x%04x\n", dev_id);

    // Serial number.
    uint64_t serial_number = flash_read_unique_id();
    printf("Serial Number = 0x%016jx\n", (uintmax_t) serial_number);

    for (;;) {
        asm volatile("svc #1");
    }
}

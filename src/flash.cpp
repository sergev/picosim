//
// Serial interface to Flash memory.
//
//  Command Name            Byte 1  Byte 2  Byte 3  Byte 4  Byte 5  Byte 6  N-Bytes
//  ----------------------------------------------------------------------------------
//  Page Program            0x02    A23-A16 A15-A8  A7-A0   (D7-D0) Next    continuous
//                                                                  byte
//  Read Data               0x03    A23-A16 A15-A8  A7-A0   (D7-D0) Next    continuous
//                                                                  byte
//  Read Status             0x05    (S7-S0) -       -       -       -       continuous
//
//  Write Enable            0x06    -       -       -       -       -       -
//
//  Sector Erase            0x20    A23-A16 A15-A8  A7-A0   -       -       -
//
//  Read Serial Flash       0x5a    A23-A16 A15-A8  A7-A0   Dummy   D7-D0   continuous
//  Discoverable Parameter
//  Read JEDEC ID           0x9f    MID7-0  ID15-8  ID7-0   -       -       continuous
//
//  Read Unique ID Number   0x4b    Dummy   Dummy   Dummy   Dummy   ID7-0   continuous
//
#include "simulator.h"

// Fake serial number of the Flash chip.
static char flash_serial_number[9] = "\x12\x34\x56\x78\x9a\xbc\xde\xf0";

//
// Flash commands
//
enum {
    FLASHCMD_PAGE_PROGRAM  = 0x02,
    FLASHCMD_READ_DATA     = 0x03,
    FLASHCMD_READ_STATUS   = 0x05,
    FLASHCMD_WRITE_ENABLE  = 0x06,
    FLASHCMD_SECTOR_ERASE  = 0x20,
    FLASHCMD_READ_SFDP     = 0x5a,
    FLASHCMD_READ_JEDEC_ID = 0x9f,
    FLASHCMD_READ_UNIQ_ID  = 0x4b,
};

void Simulator::flash_select(bool enable)
{
    if (flash_enable == enable) {
        return;
    }
    if (Log::is_verbose()) {
        Log::out() << "--- " << __func__ << "() " << (enable ? "+++" : "---") << std::endl;
    }
    flash_enable = enable;
    if (enable) {
        flash_tcount = 0;
        flash_rcount = 0;
    }
}

void Simulator::flash_send(unsigned char val)
{
    if (!flash_enable) {
        return;
    }

    if (flash_tcount > 0) {
        // Check packet length.
        switch (flash_tbuf[0]) {
        case FLASHCMD_READ_JEDEC_ID: // Read JEDEC ID
            if (flash_tcount >= 3)
                goto ignore;
            break;
        case FLASHCMD_READ_UNIQ_ID: // Read Unique ID Number
            if (flash_tcount >= 1)
                goto ignore;
            break;
        default:
            // Ignore.
ignore:     if (Log::is_verbose()) {
                Log::out() << "--- " << __func__ << "() ignore 0x" << std::hex << (unsigned)val << std::endl;
            }
            return;
        }
    }
    if (Log::is_verbose()) {
        Log::out() << "--- " << __func__ << "() send 0x" << std::hex << (unsigned)val << std::endl;
    }

    // Append data to the transmit buffer.
    flash_tbuf[flash_tcount] = val;
    flash_tcount++;
}

unsigned char Simulator::flash_receive()
{
    if (!flash_enable || flash_tcount == 0) {
        return 0;
    }

    unsigned char reply = 0;
    switch (flash_tbuf[0]) {
    case FLASHCMD_READ_JEDEC_ID: // Read JEDEC ID
        switch (flash_rcount) {
        case 1:
            reply = 0xef; // Manufacturer Winbond
            break;
        case 2:
            reply = 0x40; // Device high byte
            break;
        case 3:
            reply = 0x18; // Device low byte
            break;
        }
        flash_rcount++;
        break;
    case FLASHCMD_READ_UNIQ_ID: // Read Unique ID Number
        if (flash_rcount >= 5 && flash_rcount < 13) {
            reply = flash_serial_number[flash_rcount - 5];
        }
        flash_rcount++;
        break;
    default:                        /* Ignore */
        break;
    }
    if (Log::is_verbose()) {
        Log::out() << "--- " << __func__ << "() reply 0x" << std::hex << (unsigned)reply << std::endl;
    }
    return reply;
}

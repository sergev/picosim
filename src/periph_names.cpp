#include "peripherals.h"
//#include "esp32c3/soc.h"
//#include "esp32c3/gpio_reg.h"
//#include "esp32c3/uart_reg.h"
//#include "esp32c3/rtc_cntl_reg.h"
//#include "esp32c3/io_mux_reg.h"
//#include "esp32c3/usb_serial_jtag_reg.h"
//#include "esp32c3/system_reg.h"
//#include "esp32c3/efuse_reg.h"
//#include "esp32c3/interrupt_core0_reg.h"
//#include "esp32c3/extmem_reg.h"
//#include "esp32c3/assist_debug_reg.h"

static const std::map<unsigned, const std::string> periph_reg_name = {
    //
    // UART Controller 0 at address 6000_0000...6000_0FFF
    //
    // clang-format off
    //TODO: { UART_FIFO_REG(0),           "UART0_FIFO" },
};

//
// Get name of peripheral register at given address.
//
std::string Peripherals::reg_name(unsigned addr)
{
#if 0
    addr += SOC_PERIPHERAL_LOW;
#endif
    if (periph_reg_name.count(addr) > 0)
        return periph_reg_name.at(addr);

    std::stringstream buf;
    buf << "[0x" << std::hex << addr << "]";
    return buf.str();
}

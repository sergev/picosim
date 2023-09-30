#include "peripherals.h"
#include "rp2040/addressmap.h"
#include "rp2040/sio.h"
#include "rp2040/clocks.h"
#include "rp2040/resets.h"
#include "rp2040/syscfg.h"
#include "rp2040/vreg_and_chip_reset.h"

static const std::map<unsigned, const std::string> periph_reg_name = {
    // clang-format off
    //
    // SIO registers at address d000_0000...d000_017c
    //
    { SIO_BASE + SIO_CPUID_OFFSET,                          "CPUID" },
    { SIO_BASE + SIO_GPIO_IN_OFFSET,                        "GPIO_IN" },
    { SIO_BASE + SIO_GPIO_HI_IN_OFFSET,                     "GPIO_HI_IN" },
    { SIO_BASE + SIO_GPIO_OUT_OFFSET,                       "GPIO_OUT" },
    { SIO_BASE + SIO_GPIO_OUT_SET_OFFSET,                   "GPIO_OUT_SET" },
    { SIO_BASE + SIO_GPIO_OUT_CLR_OFFSET,                   "GPIO_OUT_CLR" },
    { SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET,                   "GPIO_OUT_XOR" },
    { SIO_BASE + SIO_GPIO_OE_OFFSET,                        "GPIO_OE" },
    { SIO_BASE + SIO_GPIO_OE_SET_OFFSET,                    "GPIO_OE_SET" },
    { SIO_BASE + SIO_GPIO_OE_CLR_OFFSET,                    "GPIO_OE_CLR" },
    { SIO_BASE + SIO_GPIO_OE_XOR_OFFSET,                    "GPIO_OE_XOR" },
    { SIO_BASE + SIO_GPIO_HI_OUT_OFFSET,                    "GPIO_HI_OUT" },
    { SIO_BASE + SIO_GPIO_HI_OUT_SET_OFFSET,                "GPIO_HI_OUT_SET" },
    { SIO_BASE + SIO_GPIO_HI_OUT_CLR_OFFSET,                "GPIO_HI_OUT_CLR" },
    { SIO_BASE + SIO_GPIO_HI_OUT_XOR_OFFSET,                "GPIO_HI_OUT_XOR" },
    { SIO_BASE + SIO_GPIO_HI_OE_OFFSET,                     "GPIO_HI_OE" },
    { SIO_BASE + SIO_GPIO_HI_OE_SET_OFFSET,                 "GPIO_HI_OE_SET" },
    { SIO_BASE + SIO_GPIO_HI_OE_CLR_OFFSET,                 "GPIO_HI_OE_CLR" },
    { SIO_BASE + SIO_GPIO_HI_OE_XOR_OFFSET,                 "GPIO_HI_OE_XOR" },
    { SIO_BASE + SIO_FIFO_ST_OFFSET,                        "FIFO_ST" },
    { SIO_BASE + SIO_FIFO_WR_OFFSET,                        "FIFO_WR" },
    { SIO_BASE + SIO_FIFO_RD_OFFSET,                        "FIFO_RD" },
    { SIO_BASE + SIO_SPINLOCK_ST_OFFSET,                    "SPINLOCK_ST" },
    { SIO_BASE + SIO_DIV_UDIVIDEND_OFFSET,                  "DIV_UDIVIDEND" },
    { SIO_BASE + SIO_DIV_UDIVISOR_OFFSET,                   "DIV_UDIVISOR" },
    { SIO_BASE + SIO_DIV_SDIVIDEND_OFFSET,                  "DIV_SDIVIDEND" },
    { SIO_BASE + SIO_DIV_SDIVISOR_OFFSET,                   "DIV_SDIVISOR" },
    { SIO_BASE + SIO_DIV_QUOTIENT_OFFSET,                   "DIV_QUOTIENT" },
    { SIO_BASE + SIO_DIV_REMAINDER_OFFSET,                  "DIV_REMAINDER" },
    { SIO_BASE + SIO_DIV_CSR_OFFSET,                        "DIV_CSR" },
    { SIO_BASE + SIO_INTERP0_ACCUM0_OFFSET,                 "INTERP0_ACCUM0" },
    { SIO_BASE + SIO_INTERP0_ACCUM1_OFFSET,                 "INTERP0_ACCUM1" },
    { SIO_BASE + SIO_INTERP0_BASE0_OFFSET,                  "INTERP0_BASE0" },
    { SIO_BASE + SIO_INTERP0_BASE1_OFFSET,                  "INTERP0_BASE1" },
    { SIO_BASE + SIO_INTERP0_BASE2_OFFSET,                  "INTERP0_BASE2" },
    { SIO_BASE + SIO_INTERP0_POP_LANE0_OFFSET,              "INTERP0_POP_LANE0" },
    { SIO_BASE + SIO_INTERP0_POP_LANE1_OFFSET,              "INTERP0_POP_LANE1" },
    { SIO_BASE + SIO_INTERP0_POP_FULL_OFFSET,               "INTERP0_POP_FULL" },
    { SIO_BASE + SIO_INTERP0_PEEK_LANE0_OFFSET,             "INTERP0_PEEK_LANE0" },
    { SIO_BASE + SIO_INTERP0_PEEK_LANE1_OFFSET,             "INTERP0_PEEK_LANE1" },
    { SIO_BASE + SIO_INTERP0_PEEK_FULL_OFFSET,              "INTERP0_PEEK_FULL" },
    { SIO_BASE + SIO_INTERP0_CTRL_LANE0_OFFSET,             "INTERP0_CTRL_LANE0" },
    { SIO_BASE + SIO_INTERP0_CTRL_LANE1_OFFSET,             "INTERP0_CTRL_LANE1" },
    { SIO_BASE + SIO_INTERP0_ACCUM0_ADD_OFFSET,             "INTERP0_ACCUM0_ADD" },
    { SIO_BASE + SIO_INTERP0_ACCUM1_ADD_OFFSET,             "INTERP0_ACCUM1_ADD" },
    { SIO_BASE + SIO_INTERP0_BASE_1AND0_OFFSET,             "INTERP0_BASE_1AND0" },
    { SIO_BASE + SIO_INTERP1_ACCUM0_OFFSET,                 "INTERP1_ACCUM0" },
    { SIO_BASE + SIO_INTERP1_ACCUM1_OFFSET,                 "INTERP1_ACCUM1" },
    { SIO_BASE + SIO_INTERP1_BASE0_OFFSET,                  "INTERP1_BASE0" },
    { SIO_BASE + SIO_INTERP1_BASE1_OFFSET,                  "INTERP1_BASE1" },
    { SIO_BASE + SIO_INTERP1_BASE2_OFFSET,                  "INTERP1_BASE2" },
    { SIO_BASE + SIO_INTERP1_POP_LANE0_OFFSET,              "INTERP1_POP_LANE0" },
    { SIO_BASE + SIO_INTERP1_POP_LANE1_OFFSET,              "INTERP1_POP_LANE1" },
    { SIO_BASE + SIO_INTERP1_POP_FULL_OFFSET,               "INTERP1_POP_FULL" },
    { SIO_BASE + SIO_INTERP1_PEEK_LANE0_OFFSET,             "INTERP1_PEEK_LANE0" },
    { SIO_BASE + SIO_INTERP1_PEEK_LANE1_OFFSET,             "INTERP1_PEEK_LANE1" },
    { SIO_BASE + SIO_INTERP1_PEEK_FULL_OFFSET,              "INTERP1_PEEK_FULL" },
    { SIO_BASE + SIO_INTERP1_CTRL_LANE0_OFFSET,             "INTERP1_CTRL_LANE0" },
    { SIO_BASE + SIO_INTERP1_CTRL_LANE1_OFFSET,             "INTERP1_CTRL_LANE1" },
    { SIO_BASE + SIO_INTERP1_ACCUM0_ADD_OFFSET,             "INTERP1_ACCUM0_ADD" },
    { SIO_BASE + SIO_INTERP1_ACCUM1_ADD_OFFSET,             "INTERP1_ACCUM1_ADD" },
    { SIO_BASE + SIO_INTERP1_BASE_1AND0_OFFSET,             "INTERP1_BASE_1AND0" },
    { SIO_BASE + SIO_SPINLOCK0_OFFSET,                      "SPINLOCK0" },
    { SIO_BASE + SIO_SPINLOCK1_OFFSET,                      "SPINLOCK1" },
    { SIO_BASE + SIO_SPINLOCK2_OFFSET,                      "SPINLOCK2" },
    { SIO_BASE + SIO_SPINLOCK3_OFFSET,                      "SPINLOCK3" },
    { SIO_BASE + SIO_SPINLOCK4_OFFSET,                      "SPINLOCK4" },
    { SIO_BASE + SIO_SPINLOCK5_OFFSET,                      "SPINLOCK5" },
    { SIO_BASE + SIO_SPINLOCK6_OFFSET,                      "SPINLOCK6" },
    { SIO_BASE + SIO_SPINLOCK7_OFFSET,                      "SPINLOCK7" },
    { SIO_BASE + SIO_SPINLOCK8_OFFSET,                      "SPINLOCK8" },
    { SIO_BASE + SIO_SPINLOCK9_OFFSET,                      "SPINLOCK9" },
    { SIO_BASE + SIO_SPINLOCK10_OFFSET,                     "SPINLOCK10" },
    { SIO_BASE + SIO_SPINLOCK11_OFFSET,                     "SPINLOCK11" },
    { SIO_BASE + SIO_SPINLOCK12_OFFSET,                     "SPINLOCK12" },
    { SIO_BASE + SIO_SPINLOCK13_OFFSET,                     "SPINLOCK13" },
    { SIO_BASE + SIO_SPINLOCK14_OFFSET,                     "SPINLOCK14" },
    { SIO_BASE + SIO_SPINLOCK15_OFFSET,                     "SPINLOCK15" },
    { SIO_BASE + SIO_SPINLOCK16_OFFSET,                     "SPINLOCK16" },
    { SIO_BASE + SIO_SPINLOCK17_OFFSET,                     "SPINLOCK17" },
    { SIO_BASE + SIO_SPINLOCK18_OFFSET,                     "SPINLOCK18" },
    { SIO_BASE + SIO_SPINLOCK19_OFFSET,                     "SPINLOCK19" },
    { SIO_BASE + SIO_SPINLOCK20_OFFSET,                     "SPINLOCK20" },
    { SIO_BASE + SIO_SPINLOCK21_OFFSET,                     "SPINLOCK21" },
    { SIO_BASE + SIO_SPINLOCK22_OFFSET,                     "SPINLOCK22" },
    { SIO_BASE + SIO_SPINLOCK23_OFFSET,                     "SPINLOCK23" },
    { SIO_BASE + SIO_SPINLOCK24_OFFSET,                     "SPINLOCK24" },
    { SIO_BASE + SIO_SPINLOCK25_OFFSET,                     "SPINLOCK25" },
    { SIO_BASE + SIO_SPINLOCK26_OFFSET,                     "SPINLOCK26" },
    { SIO_BASE + SIO_SPINLOCK27_OFFSET,                     "SPINLOCK27" },
    { SIO_BASE + SIO_SPINLOCK28_OFFSET,                     "SPINLOCK28" },
    { SIO_BASE + SIO_SPINLOCK29_OFFSET,                     "SPINLOCK29" },
    { SIO_BASE + SIO_SPINLOCK30_OFFSET,                     "SPINLOCK30" },
    { SIO_BASE + SIO_SPINLOCK31_OFFSET,                     "SPINLOCK31" },

    //
    // Clocks registers at address 4000_8000...4000_00c4
    //
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT0_CTRL_OFFSET,          "CLK_GPOUT0_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT0_DIV_OFFSET,           "CLK_GPOUT0_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT0_SELECTED_OFFSET,      "CLK_GPOUT0_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT1_CTRL_OFFSET,          "CLK_GPOUT1_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT1_DIV_OFFSET,           "CLK_GPOUT1_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT1_SELECTED_OFFSET,      "CLK_GPOUT1_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT2_CTRL_OFFSET,          "CLK_GPOUT2_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT2_DIV_OFFSET,           "CLK_GPOUT2_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT2_SELECTED_OFFSET,      "CLK_GPOUT2_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT3_CTRL_OFFSET,          "CLK_GPOUT3_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT3_DIV_OFFSET,           "CLK_GPOUT3_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_GPOUT3_SELECTED_OFFSET,      "CLK_GPOUT3_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_REF_CTRL_OFFSET,             "CLK_REF_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_REF_DIV_OFFSET,              "CLK_REF_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_REF_SELECTED_OFFSET,         "CLK_REF_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_SYS_CTRL_OFFSET,             "CLK_SYS_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_SYS_DIV_OFFSET,              "CLK_SYS_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_SYS_SELECTED_OFFSET,         "CLK_SYS_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_PERI_CTRL_OFFSET,            "CLK_PERI_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_PERI_SELECTED_OFFSET,        "CLK_PERI_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_USB_CTRL_OFFSET,             "CLK_USB_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_USB_DIV_OFFSET,              "CLK_USB_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_USB_SELECTED_OFFSET,         "CLK_USB_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_ADC_CTRL_OFFSET,             "CLK_ADC_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_ADC_DIV_OFFSET,              "CLK_ADC_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_ADC_SELECTED_OFFSET,         "CLK_ADC_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_RTC_CTRL_OFFSET,             "CLK_RTC_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_RTC_DIV_OFFSET,              "CLK_RTC_DIV" },
    { CLOCKS_BASE + CLOCKS_CLK_RTC_SELECTED_OFFSET,         "CLK_RTC_SELECTED" },
    { CLOCKS_BASE + CLOCKS_CLK_SYS_RESUS_CTRL_OFFSET,       "CLK_SYS_RESUS_CTRL" },
    { CLOCKS_BASE + CLOCKS_CLK_SYS_RESUS_STATUS_OFFSET,     "CLK_SYS_RESUS_STATUS" },
    { CLOCKS_BASE + CLOCKS_FC0_REF_KHZ_OFFSET,              "FC0_REF_KHZ" },
    { CLOCKS_BASE + CLOCKS_FC0_MIN_KHZ_OFFSET,              "FC0_MIN_KHZ" },
    { CLOCKS_BASE + CLOCKS_FC0_MAX_KHZ_OFFSET,              "FC0_MAX_KHZ" },
    { CLOCKS_BASE + CLOCKS_FC0_DELAY_OFFSET,                "FC0_DELAY" },
    { CLOCKS_BASE + CLOCKS_FC0_INTERVAL_OFFSET,             "FC0_INTERVAL" },
    { CLOCKS_BASE + CLOCKS_FC0_SRC_OFFSET,                  "FC0_SRC" },
    { CLOCKS_BASE + CLOCKS_FC0_STATUS_OFFSET,               "FC0_STATUS" },
    { CLOCKS_BASE + CLOCKS_FC0_RESULT_OFFSET,               "FC0_RESULT" },
    { CLOCKS_BASE + CLOCKS_WAKE_EN0_OFFSET,                 "WAKE_EN0" },
    { CLOCKS_BASE + CLOCKS_WAKE_EN1_OFFSET,                 "WAKE_EN1" },
    { CLOCKS_BASE + CLOCKS_SLEEP_EN0_OFFSET,                "SLEEP_EN0" },
    { CLOCKS_BASE + CLOCKS_SLEEP_EN1_OFFSET,                "SLEEP_EN1" },
    { CLOCKS_BASE + CLOCKS_ENABLED0_OFFSET,                 "ENABLED0" },
    { CLOCKS_BASE + CLOCKS_ENABLED1_OFFSET,                 "ENABLED1" },
    { CLOCKS_BASE + CLOCKS_INTR_OFFSET,                     "INTR" },
    { CLOCKS_BASE + CLOCKS_INTE_OFFSET,                     "INTE" },
    { CLOCKS_BASE + CLOCKS_INTF_OFFSET,                     "INTF" },
    { CLOCKS_BASE + CLOCKS_INTS_OFFSET,                     "INTS" },

    //
    // System config registers at address 4000_4000...4000_0018
    //
    { SYSCFG_BASE + SYSCFG_PROC0_NMI_MASK_OFFSET,           "PROC0_NMI_MASK" },
    { SYSCFG_BASE + SYSCFG_PROC1_NMI_MASK_OFFSET,           "PROC1_NMI_MASK" },
    { SYSCFG_BASE + SYSCFG_PROC_CONFIG_OFFSET,              "PROC_CONFIG" },
    { SYSCFG_BASE + SYSCFG_PROC_IN_SYNC_BYPASS_OFFSET,      "PROC_IN_SYNC_BYPASS" },
    { SYSCFG_BASE + SYSCFG_PROC_IN_SYNC_BYPASS_HI_OFFSET,   "PROC_IN_SYNC_BYPASS_HI" },
    { SYSCFG_BASE + SYSCFG_DBGFORCE_OFFSET,                 "DBGFORCE" },
    { SYSCFG_BASE + SYSCFG_MEMPOWERDOWN_OFFSET,             "MEMPOWERDOWN" },

    //
    // VREG_AND_CHIP_RESET registers at address 4006_4000...4006_4008
    //
    { VREG_AND_CHIP_RESET_BASE + VREG_AND_CHIP_RESET_VREG_OFFSET,        "VREG" },
    { VREG_AND_CHIP_RESET_BASE + VREG_AND_CHIP_RESET_BOD_OFFSET,         "BOD" },
    { VREG_AND_CHIP_RESET_BASE + VREG_AND_CHIP_RESET_CHIP_RESET_OFFSET,  "CHIP_RESET" },

    //
    // The reset controller registers at address 4000_c000...4000_c008
    //
    { RESETS_BASE + RESETS_RESET_OFFSET,                            "RESET" },
    { RESETS_BASE + RESETS_WDSEL_OFFSET,                            "WDSEL" },
    { RESETS_BASE + RESETS_RESET_DONE_OFFSET,                       "RESET_DONE" },
    { RESETS_BASE + REG_ALIAS_SET_BITS + RESETS_RESET_OFFSET,       "RESET:set" },
    { RESETS_BASE + REG_ALIAS_SET_BITS + RESETS_WDSEL_OFFSET,       "WDSEL:set" },
    { RESETS_BASE + REG_ALIAS_SET_BITS + RESETS_RESET_DONE_OFFSET,  "RESET_DONE:set" },
    { RESETS_BASE + REG_ALIAS_CLR_BITS + RESETS_RESET_OFFSET,       "RESET:clr" },
    { RESETS_BASE + REG_ALIAS_CLR_BITS + RESETS_WDSEL_OFFSET,       "WDSEL:clr" },
    { RESETS_BASE + REG_ALIAS_CLR_BITS + RESETS_RESET_DONE_OFFSET,  "RESET_DONE:clr" },

    // clang-format on
};

//
// Get name of peripheral register at given address.
//
std::string Peripherals::reg_name(unsigned addr)
{
    addr += base_address;
    if (periph_reg_name.count(addr) > 0)
        return periph_reg_name.at(addr);

    std::stringstream buf;
    buf << "Register [" << std::hex << addr << "]";
    return buf.str();
}

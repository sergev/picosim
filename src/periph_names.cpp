#include "peripherals.h"
#include "rp2040/addressmap.h"
#include "rp2040/sio.h"
#include "rp2040/clocks.h"
#include "rp2040/resets.h"
#include "rp2040/syscfg.h"
#include "rp2040/vreg_and_chip_reset.h"
#include "rp2040/pads_bank0.h"
#include "rp2040/watchdog.h"
#include "rp2040/tbman.h"
#include "rp2040/rosc.h"
#include "rp2040/xosc.h"
#include "rp2040/pll.h"
#include "rp2040/io_qspi.h"
#include "rp2040/ssi.h"
#include "rp2040/pads_qspi.h"
#include "rp2040/m0plus.h"
#include "rp2040/timer.h"
#include "rp2040/uart.h"

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
    { CLOCKS_BASE + CLOCKS_CLK_PERI_CTRL_OFFSET + 4,        "CLK_PERI_DIV:unimplemented" }, // accessed from clock_configure()
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
    { RESETS_BASE + RESETS_RESET_OFFSET,                    "RESET" },
    { RESETS_BASE + RESETS_WDSEL_OFFSET,                    "WDSEL" },
    { RESETS_BASE + RESETS_RESET_DONE_OFFSET,               "RESET_DONE" },

    //
    // User Bank Pad Control registers at address 4001_c000...4001_c080
    //
    { PADS_BANK0_BASE + PADS_BANK0_VOLTAGE_SELECT_OFFSET,   "BANK0_VOLTAGE_SELECT" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO0_OFFSET,            "BANK0_GPIO0" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO1_OFFSET,            "BANK0_GPIO1" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO2_OFFSET,            "BANK0_GPIO2" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO3_OFFSET,            "BANK0_GPIO3" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO4_OFFSET,            "BANK0_GPIO4" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO5_OFFSET,            "BANK0_GPIO5" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO6_OFFSET,            "BANK0_GPIO6" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO7_OFFSET,            "BANK0_GPIO7" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO8_OFFSET,            "BANK0_GPIO8" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO9_OFFSET,            "BANK0_GPIO9" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO10_OFFSET,           "BANK0_GPIO10" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO11_OFFSET,           "BANK0_GPIO11" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO12_OFFSET,           "BANK0_GPIO12" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO13_OFFSET,           "BANK0_GPIO13" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO14_OFFSET,           "BANK0_GPIO14" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO15_OFFSET,           "BANK0_GPIO15" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO16_OFFSET,           "BANK0_GPIO16" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO17_OFFSET,           "BANK0_GPIO17" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO18_OFFSET,           "BANK0_GPIO18" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO19_OFFSET,           "BANK0_GPIO19" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO20_OFFSET,           "BANK0_GPIO20" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO21_OFFSET,           "BANK0_GPIO21" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO22_OFFSET,           "BANK0_GPIO22" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO23_OFFSET,           "BANK0_GPIO23" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO24_OFFSET,           "BANK0_GPIO24" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO25_OFFSET,           "BANK0_GPIO25" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO26_OFFSET,           "BANK0_GPIO26" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO27_OFFSET,           "BANK0_GPIO27" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO28_OFFSET,           "BANK0_GPIO28" },
    { PADS_BANK0_BASE + PADS_BANK0_GPIO29_OFFSET,           "BANK0_GPIO29" },
    { PADS_BANK0_BASE + PADS_BANK0_SWCLK_OFFSET,            "BANK0_SWCLK" },
    { PADS_BANK0_BASE + PADS_BANK0_SWD_OFFSET,              "BANK0_SWD" },

    //
    // Watchdog registers at address 4005_8000...4005_802c
    //
    { WATCHDOG_BASE + WATCHDOG_CTRL_OFFSET,                 "WATCHDOG_CTRL" },
    { WATCHDOG_BASE + WATCHDOG_LOAD_OFFSET,                 "WATCHDOG_LOAD" },
    { WATCHDOG_BASE + WATCHDOG_REASON_OFFSET,               "WATCHDOG_REASON" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH0_OFFSET,             "WATCHDOG_SCRATCH0" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH1_OFFSET,             "WATCHDOG_SCRATCH1" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH2_OFFSET,             "WATCHDOG_SCRATCH2" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH3_OFFSET,             "WATCHDOG_SCRATCH3" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH4_OFFSET,             "WATCHDOG_SCRATCH4" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH5_OFFSET,             "WATCHDOG_SCRATCH5" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH6_OFFSET,             "WATCHDOG_SCRATCH6" },
    { WATCHDOG_BASE + WATCHDOG_SCRATCH7_OFFSET,             "WATCHDOG_SCRATCH7" },
    { WATCHDOG_BASE + WATCHDOG_TICK_OFFSET,                 "WATCHDOG_TICK" },

    //
    // TBMAN registers at address 4006c000
    //
    { TBMAN_BASE + TBMAN_PLATFORM_OFFSET,                   "TBMAN_PLATFORM" },

    //
    // ROSC registers at address 4006_0000...4006_0020
    //
    { ROSC_BASE + ROSC_CTRL_OFFSET,                         "ROSC_CTRL" },
    { ROSC_BASE + ROSC_FREQA_OFFSET,                        "ROSC_FREQA" },
    { ROSC_BASE + ROSC_FREQB_OFFSET,                        "ROSC_FREQB" },
    { ROSC_BASE + ROSC_DORMANT_OFFSET,                      "ROSC_DORMANT" },
    { ROSC_BASE + ROSC_DIV_OFFSET,                          "ROSC_DIV" },
    { ROSC_BASE + ROSC_PHASE_OFFSET,                        "ROSC_PHASE" },
    { ROSC_BASE + ROSC_STATUS_OFFSET,                       "ROSC_STATUS" },
    { ROSC_BASE + ROSC_RANDOMBIT_OFFSET,                    "ROSC_RANDOMBIT" },
    { ROSC_BASE + ROSC_COUNT_OFFSET,                        "ROSC_COUNT" },

    //
    // XOSC registers at address 4002_4000...4002_401c
    //
    { XOSC_BASE + XOSC_CTRL_OFFSET,                         "XOSC_CTRL" },
    { XOSC_BASE + XOSC_STATUS_OFFSET,                       "XOSC_STATUS" },
    { XOSC_BASE + XOSC_DORMANT_OFFSET,                      "XOSC_DORMANT" },
    { XOSC_BASE + XOSC_STARTUP_OFFSET,                      "XOSC_STARTUP" },
    { XOSC_BASE + XOSC_COUNT_OFFSET,                        "XOSC_COUNT" },

    //
    // PLL_SYS and PLL_USB registers at addresses 4002_8000 and 4002_c000 respectively
    //
    { PLL_SYS_BASE + PLL_CS_OFFSET,                         "PLL_SYS_CS" },
    { PLL_SYS_BASE + PLL_PWR_OFFSET,                        "PLL_SYS_PWR" },
    { PLL_SYS_BASE + PLL_FBDIV_INT_OFFSET,                  "PLL_SYS_FBDIV_INT" },
    { PLL_SYS_BASE + PLL_PRIM_OFFSET,                       "PLL_SYS_PRIM" },

    { PLL_USB_BASE + PLL_CS_OFFSET,                         "PLL_USB_CS" },
    { PLL_USB_BASE + PLL_PWR_OFFSET,                        "PLL_USB_PWR" },
    { PLL_USB_BASE + PLL_FBDIV_INT_OFFSET,                  "PLL_USB_FBDIV_INT" },
    { PLL_USB_BASE + PLL_PRIM_OFFSET,                       "PLL_USB_PRIM" },

    //
    // QSPI Bank IO registers at address 4001_8000...4001_8054
    //
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SCLK_STATUS_OFFSET,  "GPIO_QSPI_SCLK_STATUS" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SCLK_CTRL_OFFSET,    "GPIO_QSPI_SCLK_CTRL" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SS_STATUS_OFFSET,    "GPIO_QSPI_SS_STATUS" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SS_CTRL_OFFSET,      "GPIO_QSPI_SS_CTRL" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD0_STATUS_OFFSET,   "GPIO_QSPI_SD0_STATUS" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD0_CTRL_OFFSET,     "GPIO_QSPI_SD0_CTRL" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD1_STATUS_OFFSET,   "GPIO_QSPI_SD1_STATUS" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD1_CTRL_OFFSET,     "GPIO_QSPI_SD1_CTRL" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD2_STATUS_OFFSET,   "GPIO_QSPI_SD2_STATUS" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD2_CTRL_OFFSET,     "GPIO_QSPI_SD2_CTRL" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD3_STATUS_OFFSET,   "GPIO_QSPI_SD3_STATUS" },
    { IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD3_CTRL_OFFSET,     "GPIO_QSPI_SD3_CTRL" },
    { IO_QSPI_BASE + IO_QSPI_INTR_OFFSET,                   "QSPI_INTR" },
    { IO_QSPI_BASE + IO_QSPI_PROC0_INTE_OFFSET,             "QSPI_PROC0_INTE" },
    { IO_QSPI_BASE + IO_QSPI_PROC0_INTF_OFFSET,             "QSPI_PROC0_INTF" },
    { IO_QSPI_BASE + IO_QSPI_PROC0_INTS_OFFSET,             "QSPI_PROC0_INTS" },
    { IO_QSPI_BASE + IO_QSPI_PROC1_INTE_OFFSET,             "QSPI_PROC1_INTE" },
    { IO_QSPI_BASE + IO_QSPI_PROC1_INTF_OFFSET,             "QSPI_PROC1_INTF" },
    { IO_QSPI_BASE + IO_QSPI_PROC1_INTS_OFFSET,             "QSPI_PROC1_INTS" },
    { IO_QSPI_BASE + IO_QSPI_DORMANT_WAKE_INTE_OFFSET,      "QSPI_DORMANT_WAKE_INTE" },
    { IO_QSPI_BASE + IO_QSPI_DORMANT_WAKE_INTF_OFFSET,      "QSPI_DORMANT_WAKE_INTF" },
    { IO_QSPI_BASE + IO_QSPI_DORMANT_WAKE_INTS_OFFSET,      "QSPI_DORMANT_WAKE_INTS" },

    //
    // SSI registers at address 1800_0000...1800_00f8
    //
    { XIP_SSI_BASE + SSI_CTRLR0_OFFSET,                     "SSI_CTRLR0" },
    { XIP_SSI_BASE + SSI_CTRLR1_OFFSET,                     "SSI_CTRLR1" },
    { XIP_SSI_BASE + SSI_SSIENR_OFFSET,                     "SSI_SSIENR" },
    { XIP_SSI_BASE + SSI_MWCR_OFFSET,                       "SSI_MWCR" },
    { XIP_SSI_BASE + SSI_SER_OFFSET,                        "SSI_SER" },
    { XIP_SSI_BASE + SSI_BAUDR_OFFSET,                      "SSI_BAUDR" },
    { XIP_SSI_BASE + SSI_TXFTLR_OFFSET,                     "SSI_TXFTLR" },
    { XIP_SSI_BASE + SSI_RXFTLR_OFFSET,                     "SSI_RXFTLR" },
    { XIP_SSI_BASE + SSI_TXFLR_OFFSET,                      "SSI_TXFLR" },
    { XIP_SSI_BASE + SSI_RXFLR_OFFSET,                      "SSI_RXFLR" },
    { XIP_SSI_BASE + SSI_SR_OFFSET,                         "SSI_SR" },
    { XIP_SSI_BASE + SSI_IMR_OFFSET,                        "SSI_IMR" },
    { XIP_SSI_BASE + SSI_ISR_OFFSET,                        "SSI_ISR" },
    { XIP_SSI_BASE + SSI_RISR_OFFSET,                       "SSI_RISR" },
    { XIP_SSI_BASE + SSI_TXOICR_OFFSET,                     "SSI_TXOICR" },
    { XIP_SSI_BASE + SSI_RXOICR_OFFSET,                     "SSI_RXOICR" },
    { XIP_SSI_BASE + SSI_RXUICR_OFFSET,                     "SSI_RXUICR" },
    { XIP_SSI_BASE + SSI_MSTICR_OFFSET,                     "SSI_MSTICR" },
    { XIP_SSI_BASE + SSI_ICR_OFFSET,                        "SSI_ICR" },
    { XIP_SSI_BASE + SSI_DMACR_OFFSET,                      "SSI_DMACR" },
    { XIP_SSI_BASE + SSI_DMATDLR_OFFSET,                    "SSI_DMATDLR" },
    { XIP_SSI_BASE + SSI_DMARDLR_OFFSET,                    "SSI_DMARDLR" },
    { XIP_SSI_BASE + SSI_IDR_OFFSET,                        "SSI_IDR" },
    { XIP_SSI_BASE + SSI_SSI_VERSION_ID_OFFSET,             "SSI_VERSION_ID" },
    { XIP_SSI_BASE + SSI_DR0_OFFSET,                        "SSI_DR0" },
    { XIP_SSI_BASE + SSI_RX_SAMPLE_DLY_OFFSET,              "SSI_RX_SAMPLE_DLY" },
    { XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET,                 "SSI_SPI_CTRLR0" },
    { XIP_SSI_BASE + SSI_TXD_DRIVE_EDGE_OFFSET,             "SSI_TXD_DRIVE_EDGE" },

    //
    // QSPI Bank Pad Control registers at address 4002_0000...4002_0018
    //
    { PADS_QSPI_BASE + PADS_QSPI_VOLTAGE_SELECT_OFFSET,     "QSPI_VOLTAGE_SELECT" },
    { PADS_QSPI_BASE + PADS_QSPI_GPIO_QSPI_SCLK_OFFSET,     "GPIO_QSPI_SCLK" },
    { PADS_QSPI_BASE + PADS_QSPI_GPIO_QSPI_SD0_OFFSET,      "GPIO_QSPI_SD0" },
    { PADS_QSPI_BASE + PADS_QSPI_GPIO_QSPI_SD1_OFFSET,      "GPIO_QSPI_SD1" },
    { PADS_QSPI_BASE + PADS_QSPI_GPIO_QSPI_SD2_OFFSET,      "GPIO_QSPI_SD2" },
    { PADS_QSPI_BASE + PADS_QSPI_GPIO_QSPI_SD3_OFFSET,      "GPIO_QSPI_SD3" },
    { PADS_QSPI_BASE + PADS_QSPI_GPIO_QSPI_SS_OFFSET,       "GPIO_QSPI_SS" },

    //
    // ARM Cortex-M0+ registers at address e000_0000...e000_ffff
    //
    { PPB_BASE + M0PLUS_SYST_CSR_OFFSET,                    "M0PLUS_SYST_CSR" },
    { PPB_BASE + M0PLUS_SYST_RVR_OFFSET,                    "M0PLUS_SYST_RVR" },
    { PPB_BASE + M0PLUS_SYST_CVR_OFFSET,                    "M0PLUS_SYST_CVR" },
    { PPB_BASE + M0PLUS_SYST_CALIB_OFFSET,                  "M0PLUS_SYST_CALIB" },
    { PPB_BASE + M0PLUS_NVIC_ISER_OFFSET,                   "M0PLUS_NVIC_ISER" },
    { PPB_BASE + M0PLUS_NVIC_ICER_OFFSET,                   "M0PLUS_NVIC_ICER" },
    { PPB_BASE + M0PLUS_NVIC_ISPR_OFFSET,                   "M0PLUS_NVIC_ISPR" },
    { PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET,                   "M0PLUS_NVIC_ICPR" },
    { PPB_BASE + M0PLUS_NVIC_IPR0_OFFSET,                   "M0PLUS_NVIC_IPR0" },
    { PPB_BASE + M0PLUS_NVIC_IPR1_OFFSET,                   "M0PLUS_NVIC_IPR1" },
    { PPB_BASE + M0PLUS_NVIC_IPR2_OFFSET,                   "M0PLUS_NVIC_IPR2" },
    { PPB_BASE + M0PLUS_NVIC_IPR3_OFFSET,                   "M0PLUS_NVIC_IPR3" },
    { PPB_BASE + M0PLUS_NVIC_IPR4_OFFSET,                   "M0PLUS_NVIC_IPR4" },
    { PPB_BASE + M0PLUS_NVIC_IPR5_OFFSET,                   "M0PLUS_NVIC_IPR5" },
    { PPB_BASE + M0PLUS_NVIC_IPR6_OFFSET,                   "M0PLUS_NVIC_IPR6" },
    { PPB_BASE + M0PLUS_NVIC_IPR7_OFFSET,                   "M0PLUS_NVIC_IPR7" },
    { PPB_BASE + M0PLUS_CPUID_OFFSET,                       "M0PLUS_CPUID" },
    { PPB_BASE + M0PLUS_ICSR_OFFSET,                        "M0PLUS_ICSR" },
    { PPB_BASE + M0PLUS_VTOR_OFFSET,                        "M0PLUS_VTOR" },
    { PPB_BASE + M0PLUS_AIRCR_OFFSET,                       "M0PLUS_AIRCR" },
    { PPB_BASE + M0PLUS_SCR_OFFSET,                         "M0PLUS_SCR" },
    { PPB_BASE + M0PLUS_CCR_OFFSET,                         "M0PLUS_CCR" },
    { PPB_BASE + M0PLUS_SHPR2_OFFSET,                       "M0PLUS_SHPR2" },
    { PPB_BASE + M0PLUS_SHPR3_OFFSET,                       "M0PLUS_SHPR3" },
    { PPB_BASE + M0PLUS_SHCSR_OFFSET,                       "M0PLUS_SHCSR" },
    { PPB_BASE + M0PLUS_MPU_TYPE_OFFSET,                    "M0PLUS_MPU_TYPE" },
    { PPB_BASE + M0PLUS_MPU_CTRL_OFFSET,                    "M0PLUS_MPU_CTRL" },
    { PPB_BASE + M0PLUS_MPU_RNR_OFFSET,                     "M0PLUS_MPU_RNR" },
    { PPB_BASE + M0PLUS_MPU_RBAR_OFFSET,                    "M0PLUS_MPU_RBAR" },
    { PPB_BASE + M0PLUS_MPU_RASR_OFFSET,                    "M0PLUS_MPU_RASR" },

    //
    // Timer registers at address 4005_4000...4005_4040
    //
    { TIMER_BASE + TIMER_TIMEHW_OFFSET,                     "TIMER_TIMEHW" },
    { TIMER_BASE + TIMER_TIMELW_OFFSET,                     "TIMER_TIMELW" },
    { TIMER_BASE + TIMER_TIMEHR_OFFSET,                     "TIMER_TIMEHR" },
    { TIMER_BASE + TIMER_TIMELR_OFFSET,                     "TIMER_TIMELR" },
    { TIMER_BASE + TIMER_ALARM0_OFFSET,                     "TIMER_ALARM0" },
    { TIMER_BASE + TIMER_ALARM1_OFFSET,                     "TIMER_ALARM1" },
    { TIMER_BASE + TIMER_ALARM2_OFFSET,                     "TIMER_ALARM2" },
    { TIMER_BASE + TIMER_ALARM3_OFFSET,                     "TIMER_ALARM3" },
    { TIMER_BASE + TIMER_ARMED_OFFSET,                      "TIMER_ARMED" },
    { TIMER_BASE + TIMER_TIMERAWH_OFFSET,                   "TIMER_TIMERAWH" },
    { TIMER_BASE + TIMER_TIMERAWL_OFFSET,                   "TIMER_TIMERAWL" },
    { TIMER_BASE + TIMER_DBGPAUSE_OFFSET,                   "TIMER_DBGPAUSE" },
    { TIMER_BASE + TIMER_PAUSE_OFFSET,                      "TIMER_PAUSE" },
    { TIMER_BASE + TIMER_INTR_OFFSET,                       "TIMER_INTR" },
    { TIMER_BASE + TIMER_INTE_OFFSET,                       "TIMER_INTE" },
    { TIMER_BASE + TIMER_INTF_OFFSET,                       "TIMER_INTF" },
    { TIMER_BASE + TIMER_INTS_OFFSET,                       "TIMER_INTS" },

    //
    // UART0/UART1 registers at address 4003_4000 and 0x40038000 respectively
    //
    { UART0_BASE + UART_UARTDR_OFFSET,                      "UART0_DR" },
    { UART0_BASE + UART_UARTRSR_OFFSET,                     "UART0_RSR" },
    { UART0_BASE + UART_UARTFR_OFFSET,                      "UART0_FR" },
    { UART0_BASE + UART_UARTILPR_OFFSET,                    "UART0_ILPR" },
    { UART0_BASE + UART_UARTIBRD_OFFSET,                    "UART0_IBRD" },
    { UART0_BASE + UART_UARTFBRD_OFFSET,                    "UART0_FBRD" },
    { UART0_BASE + UART_UARTLCR_H_OFFSET,                   "UART0_LCR_H" },
    { UART0_BASE + UART_UARTCR_OFFSET,                      "UART0_CR" },
    { UART0_BASE + UART_UARTIFLS_OFFSET,                    "UART0_IFLS" },
    { UART0_BASE + UART_UARTIMSC_OFFSET,                    "UART0_IMSC" },
    { UART0_BASE + UART_UARTRIS_OFFSET,                     "UART0_RIS" },
    { UART0_BASE + UART_UARTMIS_OFFSET,                     "UART0_MIS" },
    { UART0_BASE + UART_UARTICR_OFFSET,                     "UART0_ICR" },
    { UART0_BASE + UART_UARTDMACR_OFFSET,                   "UART0_DMACR" },
    { UART0_BASE + UART_UARTPERIPHID0_OFFSET,               "UART0_PERIPHID0" },
    { UART0_BASE + UART_UARTPERIPHID1_OFFSET,               "UART0_PERIPHID1" },
    { UART0_BASE + UART_UARTPERIPHID2_OFFSET,               "UART0_PERIPHID2" },
    { UART0_BASE + UART_UARTPERIPHID3_OFFSET,               "UART0_PERIPHID3" },
    { UART0_BASE + UART_UARTPCELLID0_OFFSET,                "UART0_PCELLID0" },
    { UART0_BASE + UART_UARTPCELLID1_OFFSET,                "UART0_PCELLID1" },
    { UART0_BASE + UART_UARTPCELLID2_OFFSET,                "UART0_PCELLID2" },
    { UART0_BASE + UART_UARTPCELLID3_OFFSET,                "UART0_PCELLID3" },

    { UART1_BASE + UART_UARTDR_OFFSET,                      "UART1_DR" },
    { UART1_BASE + UART_UARTRSR_OFFSET,                     "UART1_RSR" },
    { UART1_BASE + UART_UARTFR_OFFSET,                      "UART1_FR" },
    { UART1_BASE + UART_UARTILPR_OFFSET,                    "UART1_ILPR" },
    { UART1_BASE + UART_UARTIBRD_OFFSET,                    "UART1_IBRD" },
    { UART1_BASE + UART_UARTFBRD_OFFSET,                    "UART1_FBRD" },
    { UART1_BASE + UART_UARTLCR_H_OFFSET,                   "UART1_LCR_H" },
    { UART1_BASE + UART_UARTCR_OFFSET,                      "UART1_CR" },
    { UART1_BASE + UART_UARTIFLS_OFFSET,                    "UART1_IFLS" },
    { UART1_BASE + UART_UARTIMSC_OFFSET,                    "UART1_IMSC" },
    { UART1_BASE + UART_UARTRIS_OFFSET,                     "UART1_RIS" },
    { UART1_BASE + UART_UARTMIS_OFFSET,                     "UART1_MIS" },
    { UART1_BASE + UART_UARTICR_OFFSET,                     "UART1_ICR" },
    { UART1_BASE + UART_UARTDMACR_OFFSET,                   "UART1_DMACR" },
    { UART1_BASE + UART_UARTPERIPHID0_OFFSET,               "UART1_PERIPHID0" },
    { UART1_BASE + UART_UARTPERIPHID1_OFFSET,               "UART1_PERIPHID1" },
    { UART1_BASE + UART_UARTPERIPHID2_OFFSET,               "UART1_PERIPHID2" },
    { UART1_BASE + UART_UARTPERIPHID3_OFFSET,               "UART1_PERIPHID3" },
    { UART1_BASE + UART_UARTPCELLID0_OFFSET,                "UART1_PCELLID0" },
    { UART1_BASE + UART_UARTPCELLID1_OFFSET,                "UART1_PCELLID1" },
    { UART1_BASE + UART_UARTPCELLID2_OFFSET,                "UART1_PCELLID2" },
    { UART1_BASE + UART_UARTPCELLID3_OFFSET,                "UART1_PCELLID3" },

    // clang-format on
};

//
// Get name of peripheral register at given address.
//
std::string Peripherals::reg_name(unsigned addr)
{
    addr += base_address;

    if (periph_reg_name.count(addr) > 0) {
        return periph_reg_name.at(addr);
    }
    else if (periph_reg_name.count(addr - REG_ALIAS_SET_BITS) > 0) {
        return periph_reg_name.at(addr - REG_ALIAS_SET_BITS) + ":set";
    }
    else if (periph_reg_name.count(addr - REG_ALIAS_CLR_BITS) > 0) {
        return periph_reg_name.at(addr - REG_ALIAS_CLR_BITS) + ":clr";
    }
    else if (periph_reg_name.count(addr - REG_ALIAS_XOR_BITS) > 0) {
        return periph_reg_name.at(addr - REG_ALIAS_XOR_BITS) + ":xor";
    } else {
        // Unknown register.
        std::stringstream buf;
        buf << "Register [" << std::hex << addr << "]";
        return buf.str();
    }
}

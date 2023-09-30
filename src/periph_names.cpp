#include "peripherals.h"
#include "rp2040/addressmap.h"
#include "rp2040/sio.h"

static const std::map<unsigned, const std::string> periph_reg_name = {
    //
    // SIO registers at address d000_0000...d000_017c
    //
    // clang-format off
    { SIO_BASE + SIO_CPUID_OFFSET,                          "SIO_CPUID" },
    { SIO_BASE + SIO_GPIO_IN_OFFSET,                        "SIO_GPIO_IN" },
    { SIO_BASE + SIO_GPIO_HI_IN_OFFSET,                     "SIO_GPIO_HI_IN" },
    { SIO_BASE + SIO_GPIO_OUT_OFFSET,                       "SIO_GPIO_OUT" },
    { SIO_BASE + SIO_GPIO_OUT_SET_OFFSET,                   "SIO_GPIO_OUT_SET" },
    { SIO_BASE + SIO_GPIO_OUT_CLR_OFFSET,                   "SIO_GPIO_OUT_CLR" },
    { SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET,                   "SIO_GPIO_OUT_XOR" },
    { SIO_BASE + SIO_GPIO_OE_OFFSET,                        "SIO_GPIO_OE" },
    { SIO_BASE + SIO_GPIO_OE_SET_OFFSET,                    "SIO_GPIO_OE_SET" },
    { SIO_BASE + SIO_GPIO_OE_CLR_OFFSET,                    "SIO_GPIO_OE_CLR" },
    { SIO_BASE + SIO_GPIO_OE_XOR_OFFSET,                    "SIO_GPIO_OE_XOR" },
    { SIO_BASE + SIO_GPIO_HI_OUT_OFFSET,                    "SIO_GPIO_HI_OUT" },
    { SIO_BASE + SIO_GPIO_HI_OUT_SET_OFFSET,                "SIO_GPIO_HI_OUT_SET" },
    { SIO_BASE + SIO_GPIO_HI_OUT_CLR_OFFSET,                "SIO_GPIO_HI_OUT_CLR" },
    { SIO_BASE + SIO_GPIO_HI_OUT_XOR_OFFSET,                "SIO_GPIO_HI_OUT_XOR" },
    { SIO_BASE + SIO_GPIO_HI_OE_OFFSET,                     "SIO_GPIO_HI_OE" },
    { SIO_BASE + SIO_GPIO_HI_OE_SET_OFFSET,                 "SIO_GPIO_HI_OE_SET" },
    { SIO_BASE + SIO_GPIO_HI_OE_CLR_OFFSET,                 "SIO_GPIO_HI_OE_CLR" },
    { SIO_BASE + SIO_GPIO_HI_OE_XOR_OFFSET,                 "SIO_GPIO_HI_OE_XOR" },
    { SIO_BASE + SIO_FIFO_ST_OFFSET,                        "SIO_FIFO_ST" },
    { SIO_BASE + SIO_FIFO_WR_OFFSET,                        "SIO_FIFO_WR" },
    { SIO_BASE + SIO_FIFO_RD_OFFSET,                        "SIO_FIFO_RD" },
    { SIO_BASE + SIO_SPINLOCK_ST_OFFSET,                    "SIO_SPINLOCK_ST" },
    { SIO_BASE + SIO_DIV_UDIVIDEND_OFFSET,                  "SIO_DIV_UDIVIDEND" },
    { SIO_BASE + SIO_DIV_UDIVISOR_OFFSET,                   "SIO_DIV_UDIVISOR" },
    { SIO_BASE + SIO_DIV_SDIVIDEND_OFFSET,                  "SIO_DIV_SDIVIDEND" },
    { SIO_BASE + SIO_DIV_SDIVISOR_OFFSET,                   "SIO_DIV_SDIVISOR" },
    { SIO_BASE + SIO_DIV_QUOTIENT_OFFSET,                   "SIO_DIV_QUOTIENT" },
    { SIO_BASE + SIO_DIV_REMAINDER_OFFSET,                  "SIO_DIV_REMAINDER" },
    { SIO_BASE + SIO_DIV_CSR_OFFSET,                        "SIO_DIV_CSR" },
    { SIO_BASE + SIO_INTERP0_ACCUM0_OFFSET,                 "SIO_INTERP0_ACCUM0" },
    { SIO_BASE + SIO_INTERP0_ACCUM1_OFFSET,                 "SIO_INTERP0_ACCUM1" },
    { SIO_BASE + SIO_INTERP0_BASE0_OFFSET,                  "SIO_INTERP0_BASE0" },
    { SIO_BASE + SIO_INTERP0_BASE1_OFFSET,                  "SIO_INTERP0_BASE1" },
    { SIO_BASE + SIO_INTERP0_BASE2_OFFSET,                  "SIO_INTERP0_BASE2" },
    { SIO_BASE + SIO_INTERP0_POP_LANE0_OFFSET,              "SIO_INTERP0_POP_LANE0" },
    { SIO_BASE + SIO_INTERP0_POP_LANE1_OFFSET,              "SIO_INTERP0_POP_LANE1" },
    { SIO_BASE + SIO_INTERP0_POP_FULL_OFFSET,               "SIO_INTERP0_POP_FULL" },
    { SIO_BASE + SIO_INTERP0_PEEK_LANE0_OFFSET,             "SIO_INTERP0_PEEK_LANE0" },
    { SIO_BASE + SIO_INTERP0_PEEK_LANE1_OFFSET,             "SIO_INTERP0_PEEK_LANE1" },
    { SIO_BASE + SIO_INTERP0_PEEK_FULL_OFFSET,              "SIO_INTERP0_PEEK_FULL" },
    { SIO_BASE + SIO_INTERP0_CTRL_LANE0_OFFSET,             "SIO_INTERP0_CTRL_LANE0" },
    { SIO_BASE + SIO_INTERP0_CTRL_LANE1_OFFSET,             "SIO_INTERP0_CTRL_LANE1" },
    { SIO_BASE + SIO_INTERP0_ACCUM0_ADD_OFFSET,             "SIO_INTERP0_ACCUM0_ADD" },
    { SIO_BASE + SIO_INTERP0_ACCUM1_ADD_OFFSET,             "SIO_INTERP0_ACCUM1_ADD" },
    { SIO_BASE + SIO_INTERP0_BASE_1AND0_OFFSET,             "SIO_INTERP0_BASE_1AND0" },
    { SIO_BASE + SIO_INTERP1_ACCUM0_OFFSET,                 "SIO_INTERP1_ACCUM0" },
    { SIO_BASE + SIO_INTERP1_ACCUM1_OFFSET,                 "SIO_INTERP1_ACCUM1" },
    { SIO_BASE + SIO_INTERP1_BASE0_OFFSET,                  "SIO_INTERP1_BASE0" },
    { SIO_BASE + SIO_INTERP1_BASE1_OFFSET,                  "SIO_INTERP1_BASE1" },
    { SIO_BASE + SIO_INTERP1_BASE2_OFFSET,                  "SIO_INTERP1_BASE2" },
    { SIO_BASE + SIO_INTERP1_POP_LANE0_OFFSET,              "SIO_INTERP1_POP_LANE0" },
    { SIO_BASE + SIO_INTERP1_POP_LANE1_OFFSET,              "SIO_INTERP1_POP_LANE1" },
    { SIO_BASE + SIO_INTERP1_POP_FULL_OFFSET,               "SIO_INTERP1_POP_FULL" },
    { SIO_BASE + SIO_INTERP1_PEEK_LANE0_OFFSET,             "SIO_INTERP1_PEEK_LANE0" },
    { SIO_BASE + SIO_INTERP1_PEEK_LANE1_OFFSET,             "SIO_INTERP1_PEEK_LANE1" },
    { SIO_BASE + SIO_INTERP1_PEEK_FULL_OFFSET,              "SIO_INTERP1_PEEK_FULL" },
    { SIO_BASE + SIO_INTERP1_CTRL_LANE0_OFFSET,             "SIO_INTERP1_CTRL_LANE0" },
    { SIO_BASE + SIO_INTERP1_CTRL_LANE1_OFFSET,             "SIO_INTERP1_CTRL_LANE1" },
    { SIO_BASE + SIO_INTERP1_ACCUM0_ADD_OFFSET,             "SIO_INTERP1_ACCUM0_ADD" },
    { SIO_BASE + SIO_INTERP1_ACCUM1_ADD_OFFSET,             "SIO_INTERP1_ACCUM1_ADD" },
    { SIO_BASE + SIO_INTERP1_BASE_1AND0_OFFSET,             "SIO_INTERP1_BASE_1AND0" },
    { SIO_BASE + SIO_SPINLOCK0_OFFSET,                      "SIO_SPINLOCK0" },
    { SIO_BASE + SIO_SPINLOCK1_OFFSET,                      "SIO_SPINLOCK1" },
    { SIO_BASE + SIO_SPINLOCK2_OFFSET,                      "SIO_SPINLOCK2" },
    { SIO_BASE + SIO_SPINLOCK3_OFFSET,                      "SIO_SPINLOCK3" },
    { SIO_BASE + SIO_SPINLOCK4_OFFSET,                      "SIO_SPINLOCK4" },
    { SIO_BASE + SIO_SPINLOCK5_OFFSET,                      "SIO_SPINLOCK5" },
    { SIO_BASE + SIO_SPINLOCK6_OFFSET,                      "SIO_SPINLOCK6" },
    { SIO_BASE + SIO_SPINLOCK7_OFFSET,                      "SIO_SPINLOCK7" },
    { SIO_BASE + SIO_SPINLOCK8_OFFSET,                      "SIO_SPINLOCK8" },
    { SIO_BASE + SIO_SPINLOCK9_OFFSET,                      "SIO_SPINLOCK9" },
    { SIO_BASE + SIO_SPINLOCK10_OFFSET,                     "SIO_SPINLOCK10" },
    { SIO_BASE + SIO_SPINLOCK11_OFFSET,                     "SIO_SPINLOCK11" },
    { SIO_BASE + SIO_SPINLOCK12_OFFSET,                     "SIO_SPINLOCK12" },
    { SIO_BASE + SIO_SPINLOCK13_OFFSET,                     "SIO_SPINLOCK13" },
    { SIO_BASE + SIO_SPINLOCK14_OFFSET,                     "SIO_SPINLOCK14" },
    { SIO_BASE + SIO_SPINLOCK15_OFFSET,                     "SIO_SPINLOCK15" },
    { SIO_BASE + SIO_SPINLOCK16_OFFSET,                     "SIO_SPINLOCK16" },
    { SIO_BASE + SIO_SPINLOCK17_OFFSET,                     "SIO_SPINLOCK17" },
    { SIO_BASE + SIO_SPINLOCK18_OFFSET,                     "SIO_SPINLOCK18" },
    { SIO_BASE + SIO_SPINLOCK19_OFFSET,                     "SIO_SPINLOCK19" },
    { SIO_BASE + SIO_SPINLOCK20_OFFSET,                     "SIO_SPINLOCK20" },
    { SIO_BASE + SIO_SPINLOCK21_OFFSET,                     "SIO_SPINLOCK21" },
    { SIO_BASE + SIO_SPINLOCK22_OFFSET,                     "SIO_SPINLOCK22" },
    { SIO_BASE + SIO_SPINLOCK23_OFFSET,                     "SIO_SPINLOCK23" },
    { SIO_BASE + SIO_SPINLOCK24_OFFSET,                     "SIO_SPINLOCK24" },
    { SIO_BASE + SIO_SPINLOCK25_OFFSET,                     "SIO_SPINLOCK25" },
    { SIO_BASE + SIO_SPINLOCK26_OFFSET,                     "SIO_SPINLOCK26" },
    { SIO_BASE + SIO_SPINLOCK27_OFFSET,                     "SIO_SPINLOCK27" },
    { SIO_BASE + SIO_SPINLOCK28_OFFSET,                     "SIO_SPINLOCK28" },
    { SIO_BASE + SIO_SPINLOCK29_OFFSET,                     "SIO_SPINLOCK29" },
    { SIO_BASE + SIO_SPINLOCK30_OFFSET,                     "SIO_SPINLOCK30" },
    { SIO_BASE + SIO_SPINLOCK31_OFFSET,                     "SIO_SPINLOCK31" },
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
    buf << "[0x" << std::hex << addr << "]";
    return buf.str();
}

#ifndef REGISTERS_H
#define REGISTERS_H

#include <array>
#include <iomanip>

#include "phys_memory.h"
#include "systemc"
#include "tlm.h"

/**
 * @brief Register file implementation
 */
class Registers {
public:
    enum {
        R0 = 0,
        R1 = 1,
        R2,
        R3,
        R4,
        R5,
        R6,
        R7,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15,
        SL = R10, // Stack Limit
        FP = R11, // Frame Pointer
        IP = R12, // Intra-Procedure scratch register
        SP = R13, // Main Stack Pointer
        LR = R14, // Link Register
        PC = R15, // Program Counter
    };

    // Get/set register value.
    int32_t getValue(int reg_num);
    void setValue(int reg_num, int32_t value);

    // Get/set PC value.
    uint32_t getPC() const { return register_bank[PC]; }
    void setPC(uint32_t new_val) { register_bank[PC] = new_val; }

    // Increment PC counter to next address.
    void incPC(unsigned increment) { register_bank[PC] += increment; }

    // Get/set Main/Program Stack Pointer value.
    uint32_t getMSP() const { return register_bank[SP]; }
    uint32_t getPSP() const { return register_psp; }
    void setMSP(uint32_t new_val) { setValue(SP, new_val); }
    void setPSP(uint32_t new_val);

    // Dump register data to console.
    void dump();

private:
    // bank of registers (16 regs of 32bits each).
    std::array<int32_t, 16> register_bank{};

    // Program stack pointer (32 bits width).
    uint32_t register_psp{};
};

#endif

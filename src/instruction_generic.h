/*!
 \file extension_base.h
 \brief Base class for ISA extensions
 \author Màrius Montón
 \date May 2020
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef INC_EXTENSION_BASE_H_
#define INC_EXTENSION_BASE_H_

#include "log.h"
#include "systemc"

class Processor;

class Instruction_Generic {
public:
    Instruction_Generic(Processor &proc) : cpu(proc)
    {
    }

    virtual ~Instruction_Generic() = default;

    void setInstr(uint32_t p_instr)
    {
        m_instr = p_instr;
    }

    /* pure virtual functions */
    virtual int32_t opcode() const = 0;

    virtual int32_t get_rd() const { return m_instr.range(11, 7); }

    virtual void set_rd(int32_t value) { m_instr.range(11, 7) = value; }

    virtual int32_t get_rs1() const { return m_instr.range(19, 15); }

    virtual void set_rs1(int32_t value) { m_instr.range(19, 15) = value; }

    virtual int32_t get_rs2() const { return m_instr.range(24, 20); }

    virtual void set_rs2(int32_t value) { m_instr.range(24, 20) = value; }

    virtual int32_t get_funct3() const { return m_instr.range(14, 12); }

    virtual void set_funct3(int32_t value) { m_instr.range(14, 12) = value; }

protected:
    sc_dt::sc_uint<32> m_instr{ 0 };
    Processor &cpu;
};

#endif /* INC_EXTENSION_BASE_H_ */

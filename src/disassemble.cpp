//
// ARM Disassembler
//
// Copyright (C) 2023 Serge Vakulenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "disassemble.h"

#include <iomanip>
#include <sstream>

//
// Register names
//
static const char *reg_name[16] = {
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "sl", "fp", "ip", "sp", "lr", "pc",
};

//
// Unknown instruction.
//
static const char UNKNOWN[] = "???";

//
// Branch to offset.
//
static std::string thumb_branch(unsigned opcode, unsigned address)
{
    unsigned offset = opcode & 0x7ff;
    unsigned opc    = (opcode >> 11) & 0x3;
    std::ostringstream text;

    if (opc != 0) {
        return UNKNOWN;
    }

    // Sign extend 11-bit offset.
    if (offset & 0x00000400)
        offset = 0xfffff800 | offset;

    address += 4 + (offset << 1);

    text << "b.n 0x" << std::hex << std::setfill('0') << std::setw(8) << address;
    return text.str();
}

//
// Add/substract register or immediate.
//
static std::string thumb_add_sub(unsigned opcode)
{
    unsigned Rd          = (opcode >> 0) & 0x7;
    unsigned Rn          = (opcode >> 3) & 0x7;
    unsigned Rm_imm      = (opcode >> 6) & 0x7;
    unsigned opc         = opcode & (1 << 9);
    unsigned reg_imm     = opcode & (1 << 10);
    const char *mnemonic = opc ? "subs" : "adds";
    std::ostringstream text;

    if (reg_imm == 0) {
        // Add/substract two registers
        text << mnemonic << ' ' << reg_name[Rd] << ", " << reg_name[Rn] << ", " << reg_name[Rm_imm];
    } else if (Rm_imm == 0) {
        // MOVS instruction.
        text << "movs " << reg_name[Rd] << ", " << reg_name[Rn];
    } else {
        // Add/substract a register and immediate.
        text << mnemonic << ' ' << reg_name[Rd] << ", " << reg_name[Rn] << ", #" << Rm_imm;
    }
    return text.str();
}

//
// Shift by immediate.
//
static std::string thumb_shift_imm(unsigned opcode)
{
    unsigned Rd          = (opcode >> 0) & 0x7;
    unsigned Rm          = (opcode >> 3) & 0x7;
    unsigned imm         = (opcode >> 6) & 0x1f;
    unsigned opc         = (opcode >> 11) & 0x3;
    const char *mnemonic = NULL;
    std::ostringstream text;

    switch (opc) {
    case 0:
        if (imm == 0) {
            text << "movs " << reg_name[Rd] << ", " << reg_name[Rm];
            return text.str();
        } else {
            mnemonic = "lsls";
        }
        break;

    case 1:
        if (imm == 0)
            imm = 32;
        mnemonic = "lsrs";
        break;

    case 2:
        if (imm == 0)
            imm = 32;
        mnemonic = "asrs";
        break;
    }

    text << mnemonic << ' ' << reg_name[Rd] << ", " << reg_name[Rm] << ", #" << imm;
    return text.str();
}

//
// Add/substract/compare/move immediate.
//
static std::string thumb_arith_imm(unsigned opcode)
{
    unsigned imm         = opcode & 0xff;
    unsigned Rd          = (opcode >> 8) & 0x7;
    unsigned opc         = (opcode >> 11) & 0x3;
    const char *mnemonic = NULL;
    std::ostringstream text;

    switch (opc) {
    case 0:
        mnemonic = "movs";
        break;
    case 1:
        mnemonic = "cmp";
        break;
    case 2:
        mnemonic = "adds";
        break;
    case 3:
        mnemonic = "subs";
        break;
    }

    text << mnemonic << ' ' << reg_name[Rd] << ", #" << imm;
    return text.str();
}

//
// Arithmetic instructions with registers.
//
static std::string thumb_arith_reg(unsigned opcode)
{
    unsigned op          = (opcode & 0x03C0) >> 6;
    unsigned Rd          = (opcode & 0x0007);
    unsigned Rm          = (opcode & 0x0038) >> 3;
    const char *mnemonic = NULL;
    std::ostringstream text;

    switch (op) {
    case 0x0:
        mnemonic = "ands";
        break;
    case 0x1:
        mnemonic = "eors";
        break;
    case 0x2:
        mnemonic = "lsls";
        break;
    case 0x3:
        mnemonic = "lsrs";
        break;
    case 0x4:
        mnemonic = "asrs";
        break;
    case 0x5:
        mnemonic = "adcs";
        break;
    case 0x6:
        mnemonic = "sbcs";
        break;
    case 0x7:
        mnemonic = "rors";
        break;
    case 0x8:
        mnemonic = "tst";
        break;
    case 0x9:
        mnemonic = "negs";
        break;
    case 0xA:
        mnemonic = "cmp";
        break;
    case 0xB:
        mnemonic = "cmn";
        break;
    case 0xC:
        mnemonic = "orrs";
        break;
    case 0xD:
        mnemonic = "muls";
        break;
    case 0xE:
        mnemonic = "bics";
        break;
    case 0xF:
        mnemonic = "mvns";
        break;
    }

    text << mnemonic << ' ' << reg_name[Rd] << ", " << reg_name[Rm];
    return text.str();
}

//
// ADD, CMP, MOV with registers.
//
static std::string thumb_add_cmp_mov(unsigned opcode)
{
    unsigned op          = (opcode & 0x0300) >> 8;
    unsigned Rd          = (opcode & 0x0007);
    unsigned Rm          = (opcode & 0x0038) >> 3;
    unsigned H1          = (opcode & 0x0080) >> 7;
    unsigned H2          = (opcode & 0x0040) >> 6;
    const char *mnemonic = NULL;
    std::ostringstream text;

    Rd |= H1 << 3;
    Rm |= H2 << 3;

    switch (op) {
    default:
    case 0x0:
        mnemonic = "add";
        break;
    case 0x1:
        mnemonic = "cmp";
        break;
    case 0x2:
        if (Rd == 8 && Rm == 8) {
            return "nop";
        }
        mnemonic = "mov";
        break;
    }

    text << mnemonic << ' ' << reg_name[Rd] << ", " << reg_name[Rm];
    return text.str();
}

//
// BX instruction.
//
static std::string thumb_bx(unsigned opcode)
{
    unsigned Rm = (opcode >> 3) & 0x0f;
    std::ostringstream text;

    if ((opcode & 0x0087) != 0)
        return UNKNOWN;

    text << "bx " << reg_name[Rm];
    return text.str();
}

//
// Load from literal pool.
//
static std::string thumb_load_literal(unsigned opcode)
{
    unsigned immediate = opcode & 0xff;
    unsigned Rd        = (opcode >> 8) & 0x7;
    std::ostringstream text;

    immediate *= 4;

    text << "ldr " << reg_name[Rd] << ", [pc, #" << immediate << ']';

#if 0
    // TODO: show address = thumb_alignpc4(address) + immediate.
    // PC-relative data addressing is word-aligned even with Thumb.
    address = (address + 4) & ~3;
    text << std::hex << (address + immediate);
#endif
    return text.str();
}

//
// Load/Store register offset.
//
static std::string thumb_load_store_reg(unsigned opcode)
{
    unsigned Rd          = (opcode >> 0) & 0x7;
    unsigned Rn          = (opcode >> 3) & 0x7;
    unsigned Rm          = (opcode >> 6) & 0x7;
    unsigned opc         = (opcode >> 9) & 0x7;
    const char *mnemonic = NULL;
    std::ostringstream text;

    switch (opc) {
    case 0:
        mnemonic = "str";
        break;
    case 1:
        mnemonic = "strh";
        break;
    case 2:
        mnemonic = "strb";
        break;
    case 3:
        mnemonic = "ldrsb";
        break;
    case 4:
        mnemonic = "ldr";
        break;
    case 5:
        mnemonic = "ldrh";
        break;
    case 6:
        mnemonic = "ldrb";
        break;
    case 7:
        mnemonic = "ldrsh";
        break;
    }

    text << mnemonic << ' ' << reg_name[Rd] << ", [" << reg_name[Rn] << ", " << reg_name[Rm] << "]";
    return text.str();
}

//
// Load/Store immediate offset.
//
static std::string thumb_load_store_imm(unsigned opcode)
{
    unsigned offset = (opcode >> 6) & 0x1f;
    unsigned Rd     = (opcode >> 0) & 0x7;
    unsigned Rn     = (opcode >> 3) & 0x7;
    unsigned L      = opcode & (1 << 11);
    unsigned B      = opcode & (1 << 12);
    const char *mnemonic;
    std::ostringstream text;

    if ((opcode & 0xF000) == 0x8000) {
        mnemonic = L ? "ldrh" : "strh";
        offset <<= 1;
    } else if (B) {
        mnemonic = L ? "ldrb" : "strb";
    } else {
        mnemonic = L ? "ldr" : "str";
        offset <<= 2;
    }

    text << mnemonic << ' ' << reg_name[Rd] << ", [" << reg_name[Rn] << ", #" << offset << ']';
    return text.str();
}

//
// Load/Store from/to stack.
//
static std::string thumb_load_store_stack(unsigned opcode)
{
    unsigned offset      = opcode & 0xff;
    unsigned Rd          = (opcode >> 8) & 0x7;
    unsigned L           = opcode & (1 << 11);
    const char *mnemonic = L ? "ldr" : "str";
    std::ostringstream text;

    offset *= 4;
    text << mnemonic << ' ' << reg_name[Rd] << ", [" << reg_name[13] << ", #" << offset << ']';
    return text.str();
}

//
// Add to SP/PC.
//
static std::string thumb_add_sp_pc(unsigned opcode)
{
    unsigned imm         = opcode & 0xff;
    unsigned Rd          = (opcode >> 8) & 0x7;
    unsigned SP          = opcode & (1 << 11);
    const char *src_name = SP ? reg_name[13] : reg_name[15];
    std::ostringstream text;

    imm *= 4;
    text << "add " << reg_name[Rd] << ", " << src_name << ", #" << imm;
    return text.str();
}

//
// Add offset to stack pointer
//
static std::string thumb_adjust_stack(unsigned opcode)
{
    unsigned imm         = opcode & 0x7f;
    unsigned opc         = opcode & (1 << 7);
    const char *mnemonic = opc ? "sub" : "add";
    std::ostringstream text;

    imm *= 4;
    text << mnemonic << ' ' << reg_name[13] << ", #" << imm;
    return text.str();
}

static std::string thumb_breakpoint(unsigned opcode)
{
    unsigned imm = opcode & 0xff;
    std::ostringstream text;

    text << "bkpt 0x" << std::hex << std::setfill('0') << std::setw(4) << imm;
    return text.str();
}

//
// Load/Store multiple.
//
static std::string thumb_load_store_multiple(unsigned opcode)
{
    unsigned reg_list = opcode & 0xff;
    unsigned L        = opcode & (1 << 11);
    unsigned R        = opcode & (1 << 8);
    unsigned Rn       = (opcode >> 8) & 7;
    std::ostringstream text;

    if ((opcode & 0xf000) == 0xc000) {
        //
        // Generic load/store multiple.
        //
        const char *wback = "!";

        if (L) {
            text << "ldmia ";
            if (opcode & (1 << Rn))
                wback = "";
        } else {
            text << "stmia ";
        }
        text << reg_name[Rn] << wback << ", ";
    } else {
        //
        // Push/pop.
        //
        Rn = 13; // SP
        if (L) {
            text << "pop ";
            if (R)
                reg_list |= (1 << 15); // PC
        } else {
            text << "push ";
            if (R)
                reg_list |= (1 << 14); // LR
        }
    }

    text << '{';

    bool cont_flag = false;
    for (int i = 0; i <= 15; i++) {
        if (reg_list & (1 << i)) {
            if (cont_flag) {
                text << ", ";
            }
            text << reg_name[i];
            cont_flag = true;
        }
    }

    text << '}';
    return text.str();
}

//
// Conditional branch.
//
static std::string thumb_cond_branch(unsigned opcode, unsigned address)
{
    unsigned offset = opcode & 0xff;
    unsigned cond   = (opcode >> 8) & 0xf;
    std::ostringstream text;
    static const char *suffix[16] = {
        "eq", "ne", "cs", "cc", "mi", "pl", "vs", "vc",
        "hi", "ls", "ge", "lt", "gt", "le", "",   "nv",
    };

    // Sign extend 8-bit offset.
    if (offset & 0x00000080)
        offset = 0xffffff00 | offset;

    address += 4 + (offset << 1);

    text << 'b' << suffix[cond] << ".n 0x" << std::hex << std::setfill('0') << std::setw(8)
         << address;
    return text.str();
}

//
// UDF instruction.
//
static std::string thumb_udf(unsigned opcode)
{
    unsigned offset = opcode & 0xff;
    std::ostringstream text;

    text << "udf #" << offset;
    return text.str();
}

//
// SVC instruction.
//
static std::string thumb_svc(unsigned opcode)
{
    unsigned offset = opcode & 0xff;
    std::ostringstream text;

    text << "svc " << offset;
    return text.str();
}

static std::string thumb_extend(unsigned opcode)
{
    unsigned rd = opcode & 0x7;
    unsigned rs = (opcode >> 3) & 0x7;
    char suffix = (opcode & 0x0040) ? 'b' : 'h';
    char prefix = (opcode & 0x0080) ? 'u' : 's';
    std::ostringstream text;

    text << prefix << "xt" << suffix << ' ' << reg_name[rd] << ", " << reg_name[rs];
    return text.str();
}

static std::string thumb_byterev(unsigned opcode)
{
    unsigned rd = opcode & 0x7;
    unsigned rs = (opcode >> 3) & 0x7;
    std::ostringstream text;

    switch ((opcode >> 6) & 3) {
    case 0:
        text << "rev ";
        break;
    case 1:
        text << "rev16 ";
        break;
    case 3:
        text << "revsh ";
        break;
    default:
        return UNKNOWN;
    }
    text << reg_name[rd] << ", " << reg_name[rs];
    return text.str();
}

static std::string thumb_hint(unsigned opcode)
{
    switch ((opcode >> 4) & 0x0f) {
    case 1:
        return "yield";
    case 2:
        return "wfe";
    case 3:
        return "wfi";
    case 4:
        return "sev";
    default:
        return UNKNOWN;
    }
}

static std::string thumb_branch_link(unsigned opcode, unsigned address)
{
    unsigned offset = opcode & 0x7ff;
    unsigned b21    = 1 << 21;
    unsigned b22    = 1 << 22;
    std::ostringstream text;

    offset |= (opcode & 0x03ff0000) >> 5;
    if (opcode & (1 << 26)) {
        offset |= 0xff << 23;
        if ((opcode & (1 << 11)) == 0)
            b21 = 0;
        if ((opcode & (1 << 13)) == 0)
            b22 = 0;
    } else {
        if (opcode & (1 << 11))
            b21 = 0;
        if (opcode & (1 << 13))
            b22 = 0;
    }
    offset |= b21;
    offset |= b22;

    address += 4;
    address += offset << 1;

    text << "bl 0x" << std::hex << std::setfill('0') << std::setw(8) << address;
    return text.str();
}

static const char *special_name(int number)
{
    switch (number) {
    case 0:
        return "APSR";
    case 1:
        return "IAPSR";
    case 2:
        return "EAPSR";
    case 3:
        return "PSR";
    case 5:
        return "IPSR";
    case 6:
        return "EPSR";
    case 7:
        return "IEPSR";
    case 8:
        return "MSP";
    case 9:
        return "PSP";
    case 10:
        return "MSPLIM";
    case 11:
        return "PSPLIM";
    case 16:
        return "PRIMASK";
    case 17:
        return "BASEPRI";
    case 18:
        return "BASEPRI_MAX";
    case 19:
        return "FAULTMASK";
    case 20:
        return "CONTROL";
    case 0x88:
        return "MSP_NS";
    case 0x89:
        return "PSP_NS";
    case 0x8a:
        return "MSPLIM_NS";
    case 0x8b:
        return "PSPLIM_NS";
    case 0x90:
        return "PRIMASK_NS";
    case 0x91:
        return "BASEPRI_NS";
    case 0x93:
        return "FAULTMASK_NS";
    case 0x94:
        return "CONTROL_NS";
    case 0x98:
        return "SP_NS";
    }
    return "(RESERVED)";
}

static std::string thumb_barrier(unsigned opcode)
{
    unsigned option = opcode & 0x0f;
    std::ostringstream text;

    switch ((opcode >> 4) & 0x0f) {
    case 4:
        text << "dsb";
        break;
    case 5:
        text << "dmb";
        break;
    case 6:
        text << "isb";
        break;
    default:
        return UNKNOWN;
    }

    if (option) {
        text << " #" << option;
    }
    return text.str();
}

static std::string thumb_sysreg(unsigned opcode)
{
    std::ostringstream text;

    switch ((opcode >> 20) & 0x6) {
    case 0x0:
        text << "msr " << special_name(opcode & 0xff) << ", " << reg_name[(opcode >> 16) & 0x0f];
        return text.str();
    case 0x6:
        text << "mrs " << reg_name[(opcode >> 8) & 0x0f] << ", " << special_name(opcode & 0xff);
        return text.str();
    }
    return UNKNOWN;
}

//
// Disassemble 32-bit instruction.
//
static std::string disassemble_32bit(unsigned opcode, unsigned address)
{
    if ((opcode & 0xf800d000) == 0xf000d000)
        return thumb_branch_link(opcode, address);

    if ((opcode & 0xffffffc0) == 0xf3bf8f40)
        return thumb_barrier(opcode);

    if ((opcode & 0xff90f060) == 0xf3808000)
        return thumb_sysreg(opcode);

    return UNKNOWN;
}

//
// Disassemble 16-bit Thumb1 instruction.
//
static std::string disassemble_16bit(unsigned opcode, unsigned address)
{
    switch (opcode >> 8) {
    // clang-format off
    case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
    case 0x08: case 0x09: case 0x0a: case 0x0b: case 0x0c: case 0x0d: case 0x0e: case 0x0f:
    case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
        return thumb_shift_imm(opcode);

    case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
        return thumb_add_sub(opcode);

    case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26: case 0x27:
    case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
    case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
    case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
        return thumb_arith_imm(opcode);

    case 0x40: case 0x41: case 0x42: case 0x43:
        return thumb_arith_reg(opcode);

    case 0x44: case 0x45: case 0x46:
        return thumb_add_cmp_mov(opcode);

    case 0x47:
        return thumb_bx(opcode);

    case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
        return thumb_load_literal(opcode);

    case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x57:
    case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5e: case 0x5f:
        return thumb_load_store_reg(opcode);

    case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66: case 0x67:
    case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6e: case 0x6f:
    case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77:
    case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x7f:
    case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87:
    case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8e: case 0x8f:
        return thumb_load_store_imm(opcode);

    case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x96: case 0x97:
    case 0x98: case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9e: case 0x9f:
        return thumb_load_store_stack(opcode);

    case 0xa0: case 0xa1: case 0xa2: case 0xa3: case 0xa4: case 0xa5: case 0xa6: case 0xa7:
    case 0xa8: case 0xa9: case 0xaa: case 0xab: case 0xac: case 0xad: case 0xae: case 0xaf:
        return thumb_add_sp_pc(opcode);

    case 0xb0:
        return thumb_adjust_stack(opcode);

    case 0xb2:
        return thumb_extend(opcode);

    case 0xb4:
    case 0xb5:
    case 0xbc:
    case 0xbd:
        return thumb_load_store_multiple(opcode);

    case 0xba:
        return thumb_byterev(opcode);

    case 0xbe:
        return thumb_breakpoint(opcode);

    case 0xbf:
        return thumb_hint(opcode);

    case 0xc0: case 0xc1: case 0xc2: case 0xc3: case 0xc4: case 0xc5: case 0xc6: case 0xc7:
    case 0xc8: case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf:
        return thumb_load_store_multiple(opcode);

    case 0xd0: case 0xd1: case 0xd2: case 0xd3: case 0xd4: case 0xd5: case 0xd6: case 0xd7:
    case 0xd8: case 0xd9: case 0xda: case 0xdb: case 0xdc: case 0xdd:
        return thumb_cond_branch(opcode, address);

    case 0xde:
        return thumb_udf(opcode);

    case 0xdf:
        return thumb_svc(opcode);

    case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4: case 0xe5: case 0xe6: case 0xe7:
    case 0xe8: case 0xe9: case 0xea: case 0xeb: case 0xec: case 0xed: case 0xee: case 0xef:
    case 0xf0: case 0xf1: case 0xf2: case 0xf3: case 0xf4: case 0xf5: case 0xf6: case 0xf7:
    case 0xf8: case 0xf9: case 0xfa: case 0xfb: case 0xfc: case 0xfd: case 0xfe: case 0xff:
        return thumb_branch(opcode, address);

    // clang-format on
    default:
        return UNKNOWN;
    }
}

//
// Compute length of the opcode: 2 or 4 bytes.
//
unsigned arm_opcode_length(uint16_t opcode)
{
    if ((opcode & 0xe000) == 0xe000 && (opcode & 0x1800) != 0)
        return 4;

    return 2;
}

//
// Disassemble instruction.
//
std::string arm_disassemble(unsigned opcode, unsigned address)
{
    // Clear low bit ... it's set on function pointers.
    address &= ~1;

    if ((opcode >> 16) != 0) {
        return disassemble_32bit(opcode, address);
    } else {
        return disassemble_16bit(opcode, address);
    }
}

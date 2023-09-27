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

static std::string thumb_b_bl_blx(unsigned short opcode, unsigned address)
{
    unsigned offset = opcode & 0x7ff;
    unsigned opc = (opcode >> 11) & 0x3;
    std::ostringstream text;

    if (opc != 0) {
        // Unknown instruction.
        return "";
    }

    // Sign extend 11-bit offset.
    if (offset & 0x00000400)
        offset = 0xfffff800 | offset;

    address += 4 + (offset << 1);

    text << "b.n 0x" << std::hex << std::setfill('0') << std::setw(8) << address;
    return text.str();
}

static std::string thumb_add_sub(unsigned short opcode)
{
    unsigned Rd = (opcode >> 0) & 0x7;
    unsigned Rn = (opcode >> 3) & 0x7;
    unsigned Rm_imm = (opcode >> 6) & 0x7;
    unsigned opc = opcode & (1 << 9);
    unsigned reg_imm = opcode & (1 << 10);
    const char *mnemonic = opc ? "subs" : "adds";
    std::ostringstream text;

    text << mnemonic << ' ' << reg_name[Rd] << ", " << reg_name[Rn];
    if (reg_imm) {
        text << ", #" << Rm_imm;
    } else {
        text << ", " << reg_name[Rm_imm];
    }
    return text.str();
}

static std::string thumb_shift_imm(unsigned short opcode)
{
    unsigned Rd = (opcode >> 0) & 0x7;
    unsigned Rm = (opcode >> 3) & 0x7;
    unsigned imm = (opcode >> 6) & 0x1f;
    unsigned opc = (opcode >> 11) & 0x3;
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

static std::string thumb_data_proc_imm(unsigned short opcode)
{
    unsigned imm = opcode & 0xff;
    unsigned Rd = (opcode >> 8) & 0x7;
    unsigned opc = (opcode >> 11) & 0x3;
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

static std::string thumb_data_proc(unsigned short opcode)
{
    unsigned high_reg = (opcode & 0x0400) >> 10;
    unsigned op = (opcode & 0x03C0) >> 6;
    unsigned Rd = (opcode & 0x0007);
    unsigned Rm = (opcode & 0x0038) >> 3;
    unsigned H1 = (opcode & 0x0080) >> 7;
    unsigned H2 = (opcode & 0x0040) >> 6;
    const char *mnemonic = NULL;
    std::ostringstream text;

    if (high_reg) {
        Rd |= H1 << 3;
        Rm |= H2 << 3;
        op >>= 2;

        switch (op) {
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
        case 0x3:
            if ((opcode & 0x7) == 0x0) {
                if (H1) {
                    // BLX is not supported.
                    return "";
                } else {
                    text << "bx " << reg_name[Rm];
                    return text.str();
                }
            }
            // Undefined instruction.
            return "";
        }
    } else {
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
    }

    text << mnemonic << ' ' << reg_name[Rd] << ", " << reg_name[Rm];
    return text.str();
}

static std::string thumb_load_literal(unsigned short opcode)
{
    unsigned immediate = opcode & 0xff;
    unsigned Rd = (opcode >> 8) & 0x7;
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

static std::string thumb_load_store_reg(unsigned short opcode)
{
    unsigned Rd = (opcode >> 0) & 0x7;
    unsigned Rn = (opcode >> 3) & 0x7;
    unsigned Rm = (opcode >> 6) & 0x7;
    unsigned opc = (opcode >> 9) & 0x7;
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

static std::string thumb_load_store_imm(unsigned short opcode)
{
    unsigned offset = (opcode >> 6) & 0x1f;
    unsigned Rd = (opcode >> 0) & 0x7;
    unsigned Rn = (opcode >> 3) & 0x7;
    unsigned L = opcode & (1 << 11);
    unsigned B = opcode & (1 << 12);
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

static std::string thumb_load_store_stack(unsigned short opcode)
{
    unsigned offset = opcode & 0xff;
    unsigned Rd = (opcode >> 8) & 0x7;
    unsigned L = opcode & (1 << 11);
    const char *mnemonic = L ? "ldr" : "str";
    std::ostringstream text;

    offset *= 4;
    text << mnemonic << ' ' << reg_name[Rd] << ", [" << reg_name[13] << ", #" << offset << ']';
    return text.str();
}

static std::string thumb_add_sp_pc(unsigned short opcode)
{
    unsigned imm = opcode & 0xff;
    unsigned Rd = (opcode >> 8) & 0x7;
    unsigned SP = opcode & (1 << 11);
    const char *src_name = SP ? reg_name[13] : reg_name[15];
    std::ostringstream text;

    imm *= 4;
    text << "add " << reg_name[Rd] << ", " << src_name << ", #" << imm;
    return text.str();
}

static std::string thumb_adjust_stack(unsigned short opcode)
{
    unsigned imm = opcode & 0x7f;
    unsigned opc = opcode & (1 << 7);
    const char *mnemonic = opc ? "sub" : "add";
    std::ostringstream text;

    imm *= 4;
    text << mnemonic << ' ' << reg_name[13] << ", #" << imm;
    return text.str();
}

static std::string thumb_breakpoint(unsigned short opcode)
{
    unsigned imm = opcode & 0xff;
    std::ostringstream text;

    text << "bkpt 0x" << std::hex << std::setfill('0') << std::setw(4) << imm;
    return text.str();
}

static std::string thumb_load_store_multiple(unsigned short opcode)
{
    unsigned reg_list = opcode & 0xff;
    unsigned L = opcode & (1 << 11);
    unsigned R = opcode & (1 << 8);
    unsigned Rn = (opcode >> 8) & 7;
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

static std::string thumb_cond_branch(unsigned short opcode, unsigned address)
{
    unsigned offset = opcode & 0xff;
    unsigned cond = (opcode >> 8) & 0xf;
    std::ostringstream text;
    static const char *suffix[16] = {
        "eq", "ne", "cs", "cc", "mi", "pl", "vs", "vc",
        "hi", "ls", "ge", "lt", "gt", "le", "",   "nv",
    };

    if (cond == 0xf) {
        text << "svc " << offset;
    } else if (cond == 0xe) {
        text << "udf #" << offset;
    } else {
        // Sign extend 8-bit offset.
        if (offset & 0x00000080)
            offset = 0xffffff00 | offset;

        address += 4 + (offset << 1);

        text << 'b' << suffix[cond] << ".n 0x" << std::hex << std::setfill('0') << std::setw(8)
             << address;
    }
    return text.str();
}

static std::string thumb_extend(unsigned short opcode)
{
    unsigned rd = opcode & 0x7;
    unsigned rs = (opcode >> 3) & 0x7;
    char suffix = (opcode & 0x0040) ? 'b' : 'h';
    char prefix = (opcode & 0x0080) ? 'u' : 's';
    std::ostringstream text;

    text << prefix << "xt" << suffix << ' ' << reg_name[rd] << ", " << reg_name[rs];
    return text.str();
}

static std::string thumb_byterev(unsigned short opcode)
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
        // Undefined instruction.
        return "";
    }
    text << reg_name[rd] << ", " << reg_name[rs];
    return text.str();
}

static std::string thumb_hint(unsigned short opcode)
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
        return "";
    }
}

static std::string long_b_bl(unsigned opcode, unsigned address)
{
    unsigned offset = opcode & 0x7ff;
    unsigned b21 = 1 << 21;
    unsigned b22 = 1 << 22;
    std::ostringstream text;

    // Instead of combining two smaller 16-bit branch instructions,
    // Thumb2 uses only one larger 32-bit instruction.
    //
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

    if (!(opcode & (1 << 14))) {
        // B.W is not supported.
        return "";
    }
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

static std::string long_misc(unsigned opcode)
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
        return "";
    }

    if (option) {
        text << " #" << option;
    }
    return text.str();
}

//
// Branches and miscellaneous control
//
static std::string long_b_misc(unsigned opcode, unsigned address)
{
    std::ostringstream text;

    // Permanently undefined.
    if ((opcode & 0x07f07000) == 0x07f02000) {
        return "";
    }

    switch ((opcode >> 12) & 0x5) {
    case 0x1:
    case 0x5:
        return long_b_bl(opcode, address);
    case 0x4:
        return "";
    case 0:
        if (((opcode >> 23) & 0x07) != 0x07)
            return "";
        if (opcode & (1 << 26))
            return "";
        break;
    }

    switch ((opcode >> 20) & 0x7f) {
    case 0x38:
    case 0x39:
        text << "msr " << special_name(opcode & 0xff) << ", " << reg_name[(opcode >> 16) & 0x0f];
        return text.str();
    case 0x3b:
        return long_misc(opcode);
    case 0x3e:
    case 0x3f:
        text << "mrs " << reg_name[(opcode >> 8) & 0x0f] << ", " << special_name(opcode & 0xff);
        return text.str();
    }

    return "";
}

//
// Compute length of the opcode: 2 or 4 bytes.
//
unsigned arm_opcode_length(unsigned opcode)
{
    // Put 16-bit opcodes into upper bits.
    if ((opcode >> 16) == 0)
        opcode <<= 16;

    if ((opcode & 0xe0000000) == 0xe0000000 && (opcode & 0x18000000) != 0)
        return 4;

    return 2;
}

//
// Disassemble instruction.
//
std::string arm_disassemble(unsigned opcode, unsigned address)
{
    // Put 16-bit opcodes into upper bits.
    if ((opcode >> 16) == 0)
        opcode <<= 16;

    // Clear low bit ... it's set on function pointers.
    address &= ~1;

    if ((opcode & 0xe0000000) == 0xe0000000 && (opcode & 0x18000000) != 0) {
        //
        // Disassemble32-bit instruction.
        //
        if ((opcode & 0x18008000) == 0x10008000) {
            return long_b_misc(opcode, address);
        }
        return "";
    }

    //
    // Disassemble 16-bit Thumb1 instruction.
    //
    opcode >>= 16;

    if ((opcode & 0xe000) == 0x0000) {
        if ((opcode & 0x1800) == 0x1800) {
            // Add/substract register or immediate.
            return thumb_add_sub(opcode);
        } else {
            // Shift by immediate.
            return thumb_shift_imm(opcode);
        }
    }

    // Add/substract/compare/move immediate.
    else if ((opcode & 0xe000) == 0x2000) {
        return thumb_data_proc_imm(opcode);
    }

    // Data processing instructions.
    else if ((opcode & 0xf800) == 0x4000) {
        return thumb_data_proc(opcode);
    }

    // Load from literal pool.
    else if ((opcode & 0xf800) == 0x4800) {
        return thumb_load_literal(opcode);
    }

    // Load/Store register offset.
    else if ((opcode & 0xf000) == 0x5000) {
        return thumb_load_store_reg(opcode);
    }

    // Load/Store immediate offset.
    else if (((opcode & 0xe000) == 0x6000) || ((opcode & 0xf000) == 0x8000)) {
        return thumb_load_store_imm(opcode);
    }

    // Load/Store from/to stack.
    else if ((opcode & 0xf000) == 0x9000) {
        return thumb_load_store_stack(opcode);
    }

    // Add to SP/PC.
    else if ((opcode & 0xf000) == 0xa000) {
        return thumb_add_sp_pc(opcode);
    }

    // Misc.
    else if ((opcode & 0xf000) == 0xb000) {
        switch ((opcode >> 8) & 0x0f) {
        case 0x0:
            return thumb_adjust_stack(opcode);
        case 0x2:
            return thumb_extend(opcode);
        case 0x4:
        case 0x5:
        case 0xc:
        case 0xd:
            return thumb_load_store_multiple(opcode);
        case 0xa:
            return thumb_byterev(opcode);
        case 0xe:
            return thumb_breakpoint(opcode);
        case 0xf:
            return thumb_hint(opcode);
        default:
            // Undefined instruction.
            return "";
        }
    }

    // Load/Store multiple.
    else if ((opcode & 0xf000) == 0xc000) {
        return thumb_load_store_multiple(opcode);
    }

    // Conditional branch + SWI.
    else if ((opcode & 0xf000) == 0xd000) {
        return thumb_cond_branch(opcode, address);
    }

    else if ((opcode & 0xe000) == 0xe000) {
        if ((opcode & 0xf801) == 0xe801) {
            // Undefined instruction.
            return "";
        } else {
            // Branch to offset.
            return thumb_b_bl_blx(opcode, address);
        }
    }

    // Thumb: should never reach this point.
    return "";
}

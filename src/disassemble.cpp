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

#include <stdio.h>
#include <string.h>

struct arm_instruction {
    char text[128];
};

//
// Textual represenation of the condition field.
// ALways (default) is ommitted (empty string).
//
static const char *condition_strings[16] = {
    "EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE", "", "NV",
};

//
// Register names
//
static const char *reg_name[16] = {
    "r0", "r1", "r2", "r3", "r4", "r5",  "r6", "r7",
    "r8", "r9", "sl", "fp", "ip", "sp", "lr", "pc",
};

static int thumb_b_bl_blx(unsigned short opcode, unsigned address,
                          struct arm_instruction *instruction)
{
    unsigned offset = opcode & 0x7ff;
    unsigned opc = (opcode >> 11) & 0x3;
    unsigned target_address;
    const char *mnemonic = NULL;

    /* sign extend 11-bit offset */
    if (((opc == 0) || (opc == 2)) && (offset & 0x00000400))
        offset = 0xfffff800 | offset;

    target_address = address + 4 + (offset << 1);

    switch (opc) {
    /* unconditional branch */
    case 0:
        mnemonic = "B";
        break;
    /* BLX suffix */
    case 1:
        mnemonic = "BLX";
        target_address &= 0xfffffffc;
        break;
    /* BL/BLX prefix */
    case 2:
        mnemonic = "prefix";
        target_address = offset << 12;
        break;
    /* BL suffix */
    case 3:
        mnemonic = "BL";
        break;
    }

    /* TODO: deal correctly with dual opcode (prefixed) BL/BLX;
     * these are effectively 32-bit instructions even in Thumb1.  For
     * disassembly, it's simplest to always use the Thumb2 decoder.
     *
     * But some cores will evidently handle them as two instructions,
     * where exceptions may occur between the two.  The ETMv3.2+ ID
     * register has a bit which exposes this behavior.
     */
    snprintf(instruction->text, sizeof(instruction->text), "%s %#8.8x", mnemonic, target_address);

    return 0;
}

static int thumb_add_sub(unsigned short opcode, unsigned address,
                         struct arm_instruction *instruction)
{
    unsigned char Rd = (opcode >> 0) & 0x7;
    unsigned char Rn = (opcode >> 3) & 0x7;
    unsigned char Rm_imm = (opcode >> 6) & 0x7;
    unsigned opc = opcode & (1 << 9);
    unsigned reg_imm = opcode & (1 << 10);
    const char *mnemonic;

    if (opc) {
        mnemonic = "subs";
    } else {
        mnemonic = "adds";
    }

    if (reg_imm) {
        snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s, #%d", mnemonic,
                 reg_name[Rd], reg_name[Rn], Rm_imm);
    } else {
        snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s, %s", mnemonic,
                 reg_name[Rd], reg_name[Rn], reg_name[Rm_imm]);
    }

    return 0;
}

static int thumb_shift_imm(unsigned short opcode, unsigned address,
                           struct arm_instruction *instruction)
{
    unsigned char Rd = (opcode >> 0) & 0x7;
    unsigned char Rm = (opcode >> 3) & 0x7;
    unsigned char imm = (opcode >> 6) & 0x1f;
    unsigned char opc = (opcode >> 11) & 0x3;
    const char *mnemonic = NULL;

    switch (opc) {
    case 0:
        if (imm == 0) {
            snprintf(instruction->text, sizeof(instruction->text), "movs %s, %s",
                     reg_name[Rd], reg_name[Rm]);
            return 0;
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

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s, #%u", mnemonic,
             reg_name[Rd], reg_name[Rm], imm);

    return 0;
}

static int thumb_data_proc_imm(unsigned short opcode, unsigned address,
                               struct arm_instruction *instruction)
{
    unsigned char imm = opcode & 0xff;
    unsigned char Rd = (opcode >> 8) & 0x7;
    unsigned opc = (opcode >> 11) & 0x3;
    const char *mnemonic = NULL;

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

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, #%u", mnemonic, reg_name[Rd],
             imm);

    return 0;
}

static int thumb_data_proc(unsigned short opcode, unsigned address,
                           struct arm_instruction *instruction)
{
    unsigned char high_reg, op, Rm, Rd, H1, H2;
    const char *mnemonic = NULL;

    high_reg = (opcode & 0x0400) >> 10;
    op = (opcode & 0x03C0) >> 6;

    Rd = (opcode & 0x0007);
    Rm = (opcode & 0x0038) >> 3;
    H1 = (opcode & 0x0080) >> 7;
    H2 = (opcode & 0x0040) >> 6;

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
                strcpy(instruction->text, "nop");
                return 0;
            }
            mnemonic = "mov";
            break;
        case 0x3:
            if ((opcode & 0x7) == 0x0) {
                if (H1) {
                    snprintf(instruction->text, sizeof(instruction->text), "BLX %s", reg_name[Rm]);
                } else {
                    snprintf(instruction->text, sizeof(instruction->text), "BX %s", reg_name[Rm]);
                }
            } else {
                snprintf(instruction->text, sizeof(instruction->text), "UNDEFINED INSTRUCTION");
            }
            return 0;
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

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s", mnemonic, reg_name[Rd],
             reg_name[Rm]);

    return 0;
}

/* PC-relative data addressing is word-aligned even with Thumb */
static inline unsigned thumb_alignpc4(unsigned addr)
{
    return (addr + 4) & ~3;
}

static int thumb_load_literal(unsigned short opcode, unsigned address,
                              struct arm_instruction *instruction)
{
    unsigned immediate;
    unsigned char Rd = (opcode >> 8) & 0x7;

    immediate = opcode & 0x000000ff;
    immediate *= 4;

    snprintf(instruction->text, sizeof(instruction->text), "LDR %s, [pc, #%#x] ; %#8.8x",
             reg_name[Rd], immediate, thumb_alignpc4(address) + immediate);

    return 0;
}

static int thumb_load_store_reg(unsigned short opcode, unsigned address,
                                struct arm_instruction *instruction)
{
    unsigned char Rd = (opcode >> 0) & 0x7;
    unsigned char Rn = (opcode >> 3) & 0x7;
    unsigned char Rm = (opcode >> 6) & 0x7;
    unsigned char opc = (opcode >> 9) & 0x7;
    const char *mnemonic = NULL;

    switch (opc) {
    case 0:
        mnemonic = "STR";
        break;
    case 1:
        mnemonic = "STRH";
        break;
    case 2:
        mnemonic = "STRB";
        break;
    case 3:
        mnemonic = "LDRSB";
        break;
    case 4:
        mnemonic = "LDR";
        break;
    case 5:
        mnemonic = "LDRH";
        break;
    case 6:
        mnemonic = "LDRB";
        break;
    case 7:
        mnemonic = "LDRSH";
        break;
    }

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, [%s, %s]", mnemonic,
             reg_name[Rd], reg_name[Rn], reg_name[Rm]);

    return 0;
}

static int thumb_load_store_imm(unsigned short opcode, unsigned address,
                                struct arm_instruction *instruction)
{
    unsigned offset = (opcode >> 6) & 0x1f;
    unsigned char Rd = (opcode >> 0) & 0x7;
    unsigned char Rn = (opcode >> 3) & 0x7;
    unsigned L = opcode & (1 << 11);
    unsigned B = opcode & (1 << 12);
    const char *mnemonic;
    char suffix = ' ';
    unsigned shift = 2;

    if (L) {
        mnemonic = "LDR";
    } else {
        mnemonic = "STR";
    }

    if ((opcode & 0xF000) == 0x8000) {
        suffix = 'H';
        shift = 1;
    } else if (B) {
        suffix = 'B';
        shift = 0;
    }

    snprintf(instruction->text, sizeof(instruction->text), "%s%c %s, [%s, #%#x]", mnemonic, suffix,
             reg_name[Rd], reg_name[Rn], offset << shift);

    return 0;
}

static int thumb_load_store_stack(unsigned short opcode, unsigned address,
                                  struct arm_instruction *instruction)
{
    unsigned offset = opcode & 0xff;
    unsigned char Rd = (opcode >> 8) & 0x7;
    unsigned L = opcode & (1 << 11);
    const char *mnemonic;

    if (L) {
        mnemonic = "LDR";
    } else {
        mnemonic = "STR";
    }

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, [SP, #%#x]", mnemonic,
             reg_name[Rd], offset * 4);

    return 0;
}

static int thumb_add_sp_pc(unsigned short opcode, unsigned address,
                           struct arm_instruction *instruction)
{
    unsigned imm = opcode & 0xff;
    unsigned char Rd = (opcode >> 8) & 0x7;
    unsigned SP = opcode & (1 << 11);
    const char *src_name;

    if (SP) {
        src_name = "SP";
    } else {
        src_name = "PC";
    }

    snprintf(instruction->text, sizeof(instruction->text), "ADD %s, %s, #%#x", reg_name[Rd],
             src_name, imm * 4);

    return 0;
}

static int thumb_adjust_stack(unsigned short opcode, unsigned address,
                              struct arm_instruction *instruction)
{
    unsigned imm = opcode & 0x7f;
    unsigned char opc = opcode & (1 << 7);
    const char *mnemonic;

    if (opc) {
        mnemonic = "SUB";
    } else {
        mnemonic = "ADD";
    }

    snprintf(instruction->text, sizeof(instruction->text), "%s SP, #%#x", mnemonic, imm * 4);

    return 0;
}

static int thumb_breakpoint(unsigned short opcode, unsigned address,
                            struct arm_instruction *instruction)
{
    unsigned imm = opcode & 0xff;

    snprintf(instruction->text, sizeof(instruction->text), "BKPT %#2.2x", imm);

    return 0;
}

static int thumb_load_store_multiple(unsigned short opcode, unsigned address,
                                     struct arm_instruction *instruction)
{
    unsigned reg_list = opcode & 0xff;
    unsigned L = opcode & (1 << 11);
    unsigned R = opcode & (1 << 8);
    unsigned char Rn = (opcode >> 8) & 7;
    char list[40];
    char *list_p;
    const char *mnemonic;
    char ptr_name[7] = "";
    int i;

    /* REVISIT:  in ThumbEE mode, there are no LDM or STM instructions.
     * The STMIA and LDMIA opcodes are used for other instructions.
     */

    if ((opcode & 0xf000) == 0xc000) { /* generic load/store multiple */
        const char *wback = "!";

        if (L) {
            mnemonic = "LDM";
            if (opcode & (1 << Rn))
                wback = "";
        } else {
            mnemonic = "STM";
        }
        snprintf(ptr_name, sizeof ptr_name, "%s%s, ", reg_name[Rn], wback);
    } else {     /* push/pop */
        Rn = 13; /* SP */
        if (L) {
            mnemonic = "POP";
            if (R)
                reg_list |= (1 << 15) /*PC*/;
        } else {
            mnemonic = "PUSH";
            if (R)
                reg_list |= (1 << 14) /*LR*/;
        }
    }

    list_p = list;
    for (i = 0; i <= 15; i++) {
        if (reg_list & (1 << i))
            list_p += snprintf(list_p, (list + 40 - list_p), "%s, ", reg_name[i]);
    }
    if (list_p > list)
        list_p[-2] = '\0';
    else /* invalid op : no registers */
        list[0] = '\0';

    snprintf(instruction->text, sizeof(instruction->text), "%s %s{%s}", mnemonic, ptr_name, list);

    return 0;
}

static int thumb_cond_branch(unsigned short opcode, unsigned address,
                             struct arm_instruction *instruction)
{
    unsigned offset = opcode & 0xff;
    unsigned char cond = (opcode >> 8) & 0xf;
    unsigned target_address;

    if (cond == 0xf) {
        snprintf(instruction->text, sizeof(instruction->text), "SVC %#2.2x", offset);
        return 0;
    } else if (cond == 0xe) {
        snprintf(instruction->text, sizeof(instruction->text), "UNDEFINED INSTRUCTION");
        return 0;
    }

    /* sign extend 8-bit offset */
    if (offset & 0x00000080)
        offset = 0xffffff00 | offset;

    target_address = address + 4 + (offset << 1);

    snprintf(instruction->text, sizeof(instruction->text), "B%s %#8.8x", condition_strings[cond],
             target_address);

    return 0;
}

static int thumb_cb(unsigned short opcode, unsigned address, struct arm_instruction *instruction)
{
    unsigned offset;

    /* added in Thumb2 */
    offset = (opcode >> 3) & 0x1f;
    offset |= (opcode & 0x0200) >> 4;

    snprintf(instruction->text, sizeof(instruction->text), "CB%sZ %s, %#8.8x",
             (opcode & 0x0800) ? "N" : "", reg_name[opcode & 0x7], address + 4 + (offset << 1));

    return 0;
}

static int thumb_extend(unsigned short opcode, unsigned address,
                        struct arm_instruction *instruction)
{
    /* added in ARMv6 */
    snprintf(instruction->text, sizeof(instruction->text), "%cXT%c %s, r%d",
             (opcode & 0x0080) ? 'U' : 'S', (opcode & 0x0040) ? 'B' : 'H', reg_name[opcode & 0x7],
             (opcode >> 3) & 0x7);

    return 0;
}

static int thumb_cps(unsigned short opcode, unsigned address, struct arm_instruction *instruction)
{
    /* added in ARMv6 */
    if ((opcode & 0x0ff0) == 0x0650)
        snprintf(instruction->text, sizeof(instruction->text), "SETEND %s",
                 (opcode & 0x80) ? "BE" : "LE");
    else /* ASSUME (opcode & 0x0fe0) == 0x0660 */
        snprintf(instruction->text, sizeof(instruction->text), "CPSI%c %s%s%s",
                 (opcode & 0x0010) ? 'D' : 'E', (opcode & 0x0004) ? "A" : "",
                 (opcode & 0x0002) ? "I" : "", (opcode & 0x0001) ? "F" : "");

    return 0;
}

static int thumb_byterev(unsigned short opcode, unsigned address,
                         struct arm_instruction *instruction)
{
    const char *suffix;

    /* added in ARMv6 */
    switch ((opcode >> 6) & 3) {
    case 0:
        suffix = "";
        break;
    case 1:
        suffix = "16";
        break;
    default:
        suffix = "SH";
        break;
    }
    snprintf(instruction->text, sizeof(instruction->text), "REV%s %s, %s", suffix,
             reg_name[opcode & 0x7], reg_name[(opcode >> 3) & 0x7]);

    return 0;
}

static int thumb_hint(unsigned short opcode, unsigned address, struct arm_instruction *instruction)
{
    const char *hint;

    switch ((opcode >> 4) & 0x0f) {
    case 0:
        hint = "NOP";
        break;
    case 1:
        hint = "YIELD";
        break;
    case 2:
        hint = "WFE";
        break;
    case 3:
        hint = "WFI";
        break;
    case 4:
        hint = "SEV";
        break;
    default:
        hint = "HINT (UNRECOGNIZED)";
        break;
    }

    snprintf(instruction->text, sizeof(instruction->text), "%s", hint);

    return 0;
}

static int thumb_ifthen(unsigned short opcode, unsigned address,
                        struct arm_instruction *instruction)
{
    unsigned cond = (opcode >> 4) & 0x0f;
    const char *x = "", *y = "", *z = "";

    if (opcode & 0x01)
        z = (opcode & 0x02) ? "T" : "E";
    if (opcode & 0x03)
        y = (opcode & 0x04) ? "T" : "E";
    if (opcode & 0x07)
        x = (opcode & 0x08) ? "T" : "E";

    snprintf(instruction->text, sizeof(instruction->text), "IT%s%s%s %s", x, y, z,
             condition_strings[cond]);

    /* NOTE:  strictly speaking, the next 1-4 instructions should
     * now be displayed with the relevant conditional suffix...
     */

    return 0;
}

static std::string long_b_bl(unsigned opcode, unsigned address)
{
    struct arm_instruction instruction {};
    unsigned offset;
    unsigned b21 = 1 << 21;
    unsigned b22 = 1 << 22;

    /* instead of combining two smaller 16-bit branch instructions,
     * Thumb2 uses only one larger 32-bit instruction.
     */
    offset = opcode & 0x7ff;
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

    snprintf(instruction.text, sizeof(instruction.text), "%s %#8.8x",
             (opcode & (1 << 14)) ? "bl" : "B.W", address);
    return instruction.text;
}

static const char *special_name(int number)
{
    const char *special = "(RESERVED)";

    switch (number) {
    case 0:
        special = "APSR";
        break;
    case 1:
        special = "IAPSR";
        break;
    case 2:
        special = "EAPSR";
        break;
    case 3:
        special = "PSR";
        break;
    case 5:
        special = "IPSR";
        break;
    case 6:
        special = "EPSR";
        break;
    case 7:
        special = "IEPSR";
        break;
    case 8:
        special = "MSP";
        break;
    case 9:
        special = "PSP";
        break;
    case 10:
        special = "MSPLIM";
        break;
    case 11:
        special = "PSPLIM";
        break;
    case 16:
        special = "PRIMASK";
        break;
    case 17:
        special = "BASEPRI";
        break;
    case 18:
        special = "BASEPRI_MAX";
        break;
    case 19:
        special = "FAULTMASK";
        break;
    case 20:
        special = "CONTROL";
        break;
    case 0x88:
        special = "MSP_NS";
        break;
    case 0x89:
        special = "PSP_NS";
        break;
    case 0x8a:
        special = "MSPLIM_NS";
        break;
    case 0x8b:
        special = "PSPLIM_NS";
        break;
    case 0x90:
        special = "PRIMASK_NS";
        break;
    case 0x91:
        special = "BASEPRI_NS";
        break;
    case 0x93:
        special = "FAULTMASK_NS";
        break;
    case 0x94:
        special = "CONTROL_NS";
        break;
    case 0x98:
        special = "SP_NS";
        break;
    }
    return special;
}

static std::string long_misc(unsigned opcode, unsigned address)
{
    struct arm_instruction instruction {};
    unsigned option = opcode & 0x0f;
    const char *mnemonic;

    switch ((opcode >> 4) & 0x0f) {
    case 4:
        mnemonic = "dsb";
        break;
    case 5:
        mnemonic = "dmb";
        break;
    case 6:
        mnemonic = "isb";
        break;
    default:
        return "";
    }

    if (option)
        snprintf(instruction.text, sizeof(instruction.text), "%s #%u", mnemonic, option);
    else
        strcpy(instruction.text, mnemonic);

    return instruction.text;
}

//
// ARMv7-M: A5.3.4 Branches and miscellaneous control
//
static std::string long_b_misc(unsigned opcode, unsigned address)
{
    struct arm_instruction instruction {};

    /* permanently undefined */
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
        snprintf(instruction.text, sizeof(instruction.text), "msr %s, %s",
                 special_name(opcode & 0xff), reg_name[(opcode >> 16) & 0x0f]);
        return instruction.text;
    case 0x3b:
        return long_misc(opcode, address);
    case 0x3e:
    case 0x3f:
        snprintf(instruction.text, sizeof(instruction.text), "mrs %s, %s",
                 reg_name[(opcode >> 8) & 0x0f], special_name(opcode & 0xff));
        return instruction.text;
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
    struct arm_instruction instruction {};

    if ((opcode & 0xe000) == 0x0000) {
        /* add/substract register or immediate */
        if ((opcode & 0x1800) == 0x1800)
            thumb_add_sub(opcode, address, &instruction);
        /* shift by immediate */
        else
            thumb_shift_imm(opcode, address, &instruction);
    }

    /* Add/substract/compare/move immediate */
    else if ((opcode & 0xe000) == 0x2000) {
        thumb_data_proc_imm(opcode, address, &instruction);
    }

    /* Data processing instructions */
    else if ((opcode & 0xf800) == 0x4000) {
        thumb_data_proc(opcode, address, &instruction);
    }

    /* Load from literal pool */
    else if ((opcode & 0xf800) == 0x4800) {
        thumb_load_literal(opcode, address, &instruction);
    }

    /* Load/Store register offset */
    else if ((opcode & 0xf000) == 0x5000) {
        thumb_load_store_reg(opcode, address, &instruction);
    }

    /* Load/Store immediate offset */
    else if (((opcode & 0xe000) == 0x6000) || ((opcode & 0xf000) == 0x8000)) {
        thumb_load_store_imm(opcode, address, &instruction);
    }

    /* Load/Store from/to stack */
    else if ((opcode & 0xf000) == 0x9000) {
        thumb_load_store_stack(opcode, address, &instruction);
    }

    /* Add to SP/PC */
    else if ((opcode & 0xf000) == 0xa000) {
        thumb_add_sp_pc(opcode, address, &instruction);
    }

    /* Misc */
    else if ((opcode & 0xf000) == 0xb000) {
        switch ((opcode >> 8) & 0x0f) {
        case 0x0:
            thumb_adjust_stack(opcode, address, &instruction);
            break;
        case 0x1:
        case 0x3:
        case 0x9:
        case 0xb:
            thumb_cb(opcode, address, &instruction);
            break;
        case 0x2:
            thumb_extend(opcode, address, &instruction);
            break;
        case 0x4:
        case 0x5:
        case 0xc:
        case 0xd:
            thumb_load_store_multiple(opcode, address, &instruction);
            break;
        case 0x6:
            thumb_cps(opcode, address, &instruction);
            break;
        case 0xa:
            if ((opcode & 0x00c0) != 0x0080)
                thumb_byterev(opcode, address, &instruction);
            break;
        case 0xe:
            thumb_breakpoint(opcode, address, &instruction);
            break;
        case 0xf:
            if (opcode & 0x000f)
                thumb_ifthen(opcode, address, &instruction);
            else
                thumb_hint(opcode, address, &instruction);
            break;
        default:
            // Undefined instruction.
            return "";
        }
    }

    /* Load/Store multiple */
    else if ((opcode & 0xf000) == 0xc000) {
        thumb_load_store_multiple(opcode, address, &instruction);
    }

    /* Conditional branch + SWI */
    else if ((opcode & 0xf000) == 0xd000) {
        thumb_cond_branch(opcode, address, &instruction);
    }

    else if ((opcode & 0xe000) == 0xe000) {
        /* Undefined instructions */
        if ((opcode & 0xf801) == 0xe801) {
            // Undefined instruction.
            return "";
        } else {
            /* Branch to offset */
            thumb_b_bl_blx(opcode, address, &instruction);
        }
    } else {
        // Thumb: should never reach this point.
        return "";
    }
    return instruction.text;
}

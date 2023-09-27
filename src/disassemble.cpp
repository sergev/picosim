//
// ARM Disassembler
//
// Copyright (C) 2006 by Dominic Rath
// Dominic.Rath@gmx.de
//
// Copyright (C) 2009 by David Brownell
// Copyright (C) 2023 Serge Vakulenko
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the
// Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
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
    "EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC",
    "HI", "LS", "GE", "LT", "GT", "LE", "",   "NV",
};

//
// Register names
//
static const char *reg_name[16] = {
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
    "r8", "r9", "sl", "fp", "ip", "r13", "lr", "r15",
};

/* make up for C's missing ROR */
static unsigned ror(unsigned value, int places)
{
    return (value >> places) | (value << (32 - places));
}

static int evaluate_b_bl_blx_thumb(unsigned short opcode, unsigned address,
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

static int evaluate_add_sub_thumb(unsigned short opcode, unsigned address,
                                  struct arm_instruction *instruction)
{
    unsigned char Rd = (opcode >> 0) & 0x7;
    unsigned char Rn = (opcode >> 3) & 0x7;
    unsigned char Rm_imm = (opcode >> 6) & 0x7;
    unsigned opc = opcode & (1 << 9);
    unsigned reg_imm = opcode & (1 << 10);
    const char *mnemonic;

    if (opc) {
        mnemonic = "SUBS";
    } else {
        /* REVISIT:  if reg_imm == 0, display as "MOVS" */
        mnemonic = "ADDS";
    }

    if (reg_imm) {
        snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s, #%d",
                 mnemonic, reg_name[Rd], reg_name[Rn], Rm_imm);
    } else {
        snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s, %s",
                 mnemonic, reg_name[Rd], reg_name[Rn], reg_name[Rm_imm]);
    }

    return 0;
}

static int evaluate_shift_imm_thumb(unsigned short opcode, unsigned address,
                                    struct arm_instruction *instruction)
{
    unsigned char Rd = (opcode >> 0) & 0x7;
    unsigned char Rm = (opcode >> 3) & 0x7;
    unsigned char imm = (opcode >> 6) & 0x1f;
    unsigned char opc = (opcode >> 11) & 0x3;
    const char *mnemonic = NULL;

    switch (opc) {
    case 0:
        mnemonic = "LSLS";
        break;
    case 1:
        mnemonic = "LSRS";
        break;
    case 2:
        mnemonic = "ASRS";
        break;
    }

    if ((imm == 0) && (opc != 0))
        imm = 32;

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s, #%#2.2x",
             mnemonic, reg_name[Rd], reg_name[Rm], imm);

    return 0;
}

static int evaluate_data_proc_imm_thumb(unsigned short opcode, unsigned address,
                                        struct arm_instruction *instruction)
{
    unsigned char imm = opcode & 0xff;
    unsigned char Rd = (opcode >> 8) & 0x7;
    unsigned opc = (opcode >> 11) & 0x3;
    const char *mnemonic = NULL;

    switch (opc) {
    case 0:
        mnemonic = "MOVS";
        break;
    case 1:
        mnemonic = "CMP";
        break;
    case 2:
        mnemonic = "ADDS";
        break;
    case 3:
        mnemonic = "SUBS";
        break;
    }

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, #%#2.2x",
             mnemonic, reg_name[Rd], imm);

    return 0;
}

static int evaluate_data_proc_thumb(unsigned short opcode, unsigned address,
                                    struct arm_instruction *instruction)
{
    unsigned char high_reg, op, Rm, Rd, H1, H2;
    const char *mnemonic = NULL;
    int nop = 0;

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
            mnemonic = "ADD";
            break;
        case 0x1:
            mnemonic = "CMP";
            break;
        case 0x2:
            mnemonic = "MOV";
            if (Rd == Rm)
                nop = 1;
            break;
        case 0x3:
            if ((opcode & 0x7) == 0x0) {
                if (H1) {
                    snprintf(instruction->text, sizeof(instruction->text),
                             "BLX %s", reg_name[Rm]);
                } else {
                    snprintf(instruction->text, sizeof(instruction->text),
                             "BX %s", reg_name[Rm]);
                }
            } else {
                snprintf(instruction->text, sizeof(instruction->text),
                         "UNDEFINED INSTRUCTION");
            }
            return 0;
            break;
        }
    } else {
        switch (op) {
        case 0x0:
            mnemonic = "ANDS";
            break;
        case 0x1:
            mnemonic = "EORS";
            break;
        case 0x2:
            mnemonic = "LSLS";
            break;
        case 0x3:
            mnemonic = "LSRS";
            break;
        case 0x4:
            mnemonic = "ASRS";
            break;
        case 0x5:
            mnemonic = "ADCS";
            break;
        case 0x6:
            mnemonic = "SBCS";
            break;
        case 0x7:
            mnemonic = "RORS";
            break;
        case 0x8:
            mnemonic = "TST";
            break;
        case 0x9:
            mnemonic = "RSBS";
            break;
        case 0xA:
            mnemonic = "CMP";
            break;
        case 0xB:
            mnemonic = "CMN";
            break;
        case 0xC:
            mnemonic = "ORRS";
            break;
        case 0xD:
            mnemonic = "MULS";
            break;
        case 0xE:
            mnemonic = "BICS";
            break;
        case 0xF:
            mnemonic = "MVNS";
            break;
        }
    }

    if (nop)
        snprintf(instruction->text, sizeof(instruction->text),
                 "NOP ; (%s %s, %s)", mnemonic, reg_name[Rd], reg_name[Rm]);
    else
        snprintf(instruction->text, sizeof(instruction->text), "%s %s, %s",
                 mnemonic, reg_name[Rd], reg_name[Rm]);

    return 0;
}

/* PC-relative data addressing is word-aligned even with Thumb */
static inline unsigned thumb_alignpc4(unsigned addr)
{
    return (addr + 4) & ~3;
}

static int evaluate_load_literal_thumb(unsigned short opcode, unsigned address,
                                       struct arm_instruction *instruction)
{
    unsigned immediate;
    unsigned char Rd = (opcode >> 8) & 0x7;

    immediate = opcode & 0x000000ff;
    immediate *= 4;

    snprintf(instruction->text, sizeof(instruction->text),
             "LDR %s, [pc, #%#x] ; %#8.8x",
             reg_name[Rd], immediate, thumb_alignpc4(address) + immediate);

    return 0;
}

static int evaluate_load_store_reg_thumb(unsigned short opcode, unsigned address,
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

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, [%s, %s]",
             mnemonic, reg_name[Rd], reg_name[Rn], reg_name[Rm]);

    return 0;
}

static int evaluate_load_store_imm_thumb(unsigned short opcode, unsigned address,
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

    snprintf(instruction->text, sizeof(instruction->text), "%s%c %s, [%s, #%#x]",
             mnemonic, suffix, reg_name[Rd], reg_name[Rn], offset << shift);

    return 0;
}

static int evaluate_load_store_stack_thumb(unsigned short opcode, unsigned address,
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

    snprintf(instruction->text, sizeof(instruction->text), "%s %s, [SP, #%#x]",
             mnemonic, reg_name[Rd], offset * 4);

    return 0;
}

static int evaluate_add_sp_pc_thumb(unsigned short opcode, unsigned address,
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

static int evaluate_adjust_stack_thumb(unsigned short opcode, unsigned address,
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

    snprintf(instruction->text, sizeof(instruction->text), "%s SP, #%#x",
             mnemonic, imm * 4);

    return 0;
}

static int evaluate_breakpoint_thumb(unsigned short opcode, unsigned address,
                                     struct arm_instruction *instruction)
{
    unsigned imm = opcode & 0xff;

    snprintf(instruction->text, sizeof(instruction->text), "BKPT %#2.2x", imm);

    return 0;
}

static int evaluate_load_store_multiple_thumb(unsigned short opcode, unsigned address,
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

    snprintf(instruction->text, sizeof(instruction->text), "%s %s{%s}", mnemonic,
             ptr_name, list);

    return 0;
}

static int evaluate_cond_branch_thumb(unsigned short opcode, unsigned address,
                                      struct arm_instruction *instruction)
{
    unsigned offset = opcode & 0xff;
    unsigned char cond = (opcode >> 8) & 0xf;
    unsigned target_address;

    if (cond == 0xf) {
        snprintf(instruction->text, sizeof(instruction->text), "SVC %#2.2x",
                 offset);
        return 0;
    } else if (cond == 0xe) {
        snprintf(instruction->text, sizeof(instruction->text), "UNDEFINED INSTRUCTION");
        return 0;
    }

    /* sign extend 8-bit offset */
    if (offset & 0x00000080)
        offset = 0xffffff00 | offset;

    target_address = address + 4 + (offset << 1);

    snprintf(instruction->text, sizeof(instruction->text), "B%s %#8.8x",
             condition_strings[cond], target_address);

    return 0;
}

static int evaluate_cb_thumb(unsigned short opcode, unsigned address,
                             struct arm_instruction *instruction)
{
    unsigned offset;

    /* added in Thumb2 */
    offset = (opcode >> 3) & 0x1f;
    offset |= (opcode & 0x0200) >> 4;

    snprintf(instruction->text, sizeof(instruction->text), "CB%sZ %s, %#8.8x",
             (opcode & 0x0800) ? "N" : "", reg_name[opcode & 0x7], address + 4 + (offset << 1));

    return 0;
}

static int evaluate_extend_thumb(unsigned short opcode, unsigned address,
                                 struct arm_instruction *instruction)
{
    /* added in ARMv6 */
    snprintf(instruction->text, sizeof(instruction->text), "%cXT%c %s, r%d",
             (opcode & 0x0080) ? 'U' : 'S', (opcode & 0x0040) ? 'B' : 'H', reg_name[opcode & 0x7],
             (opcode >> 3) & 0x7);

    return 0;
}

static int evaluate_cps_thumb(unsigned short opcode, unsigned address,
                              struct arm_instruction *instruction)
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

static int evaluate_byterev_thumb(unsigned short opcode, unsigned address,
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
    snprintf(instruction->text, sizeof(instruction->text), "REV%s %s, %s",
             suffix, reg_name[opcode & 0x7], reg_name[(opcode >> 3) & 0x7]);

    return 0;
}

static int evaluate_hint_thumb(unsigned short opcode, unsigned address,
                               struct arm_instruction *instruction)
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

static int evaluate_ifthen_thumb(unsigned short opcode, unsigned address,
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

static std::string evaluate_opcode16(unsigned short opcode, unsigned address)
{
    struct arm_instruction instruction{};

    if ((opcode & 0xe000) == 0x0000) {
        /* add/substract register or immediate */
        if ((opcode & 0x1800) == 0x1800)
            evaluate_add_sub_thumb(opcode, address, &instruction);
        /* shift by immediate */
        else
            evaluate_shift_imm_thumb(opcode, address, &instruction);
    }

    /* Add/substract/compare/move immediate */
    else if ((opcode & 0xe000) == 0x2000) {
        evaluate_data_proc_imm_thumb(opcode, address, &instruction);
    }

    /* Data processing instructions */
    else if ((opcode & 0xf800) == 0x4000) {
        evaluate_data_proc_thumb(opcode, address, &instruction);
    }

    /* Load from literal pool */
    else if ((opcode & 0xf800) == 0x4800) {
        evaluate_load_literal_thumb(opcode, address, &instruction);
    }

    /* Load/Store register offset */
    else if ((opcode & 0xf000) == 0x5000) {
        evaluate_load_store_reg_thumb(opcode, address, &instruction);
    }

    /* Load/Store immediate offset */
    else if (((opcode & 0xe000) == 0x6000) || ((opcode & 0xf000) == 0x8000)) {
        evaluate_load_store_imm_thumb(opcode, address, &instruction);
    }

    /* Load/Store from/to stack */
    else if ((opcode & 0xf000) == 0x9000) {
        evaluate_load_store_stack_thumb(opcode, address, &instruction);
    }

    /* Add to SP/PC */
    else if ((opcode & 0xf000) == 0xa000) {
        evaluate_add_sp_pc_thumb(opcode, address, &instruction);
    }

    /* Misc */
    else if ((opcode & 0xf000) == 0xb000) {
        switch ((opcode >> 8) & 0x0f) {
        case 0x0:
            evaluate_adjust_stack_thumb(opcode, address, &instruction);
            break;
        case 0x1:
        case 0x3:
        case 0x9:
        case 0xb:
            evaluate_cb_thumb(opcode, address, &instruction);
            break;
        case 0x2:
            evaluate_extend_thumb(opcode, address, &instruction);
            break;
        case 0x4:
        case 0x5:
        case 0xc:
        case 0xd:
            evaluate_load_store_multiple_thumb(opcode, address, &instruction);
            break;
        case 0x6:
            evaluate_cps_thumb(opcode, address, &instruction);
            break;
        case 0xa:
            if ((opcode & 0x00c0) != 0x0080)
                evaluate_byterev_thumb(opcode, address, &instruction);
            break;
        case 0xe:
            evaluate_breakpoint_thumb(opcode, address, &instruction);
            break;
        case 0xf:
            if (opcode & 0x000f)
                evaluate_ifthen_thumb(opcode, address, &instruction);
            else
                evaluate_hint_thumb(opcode, address, &instruction);
            break;
        default:
            snprintf(instruction.text, sizeof(instruction.text), "UNDEFINED INSTRUCTION");
        }
    }

    /* Load/Store multiple */
    else if ((opcode & 0xf000) == 0xc000) {
        evaluate_load_store_multiple_thumb(opcode, address, &instruction);
    }

    /* Conditional branch + SWI */
    else if ((opcode & 0xf000) == 0xd000) {
        evaluate_cond_branch_thumb(opcode, address, &instruction);
    }

    else if ((opcode & 0xe000) == 0xe000) {
        /* Undefined instructions */
        if ((opcode & 0xf801) == 0xe801) {
            strcpy(instruction.text, "UNDEFINED INSTRUCTION");
        } else {
            /* Branch to offset */
            evaluate_b_bl_blx_thumb(opcode, address, &instruction);
        }
    } else {
        // Thumb: should never reach this point.
        return "???";
    }
    return instruction.text;
}

static int t2ev_b_bl(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                     char *cp, unsigned cpsize)
{
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

    snprintf(cp, cpsize, "%s %#8.8x", (opcode & (1 << 14)) ? "bl" : "B.W", address);

    return 0;
}

static int t2ev_cond_b(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                       char *cp, unsigned cpsize)
{
    unsigned offset;
    unsigned b17 = 1 << 17;
    unsigned b18 = 1 << 18;
    unsigned cond = (opcode >> 22) & 0x0f;

    offset = opcode & 0x7ff;
    offset |= (opcode & 0x003f0000) >> 5;
    if (opcode & (1 << 26)) {
        offset |= 0xffffU << 19;
        if ((opcode & (1 << 11)) == 0)
            b17 = 0;
        if ((opcode & (1 << 13)) == 0)
            b18 = 0;
    } else {
        if (opcode & (1 << 11))
            b17 = 0;
        if (opcode & (1 << 13))
            b18 = 0;
    }
    offset |= b17;
    offset |= b18;

    address += 4;
    address += offset << 1;

    snprintf(cp, cpsize, "B%s.W %#8.8x", condition_strings[cond], address);

    return 0;
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

static int t2ev_hint(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                     char *cp, unsigned cpsize)
{
    const char *mnemonic;

    if (opcode & 0x0700) {
        strcpy(cp, "UNDEFINED");
        return 0;
    }

    if (opcode & 0x00f0) {
        snprintf(cp, cpsize, "DBG #%d", (int)opcode & 0xf);
        return 0;
    }

    switch (opcode & 0x0f) {
    case 0:
        mnemonic = "NOP.W";
        break;
    case 1:
        mnemonic = "YIELD.W";
        break;
    case 2:
        mnemonic = "WFE.W";
        break;
    case 3:
        mnemonic = "WFI.W";
        break;
    case 4:
        mnemonic = "SEV.W";
        break;
    default:
        mnemonic = "HINT.W (UNRECOGNIZED)";
        break;
    }
    strcpy(cp, mnemonic);
    return 0;
}

static int t2ev_misc(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                     char *cp, unsigned cpsize)
{
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
        return -1;
    }

    if (option)
        snprintf(cp, cpsize, "%s #%u", mnemonic, option);
    else
        strcpy(cp, mnemonic);

    return 0;
}

static int t2ev_b_misc(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                       char *cp, unsigned cpsize)
{
    /* permanently undefined */
    if ((opcode & 0x07f07000) == 0x07f02000) {
        strcpy(cp, "UNDEFINED");
        return 0;
    }

    switch ((opcode >> 12) & 0x5) {
    case 0x1:
    case 0x5:
        return t2ev_b_bl(opcode, address, instruction, cp, cpsize);
    case 0x4:
        goto undef;
    case 0:
        if (((opcode >> 23) & 0x07) != 0x07)
            return t2ev_cond_b(opcode, address, instruction, cp, cpsize);
        if (opcode & (1 << 26))
            goto undef;
        break;
    }

    switch ((opcode >> 20) & 0x7f) {
    case 0x38:
    case 0x39:
        snprintf(cp, cpsize, "msr %s, %s", special_name(opcode & 0xff), reg_name[(opcode >> 16) & 0x0f]);
        return 0;
    case 0x3a:
        return t2ev_hint(opcode, address, instruction, cp, cpsize);
    case 0x3b:
        return t2ev_misc(opcode, address, instruction, cp, cpsize);
    case 0x3c:
        snprintf(cp, cpsize, "BXJ %s", reg_name[(opcode >> 16) & 0x0f]);
        return 0;
    case 0x3e:
    case 0x3f:
        snprintf(cp, cpsize, "mrs %s, %s", reg_name[(opcode >> 8) & 0x0f], special_name(opcode & 0xff));
        return 0;
    }

undef:
    return -1;
}

static int t2ev_data_mod_immed(unsigned opcode, unsigned address,
                               struct arm_instruction *instruction, char *cp, unsigned cpsize)
{
    const char *mnemonic = NULL;
    int rn = (opcode >> 16) & 0xf;
    int rd = (opcode >> 8) & 0xf;
    unsigned immed = opcode & 0xff;
    unsigned func;
    int one = 0;
    const char *suffix = "";
    const char *suffix2 = "";

    /* ARMv7-M: A5.3.2 Modified immediate constants */
    func = (opcode >> 11) & 0x0e;
    if (immed & 0x80)
        func |= 1;
    if (opcode & (1 << 26))
        func |= 0x10;

    /* "Modified" immediates */
    switch (func >> 1) {
    case 0:
        break;
    case 2:
        immed <<= 8;
        /* FALLTHROUGH */
    case 1:
        immed += immed << 16;
        break;
    case 3:
        immed += immed << 8;
        immed += immed << 16;
        break;
    default:
        immed |= 0x80;
        immed = ror(immed, func);
    }

    if (opcode & (1 << 20))
        suffix = "S";

    switch ((opcode >> 21) & 0xf) {
    case 0:
        if (rd == 0xf) {
            mnemonic = "TST";
            one = 1;
            suffix = "";
            rd = rn;
        } else {
            mnemonic = "AND";
        }
        break;
    case 1:
        mnemonic = "BIC";
        break;
    case 2:
        if (rn == 0xf) {
            mnemonic = "MOV";
            one = 1;
            suffix2 = ".W";
        } else {
            mnemonic = "ORR";
        }
        break;
    case 3:
        if (rn == 0xf) {
            mnemonic = "MVN";
            one = 1;
        } else {
            mnemonic = "ORN";
        }
        break;
    case 4:
        if (rd == 0xf) {
            mnemonic = "TEQ";
            one = 1;
            suffix = "";
            rd = rn;
        } else {
            mnemonic = "EOR";
        }
        break;
    case 8:
        if (rd == 0xf) {
            mnemonic = "CMN";
            one = 1;
            suffix = "";
            rd = rn;
        } else {
            mnemonic = "ADD";
            suffix2 = ".W";
        }
        break;
    case 10:
        mnemonic = "ADC";
        suffix2 = ".W";
        break;
    case 11:
        mnemonic = "SBC";
        break;
    case 13:
        if (rd == 0xf) {
            mnemonic = "CMP";
            one = 1;
            suffix = "";
            rd = rn;
        } else {
            mnemonic = "SUB";
        }
        suffix2 = ".W";
        break;
    case 14:
        mnemonic = "RSB";
        suffix2 = ".W";
        break;
    default:
        return -1;
    }

    if (one)
        snprintf(cp, cpsize, "%s%s %s, #%d ; %#8.8x", mnemonic, suffix2, reg_name[rd], immed, immed);
    else
        snprintf(cp, cpsize, "%s%s%s %s, %s, #%d ; %#8.8x", mnemonic, suffix, suffix2, reg_name[rd], reg_name[rn], immed,
                immed);

    return 0;
}

static int t2ev_data_immed(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                           char *cp, unsigned cpsize)
{
    const char *mnemonic = NULL;
    int rn = (opcode >> 16) & 0xf;
    int rd = (opcode >> 8) & 0xf;
    unsigned immed;
    int add = 0;
    int is_signed = 0;

    immed = (opcode & 0x0ff) | ((opcode & 0x7000) >> 4);
    if (opcode & (1 << 26))
        immed |= (1 << 11);

    switch ((opcode >> 20) & 0x1f) {
    case 0:
        if (rn == 0xf) {
            add = 1;
            goto do_adr;
        }
        mnemonic = "ADDW";
        break;
    case 4:
        immed |= (opcode >> 4) & 0xf000;
        snprintf(cp, cpsize, "MOVW %s, #%d ; %#3.3x", reg_name[rd], immed, immed);
        return 0;
    case 0x0a:
        if (rn == 0xf)
            goto do_adr;
        mnemonic = "SUBW";
        break;
    case 0x0c:
        /* move constant to top 16 bits of register */
        immed |= (opcode >> 4) & 0xf000;
        snprintf(cp, cpsize, "MOVT %s, #%d ; %#4.4x", reg_name[rd], immed, immed);
        return 0;
    case 0x10:
    case 0x12:
        is_signed = 1;
    case 0x18:
    case 0x1a:
        /* signed/unsigned saturated add */
        immed = (opcode >> 6) & 0x03;
        immed |= (opcode >> 10) & 0x1c;
        snprintf(cp, cpsize, "%sSAT %s, #%d, %s, %s #%d ", is_signed ? "S" : "U", reg_name[rd],
                (int)(opcode & 0x1f) + is_signed, reg_name[rn], (opcode & (1 << 21)) ? "ASR" : "LSL",
                immed ? immed : 32);
        return 0;
    case 0x14:
        is_signed = 1;
        /* FALLTHROUGH */
    case 0x1c:
        /* signed/unsigned bitfield extract */
        immed = (opcode >> 6) & 0x03;
        immed |= (opcode >> 10) & 0x1c;
        snprintf(cp, cpsize, "%sBFX %s, %s, #%d, #%d ", is_signed ? "S" : "U", reg_name[rd], reg_name[rn], immed,
                (int)(opcode & 0x1f) + 1);
        return 0;
    case 0x16:
        immed = (opcode >> 6) & 0x03;
        immed |= (opcode >> 10) & 0x1c;
        if (rn == 0xf) /* bitfield clear */
            snprintf(cp, cpsize, "BFC %s, #%d, #%d ", reg_name[rd], immed, (int)(opcode & 0x1f) + 1 - immed);
        else /* bitfield insert */
            snprintf(cp, cpsize, "BFI %s, %s, #%d, #%d ", reg_name[rd], reg_name[rn], immed,
                    (int)(opcode & 0x1f) + 1 - immed);
        return 0;
    default:
        return -1;
    }

    snprintf(cp, cpsize, "%s %s, %s, #%d ; %#3.3x", mnemonic, reg_name[rd], reg_name[rn], immed, immed);
    return 0;

do_adr:
    address = thumb_alignpc4(address);
    if (add)
        address += immed;
    else
        address -= immed;

    /* REVISIT "ADD/SUB Rd, PC, #const ; 0x..." might be better;
     * not hiding the pc-relative stuff will sometimes be useful.
     */
    snprintf(cp, cpsize, "ADR.W %s, %#8.8x", reg_name[rd], address);
    return 0;
}

static int t2ev_store_single(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                             char *cp, unsigned cpsize)
{
    unsigned op = (opcode >> 20) & 0xf;
    const char *size = "";
    const char *suffix = "";
    const char *p1 = "";
    const char *p2 = "]";
    unsigned immed;
    unsigned rn = (opcode >> 16) & 0x0f;
    unsigned rt = (opcode >> 12) & 0x0f;

    if (rn == 0xf)
        return -1;

    if (opcode & 0x0800)
        op |= 1;
    switch (op) {
    /* byte */
    case 0x8:
    case 0x9:
        size = "B";
        goto imm12;
    case 0x1:
        size = "B";
        goto imm8;
    case 0x0:
        size = "B";
        break;
    /* halfword */
    case 0xa:
    case 0xb:
        size = "H";
        goto imm12;
    case 0x3:
        size = "H";
        goto imm8;
    case 0x2:
        size = "H";
        break;
    /* word */
    case 0xc:
    case 0xd:
        goto imm12;
    case 0x5:
        goto imm8;
    case 0x4:
        break;
    /* error */
    default:
        return -1;
    }

    snprintf(cp, cpsize, "STR%s.W %s, [%s, %s, LSL #%d]", size, reg_name[rt], reg_name[rn], reg_name[opcode & 0x0f],
            (int)(opcode >> 4) & 0x03);
    return 0;

imm12:
    immed = opcode & 0x0fff;
    snprintf(cp, cpsize, "STR%s.W %s, [%s, #%u] ; %#3.3x", size, reg_name[rt], reg_name[rn], immed, immed);
    return 0;

imm8:
    immed = opcode & 0x00ff;

    switch (opcode & 0x700) {
    case 0x600:
        suffix = "T";
        break;
    case 0x000:
    case 0x200:
        return -1;
    }

    /* two indexed modes will write back rn */
    if (opcode & 0x100) {
        if (opcode & 0x400) /* pre-indexed */
            p2 = "]!";
        else { /* post-indexed */
            p1 = "]";
            p2 = "";
        }
    }

    snprintf(cp, cpsize, "STR%s%s %s, [%s%s, #%s%u%s ; %#2.2x", size, suffix, reg_name[rt], reg_name[rn], p1,
            (opcode & 0x200) ? "" : "-", immed, p2, immed);
    return 0;
}

static int t2ev_mul32(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                      char *cp, unsigned cpsize)
{
    int ra = (opcode >> 12) & 0xf;

    switch (opcode & 0x007000f0) {
    case 0:
        if (ra == 0xf)
            snprintf(cp, cpsize, "MUL %s, %s, %s", reg_name[(opcode >> 8) & 0xf], reg_name[(opcode >> 16) & 0xf],
                    reg_name[(opcode >> 0) & 0xf]);
        else
            snprintf(cp, cpsize, "MLA %s, %s, %s, %s", reg_name[(opcode >> 8) & 0xf],
                    reg_name[(opcode >> 16) & 0xf], reg_name[(opcode >> 0) & 0xf], reg_name[ra]);
        break;
    case 0x10:
        snprintf(cp, cpsize, "MLS %s, %s, %s, %s", reg_name[(opcode >> 8) & 0xf], reg_name[(opcode >> 16) & 0xf],
                reg_name[(opcode >> 0) & 0xf], reg_name[ra]);
        break;
    default:
        return -1;
    }
    return 0;
}

static int t2ev_mul64_div(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                          char *cp, unsigned cpsize)
{
    int op = (opcode >> 4) & 0xf;
    const char *infix = "MUL";

    op += (opcode >> 16) & 0x70;
    switch (op) {
    case 0x40:
    case 0x60:
        infix = "MLA";
        /* FALLTHROUGH */
    case 0:
    case 0x20:
        snprintf(cp, cpsize, "%c%sL %s, %s, %s, %s", (op & 0x20) ? 'U' : 'S', infix,
                reg_name[(opcode >> 12) & 0xf], reg_name[(opcode >> 8) & 0xf], reg_name[(opcode >> 16) & 0xf],
                reg_name[(opcode >> 0) & 0xf]);
        break;
    case 0x1f:
    case 0x3f:
        snprintf(cp, cpsize, "%cDIV %s, %s, %s", (op & 0x20) ? 'U' : 'S', reg_name[(opcode >> 8) & 0xf],
                reg_name[(opcode >> 16) & 0xf], reg_name[(opcode >> 0) & 0xf]);
        break;
    default:
        return -1;
    }

    return 0;
}

static int t2ev_ldm_stm(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                        char *cp, unsigned cpsize)
{
    int rn = (opcode >> 16) & 0xf;
    int op = (opcode >> 22) & 0x6;
    int t = (opcode >> 21) & 1;
    unsigned registers = opcode & 0xffff;
    const char *mode = "";

    if (opcode & (1 << 20))
        op |= 1;

    switch (op) {
    case 0:
        mode = "DB";
        /* FALL THROUGH */
    case 6:
        snprintf(cp, cpsize, "SRS%s sp%s, #%d", mode, t ? "!" : "", (unsigned)(opcode & 0x1f));
        return 0;
    case 1:
        mode = "DB";
        /* FALL THROUGH */
    case 7:
        snprintf(cp, cpsize, "RFE%s %s%s", mode, reg_name[(opcode >> 16) & 0xf], t ? "!" : "");
        return 0;
    case 2:
        snprintf(cp, cpsize, "STM.W %s%s, ", reg_name[rn], t ? "!" : "");
        break;
    case 3:
        if (rn == 13 && t)
            snprintf(cp, cpsize, "POP.W ");
        else
            snprintf(cp, cpsize, "LDM.W %s%s, ", reg_name[rn], t ? "!" : "");
        break;
    case 4:
        if (rn == 13 && t)
            snprintf(cp, cpsize, "PUSH.W ");
        else
            snprintf(cp, cpsize, "STMDB %s%s, ", reg_name[rn], t ? "!" : "");
        break;
    case 5:
        snprintf(cp, cpsize, "LDMDB.W %s%s, ", reg_name[rn], t ? "!" : "");
        break;
    default:
        return -1;
    }

    cp = strchr(cp, 0);
    *cp++ = '{';
    for (t = 0; registers; t++, registers >>= 1) {
        if ((registers & 1) == 0)
            continue;
        registers &= ~1;
        snprintf(cp, cpsize, "%s%s", reg_name[t], registers ? ", " : "");
        cp = strchr(cp, 0);
    }
    *cp++ = '}';
    *cp++ = 0;

    return 0;
}

/* load/store dual or exclusive, table branch */
static int t2ev_ldrex_strex(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                            char *cp, unsigned cpsize)
{
    unsigned op1op2 = (opcode >> 20) & 0x3;
    unsigned op3 = (opcode >> 4) & 0xf;
    const char *mnemonic;
    unsigned rn = (opcode >> 16) & 0xf;
    unsigned rt = (opcode >> 12) & 0xf;
    unsigned rd = (opcode >> 8) & 0xf;
    unsigned imm = opcode & 0xff;
    const char *p1 = "";
    const char *p2 = "]";

    op1op2 |= (opcode >> 21) & 0xc;
    switch (op1op2) {
    case 0:
        mnemonic = "STREX";
        goto strex;
    case 1:
        mnemonic = "LDREX";
        goto ldrex;
    case 2:
    case 6:
    case 8:
    case 10:
    case 12:
    case 14:
        mnemonic = "STRD";
        goto immediate;
    case 3:
    case 7:
    case 9:
    case 11:
    case 13:
    case 15:
        mnemonic = "LDRD";
        if (rn == 15)
            goto literal;
        else
            goto immediate;
    case 4:
        switch (op3) {
        case 4:
            mnemonic = "STREXB";
            break;
        case 5:
            mnemonic = "STREXH";
            break;
        default:
            return -1;
        }
        rd = opcode & 0xf;
        imm = 0;
        goto strex;
    case 5:
        switch (op3) {
        case 0:
            snprintf(cp, cpsize, "TBB [%s, %s]", reg_name[rn], reg_name[imm & 0xf]);
            return 0;
        case 1:
            snprintf(cp, cpsize, "TBH [%s, %s, LSL #1]", reg_name[rn], reg_name[imm & 0xf]);
            return 0;
        case 4:
            mnemonic = "LDREXB";
            break;
        case 5:
            mnemonic = "LDREXH";
            break;
        default:
            return -1;
        }
        imm = 0;
        goto ldrex;
    }
    return -1;

strex:
    imm <<= 2;
    if (imm)
        snprintf(cp, cpsize, "%s %s, %s, [%s, #%u] ; %#2.2x", mnemonic, reg_name[rd], reg_name[rt], reg_name[rn], imm, imm);
    else
        snprintf(cp, cpsize, "%s %s, %s, [%s]", mnemonic, reg_name[rd], reg_name[rt], reg_name[rn]);
    return 0;

ldrex:
    imm <<= 2;
    if (imm)
        snprintf(cp, cpsize, "%s %s, [%s, #%u] ; %#2.2x", mnemonic, reg_name[rt], reg_name[rn], imm, imm);
    else
        snprintf(cp, cpsize, "%s %s, [%s]", mnemonic, reg_name[rt], reg_name[rn]);
    return 0;

immediate:
    /* two indexed modes will write back rn */
    if (opcode & (1 << 21)) {
        if (opcode & (1 << 24)) /* pre-indexed */
            p2 = "]!";
        else { /* post-indexed */
            p1 = "]";
            p2 = "";
        }
    }

    imm <<= 2;
    snprintf(cp, cpsize, "%s %s, %s, [%s%s, #%s%u%s ; %#2.2x", mnemonic, reg_name[rt], reg_name[rd], reg_name[rn], p1,
            (opcode & (1 << 23)) ? "" : "-", imm, p2, imm);
    return 0;

literal:
    address = thumb_alignpc4(address);
    imm <<= 2;
    if (opcode & (1 << 23))
        address += imm;
    else
        address -= imm;
    snprintf(cp, cpsize, "%s %s, %s, %#8.8x", mnemonic, reg_name[rt], reg_name[rd], address);
    return 0;
}

static int t2ev_data_shift(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                           char *cp, unsigned cpsize)
{
    int op = (opcode >> 21) & 0xf;
    int rd = (opcode >> 8) & 0xf;
    int rn = (opcode >> 16) & 0xf;
    int type = (opcode >> 4) & 0x3;
    int immed = (opcode >> 6) & 0x3;
    const char *mnemonic;
    const char *suffix = "";

    immed |= (opcode >> 10) & 0x1c;
    if (opcode & (1 << 20))
        suffix = "S";

    switch (op) {
    case 0:
        if (rd == 0xf) {
            if (!(opcode & (1 << 20)))
                return -1;
            mnemonic = "TST";
            suffix = "";
            goto two;
        }
        mnemonic = "AND";
        break;
    case 1:
        mnemonic = "BIC";
        break;
    case 2:
        if (rn == 0xf) {
            switch (type) {
            case 0:
                if (immed == 0) {
                    snprintf(cp, cpsize, "MOV%s.W %s, %s", suffix, reg_name[rd], reg_name[opcode & 0xf]);
                    return 0;
                }
                mnemonic = "LSL";
                break;
            case 1:
                mnemonic = "LSR";
                break;
            case 2:
                mnemonic = "ASR";
                break;
            default:
                if (immed == 0) {
                    snprintf(cp, cpsize, "RRX%s %s, %s", suffix, reg_name[rd], reg_name[opcode & 0xf]);
                    return 0;
                }
                mnemonic = "ROR";
                break;
            }
            goto immediate;
        } else {
            mnemonic = "ORR";
        }
        break;
    case 3:
        if (rn == 0xf) {
            mnemonic = "MVN";
            rn = rd;
            goto two;
        } else {
            mnemonic = "ORN";
        }
        break;
    case 4:
        if (rd == 0xf) {
            if (!(opcode & (1 << 20)))
                return -1;
            mnemonic = "TEQ";
            suffix = "";
            goto two;
        }
        mnemonic = "EOR";
        break;
    case 8:
        if (rd == 0xf) {
            if (!(opcode & (1 << 20)))
                return -1;
            mnemonic = "CMN";
            suffix = "";
            goto two;
        }
        mnemonic = "ADD";
        break;
    case 0xa:
        mnemonic = "ADC";
        break;
    case 0xb:
        mnemonic = "SBC";
        break;
    case 0xd:
        if (rd == 0xf) {
            if (!(opcode & (1 << 21)))
                return -1;
            mnemonic = "CMP";
            suffix = "";
            goto two;
        }
        mnemonic = "SUB";
        break;
    case 0xe:
        mnemonic = "RSB";
        break;
    default:
        return -1;
    }

    snprintf(cp, cpsize, "%s%s.W %s, %s, %s", mnemonic, suffix, reg_name[rd], reg_name[rn], reg_name[opcode & 0xf]);

shift:
    cp = strchr(cp, 0);

    switch (type) {
    case 0:
        if (immed == 0)
            return 0;
        suffix = "LSL";
        break;
    case 1:
        suffix = "LSR";
        if (immed == 32)
            immed = 0;
        break;
    case 2:
        suffix = "ASR";
        if (immed == 32)
            immed = 0;
        break;
    case 3:
        if (immed == 0) {
            strcpy(cp, ", RRX");
            return 0;
        }
        suffix = "ROR";
        break;
    }
    snprintf(cp, cpsize, ", %s #%d", suffix, immed ? immed : 32);
    return 0;

two:
    snprintf(cp, cpsize, "%s%s.W %s, %s", mnemonic, suffix, reg_name[rn], reg_name[opcode & 0xf]);
    goto shift;

immediate:
    snprintf(cp, cpsize, "%s%s.W %s, %s, #%d", mnemonic, suffix, reg_name[rd], reg_name[opcode & 0xf],
            immed ? immed : 32);
    return 0;
}

static int t2ev_data_reg(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                         char *cp, unsigned cpsize)
{
    const char *mnemonic;
    const char *suffix = "";

    if (((opcode >> 4) & 0xf) == 0) {
        switch ((opcode >> 21) & 0x7) {
        case 0:
            mnemonic = "LSL";
            break;
        case 1:
            mnemonic = "LSR";
            break;
        case 2:
            mnemonic = "ASR";
            break;
        case 3:
            mnemonic = "ROR";
            break;
        default:
            return -1;
        }

        if (opcode & (1 << 20))
            suffix = "S";
        snprintf(cp, cpsize, "%s%s.W %s, %s, %s", mnemonic, suffix, reg_name[(opcode >> 8) & 0xf],
                reg_name[(opcode >> 16) & 0xf], reg_name[(opcode >> 0) & 0xf]);

    } else if (opcode & (1 << 7)) {
        switch ((opcode >> 20) & 0xf) {
        case 0:
        case 1:
        case 4:
        case 5:
            switch ((opcode >> 4) & 0x3) {
            case 1:
                suffix = ", ROR #8";
                break;
            case 2:
                suffix = ", ROR #16";
                break;
            case 3:
                suffix = ", ROR #24";
                break;
            }
            snprintf(cp, cpsize, "%cXT%c.W %s, %s%s", (opcode & (1 << 24)) ? 'U' : 'S',
                    (opcode & (1 << 26)) ? 'B' : 'H', reg_name[(opcode >> 8) & 0xf],
                    reg_name[(opcode >> 0) & 0xf], suffix);
            break;
        case 8:
        case 9:
        case 0xa:
        case 0xb:
            if (opcode & (1 << 6))
                return -1;
            if (((opcode >> 12) & 0xf) != 0xf)
                return -1;
            if (!(opcode & (1 << 20)))
                return -1;

            switch (((opcode >> 19) & 0x04) | ((opcode >> 4) & 0x3)) {
            case 0:
                mnemonic = "REV.W";
                break;
            case 1:
                mnemonic = "REV16.W";
                break;
            case 2:
                mnemonic = "RBIT";
                break;
            case 3:
                mnemonic = "REVSH.W";
                break;
            case 4:
                mnemonic = "CLZ";
                break;
            default:
                return -1;
            }
            snprintf(cp, cpsize, "%s %s, %s", mnemonic, reg_name[(opcode >> 8) & 0xf],
                    reg_name[(opcode >> 0) & 0xf]);
            break;
        default:
            return -1;
        }
    }

    return 0;
}

static int t2ev_load_word(unsigned opcode, unsigned address, struct arm_instruction *instruction,
                          char *cp, unsigned cpsize)
{
    int rn = (opcode >> 16) & 0xf;
    int immed;

    if (rn == 0xf) {
        immed = opcode & 0x0fff;
        if ((opcode & (1 << 23)) == 0)
            immed = -immed;
        snprintf(cp, cpsize, "LDR %s, %#8.8x", reg_name[(opcode >> 12) & 0xf], thumb_alignpc4(address) + immed);
        return 0;
    }

    if (opcode & (1 << 23)) {
        immed = opcode & 0x0fff;
        snprintf(cp, cpsize, "LDR.W %s, [%s, #%d] ; %#3.3x", reg_name[(opcode >> 12) & 0xf], reg_name[rn], immed,
                immed);
        return 0;
    }

    if (!(opcode & (0x3f << 6))) {
        snprintf(cp, cpsize, "LDR.W %s, [%s, %s, LSL #%d]", reg_name[(opcode >> 12) & 0xf], reg_name[rn],
                reg_name[(opcode >> 0) & 0xf], (int)(opcode >> 4) & 0x3);
        return 0;
    }

    if (((opcode >> 8) & 0xf) == 0xe) {
        immed = opcode & 0x00ff;

        snprintf(cp, cpsize, "LDRT %s, [%s, #%d] ; %#2.2x", reg_name[(opcode >> 12) & 0xf], reg_name[rn], immed, immed);
        return 0;
    }

    if (((opcode >> 8) & 0xf) == 0xc || (opcode & 0x0900) == 0x0900) {
        const char *p1 = "]", *p2 = "";

        if (!(opcode & 0x0500))
            return -1;

        immed = opcode & 0x00ff;

        /* two indexed modes will write back rn */
        if (opcode & 0x100) {
            if (opcode & 0x400) /* pre-indexed */
                p2 = "]!";
            else { /* post-indexed */
                p1 = "]";
                p2 = "";
            }
        }

        snprintf(cp, cpsize, "LDR %s, [%s%s, #%s%u%s ; %#2.2x", reg_name[(opcode >> 12) & 0xf], reg_name[rn], p1,
                (opcode & 0x200) ? "" : "-", immed, p2, immed);
        return 0;
    }

    return -1;
}

static int t2ev_load_byte_hints(unsigned opcode, unsigned address,
                                struct arm_instruction *instruction, char *cp, unsigned cpsize)
{
    int rn = (opcode >> 16) & 0xf;
    int rt = (opcode >> 12) & 0xf;
    int op2 = (opcode >> 6) & 0x3f;
    unsigned immed;
    const char *p1 = "", *p2 = "]";
    const char *mnemonic;

    switch ((opcode >> 23) & 0x3) {
    case 0:
        if ((rn & rt) == 0xf) {
        pld_literal:
            immed = opcode & 0xfff;
            address = thumb_alignpc4(address);
            if (opcode & (1 << 23))
                address += immed;
            else
                address -= immed;
            snprintf(cp, cpsize, "PLD %s, %#8.8x", reg_name[rt], address);
            return 0;
        }
        if (rn == 0x0f && rt != 0x0f) {
        ldrb_literal:
            immed = opcode & 0xfff;
            address = thumb_alignpc4(address);
            if (opcode & (1 << 23))
                address += immed;
            else
                address -= immed;
            snprintf(cp, cpsize, "LDRB %s, %#8.8x", reg_name[rt], address);
            return 0;
        }
        if (rn == 0x0f)
            break;
        if ((op2 & 0x3c) == 0x38) {
            immed = opcode & 0xff;
            snprintf(cp, cpsize, "LDRBT %s, [%s, #%d] ; %#2.2x", reg_name[rt], reg_name[rn], immed, immed);
            return 0;
        }
        if ((op2 & 0x3c) == 0x30) {
            if (rt == 0x0f) {
                immed = opcode & 0xff;
                immed = -immed;
            preload_immediate:
                p1 = (opcode & (1 << 21)) ? "W" : "";
                snprintf(cp, cpsize, "PLD%s [%s, #%d] ; %#6.6x", p1, reg_name[rn], immed, immed);
                return 0;
            }
            mnemonic = "LDRB";
        ldrxb_immediate_t3:
            immed = opcode & 0xff;
            if (!(opcode & 0x200))
                immed = -immed;

            /* two indexed modes will write back rn */
            if (opcode & 0x100) {
                if (opcode & 0x400) /* pre-indexed */
                    p2 = "]!";
                else { /* post-indexed */
                    p1 = "]";
                    p2 = "";
                }
            }
        ldrxb_immediate_t2:
            snprintf(cp, cpsize, "%s %s, [%s%s, #%d%s ; %#8.8x", mnemonic, reg_name[rt], reg_name[rn], p1, immed, p2, immed);
            return 0;
        }
        if ((op2 & 0x24) == 0x24) {
            mnemonic = "LDRB";
            goto ldrxb_immediate_t3;
        }
        if (op2 == 0) {
            int rm = opcode & 0xf;

            if (rt == 0x0f)
                snprintf(cp, cpsize, "PLD ");
            else
                snprintf(cp, cpsize, "LDRB.W %s, ", reg_name[rt]);
            immed = (opcode >> 4) & 0x3;
            cp = strchr(cp, 0);
            snprintf(cp, cpsize, "[%s, %s, LSL #%d]", reg_name[rn], reg_name[rm], immed);
            return 0;
        }
        break;
    case 1:
        if ((rn & rt) == 0xf)
            goto pld_literal;
        if (rt == 0xf) {
            immed = opcode & 0xfff;
            goto preload_immediate;
        }
        if (rn == 0x0f)
            goto ldrb_literal;
        mnemonic = "LDRB.W";
        immed = opcode & 0xfff;
        goto ldrxb_immediate_t2;
    case 2:
        if ((rn & rt) == 0xf) {
            immed = opcode & 0xfff;
            address = thumb_alignpc4(address);
            if (opcode & (1 << 23))
                address += immed;
            else
                address -= immed;
            snprintf(cp, cpsize, "PLI %#8.8x", address);
            return 0;
        }
        if (rn == 0xf && rt != 0xf) {
        ldrsb_literal:
            immed = opcode & 0xfff;
            address = thumb_alignpc4(address);
            if (opcode & (1 << 23))
                address += immed;
            else
                address -= immed;
            snprintf(cp, cpsize, "LDRSB %#8.8x", address);
            return 0;
        }
        if (rn == 0xf)
            break;
        if ((op2 & 0x3c) == 0x38) {
            immed = opcode & 0xff;
            snprintf(cp, cpsize, "LDRSBT %s, [%s, #%d] ; %#2.2x", reg_name[rt], reg_name[rn], immed, immed);
            return 0;
        }
        if ((op2 & 0x3c) == 0x30) {
            if (rt == 0xf) {
                immed = opcode & 0xff;
                immed = -immed; // pli
                snprintf(cp, cpsize, "PLI [%s, #%d] ; -%#2.2x", reg_name[rn], immed, -immed);
                return 0;
            }
            mnemonic = "LDRSB";
            goto ldrxb_immediate_t3;
        }
        if ((op2 & 0x24) == 0x24) {
            mnemonic = "LDRSB";
            goto ldrxb_immediate_t3;
        }
        if (op2 == 0) {
            int rm = opcode & 0xf;

            if (rt == 0x0f)
                snprintf(cp, cpsize, "PLI ");
            else
                snprintf(cp, cpsize, "LDRSB.W %s, ", reg_name[rt]);
            immed = (opcode >> 4) & 0x3;
            cp = strchr(cp, 0);
            snprintf(cp, cpsize, "[%s, %s, LSL #%d]", reg_name[rn], reg_name[rm], immed);
            return 0;
        }
        break;
    case 3:
        if (rt == 0xf) {
            immed = opcode & 0xfff;
            snprintf(cp, cpsize, "PLI [%s, #%d] ; %#3.3x", reg_name[rn], immed, immed);
            return 0;
        }
        if (rn == 0xf)
            goto ldrsb_literal;
        immed = opcode & 0xfff;
        mnemonic = "LDRSB";
        goto ldrxb_immediate_t2;
    }

    return -1;
}

static int t2ev_load_halfword(unsigned opcode, unsigned address,
                              struct arm_instruction *instruction, char *cp, unsigned cpsize)
{
    int rn = (opcode >> 16) & 0xf;
    int rt = (opcode >> 12) & 0xf;
    int op2 = (opcode >> 6) & 0x3f;
    const char *sign = "";
    unsigned immed;

    if (rt == 0xf) {
        snprintf(cp, cpsize, "HINT (UNALLOCATED)");
        return 0;
    }

    if (opcode & (1 << 24))
        sign = "S";

    if ((opcode & (1 << 23)) == 0) {
        if (rn == 0xf) {
        ldrh_literal:
            immed = opcode & 0xfff;
            address = thumb_alignpc4(address);
            if (opcode & (1 << 23))
                address += immed;
            else
                address -= immed;
            snprintf(cp, cpsize, "LDR%sH %s, %#8.8x", sign, reg_name[rt], address);
            return 0;
        }
        if (op2 == 0) {
            int rm = opcode & 0xf;

            immed = (opcode >> 4) & 0x3;
            snprintf(cp, cpsize, "LDR%sH.W %s, [%s, %s, LSL #%d]", sign, reg_name[rt], reg_name[rn], reg_name[rm], immed);
            return 0;
        }
        if ((op2 & 0x3c) == 0x38) {
            immed = opcode & 0xff;
            snprintf(cp, cpsize, "LDR%sHT %s, [%s, #%d] ; %#2.2x", sign, reg_name[rt], reg_name[rn], immed, immed);
            return 0;
        }
        if ((op2 & 0x3c) == 0x30 || (op2 & 0x24) == 0x24) {
            const char *p1 = "", *p2 = "]";

            immed = opcode & 0xff;
            if (!(opcode & 0x200))
                immed = -immed;

            /* two indexed modes will write back rn */
            if (opcode & 0x100) {
                if (opcode & 0x400) /* pre-indexed */
                    p2 = "]!";
                else { /* post-indexed */
                    p1 = "]";
                    p2 = "";
                }
            }
            snprintf(cp, cpsize, "LDR%sH %s, [%s%s, #%d%s ; %#8.8x", sign, reg_name[rt], reg_name[rn], p1, immed, p2, immed);
            return 0;
        }
    } else {
        if (rn == 0xf)
            goto ldrh_literal;

        immed = opcode & 0xfff;
        snprintf(cp, cpsize, "LDR%sH%s %s, [%s, #%d] ; %#6.6x", sign, *sign ? "" : ".W", reg_name[rt], reg_name[rn], immed,
                immed);
        return 0;
    }

    return -1;
}

static std::string evaluate_opcode32(unsigned opcode, unsigned address)
{
    // 32-bit instructions.
    struct arm_instruction instruction{};

    char *cp = instruction.text;
    int retval = -2;

    /* ARMv7-M: A5.3.1 Data processing (modified immediate) */
    if ((opcode & 0x1a008000) == 0x10000000)
        retval = t2ev_data_mod_immed(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.3 Data processing (plain binary immediate) */
    else if ((opcode & 0x1a008000) == 0x12000000)
        retval = t2ev_data_immed(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.4 Branches and miscellaneous control */
    else if ((opcode & 0x18008000) == 0x10008000)
        retval = t2ev_b_misc(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.5 Load/store multiple */
    else if ((opcode & 0x1e400000) == 0x08000000)
        retval = t2ev_ldm_stm(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.6 Load/store dual or exclusive, table branch */
    else if ((opcode & 0x1e400000) == 0x08400000)
        retval = t2ev_ldrex_strex(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.7 Load word */
    else if ((opcode & 0x1f700000) == 0x18500000)
        retval = t2ev_load_word(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.8 Load halfword, unallocated memory hints */
    else if ((opcode & 0x1e700000) == 0x18300000)
        retval = t2ev_load_halfword(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.9 Load byte, memory hints */
    else if ((opcode & 0x1e700000) == 0x18100000)
        retval = t2ev_load_byte_hints(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.10 Store single data item */
    else if ((opcode & 0x1f100000) == 0x18000000)
        retval = t2ev_store_single(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.11 Data processing (shifted register) */
    else if ((opcode & 0x1e000000) == 0x0a000000)
        retval = t2ev_data_shift(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.12 Data processing (register)
     * and      A5.3.13 Miscellaneous operations
     */
    else if ((opcode & 0x1f000000) == 0x1a000000)
        retval = t2ev_data_reg(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.14 Multiply, and multiply accumulate */
    else if ((opcode & 0x1f800000) == 0x1b000000)
        retval = t2ev_mul32(opcode, address, &instruction, cp, sizeof(instruction.text));

    /* ARMv7-M: A5.3.15 Long multiply, long multiply accumulate, divide */
    else if ((opcode & 0x1f800000) == 0x1b800000)
        retval = t2ev_mul64_div(opcode, address, &instruction, cp, sizeof(instruction.text));

    if (retval != 0)
        return "???";

    return instruction.text;
}

//
// Compute length of the opcode: 2 or 4 bytes.
//
unsigned arm_opcode_length(unsigned opcode)
{
    if ((opcode & 0xe0000000) == 0xe0000000 &&
        (opcode & 0x18000000) != 0)
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

    if ((opcode & 0xe0000000) == 0xe0000000 &&
        (opcode & 0x18000000) != 0) {
        // 32-bit instruction.
        return evaluate_opcode32(opcode, address);
    }

    // 16-bit Thumb1 instruction.
    return evaluate_opcode16(opcode >> 16, address);
}

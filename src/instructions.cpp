#include "processor.h"
#include "bus_controller.h"

//
// Execute 16-bit Thumb1 instruction.
// Set pc_next when jump performed.
//
void Processor::process_opcode16()
{
    switch (opcode >> 8) {
    // clang-format off
    case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
    case 0x08: case 0x09: case 0x0a: case 0x0b: case 0x0c: case 0x0d: case 0x0e: case 0x0f:
    case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
        thumb_shift_imm();
        break;

    case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
        thumb_add_sub();
        break;

    case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26: case 0x27:
    case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
    case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
    case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
        thumb_arith_imm();
        break;

    case 0x40: case 0x41: case 0x42: case 0x43:
        thumb_arith_reg();
        break;

    case 0x44: case 0x45: case 0x46:
        thumb_add_cmp_mov();
        break;

    case 0x47:
        thumb_bx();
        break;

    case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
        thumb_load_literal();
        break;

    case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x57:
    case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5e: case 0x5f:
        thumb_load_store_reg();
        break;

    case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x66: case 0x67:
    case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6e: case 0x6f:
    case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77:
    case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x7f:
    case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87:
    case 0x88: case 0x89: case 0x8a: case 0x8b: case 0x8c: case 0x8d: case 0x8e: case 0x8f:
        thumb_load_store_imm();
        break;

    case 0x90: case 0x91: case 0x92: case 0x93: case 0x94: case 0x95: case 0x96: case 0x97:
    case 0x98: case 0x99: case 0x9a: case 0x9b: case 0x9c: case 0x9d: case 0x9e: case 0x9f:
        thumb_load_store_stack();
        break;

    case 0xa0: case 0xa1: case 0xa2: case 0xa3: case 0xa4: case 0xa5: case 0xa6: case 0xa7:
    case 0xa8: case 0xa9: case 0xaa: case 0xab: case 0xac: case 0xad: case 0xae: case 0xaf:
        thumb_add_sp_pc();
        break;

    case 0xb0:
        thumb_adjust_stack();
        break;

    case 0xb2:
        thumb_extend();
        break;

    case 0xb4:
    case 0xb5:
        thumb_push();
        break;

    case 0xbc:
    case 0xbd:
        thumb_pop();
        break;

    case 0xb6:
        thumb_cps();
        break;

    case 0xba:
        thumb_byterev();
        break;

    case 0xbe:
        thumb_breakpoint();
        break;

    case 0xbf:
        thumb_hint();
        break;

    case 0xc0: case 0xc1: case 0xc2: case 0xc3: case 0xc4: case 0xc5: case 0xc6: case 0xc7:
        thumb_stmia();
        break;

    case 0xc8: case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf:
        thumb_ldmia();
        break;

    case 0xd0: case 0xd1: case 0xd2: case 0xd3: case 0xd4: case 0xd5: case 0xd6: case 0xd7:
    case 0xd8: case 0xd9: case 0xda: case 0xdb: case 0xdc: case 0xdd:
        thumb_cond_branch();
        break;

    case 0xde:
        thumb_udf();
        break;

    case 0xdf:
        thumb_svc();
        break;

    case 0xe0: case 0xe1: case 0xe2: case 0xe3: case 0xe4: case 0xe5: case 0xe6: case 0xe7:
    case 0xe8: case 0xe9: case 0xea: case 0xeb: case 0xec: case 0xed: case 0xee: case 0xef:
    case 0xf0: case 0xf1: case 0xf2: case 0xf3: case 0xf4: case 0xf5: case 0xf6: case 0xf7:
    case 0xf8: case 0xf9: case 0xfa: case 0xfb: case 0xfc: case 0xfd: case 0xfe: case 0xff:
        thumb_branch();
        break;

    // clang-format on
    default:
        terminate_simulation("Invalid instruction");
    }
}

//
// Execute 32-bit instruction.
//
void Processor::process_opcode32()
{
    if ((opcode & 0xf800d000) == 0xf000d000) {
        thumb_branch_link();
    } else if ((opcode & 0xffffffc0) == 0xf3bf8f40) {
        thumb_barrier();
    } else if ((opcode & 0xff90f060) == 0xf3808000) {
        thumb_sysreg();
    } else {
        terminate_simulation("Invalid instruction");
    }
}

//
// movs r1, #255
// cmp r1, #255
// add r1, #255
// sub r1, #255
//
void Processor::thumb_arith_imm()
{
    unsigned imm = opcode & 0xff;
    unsigned rd  = (opcode >> 8) & 0x7;
    unsigned opc = (opcode >> 11) & 0x3;

    switch (opc) {
    case 0:
        // MOV instruction.
        set_reg_nz(rd, imm);
        break;
    case 1:
        // CMP instruction.
        add_with_carry(get_reg(rd), ~imm, 1);
        break;
    case 2:
        // ADD instruction.
        set_reg(rd, add_with_carry(get_reg(rd), imm, 0));
        break;
    case 3:
        // SUB instruction.
        set_reg(rd, add_with_carry(get_reg(rd), ~imm, 1));
        break;
    }
}

//
// svc 255
//
void Processor::thumb_svc()
{
    unsigned offset = opcode & 0xff;

    if (offset == 0 && linux_mode) {
        // Interpret Linux syscalls.
        linux_syscall(get_reg(7));
    } else {
        terminate_simulation("Unsupported SVC instruction");
    }
}

//
// Interpret Linux syscalls.
//
void Processor::linux_syscall(int op)
{
    switch (get_reg(7)) {
    case 1:
        // Syscall exit(status).
        app_finished = true;
        break;

    case 4: {
        // Syscall write(fd, buf, count).
        unsigned fd = get_reg(0);
        unsigned addr = get_reg(1);
        unsigned len = get_reg(2);

        // Make sure arguments are reasonable.
        if (fd == 1 && len > 0 && len <= 10000 &&
            addr >= ADDR_SRAM_START && (addr+len) <= ADDR_SRAM_LAST) {
#if 0
            char buf[len];
            data_readn(buf, addr, len); // TODO
            write(1, buf, len);
#endif
        }
        break;
    }
    default:
        terminate_simulation("Unsupported syscall");
    }
}

//
// ldr r1, [pc, #1020]
//
void Processor::thumb_load_literal()
{
    unsigned immediate = opcode & 0xff;
    unsigned rd        = (opcode >> 8) & 0x7;
    uint32_t address   = ((get_pc() + 4) & ~3) + (immediate << 2);
    unsigned word      = data_read32(address);

    set_reg(rd, word);
}

//
// msr APSR, r1
// mrs r1, PRIMASK
//
void Processor::thumb_sysreg()
{
    unsigned sysreg = opcode & 0xff;
    unsigned rn     = (opcode >> 16) & 0x0f;
    unsigned rd     = (opcode >> 8) & 0x0f;

    switch ((opcode >> 20) & 0x6) {
    case 0x0:
        // msr APSR, r1
        set_sysreg(sysreg, get_reg(rn));
        return;
    case 0x6:
        // mrs r1, PRIMASK
        set_reg(rd, get_sysreg(sysreg));
        return;
    }
    terminate_simulation("Invalid instruction");
}

void Processor::thumb_shift_imm()
{
    unsigned rd  = (opcode >> 0) & 7;
    unsigned rm  = (opcode >> 3) & 7;
    unsigned imm = (opcode >> 6) & 0x1f;
    unsigned opc = (opcode >> 11) & 3;

    switch (opc) {
    case 0:
        if (imm == 0) {
            // MOVS instruction.
            set_reg_nz(rd, get_reg(rm));
        } else {
            // LSL instruction.
            uint32_t value = get_reg(rm);
            set_reg_nz(rd, value << imm);
            xpsr.field.c = value >> (32 - imm);
        }
        break;

    case 1: {
        // LSR instruction.
        if (imm == 0) {
            imm = 32;
        }
        uint32_t value = get_reg(rm);
        set_reg_nz(rd, (uint64_t)value >> imm);
        xpsr.field.c = value >> (imm - 1);
        break;
    }
    case 2: {
        // ASR instruction.
        if (imm == 0) {
            imm = 32;
        }
        int64_t value = get_reg(rm);
        set_reg_nz(rd, value >> imm);
        xpsr.field.c = value >> (imm - 1);
        break;
    }
    }
}

//
// See AddWithCarry() pseudocode ARM ARMv6-M Architecture Reference Manual.
//
// AddWithCarry(bits(N) x, bits(N) y, bit carry_in) -> (bits(N), bit, bit)
//      unsigned_sum = UInt(x) + UInt(y) + UInt(carry_in);
//      signed_sum   = SInt(x) + SInt(y) + UInt(carry_in);
//      result       = unsigned_sum<N-1:0>; // same value as signed_sum<N-1:0>
//      carry_out    = if UInt(result) == unsigned_sum then '0' else '1';
//      overflow     = if SInt(result) == signed_sum then '0' else '1';
//      return (result, carry_out, overflow);
//
int32_t Processor::add_with_carry(int32_t x, int32_t y, bool carry_in)
{
    uint64_t unsigned_sum = (uint64_t)(uint32_t)x + (uint64_t)(uint32_t)y + carry_in;
    int64_t  signed_sum   = (int64_t)x + (int64_t)y + carry_in;
    int32_t  result       = (int32_t)unsigned_sum;

    xpsr.field.n = (result < 0);
    xpsr.field.z = (result == 0);
    xpsr.field.c = ((uint32_t)result != unsigned_sum); // carry out
    xpsr.field.v = ((int32_t)result != signed_sum);    // overflow

    return result;
}

//
// add r1, r2, r3
// add r1, r2, #7
// sub r1, r2, r3
// sub r1, r2, #7
// movs r1, r2
//
void Processor::thumb_add_sub()
{
    unsigned rd           = (opcode >> 0) & 0x7;
    unsigned rn           = (opcode >> 3) & 0x7;
    unsigned rm_imm       = (opcode >> 6) & 0x7;
    unsigned sub_flag     = (opcode >> 9) & 1;
    unsigned reg_imm_flag = (opcode >> 10) & 1;

    int32_t n = get_reg(rn);
    int32_t m = reg_imm_flag ? rm_imm
                             : get_reg(rm_imm);
    int32_t result = sub_flag ? add_with_carry(n, ~m, 1)
                              : add_with_carry(n, m, 0);
    set_reg(rd, result);
}

void Processor::thumb_arith_reg()
{
    unsigned op = (opcode >> 6) & 0x0f;
    unsigned rd = opcode & 7;
    unsigned rm = (opcode >> 3) & 7;

    switch (op) {
    case 0x0:
        // AND instruction.
        set_reg_nz(rd, get_reg(rd) & get_reg(rm));
        break;
    case 0x1:
        // EOR instruction.
        set_reg_nz(rd, get_reg(rd) ^ get_reg(rm));
        break;
    case 0x2: {
        // LSL instruction.
        uint64_t value = (uint32_t) get_reg(rd);
        unsigned shift = get_reg(rm) & 0xff;
        if (shift > 0) {
            if (shift <= 32) {
                xpsr.field.c = value >> (32 - shift);
                value <<= shift;
            } else {
                xpsr.field.c = 0;
                value = 0;
            }
        }
        set_reg_nz(rd, value);
        break;
    }
    case 0x3: {
        // LSR instruction.
        uint64_t value = (uint32_t) get_reg(rd);
        unsigned shift = get_reg(rm) & 0xff;
        if (shift > 0) {
            if (shift <= 32) {
                xpsr.field.c = value >> (shift - 1);
                value >>= shift;
            } else {
                xpsr.field.c = 0;
                value = 0;
            }
        }
        set_reg_nz(rd, value);
        break;
    }
    case 0x4: {
        // ASR instruction.
        int64_t value  = get_reg(rd);
        unsigned shift = get_reg(rm) & 0xff;
        if (shift > 0) {
            if (shift > 32) {
                shift = 32;
            }
            xpsr.field.c = value >> (shift - 1);
        }
        set_reg_nz(rd, value >> shift);
        break;
    }
    case 0x5:
        // ADC instruction.
        set_reg(rd, add_with_carry(get_reg(rd), get_reg(rm), xpsr.field.c));
        break;
    case 0x6:
        // SBC instruction.
        set_reg(rd, add_with_carry(get_reg(rd), ~get_reg(rm), xpsr.field.c));
        break;
    case 0x7: {
        // ROR instruction.
        uint64_t value = (uint32_t) get_reg(rd);
        unsigned shift = get_reg(rm) & 0xff;
        if (shift > 0) {
            shift &= 0x1f;
            value |= value << 32;
            value >>= shift;
            xpsr.field.c = value >> 31;
        }
        set_reg_nz(rd, value);
        break;
    }
    case 0x8:
        // TST instruction.
        set_nz_flags(get_reg(rd) & get_reg(rm));
        break;
    case 0x9:
        // NEG instruction.
        set_reg(rd, add_with_carry(~get_reg(rm), 0, 1));
        break;
    case 0xA:
        // CMP instruction.
        add_with_carry(get_reg(rd), ~get_reg(rm), 1);
        break;
    case 0xB:
        // CMN instruction.
        add_with_carry(get_reg(rd), get_reg(rm), 0);
        break;
    case 0xC:
        // ORR instruction.
        set_reg_nz(rd, get_reg(rd) | get_reg(rm));
        break;
    case 0xD:
        // MUL instruction.
        set_reg_nz(rd, get_reg(rd) * get_reg(rm));
        break;
    case 0xE:
        // BIC instruction.
        set_reg_nz(rd, get_reg(rd) & ~get_reg(rm));
        break;
    case 0xF:
        // MVN instruction.
        set_reg_nz(rd, ~get_reg(rm));
        break;
    }
}

void Processor::thumb_add_cmp_mov()
{
    unsigned rd = opcode & 7;
    unsigned rm = (opcode >> 3) & 0x0f;
    unsigned h1 = (opcode >> 7) & 1;
    unsigned op = (opcode >> 8) & 3;

    int32_t value = get_reg(rm);
    if (rm == Registers::PC) {
        // ARMv6-M feature: PC goes ahead by 4 bytes.
        value += 4;
    }

    rd |= h1 << 3;

    switch (op) {
    default:
    case 0x0:
        // ADD instruction.
        value += get_reg(rd);
        if (rd == Registers::PC) {
            // ARMv6-M feature: PC goes ahead by 4 bytes.
            value += 4;
        }
        set_reg(rd, value);
        break;

    case 0x1: {
        // CMP instruction.
        int32_t lval = get_reg(rd);
        if (rd == Registers::PC) {
            // ARMv6-M feature: PC goes ahead by 4 bytes.
            lval += 4;
        }
        add_with_carry(lval, ~value, 1);
        break;
    }
    case 0x2:
        if (rd == 8 && rm == 8) {
            // NOP instruction.
            return;
        }
        // MOV instruction.
        set_reg(rd, value);
        break;
    }
}

void Processor::thumb_bx()
{
    terminate_simulation(__func__); // TODO
#if 0
    unsigned rm = (opcode >> 3) & 0x0f;
    std::ostringstream text;

    if ((opcode & 0x0087) != 0)
        return UNKNOWN;

    text << "bx " << reg_name[rm];
    return text.str();
#endif
}

void Processor::thumb_load_store_reg()
{
    unsigned rd      = (opcode >> 0) & 0x7;
    unsigned rn      = (opcode >> 3) & 0x7;
    unsigned rm      = (opcode >> 6) & 0x7;
    unsigned opc     = (opcode >> 9) & 0x7;
    uint32_t address = get_reg(rn) + get_reg(rm);

    switch (opc) {
    case 0:
        // STR instruction.
        data_write32(address, get_reg(rd));
        break;
    case 1:
        // STRH instruction.
        data_write16(address, get_reg(rd));
        break;
    case 2:
        // STRB instruction.
        data_write8(address, get_reg(rd));
        break;
    case 3:
        // LDRSB instruction: sign extension.
        set_reg(rd, (int32_t)(int8_t)data_read8(address));
        break;
    case 4:
        // LDR instruction.
        set_reg(rd, data_read32(address));
        break;
    case 5:
        // LDRH instruction.
        set_reg(rd, data_read16(address));
        break;
    case 6:
        // LDRB instruction.
        set_reg(rd, data_read8(address));
        break;
    case 7:
        // LDRSH instruction: sign extension.
        set_reg(rd, (int32_t)(int16_t)data_read16(address));
        break;
    }
}

void Processor::thumb_load_store_imm()
{
    unsigned rd        = (opcode >> 0) & 0x7;
    unsigned rn        = (opcode >> 3) & 0x7;
    unsigned offset    = (opcode >> 6) & 0x1f;
    unsigned load_flag = (opcode >> 11) & 1;
    uint32_t address   = get_reg(rn);

    switch (opcode >> 12) {
    case 0x8:
        address += offset << 1;
        if (load_flag) {
            // LDRH instruction.
            set_reg(rd, data_read16(address));
        } else {
            // STRH instruction.
            data_write16(address, get_reg(rd));
        }
        break;
    case 0x7:
        address += offset;
        if (load_flag) {
            // LDRB instruction.
            set_reg(rd, data_read8(address));
        } else {
            // STRB instruction.
            data_write8(address, get_reg(rd));
        }
        break;
    default:
        address += offset << 2;
        if (load_flag) {
            // LDR instruction.
            set_reg(rd, data_read32(address));
        } else {
            // STR instruction.
            data_write32(address, get_reg(rd));
        }
        break;
    }
}

void Processor::thumb_load_store_stack()
{
    unsigned offset    = opcode & 0xff;
    unsigned rd        = (opcode >> 8) & 0x7;
    unsigned load_flag = opcode & (1 << 11);
    uint32_t address   = get_reg(Registers::SP) + (offset << 2);

    if (load_flag) {
        // LDR instruction.
        set_reg(rd, data_read32(address));
    } else {
        // STR instruction.
        data_write32(address, get_reg(rd));
    }
}

void Processor::thumb_add_sp_pc()
{
    unsigned imm         = opcode & 0xff;
    unsigned rd          = (opcode >> 8) & 0x7;
    unsigned sp_flag     = opcode & (1 << 11);
    unsigned sp          = get_reg(Registers::SP);
    unsigned pc_aligned  = (register_bank.getPC() + 4) & ~3;
    unsigned value       = (sp_flag ? sp : pc_aligned) + (imm << 2);

    set_reg(rd, value);
}

void Processor::thumb_adjust_stack()
{
    unsigned imm      = opcode & 0x7f;
    unsigned sub_flag = (opcode >> 7) & 1;
    unsigned value    = get_reg(Registers::SP);

    if (sub_flag) {
        // SUB instruction.
        value -= imm << 2;
    } else {
        // ADD instruction.
        value += imm << 2;
    }
    set_reg(Registers::SP, value);
}

void Processor::thumb_extend()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_cps()
{
    switch (opcode & 0xff) {
    case 0x62:
        // CPSIE I instruction.
        set_sysreg(SYSM_PRIMASK, 0);
        break;
    case 0x72:
        // CPSID I instruction.
        set_sysreg(SYSM_PRIMASK, 1);
        break;
    }
}

void Processor::thumb_byterev()
{
    unsigned rd = opcode & 7;
    unsigned rs = (opcode >> 3) & 7;
    union {
        uint32_t u32;
        uint8_t byte[4];
    } input, output;

    switch ((opcode >> 6) & 3) {
    case 0:
        // REV instruction.
        input.u32 = get_reg(rs);
        output.byte[0] = input.byte[3];
        output.byte[1] = input.byte[2];
        output.byte[2] = input.byte[1];
        output.byte[3] = input.byte[0];
        set_reg(rd, output.u32);
        break;
    case 1:
        // REV16 instruction.
        input.u32 = get_reg(rs);
        output.byte[0] = input.byte[1];
        output.byte[1] = input.byte[0];
        output.byte[2] = input.byte[3];
        output.byte[3] = input.byte[2];
        set_reg(rd, output.u32);
        break;
    case 3:
        terminate_simulation("revsh"); // TODO
        break;
    default:
        terminate_simulation("Unknown byterev instruction");
    }
}

void Processor::thumb_breakpoint()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_hint()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_ldmia()
{
    unsigned reg_list = opcode & 0xff;
    unsigned rn       = (opcode >> 8) & 7;
    uint32_t address  = get_reg(rn);

    for (unsigned rd = 0; rd < 8; rd++) {
        if ((reg_list >> rd) & 1) {
            set_reg(rd, data_read32(address));
            address += 4;
        }
    }

    if (!((reg_list >> rn) & 1)) {
        // Rn is not in list - write back incremented value.
        set_reg(rn, address);
    }
}

void Processor::thumb_stmia()
{
    unsigned reg_list = opcode & 0xff;
    unsigned rn       = (opcode >> 8) & 7;
    uint32_t address  = get_reg(rn);

    for (unsigned rd = 0; rd < 8; rd++) {
        if ((reg_list >> rd) & 1) {
            data_write32(address, get_reg(rd));
            address += 4;
        }
    }

    // Write back incremented address.
    set_reg(rn, address);
}

void Processor::thumb_pop()
{
    unsigned reg_list = opcode & 0xff;
    unsigned sp_flag  = (opcode >> 8) & 1;
    uint32_t address  = get_reg(Registers::SP);

    for (unsigned rd = 0; rd < 8; rd++) {
        if ((reg_list >> rd) & 1) {
            set_reg(rd, data_read32(address));
            address += 4;
        }
    }

    if (sp_flag) {
        // Jump.
        next_pc = data_read32(address) & ~1;
        address += 4;
    }

    // Update SP.
    set_reg(Registers::SP, address);
}

void Processor::thumb_push()
{
    unsigned reg_list = opcode & 0xff;
    unsigned lr_flag  = (opcode >> 8) & 1;
    uint32_t address  = get_reg(Registers::SP);

    if (lr_flag) {
        // Save LR first.
        address -= 4;
        data_write32(address, get_reg(Registers::LR));
    }

    for (unsigned rd = 7; rd < 8; rd--) {
        if ((reg_list >> rd) & 1) {
            address -= 4;
            data_write32(address, get_reg(rd));
        }
    }

    // Update SP.
    set_reg(Registers::SP, address);
}

//
// Condition codes
//
// cond Mnemonic   Meaning                         Condition flags
// ---------------------------------------------------------------
// 0000 EQ         Equal                           Z==1
// 0001 NE         Not equal                       Z==0
// 0010 CS         Carry set                       C==1
// 0011 CC         Carry clear                     C==0
// 0100 MI         Minus, negative                 N==1
// 0101 PL         Plus, positive or zero          N==0
// 0110 VS         Overflow                        V==1
// 0111 VC         No overflow                     V==0
// 1000 HI         Unsigned higher                 C==1 and Z==0
// 1001 LS         Unsigned lower or same          C==0 or Z==1
// 1010 GE         Signed greater than or equal    N==V
// 1011 LT         Signed less than                N!=V
// 1100 GT         Signed greater than             Z==0 and N==V
// 1101 LE         Signed less than or equal       Z==1 or N!=V
//
void Processor::thumb_cond_branch()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_branch()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_branch_link()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_barrier()
{
    unsigned op                      = (opcode >> 4) & 0x0f;
    unsigned option [[maybe_unused]] = opcode & 0x0f;

    switch (op) {
    case 4:
        // DSB instruction.
        break;
    case 5:
        // DMB instruction.
        break;
    case 6:
        // ISB instruction.
        break;
    default:
        terminate_simulation("Unknown barrier instruction");
    }
}

void Processor::thumb_udf()
{
    terminate_simulation("Undefined instruction");
}

#include "processor.h"

//
// Execute 16-bit Thumb1 instruction.
// Set pc_next when jump performed.
//
void Processor::process_opcode16()
{
    switch (opcode >> 8) {
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

    case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
        thumb_arith_reg();
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
    case 0xbc:
    case 0xbd:
        thumb_load_store_multiple();
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
    case 0xc8: case 0xc9: case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce: case 0xcf:
        thumb_load_store_multiple();
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
// adds r1, #255
// subs r1, #255
//
void Processor::thumb_arith_imm()
{
    unsigned imm = opcode & 0xff;
    unsigned rd = (opcode >> 8) & 0x7;
    unsigned opc = (opcode >> 11) & 0x3;

    switch (opc) {
    case 0:
        // movs r1, #255
        set_reg(rd, imm);
        break;
    case 1:
        terminate_simulation("cmp"); // TODO
        break;
    case 2:
        terminate_simulation("adds"); // TODO
        break;
    case 3:
        terminate_simulation("subs"); // TODO
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
#if 0
        unsigned fd = get_reg(0);
        unsigned buf = get_reg(1);
        unsigned len = get_reg(2);

        // Make sure arguments are reasonable.
        // TODO: get direct SRAM ptr.
        if (fd == 1 && buf >= ADDR_SRAM_START && (buf+len) <= ADDR_SRAM_LAST) {
            write(1, buf + sram_ptr, len);
        }
#endif
        break;
    }
    default:
        terminate_simulation("Unsupported syscall");
    }
}

void Processor::thumb_shift_imm()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_add_sub()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_arith_reg()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_load_literal()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_load_store_reg()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_load_store_imm()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_load_store_stack()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_add_sp_pc()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_adjust_stack()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_extend()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_byterev()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_breakpoint()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_hint()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_load_store_multiple()
{
    terminate_simulation(__func__); // TODO
}

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
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_sysreg()
{
    terminate_simulation(__func__); // TODO
}

void Processor::thumb_udf()
{
    terminate_simulation(__func__); // TODO
}

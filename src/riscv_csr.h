/*
 * Control and Status Registers for RISC-V processor.
 *
 * Copyright (C) 2021 Serge Vakulenko
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaim all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 */
#ifndef _RISCV_CSR_H
#define _RISCV_CSR_H

//----------------------------------
// Machine Information CSRs
//
#define CSR_MVENDORID       0xF11       // RO - Machine Vendor ID
#define CSR_MARCHID         0xF12       // RO - Machine Architecture ID
#define CSR_MIMPID          0xF13       // RO - Machine Implementation ID
#define CSR_MHARTID         0xF14       // RO - Machine Hart ID

//----------------------------------
// Machine Trap Setup CSRs
//
#define CSR_MSTATUS         0x300       // R/W - Machine Mode Status
#define CSR_MISA            0x301       // RO  - Machine ISA
#define CSR_MTVEC           0x305       // R/W - Machine Trap Vector

#define MSTATUS_UIE         (1 << 0)
#define MSTATUS_SIE         (1 << 1)
#define MSTATUS_MIE         (1 << 3)
#define MSTATUS_UPIE        (1 << 4)
#define MSTATUS_SPIE        (1 << 5)
#define MSTATUS_MPIE        (1 << 7)
#define MSTATUS_SPP         (1 << 8)
#define MSTATUS_MPP_shift   11
#define MSTATUS_MPP         (3 << MSTATUS_MPP_shift)
#define MSTATUS_FS          (1 << 13)
#define MSTATUS_XS          (1 << 15)
#define MSTATUS_MPRV        (1 << 17)
#define MSTATUS_SUM         (1 << 18)
#define MSTATUS_MXR         (1 << 19)
#define MSTATUS_TVM         (1 << 20)
#define MSTATUS_TW          (1 << 21)
#define MSTATUS_TSR         (1 << 22)

#define MSTATUS_MPP_USER        0       // User mode
#define MSTATUS_MPP_SUPERVISOR  1       // Unsupported
#define MSTATUS_MPP_HYPERVISOR  2       // Unsupported
#define MSTATUS_MPP_MACHINE     3       // Machine mode

#define MISA_A_EXTENSION    (1 << 0)    // RO - Atomic extension
#define MISA_C_EXTENSION    (1 << 2)    // RO - Compressed extension
#define MISA_D_EXTENSION    (1 << 3)    // RO - Double-precision floating-point extension
#define MISA_E_EXTENSION    (1 << 4)    // RO - RV32E base ISA
#define MISA_F_EXTENSION    (1 << 5)    // RO - Single-precision floating-point extension
#define MISA_G_EXTENSION    (1 << 6)    // RO - Additional standard extensions present
#define MISA_H_EXTENSION    (1 << 7)    // RO - Hypervisor extension
#define MISA_I_BASE         (1 << 8)    // RO - RV32I/64I/128I base ISA
#define MISA_M_EXTENSION    (1 << 12)   // RO - Integer Multiply/Divide extension
#define MISA_N_EXTENSION    (1 << 13)   // RO - User-level interrupts supported
#define MISA_Q_EXTENSION    (1 << 16)   // RO - Quad-precision floating-point extension
#define MISA_S_EXTENSION    (1 << 18)   // RO - Supervisor mode implemented
#define MISA_U_EXTENSION    (1 << 20)   // RO - User mode implemented
#define MISA_X_EXTENSION    (1 << 23)   // RO - Non-standard extensions present
#define MISA_MXL_32         (1 << 30)   // RO - Native base integer ISA width XLEN=32 bits
#define MISA_MXL_64         (2 << 30)   // RO - Native base integer ISA width XLEN=64 bits
#define MISA_MXL_128        (3 << 30)   // RO - Native base integer ISA width XLEN=128 bits

//----------------------------------
// Machine Trap Handling CSRs
//
#define CSR_MSCRATCH        0x340       // R/W - Machine Scratch
#define CSR_MEPC            0x341       // R/W - Machine Trap Program Counter
#define CSR_MCAUSE          0x342       // R/W - Machine Trap Cause
#define CSR_MTVAL           0x343       // R/W - Machine Trap Value

#define MCAUSE_EXCEPTION_CODE   0x1f
#define MCAUSE_INTERRUPT_FLAG   0x80000000

//----------------------------------
// User Trap Setup
//
#define CSR_USTATUS         0x000       // UR/W - User Mode Status

//----------------------------------
// User Custom Registers
//
#define CSR_UCUSTOM0        0x800       // UR/W - User Custom Read/Write Register 0
#define CSR_UCUSTOM1        0x801       // UR/W - User Custom Read/Write Register 1
#define CSR_UCUSTOM2        0x802       // UR/W - User Custom Read/Write Register 2
#define CSR_UCUSTOM3        0x803       // UR/W - User Custom Read/Write Register 3
#define CSR_UCUSTOM4        0x804       // UR/W - User Custom Read/Write Register 4
#define CSR_UCUSTOM5        0x805       // UR/W - User Custom Read/Write Register 5

//----------------------------------
// Physical Memory Protection (PMP) CSRs
//
#define CSR_PMPCFG(n)       (0x3A0+n)   // R/W - Physical memory protection configuration 0-3
#define CSR_PMPADDR(n)      (0x3B0+n)   // R/W - Physical memory protection address registers 0-15

//----------------------------------
// Trigger Module CSRs (shared with Debug Mode)
//
#define CSR_TSELECT         0x7A0       // R/W - Trigger Select Register
#define CSR_TDATA1          0x7A1       // R/W - Trigger Abstract Data 1
#define CSR_TDATA2          0x7A2       // R/W - Trigger Abstract Data 2
#define CSR_TCONTROL        0x7A5       // R/W - Global Trigger Control

//----------------------------------
// Debug Mode CSRs
//
#define CSR_DCSR            0x7B0       // R/W - Debug Control and Status
#define CSR_DPC             0x7B1       // R/W - Debug PC
#define CSR_DSCRATCH0       0x7B2       // R/W - Debug Scratch Register 0
#define CSR_DSCRATCH1       0x7B3       // R/W - Debug Scratch Register 1

//----------------------------------
// Performance Counter CSRs (Custom) 4
//
#define CSR_MPCER           0x7E0       // R/W - Machine Performance Counter Event
#define CSR_MPCMR           0x7E1       // R/W - Machine Performance Counter Mode
#define CSR_MPCCR           0x7E2       // R/W - Machine Performance Counter Count

#endif /* _RISCV_CSR_H */

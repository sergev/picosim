#include "base_instructions.h"
#include "processor.h"

enum Codes {
    LUI = 0b0110111,
    AUIPC = 0b0010111,
    JAL = 0b1101111,
    JALR = 0b1100111,

    BEQ = 0b1100011,
    BEQ_F = 0b000,
    BNE_F = 0b001,
    BLT_F = 0b100,
    BGE_F = 0b101,
    BLTU_F = 0b110,
    BGEU_F = 0b111,

    LB = 0b0000011,
    LB_F = 0b000,
    LH_F = 0b001,
    LW_F = 0b010,
    LBU_F = 0b100,
    LHU_F = 0b101,

    SB = 0b0100011,
    SB_F = 0b000,
    SH_F = 0b001,
    SW_F = 0b010,

    ADDI = 0b0010011,
    ADDI_F = 0b000,
    SLTI_F = 0b010,
    SLTIU_F = 0b011,
    XORI_F = 0b100,
    ORI_F = 0b110,
    ANDI_F = 0b111,
    SLLI_F = 0b001,
    SRLI_F = 0b101,
    SRLI_F7 = 0b0000000,
    SRAI_F7 = 0b0100000,

    ADD = 0b0110011,
    ADD_F = 0b000,
    SUB_F = 0b000,
    ADD_F7 = 0b0000000,
    SUB_F7 = 0b0100000,

    SLL_F = 0b001,
    SLT_F = 0b010,
    SLTU_F = 0b011,
    XOR_F = 0b100,
    SRL_F = 0b101,
    SRA_F = 0b101,
    SRL_F7 = 0b0000000,
    SRA_F7 = 0b0100000,
    OR_F = 0b110,
    AND_F = 0b111,

    FENCE = 0b0001111,
    ECALL = 0b1110011,
    ECALL_F = 0b000000000000,
    EBREAK_F = 0b000000000001,
    URET_F = 0b000000000010,
    SRET_F = 0b000100000010,
    MRET_F = 0b001100000010,
    WFI_F = 0b000100000101,
    SFENCE_F = 0b0001001,

    ECALL_F3 = 0b000,
    CSRRW = 0b001,
    CSRRS = 0b010,
    CSRRC = 0b011,
    CSRRWI = 0b101,
    CSRRSI = 0b110,
    CSRRCI = 0b111,
};

bool Base_Instructions::Exec_LUI() const
{
    int rd;
    uint32_t imm = 0;

    rd = get_rd();
    imm = get_imm_U() << 12;
    cpu.set_reg(rd, static_cast<int32_t>(imm));

    // Log::out() << "LUI x" << std::dec << rd << " <- 0x" << std::hex << imm << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_AUIPC() const
{
    int rd;
    uint32_t imm = 0;
    int new_pc;

    rd = get_rd();
    imm = get_imm_U() << 12;
    new_pc = static_cast<int32_t>(cpu.get_pc() + imm);

    cpu.set_reg(rd, new_pc);

    // Log::out() << "AUIPC x" << std::dec << rd << " <- 0x" << std::hex << imm
    //                         << " + PC (0x" << new_pc << ")"
    //                         << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_JAL() const
{
    int32_t mem_addr = 0;
    int rd;
    int new_pc, old_pc;

    rd = get_rd();
    mem_addr = get_imm_J();
    old_pc = static_cast<int32_t>(cpu.get_pc());
    new_pc = old_pc + mem_addr;

    cpu.set_pc(new_pc);
    cpu.set_reg(rd, old_pc + 4);

    // Log::out() << "JAL: x" << std::dec << rd << " <- 0x" << std::hex << old_pc
    //                        << std::dec << ". PC + 0x" << std::hex << mem_addr << " -> PC (0x"
    //                        << new_pc << ")"
    //                        << std::dec << std::endl;

    // Jump to self: terminate the simulation.
    if (mem_addr == 0) {
        cpu.terminate_simulation("Jump to self: infinite loop");
    }
    return true;
}

bool Base_Instructions::Exec_JALR() const
{
    uint32_t mem_addr = 0;
    int rd, rs1;
    int new_pc, old_pc;

    rd = get_rd();
    rs1 = get_rs1();
    mem_addr = get_imm_I();
    old_pc = static_cast<int32_t>(cpu.get_pc());
    new_pc = static_cast<int32_t>((cpu.get_reg(rs1) + mem_addr) & 0xFFFFFFFE);

    cpu.set_pc(new_pc);
    cpu.set_reg(rd, old_pc + 4);

    // Log::out() << "JALR: x" << std::dec << rd << " <- 0x" << std::hex << old_pc + 4
    //                         << " PC <- 0x" << new_pc << std::dec << std::endl;
    return true;
}

bool Base_Instructions::Exec_BEQ() const
{
    int rs1, rs2;
    int new_pc = 0;

    rs1 = get_rs1();
    rs2 = get_rs2();

    if (cpu.get_reg(rs1) == cpu.get_reg(rs2)) {
        new_pc = static_cast<int32_t>(cpu.get_pc() + get_imm_B());
        cpu.set_pc(new_pc);
    } else {
        cpu.inc_pc(4);
        new_pc = static_cast<int32_t>(cpu.get_pc());
    }

    // Log::out() << "BEQ x" << std::dec << rs1 << "(0x" << std::hex
    //                       << cpu.get_reg(rs1) << ") == x" << std::dec << rs2 << "(0x"
    //                       << std::hex << cpu.get_reg(rs2) << ")? -> PC (0x" << std::hex
    //                       << new_pc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_BNE() const
{
    int rs1, rs2;
    int new_pc = 0;
    uint32_t val1, val2;

    rs1 = get_rs1();
    rs2 = get_rs2();

    val1 = cpu.get_reg(rs1);
    val2 = cpu.get_reg(rs2);

    if (val1 != val2) {
        new_pc = static_cast<int32_t>(cpu.get_pc() + get_imm_B());
        cpu.set_pc(new_pc);
    } else {
        cpu.inc_pc(4);
        new_pc = static_cast<int32_t>(cpu.get_pc());
    }

    // Log::out() << "BNE: x" << std::dec << rs1 << "(0x" << std::hex << val1
    //                        << ") == x" << std::dec << rs2 << "(0x" << std::hex << val2
    //                        << ")? -> PC (0x" << std::hex << new_pc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_BLT() const
{
    int rs1, rs2;
    int new_pc = 0;

    rs1 = get_rs1();
    rs2 = get_rs2();

    if ((int32_t)cpu.get_reg(rs1) < (int32_t)cpu.get_reg(rs2)) {
        new_pc = static_cast<int32_t>(cpu.get_pc() + get_imm_B());
        cpu.set_pc(new_pc);
    } else {
        cpu.inc_pc(4);
    }

    // Log::out() << "BLT x" << std::dec << rs1 << "(0x" << std::hex
    //                       << (int32_t)cpu.get_reg(rs1) << ") < x" << std::dec << rs2
    //                       << "(0x" << std::hex << (int32_t)cpu.get_reg(rs2)
    //                       << ")? -> PC (0x" << std::hex << new_pc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_BGE() const
{
    int rs1, rs2;
    int new_pc = 0;

    rs1 = get_rs1();
    rs2 = get_rs2();

    if ((int32_t)cpu.get_reg(rs1) >= (int32_t)cpu.get_reg(rs2)) {
        new_pc = static_cast<int32_t>(cpu.get_pc() + get_imm_B());
        cpu.set_pc(new_pc);
    } else {
        cpu.inc_pc(4);
    }

    // Log::out() << "BGE x" << std::dec << rs1 << "(0x" << std::hex
    //                       << (int32_t)cpu.get_reg(rs1) << ") > x" << std::dec << rs2
    //                       << "(0x" << std::hex << (int32_t)cpu.get_reg(rs2)
    //                       << ")? -> PC (0x" << std::hex << new_pc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_BLTU() const
{
    int rs1, rs2;
    int new_pc = 0;

    rs1 = get_rs1();
    rs2 = get_rs2();

    if ((uint32_t)cpu.get_reg(rs1) < (uint32_t)cpu.get_reg(rs2)) {
        new_pc = static_cast<int32_t>(cpu.get_pc() + get_imm_B());
        cpu.set_pc(new_pc);
    } else {
        cpu.inc_pc(4);
        new_pc = static_cast<int32_t>(cpu.get_pc());
    }

    // Log::out() << "BLTU x" << std::dec << rs1 << "(0x" << std::hex
    //                        << cpu.get_reg(rs1) << ") < x" << std::dec << rs2 << "(0x"
    //                        << std::hex << cpu.get_reg(rs2) << ")? -> PC (0x" << std::hex
    //                        << new_pc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_BGEU() const
{
    int rs1, rs2;
    int new_pc = 0;

    rs1 = get_rs1();
    rs2 = get_rs2();

    if ((uint32_t)cpu.get_reg(rs1) >= (uint32_t)cpu.get_reg(rs2)) {
        new_pc = static_cast<int32_t>(cpu.get_pc() + get_imm_B());
        cpu.set_pc(new_pc);
    } else {
        cpu.inc_pc(4);
    }

    // Log::out() << "BGEU x" << std::dec << rs1 << "(0x" << std::hex
    //                        << cpu.get_reg(rs1) << ") > x" << std::dec << rs2 << "(0x"
    //                        << std::hex << cpu.get_reg(rs2) << ")? -> PC (0x" << std::hex
    //                        << new_pc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_LB() const
{
    uint32_t mem_addr = 0;
    int rd, rs1;
    int32_t imm = 0;
    int8_t data;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    mem_addr = imm + cpu.get_reg(rs1);
    data = static_cast<int8_t>(cpu.data_read8(mem_addr));
    cpu.set_reg(rd, data);

    // Log::out() << "LB: x" << rs1 << " + " << imm << " (@0x" << std::hex << mem_addr
    //                       << std::dec << ") -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_LH()
{
    uint32_t mem_addr = 0;
    int rd, rs1;
    int32_t imm = 0;
    int16_t data;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    mem_addr = imm + cpu.get_reg(rs1);
    if (mem_addr & 1) {
        cpu.raise_exception(EXCEPTION_CAUSE_LOAD_MISALIGN, mem_addr);
        return false;
    }
    data = static_cast<int16_t>(cpu.data_read16(mem_addr));
    cpu.set_reg(rd, data);

    // Log::out() << "LH: x" << rs1 << " + " << imm << " (@0x" << std::hex << mem_addr
    //                       << std::dec << ") -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_LW()
{
    uint32_t mem_addr = 0;
    int rd, rs1;
    int32_t imm = 0;
    uint32_t data;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    mem_addr = imm + cpu.get_reg(rs1);
    if (mem_addr & 3) {
        cpu.raise_exception(EXCEPTION_CAUSE_LOAD_MISALIGN, mem_addr);
        return false;
    }
    data = cpu.data_read32(mem_addr);
    cpu.set_reg(rd, static_cast<int32_t>(data));

    // Log::out() << std::dec << "LW: x" << rs1 << "(0x" << std::hex
    //                        << cpu.get_reg(rs1) << ") + " << std::dec << imm << " (@0x"
    //                        << std::hex << mem_addr << std::dec << ") -> x" << rd << std::hex
    //                        << " (0x" << data << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_LBU() const
{
    uint32_t mem_addr = 0;
    int rd, rs1;
    int32_t imm = 0;
    uint8_t data;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    mem_addr = imm + cpu.get_reg(rs1);
    data = cpu.data_read8(mem_addr);
    cpu.set_reg(rd, static_cast<int32_t>(data));

    // Log::out() << "LBU: x" << rs1 << " + " << imm << " (@0x" << std::hex << mem_addr
    //                        << std::dec << ") -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_LHU()
{
    uint32_t mem_addr = 0;
    int rd, rs1;
    int32_t imm = 0;
    uint16_t data;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    mem_addr = imm + cpu.get_reg(rs1);
    if (mem_addr & 1) {
        cpu.raise_exception(EXCEPTION_CAUSE_LOAD_MISALIGN, mem_addr);
        return false;
    }
    data = cpu.data_read16(mem_addr);
    cpu.set_reg(rd, data);

    // Log::out() << "LHU: x" << std::dec << rs1 << " + " << imm << " (@0x" << std::hex
    //                        << mem_addr << std::dec << ") -> x" << rd << "(0x" << std::hex
    //                        << data << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_SB() const
{
    uint32_t mem_addr = 0;
    int rs1, rs2;
    int32_t imm = 0;
    uint32_t data;

    rs1 = get_rs1();
    rs2 = get_rs2();
    imm = get_imm_S();

    mem_addr = imm + cpu.get_reg(rs1);
    data = cpu.get_reg(rs2);

    cpu.data_write8(mem_addr, data);

    // Log::out() << "SB: x" << std::dec << rs2 << " -> x" << rs1 << " + 0x"
    //                       << std::hex << imm << " (@0x" << std::hex << mem_addr << std::dec
    //                       << ")" << std::endl;

    return true;
}

bool Base_Instructions::Exec_SH()
{
    uint32_t mem_addr = 0;
    int rs1, rs2;
    int32_t imm = 0;
    uint32_t data;

    rs1 = get_rs1();
    rs2 = get_rs2();
    imm = get_imm_S();

    mem_addr = imm + cpu.get_reg(rs1);
    if (mem_addr & 1) {
        cpu.raise_exception(EXCEPTION_CAUSE_STORE_MISALIGN, mem_addr);
        return false;
    }
    data = cpu.get_reg(rs2);

    cpu.data_write16(mem_addr, data);

    // Log::out() << "SH: x" << std::dec << rs2 << " -> x" << rs1 << " + 0x"
    //                       << std::hex << imm << " (@0x" << std::hex << mem_addr << std::dec
    //                       << ")" << std::endl;

    return true;
}

bool Base_Instructions::Exec_SW()
{
    uint32_t mem_addr = 0;
    int rs1, rs2;
    int32_t imm = 0;
    uint32_t data;

    rs1 = get_rs1();
    rs2 = get_rs2();
    imm = get_imm_S();

    mem_addr = imm + cpu.get_reg(rs1);
    if (mem_addr & 3) {
        cpu.raise_exception(EXCEPTION_CAUSE_STORE_MISALIGN, mem_addr);
        return false;
    }
    data = cpu.get_reg(rs2);

    cpu.data_write32(mem_addr, data);

    // Log::out() << "SW: x" << std::dec << rs2 << "(0x" << std::hex << data
    //                       << ") -> x" << std::dec << rs1 << " + 0x" << std::hex << imm
    //                       << " (@0x" << std::hex << mem_addr << std::dec << ")" << std::endl;
    return true;
}

bool Base_Instructions::Exec_ADDI() const
{
    int rd, rs1;
    int32_t imm = 0;
    int32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    calc = cpu.get_reg(rs1) + imm;
    cpu.set_reg(rd, calc);

    // Log::out() << "ADDI: x" << std::dec << rs1 << " + " << imm << " -> x"
    //                         << std::dec << rd << "(0x" << std::hex << calc << ")"
    //                         << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_SLTI() const
{
    int rd, rs1;
    int32_t imm;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    if (cpu.get_reg(rs1) < imm) {
        cpu.set_reg(rd, 1);

        // Log::out() << "SLTI: x" << rs1 << " < " << imm << " => "
        //                         << "1 -> x" << rd << std::endl;
    } else {
        cpu.set_reg(rd, 0);

        // Log::out() << "SLTI: x" << rs1 << " < " << imm << " => "
        //                         << "0 -> x" << rd << std::endl;
    }
    return true;
}

bool Base_Instructions::Exec_SLTIU() const
{
    int rd, rs1;
    int32_t imm;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    if ((uint32_t)cpu.get_reg(rs1) < (uint32_t)imm) {
        cpu.set_reg(rd, 1);

        // Log::out() << "SLTIU: x" << rs1 << " < " << imm << " => "
        //                          << "1 -> x" << rd << std::endl;
    } else {
        cpu.set_reg(rd, 0);

        // Log::out() << "SLTIU: x" << rs1 << " < " << imm << " => "
        //                          << "0 -> x" << rd << std::endl;
    }
    return true;
}

bool Base_Instructions::Exec_XORI() const
{
    int rd, rs1;
    int32_t imm;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    calc = cpu.get_reg(rs1) ^ imm;
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "XORI: x" << rs1 << " XOR " << imm << "-> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_ORI() const
{
    int rd, rs1;
    int32_t imm;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    calc = cpu.get_reg(rs1) | imm;
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "ORI: x" << rs1 << " OR " << imm << "-> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_ANDI() const
{
    int rd, rs1;
    uint32_t imm;
    uint32_t calc;
    uint32_t aux;

    rd = get_rd();
    rs1 = get_rs1();
    imm = get_imm_I();

    aux = cpu.get_reg(rs1);
    calc = aux & imm;
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "ANDI: x" << rs1 << "(0x" << std::hex << aux << ") AND 0x" << imm
    //                         << " -> x" << std::dec << rd << "(0x" << std::hex << calc << ")"
    //                         << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_SLLI()
{
    int rd, rs1, rs2;
    uint32_t shift;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_shamt();

    if (rs2 >= 0x20) {
        std::cout << "ILEGAL INSTRUCTION, shamt[5] != 0"
                  << std::endl;
        cpu.raise_exception(EXCEPTION_CAUSE_ILLEGAL_INSTRUCTION, m_instr);

        return false;
    }

    shift = rs2 & 0x1F;

    calc = ((uint32_t)cpu.get_reg(rs1)) << shift;
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "SLLI: x" << std::dec << rs1 << " << " << shift << " -> x" << rd
    //                         << "(0x" << std::hex << calc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_SRLI() const
{
    int rd, rs1, rs2;
    uint32_t shift;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    shift = rs2 & 0x1F;

    calc = ((uint32_t)cpu.get_reg(rs1)) >> shift;
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "SRLI: x" << std::dec << rs1 << " >> " << shift << " -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_SRAI() const
{
    int rd, rs1, rs2;
    uint32_t shift;
    int32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    shift = rs2 & 0x1F;

    calc = cpu.get_reg(rs1) >> shift;
    cpu.set_reg(rd, calc);

    // Log::out() << "SRAI: x" << std::dec << rs1 << " >> " << shift << " -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_ADD() const
{
    int rd, rs1, rs2;
    uint32_t calc;
    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    calc = cpu.get_reg(rs1) + cpu.get_reg(rs2);

    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "ADD: x" << std::dec << rs1 << " + x" << rs2 << " -> x" << rd
    //                        << std::hex << "(0x" << calc << ")" << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_SUB() const
{
    int rd, rs1, rs2;
    uint32_t calc;
    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    calc = cpu.get_reg(rs1) - cpu.get_reg(rs2);
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "SUB: x" << rs1 << " - x" << rs2 << " -> x" << rd << "(" << calc
    //                        << ")" << std::endl;

    return true;
}

bool Base_Instructions::Exec_SLL() const
{
    int rd, rs1, rs2;
    uint32_t shift;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    shift = cpu.get_reg(rs2) & 0x1F;

    calc = ((uint32_t)cpu.get_reg(rs1)) << shift;
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "SLL: x" << rs1 << " << " << shift << " -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_SLT() const
{
    int rd, rs1, rs2;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    if (cpu.get_reg(rs1) < cpu.get_reg(rs2)) {
        cpu.set_reg(rd, 1);

        // Log::out() << "SLT: x" << rs1 << " < x" << rs2 << " => "
        //                        << "1 -> x" << rd << std::endl;
    } else {
        cpu.set_reg(rd, 0);

        // Log::out() << "SLT: x" << rs1 << " < x" << rs2 << " => "
        //                        << "0 -> x" << rd << std::endl;
    }
    return true;
}

bool Base_Instructions::Exec_SLTU() const
{
    int rd, rs1, rs2;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    if ((uint32_t)cpu.get_reg(rs1) < (uint32_t)cpu.get_reg(rs2)) {
        cpu.set_reg(rd, 1);

        // Log::out() << "SLTU: x" << rs1 << " < x" << rs2 << " => "
        //                         << "1 -> x" << rd << std::endl;
    } else {
        cpu.set_reg(rd, 0);

        // Log::out() << "SLTU: x" << rs1 << " < x" << rs2 << " => "
        //                         << "0 -> x" << rd << std::endl;
    }
    return true;
}

bool Base_Instructions::Exec_XOR() const
{
    int rd, rs1, rs2;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    calc = cpu.get_reg(rs1) ^ cpu.get_reg(rs2);
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "XOR: x" << rs1 << " XOR x" << rs2 << "-> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_SRL() const
{
    int rd, rs1, rs2;
    uint32_t shift;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    shift = cpu.get_reg(rs2) & 0x1F;

    calc = ((uint32_t)cpu.get_reg(rs1)) >> shift;
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "SRL: x" << rs1 << " >> " << shift << " -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_SRA() const
{
    int rd, rs1, rs2;
    uint32_t shift;
    int32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    shift = cpu.get_reg(rs2) & 0x1F;

    calc = cpu.get_reg(rs1) >> shift;
    cpu.set_reg(rd, calc);

    // Log::out() << "SRA: x" << rs1 << " >> " << shift << " -> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_OR() const
{
    int rd, rs1, rs2;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    calc = cpu.get_reg(rs1) | cpu.get_reg(rs2);
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "OR: x" << rs1 << " OR x" << rs2 << "-> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_AND() const
{
    int rd, rs1, rs2;
    uint32_t calc;

    rd = get_rd();
    rs1 = get_rs1();
    rs2 = get_rs2();

    calc = cpu.get_reg(rs1) & cpu.get_reg(rs2);
    cpu.set_reg(rd, static_cast<int32_t>(calc));

    // Log::out() << "AND: x" << rs1 << " AND x" << rs2 << "-> x" << rd << std::endl;

    return true;
}

bool Base_Instructions::Exec_FENCE() const
{
    // Log::out() << "FENCE" << std::endl;

    return true;
}

bool Base_Instructions::Exec_ECALL()
{
    // Log::out() << "ECALL" << std::endl;

    uint32_t cause = (cpu.get_priv() == MSTATUS_MPP_MACHINE) ?
                     EXCEPTION_CAUSE_ECALL_M : EXCEPTION_CAUSE_ECALL_U;
    cpu.raise_exception(cause, 0);
    return false;
}

bool Base_Instructions::Exec_EBREAK()
{
    // Log::out() << "EBREAK" << std::endl;

    cpu.raise_exception(EXCEPTION_CAUSE_BREAKPOINT, cpu.get_pc());
    return false;
}

//
// The CSRRW (Atomic Read/Write CSR) instruction atomically swaps values in
// the CSRs and integer registers. CSRRW reads the old value of the CSR,
// zero-extends the value to XLEN bits, then writes it to integer register
// rd. The initial value in rs1 is written to the CSR. If rd=x0, then the
// instruction shall not read the CSR and shall not cause any of the side
// effects that might occur on a CSR read.
//
bool Base_Instructions::Exec_CSRRW() const
{
    int rd, rs1;
    int csr;
    uint32_t dest, source;

    rd = get_rd();
    rs1 = get_rs1();
    csr = get_csr();

    /* These operations must be atomical */
    source = cpu.get_reg(rs1);
    if (rd != 0) {
        dest = cpu.get_csr(csr);
        cpu.set_reg(rd, static_cast<int32_t>(dest));
    }
    cpu.set_csr(csr, source);

    // Log::out() << std::hex << "CSRRW: CSR #" << csr << " -> x" << std::dec << rd
    //                        << ". x" << rs1 << "-> CSR #" << std::hex << csr << " (0x" << source << ")"
    //                        << std::dec << std::endl;

    return true;
}

//
// The CSRRS (Atomic Read and Set Bits in CSR) instruction reads the value
// of the CSR, zero-extends the value to XLEN bits, and writes it to
// integer register rd. The initial value in integer register rs1 is
// treated as a bit mask that specifies bit positions to be set in the CSR.
// Any bit that is high in rs1 will cause the corresponding bit to be set
// in the CSR, if that CSR bit is writable. Other bits in the CSR are not
// explicitly written.
//
bool Base_Instructions::Exec_CSRRS() const
{
    int rd, rs1;
    int csr;
    uint32_t bitmask, aux, aux2;

    rd = get_rd();
    rs1 = get_rs1();
    csr = get_csr();

    if (rd == 0) {
        // Log::out() << "CSRRS with rd1 == 0, doing nothing." << std::endl;
        return false;
    }

    /* These operations must be atomical */
    aux = cpu.get_csr(csr);
    bitmask = cpu.get_reg(rs1);

    cpu.set_reg(rd, static_cast<int32_t>(aux));

    aux2 = aux | bitmask;
    cpu.set_csr(csr, aux2);

    // Log::out() << "CSRRS: CSR #" << csr << "(0x" << std::hex << aux << ") -> x"
    //                              << std::dec << rd << ". x" << rs1 << " & CSR #" << csr << " <- 0x"
    //                              << std::hex << aux2 << std::dec << std::endl;

    return true;
}

//
// The CSRRC (Atomic Read and Clear Bits in CSR) instruction reads the
// value of the CSR, zero-extends the value to XLEN bits, and writes it to
// integer register rd. The initial value in integer register rs1 is
// treated as a bit mask that specifies bit positions to be cleared in the
// CSR. Any bit that is high in rs1 will cause the corresponding bit to be
// cleared in the CSR, if that CSR bit is writable. Other bits in the CSR
// are not explicitly written.
//
bool Base_Instructions::Exec_CSRRC() const
{
    int rd, rs1;
    int csr;
    uint32_t bitmask, aux, aux2;

    rd = get_rd();
    rs1 = get_rs1();
    csr = get_csr();

    if (rd == 0) {
        // Log::out() << "CSRRC with rd1 == 0, doing nothing." << std::endl;
        return true;
    }

    /* These operations must be atomical */
    aux = cpu.get_csr(csr);
    bitmask = cpu.get_reg(rs1);

    cpu.set_reg(rd, static_cast<int32_t>(aux));

    aux2 = aux & ~bitmask;
    cpu.set_csr(csr, aux2);

    // Log::out() << "CSRRC: CSR #" << csr << "(0x" << std::hex << aux << ") -> x"
    //                              << std::dec << rd << ". x" << rs1 << " & CSR #" << csr << " <- 0x"
    //                              << std::hex << aux2 << std::dec << std::endl;

    return true;
}

//
// The CSRRWI, CSRRSI, and CSRRCI variants are similar to CSRRW, CSRRS, and
// CSRRC respectively, except they update the CSR using an XLEN-bit value
// obtained by zero-extending a 5-bit unsigned immediate (uimm[4:0]) field
// encoded in the rs1 field instead of a value from an integer register.
// For CSRRSI and CSRRCI, if the uimm[4:0] field is zero, then these
// instructions will not write to the CSR, and shall not cause any of the
// side effects that might otherwise occur on a CSR write, nor raise
// illegal instruction exceptions on accesses to read-only CSRs. For
// CSRRWI, if rd=x0, then the instruction shall not read the CSR and shall
// not cause any of the side effects that might occur on a CSR read. Both
// CSRRSI and CSRRCI will always read the CSR and cause any read side
// effects regardless of rd and rs1 fields.
//
bool Base_Instructions::Exec_CSRRWI() const
{
    int rd, rs1;
    int csr;
    uint32_t aux;

    rd = get_rd();
    rs1 = get_rs1();
    csr = get_csr();

    /* These operations must be atomical */
    if (rd != 0) {
        aux = cpu.get_csr(csr);
        cpu.set_reg(rd, static_cast<int32_t>(aux));
    }
    aux = rs1;
    cpu.set_csr(csr, aux);

    // Log::out() << "CSRRWI: CSR #" << csr << " -> x" << rd << ". x" << rs1 << "-> CSR #"
    //                               << csr << std::endl;

    return true;
}

bool Base_Instructions::Exec_CSRRSI() const
{
    int rd, rs1;
    int csr;
    uint32_t bitmask, aux;

    rd = get_rd();
    rs1 = get_rs1();
    csr = get_csr();

    if (rs1 == 0) {
        return true;
    }

    /* These operations must be atomical */
    aux = cpu.get_csr(csr);
    cpu.set_reg(rd, static_cast<int32_t>(aux));

    bitmask = rs1;
    aux = aux | bitmask;
    cpu.set_csr(csr, aux);

    // Log::out() << "CSRRSI: CSR #" << csr << " -> x" << rd << ". x" << rs1 << " & CSR #"
    //                               << csr << "(0x" << std::hex << aux << ")"
    //                               << std::dec << std::endl;

    return true;
}

bool Base_Instructions::Exec_CSRRCI() const
{
    int rd, rs1;
    int csr;
    uint32_t bitmask, aux;

    rd = get_rd();
    rs1 = get_rs1();
    csr = get_csr();

    if (rs1 == 0) {
        return true;
    }

    /* These operations must be atomical */
    aux = cpu.get_csr(csr);
    cpu.set_reg(rd, static_cast<int32_t>(aux));

    bitmask = rs1;
    aux = aux & ~bitmask;
    cpu.set_csr(csr, aux);

    // Log::out() << "CSRRCI: CSR #" << csr << " -> x" << rd << ". x" << rs1 << " & CSR #"
    //                               << csr << "(0x" << std::hex << aux << ")"
    //                               << std::dec << std::endl;

    return true;
}

/*********************** Privileged Instructions ******************************/

bool Base_Instructions::Exec_MRET() const
{
    uint32_t new_pc = 0;

    new_pc = cpu.get_csr(CSR_MEPC);
    cpu.set_pc(new_pc);

    // Log::out() << "MRET: PC <- 0x" << std::hex << new_pc << std::dec << std::endl;

    // update mstatus
    uint32_t csr_temp;
    csr_temp = cpu.get_csr(CSR_MSTATUS);
    if (csr_temp & MSTATUS_MPIE) {
        csr_temp |= MSTATUS_MIE;
    }
    csr_temp |= MSTATUS_MPIE;
    cpu.set_csr(CSR_MSTATUS, csr_temp);

    return true;
}

bool Base_Instructions::Exec_WFI() const
{
    // Log::out() << "WFI" << std::endl;

    return true;
}

bool Base_Instructions::Exec_SFENCE() const
{
    // Log::out() << "SFENCE" << std::endl;

    return true;
}

bool Base_Instructions::process_instruction(uint32_t instruction, bool *breakpoint)
{
    bool PC_not_affected = true;

    *breakpoint = false;
    setInstr(instruction);

    switch (decode()) {
    case OP_LUI:
        Exec_LUI();
        break;
    case OP_AUIPC:
        Exec_AUIPC();
        break;
    case OP_JAL:
        Exec_JAL();
        PC_not_affected = false;
        break;
    case OP_JALR:
        Exec_JALR();
        PC_not_affected = false;
        break;
    case OP_BEQ:
        Exec_BEQ();
        PC_not_affected = false;
        break;
    case OP_BNE:
        Exec_BNE();
        PC_not_affected = false;
        break;
    case OP_BLT:
        Exec_BLT();
        PC_not_affected = false;
        break;
    case OP_BGE:
        Exec_BGE();
        PC_not_affected = false;
        break;
    case OP_BLTU:
        Exec_BLTU();
        PC_not_affected = false;
        break;
    case OP_BGEU:
        Exec_BGEU();
        PC_not_affected = false;
        break;
    case OP_LB:
        Exec_LB();
        break;
    case OP_LH:
        PC_not_affected = Exec_LH();
        break;
    case OP_LW:
        PC_not_affected = Exec_LW();
        break;
    case OP_LBU:
        Exec_LBU();
        break;
    case OP_LHU:
        PC_not_affected = Exec_LHU();
        break;
    case OP_SB:
        Exec_SB();
        break;
    case OP_SH:
        PC_not_affected = Exec_SH();
        break;
    case OP_SW:
        PC_not_affected = Exec_SW();
        break;
    case OP_ADDI:
        Exec_ADDI();
        break;
    case OP_SLTI:
        Exec_SLTI();
        break;
    case OP_SLTIU:
        Exec_SLTIU();
        break;
    case OP_XORI:
        Exec_XORI();
        break;
    case OP_ORI:
        Exec_ORI();
        break;
    case OP_ANDI:
        Exec_ANDI();
        break;
    case OP_SLLI:
        PC_not_affected = Exec_SLLI();
        break;
    case OP_SRLI:
        Exec_SRLI();
        break;
    case OP_SRAI:
        Exec_SRAI();
        break;
    case OP_ADD:
        Exec_ADD();
        break;
    case OP_SUB:
        Exec_SUB();
        break;
    case OP_SLL:
        Exec_SLL();
        break;
    case OP_SLT:
        Exec_SLT();
        break;
    case OP_SLTU:
        Exec_SLTU();
        break;
    case OP_XOR:
        Exec_XOR();
        break;
    case OP_SRL:
        Exec_SRL();
        break;
    case OP_SRA:
        Exec_SRA();
        break;
    case OP_OR:
        Exec_OR();
        break;
    case OP_AND:
        Exec_AND();
        break;
    case OP_FENCE:
        Exec_FENCE();
        break;
    case OP_ECALL:
        Exec_ECALL();
        *breakpoint = true;
        std::cout << "ECALL" << std::endl;
        break;
    case OP_EBREAK:
        Exec_EBREAK();
        *breakpoint = true;
        //std::cout << "EBREAK" << std::endl;
        break;
    case OP_CSRRW:
        Exec_CSRRW();
        break;
    case OP_CSRRS:
        Exec_CSRRS();
        break;
    case OP_CSRRC:
        Exec_CSRRC();
        break;
    case OP_CSRRWI:
        Exec_CSRRWI();
        break;
    case OP_CSRRSI:
        Exec_CSRRSI();
        break;
    case OP_CSRRCI:
        Exec_CSRRCI();
        break;
    case OP_MRET:
        Exec_MRET();
        PC_not_affected = false;
        break;
    case OP_WFI:
        Exec_WFI();
        break;
    case OP_SFENCE:
        Exec_SFENCE();
        break;
    default:
        cpu.terminate_simulation("Wrong instruction");
        break;
    }

    return PC_not_affected;
}

opCodes Base_Instructions::decode()
{
    switch (opcode()) {
    case LUI:
        return OP_LUI;
    case AUIPC:
        return OP_AUIPC;
    case JAL:
        return OP_JAL;
    case JALR:
        return OP_JALR;
    case BEQ:
        switch (get_funct3()) {
        case BEQ_F:
            return OP_BEQ;
        case BNE_F:
            return OP_BNE;
        case BLT_F:
            return OP_BLT;
        case BGE_F:
            return OP_BGE;
        case BLTU_F:
            return OP_BLTU;
        case BGEU_F:
            return OP_BGEU;
        }
        return OP_ERROR;
    case LB:
        switch (get_funct3()) {
        case LB_F:
            return OP_LB;
        case LH_F:
            return OP_LH;
        case LW_F:
            return OP_LW;
        case LBU_F:
            return OP_LBU;
        case LHU_F:
            return OP_LHU;
        }
        return OP_ERROR;
    case SB:
        switch (get_funct3()) {
        case SB_F:
            return OP_SB;
        case SH_F:
            return OP_SH;
        case SW_F:
            return OP_SW;
        }
        return OP_ERROR;
    case ADDI:
        switch (get_funct3()) {
        case ADDI_F:
            return OP_ADDI;
        case SLTI_F:
            return OP_SLTI;
        case SLTIU_F:
            return OP_SLTIU;
        case XORI_F:
            return OP_XORI;
        case ORI_F:
            return OP_ORI;
        case ANDI_F:
            return OP_ANDI;
        case SLLI_F:
            return OP_SLLI;
        case SRLI_F:
            switch (get_funct7()) {
            case SRLI_F7:
                return OP_SRLI;
            case SRAI_F7:
                return OP_SRAI;
            }
            return OP_ERROR;
        }
        return OP_ERROR;
    case ADD: {
        switch (get_funct3()) {
        case ADD_F:
            switch (get_funct7()) {
            case ADD_F7:
                return OP_ADD;
            case SUB_F7:
                return OP_SUB;
            default:
                return OP_ADD;
            }
            break;
        case SLL_F:
            return OP_SLL;
        case SLT_F:
            return OP_SLT;
        case SLTU_F:
            return OP_SLTU;
        case XOR_F:
            return OP_XOR;
        case SRL_F:
            switch (get_funct7()) {
            case SRL_F7:
                return OP_SRL;
            case SRA_F7:
                return OP_SRA;
            default:
                return OP_ERROR;
            }
        case OR_F:
            return OP_OR;
        case AND_F:
            return OP_AND;
        default:
            return OP_ERROR;
        }
    } /* ADD */
    case FENCE:
        return OP_FENCE;
    case ECALL: {
        switch (get_funct3()) {
        case ECALL_F3:
            switch (get_csr()) {
            case ECALL_F:
                return OP_ECALL;
            case EBREAK_F:
                return OP_EBREAK;
            case URET_F:
                return OP_URET;
            case SRET_F:
                return OP_SRET;
            case MRET_F:
                return OP_MRET;
            case WFI_F:
                return OP_WFI;
            case SFENCE_F:
                return OP_SFENCE;
            }
            if (m_instr.range(31, 25) == 0b0001001) {
                return OP_SFENCE;
            }
            break;
        case CSRRW:
            return OP_CSRRW;
            break;
        case CSRRS:
            return OP_CSRRS;
            break;
        case CSRRC:
            return OP_CSRRC;
            break;
        case CSRRWI:
            return OP_CSRRWI;
            break;
        case CSRRSI:
            return OP_CSRRSI;
            break;
        case CSRRCI:
            return OP_CSRRCI;
            break;
        }
    } break;
    default:
        return OP_ERROR;
    }

    return OP_ERROR;
}

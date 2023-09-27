/*
 * This routine loads a 32-bit ELF binary executable into memory.
 *
 * Copyright (c) 2021 Serge Vakulenko
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "simulator.h"
#include "exec_elf32.h"

void Simulator::read_elf_file(std::string const &filename)
{
    //
    // Open input file.
    // Note that it's automatically closed when the ifstream object is destroyed.
    //
    std::ifstream elf_file;
    elf_file.open(filename, std::ios::in | std::ios::binary);
    if (!elf_file.is_open()) {
        Log::err() << "Cannot open file: " << filename << std::endl;
        SC_REPORT_ERROR("Simulator", "Cannot open file");
        return;
    }

    //
    // Read ELF header, which is at the beginning of the file.
    //
    elf32_ehdr elf_header;
    elf_file.read((char*) &elf_header, sizeof elf_header);
    if (elf_file.fail()) {
        Log::err() << filename << ": Cannot read ELF header" << std::endl;
        SC_REPORT_ERROR("Simulator", "Cannot read ELF header");
        return;
    }

    //
    // Make sure the ELF header is correct.
    //
    if (elf_header.e_ident[EI_MAG0] != ELFMAG0 ||
        elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header.e_ident[EI_MAG2] != ELFMAG2 ||
        elf_header.e_ident[EI_MAG3] != ELFMAG3) {
        SC_REPORT_ERROR("Simulator", "Bad ELF magic");
        return;
    }
    if (elf_header.e_ident[EI_CLASS] != ELFCLASS32) {
        SC_REPORT_ERROR("Simulator", "Bad ELF class");
        return;
    }
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB) {
        SC_REPORT_ERROR("Simulator", "Bad ELF data format, little-endian expected");
        return;
    }
    if (elf_header.e_ident[EI_VERSION] != EV_CURRENT) {
        SC_REPORT_ERROR("Simulator", "Bad ELF Indent version");
        return;
    }
    if (elf_header.e_ident[EI_OSABI] != ELFOSABI_SYSV) {
        SC_REPORT_ERROR("Simulator", "Bad ABI identification");
        return;
    }
    if (elf_header.e_ehsize != sizeof(struct elf32_ehdr)) {
        SC_REPORT_ERROR("Simulator", "Bad ELF header size");
        return;
    }
    if (elf_header.e_type != ET_EXEC) {
        SC_REPORT_ERROR("Simulator", "Not executable");
        return;
    }
    if (elf_header.e_machine != EM_RISCV) {
        SC_REPORT_ERROR("Simulator", "Bad ELF machine");
        return;
    }
    if (elf_header.e_version != EV_CURRENT) {
        SC_REPORT_ERROR("Simulator", "Bad ELF version");
        return;
    }
    if (elf_header.e_phentsize != sizeof(struct elf32_phdr)) {
        SC_REPORT_ERROR("Simulator", "Bad ELF Program Header Entry size");
        return;
    }
    if (elf_header.e_phoff == 0) {
        SC_REPORT_ERROR("Simulator", "Bad ELF Program Header offset");
        return;
    }
    if (elf_header.e_phnum == 0) {
        SC_REPORT_ERROR("Simulator", "Empty Program header");
        return;
    }

    //
    // Read program header.
    //
    std::vector<elf32_phdr> prog_header(elf_header.e_phnum);
    elf_file.seekg(elf_header.e_phoff);
    elf_file.read((char*) prog_header.data(), elf_header.e_phnum * sizeof(elf32_phdr));
    if (elf_file.fail()) {
        SC_REPORT_ERROR("Simulator", "Cannot read Program header");
        return;
    }

    //
    // Read loadable segments.
    //
    for (int i = 0; i < elf_header.e_phnum; i++) {
        // Chooze loadable non-empty segments.
        auto &segm = prog_header[i];
        if (segm.p_type != PT_LOAD || segm.p_memsz <= 0)
            continue;

        if (Log::is_verbose()) {
            if (segm.p_flags & PF_X) {
                // Executable code.
                Log::out() << "Code 0x" << std::hex << segm.p_vaddr
                           << "-0x" << (segm.p_vaddr + segm.p_memsz - 1)
                           << " size " << std::dec << segm.p_memsz << " bytes" << std::endl;

            } else if (segm.p_filesz > 0) {
                // Initialized data.
                Log::out() << "Data 0x" << std::hex << segm.p_vaddr
                           << "-0x" << (segm.p_vaddr + segm.p_filesz - 1)
                           << " size " << std::dec << segm.p_filesz << " bytes" << std::endl;

                if (segm.p_memsz > segm.p_filesz) {
                    // Zeroed data.
                    Log::out() << "BSS  0x" << (segm.p_vaddr + segm.p_filesz)
                               << "-0x" << (segm.p_vaddr + segm.p_memsz - 1)
                               << " size " << std::dec << (segm.p_memsz - segm.p_filesz)
                               << " bytes" << std::endl;
                }
            }
        }

        // Read data from file.
        if (segm.p_filesz > 0) {
            char buf[segm.p_filesz];
            elf_file.seekg(segm.p_offset);
            elf_file.read(buf, segm.p_filesz);
            if (elf_file.fail()) {
                Log::err() << filename << ": cannot read segment #" << i << std::endl;
                SC_REPORT_ERROR("Simulator", "Cannot read segment");
                return;
            }
            if (debug_write((uint8_t*)buf, segm.p_vaddr, segm.p_filesz) != segm.p_filesz) {
                Log::err() << filename << ": cannot write segment #" << i
                           << " to memory at address 0x" << std::hex << segm.p_vaddr
                           << std::dec << std::endl;
                SC_REPORT_ERROR("Simulator", "Cannot write to memory");
                return;
            }
        }

        // Clear BSS.
        if (segm.p_memsz > segm.p_filesz) {
            unsigned nbytes = segm.p_memsz - segm.p_filesz;
            unsigned addr = segm.p_vaddr + segm.p_filesz;
            char buf[nbytes];
            std::memset(buf, 0, nbytes);
            if (debug_write((uint8_t*)buf, addr, nbytes) != nbytes) {
                Log::err() << filename << ": cannot clear memory at address 0x"
                           << std::hex << addr << std::dec << std::endl;
                SC_REPORT_ERROR("Simulator", "Cannot clear memory");
                return;
            }
        }
    }

    //
    // Set PC to the entry point.
    //
    entry_address = elf_header.e_entry;
    if (Log::is_verbose()) {
        Log::out() << "Entry address: 0x" << std::hex << entry_address << std::dec << std::endl;
    }
    cpu.set_pc(entry_address);

    //
    // Scan the symbol table to find signature labels.
    //
    if (elf_header.e_shnum > 0) {
        if (elf_header.e_shentsize != sizeof(struct elf32_shdr)) {
            SC_REPORT_ERROR("Simulator", "Bad Section header size");
            return;
        }

        // Load section headers.
        std::vector<elf32_shdr> section_header(elf_header.e_shnum);
        elf_file.seekg(elf_header.e_shoff);
        elf_file.read((char*) section_header.data(), elf_header.e_shnum * sizeof(elf32_shdr));
        if (elf_file.fail()) {
            SC_REPORT_ERROR("Simulator", "Cannot read Section header");
            return;
        }

        // Load the string table.
        std::vector<char> string_table;
        for (size_t i = 0; i < elf_header.e_shnum; i++) {
            if (section_header[i].sh_type == SHT_STRTAB) {
                unsigned num_bytes = section_header[i].sh_size;
                if (num_bytes > 0) {
                    // Load the string table.
                    string_table.resize(num_bytes);
                    elf_file.seekg(section_header[i].sh_offset);
                    elf_file.read((char*) string_table.data(), num_bytes);
                    if (elf_file.fail()) {
                        SC_REPORT_ERROR("Simulator", "Cannot read String table");
                        return;
                    }
                }
                break;
            }
        }

        // Load the symbol table.
        for (size_t i = 0; i < elf_header.e_shnum; i++) {
            if (section_header[i].sh_type == SHT_SYMTAB) {
                if (section_header[i].sh_entsize != sizeof(struct elf32_sym)) {
                    SC_REPORT_ERROR("Simulator", "Bad Symbol Entry size");
                    return;
                }

                unsigned num_symbols = section_header[i].sh_size / section_header[i].sh_entsize;
                if (num_symbols > 0) {

                    // Load the symbol table.
                    std::vector<elf32_sym> symbol_table(num_symbols);
                    elf_file.seekg(section_header[i].sh_offset);
                    elf_file.read((char*) symbol_table.data(), section_header[i].sh_size);
                    if (elf_file.fail()) {
                        SC_REPORT_ERROR("Simulator", "Cannot read Symbol Table header");
                        return;
                    }

                    for (size_t s = 0; s < num_symbols; s++) {
                        if (symbol_table[s].st_name != ELF_SYM_UNDEFINED &&
                            symbol_table[s].st_info == ELF_ST_INFO(STB_GLOBAL, STT_NOTYPE) &&
                            symbol_table[s].st_name < string_table.size()) {

                            // Found a global untyped symbol with valid name.
                            const std::string name = &string_table[symbol_table[s].st_name];
#if 0
                            if (Log::is_verbose()) {
                                Log::out() << "Symbol " << name
                                    << " = 0x" << std::hex << symbol_table[s].st_value << std::dec
                                    << std::endl;
                            }
#endif
                            if (name == "begin_signature") {
                                // Start of signature area in memory.
                                begin_signature = symbol_table[s].st_value;
                            }
                            if (name == "end_signature") {
                                // End of signature area in memory.
                                end_signature = symbol_table[s].st_value;
                            }
                        }
                    }
                }
            }
        }
    }
    if (begin_signature > 0 && end_signature > 0) {
        Log::out() << "Signature found at 0x" << std::hex << begin_signature
                   << "...0x" << end_signature << std::dec << std::endl;
    }
}
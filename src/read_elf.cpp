/*
 * This routine loads a 32-bit ELF binary executable into memory.
 *
 * Copyright (c) 2021 Serge Vakulenko
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "exec_elf32.h"
#include "simulator.h"

static bool open_elf_file(std::string const &filename, std::ifstream &elf_file, elf32_ehdr &elf_header)
{
    //
    // Open input file.
    //
    elf_file.open(filename, std::ios::in | std::ios::binary);
    if (!elf_file.is_open()) {
        Log::err() << "Cannot open file: " << filename << std::endl;
        SC_REPORT_ERROR("Simulator", "Cannot open file");
        return false;
    }

    //
    // Read ELF header, which is at the beginning of the file.
    //
    elf_file.read((char *)&elf_header, sizeof elf_header);
    if (elf_file.fail()) {
        Log::err() << filename << ": Cannot read ELF header" << std::endl;
        SC_REPORT_ERROR("Simulator", "Cannot read ELF header");
        return false;
    }

    //
    // Make sure the ELF header is correct.
    //
    if (elf_header.e_ident[EI_MAG0] != ELFMAG0 || elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header.e_ident[EI_MAG2] != ELFMAG2 || elf_header.e_ident[EI_MAG3] != ELFMAG3) {
        SC_REPORT_ERROR("Simulator", "Bad ELF magic");
        return false;
    }
    if (elf_header.e_ident[EI_CLASS] != ELFCLASS32) {
        SC_REPORT_ERROR("Simulator", "Bad ELF class");
        return false;
    }
    if (elf_header.e_ident[EI_DATA] != ELFDATA2LSB) {
        SC_REPORT_ERROR("Simulator", "Bad ELF data format, little-endian expected");
        return false;
    }
    if (elf_header.e_ident[EI_VERSION] != EV_CURRENT) {
        SC_REPORT_ERROR("Simulator", "Bad ELF Indent version");
        return false;
    }
    if (elf_header.e_ident[EI_OSABI] != ELFOSABI_SYSV) {
        SC_REPORT_ERROR("Simulator", "Bad ABI identification");
        return false;
    }
    if (elf_header.e_ehsize != sizeof(struct elf32_ehdr)) {
        SC_REPORT_ERROR("Simulator", "Bad ELF header size");
        return false;
    }
    if (elf_header.e_type != ET_EXEC) {
        SC_REPORT_ERROR("Simulator", "Not executable");
        return false;
    }
    if (elf_header.e_machine != EM_ARM) {
        // Log::err() << filename << ": Bad ELF machine " << elf_header.e_machine << std::endl;
        SC_REPORT_ERROR("Simulator", "Bad ELF machine");
        return false;
    }
    if (elf_header.e_version != EV_CURRENT) {
        SC_REPORT_ERROR("Simulator", "Bad ELF version");
        return false;
    }
    if (elf_header.e_phentsize != sizeof(struct elf32_phdr)) {
        SC_REPORT_ERROR("Simulator", "Bad ELF Program Header Entry size");
        return false;
    }
    if (elf_header.e_phoff == 0) {
        SC_REPORT_ERROR("Simulator", "Bad ELF Program Header offset");
        return false;
    }
    if (elf_header.e_phnum == 0) {
        SC_REPORT_ERROR("Simulator", "Empty Program header");
        return false;
    }
    return true;
}

std::string Simulator::get_elf_config(std::string const &filename)
{
    std::string config = "linux"; // Assume Linux by default

    //
    // Open input file, read and check ELF header.
    // Note that it's automatically closed when the ifstream object is destroyed.
    //
    std::ifstream elf_file;
    elf32_ehdr elf_header;
    if (open_elf_file(filename, elf_file, elf_header)) {
        if (elf_header.e_entry >= 0x10000000 && elf_header.e_entry <= 0x101fffff) {
            config = "pico";
        }
    }
    return config;
}

void Simulator::read_elf_file(std::string const &filename)
{
    //
    // Open input file, read and check ELF header.
    // Note that it's automatically closed when the ifstream object is destroyed.
    //
    std::ifstream elf_file;
    elf32_ehdr elf_header;
    if (!open_elf_file(filename, elf_file, elf_header)) {
        return;
    }

    //
    // Read program header.
    //
    std::vector<elf32_phdr> prog_header(elf_header.e_phnum);
    elf_file.seekg(elf_header.e_phoff);
    elf_file.read((char *)prog_header.data(), elf_header.e_phnum * sizeof(elf32_phdr));
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
                Log::out() << "Code 0x" << std::hex << segm.p_vaddr << "-0x"
                           << (segm.p_vaddr + segm.p_memsz - 1) << " size " << std::dec
                           << segm.p_memsz << " bytes" << std::endl;

            } else if (segm.p_filesz > 0) {
                // Initialized data.
                Log::out() << "Data 0x" << std::hex << segm.p_vaddr << "-0x"
                           << (segm.p_vaddr + segm.p_filesz - 1) << " size " << std::dec
                           << segm.p_filesz << " bytes" << std::endl;

                if (segm.p_memsz > segm.p_filesz) {
                    // Zeroed data.
                    Log::out() << "BSS  0x" << (segm.p_vaddr + segm.p_filesz) << "-0x"
                               << (segm.p_vaddr + segm.p_memsz - 1) << " size " << std::dec
                               << (segm.p_memsz - segm.p_filesz) << " bytes" << std::endl;
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
            if (debug_write((uint8_t *)buf, segm.p_vaddr, segm.p_filesz) != segm.p_filesz) {
                Log::err() << filename << ": cannot write segment #" << i
                           << " to memory at address 0x" << std::hex << segm.p_vaddr << std::dec
                           << std::endl;
                SC_REPORT_ERROR("Simulator", "Cannot write to memory");
                return;
            }
        }

        // Clear BSS.
        if (segm.p_memsz > segm.p_filesz) {
            unsigned nbytes = segm.p_memsz - segm.p_filesz;
            unsigned addr   = segm.p_vaddr + segm.p_filesz;
            char buf[nbytes];
            std::memset(buf, 0, nbytes);
            if (debug_write((uint8_t *)buf, addr, nbytes) != nbytes) {
                Log::err() << filename << ": cannot clear memory at address 0x" << std::hex << addr
                           << std::dec << std::endl;
                SC_REPORT_ERROR("Simulator", "Cannot clear memory");
                return;
            }
        }
    }

    if (config == "linux") {
        // Get entry address.
        entry_address = elf_header.e_entry & ~1;
        if (Log::is_verbose()) {
            Log::out() << "Entry address: 0x" << std::hex << entry_address << std::dec << std::endl;
        }
    }
}

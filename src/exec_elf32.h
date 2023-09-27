/*-
 * Copyright (c) 1994 The NetBSD Foundation, Inc.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef EXEC_ELF_H_
#define EXEC_ELF_H_

/*
 * ELF Header
 */
#define ELF_NIDENT 16

struct elf32_ehdr {
    uint8_t e_ident[ELF_NIDENT]; /* Id bytes */
    uint16_t e_type;             /* file type */
    uint16_t e_machine;          /* machine type */
    uint32_t e_version;          /* version number */
    uint32_t e_entry;            /* entry point */
    uint32_t e_phoff;            /* Program header table offset */
    uint32_t e_shoff;            /* Section header table offset */
    uint32_t e_flags;            /* Processor flags (currently unused, should be 0) */
    uint16_t e_ehsize;           /* sizeof elf_ehdr */
    uint16_t e_phentsize;        /* Program header entry size */
    uint16_t e_phnum;            /* Number of program headers */
    uint16_t e_shentsize;        /* Section header entry size */
    uint16_t e_shnum;            /* Number of section headers */
    uint16_t e_shstrndx;         /* String table index */
};

/* e_ident offsets */
#define EI_MAG0 0 /* first byte of magic number */
#define ELFMAG0 0x7f
#define EI_MAG1 1 /* second byte of magic number */
#define ELFMAG1 'E'
#define EI_MAG2 2 /* third byte of magic number */
#define ELFMAG2 'L'
#define EI_MAG3 3 /* fourth byte of magic number */
#define ELFMAG3 'F'

#define EI_CLASS     4 /* 5:th byte: File class */
#define ELFCLASSNONE 0 /* Invalid class */
#define ELFCLASS32   1 /* 32-bit objects */
#define ELFCLASS64   2 /* 64-bit objects */
#define ELFCLASSNUM  3

#define EI_DATA     5 /* 6:th byte: Data encoding */
#define ELFDATANONE 0 /* Unknown data format */
#define ELFDATA2LSB 1 /* two's complement, little-endian */
#define ELFDATA2MSB 2 /* two's complement, big-endian */

#define EI_VERSION 6 /* Version number of the ELF specification */
#define EV_NONE    0 /* Invalid version */
#define EV_CURRENT 1 /* Current version */
#define EV_NUM     2

#define EI_OSABI            7   /* Operating system/ABI identification */
#define ELFOSABI_SYSV       0   /* UNIX System V ABI */
#define ELFOSABI_STANDALONE 255 /* Stand-alone (embedded) application */

#define EI_ABIVERSION 8 /* ABI version */

#define EI_PAD 9 /* Start of padding bytes up to EI_NIDENT*/

#define ELFMAG  "\177ELF"
#define SELFMAG 4

/* e_type */
#define ET_NONE 0 /* Unknown file type */
#define ET_REL  1 /* A Relocatable file */
#define ET_EXEC 2 /* An Executable file */
#define ET_DYN  3 /* A Shared object file */
#define ET_CORE 4 /* A Core file */
#define ET_NUM  5

#define ET_LOOS   0xfe00 /* Operating system specific range */
#define ET_HIOS   0xfeff
#define ET_LOPROC 0xff00 /* Processor-specific range */
#define ET_HIPROC 0xffff

/* e_machine */
#define EM_NONE  0   /* No machine */
#define EM_ARM   40  /* 32-bit ARM */
#define EM_RISCV 243 /* RISC-V */
#define EM_NUM   36903

/*
 * ELF Program Header
 */
struct elf32_phdr {
    uint32_t p_type;   /* entry type */
    uint32_t p_offset; /* file offset */
    uint32_t p_vaddr;  /* virtual address */
    uint32_t p_paddr;  /* physical address (reserved, 0) */
    uint32_t p_filesz; /* file size of segment (may be 0) */
    uint32_t p_memsz;  /* memory size of segment (may be 0) */
    uint32_t p_flags;  /* flags */
    uint32_t p_align;  /* memory & file alignment */
};

/* p_type */
#define PT_NULL      0 /* Program header table entry unused */
#define PT_LOAD      1 /* Loadable program segment */
#define PT_DYNAMIC   2 /* Dynamic linking information */
#define PT_INTERP    3 /* Program interpreter */
#define PT_NOTE      4 /* Auxiliary information */
#define PT_SHLIB     5 /* Reserved, unspecified semantics */
#define PT_PHDR      6 /* Entry for header table itself */
#define PT_NUM       7
#define PT_LOPROC    0x70000000 /* Start of processor-specific semantics */
#define PT_HIPROC    0x7fffffff /* end of processor-specific semantics */
#define PT_GNU_STACK            /* GNU stack extension */

/* p_flags */
#define PF_R 0x4 /* Segment is readable */
#define PF_W 0x2 /* Segment is writable */
#define PF_X 0x1 /* Segment is executable */
/* A text segment commonly have PF_X|PF_R, a data segment PF_X|PF_W and PF_R */

#define PF_MASKOS   0x0ff00000 /* Opersting system specific values */
#define PF_MASKPROC 0xf0000000 /* Processor-specific values */

#define PT_MIPS_REGINFO 0x70000000

/*
 * Section Headers
 */
struct elf32_shdr {
    uint32_t sh_name;      /* section name (.shstrtab index) */
    uint32_t sh_type;      /* section type */
    uint32_t sh_flags;     /* section flags */
    uint32_t sh_addr;      /* virtual address */
    uint32_t sh_offset;    /* file offset */
    uint32_t sh_size;      /* section size */
    uint32_t sh_link;      /* link to another */
    uint32_t sh_info;      /* misc info */
    uint32_t sh_addralign; /* memory alignment */
    uint32_t sh_entsize;   /* table entry size */
};

/* sh_type */
#define SHT_NULL     0  /* inactive */
#define SHT_PROGBITS 1  /* program defined contents */
#define SHT_SYMTAB   2  /* holds symbol table */
#define SHT_STRTAB   3  /* holds string table */
#define SHT_RELA     4  /* holds relocation info with explicit addends */
#define SHT_HASH     5  /* holds symbol hash table */
#define SHT_DYNAMIC  6  /* holds dynamic linking information */
#define SHT_NOTE     7  /* holds information marking */
#define SHT_NOBITS   8  /* holds a section that does not occupy space */
#define SHT_REL      9  /* holds relocation info without explicit addends */
#define SHT_SHLIB    10 /* reserved with unspecified semantics */
#define SHT_DYNSYM   11 /* holds a minimal set of dynamic linking symbols */
#define SHT_NUM      12

#define SHT_LOOS   0x60000000 /* Operating system specific range */
#define SHT_HIOS   0x6fffffff
#define SHT_LOPROC 0x70000000 /* Processor-specific range */
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000 /* Application-specific range */
#define SHT_HIUSER 0xffffffff

/* sh_flags */
#define SHF_WRITE     0x1 /* Section contains writable data */
#define SHF_ALLOC     0x2 /* Section occupies memory */
#define SHF_EXECINSTR 0x4 /* Section contains executable insns */

#define SHF_MASKOS   0x0f000000 /* Operating system specific values */
#define SHF_MASKPROC 0xf0000000 /* Processor-specific values */

/*
 * Symbol Table
 */
struct elf32_sym {
    uint32_t st_name;  /* Symbol name (.symtab index) */
    uint32_t st_value; /* value of symbol */
    uint32_t st_size;  /* size of symbol */
    uint8_t st_info;   /* type / binding attrs */
    uint8_t st_other;  /* unused */
    uint16_t st_shndx; /* section index of symbol */
};

/* Symbol Table index of the undefined symbol */
#define ELF_SYM_UNDEFINED 0

/* st_info: Symbol Bindings */
#define STB_LOCAL  0 /* local symbol */
#define STB_GLOBAL 1 /* global symbol */
#define STB_WEAK   2 /* weakly defined global symbol */
#define STB_NUM    3

#define STB_LOOS   10 /* Operating system specific range */
#define STB_HIOS   12
#define STB_LOPROC 13 /* Processor-specific range */
#define STB_HIPROC 15

/* st_info: Symbol Types */
#define STT_NOTYPE  0 /* Type not specified */
#define STT_OBJECT  1 /* Associated with a data object */
#define STT_FUNC    2 /* Associated with a function */
#define STT_SECTION 3 /* Associated with a section */
#define STT_FILE    4 /* Associated with a file name */
#define STT_NUM     5

#define STT_LOOS   10 /* Operating system specific range */
#define STT_HIOS   12
#define STT_LOPROC 13 /* Processor-specific range */
#define STT_HIPROC 15

/* st_info utility macros */
#define ELF_ST_BIND(info)       ((unsigned int)(info) >> 4)
#define ELF_ST_TYPE(info)       ((unsigned int)(info)&0xf)
#define ELF_ST_INFO(bind, type) ((unsigned char)(((bind) << 4) | ((type)&0xf)))

/*
 * Special section indexes
 */
#define SHN_UNDEF 0 /* Undefined section */

#define SHN_LORESERVE 0xff00 /* Start of Reserved range */
#define SHN_ABS       0xfff1 /*  Absolute symbols */
#define SHN_COMMON    0xfff2 /*  Common symbols */
#define SHN_HIRESERVE 0xffff

#define SHN_LOPROC 0xff00 /* Start of Processor-specific range */
#define SHN_HIPROC 0xff1f
#define SHN_LOOS   0xff20 /* Operating system specific range */
#define SHN_HIOS   0xff3f

#define SHN_MIPS_ACOMMON 0xff00
#define SHN_MIPS_TEXT    0xff01
#define SHN_MIPS_DATA    0xff02
#define SHN_MIPS_SCOMMON 0xff03

/*
 * Relocation Entries
 */
struct elf32_rel {
    uint32_t r_offset; /* where to do it */
    uint32_t r_info;   /* index & type of relocation */
};

struct elf32_rela {
    uint32_t r_offset; /* where to do it */
    uint32_t r_info;   /* index & type of relocation */
    int32_t r_addend;  /* adjustment value */
};

/* r_info utility macros */
#define ELF_R_SYM(info)       ((info) >> 8)
#define ELF_R_TYPE(info)      ((info)&0xff)
#define ELF_R_INFO(sym, type) (((sym) << 8) + (unsigned char)(type))

/*
 * Dynamic Section structure array
 */
struct elf32_dyn {
    uint32_t d_tag; /* entry tag value */
    union {
        uint32_t d_ptr;
        uint32_t d_val;
    } d_un;
};

/* d_tag */
#define DT_NULL         0  /* Marks end of dynamic array */
#define DT_NEEDED       1  /* Name of needed library (DT_STRTAB offset) */
#define DT_PLTRELSZ     2  /* Size, in bytes, of relocations in PLT */
#define DT_PLTGOT       3  /* Address of PLT and/or GOT */
#define DT_HASH         4  /* Address of symbol hash table */
#define DT_STRTAB       5  /* Address of string table */
#define DT_SYMTAB       6  /* Address of symbol table */
#define DT_RELA         7  /* Address of Rela relocation table */
#define DT_RELASZ       8  /* Size, in bytes, of DT_RELA table */
#define DT_RELAENT      9  /* Size, in bytes, of one DT_RELA entry */
#define DT_STRSZ        10 /* Size, in bytes, of DT_STRTAB table */
#define DT_SYMENT       11 /* Size, in bytes, of one DT_SYMTAB entry */
#define DT_INIT         12 /* Address of initialization function */
#define DT_FINI         13 /* Address of termination function */
#define DT_SONAME       14 /* Shared object name (DT_STRTAB offset) */
#define DT_RPATH        15 /* Library search path (DT_STRTAB offset) */
#define DT_SYMBOLIC     16 /* Start symbol search within local object */
#define DT_REL          17 /* Address of Rel relocation table */
#define DT_RELSZ        18 /* Size, in bytes, of DT_REL table */
#define DT_RELENT       19 /* Size, in bytes, of one DT_REL entry */
#define DT_PLTREL       20 /* Type of PLT relocation entries */
#define DT_DEBUG        21 /* Used for debugging; unspecified */
#define DT_TEXTREL      22 /* Relocations might modify non-writable seg */
#define DT_JMPREL       23 /* Address of relocations associated with PLT */
#define DT_BIND_NOW     24 /* Process all relocations at load-time */
#define DT_INIT_ARRAY   25 /* Address of initialization function array */
#define DT_FINI_ARRAY   26 /* Size, in bytes, of DT_INIT_ARRAY array */
#define DT_INIT_ARRAYSZ 27 /* Address of termination function array */
#define DT_FINI_ARRAYSZ 28 /* Size, in bytes, of DT_FINI_ARRAY array*/
#define DT_NUM          29

#define DT_LOOS   0x60000000 /* Operating system specific range */
#define DT_HIOS   0x6fffffff
#define DT_LOPROC 0x70000000 /* Processor-specific range */
#define DT_HIPROC 0x7fffffff

/*
 * Auxiliary Vectors
 */
struct elf32_auxinfo {
    uint32_t a_type; /* 32-bit id */
    uint32_t a_v;    /* 32-bit id */
};

/* a_type */
#define AT_NULL        0  /* Marks end of array */
#define AT_IGNORE      1  /* No meaning, a_un is undefined */
#define AT_EXECFD      2  /* Open file descriptor of object file */
#define AT_PHDR        3  /* &phdr[0] */
#define AT_PHENT       4  /* sizeof(phdr[0]) */
#define AT_PHNUM       5  /* # phdr entries */
#define AT_PAGESZ      6  /* PAGESIZE */
#define AT_BASE        7  /* Interpreter base addr */
#define AT_FLAGS       8  /* Processor flags */
#define AT_ENTRY       9  /* Entry address of executable */
#define AT_DCACHEBSIZE 10 /* Data cache block size */
#define AT_ICACHEBSIZE 11 /* Instruction cache block size */
#define AT_UCACHEBSIZE 12 /* Unified cache block size */

/* Vendor specific */
#define AT_MIPS_NOTELF 10 /* XXX a_val != 0 -> MIPS XCOFF executable */

#define AT_SUN_UID  2000 /* euid */
#define AT_SUN_RUID 2001 /* ruid */
#define AT_SUN_GID  2002 /* egid */
#define AT_SUN_RGID 2003 /* rgid */

/* Solaris kernel specific */
#define AT_SUN_LDELF   2004 /* dynamic linker's ELF header */
#define AT_SUN_LDSHDR  2005 /* dynamic linker's section header */
#define AT_SUN_LDNAME  2006 /* dynamic linker's name */
#define AT_SUN_LPGSIZE 2007 /* large pagesize */

/* Other information */
#define AT_SUN_PLATFORM 2008 /* sysinfo(SI_PLATFORM) */
#define AT_SUN_HWCAP    2009 /* process hardware capabilities */
#define AT_SUN_IFLUSH   2010 /* do we need to flush the instruction cache? */
#define AT_SUN_CPU      2011 /* cpu name */
/* ibcs2 emulation band aid */
#define AT_SUN_EMUL_ENTRY  2012 /* coff entry point */
#define AT_SUN_EMUL_EXECFD 2013 /* coff file descriptor */
/* Executable's fully resolved name */
#define AT_SUN_EXECNAME 2014

/*
 * Note Headers
 */
struct elf32_nhdr {
    uint32_t n_namesz;
    uint32_t n_descsz;
    uint32_t n_type;
};

#define ELF_NOTE_TYPE_OSVERSION 1

/* NetBSD-specific note type: Emulation name.  desc is emul name string. */
#define ELF_NOTE_NETBSD_TYPE_EMULNAME 2

/* NetBSD-specific note name and description sizes */
#define ELF_NOTE_NETBSD_NAMESZ 7
#define ELF_NOTE_NETBSD_DESCSZ 4
/* NetBSD-specific note name */
#define ELF_NOTE_NETBSD_NAME "NetBSD\0\0"

/* GNU-specific note name and description sizes */
#define ELF_NOTE_GNU_NAMESZ 4
#define ELF_NOTE_GNU_DESCSZ 4
/* GNU-specific note name */
#define ELF_NOTE_GNU_NAME "GNU\0"

/* GNU-specific OS/version value stuff */
#define ELF_NOTE_GNU_OSMASK  (unsigned int)0xff000000
#define ELF_NOTE_GNU_OSLINUX (unsigned int)0x01000000
#define ELF_NOTE_GNU_OSMACH  (unsigned int)0x00000000

#endif /* EXEC_ELF_H_ */

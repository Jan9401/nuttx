/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef ELF_LOADER_H_
#define ELF_LOADER_H_

#include <openamp/remoteproc.h>
#include <openamp/remoteproc_loader.h>

#if defined __cplusplus
extern "C" {
#endif

/* ELF32 base types - 32-bit. */
typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf32_Word;

/* ELF64 base types - 64-bit. */
typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef int32_t Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
typedef int64_t Elf64_Sxword;

/* Size of ELF identifier field in the ELF file header. */
#define     EI_NIDENT       16

/* ELF32 file header */
typedef struct {
	unsigned char e_ident[EI_NIDENT];
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Addr e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
} Elf32_Ehdr;

/* ELF64 file header */
typedef struct {
	unsigned char e_ident[EI_NIDENT];
	Elf64_Half e_type;
	Elf64_Half e_machine;
	Elf64_Word e_version;
	Elf64_Addr e_entry;
	Elf64_Off e_phoff;
	Elf64_Off e_shoff;
	Elf64_Word e_flags;
	Elf64_Half e_ehsize;
	Elf64_Half e_phentsize;
	Elf64_Half e_phnum;
	Elf64_Half e_shentsize;
	Elf64_Half e_shnum;
	Elf64_Half e_shstrndx;
} Elf64_Ehdr;

/* e_ident */
#define     ET_NONE         0
#define     ET_REL          1	/* Re-locatable file         */
#define     ET_EXEC         2	/* Executable file           */
#define     ET_DYN          3	/* Shared object file        */
#define     ET_CORE         4	/* Core file                 */
#define     ET_LOOS         0xfe00	/* Operating system-specific */
#define     ET_HIOS         0xfeff	/* Operating system-specific */
#define     ET_LOPROC       0xff00	/* remote_proc-specific        */
#define     ET_HIPROC       0xffff	/* remote_proc-specific        */

/* e_machine */
#define     EM_ARM          40	/* ARM/Thumb Architecture    */

/* e_version */
#define     EV_CURRENT      1	/* Current version           */

/* e_ident[] Identification Indexes */
#define     EI_MAG0         0	/* File identification       */
#define     EI_MAG1         1	/* File identification       */
#define     EI_MAG2         2	/* File identification       */
#define     EI_MAG3         3	/* File identification       */
#define     EI_CLASS        4	/* File class                */
#define     EI_DATA         5	/* Data encoding             */
#define     EI_VERSION      6	/* File version              */
#define     EI_OSABI        7	/* Operating system/ABI identification */
#define     EI_ABIVERSION   8	/* ABI version               */
#define     EI_PAD          9	/* Start of padding bytes    */
#define     EI_NIDENT       16	/* Size of e_ident[]         */

/*
 * EI_MAG0 to EI_MAG3 - A file's first 4 bytes hold amagic number, identifying
 * the file as an ELF object file
 */
#define     ELFMAG0         0x7f /* e_ident[EI_MAG0]          */
#define     ELFMAG1         'E'	/* e_ident[EI_MAG1]          */
#define     ELFMAG2         'L'	/* e_ident[EI_MAG2]          */
#define     ELFMAG3         'F'	/* e_ident[EI_MAG3]          */
#define     ELFMAG          "\177ELF"
#define     SELFMAG         4

/*
 * EI_CLASS - The next byte, e_ident[EI_CLASS], identifies the file's class, or
 * capacity.
 */
#define     ELFCLASSNONE    0	/* Invalid class             */
#define     ELFCLASS32      1	/* 32-bit objects            */
#define     ELFCLASS64      2	/* 64-bit objects            */

/*
 * EI_DATA - Byte e_ident[EI_DATA] specifies the data encoding of the
 * remote_proc-specific data in the object file. The following encodings are
 * currently defined.
 */
#define     ELFDATANONE     0	/* Invalid data encoding     */
#define     ELFDATA2LSB     1	/* See Data encodings, below */
#define     ELFDATA2MSB     2	/* See Data encodings, below */

/* EI_OSABI - We do not define an OS specific ABI */
#define     ELFOSABI_NONE   0

/* ELF32 program header */
typedef struct elf32_phdr {
	Elf32_Word p_type;
	Elf32_Off p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_memsz;
	Elf32_Word p_flags;
	Elf32_Word p_align;
} Elf32_Phdr;

/* ELF64 program header */
typedef struct elf64_phdr {
	Elf64_Word p_type;
	Elf64_Word p_flags;
	Elf64_Off p_offset;
	Elf64_Addr p_vaddr;
	Elf64_Addr p_paddr;
	Elf64_Xword p_filesz;
	Elf64_Xword p_memsz;
	Elf64_Xword p_align;
} Elf64_Phdr;

/* segment types */
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7               /* Thread local storage segment */
#define PT_LOOS    0x60000000      /* OS-specific */
#define PT_HIOS    0x6fffffff      /* OS-specific */
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff

/* ELF32 section header. */
typedef struct {
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
} Elf32_Shdr;

/* ELF64 section header. */
typedef struct {
	Elf64_Word sh_name;
	Elf64_Word sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	Elf64_Xword sh_size;
	Elf64_Word sh_link;
	Elf64_Word sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
} Elf64_Shdr;

/* sh_type */
#define     SHT_NULL                0
#define     SHT_PROGBITS            1
#define     SHT_SYMTAB              2
#define     SHT_STRTAB              3
#define     SHT_RELA                4
#define     SHT_HASH                5
#define     SHT_DYNAMIC             6
#define     SHT_NOTE                7
#define     SHT_NOBITS              8
#define     SHT_REL                 9
#define     SHT_SHLIB               10
#define     SHT_DYNSYM              11
#define     SHT_INIT_ARRAY          14
#define     SHT_FINI_ARRAY          15
#define     SHT_PREINIT_ARRAY       16
#define     SHT_GROUP               17
#define     SHT_SYMTAB_SHNDX        18
#define     SHT_LOOS                0x60000000
#define     SHT_HIOS                0x6fffffff
#define     SHT_LOPROC              0x70000000
#define     SHT_HIPROC              0x7fffffff
#define     SHT_LOUSER              0x80000000
#define     SHT_HIUSER              0xffffffff

/* sh_flags */
#define     SHF_WRITE       0x1
#define     SHF_ALLOC       0x2
#define     SHF_EXECINSTR   0x4
#define     SHF_MASKPROC    0xf0000000

/* Relocation entry (without addend) */
typedef struct {
	Elf32_Addr r_offset;
	Elf32_Word r_info;
} Elf32_Rel;

typedef struct {
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
} Elf64_Rel;

/* Relocation entry with addend */
typedef struct {
	Elf32_Addr r_offset;
	Elf32_Word r_info;
	Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct elf64_rela {
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
	Elf64_Sxword r_addend;
} Elf64_Rela;

/* Macros to extract information from 'r_info' field of relocation entries */
#define ELF32_R_SYM(i)  ((i) >> 8)
#define ELF32_R_TYPE(i) ((unsigned char)(i))
#define ELF64_R_SYM(i)  ((i) >> 32)
#define ELF64_R_TYPE(i) ((i) & 0xffffffff)

/* Symbol table entry */
typedef struct {
	Elf32_Word st_name;
	Elf32_Addr st_value;
	Elf32_Word st_size;
	unsigned char st_info;
	unsigned char st_other;
	Elf32_Half st_shndx;
} Elf32_Sym;

typedef struct elf64_sym {
	Elf64_Word st_name;
	unsigned char st_info;
	unsigned char st_other;
	Elf64_Half st_shndx;
	Elf64_Addr st_value;
	Elf64_Xword st_size;
} Elf64_Sym;

/* ARM specific dynamic relocation codes */
#define     R_ARM_GLOB_DAT	21	/* 0x15 */
#define     R_ARM_JUMP_SLOT	22	/* 0x16 */
#define     R_ARM_RELATIVE	23	/* 0x17 */
#define     R_ARM_ABS32		2	/* 0x02 */

/* ELF decoding information */
struct elf32_info {
	Elf32_Ehdr ehdr;
	int load_state;
	Elf32_Phdr *phdrs;
	Elf32_Shdr *shdrs;
	void *shstrtab;
};

struct elf64_info {
	Elf64_Ehdr ehdr;
	int load_state;
	Elf64_Phdr *phdrs;
	Elf64_Shdr *shdrs;
	void *shstrtab;
};

#define ELF_STATE_INIT              0x0L
#define ELF_STATE_WAIT_FOR_PHDRS    0x100L
#define ELF_STATE_WAIT_FOR_SHDRS    0x200L
#define ELF_STATE_WAIT_FOR_SHSTRTAB 0x400L
#define ELF_STATE_HDRS_COMPLETE     0x800L
#define ELF_STATE_MASK              0xFF00L
#define ELF_NEXT_SEGMENT_MASK       0x00FFL

extern const struct loader_ops elf_ops;

/**
 * elf_identify - check if it is an ELF file
 *
 * It will check if the input image header is an ELF header.
 *
 * @img_data: firmware private data which will be passed to user defined loader
 *            operations
 * @len: firmware header length
 *
 * return 0 for success or negative value for failure.
 */
int elf_identify(const void *img_data, size_t len);


#if defined __cplusplus
}
#endif

#endif /* ELF_LOADER_H_ */

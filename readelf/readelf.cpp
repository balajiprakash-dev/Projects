/*
 * DEFINES AND STRUCTS COPIED FROM https://refspecs.linuxfoundation.org/elf/elf.pdf
 * BINARY SAMEPLE FROM https://github.com/JonathanSalwan/binary-samples/tree/master
 */
#include <iostream>
#include <cstdint>
#include <fstream>

using namespace std;

typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Word;
typedef uint32_t Elf32_Off;

#define EI_NIDENT 16 // Size of e_ident[]

// Figure 1-3. ELF Header
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

// Figure 1-4. e_ident[] Identification Indexes
#define EI_MAG0 0 // File identification
#define EI_MAG1 1 // File identification
#define EI_MAG2 2 // File identification
#define EI_MAG3 3 // File identification
#define EI_CLASS 4 // File class
#define EI_DATA 5 // Data encoding
#define EI_VERSION 6 // File version
#define EI_PAD 7 // Start of padding bytes

#define ELFMAG0 0x7f        // e_ident[EI_MAG0]
#define ELFMAG1 'E'         // e_ident[EI_MAG1]
#define ELFMAG2 'L'         // e_ident[EI_MAG2]
#define ELFMAG3 'F'         // e_ident[EI_MAG3]

int main(void) {
    
    fstream elf("elf-Linux-ARM64-bash", ios::in | ios::binary);

    Elf32_Ehdr header;

    elf.read(reinterpret_cast<char*>(&header), sizeof(Elf32_Ehdr));
    
    if (header.e_ident[EI_MAG0] == ELFMAG0 && header.e_ident[EI_MAG1] == ELFMAG1 && header.e_ident[EI_MAG2] == ELFMAG2 && header.e_ident[EI_MAG3] == ELFMAG3) {
        cout<<"magic: "<<header.e_ident<<endl;
        cout<<"type: "<<header.e_type<<endl;
        cout<<"machine: "<<header.e_machine<<endl;
        cout<<"version: "<<header.e_version<<endl;
        cout<<"entry point: "<<header.e_entry<<endl;
        cout<<"e_phoff: "<<header.e_phoff<<endl;
        cout<<"e_shoff: "<<header.e_shoff<<endl;
        cout<<"e_flags: "<<header.e_flags<<endl;
    } else {
        cout<<"NOT ELF FILE";
    }

    elf.close();
    
    return 0;
}
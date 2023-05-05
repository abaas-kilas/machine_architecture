// Template for parsing an ELF file to print its symbol table
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>

// The below macros help to prevent errors when doing pointer
// arithmetic. Adding an offset to a pointer is the most common
// operation here while the other macros may not be needed.

#define PTR_PLUS_BYTES(ptr,off) ((void *) (((size_t) (ptr)) + ((size_t) (off))))
// macro to add a byte offset to a pointer, arguments are a pointer
// and a # of bytes (usually size_t)

#define PTR_MINUS_BYTES(ptr,off) ((void *) (((size_t) (ptr)) - ((size_t) (off))))
// macro to subtract a byte offset from a pointer, arguments are a pointer
// and a # of bytes (usually size_t)

#define PTR_MINUS_PTR(ptr,ptq) ((long) (((size_t) (ptr)) - ((size_t) (ptq))))
// macro to subtract one pointer from another

int DEBUG = 0;                  
// Controls whether to print debug messages
// Can be used in conditionals like if(DEBUG){ ... }
// and running 'showsym -d x.o' will set DEBUG=1

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s [-d] <file>\n",argv[0]);
    return 0;
  }

  char *objfile_name = argv[1];

  // check for debug mode
  if(argc >=3){
    if(strcmp("-d",argv[1])==0){
      DEBUG = 1;
      objfile_name = argv[2];
    }
    else{
      printf("incorrect usage\n");
      return 1;
    }
  }
                        
  // Open file descriptor and set up memory map for objfile_name
  int fd = open(objfile_name, O_RDONLY);
  struct stat st_buff;
  fstat(fd, &st_buff);
  unsigned long size = st_buff.st_size;
  char *file = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

  // CREATE A POINTER to the intial bytes of the file which are an ELF64_Ehdr struct
  Elf64_Ehdr *ehdr = (Elf64_Ehdr *) file;

  // CHECK e_ident field's bytes 0 to 4 for the sequence {0x7f,'E','L','F'}
  int match = ehdr->e_ident[0]==0x7f && ehdr->e_ident[1]=='E' && ehdr->e_ident[2]=='L' && ehdr->e_ident[3]=='F';

  // Exit the program with code 1 if the bytes do not match
  if(!match){
    printf("ERROR: Magic bytes wrong, this is not an ELF file");
    exit(1);
  }

  // PROVIDED: check for a 64-bit file
  if(ehdr->e_ident[EI_CLASS] != ELFCLASS64){
    printf("Not a 64-bit file ELF file\n");
    return 1;
  }

  // PROVIDED: check for x86-64 architecture
  if(ehdr->e_machine != EM_X86_64){
    printf("Not an x86-64 file\n");
    return 1;
  }

  // DETERMINE THE OFFSET of the Section Header Array (e_shoff), the
  // number of sections (e_shnum), and the index of the Section Header
  // String table (e_shstrndx). These fields are from the ELF File
  // Header.
  long shdr_offset = ehdr->e_shoff;
  short shdr_len = ehdr->e_shnum;
  short stbl_offset = ehdr->e_shstrndx;

  // Set up a pointer to the array of section headers. Use the section
  // header string table index to find its byte position in the file
  // and set up a pointer to it.
  Elf64_Shdr *sec_hdrs = PTR_PLUS_BYTES(file,shdr_offset);
  Elf64_Shdr *stbl_hdr = sec_hdrs+stbl_offset; // intermediate pointer to string table section header
  char *sec_names = PTR_PLUS_BYTES(file,stbl_hdr->sh_offset);
  

  // Search the Section Header Array for the secion with name .symtab
  // (symbol table) and .strtab (string table).  Note their positions
  // in the file (sh_offset field).  Also note the size in bytes
  // (sh_size) and and the size of each entry (sh_entsize) for .symtab
  // so its number of entries can be computed.
  long symbols=-1,strings=-1,sym_size,sym_entsize,sym_ent; // relevant variables
  
  for(int i=0; i<shdr_len; i++){
    int name_off=sec_hdrs[i].sh_name;
    char *name=PTR_PLUS_BYTES(sec_names,name_off);
    if(strcmp(name,".symtab")==0){
      symbols=sec_hdrs[i].sh_offset;
      sym_size=sec_hdrs[i].sh_size;         // total size
      sym_entsize=sec_hdrs[i].sh_entsize;   // entry size
      sym_ent=sym_size/sym_entsize;         // num of entries (total size/entry size)
    }
    if(strcmp(name,".strtab")==0){
      strings=sec_hdrs[i].sh_offset;
    }
  }

  // END program in cases where ELF files have no symbol or string table
  if(symbols==-1){
    printf("ERROR: Couldn't find symbol table\n");
    return 1;
  }
  if(strings==-1){
    printf("ERROR: Couldn't find string table\n");
    return 1;
  }

  // PRINT byte information about where the symbol table was found and
  // its sizes. The number of entries in the symbol table can be
  // determined by dividing its total size in bytes by the size of
  // each entry.
  printf("Symbol Table\n");
  printf("- %ld bytes offset from start of file\n",symbols);
  printf("- %ld bytes total size\n",sym_size);
  printf("- %ld bytes per entry\n",sym_entsize);
  printf("- %ld entries\n",sym_ent);


  // Set up pointers to the Symbol Table and associated String Table
  // using offsets found earlier.
  Elf64_Sym *symbol_tbl = (Elf64_Sym *) PTR_PLUS_BYTES(file,symbols);
  char *string_tbl = PTR_PLUS_BYTES(file,strings);


  // Print column IDs for info on each symbol
  printf("[%3s]  %8s %4s %s\n",
         "idx","TYPE","SIZE","NAME");

  // Iterate over the symbol table entries
  for(int i=0; i<sym_ent; i++){
    
    // Determine size of symbol and name. Use <NONE> name has zero
    // length.
    size=symbol_tbl[i].st_size;
    int sym_name_off=symbol_tbl[i].st_name;
    char *sym_name = PTR_PLUS_BYTES(string_tbl,sym_name_off);
    char name[128] = "";
    if (strlen(sym_name)!=0){
      strcpy(name, sym_name);   // symbol name present
    }
    else{
      strcpy(name, "<NONE>");   // default no name
    }

    // Determine type of symbol. See assignment specification for
    // fields, macros, and definitions related to this.
    unsigned char typec = ELF64_ST_TYPE(symbol_tbl[i].st_info); // store type
    char type[64]=""; // store printable string
    if (typec == STT_NOTYPE){
      strcpy(type, "NOTYPE");
    }
    else if (typec == STT_OBJECT){
      strcpy(type, "OBJECT");
    }
    else if (typec == STT_FUNC){
      strcpy(type, "FUNC");
    }
    if (typec == STT_FILE){
      strcpy(type, "FILE");
    }
    if (typec == STT_SECTION){
      strcpy(type, "SECTION");
    }

    // Print symbol information
    printf("[%3d]: %8s %4lu %s\n",i,type,size,name);
  }

  // Unmap file from memory and close associated file descriptor 
  munmap(file,size);
  close(fd);

  return 0;
}

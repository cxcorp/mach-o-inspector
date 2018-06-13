# mach-o inspector

A work-in-progress learning project with the goal of learning about the Mach-O format and brushing up on C. Tested on MacOS 10.13.4.

# Status
The program currently dumps `/bin/mv`'s segments and sections.

```
$ ./inspector

magic: feedfacf
cpu specifier: CPU_TYPE_X86_64
machine specifier: 80000003
type of file: MH_EXECUTE
number of load commands: 00000010
the size of all the load commands: 00000600
flags: 00200085
reserved: 00000000

[0] 0x0 (72 bytes): LC_SEGMENT_64 (0x19), 64-bit segment of this file to be mapped
  ↳ __PAGEZERO, 0 sections
[1] 0x48 (552 bytes): LC_SEGMENT_64 (0x19), 64-bit segment of this file to be mapped
  ↳ __TEXT, 6 sections
    ↳ __text
    ↳ __stubs
    ↳ __stub_helper
    ↳ __const
    ↳ __cstring
    ↳ __unwind_info
[2] 0x270 (472 bytes): LC_SEGMENT_64 (0x19), 64-bit segment of this file to be mapped
  ↳ __DATA, 5 sections
    ↳ __nl_symbol_ptr
    ↳ __got
    ↳ __la_symbol_ptr
    ↳ __bss
    ↳ __common
[3] 0x448 (72 bytes): LC_SEGMENT_64 (0x19), 64-bit segment of this file to be mapped
  ↳ __LINKEDIT, 0 sections
[4] 0x490 (48 bytes): LC_DYLD_INFO_ONLY (0x80000022), compressed dyld information only
[5] 0x4C0 (24 bytes): LC_SYMTAB (0x2), link-edit stab symbol table info
[6] 0x4D8 (80 bytes): LC_DYSYMTAB (0xB), dynamic link-edit symbol table info
[7] 0x528 (32 bytes): LC_LOAD_DYLINKER (0xE), load a dynamic linker
[8] 0x548 (24 bytes): LC_UUID (0x1B), the uuid
[9] 0x560 (16 bytes): LC_VERSION_MIN_MACOSX (0x24), build for MacOSX min OS version
[10] 0x570 (16 bytes): LC_SOURCE_VERSION (0x2A), source version used to build binary
[11] 0x580 (24 bytes): LC_MAIN (0x80000028), replacement for LC_UNIXTHREAD
[12] 0x598 (56 bytes): LC_LOAD_DYLIB (0xC), load a dynamically linked shared library
[13] 0x5D0 (16 bytes): LC_FUNCTION_STARTS (0x26), compressed table of function start addresses
[14] 0x5E0 (16 bytes): LC_DATA_IN_CODE (0x29), table of non-instructions in __text
[15] 0x5F0 (16 bytes): LC_CODE_SIGNATURE (0x1D), local of code signature
```

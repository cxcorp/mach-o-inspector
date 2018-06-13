//
//  cmds.c
//  macho
//
//  Created by Joona Heikkilä on 13.06.2018.
//  Copyright © 2018 corp. All rights reserved.
//

#include <mach-o/loader.h>
#include "cmds.h"

static const struct cmd_description cmdLookup[] = {
    [0x1] = { .name = "LC_SEGMENT", .value = LC_SEGMENT, .description = "segment of this file to be mapped" },
    [0x2] = { .name = "LC_SYMTAB", .value = LC_SYMTAB, .description = "link-edit stab symbol table info" },
    [0x3] = { .name = "LC_SYMSEG", .value = LC_SYMSEG, .description = "link-edit gdb symbol table info (obsolete)" },
    [0x4] = { .name = "LC_THREAD", .value = LC_THREAD, .description = "thread" },
    [0x5] = { .name = "LC_UNIXTHREAD", .value = LC_UNIXTHREAD, .description = "unix thread (includes a stack)" },
    [0x6] = { .name = "LC_LOADFVMLIB", .value = LC_LOADFVMLIB, .description = "load a specified fixed VM shared library" },
    [0x7] = { .name = "LC_IDFVMLIB", .value = LC_IDFVMLIB, .description = "fixed VM shared library identification" },
    [0x8] = { .name = "LC_IDENT", .value = LC_IDENT, .description = "object identification info (obsolete)" },
    [0x9] = { .name = "LC_FVMFILE", .value = LC_FVMFILE, .description = "fixed VM file inclusion (internal use)" },
    [0xa] = { .name = "LC_PREPAGE", .value = LC_PREPAGE, .description = "prepage command (internal use)" },
    [0xb] = { .name = "LC_DYSYMTAB", .value = LC_DYSYMTAB, .description = "dynamic link-edit symbol table info" },
    [0xc] = { .name = "LC_LOAD_DYLIB", .value = LC_LOAD_DYLIB, .description = "load a dynamically linked shared library" },
    [0xd] = { .name = "LC_ID_DYLIB", .value = LC_ID_DYLIB, .description = "dynamically linked shared lib ident" },
    [0xe] = { .name = "LC_LOAD_DYLINKER", .value = LC_LOAD_DYLINKER, .description = "load a dynamic linker" },
    [0xf] = { .name = "LC_ID_DYLINKER", .value = LC_ID_DYLINKER, .description = "dynamic linker identification" },
    [0x10] = { .name = "LC_PREBOUND_DYLIB", .value = LC_PREBOUND_DYLIB, .description = "modules prebound for a dynamically linked shared library" },
    [0x11] = { .name = "LC_ROUTINES", .value = LC_ROUTINES, .description = "image routines" },
    [0x12] = { .name = "LC_SUB_FRAMEWORK", .value = LC_SUB_FRAMEWORK, .description = "sub framework" },
    [0x13] = { .name = "LC_SUB_UMBRELLA", .value = LC_SUB_UMBRELLA, .description = "sub umbrella" },
    [0x14] = { .name = "LC_SUB_CLIENT", .value = LC_SUB_CLIENT, .description = "sub client" },
    [0x15] = { .name = "LC_SUB_LIBRARY", .value = LC_SUB_LIBRARY, .description = "sub library" },
    [0x16] = { .name = "LC_TWOLEVEL_HINTS", .value = LC_TWOLEVEL_HINTS, .description = "two-level namespace lookup hints" },
    [0x17] = { .name = "LC_PREBIND_CKSUM", .value = LC_PREBIND_CKSUM, .description = "prebind checksum" },
    [0x19] = { .name = "LC_SEGMENT_64", .value = LC_SEGMENT_64, .description = "64-bit segment of this file to be mapped" },
    [0x1a] = { .name = "LC_ROUTINES_64", .value = LC_ROUTINES_64, .description = "64-bit image routines" },
    [0x1b] = { .name = "LC_UUID", .value = LC_UUID, .description = "the uuid" },
    [0x1d] = { .name = "LC_CODE_SIGNATURE", .value = LC_CODE_SIGNATURE, .description = "local of code signature" },
    [0x1e] = { .name = "LC_SEGMENT_SPLIT_INFO", .value = LC_SEGMENT_SPLIT_INFO, .description = "local of info to split segments" },
    [0x20] = { .name = "LC_LAZY_LOAD_DYLIB", .value = LC_LAZY_LOAD_DYLIB, .description = "delay load of dylib until first use" },
    [0x21] = { .name = "LC_ENCRYPTION_INFO", .value = LC_ENCRYPTION_INFO, .description = "encrypted segment information" },
    [0x22] = { .name = "LC_DYLD_INFO", .value = LC_DYLD_INFO, .description = "compressed dyld information" },
    [0x24] = { .name = "LC_VERSION_MIN_MACOSX", .value = LC_VERSION_MIN_MACOSX, .description = "build for MacOSX min OS version" },
    [0x25] = { .name = "LC_VERSION_MIN_IPHONEOS", .value = LC_VERSION_MIN_IPHONEOS, .description = "build for iPhoneOS min OS version" },
    [0x26] = { .name = "LC_FUNCTION_STARTS", .value = LC_FUNCTION_STARTS, .description = "compressed table of function start addresses" },
    [0x27] = { .name = "LC_DYLD_ENVIRONMENT", .value = LC_DYLD_ENVIRONMENT, .description = "string for dyld to treat like environment variable" },
    [0x29] = { .name = "LC_DATA_IN_CODE", .value = LC_DATA_IN_CODE, .description = "table of non-instructions in __text" },
    [0x2A] = { .name = "LC_SOURCE_VERSION", .value = LC_SOURCE_VERSION, .description = "source version used to build binary" },
    [0x2B] = { .name = "LC_DYLIB_CODE_SIGN_DRS", .value = LC_DYLIB_CODE_SIGN_DRS, .description = "Code signing DRs copied from linked dylibs" },
    [0x2C] = { .name = "LC_ENCRYPTION_INFO_64", .value = LC_ENCRYPTION_INFO_64, .description = "64-bit encrypted segment information" },
    [0x2D] = { .name = "LC_LINKER_OPTION", .value = LC_LINKER_OPTION, .description = "linker options in MH_OBJECT files" },
    [0x2E] = { .name = "LC_LINKER_OPTIMIZATION_HINT", .value = LC_LINKER_OPTIMIZATION_HINT, .description = "optimization hints in MH_OBJECT files" },
    [0x2F] = { .name = "LC_VERSION_MIN_TVOS", .value = LC_VERSION_MIN_TVOS, .description = "build for AppleTV min OS version" },
    [0x30] = { .name = "LC_VERSION_MIN_WATCHOS", .value = LC_VERSION_MIN_WATCHOS, .description = "build for Watch min OS version" },
    [0x31] = { .name = "LC_NOTE", .value = LC_NOTE, .description = "arbitrary data included within a Mach-O file" },
    [0x32] = { .name = "LC_BUILD_VERSION", .value = LC_BUILD_VERSION, .description = "build for platform min OS version" }
};

static const struct cmd_description cmdLookupReqDyld[] = {
    [0x18] = { .name = "LC_LOAD_WEAK_DYLIB", .value = LC_LOAD_WEAK_DYLIB, .description = "load a dynamically linked shared library that is allowed to be missing (all symbols are weak imported)" },
    [0x1c] = { .name = "LC_RPATH", .value = LC_RPATH, .description = "runpath additions" },
    [0x1f] = { .name = "LC_REEXPORT_DYLIB", .value = LC_REEXPORT_DYLIB, .description = "load and re-export dylib" },
    [0x22] = { .name = "LC_DYLD_INFO_ONLY", .value = LC_DYLD_INFO_ONLY, .description = "compressed dyld information only" },
    [0x23] = { .name = "LC_LOAD_UPWARD_DYLIB", .value = LC_LOAD_UPWARD_DYLIB, .description = "load upward dylib" },
    [0x28] = { .name = "LC_MAIN", .value = LC_MAIN, .description = "replacement for LC_UNIXTHREAD" }
};

const struct cmd_description *cmd_lookup(const uint32_t cmd) {
    const uint32_t isReqDyld = (cmd & LC_REQ_DYLD) == LC_REQ_DYLD;
    const uint32_t value = cmd & ~LC_REQ_DYLD;
    return isReqDyld
        ? &cmdLookupReqDyld[value]
        : &cmdLookup[value];
}

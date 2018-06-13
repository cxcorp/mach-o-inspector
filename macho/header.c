//
//  header.c
//  macho
//
//  Created by Joona Heikkilä on 13.06.2018.
//  Copyright © 2018 corp. All rights reserved.
//

#include "header.h"

#define RET_CASE_STR(TYPE) case TYPE: return #TYPE;

const char *filetype_to_str(const uint32_t filetype) {
    switch (filetype) {
        RET_CASE_STR(MH_OBJECT)
        RET_CASE_STR(MH_EXECUTE)
        RET_CASE_STR(MH_FVMLIB)
        RET_CASE_STR(MH_CORE)
        RET_CASE_STR(MH_PRELOAD)
        RET_CASE_STR(MH_DYLIB)
        RET_CASE_STR(MH_DYLINKER)
        RET_CASE_STR(MH_BUNDLE)
        RET_CASE_STR(MH_DYLIB_STUB)
        RET_CASE_STR(MH_DSYM)
        RET_CASE_STR(MH_KEXT_BUNDLE)
        default: return NULL;
    }
}

const char *cputype_to_str(const cpu_type_t type) {
    switch (type) {
        RET_CASE_STR(CPU_TYPE_ANY)
        RET_CASE_STR(CPU_TYPE_VAX)
        RET_CASE_STR(CPU_TYPE_MC680x0)
        RET_CASE_STR(CPU_TYPE_X86)
        RET_CASE_STR(CPU_TYPE_X86_64)
        RET_CASE_STR(CPU_TYPE_MC98000)
        RET_CASE_STR(CPU_TYPE_HPPA)
        RET_CASE_STR(CPU_TYPE_ARM)
        RET_CASE_STR(CPU_TYPE_ARM64)
        RET_CASE_STR(CPU_TYPE_MC88000)
        RET_CASE_STR(CPU_TYPE_SPARC)
        RET_CASE_STR(CPU_TYPE_I860)
        RET_CASE_STR(CPU_TYPE_POWERPC)
        RET_CASE_STR(CPU_TYPE_POWERPC64)
        default: return NULL;
    }
}

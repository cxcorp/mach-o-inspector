//
//  main.c
//  macho
//
//  Created by Joona Heikkilä on 13.06.2018.
//  Copyright © 2018 corp. All rights reserved.
//

#include <mach-o/loader.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "cmds.h"
#include "header.h"

int main(int argc, const char *argv[]) {
    FILE *file = fopen("/bin/mv", "r");
    if (file == NULL) {
        perror("error opening /bin/mv");
        return 1;
    }
    
    uint32_t magic;
    if (fread(&magic, sizeof(uint32_t), 1, file) != 1) {
        perror("failed to read magic number from file");
        fclose(file);
        return 1;
    }
    
    if (magic != MH_MAGIC_64) {
        fprintf(stderr, "Only files with the MH_MAGIC_64 (%08X) magic literal are supported.", MH_MAGIC_64);
        fclose(file);
        return 1;
    }
    
    struct mach_header_64 header;
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("failed to seek file to read header");
        fclose(file);
        return 1;
    }
    
    if (fread(&header, sizeof(struct mach_header_64), 1, file) != 1) {
        perror("failed to read header from file");
        fclose(file);
        return 1;
    }
    
    printf("magic: %08x\n", header.magic);
    printf("cpu specifier: %s\n", cputype_to_str(header.cputype));
    printf("machine specifier: %08x\n", header.cpusubtype);
    printf("type of file: %s\n", filetype_to_str(header.filetype));
    printf("number of load commands: %08x\n", header.ncmds);
    printf("the size of all the load commands: %08x\n", header.sizeofcmds);
    printf("flags: %08x\n", header.flags);
    printf("reserved: %08x\n", header.reserved);
    puts("");
    
    uint8_t *loadCmds = malloc(header.sizeofcmds);
    if (loadCmds == NULL) {
        fprintf(stderr, "failed to allocate %u bytes for load commands: %s\n", header.sizeofcmds, strerror(errno));
        fclose(file);
        return 1;
    }
    
    if (fread(loadCmds, sizeof(uint8_t), header.sizeofcmds, file) != header.sizeofcmds) {
        perror("failed to read load commands from file");
        free(loadCmds);
        fclose(file);
        return 1;
    }
    
    uint8_t *dataPtr = loadCmds;
    for (size_t cmdsProcessed = 0; cmdsProcessed < header.ncmds; cmdsProcessed++) {
        struct load_command cmd;
        memcpy(&cmd, dataPtr, sizeof(struct load_command));
        const struct cmd_description *desc = cmd_lookup(cmd.cmd);
        
        printf("[%lu] 0x%lX (%u bytes): %s (0x%X), %s\n",
               cmdsProcessed,
               (dataPtr - loadCmds),
               cmd.cmdsize,
               desc->name,
               cmd.cmd,
               desc->description);
        
        if (cmd.cmd == LC_SEGMENT_64) {
            struct segment_command_64 segCmd;
            memcpy(&segCmd, dataPtr, sizeof(struct segment_command_64));
            printf("  ↳ %s, %u sections\n", segCmd.segname, segCmd.nsects);
            
            struct section_64 *section = (struct section_64 *)(dataPtr + sizeof(struct segment_command_64));
            for (size_t i = 0; i < segCmd.nsects; i++) {
                printf("    ↳ %s\n", section[i].sectname);
            }
        }
        
        dataPtr += cmd.cmdsize;
    }
    
    free(loadCmds);
    fclose(file);
    
    return 0;
}

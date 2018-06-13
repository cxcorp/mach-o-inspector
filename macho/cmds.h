//
//  cmds.h
//  macho
//
//  Created by Joona Heikkilä on 13.06.2018.
//  Copyright © 2018 corp. All rights reserved.
//

#ifndef cmds_h
#define cmds_h

#include <stdint.h>

struct cmd_description {
    const char *name;
    const char *description;
    const uint32_t value;
};

const struct cmd_description *cmd_lookup(const uint32_t cmd);

#endif /* cmds_h */

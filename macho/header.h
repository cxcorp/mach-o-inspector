//
//  header.h
//  macho
//
//  Created by Joona Heikkilä on 13.06.2018.
//  Copyright © 2018 corp. All rights reserved.
//

#ifndef header_h
#define header_h

#include <mach-o/loader.h>
#include <stdint.h>

const char *filetype_to_str(const uint32_t filetype);
const char *cputype_to_str(const cpu_type_t type);

#endif /* header_h */

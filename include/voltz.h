// voltz.h
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VOLTZ_H
#define VOLTZ_H

#include "voltz-types.h"
#include "voltz-bytecode.h"

namespace voltz {
    
    const std::nullptr_t nil = NULL;
    
    extern void (*RegisterObjectForName)(Object obj, const char* name);
    extern Object (*GetRegisteredObject)(const char* name);
    
    extern Selector (*GetSelector)(const char* value);
    extern void (*AddSelector)(Selector s);
    
    void StartRuntime(FILE* file);
    
    extern void (*Release)(Object o);
    extern Object (*Retain)(Object o);
    
    extern Object (*SendMessage)(Object target, Selector sel, int64_t argc, ...);
    
    extern Object (*GetStackValue)(int64_t index);
    extern void (*SetStackValue)(int64_t index, Object value);
    
    
    
}

#endif

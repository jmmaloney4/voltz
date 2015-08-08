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
    
    void RegisterObjectForName(Object obj, const char* name);
    Object GetRegisteredObject(const char* name);
    
    Selector GetSelector(const char* value);
    
    void StartRuntime(FILE* file);
    
    void Release(Object o);
    Object Retain(Object o);
    
    Object SendMessage(Object target, Selector sel, int64_t argc, ...);

    void Push(Thread t, Object o);
    Object Pop(Thread t);
}

#endif

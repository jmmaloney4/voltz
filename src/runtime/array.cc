// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

Array BoxArrayAll(int64_t count, Object* value) {
    
    Class arrcls = (Class) GetRegisteredObject("std::Array");
    
    Selector alloc = GetSelector("Allocate():std::Object");
    Selector init = GetSelector("Initialize():std::Object");
    
    Array rv = (Array) SendMsg(arrcls, alloc, 0);
    rv = (Array) SendMsg(rv, init, 0);
    
    rv->count = count;
    rv->value = (Object*) malloc(sizeof(Object) * count);
    
    Selector retain = GetSelector("Retain():std::Object");
    
    for (int64_t k = 0; k < count; k++) {
        rv->value[k] = SendMsg(value[k], retain, 0);
    }
    
    Selector release = GetSelector("Release():std::Void");
    
    SendMsg(arrcls, release, 0);
    SendMsg(alloc, release, 0);
    SendMsg(init, release, 0);
    SendMsg(retain, release, 0);
    SendMsg(release, release, 0);
    
    return rv;
}

Array(*voltz::BoxArray)(int64_t, Object*) = BoxArrayAll;

void InitializeArrayClass() {
    
}


// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <string.h>

using namespace voltz;

String BoxStringPhase1(const char* str) {
    String rv = (String) malloc(sizeof(struct voltz_string));
    rv->isa = StringClass;
    rv->refs = 1;
    rv->weaks = 0;
    rv->value = strdup(str);
    rv->length = strlen(str);
    
    return rv;
}

String BoxStringPhase2(const char* str) {
    Selector alloc = GetSelector("Alloc()");
    Selector init = GetSelector("Init()");
    Selector release = GetSelector("release()");
    
    Class stringClass = (Class) GetRegisteredObject("std::String");
    
    String rv = (String) SendMsg(stringClass, alloc, 0);
    rv = (String) SendMsg(rv, init, 0);
    rv->value = strdup(str);
    rv->length = strlen(str);
    
    SendMsg(alloc, release, 0);
    SendMsg(init, release, 0);
    SendMsg(stringClass, release, 0);
    SendMsg(release, release, 0);
    
    return rv;
}

String (*voltz::BoxString)(const char*) = BoxStringPhase1;

void voltz::StringPhase2() {
    BoxString = BoxStringPhase2;
}

char* UnboxStringPhase1(String value) {
    if (!value) {
        return nullptr;
    }
    return strdup(value->value);
}

char* (*voltz::UnboxString)(String) = UnboxStringPhase1;

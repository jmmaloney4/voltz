// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

String BoxStringPhase1(const char* str) {

    String rv = (String) malloc(sizeof(struct voltz_string));
    rv->isa = StringClass;
    rv->refs = 1;
    rv->weaks = 0;
    rv->value = strdup(str);
    
    return rv;
    
}

String (*voltz::BoxString)(const char*) = BoxStringPhase1;

char* UnboxStringPhase1(String value) {
    return strdup(value->value);
}

char* (*voltz::UnboxString)(String) = UnboxStringPhase1;
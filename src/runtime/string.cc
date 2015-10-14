// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <string.h>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id BoxString(const char* value) {
    id rv            = SendMsg(String, New, 0);
    rv->ivars[0].str = strdup(value);
    rv->ivars[1].num = strlen(value);
    return rv;
}

id (*voltz::BoxString)(const char*) = BoxString;

const char* vz_string_unboxI(id obj) {
    if (obj == nil) {
        return nullptr;
    }
    return strdup(obj->ivars[0].str);
}

const char* (*vz_string_unbox)(id) = vz_string_unboxI;

void vz_string_init() {}
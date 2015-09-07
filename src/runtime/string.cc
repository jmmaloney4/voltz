// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

id vz_string_boxI(const char* value) {
    id strcls = vz_class_get("std::String");
    id rv = vz_msg_send(strcls, "Alloc", 0);
    rv = vz_msg_send(rv, "Init", 0);
    rv->ivars[0].str = strdup(value);
    rv->ivars[1].num = strlen(value);
    return rv;
}

id(*vz_string_box)(const char*) = vz_string_boxI;

const char* vz_string_unboxI(id obj) {
    if (obj == nil) {
        return nullptr;
    }
    return strdup(obj->ivars[0].str);
}

const char*(*vz_string_unbox)(id) = vz_string_unboxI;

void vz_string_init() {
    
}
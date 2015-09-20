// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

id vz_bool_boxI(bool value) {
    id boolcls = vz_class_get("std::Bool");
    id rv = vz_msg_send(boolcls, value ? "True" : "False", 0);
    vz_msg_send(boolcls, "Release", 0);
    return rv;
}

id(*vz_bool_box)(bool) = vz_bool_boxI;

bool vz_bool_unboxI(id obj) {
    if (obj == nil) {
        return false;
    }
    return obj->ivars[0].num != 0;
}

bool (*vz_bool_unbox)(id) = vz_bool_unboxI;

id* vz_array_unboxI(id obj) {
    id count = vz_msg_send(obj, "Count", 0);
    NUM c = vz_num_unbox(count);
    id* rv = (id*) malloc(sizeof(id) * c);
    for (NUM k = 0; k < c; k++) {
        rv[(int64_t)k] = vz_msg_send(obj->ivars[0].obj, "Retain", 0);
    }
    vz_msg_send(count, "Release", 0);
    return rv;
}

id*(*vz_array_unbox)(id) = vz_array_unboxI;
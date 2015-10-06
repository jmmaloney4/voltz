// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

VM VoltzVM;

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
        rv[(int64_t)k] = vz_msg_send(obj->ivars[1].arr[(int64_t)k], "Retain", 0);
    }
    vz_msg_send(count, "Release", 0);
    return rv;
}

id*(*vz_array_unbox)(id) = vz_array_unboxI;

id vz_array_boxI(NUM count, ...) {
    va_list ap;
    va_start(ap, count);
    id rv = vz_array_box_v(count, ap);
    va_end(ap);
    return rv;
}

id (*vz_array_box)(NUM, ...) = vz_array_boxI;

id vz_array_box_vI(NUM count, va_list ap) {
    id* args = (id*) malloc(sizeof(id) * count);
    for (NUM k = 0; k < count; k++) {
        args[(int64_t)k] = va_arg(ap, id);
    }
    
    id rv = vz_array_box_a(count, args);
    free(args);
    return rv;
}

id (*vz_array_box_v)(NUM, va_list) = vz_array_box_vI;

id vz_array_box_aI(NUM count, id* args) {
    id arrcls = vz_class_get("std::Array");
    id rv = vz_msg_send(arrcls, "Alloc", 0);
    rv = vz_msg_send(rv, "Init", 0);
    
    rv->ivars[0].num = count;
    rv->ivars[1].arr = (id*) malloc(sizeof(id) * count);
    for (NUM k = 0; k < count; k++) {
        rv->ivars[1].arr[(int64_t)k] = vz_msg_send(args[(int64_t)k], "Retain", 0);
    }
    
    return rv;
}

id (*vz_array_box_a)(NUM, id*) = vz_array_box_aI;

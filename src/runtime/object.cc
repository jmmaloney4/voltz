// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

id vz_object_alloc(NUM ivars) {
    return (id) malloc(sizeof(struct vz_object) + (sizeof(id) * ivars));
}

id vz_object_getIvarI(id obj, const char* name) {
    SEL n = vz_sel_get(name);
    return vz_object_getIvar_s(obj, n);
}

id vz_object_getIvar_sI(id obj, SEL name) {
    if (obj == nil) {
        return nil;
    }
    
    for (id c = obj->isa; c != nil; c = c->ivars[0].obj) {
        for (NUM k = 0; k < vz_class_ivarc(c); k++) {
            if (vz_class_ivarn(c)[(int64_t)k] == name) {
                return obj->ivars[(int64_t)k].obj;
            }
        }
    }
    
    return nil;
}

void vz_object_setIvarI(id obj, const char* name, id value) {
    vz_object_setIvar_s(obj, vz_sel_get(name), value);
}

void vz_object_setIvar_sI(id obj, SEL name, id value) {
    if (obj == nil) {
        return;
    }
    
    for (id c = obj->isa; c != nil; c = c->ivars[0].obj) {
        for (NUM k = 0; k < vz_class_ivarc(c); k++) {
            if (vz_class_ivarn(c)[(int64_t)k] == name) {
                obj->ivars[(int64_t)k].obj = value;
                
            }
        }
    }
}

id vz_object_getTypeI(id obj) {
    if (obj == nil) {
        return nil;
    }
    return obj->isa;
}

id(*vz_object_getIvar)(id, const char*) = vz_object_getIvarI;
id(*vz_object_getIvar_s)(id, SEL) = vz_object_getIvar_sI;
void(*vz_object_setIvar)(id, const char*, id) = vz_object_setIvarI;
void(*vz_object_setIvar_s)(id, SEL, id) = vz_object_setIvar_sI;


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

id(*vz_object_getIvar)(id obj, const char* name);
id(*vz_object_getIvar_s)(id obj, SEL name);
void(*vz_object_setIvar)(id obj, const char* name, id value);
void(*vz_object_setIvar_s)(id obj, SEL name, id value);
id(*vz_object_getType)(id obj);

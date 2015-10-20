// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id voltz::AllocObject(NUM ivars) {
    return (id) malloc(sizeof(struct vz_object) + (sizeof(id) * ivars));
}

id GetInstanceVariable(id obj, SEL name) {
    if (obj == nil) {
        return nil;
    }

    for (id c = obj->isa; c != nil; c = c->ivars[0].obj) {
        for (NUM k = 0; k < GetClassInstanceVariableCount(c); k++) {
            if (GetClassInstanceVariableNames(c)[(int64_t) k] == name) {
                return obj->ivars[(int64_t) k].obj;
            }
        }
    }

    return nil;
}

id (*voltz::GetInstanceVariable)(id, SEL) = ::GetInstanceVariable;

void SetInstanceVariable(id obj, SEL name, id value) {
    if (obj == nil) {
        return;
    }

    for (id c = obj->isa; c != nil; c = c->ivars[0].obj) {
        for (NUM k = 0; k < GetClassInstanceVariableCount(c); k++) {
            if (GetClassInstanceVariableNames(c)[(int64_t) k] == name) {
                obj->ivars[(int64_t) k].obj = value;
            }
        }
    }
}

void (*voltz::SetInstanceVariable)(id, SEL, id) = ::SetInstanceVariable;

NUM GetNumberInstanceVariable(id obj, SEL name) {
    if (obj == nil) {
        return 0;
    }

    for (id c = obj->isa; c != nil; c = c->ivars[0].obj) {
        for (NUM k = 0; k < GetClassInstanceVariableCount(c); k++) {
            if (GetClassInstanceVariableNames(c)[(int64_t) k] == name) {
                return obj->ivars[(int64_t) k].num;
            }
        }
    }

    return 0;
}

NUM (*voltz::GetNumberInstanceVariable)(id, SEL) = ::GetNumberInstanceVariable;

void SetNumberInstanceVariable(id obj, SEL name, NUM value) {
    if (obj == nil) {
        return;
    }

    for (id c = obj->isa; c != nil; c = c->ivars[0].obj) {
        for (NUM k = 0; k < GetClassInstanceVariableCount(c); k++) {
            if (GetClassInstanceVariableNames(c)[(int64_t) k] == name) {
                obj->ivars[(int64_t) k].num = value;
            }
        }
    }
}

void (*voltz::SetNumberInstanceVariable)(id, SEL,
                                         NUM) = ::SetNumberInstanceVariable;

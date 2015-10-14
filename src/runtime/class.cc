// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <math.h>
#include <mutex>
#include <stdlib.h>
#include <string.h>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id GetClass(const char* name) {
    NUM hash = HashString(name);
    hash = (int64_t) fmod(hash, vz_classTable_size);
    if (hash < 0) {
        hash *= -1;
    }

    VoltzVM.clsmtx.lock();

    for (struct vz_classTable_entry* entry = VoltzVM.classtbl[(int64_t) hash];
         entry != NULL; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            id rv = SendMsg(entry->cls, Retain, 0);
            VoltzVM.clsmtx.unlock();
            return rv;
        }
    }

    VoltzVM.clsmtx.unlock();

    return nil;
}

id (*voltz::GetClass)(const char*) = GetClass;

void RegisterClass(const char* name, id cls) {
    NUM hash = HashString(name);
    hash = fmod(hash, vz_classTable_size);
    if (hash < 0) {
        hash *= -1;
    }

    VoltzVM.clsmtx.lock();

    for (struct vz_classTable_entry* entry = VoltzVM.classtbl[(int64_t) hash];
         entry != NULL; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            entry->cls = SendMsg(cls, Retain, 0);
            VoltzVM.clsmtx.unlock();
            return;
        }
    }

    struct vz_classTable_entry* entry =
        (struct vz_classTable_entry*) malloc(sizeof(vz_classTable_entry));
    entry->cls  = SendMsg(cls, Retain, 0);
    entry->name = strdup(name);
    entry->next = VoltzVM.classtbl[(int64_t) hash];
    VoltzVM.classtbl[(int64_t) hash] = entry;

    VoltzVM.clsmtx.unlock();
}

void (*voltz::RegisterClass)(const char*, id) = RegisterClass;

id GetClassSuper(id cls) {
    if (cls == nil) {
        return nil;
    }
    return cls->ivars[0].obj;
}

id (*voltz::GetClassSuper)(id cls) = GetClassSuper;

const char* GetClassName(id cls) {
    if (cls == nil) {
        return strdup("(null)");
    }
    return strdup(cls->ivars[0].str);
}

const char* (*voltz::GetClassName)(id cls) = GetClassName;

NUM GetClassMethodCount(id cls) {
    if (cls == nil) {
        return 0;
    }
    return cls->ivars[6].num;
}

NUM (*voltz::GetClassMethodCount)(id cls) = GetClassMethodCount;

NUM GetClassInstanceVariableCount(id cls) {
    if (cls == nil) {
        return 0;
    }

    return cls->ivars[2].num;
}

NUM (*voltz::GetClassInstanceVariableCount)(id) = GetClassInstanceVariableCount;

const SEL* GetClassInstanceVariableNames(id cls) {
    if (cls == nil) {
        return nil;
    }

    return cls->ivars[3].sarr;
}

const SEL* (*voltz::GetClassInstanceVariableNames)(id) =
    GetClassInstanceVariableNames;
/*
void vz_class_init() {
    id clscls      = vz_class_get("std::Class");
    id mthdcls     = vz_class_get("std::Method");
    id addprotocol = vz_msg_send(mthdcls, "Alloc", 0);
    id sel         = vz_sel_box(vz_sel_get("AddProtocol:"));
    id imp         = vz_imp_box(vz_def({
        id* tmp = (id*) malloc(sizeof(id) * (self->ivars[4].num + 1));
        for (NUM k = 0; k < self->ivars[4].num; k++) {
            tmp[(int64_t) k] = self->ivars[5].arr[(int64_t) k];
        }
        tmp[(int64_t) self->ivars[4].num] = vz_msg_send(argv[0], "Retain", 0);

        self->ivars[4].num++;

        id* t              = self->ivars[5].arr;
        self->ivars[5].arr = tmp;
        free(t);

        return nil;
    }));
    vz_msg_send(addprotocol, "SetSel:", 1, sel);
    vz_msg_send(addprotocol, "SetImp:", 1, imp);
    vz_msg_send(clscls, "AddMethod:", 1, addprotocol);

    vz_msg_send(clscls, "Release", 0);
    vz_msg_send(mthdcls, "Release", 0);
    vz_msg_send(addprotocol, "Release", 0);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
}
*/

void SetInstanceVariableName(id cls, NUM index, SEL name) {
    cls->ivars[3].sarr[(int64_t) index] = name;
}

void (*vz_class_setIvarName)(id, NUM, SEL) = SetClassInstanceVariableName;

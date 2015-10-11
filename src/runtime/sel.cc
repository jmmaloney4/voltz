// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <mutex>

NUM vz_string_hash(const char* s) {
    int64_t hash = 0;

    for (; *s; ++s) {
        hash += *s;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return (NUM) hash;
}

SEL vz_sel_getI(const char* value) {
    NUM hash = vz_string_hash(value);
    hash = (int64_t) fmod(hash, vz_selTable_size);
    if (hash < 0) {
        hash *= -1;
    }

    VoltzVM.selmtx.lock();

    for (struct vz_selTable_entry* entry = VoltzVM.seltbl[(int64_t) hash];
         entry != NULL; entry = entry->next) {
        if (strcmp(entry->sel->value, value) == 0) {
            VoltzVM.selmtx.unlock();
            return entry->sel;
        }
    }

    struct vz_selTable_entry* entry =
        (vz_selTable_entry*) malloc(sizeof(struct vz_selTable_entry));
    entry->sel        = (SEL) malloc(sizeof(struct vz_sel));
    entry->sel->value = strdup(value);
    entry->next = VoltzVM.seltbl[(int64_t) hash];
    VoltzVM.seltbl[(int64_t) hash] = entry;

    SEL rv = entry->sel;

    VoltzVM.selmtx.unlock();

    return rv;
}

SEL (*vz_sel_get)(const char*) = vz_sel_getI;

id vz_sel_boxI(SEL sel) {
    id selcls = vz_class_get("std::Selector");
    id rv     = vz_msg_send(selcls, "Alloc", 0);
    rv        = vz_msg_send(rv, "Init", 0);

    vz_object_setIvar(rv, "value", (id) sel);

    return rv;
}

id (*vz_sel_box)(SEL) = vz_sel_boxI;

SEL vz_sel_unboxI(id obj) { return (SEL) vz_object_getIvar(obj, "value"); }

SEL (*vz_sel_unbox)(id) = vz_sel_unboxI;

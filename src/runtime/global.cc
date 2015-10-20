// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <mutex>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id GetGlobal(const char* str) {
    NUM hash = HashString(str);
    hash = (int64_t) fmod(hash, vz_globalTable_size);
    if (hash < 0) {
        hash *= -1;
    }

    VoltzVM.globalmtx.lock();

    for (struct vz_globalTable_entry* entry = VoltzVM.globaltbl[(int64_t) hash];
         entry != nil; entry = entry->next) {
        if (strcmp(entry->name, str) == 0) {
            VoltzVM.globalmtx.unlock();
            return SendMsg(entry->value, Retain, 0);
        }
    }

    VoltzVM.globalmtx.unlock();

    return nil;
}

id (*voltz::GetGlobal)(const char*) = GetGlobal;

void SetGlobal(const char* str, id value) {
    NUM hash = HashString(str);
    hash = (int64_t) fmod(hash, vz_globalTable_size);
    if (hash < 0) {
        hash *= -1;
    }

    VoltzVM.globalmtx.lock();

    for (struct vz_globalTable_entry* entry = VoltzVM.globaltbl[(int64_t) hash];
         entry != nil; entry = entry->next) {
        if (strcmp(entry->name, str) == 0) {
            id t         = entry->value;
            entry->value = SendMsg(value, Retain, 0);
            SendMsg(t, Release, 0);
        }
    }

    struct vz_globalTable_entry* entry = (struct vz_globalTable_entry*) malloc(
        sizeof(struct vz_globalTable_entry));
    entry->name  = strdup(str);
    entry->value = SendMsg(value, Retain, 0);
    entry->next = VoltzVM.globaltbl[(int64_t) hash];
    VoltzVM.globaltbl[(int64_t) hash] = entry;

    VoltzVM.globalmtx.unlock();
}

void (*voltz::SetGlobal)(const char*, id) = SetGlobal;

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

struct vz_globalTable_entry {
    id value;
    const char* name;
    struct vz_globalTable_entry* next;
};

#define vz_globalTable_size 0x500
struct vz_globalTable_entry* vz_globalTable[vz_globalTable_size];
std::mutex vz_globalTable_mutex;

id vz_global_getI(const char* str) {
    NUM hash = vz_string_hash(str);
    hash = (int64_t) fmod(hash, vz_globalTable_size);
    if (hash < 0) {
        hash *= -1;
    }

    for (struct vz_globalTable_entry* entry = vz_globalTable[(int64_t) hash];
         entry != nil;
         entry = entry->next) {
        if (strcmp(entry->name, str) == 0) {
            return vz_msg_send(entry->value, "Retain", 0);
        }
    }

    return nil;
}

id (*vz_global_get)(const char*) = vz_global_getI;

void vz_global_setI(const char* str, id value) {
    NUM hash = vz_string_hash(str);
    hash = (int64_t) fmod(hash, vz_globalTable_size);
    if (hash < 0) {
        hash *= -1;
    }

    for (struct vz_globalTable_entry* entry = vz_globalTable[(int64_t) hash];
         entry != nil;
         entry = entry->next) {
        if (strcmp(entry->name, str) == 0) {
            id t         = entry->value;
            entry->value = vz_msg_send(value, "Retain", 0);
            vz_msg_send(t, "Release", 0);
        }
    }

    struct vz_globalTable_entry* entry = (struct vz_globalTable_entry*) malloc(
        sizeof(struct vz_globalTable_entry));
    entry->name  = strdup(str);
    entry->value = vz_msg_send(value, "Retain", 0);
    entry->next = vz_globalTable[(int64_t) hash];
    vz_globalTable[(int64_t) hash] = entry;
}

void (*vz_global_set)(const char*, id) = vz_global_setI;

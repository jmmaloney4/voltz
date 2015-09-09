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

struct vz_classTable_entry {
    id cls;
    struct vz_classTable_entry* next;
};

#define vz_classTable_size 0x500
struct vz_classTable_entry* vz_classTable[vz_classTable_size];
std::mutex vz_classTable_mutex;

id vz_class_getI(const char* name) {
    NUM hash = vz_string_hash(name);
    hash = (int64_t) fmod(hash, vz_classTable_size);
    if (hash < 0) {
        hash *= -1;
    }
    
    vz_classTable_mutex.lock();
    
    for(struct vz_classTable_entry* entry = vz_classTable[(int64_t) hash];
        entry != NULL; entry = entry->next) {
        if (strcmp(entry->cls->ivars[1].str, name) == 0) {
            id rv = entry->cls;
            vz_classTable_mutex.unlock();
            return rv;
        }
    }
    
    vz_classTable_mutex.unlock();
    
    return nil;
}

id(*vz_class_get)(const char*) = vz_class_getI;

void vz_class_registerI(const char* name, id cls) {
    NUM hash = vz_string_hash(name);
    hash = fmod(hash, vz_classTable_size);
    if (hash < 0) {
        hash *= -1;
    }
    
    vz_classTable_mutex.lock();
    
    for(struct vz_classTable_entry* entry = vz_classTable[(int64_t) hash];
        entry != NULL; entry = entry->next) {
        if (strcmp(entry->cls->ivars[1].str, name) == 0) {
            entry->cls = vz_msg_send(cls, "Retain", 0);
            vz_classTable_mutex.unlock();
            return;
        }
    }
    
    struct vz_classTable_entry* entry = (struct vz_classTable_entry*) malloc(sizeof(vz_classTable_entry));
    entry->cls = vz_msg_send(cls, "Retain", 0);
    entry->next = vz_classTable[(int64_t) hash];
    vz_classTable[(int64_t) hash] = entry;
    
    vz_classTable_mutex.unlock();
}

void (*vz_class_register)(const char*, id) = vz_class_registerI;

id vz_class_superI(id cls) {
    if (cls == nil) {
        return nil;
    }
    return cls->ivars[0].obj;
}

id(*vz_class_super)(id cls) = vz_class_superI;

const char* vz_class_nameI(id cls) {
    if (cls == nil) {
        return strdup("");
    }
    return strdup(cls->ivars[0].str);
}

const char* (*vz_class_name)(id cls) = vz_class_nameI;

NUM vz_class_mthdcI(id cls) {
    if (cls == nil) {
        return 0;
    }
    return cls->ivars[6].num;
}

NUM (*vz_class_mthdc)(id cls) = vz_class_mthdcI;

NUM vz_class_ivarcI(id cls) {
    if (cls == nil) {
        return 0;
    }
    
    return cls->ivars[2].num;
}

NUM (*vz_class_ivarc)(id) = vz_class_ivarcI;

const SEL* vz_class_ivarnI(id cls) {
    if (cls == nil) {
        return nil;
    }
    
    return cls->ivars[3].sarr;
}

const SEL* (*vz_class_ivarn)(id) = vz_class_ivarnI;

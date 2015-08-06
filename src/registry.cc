// registry.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"
#include <string.h>
#include <mutex>

using namespace voltz;

// Implemented in selector.cc
int64_t HashString(const char* s);

#define RegistryTableSize 0x1000

struct RegistryTableEntry {
    Object obj;
    const char* name;
    RegistryTableEntry* next;
};

RegistryTableEntry* RegistryTable[RegistryTableSize];
std::mutex RegistryTableMutex;

void voltz::RegisterObjectForName(Object obj, const char* name) {
    int64_t hash = HashString(name);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    RegistryTableMutex.lock();
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            Release(entry->obj);
            Retain(obj);
            entry->obj = obj;
            RegistryTableMutex.unlock();
            return;
        }
    }
    
    RegistryTableEntry* entry = new RegistryTableEntry();
    entry->name = strdup(name);
    entry->obj = Retain(obj);
    entry->next = RegistryTable[hash];
    RegistryTable[hash] = entry;
    
    RegistryTableMutex.unlock();
}

Object voltz::GetRegisteredObject(const char* name) {
    
    int64_t hash = HashString(name);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    RegistryTableMutex.lock();
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            Object rv = Retain(entry->obj);
            RegistryTableMutex.unlock();
            return rv;
        }
    }
    
    RegistryTableMutex.unlock();
    
    return nullptr;
}

// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

#define RegistryTableSize 0x1000

struct RegistryTableEntry {
    Object obj;
    const char* name;
    RegistryTableEntry* next;
};

RegistryTableEntry* RegistryTable[RegistryTableSize];

void RegisterObjectPhase1(Object obj, String name) {
    
    int64_t hash = HashString(name->value);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != nil; entry = entry->next) {
        if (strcmp(entry->name, name->value) == 0) {
            Release(entry->obj);
            entry->obj = Retain(obj);
            return;

        }
    }
    
    RegistryTableEntry* entry = (RegistryTableEntry*) malloc(sizeof(struct RegistryTableEntry));
    entry->obj = Retain(obj);
    entry->name = strdup(name->value);
    entry->next = RegistryTable[hash];
    RegistryTable[hash] = entry;
}

void(*voltz::RegisterObject)(Object, String) = RegisterObjectPhase1;

Object GetRegisteredObjectPhase1(String name) {
    
    int64_t hash = HashString(name->value);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != nil; entry = entry->next) {
        if (strcmp(entry->name, name->value) == 0) {
            return Retain(entry->obj);
        }
    }
    
    return nil;
}

Object (*voltz::GetRegisteredObject)(String) = GetRegisteredObjectPhase1;
// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <string.h>

using namespace voltz;

#define RegistryTableSize 0x1000

struct RegistryTableEntry {
    Object obj;
    const char* name;
    RegistryTableEntry* next;
};

RegistryTableEntry* RegistryTable[RegistryTableSize];

void RegisterObjectPhase1(Object obj, const char* name) {
    int64_t hash = HashString(name);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != nil; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            Release(entry->obj);
            entry->obj = Retain(obj);
            return;

        }
    }
    
    RegistryTableEntry* entry = (RegistryTableEntry*) malloc(sizeof(struct RegistryTableEntry));
    entry->obj = Retain(obj);
    entry->name = strdup(name);
    entry->next = RegistryTable[hash];
    RegistryTable[hash] = entry;
}

void RegisterObjectPhase2(Object obj, const char* name) {
    int64_t hash = HashString(name);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    Selector retain = GetSelector("Retain():std::Object");
    Selector release = GetSelector("Release():std::Void");
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != nil; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            SendMsg(entry->obj, release, 0);
            entry->obj = SendMsg(obj, retain, 0);
            
            SendMsg(retain, release, 0);
            SendMsg(release, release, 0);
            
            return;
            
        }
    }
    
    RegistryTableEntry* entry = (RegistryTableEntry*) malloc(sizeof(struct RegistryTableEntry));
    entry->obj = SendMsg(obj, retain, 0);
    entry->name = strdup(name);
    entry->next = RegistryTable[hash];
    RegistryTable[hash] = entry;
    
    SendMsg(retain, release, 0);
    SendMsg(release, release, 0);
}

void(*voltz::RegisterObject)(Object, const char*) = RegisterObjectPhase1;

Object GetRegisteredObjectPhase1(const char* name) {
    int64_t hash = HashString(name);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != nil; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            return Retain(entry->obj);
        }
    }
    
    return nil;
}

Object GetRegisteredObjectPhase2(const char* name) {
    int64_t hash = HashString(name);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= RegistryTableSize;
    
    for (RegistryTableEntry* entry = RegistryTable[hash]; entry != nil; entry = entry->next) {
        if (strcmp(entry->name, name) == 0) {
            Selector retain = GetSelector("Retain():std::Object");
            Object rv = SendMsg(entry->obj, retain, 0);
            return rv;
        }
    }
    
    return nil;
}

Object (*voltz::GetRegisteredObject)(const char*) = GetRegisteredObjectPhase1;

void voltz::RegistryPhase2() {
    RegisterObject = RegisterObjectPhase2;
    GetRegisteredObject = GetRegisteredObjectPhase2;
}

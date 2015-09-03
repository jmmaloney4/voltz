// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <string.h>

using namespace voltz;

int64_t voltz::HashString(const char* s) {
    int64_t hash = 0;
    
    for(; *s; ++s)
    {
        hash += *s;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash;
}

#define SelectorTableSize 0x1000

struct SelectorTableEntry {
    Selector sel;
    SelectorTableEntry* next;
};

SelectorTableEntry* SelectorTable[SelectorTableSize];

Selector GetSelectorPhase1(const char* value) {
    int64_t hash = HashString(value);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= SelectorTableSize;
    
    
    for (SelectorTableEntry* entry = SelectorTable[hash]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->sel->value, value) == 0) {
            return (Selector) Retain(entry->sel);
        }
    }
    
    SelectorTableEntry* entry = (SelectorTableEntry*) malloc(sizeof(SelectorTableEntry));
    entry->sel = (Selector) malloc(sizeof(struct voltz_selector));
    entry->sel->isa = SelectorClass;
    entry->sel->refs = 1;
    entry->sel->weaks = 0;
    entry->sel->value = strdup(value);
    entry->next = SelectorTable[hash];
    SelectorTable[hash] = entry;
    
    return (Selector) Retain(entry->sel);
}

Selector GetSelectorPhase2(const char* value) {
    int64_t hash = HashString(value);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= SelectorTableSize;
    
    for (SelectorTableEntry* entry = SelectorTable[hash]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->sel->value, value) == 0) {
            entry->sel->refs++;
            return entry->sel;
        }
    }
    
    Selector alloc = GetSelector("Allocate():std::Object");
    Selector init = GetSelector("Initialize():std::Object");
    Selector retain = GetSelector("Retain():std::Object");
    Selector release = GetSelector("Release():std::Void");
    
    Class SelectorClass = (Class) GetRegisteredObject("std::Selector");
    
    SelectorTableEntry* entry = (SelectorTableEntry*) malloc(sizeof(SelectorTableEntry));
    entry->sel = (Selector) SendMsg(SelectorClass, alloc, 0);
    entry->sel = (Selector) SendMsg(entry->sel, init, 0);
    entry->sel->value = strdup(value);
    
    entry->next = SelectorTable[hash];
    SelectorTable[hash] = entry;
    
    Selector rv = (Selector) SendMsg(entry->sel, retain, 0);
    
    SendMsg(alloc, release, 0);
    SendMsg(init, release, 0);
    SendMsg(retain, release, 0);
    SendMsg(release, release, 0);
    
    return rv;
}

Selector (*voltz::GetSelector)(const char*) = GetSelectorPhase1;

void voltz::SelectorPhase2() {
    GetSelector = GetSelectorPhase2;
}

void voltz::AddSelector(Selector sel) {
    int64_t hash = HashString(sel->value);
    if (hash < 0) {
        hash *= -1;
    }
    hash %= SelectorTableSize;
    
    
    for (SelectorTableEntry* entry = SelectorTable[hash]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->sel->value, sel->value) == 0) {
            fprintf(stderr, "Selector Already in Table\n");
            abort();
        }
    }
    
    SelectorTableEntry* entry = (SelectorTableEntry*) malloc(sizeof(SelectorTableEntry));
    entry->sel = (Selector) malloc(sizeof(struct voltz_selector));
    entry->sel = (Selector) Retain(sel);
    entry->next = SelectorTable[hash];
    SelectorTable[hash] = entry;
}

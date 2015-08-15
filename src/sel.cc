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

Selector (*voltz::GetSelector)(const char*) = GetSelectorPhase1;

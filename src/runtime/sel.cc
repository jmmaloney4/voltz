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

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

SEL selectors::Alloc;
SEL selectors::Init;
SEL selectors::Retain;
SEL selectors::Release;
SEL selectors::AddMethod_;
SEL selectors::New;
SEL selectors::Deinit;
SEL selectors::SetSel_;
SEL selectors::SetImp_;
SEL selectors::sel;
SEL selectors::imp;
SEL selectors::Init__;
SEL selectors::New__;
SEL selectors::Subclass___;
SEL selectors::Register;
SEL selectors::Isa;
SEL selectors::True;
SEL selectors::False;
SEL selectors::Count;
SEL selectors::value;
SEL selectors::ResolveMessageSend__;
SEL selectors::UnrecognizedSelector_;

void voltz::InitSelectors() {
    Alloc                 = GetSelector("Alloc");
    Init                  = GetSelector("Init");
    Retain                = GetSelector("Retain");
    Release               = GetSelector("Release");
    AddMethod_            = GetSelector("AddMethod:");
    New                   = GetSelector("New");
    Deinit                = GetSelector("Deinit");
    SetSel_               = GetSelector("SetSel:");
    SetImp_               = GetSelector("SetImp:");
    sel                   = GetSelector("sel");
    imp                   = GetSelector("imp");
    Init__                = GetSelector("Init::");
    New__                 = GetSelector("New::");
    Subclass___           = GetSelector("Subclass:::");
    Register              = GetSelector("Register");
    Isa                   = GetSelector("Isa");
    True                  = GetSelector("True");
    False                 = GetSelector("False");
    Count                 = GetSelector("Count");
    value                 = GetSelector("value");
    ResolveMessageSend__  = GetSelector("ResolveMessageSend::");
    UnrecognizedSelector_ = GetSelector("UnrecognizedSelector:");
}

NUM voltz::HashString(const char* s) {
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

SEL GetSelector(const char* value) {
    NUM hash = HashString(value);
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

SEL (*voltz::GetSelector)(const char*) = ::GetSelector;

id BoxSelector(SEL sel) {
    id rv = SendMsg(Selector, Alloc, 0);
    SetInstanceVariable(rv, value, (id) sel);
    return rv;
}

id (*voltz::BoxSelector)(SEL) = ::BoxSelector;

SEL UnboxSelector(id obj) { return (SEL) GetInstanceVariable(obj, value); }

SEL (*voltz::UnboxSelector)(id) = ::UnboxSelector;

// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

//                      neg   0 + pos
Int voltz::InternedInts[0x20 + 0xff];

Int BoxIntPhase1(int64_t value) {
    if (value >= -0x20 && value < 0xff) {
        return (Int) Retain(InternedInts[value + 0x20]);
    }

    Int rv = (Int) malloc(sizeof(struct voltz_int));
    rv->isa = IntClass;
    rv->refs = 1;
    rv->weaks = 0;
    rv->value = value;

    return rv;
}

Int (*voltz::BoxInt)(int64_t) = BoxIntPhase1;

Int BoxIntPhase2(int64_t value) {
    if (value >= -0x20 && value < 0xff) {
        Selector retain = GetSelector("Retain():std::Object");
        Int rv = (Int) SendMsg(InternedInts[value + 0x20], retain, 0);
        Selector release = GetSelector("Release():std::Void");
        SendMsg(retain, release, 0);
        SendMsg(release, release, 0);
        return rv;
    }

    Class IntClass = (Class) GetRegisteredObject("std::Int");
    Selector AllocSel = GetSelector("Allocate():std::Object");
    Int rv = (Int) SendMsg(IntClass, AllocSel, 0);

    Selector InitSel = GetSelector("Initialize():std::Object");
    rv = (Int) SendMsg(rv, InitSel, 0);

    rv->value = value;

    Selector releaseSel = GetSelector("Release():std::Void");
    SendMsg(IntClass, releaseSel, 0);
    SendMsg(AllocSel, releaseSel, 0);
    SendMsg(InitSel, releaseSel, 0);
    SendMsg(releaseSel, releaseSel, 0);

    return rv;
}

void voltz::IntPhase2() {
    BoxInt = BoxIntPhase2;
}

int64_t UnboxIntAll(Int value) {
    if (value == nil) {
        return 0;
    }
    return value->value;
}

int64_t (*voltz::UnboxInt)(Int) = UnboxIntAll;

void InitializeIntClass() {

    //Class intcls = GetRegisteredObject("std::Int");



}

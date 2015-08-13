// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

using namespace voltz;

//               neg   0 + pos
Int voltz::InternedInts[0x20 + 0xff];

Int BoxIntImp(int64_t value) {
    if (value >= -0x20 && value < 0xff) {
        return (Int) Retain(InternedInts[value + 0x20]);
    }
    
    String IntClassName = BoxString("std::Int");
    String AllocSelValue = BoxString("Alloc()");
    Selector AllocSel = GetSelector(AllocSelValue);
    Int Argc = BoxInt(0);
    Int rv = (Int) SendMsg((Object) GetRegisteredObject(IntClassName), AllocSel, Argc);
    
    String InitSelValue = BoxString("Init()");
    Selector InitSel = GetSelector(InitSelValue);
    
    rv = (Int) SendMsg(rv, InitSel, Argc);
    
    rv->value = value;
    
    Release(IntClassName);
    Release(AllocSelValue);
    Release(AllocSel);
    Release(Argc);
    
    return rv;
}

Int (*voltz::BoxInt)(int64_t) = BoxIntImp;

int64_t UnboxIntImp(Int value) {
    return value->value;
}

int64_t (*voltz::UnboxInt)(Int) = UnboxIntImp;

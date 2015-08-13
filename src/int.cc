// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

//               neg   0 + pos
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

int64_t UnboxIntImp(Int value) {
    return value->value;
}

int64_t (*voltz::UnboxInt)(Int) = UnboxIntImp;

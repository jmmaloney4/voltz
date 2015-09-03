// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

Imp BoxImpPhase1(FuncPtr ptr) {
    Imp rv = (Imp) malloc(sizeof(struct voltz_imp));
    rv->isa = ImpClass;
    rv->refs = 1;
    rv->weaks = 0;
    rv->value = ptr;
    return rv;
}

Imp (*voltz::BoxImp)(FuncPtr) = BoxImpPhase1;

FuncPtr UnboxImpPhase1(Imp imp) {
    return imp->value;
}

FuncPtr (*voltz::UnboxImp)(Imp) = UnboxImpPhase1;
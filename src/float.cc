// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

Float BoxFloatImp(double value) {
    String FloatClassName = BoxString("std::Float");
    String AllocSelValue = BoxString("Alloc()");
    Selector AllocSel = GetSelector(AllocSelValue);
    Int Argc = BoxInt(0);
    Float rv = (Float) SendMsg((Object) GetRegisteredObject(FloatClassName), AllocSel, Argc);
    
    // TODO: Init

    rv->value = value;
    
    Release(FloatClassName);
    Release(AllocSelValue);
    Release(AllocSel);
    Release(Argc);
    
    return rv;
}
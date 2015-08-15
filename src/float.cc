// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

Float BoxFloatAll(double value) {
    Selector AllocSel = GetSelector("Alloc()");
    Int Argc = BoxInt(0);
    Float rv = (Float) SendMsg((Object) GetRegisteredObject("std::Float"), AllocSel, Argc);
    
    Selector InitSel = GetSelector("Init()");
    rv = (Float) SendMsg(rv, InitSel, Argc);
    
    rv->value = value;
    
    Release(AllocSel);
    Release(InitSel);
    Release(Argc);
    
    return rv;
}

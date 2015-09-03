// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;

Float BoxFloatAll(double value) {
    Selector AllocSel = GetSelector("Allocate():std::Object");
    Float rv = (Float) SendMsg((Object) GetRegisteredObject("std::Float"), AllocSel, 0);
    
    Selector InitSel = GetSelector("Initialize():std::Object");
    rv = (Float) SendMsg(rv, InitSel, 0);
    
    rv->value = value;
    
    Selector release = GetSelector("Release():std::Void");
    
    SendMsg(AllocSel, release, 0);
    SendMsg(InitSel, release, 0);
    SendMsg(release, release, 0);
    
    return rv;
}

double UnboxFloatAll(Float value) {
    if (value == nil) {
        return 0;
    }
    
    return value->value;
}

Float (*voltz::BoxFloat)(double) = BoxFloatAll;
double (*voltz::UnboxFloat)(Float) = UnboxFloatAll;

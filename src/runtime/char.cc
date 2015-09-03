// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

using namespace voltz;

Char BoxCharAll(int64_t value) {
    Class charcls = (Class) GetRegisteredObject("std::Char");
    
    Selector allocsel = GetSelector("Allocate():std::Object");
    Selector initsel = GetSelector("Initialize():std::Object");
    
    Char rv = (Char) SendMsg(charcls, allocsel, 0);
    rv = (Char) SendMsg(rv, initsel, 0);
    
    rv->value = value;

    return rv;
}

int64_t UnboxCharAll(Char value) {
    if (value == nil) {
        return 0;
    }
    return value->value;
}

Char (*voltz::BoxChar)(int64_t) = BoxCharAll;
int64_t (*voltz::UnboxChar)(Char) = UnboxCharAll;
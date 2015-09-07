// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>

using namespace voltz;

bool LoadStdIO() {

    Selector alloc = GetSelector("Allocate():std::Object");
    Selector init = GetSelector("Initialize():std::Object");
    Selector addProtocol = GetSelector("Add(Protocol:std::Protocol):std::Void");
    Selector addSelector = GetSelector("Add(Selector:std::Selector):std::Void");
    Selector setName = GetSelector("Set(Name:std::String):std::Void");

    Class protocol = (Class) GetRegisteredObject("std::Protocol");

    Protocol WriteStream = (Protocol) SendMsg((Object) protocol, alloc, 0);
    WriteStream = (Protocol) SendMsg((Object) WriteStream, init, 0);
    
    

    return true;
}

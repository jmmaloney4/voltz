// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

using namespace voltz;

void voltz::InitializeObjectClass() {

    Object objcls = GetRegisteredObject("std::Object");
    Object mthdcls = GetRegisteredObject("std::Method");

    Selector allocatesel = GetSelector("Allocate():std::Object");
    Selector initializesel = GetSelector("Initialize():std::Object");
    Selector setselectorsel = GetSelector("Set(Selector:std::Selector):std::Void");
    Selector descriptionsel = GetSelector("Description():std::String");
    Selector setimpsel = GetSelector("Set(Imp:std::Imp):std::Void");
    Selector addmethodsel = GetSelector("Add(Method:std::Method):std::Void");

    Object description = SendMsg(mthdcls, allocatesel, 0);
    description = SendMsg(description, initializesel, 0);
    SendMsg(description, setselectorsel, 1, descriptionsel);
    Object descriptionimp = (Object) BoxImp([] VOLTZ_FN {
        int64_t len = strlen(self->isa->name);
        
        char buf[len];
        
        sprintf(buf, "[%s@%p]", self->isa->name, self);
        
        String rv = BoxString(buf);
        return rv;
    });
    SendMsg(description, setimpsel, 1, descriptionimp);
    
    SendMsg(objcls, addmethodsel, 1, description);
    
    
}

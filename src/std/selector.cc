// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"

bool InitSelectorClass() {
    id selcls = vz_class_get("std::Selector");
    id selisa = vz_msg_send(selcls, "Isa", 0);

    ADD_MTHD(selcls, "Value", {
        SEL val = (SEL) vz_object_getIvar(self, "value");
        return vz_string_box(val->value);
    });

    return true;
}

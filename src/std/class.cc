// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"

bool InitClassClass() {
    id clscls = vz_class_get("std::Class");

    ADD_MTHD(clscls, "Name", {
        return vz_string_box((const char*) vz_object_getIvar(self, "name"));
    });

    return true;
}
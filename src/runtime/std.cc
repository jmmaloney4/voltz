// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

void vz_std_init() {
    
    id objcls = vz_class_get("std::Object");
    id mthdcls = vz_class_get("std::Method");
    
    id name = vz_string_box("std::Bool");
    id iname = vz_string_box("std::Bool.isa");
    id ivarc = vz_num_box(1);
    id boolcls = vz_msg_send(objcls, "Sublclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    
    
    
}

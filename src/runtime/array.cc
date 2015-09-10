// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

void vz_array_init() {
    id protcls = vz_class_get("std::Protocol");
    id generic = vz_msg_send(protcls, "Alloc", 0);
    id name = vz_string_box("std::Generic");
    id superc = vz_num_box(0);
    generic = vz_msg_send(generic, "Init::", 2, name, superc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(superc, "Release", 0);
    
    id sel = vz_sel_box(vz_sel_get("GetTypes"));
    vz_msg_send(generic, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    
    id objcls = vz_class_get("std::Object");
    name = vz_string_box("std::Array");
    id iname = vz_string_box("std::Array.isa");
    id ivarc = vz_num_box(2);
    id arrcls = vz_msg_send(objcls, "Sublcass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    
    
    
}

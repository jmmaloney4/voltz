// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

void vz_mthd_init() {
    id mthdcls = vz_class_get("std::Method");
    id init = vz_msg_send(mthdcls, "Alloc", 0);
    init = vz_msg_send(init, "Init", 0);
    id sel = vz_sel_box(vz_sel_get("Init::"));
    id imp = vz_imp_box(vz_def({
        vz_msg_send(self, "SetSel:", 1, argv[0]);
        vz_msg_send(self, "SetImp:", 1, argv[1]);
        return self;
    }));
    vz_msg_send(init, "SetSel:", 1, sel);
    vz_msg_send(init, "SetImp:", 1, imp);
    vz_msg_send(mthdcls, "AddMethod:", 1, init);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(mthdcls, "Release", 0);
    
}
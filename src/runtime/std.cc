// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

id booltrue = nil;
id boolfalse = nil;

void vz_std_init() {
    
    id objcls = vz_class_get("std::Object");
    id mthdcls = vz_class_get("std::Method");
    
    // std::Bool
    id name = vz_string_box("std::Bool");
    id iname = vz_string_box("std::Bool.isa");
    id ivarc = vz_num_box(1);
    id boolcls = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    vz_class_register("std::Bool", boolcls);
    
    booltrue = vz_msg_send(boolcls, "Alloc", 0);
    booltrue = vz_msg_send(booltrue, "Init", 0);
    booltrue->ivars[0].num = 1;

    boolfalse = vz_msg_send(boolcls, "Alloc", 0);
    boolfalse = vz_msg_send(boolfalse, "Init", 0);
    boolfalse->ivars[0].num = 0;
    
    
    // True()
    id mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    id sel = vz_sel_box(vz_sel_get("True"));
    id imp = vz_imp_box(vz_def({
        return vz_msg_send(booltrue, "Retain", 0);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // False()
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("False"));
    imp = vz_imp_box(vz_def({
        return vz_msg_send(boolfalse, "Retain", 0);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // ==
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        id boolcls = vz_class_get("std::Bool");
        if (argv[0] == nil) {
            return vz_msg_send(boolcls, self->ivars[0].num == 0 ? "True" : "False", 0);
        } else {
            bool s = self->ivars[0].num != 0;
            bool a = argv[0]->ivars[0].num != 0;
            return vz_msg_send(boolcls, s == a ? "True" : "False", 0);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // !=
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        id boolcls = vz_class_get("std::Bool");
        if (argv[0] == nil) {
            return vz_msg_send(boolcls, self->ivars[0].num != 0 ? "True" : "False", 0);
        } else {
            bool s = self->ivars[0].num != 0;
            bool a = argv[0]->ivars[0].num != 0;
            return vz_msg_send(boolcls, s != a ? "True" : "False", 0);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
}

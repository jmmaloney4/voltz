// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"

bool InitBoolClass() {
    id objcls = vz_class_get("std::Object");
    
    SUBCLASS(objcls, boolcls, "std::Bool", 1);
    vz_class_register("std::Bool", boolcls);
    vz_class_setIvarName(boolcls, 0, "value");
    
    id boolclsisa = vz_msg_send(boolcls, "Isa", 0);
    /*ADD_MTHD(boolclsisa, "True", {
        return nil;
    });*/
        { id _mthdcls = vz_class_get("std::Method");
            id _mthd = vz_msg_send(_mthdcls, "Alloc", 0);
            id _sel = vz_sel_box(vz_sel_get("True"));
            id _imp = vz_imp_box((new std::function<id(id, SEL, NUM, id*)>([] (id self, SEL cmd, NUM argc, id* argv) -> id {{ return nil; }})));
            _mthd = vz_msg_send(_mthd, "Init::", 2, _sel, _imp);
            vz_msg_send(boolclsisa, "AddMethod:", 1, _mthd);
            vz_msg_send(_mthdcls, "Release", 0);
            vz_msg_send(_mthd, "Release", 0);
            vz_msg_send(_sel, "Release", 0);
            vz_msg_send(_imp, "Release", 0);
        };
}

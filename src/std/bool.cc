// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"

id booltrue  = nil;
id boolfalse = nil;

bool InitBoolClass() {
    id objcls = vz_class_get("std::Object");

    SUBCLASS(objcls, boolcls, "std::Bool", 1);
    vz_class_register("std::Bool", boolcls);
    vz_class_setIvarName(boolcls, 0, "value");

    booltrue = vz_msg_send(boolcls, "Alloc", 0);
    booltrue = vz_msg_send(booltrue, "Init", 0);
    vz_object_setIvar(booltrue, "value", (id) true);

    boolfalse = vz_msg_send(boolcls, "Alloc", 0);
    boolfalse = vz_msg_send(boolfalse, "Init", 0);
    vz_object_setIvar(boolfalse, "value", (id) false);

    id boolisa = vz_msg_send(boolcls, "Isa", 0);
    ADD_MTHD(boolisa, "True", { return vz_msg_send(booltrue, "Retain", 0); });
    ADD_MTHD(boolisa, "False", { return vz_msg_send(boolfalse, "Retain", 0); });

    ADD_MTHD(boolcls, "Bool", { return vz_msg_send(self, "Retain", 0); });

    ADD_MTHD(boolcls, "Init:", {
        self = vz_msg_send_super(self, "Init", 0);
        if (self) {
            NUM n0 = vz_num_unbox(argv[0]);
            vz_msg_send(self, "Release", 0);
            self = vz_bool_box(n0);
        }
        return self;
    });

    ADD_MTHD(boolcls, "New:", {
        id rv = vz_msg_send(self, "Alloc", 0);
        rv    = vz_msg_send(rv, "Init", 0);
        return rv;
    });

    ADD_MTHD(boolcls, "!", {
        bool b0 = vz_bool_unbox(self);
        return vz_bool_box(!b0);
    });

    ADD_MTHD(boolcls, "==:", {
        bool b0 = vz_bool_unbox(self);
        bool b1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(b0 == b1);
    });
    ADD_MTHD(boolcls, "!=:", {
        bool b0 = vz_bool_unbox(self);
        bool b1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(b0 != b1);
    });

    ADD_MTHD(boolcls, "&&:", {
        bool b0 = vz_bool_unbox(self);
        bool b1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(b0 && b1);
    });
    ADD_MTHD(boolcls, "||:", {
        bool b0 = vz_bool_unbox(self);
        bool b1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(b0 || b1);
    });
    ADD_MTHD(boolcls, "^^:", {
        bool b0 = vz_bool_unbox(self);
        bool b1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(!b0 != !b1);
    });

    ADD_MTHD(boolcls, "String", {
        bool b0 = vz_bool_unbox(self);
        return vz_string_box(b0 ? "True" : "False");
    });

    return true;
}

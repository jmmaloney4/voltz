// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"

bool InitByteClass() {
    id objcls = vz_class_get("std::Object");
    SUBCLASS(objcls, bytecls, "std::Byte", 1);
    vz_class_register("std::Byte", bytecls);
    id byteisa = vz_msg_send(bytecls, "Isa", 0);

    ADD_MTHD(bytecls, "Bool", { return vz_bool_box(vz_byte_unbox(self)); });

    ADD_MTHD(byteisa, "Null", { return vz_byte_box(0); });

    ADD_MTHD(bytecls, "Number", {
        BYTE b0 = vz_byte_unbox(self);
        return vz_num_box((NUM) b0);
    });

    ADD_MTHD(bytecls, "&:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_byte_box(b0 & b1);
    });

    ADD_MTHD(bytecls, "|:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_byte_box(b0 | b1);
    });

    ADD_MTHD(bytecls, "^:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_byte_box(b0 ^ b1);
    });

    ADD_MTHD(bytecls, "&&:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(b0 && b1);
    });

    ADD_MTHD(bytecls, "||:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(b0 || b1);
    });

    ADD_MTHD(bytecls, "^^:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(!b0 != !b1);
    });

    ADD_MTHD(bytecls, "==:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(b0 == b1);
    });

    ADD_MTHD(bytecls, "<:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(b0 < b1);
    });

    ADD_MTHD(bytecls, ">:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(b0 > b1);
    });

    ADD_MTHD(bytecls, "<=:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(b0 <= b1);
    });

    ADD_MTHD(bytecls, ">=:", {
        BYTE b0 = vz_byte_unbox(self);
        BYTE b1 = vz_byte_unbox(argv[0]);
        return vz_bool_box(b0 >= b1);
    });

    return true;
}

// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

id vz_byte_boxI(BYTE value) {
    id bytecls       = vz_class_get("std::Byte");
    id rv            = vz_msg_send(bytecls, "Alloc", 0);
    rv               = vz_msg_send(rv, "Init", 0);
    rv->ivars[0].num = (NUM) value;
    return rv;
}

id (*vz_byte_box)(BYTE) = vz_byte_boxI;

BYTE vz_byte_unboxI(id obj) { return (BYTE) obj->ivars[0].num; }

BYTE (*vz_byte_unbox)(id) = vz_byte_unboxI;
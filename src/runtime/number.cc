// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

id vz_num_boxI(NUM value) {
    id numcls = vz_class_get("std::Number");
    id rv     = vz_msg_send(numcls, "Alloc", 0);
    rv        = vz_msg_send(rv, "Init", 0);

    rv->ivars[0].num = value;

    return rv;
}

id (*vz_num_box)(NUM) = vz_num_boxI;

NUM vz_num_unboxI(id obj) {
    if (obj == nil) {
        return 0;
    }
    return obj->ivars[0].num;
}

NUM (*vz_num_unbox)(id) = vz_num_unboxI;

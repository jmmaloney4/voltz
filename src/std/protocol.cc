// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"
#include <cstdlib>

bool InitProtocolClass() {
    id objcls = vz_class_get("std::Object");
    SUBCLASS(objcls, protcls, "std::Protocol", 7);
    vz_class_setIvarName(protcls, 0, "name");
    vz_class_setIvarName(protcls, 1, "superc");
    vz_class_setIvarName(protcls, 2, "superv");
    vz_class_setIvarName(protcls, 3, "imthdc");
    vz_class_setIvarName(protcls, 4, "imthdv");
    vz_class_setIvarName(protcls, 5, "cmthdc");
    vz_class_setIvarName(protcls, 6, "cmthdv");
    vz_class_register("std::Protocol", protcls);
    id protisa = vz_msg_send(protcls, "Isa", 0);

    ADD_MTHD(protcls, "AddSelector:", {
        NUM imthdc = vz_object_getIvar_n(self, "imthdc");
        id* imthdv = (id*) vz_object_getIvar(self, "imthdv");
        id* tmp = (id*) malloc(sizeof(id) * (imthdc + 1));
        for (NUM k = 0; k < imthdc; k++) {
            tmp[(int64_t) k] = imthdv[(int64_t) k];
        }

        id mthdcls = vz_class_get("std::Method");

        id tmp0 = vz_msg_send(mthdcls, "Alloc", 0);
        tmp0    = vz_msg_send(tmp0, "Init::", 2, argv[0], nil);

        tmp[(int64_t) imthdc] = tmp0;

        vz_msg_send(mthdcls, "Release", 0);

        return nil;
    });

    return true;
}

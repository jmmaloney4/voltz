// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"
#include <cstdlib>

bool InitObjectClass() {

    id objcls = vz_class_get("std::Object");
    id objisa = vz_msg_send(objcls, "Isa", 0);

    ADD_MTHD(objcls, "Bool", { return vz_bool_box(true); });

    ADD_MTHD(objcls, "!", {
        id id0  = vz_msg_send(self, "Bool", 0);
        bool b0 = vz_bool_unbox(id0);
        vz_msg_send(id0, "Release", 0);
        return vz_bool_box(!b0);
    });

    ADD_MTHD(objisa, "Nil", { return nil; });

    ADD_MTHD(objcls, "String", {
        id isa          = vz_msg_send(self, "Isa", 0);
        id name         = vz_msg_send(isa, "Name", 0);
        const char* str = vz_string_unbox(name);
        char buf[100 + strlen(str)];
        sprintf(buf, "[%s:%p]", str, self);

        vz_msg_send(isa, "Release", 0);
        vz_msg_send(name, "Release", 0);
        free((void*) str);

        return vz_string_box(buf);
    });

    ADD_MTHD(objcls, "UnrecognizedSelector:", {
        id val          = vz_msg_send(argv[0], "Value", 0);
        const char* str = vz_string_unbox(val);
        fprintf(stderr, "Unrecognized selector '%s' sent to instance at %p.",
                str, self);
        abort();
    });

    ADD_MTHD(objcls, "ResolveMessageSend::", { return vz_bool_box(false); });

    ADD_MTHD(objcls, "==:", { return vz_bool_box(self == argv[0]); });
    ADD_MTHD(objcls, "!=:", { return vz_bool_box(self != argv[0]); });
    ADD_MTHD(objcls, "===:", { return vz_bool_box(self == argv[0]); });
    ADD_MTHD(objcls, "!==:", { return vz_bool_box(self != argv[0]); });

    return true;
}

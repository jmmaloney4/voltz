// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"
#include <stdlib.h>

bool InitArrayClass() {
    id objcls = vz_class_get("std::Object");
    SUBCLASS(objcls, arrcls, "std::Array", 2);
    vz_class_setIvarName(arrcls, 0, "count");
    vz_class_setIvarName(arrcls, 1, "value");
    vz_class_register("std::Array", arrcls);
    id arrisa = vz_msg_send(arrcls, "Isa", 0);

    PROTOCOL("std::Iterator", iterator);
    vz_class_register("std::Iterator", iterator);
    ADD_SEL(iterator, "Array");
    ADD_SEL(iterator, "Array:");
    ADD_SEL(iterator, "Done?");
    ADD_SEL(iterator, "Next");

    PROTOCOL("std::Iterable", iterable);
    vz_class_register("std::Iterable", iterable);
    ADD_SEL(iterable, "Iterator");

    PROTOCOL("std::Container", container);
    vz_class_register("std::Container", container);
    ADD_SEL(container, "Add:");
    ADD_SEL(container, "AddAll:");
    ADD_SEL(container, "All?:");
    ADD_SEL(container, "Any?:");
    ADD_SEL(container, "Array");
    ADD_SEL(container, "Count");
    ADD_SEL(container, "Contains?:");
    ADD_SEL(container, "ContainsAll?:");
    ADD_SEL(container, "Each:");
    ADD_SEL(container, "Empty?");
    ADD_SEL(container, "Filter:");
    ADD_SEL(container, "Map:");
    ADD_SEL(container, "Reduce:");

    PROTOCOL("std::OrderedContainer", ordcont);
    vz_class_register("std::OrderedContainer", ordcont);
    ADD_SEL(ordcont, "Append:");
    ADD_SEL(ordcont, "AppendAll:");
    ADD_SEL(ordcont, "First");
    ADD_SEL(ordcont, "Last");
    ADD_SEL(ordcont, "ObjectAt:");
    ADD_SEL(ordcont, "Shuffle");
    ADD_SEL(ordcont, "Shuffle:");
    ADD_SEL(ordcont, "Sort:");
    ADD_SEL(ordcont, "[]:");

    SUBCLASS(objcls, arriter, "std::Array::Iterator", 2);
    vz_class_setIvarName(arriter, 0, "index");
    vz_class_setIvarName(arriter, 1, "value");
    ADD_MTHD(arriter, "Index", {
        return vz_msg_send(vz_object_getIvar(self, "index"), "Retain", 0);
    });
    ADD_MTHD(arriter, "Index=:", {
        id id0 = vz_msg_send(self, "Index", 0);
        vz_object_setIvar(self, "index", vz_msg_send(argv[0], "Retain", 0));
        vz_msg_send(id0, "Release", 0);
        return nil;
    });
    ADD_MTHD(arriter, "Value", {
        return vz_msg_send(vz_object_getIvar(self, "value"), "Retain", 0);
    });
    ADD_MTHD(arriter, "Value=:", {
        id id0 = vz_msg_send(self, "Value", 0);
        vz_object_setIvar(self, "value", vz_msg_send(argv[0], "Retain", 0));
        vz_msg_send(id0, "Release", 0);
        return nil;
    });
    ADD_MTHD(arriter, "Next", {
        id arr   = vz_msg_send(self, "Value", 0);
        id index = vz_msg_send(self, "Index", 0);
        id count = vz_msg_send(arr, "Count", 0);
        id id0 = vz_msg_send(index, ">=:", 1, count);
        if (vz_bool_unbox(id0)) {
            vz_msg_send(arr, "Release", 0);
            vz_msg_send(index, "Release", 0);
            vz_msg_send(count, "Release", 0);
            vz_msg_send(id0, "Release", 0);
            return nil;
        }

        id id1 = vz_num_box(1);
        id id2 = vz_msg_send(index, "+:", 1, id1);
        id rv  = vz_msg_send(arr, "[]:", 1, id2);

        vz_msg_send(self, "Index=:", 1, id2);

        vz_msg_send(arr, "Release", 0);
        vz_msg_send(index, "Release", 0);
        vz_msg_send(id1, "Release", 0);
        vz_msg_send(id2, "Release", 0);

        return rv;
    });
    ADD_MTHD(arriter, "Done?", {
        id arr   = vz_msg_send(self, "Value", 0);
        id index = vz_msg_send(self, "Index", 0);
        id count = vz_msg_send(arr, "Count", 0);
        id id0   = vz_msg_send(index, ">=:", 1, count);

        vz_msg_send(arr, "Release", 0);
        vz_msg_send(index, "Release", 0);
        vz_msg_send(count, "Release", 0);

        return id0;
    });
    ADD_MTHD(arriter, "Init", {
        self = vz_msg_send_super(self, "Init", 0);
        if (self != nil) {
            id id0 = vz_num_box(0);
            vz_msg_send(self, "Index=:", 1, id0);
            vz_msg_send(self, "Value=:", 1, nil);
        }
        return self;
    });
    ADD_MTHD(arriter, "Init:", {
        self = vz_msg_send_super(self, "Init", 0);
        if (self != nil) {
            id id0 = vz_num_box(0);
            vz_msg_send(self, "Index=:", 1, id0);
            vz_msg_send(self, "Value=:", 1, argv[0]);
        }
        return self;
    });
    ADD_MTHD(arriter, "New:", {
        id rv = vz_msg_send(self, "Alloc", 0);
        rv    = vz_msg_send(rv, "Init:", 1, argv[0]);
        return rv;
    });

    ADD_MTHD(arrcls, "Iterator", {
        id arriter = vz_class_get("std::Array::Iterator");
        id rv      = vz_msg_send(arriter, "New:", 1, self);
        return rv;
    });
    ADD_MTHD(arrcls, "Add:", {
        id count = vz_msg_send(self, "Count", 0);
        NUM c    = vz_num_unbox(count);
        id* arr  = (id*) vz_object_getIvar(self, "value");
        id* tmp  = (id*) malloc(sizeof(id) * (c + 1));

        for (NUM k = 0; k < c; k++) {
            tmp[(int64_t) k] = vz_msg_send(arr[(int64_t) k], "Retain", 0);
        }
        tmp[(int64_t) c] = vz_msg_send(argv[0], "Retain", 0);

        id rv = vz_array_box_a(c + 1, tmp);

        vz_msg_send(count, "Release", 0);

        return rv;
    });

    ADD_MTHD(arrcls, "Count", { return vz_object_getIvar(self, "count"); });

    return true;
}

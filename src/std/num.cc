// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"
#include <cmath>

bool InitNumberClass() {
    id objcls = vz_class_get("std::Object");
    SUBCLASS(objcls, numcls, "std::Number", 1);
    vz_class_register("std::Number", numcls);
    vz_class_setIvarName(numcls, 0, "value");

    id numisa = vz_msg_send(numcls, "Isa", 0);

    ADD_MTHD(numcls, "Abs", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(fabs(n0));
    });

    ADD_MTHD(numcls, "ACos", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(acos(n0));
    });

    ADD_MTHD(numcls, "ASin", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(asin(n0));
    });

    ADD_MTHD(numcls, "ATan", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(atan(n0));
    });

    ADD_MTHD(numcls, "Bool", {
        NUM n0 = vz_num_unbox(self);
        return vz_bool_box(n0 != 0);
    });

    ADD_MTHD(numcls, "Cbrt", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(cbrt(n0));
    });

    ADD_MTHD(numcls, "Cos", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(atan(n0));
    });

    ADD_MTHD(numcls, "Finite?", {
        NUM n0 = vz_num_unbox(self);
        return vz_bool_box(isfinite(n0));
    });

    ADD_MTHD(numcls, "Floor", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(floor(n0));
    });

    ADD_MTHD(numcls, "GCD:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        NUM n2 = 0;

        while (n0 != 0) {
            n2 = n0;
            n0 = fmod(n1, n0);
            n1 = n2;
        }

        return vz_num_box(n2);
    });

    ADD_MTHD(numisa, "Infinity", { return vz_num_box(INFINITY); });

    ADD_MTHD(numcls, "Integer?", {
        NUM n0 = vz_num_unbox(self);
        return vz_bool_box(n0 - floor(n0) == 0.0);
    });

    ADD_MTHD(numcls, "LCM:", {
        NUM n0 = vz_num_unbox(self);

        id id0 = vz_msg_send(self, "GCD:", 1, argv[0]);
        NUM n1 = vz_num_unbox(id0);
        vz_msg_send(id0, "Release", 0);

        NUM n2 = vz_num_unbox(argv[0]);

        return vz_num_box(n0 / n1 * n2);
    });

    ADD_MTHD(numcls, "Log:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(log(n0) / log(n1));
    });

    ADD_MTHD(numisa, "NaN", { return vz_num_box(nan("")); });

    ADD_MTHD(numcls, "NaN?", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(isnan(n0));
    });

    ADD_MTHD(numcls, "Root:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(pow(n0, 1 / n1));
    });

    ADD_MTHD(numcls, "Round", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(round(n0));
    });

    ADD_MTHD(numcls, "Sin", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(sin(n0));
    });

    ADD_MTHD(numcls, "Sqrt", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(sqrt(n0));
    });

    ADD_MTHD(numcls, "String", {
        NUM n0 = vz_num_unbox(self);
        char buf[200];
        sprintf(buf, "%g", n0);
        return vz_string_box(buf);
    });

    ADD_MTHD(numcls, "Tan", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(tan(n0));
    });

    ADD_MTHD(numcls, "-", {
        NUM n0 = vz_num_unbox(self);
        return vz_num_box(n0 * -1);
    });

    ADD_MTHD(numcls, "+:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(n0 + n1);
    });

    ADD_MTHD(numcls, "+:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(n0 - n1);
    });

    ADD_MTHD(numcls, "*:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(n0 * n1);
    });

    ADD_MTHD(numcls, "**:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(pow(n0, n1));
    });

    ADD_MTHD(numcls, "/:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(n0 / n1);
    });

    ADD_MTHD(numcls, "%:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_num_box(fmod(n0, n1));
    });

    ADD_MTHD(numcls, "==:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_bool_box(n0 == n1);
    });

    ADD_MTHD(numcls, "<:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_bool_box(n0 < n1);
    });

    ADD_MTHD(numcls, ">:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_bool_box(n0 > n1);
    });

    ADD_MTHD(numcls, "<=:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_bool_box(n0 <= n1);
    });

    ADD_MTHD(numcls, ">=:", {
        NUM n0 = vz_num_unbox(self);
        NUM n1 = vz_num_unbox(argv[0]);
        return vz_bool_box(n0 >= n1);
    });

    return true;
}

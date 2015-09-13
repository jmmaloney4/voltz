// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>

union vz_ivar {
    id obj;
    SEL sel;
    NUM num;
    IMP imp;
    const char* str;
    id* arr;
    SEL* sarr;
};

struct vz_object {
    id isa;
    NUM refs;
    NUM weaks;
    vz_ivar ivars[0];
};

struct vz_sel {
    const char* value;
};

extern "C" void vz_bootstrap_runtime(int argc, const char** argv);

extern "C" id vz_object_alloc(NUM ivars);

extern "C" NUM vz_string_hash(const char* s);


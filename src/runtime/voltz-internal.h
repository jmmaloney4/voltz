// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VOLTZ_INTERNAL_H
#define VOLTZ_INTERNAL_H

#include <voltz.h>
#include <mutex>

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

#define vz_classTable_size 0x500

struct vz_classTable_entry {
    id cls;
    const char* name;
    struct vz_classTable_entry* next;
};

#define vz_globalTable_size 0x500

struct vz_globalTable_entry {
    id value;
    const char* name;
    struct vz_globalTable_entry* next;
};

#define vz_selTable_size 0x1000

struct vz_selTable_entry {
    SEL sel;
    struct vz_selTable_entry* next;
};

struct vz_vm {
    std::mutex clsmtx;
    vz_classTable_entry** classtbl;
    std::mutex globalmtx;
    vz_globalTable_entry** globaltbl;
    std::mutex selmtx;
    vz_selTable_entry** seltbl;
};

extern "C" void vz_bootstrap_runtime(int argc, const char** argv);

extern "C" id vz_object_alloc(NUM ivars);

extern "C" NUM vz_string_hash(const char* s);

extern "C" void vz_std_init();

#endif // VOLTZ_INTERNAL_H
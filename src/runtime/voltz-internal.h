// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VOLTZ_INTERNAL_H
#define VOLTZ_INTERNAL_H

#include <voltz.h>
#include <mutex>

namespace voltz {

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

    void BootstrapRuntime(int argc, const char** argv);
    id AllocObject(NUM ivars);
    NUM HashString(const char* s);

    void InitSelectors();

    namespace selectors {
        extern SEL Alloc;
        extern SEL Init;
        extern SEL Retain;
        extern SEL Release;
        extern SEL AddMethod_;
        extern SEL New;
        extern SEL Deinit;
        extern SEL SetSel_;
        extern SEL SetImp_;
        extern SEL sel;
        extern SEL imp;
        extern SEL Init__;
        extern SEL New__;
        extern SEL Subclass___;
        extern SEL Register;
        extern SEL Isa;
        extern SEL True;
        extern SEL False;
        extern SEL Count;
        extern SEL value;
        extern SEL ResolveMessageSend__;
        extern SEL UnrecognizedSelector_;
        extern SEL count;
        extern SEL handle;
        extern SEL imp;
        extern SEL rv;
        extern SEL message;
        extern SEL backtrace;
        extern SEL callstack;
        extern SEL excpstack;
    }

    namespace classes {
        extern id Object;
        extern id Class;
        extern id Method;
        extern id Selector;
        extern id Imp;
        extern id Number;
        extern id Byte;
        extern id String;
        extern id Char;
        extern id Bool;
        extern id Array;
        extern id Tuple;
        extern id Thread;
        extern id Exception;
    }
}

#endif // VOLTZ_INTERNAL_H
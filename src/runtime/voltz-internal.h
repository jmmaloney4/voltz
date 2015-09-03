// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>

namespace voltz {

    extern Int InternedInts[0x20 + 0xff];

    int64_t HashString(const char* s);

    extern Class StringClass;
    extern Class ArrayClass;
    extern Class IntClass;
    extern Class SelectorClass;
    extern Class ImpClass;

    extern Selector AllocSel;
    extern Selector InitSel;
    //extern Selector ArrayOpSel;

    void AddSelector(Selector sel);

    void IntPhase2();
    void ReleaseRetainPhase2();
    void SelectorPhase2();
    void RegistryPhase2();
    void StringPhase2();
    
    void InitializeObjectClass();
    

struct voltz_object {
    Class isa;
    int64_t refs;
    int64_t weaks;
    Object ivars[0];
};

struct voltz_class : public voltz_object {
    Class super;
    const char* name;
    int64_t ivars; // Just for this class, need to sum all the way up for Allocate():std::Object
    const char** ivarn;
    Class* ivart;
    Array prots;
    Array mthds;
};

struct voltz_protocol : public voltz_object {
    String name;
    Array prots;
    Array sels;
};

struct voltz_selector : public voltz_object {
    const char* value;
};

struct voltz_imp : public voltz_object {
    FuncPtr value;
};

struct voltz_int : public voltz_object {
    int64_t value;
};

struct voltz_float : public voltz_object {
    double value;
};

struct voltz_char : public voltz_object {
    int64_t value;
};

struct voltz_string : public voltz_object {
    int64_t length;
    const char* value;
};

struct voltz_array : public voltz_object {
    int64_t count;
    Object* value;
};

struct voltz_bool : public voltz_object {
    int64_t value;
};

struct voltz_method : public voltz_object {
    Selector sel;
    Imp imp;
};

struct voltz_enum : public voltz_object {
    int64_t size;
    Object* values;
};

}
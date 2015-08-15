// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>

using namespace voltz;

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
    
}

struct voltz::voltz_object {
    Class isa;
    int64_t refs;
    int64_t weaks;
    Object ivars[0];
};

struct voltz::voltz_class : public voltz_object {
    Class super;
    const char* name;
    int64_t ivars;
    Array prots;
    Array mthds;
};

struct voltz::voltz_protocol : public voltz_object {
    String name;
    Array sels;
};

struct voltz::voltz_selector : public voltz_object {
    const char* value;
};

struct voltz::voltz_imp : public voltz_object {
    FuncPtr value;
};

struct voltz::voltz_int : public voltz_object {
    int64_t value;
};

struct voltz::voltz_float : public voltz_object {
    double value;
};

struct voltz::voltz_char : public voltz_object {
    int64_t value;
};

struct voltz::voltz_string : public voltz_object {
    int64_t length;
    const char* value;
};

struct voltz::voltz_array : public voltz_object {
    int64_t count;
    Object* value;
};

struct voltz::voltz_bool : public voltz_object {
    int64_t value;
};

struct voltz::voltz_method : public voltz_object {
    Selector sel;
    Imp imp;
};

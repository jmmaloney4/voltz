// voltz-types.h
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VOLTZ_TYPES_H
#define VOLTZ_TYPES_H

#include <stdint.h>
#include <voltz-bytecode.h>

namespace voltz {
    
    typedef struct voltz_object* Object;
    typedef struct voltz_class* Class;
    typedef struct voltz_protocol* Protocol;
    typedef struct voltz_selector* Selector;
    typedef struct voltz_imp* Imp;
    typedef struct voltz_thread* Thread;
    typedef struct voltz_method* Method;
    
    struct voltz_object {
        Class isa;
        int64_t refs;
        int64_t weaks;
        Object ivars[0];
    };
    
    struct voltz_class : public voltz_object {
        Class super;
        const char* name;
        int64_t protocolc;
        Protocol* protocols;
        int64_t ivarc;
        int64_t mthdc;
        Method* mthdv;
    };
    
    struct voltz_protocol : public voltz_object {
        const char* name;
        int64_t protocolc;
        Protocol* protocols;
        int64_t mthdc;
        Selector* mthds;
    };
    
    struct voltz_selector : public voltz_object {
        const char* value;
    };
    
    struct voltz_imp : public voltz_object {
        int64_t count;
        Instruction* instructions;
    };
    
    struct voltz_thread : public voltz_object {
        int64_t id;
        
        Imp code;
        int64_t loc;
        
        int64_t stksz;
        Object* stack;
    };
    
    struct voltz_method : public voltz_object {
        Selector sel;
        Imp imp;
    };
    
}
#endif

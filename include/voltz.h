// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>
#include <stdarg.h>
#include <functional>
#include <cstddef>

namespace voltz {

    const std::nullptr_t nil = NULL;
    
    typedef struct voltz_object* Object;
    typedef struct voltz_class* Class;
    typedef struct voltz_protocol* Protocol;
    typedef struct voltz_selector* Selector;
    typedef struct voltz_imp* Imp;
    typedef struct voltz_int* Int;
    typedef struct voltz_float* Float;
    typedef struct voltz_char* Char;
    typedef struct voltz_string* String;
    typedef struct voltz_array* Array;

    typedef std::function<Object(Object, Array)> FuncPtr;
    
    // Not actually implemented by the runtime
    void VoltzMain(Int argc, Array argv);

    extern Int (*BoxInt)(int64_t value);
    extern Float (*BoxFloat)(double value);
    extern Char (*BoxChar)(int64_t value);
    // str is not kept after the invocation of this function
    extern String (*BoxString)(const char* value);
    // value is copied, and does not need to be kept after this function is called
    extern Array (*BoxArray)(Int count, Object* value);
    
    extern int64_t (*UnboxInt)(Int value);
    extern double (*UnboxFloat)(Float value);
    extern int64_t (*UnboxChar)(Char value);
    // the return value needs to be freed after this function is called.
    extern char* (*UnboxString)(String value);
    // the return value needs to be freed after this function is called.
    extern Object* (*UnboxArray)(Array value);

    void (*Release)(Object obj);
    Object (*Retain)(Object obj);
    void (*WeakRelease)(Object obj);
    Object (*WeakRetain)(Object obj);
    
    Selector (*GetSelector)(String value);

    void (*RegisterObject)(Object obj, String name);
    Object (*GetRegisteredObject)(String name);
    
    Class (*GetIsa)(Object obj);
    Int (*GetRefs)(Object obj);
    Int (*GetWeaks)(Object obj);
    
    Class (*GetSuper)(Class cls);
    String (*GetClassName)(Class cls);
    
    String (*GetProtocolName)(Protocol prt);

    Object (*SendMsg)(Object target, Selector sel, Int argc, ...);
    Object (*SendMsgVA)(Object target, Selector sel, Int argc, va_list ap);
    
}

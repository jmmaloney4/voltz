// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>
#include <stdarg.h>
#include <functional>
#include <cstddef>

#define VOLTZ_FN (voltz::Object self, voltz::Selector cmd, int64_t argc, Object* argv) -> voltz::Object

namespace voltz {

    const std::nullptr_t nil = NULL;

    extern int Cargc;
    extern const char** Cargv;

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
    typedef struct voltz_bool* Bool;
    typedef struct voltz_method* Method;

    typedef std::function<Object(Object, Selector, int64_t, Object*)> FuncPtr;

    // Implemented by the linker in executables, loads the linked modules, and enters the code.
    void VoltzLinkerEntry(Int argc, Array argv);

    extern Int (*BoxInt)(int64_t value);
    extern Float (*BoxFloat)(double value);
    extern Char (*BoxChar)(int64_t value);
    // str is not kept after the invocation of this function
    extern String (*BoxString)(const char* value);
    // value is copied, and does not need to be kept after this function is called
    extern Array (*BoxArray)(int64_t count, Object* value);
    extern Imp (*BoxImp)(FuncPtr value);

    extern int64_t (*UnboxInt)(Int value);
    extern double (*UnboxFloat)(Float value);
    extern int64_t (*UnboxChar)(Char value);
    // the return value needs to be freed after this function is called.
    extern char* (*UnboxString)(String value);
    extern FuncPtr (*UnboxImp)(Imp value);

    // These should get turned off in Phase 2
    extern void (*Release)(Object obj);
    extern Object (*Retain)(Object obj);

    extern Selector (*GetSelector)(const char* value);


    extern void (*RegisterObject)(Object obj, const char* name);
    extern Object (*GetRegisteredObject)(const char* name);

    extern Class (*GetIsa)(Object obj);
    extern Int (*GetRefs)(Object obj);
    extern Int (*GetWeaks)(Object obj);

    extern Class (*GetSuper)(Class cls);
    extern String (*GetClassName)(Class cls);

    extern String (*GetProtocolName)(Protocol prt);

    extern Object (*SendMsg)(Object target, Selector sel, int64_t argc, ...);
    extern Object (*SendMsgVA)(Object target, Selector sel, int64_t argc, va_list ap);

}

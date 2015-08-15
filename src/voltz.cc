// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int voltz::Cargc = 0;
const char** voltz::Cargv = nullptr;

Class voltz::StringClass = nil;
Class voltz::ArrayClass = nil;
Class voltz::IntClass = nil;
Class voltz::SelectorClass = nil;
Class voltz::ImpClass = nil;

Selector voltz::AllocSel = nil;
Selector voltz::InitSel = nil;

int main(int argc, const char** argv) {

    Cargc = argc;
    Cargv = argv;

    Class ObjectCls = (Class) malloc(sizeof(struct voltz_class));
    Class ClassCls = (Class) malloc(sizeof(struct voltz_class));
    Class ProtocolCls = (Class) malloc(sizeof(struct voltz_class));
    Class SelectorCls = (Class) malloc(sizeof(struct voltz_class));
    Class ImpCls = (Class) malloc(sizeof(struct voltz_class));
    Class IntCls = (Class) malloc(sizeof(struct voltz_class));
    Class FloatCls = (Class) malloc(sizeof(struct voltz_class));
    Class CharCls = (Class) malloc(sizeof(struct voltz_class));
    Class StringCls = (Class) malloc(sizeof(struct voltz_class));
    Class ArrayCls = (Class) malloc(sizeof(struct voltz_class));
    Class BoolCls = (Class) malloc(sizeof(struct voltz_class));
    Class MethodCls = (Class) malloc(sizeof(struct voltz_class));

    StringClass = StringCls;
    ArrayClass = ArrayCls;
    IntClass = IntCls;
    SelectorClass = SelectorCls;
    ImpClass = ImpCls;

    ObjectCls->isa = ClassCls;
    ObjectCls->super = nil;
    ObjectCls->ivars = 0;

    ClassCls->isa = ClassCls;
    ClassCls->super = ObjectCls;
    ClassCls->ivars = 0;

    ProtocolCls->super = ObjectCls;
    ProtocolCls->isa = (Class) malloc(sizeof(struct voltz_class));
    ProtocolCls->isa->isa = ClassCls;
    ProtocolCls->isa->super = ClassCls;
    ProtocolCls->ivars = 2;

    SelectorCls->super = ObjectCls;
    SelectorCls->isa = (Class) malloc(sizeof(struct voltz_class));
    SelectorCls->isa->isa = ClassCls;
    SelectorCls->isa->super = ClassCls;
    SelectorCls->ivars = 1;

    ImpCls->super = ObjectCls;
    ImpCls->isa = (Class) malloc(sizeof(struct voltz_class));
    ImpCls->isa->isa = ClassCls;
    ImpCls->isa->super = ClassCls;
    ImpCls->ivars = (sizeof(FuncPtr) / sizeof(Object)) + (sizeof(FuncPtr) % sizeof(Object)) == 0 ? 0 : 1;

    IntCls->super = ObjectCls;
    IntCls->isa = (Class) malloc(sizeof(struct voltz_class));
    IntCls->isa->isa = ClassCls;
    IntCls->isa->super = ClassCls;
    IntCls->ivars = 1;

    FloatCls->super = ObjectCls;
    FloatCls->isa = (Class) malloc(sizeof(struct voltz_class));
    FloatCls->isa->isa = ClassCls;
    FloatCls->isa->super = ClassCls;
    FloatCls->ivars = 1;

    CharCls->super = ObjectCls;
    CharCls->isa = (Class) malloc(sizeof(struct voltz_class));
    CharCls->isa->isa = ClassCls;
    CharCls->isa->super = ClassCls;
    CharCls->ivars = 1;

    StringCls->super = ObjectCls;
    StringCls->isa = (Class) malloc(sizeof(struct voltz_class));
    StringCls->isa->isa = ClassCls;
    StringCls->isa->super = ClassCls;
    StringCls->ivars = 2;

    ArrayCls->super = ObjectCls;
    ArrayCls->isa = (Class) malloc(sizeof(struct voltz_class));
    ArrayCls->isa->isa = ClassCls;
    ArrayCls->isa->super = ClassCls;
    ArrayCls->ivars = 2;

    BoolCls->super = ObjectCls;
    BoolCls->isa = (Class) malloc(sizeof(struct voltz_class));
    BoolCls->isa->isa = ClassCls;
    BoolCls->isa->super = ClassCls;
    BoolCls->ivars = 1;

    MethodCls->super = ObjectCls;
    MethodCls->isa = (Class) malloc(sizeof(struct voltz_class));
    MethodCls->isa->isa = ClassCls;
    MethodCls->isa->super = ClassCls;
    MethodCls->ivars = 2;

    ObjectCls->name = "std::Object";
    RegisterObject((Object) ObjectCls, ObjectCls->name);

    ClassCls->name = "std::Class";
    RegisterObject((Object) ClassCls, ClassCls->name);

    ProtocolCls->name = "std::Protocol";
    ProtocolCls->isa->name = "std::Protocol.isa";
    RegisterObject((Object) ProtocolCls, ProtocolCls->name);

    SelectorCls->name = "std::Selector";
    SelectorCls->isa->name = "std::Selector.isa";
    RegisterObject((Object) SelectorCls, SelectorCls->name);

    ImpCls->name = "std::Imp";
    ImpCls->isa->name = "std::Imp.isa";
    RegisterObject((Object) ImpCls, ImpCls->name);

    IntCls->name = "std::Int";
    IntCls->isa->name = "std::Int.isa";
    RegisterObject((Object) IntCls, IntCls->name);
    
    FloatCls->name = "std::Float";
    FloatCls->isa->name = "std::Float.isa";
    RegisterObject((Object) FloatCls, FloatCls->name);

    CharCls->name = "std::Char";
    CharCls->isa->name = "std::Char.isa";
    RegisterObject((Object) CharCls, CharCls->name);

    StringCls->name = "std::String";
    StringCls->isa->name = "std::String.isa";
    RegisterObject((Object) StringCls, StringCls->name);

    ArrayCls->name = "std::Array";
    ArrayCls->isa->name = "std::Array.isa";
    RegisterObject((Object) ArrayCls, ArrayCls->name);

    BoolCls->name = "std::Bool";
    BoolCls->isa->name = "std::Bool.isa";
    RegisterObject((Object) BoolCls, BoolCls->name);

    MethodCls->name = "std::Method";
    MethodCls->isa->name = "std::Method.isa";
    RegisterObject((Object) MethodCls, MethodCls->name);
    
    ObjectCls->mthds = (Array) malloc(sizeof(voltz_array));
    ObjectCls->mthds->isa = ArrayCls;
    ObjectCls->mthds->refs = 1;
    ObjectCls->mthds->weaks = 0;
    ObjectCls->mthds->count = 3;
    ObjectCls->mthds->value = (Object*) malloc(sizeof(Object) * ObjectCls->mthds->count);

    ClassCls->mthds = (Array) malloc(sizeof(voltz_array));
    ClassCls->mthds->isa = ArrayCls;
    ClassCls->mthds->refs = 1;
    ClassCls->mthds->weaks = 0;
    ClassCls->mthds->count = 2;
    ClassCls->mthds->value = (Object*) malloc(sizeof(Object) * ClassCls->mthds->count);
    
    ProtocolCls->mthds = (Array) malloc(sizeof(voltz_array));
    ProtocolCls->mthds->isa = ArrayCls;
    ProtocolCls->mthds->refs = 1;
    ProtocolCls->mthds->weaks = 0;
    ProtocolCls->mthds->count = 0;
    ProtocolCls->mthds->value = (Object*) malloc(sizeof(Object) * ProtocolCls->mthds->count);
    
    ImpCls->mthds = (Array) malloc(sizeof(voltz_array));
    ImpCls->mthds->isa = ArrayCls;
    ImpCls->mthds->refs = 1;
    ImpCls->mthds->weaks = 0;
    ImpCls->mthds->count = 0;
    ImpCls->mthds->value = (Object*) malloc(sizeof(Object) * ImpCls->mthds->count);
    
    ImpCls->mthds = (Array) malloc(sizeof(voltz_array));
    ImpCls->mthds->isa = ArrayCls;
    ImpCls->mthds->refs = 1;
    ImpCls->mthds->weaks = 0;
    ImpCls->mthds->count = 0;
    ImpCls->mthds->value = (Object*) malloc(sizeof(Object) * ImpCls->mthds->count);
    
    IntCls->mthds = (Array) malloc(sizeof(voltz_array));
    IntCls->mthds->isa = ArrayCls;
    IntCls->mthds->refs = 1;
    IntCls->mthds->weaks = 0;
    IntCls->mthds->count = 0;
    IntCls->mthds->value = (Object*) malloc(sizeof(Object) * IntCls->mthds->count);
    
    FloatCls->mthds = (Array) malloc(sizeof(voltz_array));
    FloatCls->mthds->isa = ArrayCls;
    FloatCls->mthds->refs = 1;
    FloatCls->mthds->weaks = 0;
    FloatCls->mthds->count = 0;
    FloatCls->mthds->value = (Object*) malloc(sizeof(Object) * FloatCls->mthds->count);
    
    CharCls->mthds = (Array) malloc(sizeof(voltz_array));
    CharCls->mthds->isa = ArrayCls;
    CharCls->mthds->refs = 1;
    CharCls->mthds->weaks = 0;
    CharCls->mthds->count = 0;
    CharCls->mthds->value = (Object*) malloc(sizeof(Object) * CharCls->mthds->count);
    
    StringCls->mthds = (Array) malloc(sizeof(voltz_array));
    StringCls->mthds->isa = ArrayCls;
    StringCls->mthds->refs = 1;
    StringCls->mthds->weaks = 0;
    StringCls->mthds->count = 0;
    StringCls->mthds->value = (Object*) malloc(sizeof(Object) * StringCls->mthds->count);
    
    ArrayCls->mthds = (Array) malloc(sizeof(voltz_array));
    ArrayCls->mthds->isa = ArrayCls;
    ArrayCls->mthds->refs = 1;
    ArrayCls->mthds->weaks = 0;
    ArrayCls->mthds->count = 1;
    ArrayCls->mthds->value = (Object*) malloc(sizeof(Object) * ArrayCls->mthds->count);
    
    BoolCls->mthds = (Array) malloc(sizeof(voltz_array));
    BoolCls->mthds->isa = ArrayCls;
    BoolCls->mthds->refs = 1;
    BoolCls->mthds->weaks = 0;
    BoolCls->mthds->count = 0;
    BoolCls->mthds->value = (Object*) malloc(sizeof(Object) * BoolCls->mthds->count);
    
    MethodCls->mthds = (Array) malloc(sizeof(voltz_array));
    MethodCls->mthds->isa = ArrayCls;
    MethodCls->mthds->refs = 1;
    MethodCls->mthds->weaks = 0;
    MethodCls->mthds->count = 0;
    MethodCls->mthds->value = (Object*) malloc(sizeof(Object) * MethodCls->mthds->count);

    
    
    ObjectCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    ObjectCls->isa->mthds->isa = ArrayCls;
    ObjectCls->isa->mthds->refs = 1;
    ObjectCls->isa->mthds->weaks = 0;
    ObjectCls->isa->mthds->count = 3;
    ObjectCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * ObjectCls->isa->mthds->count);
    
    ClassCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    ClassCls->isa->mthds->isa = ArrayCls;
    ClassCls->isa->mthds->refs = 1;
    ClassCls->isa->mthds->weaks = 0;
    ClassCls->isa->mthds->count = 2;
    ClassCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * ClassCls->isa->mthds->count);
    
    ProtocolCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    ProtocolCls->isa->mthds->isa = ArrayCls;
    ProtocolCls->isa->mthds->refs = 1;
    ProtocolCls->isa->mthds->weaks = 0;
    ProtocolCls->isa->mthds->count = 0;
    ProtocolCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * ProtocolCls->isa->mthds->count);
    
    ImpCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    ImpCls->isa->mthds->isa = ArrayCls;
    ImpCls->isa->mthds->refs = 1;
    ImpCls->isa->mthds->weaks = 0;
    ImpCls->isa->mthds->count = 0;
    ImpCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * ImpCls->isa->mthds->count);
    
    ImpCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    ImpCls->isa->mthds->isa = ArrayCls;
    ImpCls->isa->mthds->refs = 1;
    ImpCls->isa->mthds->weaks = 0;
    ImpCls->isa->mthds->count = 0;
    ImpCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * ImpCls->isa->mthds->count);
    
    IntCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    IntCls->isa->mthds->isa = ArrayCls;
    IntCls->isa->mthds->refs = 1;
    IntCls->isa->mthds->weaks = 0;
    IntCls->isa->mthds->count = 0;
    IntCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * IntCls->isa->mthds->count);
    
    FloatCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    FloatCls->isa->mthds->isa = ArrayCls;
    FloatCls->isa->mthds->refs = 1;
    FloatCls->isa->mthds->weaks = 0;
    FloatCls->isa->mthds->count = 0;
    FloatCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * FloatCls->isa->mthds->count);
    
    CharCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    CharCls->isa->mthds->isa = ArrayCls;
    CharCls->isa->mthds->refs = 1;
    CharCls->isa->mthds->weaks = 0;
    CharCls->isa->mthds->count = 0;
    CharCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * CharCls->isa->mthds->count);
    
    StringCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    StringCls->isa->mthds->isa = ArrayCls;
    StringCls->isa->mthds->refs = 1;
    StringCls->isa->mthds->weaks = 0;
    StringCls->isa->mthds->count = 0;
    StringCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * StringCls->isa->mthds->count);
    
    ArrayCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    ArrayCls->isa->mthds->isa = ArrayCls;
    ArrayCls->isa->mthds->refs = 1;
    ArrayCls->isa->mthds->weaks = 0;
    ArrayCls->isa->mthds->count = 1;
    ArrayCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * ArrayCls->isa->mthds->count);
    
    BoolCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    BoolCls->isa->mthds->isa = ArrayCls;
    BoolCls->isa->mthds->refs = 1;
    BoolCls->isa->mthds->weaks = 0;
    BoolCls->isa->mthds->count = 0;
    BoolCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * BoolCls->isa->mthds->count);
    
    MethodCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    MethodCls->isa->mthds->isa = ArrayCls;
    MethodCls->isa->mthds->refs = 1;
    MethodCls->isa->mthds->weaks = 0;
    MethodCls->isa->mthds->count = 0;
    MethodCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * MethodCls->isa->mthds->count);
    
    

    Method alloc = (Method) malloc(sizeof(voltz_method));
    alloc->isa = MethodCls;
    alloc->refs = 1;
    alloc->weaks = 0;
    alloc->sel = (Selector) malloc(sizeof(voltz_selector));
    alloc->sel->isa = SelectorCls;
    alloc->sel->refs = 1;
    alloc->sel->weaks = 0;
    alloc->sel->value = "Alloc()";
    AllocSel = (Selector) Retain(alloc->sel);
    alloc->imp = (Imp) malloc(sizeof(voltz_imp));
    alloc->imp->isa = ImpCls;
    alloc->imp->refs = 1;
    alloc->imp->weaks = 0;
    alloc->imp->value = [] (Object self, Selector cmd, Array args) -> Object {
        Object rv = (Object) malloc(sizeof(struct voltz_object) + (sizeof(Object) * ((Class) self)->ivars));
        rv->isa = (Class) self;
        rv->refs = 1;
        rv->weaks = 0;
        return rv;
    };

    Method subclass = (Method) malloc(sizeof(voltz_method));
    subclass->isa = MethodCls;
    subclass->refs = 1;
    subclass->weaks = 0;
    subclass->sel = (Selector) malloc(sizeof(voltz_selector));
    subclass->sel->isa = SelectorCls;
    subclass->sel->refs = 1;
    subclass->sel->weaks = 0;
    subclass->sel->value = "Subclass()";
    subclass->imp = (Imp) malloc(sizeof(voltz_imp));
    subclass->imp->isa = ImpCls;
    subclass->imp->refs = 1;
    subclass->imp->weaks = 0;
    subclass->imp->value = [] (Object self, Selector cmd, Array args) -> Object {
        Class rv = (Class) malloc(sizeof(voltz_class));
        rv->isa = (Class) malloc(sizeof(voltz_class));

        rv->super = (Class) self;
        rv->isa->super = self->isa;

        rv->name = nil;
        rv->isa->name = nil;

        rv->refs = 0;
        rv->weaks = 0;
        rv->isa->refs = 0;
        rv->isa->weaks = 0;

        rv->ivars = ((Class) self)->ivars;
        rv->isa->ivars = 0;

        rv->prots = nil;
        rv->isa->prots = nil;

        rv->mthds = nil;
        rv->isa->mthds = nil;

        return (Object) rv;
    };

    ClassCls->mthds->value[0] = alloc;
    ClassCls->mthds->value[1] = subclass;
    
    
    

    Method init = (Method) malloc(sizeof(voltz_method));
    init->isa = MethodCls;
    init->refs = 1;
    init->weaks = 0;
    init->sel = (Selector) malloc(sizeof(voltz_selector));
    init->sel->isa = SelectorCls;
    init->sel->refs = 1;
    init->sel->weaks = 0;
    init->sel->value = "Init()";
    InitSel = (Selector) Retain(init->sel);
    init->imp = (Imp) malloc(sizeof(voltz_imp));
    init->imp->isa = ImpCls;
    init->imp->refs = 1;
    init->imp->weaks = 0;
    init->imp->value = [] (Object self, Selector cmd, Array args) -> Object {
        return self;
    };

    ObjectCls->mthds->value[0] = init;



    Method arr = (Method) malloc(sizeof(voltz_method));
    arr->isa = MethodCls;
    arr->refs = 1;
    arr->weaks = 0;
    arr->sel = (Selector) malloc(sizeof(voltz_selector));
    arr->sel->isa = SelectorCls;
    arr->sel->refs = 1;
    arr->sel->weaks = 0;
    arr->sel->value = "[](:)";
    arr->imp = (Imp) malloc(sizeof(voltz_imp));
    arr->imp->isa = ImpCls;
    arr->imp->refs = 1;
    arr->imp->weaks = 0;
    arr->imp->value = [] (Object self, Selector cmd, Array args) -> Object {
        int64_t index = UnboxInt((Int) args->value[0]);
        if (index >= ((Array) self)->count) {
            return nil;
        }
        Object rv = ((Array) self)->value[index];
        return Retain(rv);
    };

    ArrayCls->mthds->value[0] = arr;

    for (int64_t k = -0x20; k < 0xff; k++) {
        Int i = (Int) malloc(sizeof(voltz_int));
        i->isa = IntCls;
        i->refs = 1;
        i->weaks = 0;
        i->value = k;
        InternedInts[k + 0x20] = i;
    }

    Int Zero = BoxInt(0);
    Method release = (Method) SendMsg(MethodCls, AllocSel, Zero);
    release = (Method) SendMsg(release, InitSel, Zero);
    
    Selector releaseSel = GetSelector("Release()");
    
    Imp releaseImp = BoxImp([] (Object self, Selector cmd, Array args) -> Object {
        
        self->refs--;
        if (self->refs <= 0) {
            Selector deinitSel = GetSelector("Deinit()");
            Int argc = BoxInt(0);
            SendMsg(self, deinitSel, argc);
            Release(deinitSel);
        }
        
        return nil;
    });
    
    release->sel = releaseSel;
    release->imp = releaseImp;
    
    ObjectCls->mthds->value[1] = release;
    
    Method retain = (Method) SendMsg(MethodCls, AllocSel, Zero);
    retain = (Method) SendMsg(retain, InitSel, Zero);
    
    Selector retainSel = GetSelector("Retain()");
    
    Imp retainImp = BoxImp([] (Object self, Selector cmd, Array args) -> Object {
        self->refs++;
        return self;
    });
    
    retain->sel = retainSel;
    retain->imp = retainImp;
    
    ObjectCls->mthds->value[2] = retain;
    
    
    
    VoltzLinkerEntry(nil, nil);
}

Object SendMsgVAPhase1(Object target, Selector sel, Int argc, va_list ap) {

    if (target == nil) {
        return nil;
    }

    Class c = GetIsa(target);
    for (; c != nil; c = GetSuper(c)) {
        for (int64_t k = 0; k < c->mthds->count; k++) {
            if (((Method) c->mthds->value[k])->sel == sel) {

                Array args = (Array) malloc(sizeof(struct voltz_array));
                args->isa = ArrayClass;
                args->refs = 1;
                args->weaks = 0;
                args->count = argc->value;
                args->value = (Object*) malloc(sizeof(Object) * argc->value);

                for (int64_t k = 0; k < args->count; k++) {
                    args->value[k] = va_arg(ap, Object);
                }

                return ((Method) c->mthds->value[k])->imp->value(target, sel, nil);

            }
        }
    }

    fprintf(stderr, "Unrecognized Selector %s Sent to Instance at %p\n", sel->value, target);
    abort();
}

Object SendMsgPhase1(Object target, Selector sel, Int argc, ...) {
    va_list ap;
    va_start(ap, argc);
    Object rv = SendMsgVAPhase1(target, sel, argc, ap);
    va_end(ap);
    return rv;
}

Object (*voltz::SendMsg)(Object, Selector, Int, ...) = SendMsgPhase1;
Object (*voltz::SendMsgVA)(Object, Selector, Int, va_list) = SendMsgVAPhase1;

void ReleasePhase1(Object obj) {
    if (obj == nil) {
        return;
    }

    obj->refs -= 1;
    if (obj->refs <= 0 && obj->weaks <= 0) {
        // Deinit
        free(obj);
    }
}

void ReleasePhase2(Object obj) {
    Int argc = BoxInt(0);
    Selector release = GetSelector("Release()");
    SendMsg(obj, release, argc);
    
    // FIXME: Not going to work, will recurse endlessly
    Release(argc);
    Release(release);
}

Object RetainPhase1(Object obj) {
    if (obj == nil) {
        return nil;
    }

    obj->refs++;
    return obj;
}

void (*voltz::Release)(Object) = ReleasePhase1;
Object (*voltz::Retain)(Object) = RetainPhase1;

Class GetIsaAll(Object obj) {
    return obj->isa;
}

Class (*voltz::GetIsa)(Object) = GetIsaAll;

Class GetSuperAll(Class cls) {
    return cls->super;
}

Class (*voltz::GetSuper)(Class) = GetSuperAll;

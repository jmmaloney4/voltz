// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace voltz;

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
    ObjectCls->mthds->count = 4;
    ObjectCls->mthds->value = (Object*) malloc(sizeof(Object) * ObjectCls->mthds->count);

    ProtocolCls->mthds = (Array) malloc(sizeof(voltz_array));
    ProtocolCls->mthds->isa = ArrayCls;
    ProtocolCls->mthds->refs = 1;
    ProtocolCls->mthds->weaks = 0;
    ProtocolCls->mthds->count = 0;
    ProtocolCls->mthds->value = (Object*) malloc(sizeof(Object) * ProtocolCls->mthds->count);

    SelectorCls->mthds = (Array) malloc(sizeof(voltz_array));
    SelectorCls->mthds->isa = ArrayCls;
    SelectorCls->mthds->refs = 1;
    SelectorCls->mthds->weaks = 0;
    SelectorCls->mthds->count = 2;
    SelectorCls->mthds->value = (Object*) malloc(sizeof(Object) * SelectorCls->mthds->count);

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


    ClassCls->mthds = (Array) malloc(sizeof(voltz_array));
    ClassCls->mthds->isa = ArrayCls;
    ClassCls->mthds->refs = 1;
    ClassCls->mthds->weaks = 0;
    ClassCls->mthds->count = 3;
    ClassCls->mthds->value = (Object*) malloc(sizeof(Object) * ClassCls->mthds->count);

    ProtocolCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    ProtocolCls->isa->mthds->isa = ArrayCls;
    ProtocolCls->isa->mthds->refs = 1;
    ProtocolCls->isa->mthds->weaks = 0;
    ProtocolCls->isa->mthds->count = 0;
    ProtocolCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * ProtocolCls->isa->mthds->count);

    SelectorCls->isa->mthds = (Array) malloc(sizeof(voltz_array));
    SelectorCls->isa->mthds->isa = ArrayCls;
    SelectorCls->isa->mthds->refs = 1;
    SelectorCls->isa->mthds->weaks = 0;
    SelectorCls->isa->mthds->count = 0;
    SelectorCls->isa->mthds->value = (Object*) malloc(sizeof(Object) * SelectorCls->isa->mthds->count);

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
    ArrayCls->isa->mthds->count = 0;
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
    alloc->sel->value = "Allocate():std::Object";
    AllocSel = (Selector) Retain(alloc->sel);
    AddSelector(AllocSel);
    alloc->imp = (Imp) malloc(sizeof(voltz_imp));
    alloc->imp->isa = ImpCls;
    alloc->imp->refs = 1;
    alloc->imp->weaks = 0;
    alloc->imp->value = [] VOLTZ_FN {
        int64_t ivars = ((Class) self)->ivars;
        for (Class c = ((Class) self)->super; c != nil; c = c->super) {
            ivars += c->ivars;
        }
        
        Object rv = (Object) malloc(sizeof(struct voltz_object) + (sizeof(Object) * ivars));
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
    subclass->sel->value = "Subclass():std::Class";
    AddSelector(subclass->sel);
    subclass->imp = (Imp) malloc(sizeof(voltz_imp));
    subclass->imp->isa = ImpCls;
    subclass->imp->refs = 1;
    subclass->imp->weaks = 0;
    subclass->imp->value = [] VOLTZ_FN {
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
    init->sel->value = "Initialize():std::Object";
    InitSel = (Selector) Retain(init->sel);
    AddSelector(init->sel);
    init->imp = (Imp) malloc(sizeof(voltz_imp));
    init->imp->isa = ImpCls;
    init->imp->refs = 1;
    init->imp->weaks = 0;
    init->imp->value = [] VOLTZ_FN {
        return self;
    };

    ObjectCls->mthds->value[0] = init;

    for (int64_t k = -0x20; k < 0xff; k++) {
        Int i = (Int) malloc(sizeof(voltz_int));
        i->isa = IntCls;
        i->refs = 1;
        i->weaks = 0;
        i->value = k;
        InternedInts[k + 0x20] = i;
    }

    Method release = (Method) SendMsg(MethodCls, AllocSel, 0);
    release = (Method) SendMsg(release, InitSel, 0);
    release->sel = GetSelector("Release():std::Void");

    release->imp = BoxImp([] VOLTZ_FN {

        self->refs--;
        if (self->refs <= 0) {
            Selector deinitSel = GetSelector("Deinit():std::Void");
            SendMsg(self, deinitSel, 0);
            Selector release = GetSelector("Release():std::Void");
            SendMsg(deinitSel, release, 0);
            SendMsg(release, release, 0);
        }

        return nil;
    });
    ObjectCls->mthds->value[1] = release;

    Method retain = (Method) SendMsg(MethodCls, AllocSel, 0);
    retain = (Method) SendMsg(retain, InitSel, 0);
    retain->sel = GetSelector("Retain():std::Object");
    retain->imp = BoxImp([] VOLTZ_FN {
        self->refs++;
        return self;
    });
    ObjectCls->mthds->value[2] = retain;

    Method deinit = (Method) SendMsg(MethodCls, AllocSel, 0);
    deinit = (Method) SendMsg(deinit, InitSel, 0);
    deinit->sel = GetSelector("Deinit():std::Void");
    deinit->imp = BoxImp([] VOLTZ_FN {
        free(self);
        return nil;
    });
    ObjectCls->mthds->value[3] = deinit;

    Method selret = (Method) SendMsg(MethodCls, AllocSel, 0);
    selret = (Method) SendMsg(selret, InitSel, 0);
    selret->sel = GetSelector("Retain():std::Object");
    selret->imp = BoxImp([] VOLTZ_FN {
        // Selectors don't do refrence counting
        return self;
    });

    Method selrel = (Method) SendMsg(MethodCls, AllocSel, 0);
    selrel = (Method) SendMsg(selrel, InitSel, 0);
    selrel->sel = GetSelector("Release():std::Void");
    selrel->imp = BoxImp([] VOLTZ_FN {
        // Selectors don't do refrence counting
        return self;
    });

    SelectorCls->mthds->value[0] = selret;
    SelectorCls->mthds->value[1] = selrel;

    
    Method arrop = (Method) SendMsg(MethodCls, AllocSel, 0);
    arrop = (Method) SendMsg(arrop, InitSel, 0);
    arrop->sel = GetSelector("[](:std::Int):T");
    arrop->imp = BoxImp([] VOLTZ_FN {
        if (argc < 1) {
            return nil;
        }
        int64_t arg = UnboxInt((Int) argv[0]);
        
        Selector retain = GetSelector("Retain():std::Object");
        Selector release = GetSelector("Release():std::Void");
        
        if (((Array) self)->count <= arg) {
            return nil;
        }
        
        Object rv = ((Array) self)->value[arg];
        rv = SendMsg(rv, retain, 0);
        
        SendMsg(retain, release, 0);
        SendMsg(release, release, 0);
        
        return rv;
    });
    ArrayCls->mthds->value[0] = arrop;
    
    IntPhase2();
    ReleaseRetainPhase2();
    SelectorPhase2();
    RegistryPhase2();
    
    Method addMethod = (Method) SendMsg(MethodCls, AllocSel, 0);
    addMethod = (Method) SendMsg(addMethod, InitSel, 0);
    ClassCls->mthds->value[2] = addMethod;
    addMethod->sel = GetSelector("Add(Method:std::Method):std::Void");
    addMethod->imp = BoxImp([] VOLTZ_FN {
        int64_t mthdc = ((Class)self)->mthds->count;
        Method* tmp = (Method*) malloc(sizeof(Method) * (mthdc + 1));
        for (int64_t k = 0; k < mthdc; k++) {
            tmp[k] = (Method) ((Class)self)->mthds->value[k];
        }
        
        tmp[mthdc] = (Method) argv[0];
        
        Method* t = (Method*) ((Class)self)->mthds->value;
        ((Class) self)->mthds->value = (Object*) tmp;
        free(t);
        
        ((Class)self)->mthds->count++;
        
        Selector release = GetSelector("Release():std::Void");
        
        SendMsg(release, release, 0);
        
        return nil;
    });
    
    Method setSelector = (Method) SendMsg(MethodCls, AllocSel, 0);
    setSelector = (Method) SendMsg(setSelector, InitSel, 0);
    setSelector->sel = GetSelector("Set(Selector:std::Selector):std::Void");
    setSelector->imp = BoxImp([] VOLTZ_FN {
        Selector retain = GetSelector("Retain():std::Object");
        
        Selector arg = (Selector) argv[0];
        
        ((Method) self)->sel = (Selector) SendMsg(arg, retain, 0);
        
        Selector release = GetSelector("Release():std::Void");
        
        SendMsg(retain, release, 0);
        SendMsg(release, release, 0);
        
        return nil;
    });
    
    Selector addMethodSel = GetSelector("Add(Method:std::Method):std::Void");
    SendMsg(MethodCls, addMethodSel, 1, setSelector);
    Method setImp = (Method) SendMsg(MethodCls, AllocSel, 0);
    setImp = (Method) SendMsg(setImp, InitSel, 0);
    setImp->sel = GetSelector("Set(Imp:std::Imp):std::Void");
    setImp->imp = BoxImp([] VOLTZ_FN {
        Selector retain = GetSelector("Retain():std::Object");
        
        Imp arg = (Imp) argv[0];
        
        ((Method) self)->imp = (Imp) SendMsg(arg, retain, 0);
        
        Selector release = GetSelector("Release():std::Void");
        
        SendMsg(retain, release, 0);
        SendMsg(release, release, 0);
        
        return nil;
    });
    
    SendMsg(MethodCls, addMethodSel, 1, setImp);
    
    
    
    
    InitializeObjectClass();
    

    Int Argc = BoxInt(argc);
    VoltzLinkerEntry(Argc, nil);
}

Object SendMsgVAPhase1(Object target, Selector sel, int64_t argc, va_list ap) {

    if (target == nil) {
        return nil;
    }

    Class c = GetIsa(target);
    for (; c != nil; c = GetSuper(c)) {
        for (int64_t k = 0; k < c->mthds->count; k++) {
            if (((Method) c->mthds->value[k])->sel == sel) {

                Object* argv = (Object*) malloc(sizeof(Object) * argc);

                for (int64_t k = 0; k < argc; k++) {
                    argv[k] = va_arg(ap, Object);
                }

                return ((Method) c->mthds->value[k])->imp->value(target, sel, argc, argv);
            }
        }
    }

    fprintf(stderr, "Unrecognized Selector %s Sent to Instance at %p\n", sel->value, target);
    abort();
}

Object SendMsgPhase1(Object target, Selector sel, int64_t argc, ...) {
    va_list ap;
    va_start(ap, argc);
    Object rv = SendMsgVAPhase1(target, sel, argc, ap);
    va_end(ap);
    return rv;
}

Object (*voltz::SendMsg)(Object, Selector, int64_t, ...) = SendMsgPhase1;
Object (*voltz::SendMsgVA)(Object, Selector, int64_t, va_list) = SendMsgVAPhase1;

void ReleasePhase1(Object obj) {
    if (obj == nil) {
        return;
    }

    if (obj->isa == SelectorClass) {
        return;
    }

    obj->refs -= 1;
    if (obj->refs <= 0 && obj->weaks <= 0) {
        // Deinit
        free(obj);
    }
}

void ReleasePhase2(Object obj) {
    fprintf(stderr, "This program should not be using the Release() function\n");
    abort();
}

Object RetainPhase1(Object obj) {
    if (obj == nil) {
        return nil;
    }

    if (obj->isa == SelectorClass) {
        return obj;
    }

    obj->refs++;
    return obj;
}

Object RetainPhase2(Object obj) {
    fprintf(stderr, "This program should not be using the Retain() function\n");
    abort();
}

void (*voltz::Release)(Object) = ReleasePhase1;
Object (*voltz::Retain)(Object) = RetainPhase1;

void voltz::ReleaseRetainPhase2() {
    Release = ReleasePhase2;
    Retain = RetainPhase2;
}

Class GetIsaAll(Object obj) {
    return obj->isa;
}

Class (*voltz::GetIsa)(Object) = GetIsaAll;

Class GetSuperAll(Class cls) {
    return cls->super;
}

Class (*voltz::GetSuper)(Class) = GetSuperAll;

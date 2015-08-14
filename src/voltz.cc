// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

Class voltz::StringClass = nil;
Class voltz::ArrayClass = nil;
Class voltz::IntClass = nil;
Class voltz::SelectorClass = nil;

int main(int argc, const char** argv) {
        
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
    
    ObjectCls->name = (String) malloc(sizeof(voltz_string));
    ObjectCls->name->isa = StringCls;
    ObjectCls->name->refs = 1;
    ObjectCls->name->weaks = 0;
    ObjectCls->name->value = "std::Object";
    ObjectCls->name->length = strlen(ObjectCls->name->value);
    
    RegisterObject((Object) ObjectCls, ObjectCls->name);
    
    ClassCls->name = (String) malloc(sizeof(voltz_string));
    ClassCls->name->isa = StringCls;
    ClassCls->name->refs = 1;
    ClassCls->name->weaks = 0;
    ClassCls->name->value = "std::Class";
    ClassCls->name->length = strlen(ClassCls->name->value);
    
    RegisterObject((Object) ClassCls, ClassCls->name);
    
    ProtocolCls->name = (String) malloc(sizeof(voltz_string));
    ProtocolCls->name->isa = StringCls;
    ProtocolCls->name->refs = 1;
    ProtocolCls->name->weaks = 0;
    ProtocolCls->name->value = "std::Protocol";
    ProtocolCls->name->length = strlen(ProtocolCls->name->value);
    
    ProtocolCls->isa->name = (String) malloc(sizeof(voltz_string));
    ProtocolCls->isa->name->isa = StringCls;
    ProtocolCls->isa->name->refs = 1;
    ProtocolCls->isa->name->weaks = 0;
    ProtocolCls->isa->name->value = "std::Protocol.isa";
    ProtocolCls->isa->name->length = strlen(ProtocolCls->isa->name->value);
    
    RegisterObject((Object) ProtocolCls, ProtocolCls->name);
    
    SelectorCls->name = (String) malloc(sizeof(voltz_string));
    SelectorCls->name->isa = StringCls;
    SelectorCls->name->refs = 1;
    SelectorCls->name->weaks = 0;
    SelectorCls->name->value = "std::Selector";
    SelectorCls->name->length = strlen(SelectorCls->name->value);
    
    SelectorCls->isa->name = (String) malloc(sizeof(voltz_string));
    SelectorCls->isa->name->isa = StringCls;
    SelectorCls->isa->name->refs = 1;
    SelectorCls->isa->name->weaks = 0;
    SelectorCls->isa->name->value = "std::Selector.isa";
    SelectorCls->isa->name->length = strlen(SelectorCls->isa->name->value);
    
    RegisterObject((Object) SelectorCls, SelectorCls->name);
    
    ImpCls->name = (String) malloc(sizeof(voltz_string));
    ImpCls->name->isa = StringCls;
    ImpCls->name->refs = 1;
    ImpCls->name->weaks = 0;
    ImpCls->name->value = "std::Imp";
    ImpCls->name->length = strlen(ImpCls->name->value);
    
    ImpCls->isa->name = (String) malloc(sizeof(voltz_string));
    ImpCls->isa->name->isa = StringCls;
    ImpCls->isa->name->refs = 1;
    ImpCls->isa->name->weaks = 0;
    ImpCls->isa->name->value = "std::Imp.isa";
    ImpCls->isa->name->length = strlen(ImpCls->isa->name->value);
    
    RegisterObject((Object) ImpCls, ImpCls->name);
    
    IntCls->name = (String) malloc(sizeof(voltz_string));
    IntCls->name->isa = StringCls;
    IntCls->name->refs = 1;
    IntCls->name->weaks = 0;
    IntCls->name->value = "std::Int";
    IntCls->name->length = strlen(IntCls->name->value);
    
    IntCls->isa->name = (String) malloc(sizeof(voltz_string));
    IntCls->isa->name->isa = StringCls;
    IntCls->isa->name->refs = 1;
    IntCls->isa->name->weaks = 0;
    IntCls->isa->name->value = "std::Int.isa";
    IntCls->isa->name->length = strlen(IntCls->isa->name->value);
    
    RegisterObject((Object) IntCls, IntCls->name);
    
    FloatCls->name = (String) malloc(sizeof(voltz_string));
    FloatCls->name->isa = StringCls;
    FloatCls->name->refs = 1;
    FloatCls->name->weaks = 0;
    FloatCls->name->value = "std::Float";
    FloatCls->name->length = strlen(FloatCls->name->value);
    
    FloatCls->isa->name = (String) malloc(sizeof(voltz_string));
    FloatCls->isa->name->isa = StringCls;
    FloatCls->isa->name->refs = 1;
    FloatCls->isa->name->weaks = 0;
    FloatCls->isa->name->value = "std::Float.isa";
    FloatCls->isa->name->length = strlen(FloatCls->isa->name->value);
    
    RegisterObject((Object) FloatCls, FloatCls->name);
    
    CharCls->name = (String) malloc(sizeof(voltz_string));
    CharCls->name->isa = StringCls;
    CharCls->name->refs = 1;
    CharCls->name->weaks = 0;
    CharCls->name->value = "std::Char";
    CharCls->name->length = strlen(CharCls->name->value);
    
    CharCls->isa->name = (String) malloc(sizeof(voltz_string));
    CharCls->isa->name->isa = StringCls;
    CharCls->isa->name->refs = 1;
    CharCls->isa->name->weaks = 0;
    CharCls->isa->name->value = "std::Char.isa";
    CharCls->isa->name->length = strlen(CharCls->isa->name->value);
    
    RegisterObject((Object) CharCls, CharCls->name);
    
    StringCls->name = (String) malloc(sizeof(voltz_string));
    StringCls->name->isa = StringCls;
    StringCls->name->refs = 1;
    StringCls->name->weaks = 0;
    StringCls->name->value = "std::String";
    StringCls->name->length = strlen(StringCls->name->value);
    
    StringCls->isa->name = (String) malloc(sizeof(voltz_string));
    StringCls->isa->name->isa = StringCls;
    StringCls->isa->name->refs = 1;
    StringCls->isa->name->weaks = 0;
    StringCls->isa->name->value = "std::String.isa";
    StringCls->isa->name->length = strlen(StringCls->isa->name->value);
    
    RegisterObject((Object) StringCls, StringCls->name);
    
    ArrayCls->name = (String) malloc(sizeof(voltz_string));
    ArrayCls->name->isa = StringCls;
    ArrayCls->name->refs = 1;
    ArrayCls->name->weaks = 0;
    ArrayCls->name->value = "std::Array";
    ArrayCls->name->length = strlen(ArrayCls->name->value);
    
    ArrayCls->isa->name = (String) malloc(sizeof(voltz_string));
    ArrayCls->isa->name->isa = StringCls;
    ArrayCls->isa->name->refs = 1;
    ArrayCls->isa->name->weaks = 0;
    ArrayCls->isa->name->value = "std::Array.isa";
    ArrayCls->isa->name->length = strlen(ArrayCls->isa->name->value);
    
    RegisterObject((Object) ArrayCls, ArrayCls->name);
    
    BoolCls->name = (String) malloc(sizeof(voltz_string));
    BoolCls->name->isa = StringCls;
    BoolCls->name->refs = 1;
    BoolCls->name->weaks = 0;
    BoolCls->name->value = "std::Bool";
    BoolCls->name->length = strlen(BoolCls->name->value);
    
    BoolCls->isa->name = (String) malloc(sizeof(voltz_string));
    BoolCls->isa->name->isa = StringCls;
    BoolCls->isa->name->refs = 1;
    BoolCls->isa->name->weaks = 0;
    BoolCls->isa->name->value = "std::Bool.isa";
    BoolCls->isa->name->length = strlen(BoolCls->isa->name->value);
    
    RegisterObject((Object) BoolCls, BoolCls->name);
    
    MethodCls->name = (String) malloc(sizeof(voltz_string));
    MethodCls->name->isa = StringCls;
    MethodCls->name->refs = 1;
    MethodCls->name->weaks = 0;
    MethodCls->name->value = "std::Method";
    MethodCls->name->length = strlen(MethodCls->name->value);
    
    MethodCls->isa->name = (String) malloc(sizeof(voltz_string));
    MethodCls->isa->name->isa = StringCls;
    MethodCls->isa->name->refs = 1;
    MethodCls->isa->name->weaks = 0;
    MethodCls->isa->name->value = "std::Method.isa";
    MethodCls->isa->name->length = strlen(MethodCls->isa->name->value);
    
    RegisterObject((Object) MethodCls, MethodCls->name);
    
    
    
    ClassCls->mthds = (Array) malloc(sizeof(voltz_array));
    ClassCls->mthds->isa = ArrayCls;
    ClassCls->mthds->refs = 1;
    ClassCls->mthds->weaks = 0;
    ClassCls->mthds->count = 2;
    ClassCls->mthds->value = (Object*) malloc(sizeof(Object) * ClassCls->mthds->count);
    
    Method alloc = (Method) malloc(sizeof(voltz_method));
    alloc->isa = MethodCls;
    alloc->refs = 1;
    alloc->weaks = 0;
    alloc->sel = (Selector) malloc(sizeof(voltz_selector));
    alloc->sel->isa = SelectorCls;
    alloc->sel->refs = 1;
    alloc->sel->weaks = 0;
    alloc->sel->value = "Alloc()";
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
    
    
    
    ObjectCls->mthds = (Array) malloc(sizeof(voltz_array));
    ObjectCls->mthds->isa = ArrayCls;
    ObjectCls->mthds->refs = 1;
    ObjectCls->mthds->weaks = 0;
    ObjectCls->mthds->count = 1;
    ObjectCls->mthds->value = (Object*) malloc(sizeof(Object) * ObjectCls->mthds->count);
    
    Method init = (Method) malloc(sizeof(voltz_method));
    init->isa = MethodCls;
    init->refs = 1;
    init->weaks = 0;
    init->sel = (Selector) malloc(sizeof(voltz_selector));
    init->sel->isa = SelectorCls;
    init->sel->refs = 1;
    init->sel->weaks = 0;
    init->sel->value = "Init()";
    init->imp = (Imp) malloc(sizeof(voltz_imp));
    init->imp->isa = ImpCls;
    init->imp->refs = 1;
    init->imp->weaks = 0;
    init->imp->value = [] (Object self, Selector cmd, Array args) -> Object {
        return self;
    };
    
    ObjectCls->mthds->value[0] = init;
    
    ArrayCls->mthds = (Array) malloc(sizeof(voltz_array));
    ArrayCls->mthds->isa = ArrayCls;
    ArrayCls->mthds->refs = 1;
    ArrayCls->mthds->weaks = 0;
    ArrayCls->mthds->count = 1;
    ArrayCls->mthds->value = (Object*) malloc(sizeof(Object) * ArrayCls->mthds->count);
    
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

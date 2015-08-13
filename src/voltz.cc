// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

int main(int argc, const char** argv) {
    
    Class Object = (Class) malloc(sizeof(struct voltz_class));
    Object->super = NULL;
    
    Class Class = (voltz::Class) malloc(sizeof(struct voltz_class));
    Class->super = Object;
    Class->isa = Class;
    
    Object->isa = Class;
    
    
    
    voltz::Class String = (voltz::Class) malloc(sizeof(struct voltz_class));
    String->super = Object;
    String->isa = (voltz::Class) malloc(sizeof(struct voltz_class));
    String->isa->isa = Class;
    String->isa->super = Class;
    
    
    
    voltz::Class Int = (voltz::Class) malloc(sizeof(struct voltz_class));
    Int->super = Object;
    Int->isa = (voltz::Class) malloc(sizeof(struct voltz_class));
    Int->isa->isa = Class;
    Int->isa->super = Class;
    
    for (int64_t k = -0x20; k < 0xff; k++) {
        voltz::Int i = (voltz::Int) malloc(sizeof(struct voltz_int));
        i->isa = Int;
        i->refs = 1;
        i->weaks = 0;
        i->value = k;
        InternedInts[k + 0x20] = i;
    }
    
    Int->ivars = InternedInts[1 + 0x20];
    
    
    
    voltz::Class Array = (voltz::Class) malloc(sizeof(struct voltz_class));
    Array->isa = (voltz::Class) malloc(sizeof(struct voltz_class));
    Array->super = Object;
    Array->isa->isa = Class;
    Array->isa->super = Class;
    
    
    
    voltz::Class Method = (voltz::Class) malloc(sizeof(struct voltz_class));
    Method->isa = (voltz::Class) malloc(sizeof(struct voltz_class));
    Method->super = Object;
    Method->isa->isa = Class;
    Method->isa->super = Class;
    
    
    
    voltz::Class Selector = (voltz::Class) malloc(sizeof(struct voltz_class));
    Selector->isa = (voltz::Class) malloc(sizeof(struct voltz_class));
    Selector->super = Object;
    Selector->isa->isa = Class;
    Selector->isa->super = Class;
    
    
    
    voltz::Class Imp = (voltz::Class) malloc(sizeof(struct voltz_class));
    Imp->isa = (voltz::Class) malloc(sizeof(struct voltz_class));
    Imp->super = Object;
    Imp->isa->isa = Class;
    Imp->isa->super = Class;
    
    
    
    Object->mthds = (voltz::Array) malloc(sizeof(struct voltz_array));
    Object->mthds->isa = Array;
    Object->mthds->refs = 1;
    Object->mthds->weaks = 0;
    Object->mthds->count = InternedInts[1 + 0x20];
    Object->mthds->value = (voltz::Object*) malloc(sizeof(voltz::Object) * UnboxInt(Object->mthds->count));
    
    Object->mthds->value[0] = (voltz::Object) malloc(sizeof(struct voltz_method));
    Object->mthds->value[0]->isa = Method;
    Object->mthds->value[0]->refs = 1;
    Object->mthds->value[0]->weaks = 0;
    
    ((voltz::Method) Object->mthds->value[0])->sel = (voltz::Selector) malloc(sizeof(voltz_selector));
    ((voltz::Method) Object->mthds->value[0])->sel->isa = Selector;
    ((voltz::Method) Object->mthds->value[0])->sel->refs = 1;
    ((voltz::Method) Object->mthds->value[0])->sel->weaks = 0;
    
    ((voltz::Method) Object->mthds->value[0])->sel->value = (voltz::String) malloc(sizeof(struct voltz_string));
    ((voltz::Method) Object->mthds->value[0])->sel->value->isa = String;
    ((voltz::Method) Object->mthds->value[0])->sel->value->refs = 1;
    ((voltz::Method) Object->mthds->value[0])->sel->value->weaks = 0;
    ((voltz::Method) Object->mthds->value[0])->sel->value->value = "Alloc()";
    
    ((voltz::Method) Object->mthds->value[0])->sel->value->length = (voltz::Int) malloc(sizeof(struct voltz_int));
    ((voltz::Method) Object->mthds->value[0])->sel->value->length->isa = Int;
    ((voltz::Method) Object->mthds->value[0])->sel->value->length->refs = 1;
    ((voltz::Method) Object->mthds->value[0])->sel->value->length->weaks = 0;
    ((voltz::Method) Object->mthds->value[0])->sel->value->length->value = strlen(((voltz::Method) Object->mthds->value[0])->sel->value->value);
    
    ((voltz::Method) Object->mthds->value[0])->imp = (voltz::Imp) malloc(sizeof(struct voltz_imp));
    ((voltz::Method) Object->mthds->value[0])->imp->isa = Imp;
    ((voltz::Method) Object->mthds->value[0])->imp->refs = 1;
    ((voltz::Method) Object->mthds->value[0])->imp->weaks = 0;
    ((voltz::Method) Object->mthds->value[0])->imp->value = [] (voltz::Object self, voltz::Selector sel, voltz::Array args) -> voltz::Object {
        voltz::Object rv = (voltz::Object) malloc(sizeof(struct voltz_object) + (sizeof(voltz::Object) * UnboxInt(((voltz::Class) self)->ivars)));
        rv->isa = (voltz::Class) self;
        rv->refs = 1;
        rv->weaks = 0;
        return rv;
    };
    
    
    Object->name = (voltz::String) malloc(sizeof(struct voltz_string));
    Object->name->isa = String;
    Object->name->refs = 1;
    Object->name->weaks = 0;
    Object->name->value = "std::Object";
    Object->name->length = (voltz::Int) malloc(sizeof(struct voltz_int));
    Object->name->length->isa = Int;
    Object->name->length->refs = 1;
    Object->name->length->weaks = 0;
    Object->name->length->value = strlen(Object->name->value);
    
    RegisterObject((voltz::Object) Object, Object->name);
    
    
    
}

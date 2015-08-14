// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <stdio.h>

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

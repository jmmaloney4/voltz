// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

extern "C" void vz_bootstrap_runtime(int argc, const char** argv) {
    
    id objcls = vz_object_alloc(8);
    id clscls = vz_object_alloc(8);
    id numcls = vz_object_alloc(8);
    id charcls = vz_object_alloc(8);
    id stringcls = vz_object_alloc(8);
    
    objcls->isa = clscls;
    clscls->isa = clscls;
    
    numcls->isa = vz_object_alloc(8);
    charcls->isa = vz_object_alloc(8);
    stringcls->isa = vz_object_alloc(8);
    
    
    // super classes
    objcls->ivars[0].obj = nil;
    clscls->ivars[0].obj = objcls;
    numcls->ivars[0].obj = objcls;
    charcls->ivars[0].obj = objcls;
    stringcls->ivars[0].obj = objcls;
    
    numcls->isa->ivars[0].obj = clscls;
    charcls->isa->ivars[0].obj = clscls;
    stringcls->isa->ivars[0].obj = clscls;
    
    
    // names
    objcls->ivars[1].str = "std::Object";
    clscls->ivars[1].str = "std::Class";
    numcls->ivars[1].str = "std::Number";
    charcls->ivars[1].str = "std::Char";
    stringcls->ivars[1].str = "std::String";
    
    numcls->isa->ivars[1].str = "std::Number.isa";
    charcls->isa->ivars[1].str = "std::Char.isa";
    stringcls->isa->ivars[1].str = "std::String.isa";
    
    
    // ivars
    objcls->ivars[2].num = 0;
    clscls->ivars[2].num = 8;
    numcls->ivars[2].num = 1;
    charcls->ivars[2].num = 1;
    stringcls->ivars[2].num = 2;
    
    numcls->isa->ivars[2].num = 0;
    charcls->isa->ivars[2].num = 0;
    stringcls->isa->ivars[2].num = 0;
    
    
    // ivarn
    objcls->ivars[3].sarr = (SEL*) malloc(sizeof(const char*) * objcls->ivars[2].num);
    clscls->ivars[3].sarr = (SEL*) malloc(sizeof(const char*) * clscls->ivars[2].num);
    clscls->ivars[3].sarr[0] = vz_getSel("super");
    clscls->ivars[3].sarr[1] = vz_getSel("name");
    clscls->ivars[3].sarr[2] = vz_getSel("ivars");
    clscls->ivars[3].sarr[3] = vz_getSel("ivarn");
    clscls->ivars[3].sarr[4] = vz_getSel("protocolc");
    clscls->ivars[3].sarr[5] = vz_getSel("protocolv");
    clscls->ivars[3].sarr[6] = vz_getSel("mthdc");
    clscls->ivars[3].sarr[7] = vz_getSel("mthdv");
    numcls->ivars[3].sarr = (SEL*) malloc(sizeof(const char*) * numcls->ivars[2].num);
    numcls->ivars[3].sarr[0] = vz_getSel("value");
    charcls->ivars[3].sarr = (SEL*) malloc(sizeof(const char*) * numcls->ivars[2].num);
    charcls->ivars[3].sarr[0] = vz_getSel("value");
    stringcls->ivars[3].sarr = (SEL*) malloc(sizeof(const char*) * stringcls->ivars[2].num);
    stringcls->ivars[3].sarr[0] = vz_getSel("value");
    stringcls->ivars[3].sarr[1] = vz_getSel("length");
    
    
    // protocolc
    objcls->ivars[4].num = 0;
    clscls->ivars[4].num = 0;
    numcls->ivars[4].num = 0;
    charcls->ivars[4].num = 0;
    stringcls->ivars[4].num = 0;
    
    numcls->isa->ivars[4].num = 0;
    charcls->isa->ivars[4].num = 0;
    stringcls->isa->ivars[4].num = 0;

    
    // protocolv
    objcls->ivars[5].arr = (id*) malloc(0);
    clscls->ivars[5].arr = (id*) malloc(0);
    numcls->ivars[5].arr = (id*) malloc(0);
    charcls->ivars[5].arr = (id*) malloc(0);
    stringcls->ivars[5].arr = (id*) malloc(0);
    
    numcls->isa->ivars[5].arr = (id*) malloc(0);
    charcls->isa->ivars[5].arr = (id*) malloc(0);
    stringcls->isa->ivars[5].arr = (id*) malloc(0);
    
    
    // mthdc
    objcls->ivars[6].num = 0;
    clscls->ivars[6].num = 0;
    numcls->ivars[6].num = 0;
    charcls->ivars[6].num = 0;
    stringcls->ivars[6].num = 0;
    
    numcls->isa->ivars[6].num = 0;
    charcls->isa->ivars[6].num = 0;
    stringcls->isa->ivars[6].num = 0;
    
    
    // mthdv
    objcls->ivars[7].arr = (id*) malloc(sizeof(id) * objcls->ivars[6].num);
    clscls->ivars[7].arr = (id*) malloc(sizeof(id) * clscls->ivars[6].num);
    numcls->ivars[7].arr = (id*) malloc(sizeof(id) * numcls->ivars[6].num);
    charcls->ivars[7].arr = (id*) malloc(sizeof(id) * charcls->ivars[6].num);
    stringcls->ivars[7].arr = (id*) malloc(sizeof(id) * stringcls->ivars[6].num);
    
    numcls->isa->ivars[7].arr = (id*) malloc(sizeof(id) * numcls->isa->ivars[6].num);
    charcls->isa->ivars[7].arr = (id*) malloc(sizeof(id) * charcls->isa->ivars[6].num);
    stringcls->isa->ivars[7].arr = (id*) malloc(sizeof(id) * stringcls->isa->ivars[6].num);
    
    
}
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
    id mthdcls = vz_object_alloc(8);
    
    objcls->isa = clscls;
    clscls->isa = clscls;
    mthdcls->isa = vz_object_alloc(8);
    
    
    // super classes
    objcls->ivars[0].obj = nil;
    clscls->ivars[0].obj = objcls;
    mthdcls->ivars[0].obj = objcls;
    
    
    // names
    objcls->ivars[1].str = "std::Object";
    clscls->ivars[1].str = "std::Class";
    mthdcls->ivars[1].str = "std::Method";
    
    mthdcls->isa->ivars[1].str = "std::Method.isa";
    
    
    // ivars
    objcls->ivars[2].num = 0;
    clscls->ivars[2].num = 8;
    mthdcls->ivars[2].num = 2;
    
    mthdcls->isa->ivars[2].num = 0;
    
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
    mthdcls->ivars[3].sarr = (SEL*) malloc(sizeof(const char*) * mthdcls->ivars[2].num);
    mthdcls->ivars[3].sarr[0] = vz_getSel("sel");
    mthdcls->ivars[3].sarr[1] = vz_getSel("imp");
    
    // protocolc
    objcls->ivars[4].num = 0;
    clscls->ivars[4].num = 0;
    mthdcls->ivars[4].num = 0;

    
    // protocolv
    objcls->ivars[5].arr = (id*) malloc(0);
    clscls->ivars[5].arr = (id*) malloc(0);
    mthdcls->ivars[5].arr = (id*) malloc(0);
    
    // mthdc
    objcls->ivars[6].num = 0;
    clscls->ivars[6].num = 0;
    mthdcls->ivars[6].num = 0;
    
    
    // mthdv
    objcls->ivars[7].arr = (id*) malloc(sizeof(id) * objcls->ivars[6].num);
    clscls->ivars[7].arr = (id*) malloc(sizeof(id) * clscls->ivars[6].num);
    mthdcls->ivars[7].arr = (id*) malloc(sizeof(id) * mthdcls->ivars[6].num);

    
    
}
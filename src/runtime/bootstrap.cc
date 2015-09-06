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
    id selcls = vz_object_alloc(8);
    id impcls = vz_object_alloc(8);
    
    objcls->isa = clscls;
    clscls->isa = clscls;
    mthdcls->isa = vz_object_alloc(8);
    selcls->isa = vz_object_alloc(8);
    impcls->isa = vz_object_alloc(8);
    
    objcls->refs = 1;
    objcls->weaks = 0;
    
    clscls->refs = 1;
    clscls->weaks = 0;
    
    mthdcls->refs = 1;
    mthdcls->weaks = 0;
    
    selcls->refs = 1;
    selcls->weaks = 0;
    
    impcls->refs = 1;
    impcls->weaks = 0;
    
    // super classes
    objcls->ivars[0].obj = nil;
    clscls->ivars[0].obj = objcls;
    mthdcls->ivars[0].obj = objcls;
    selcls->ivars[0].obj = objcls;
    impcls->ivars[0].obj = objcls;
    
    
    // names
    objcls->ivars[1].str = "std::Object";
    clscls->ivars[1].str = "std::Class";
    mthdcls->ivars[1].str = "std::Method";
    selcls->ivars[1].str = "std::Selector";
    impcls->ivars[1].str = "std::Imp";
    
    mthdcls->isa->ivars[1].str = "std::Method.isa";
    selcls->isa->ivars[1].str = "std::Selector.isa";
    impcls->isa->ivars[1].str = "std::Imp.isa";
    
    
    // ivars
    objcls->ivars[2].num = 0;
    clscls->ivars[2].num = 8;
    mthdcls->ivars[2].num = 2;
    selcls->ivars[2].num = 1;
    impcls->ivars[2].num = 1;
    
    mthdcls->isa->ivars[2].num = 0;
    selcls->isa->ivars[2].num = 0;
    impcls->isa->ivars[2].num = 0;
    
    
    // ivarn
    objcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * objcls->ivars[2].num);
    clscls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * clscls->ivars[2].num);
    clscls->ivars[3].sarr[0] = vz_getSel("super");
    clscls->ivars[3].sarr[1] = vz_getSel("name");
    clscls->ivars[3].sarr[2] = vz_getSel("ivars");
    clscls->ivars[3].sarr[3] = vz_getSel("ivarn");
    clscls->ivars[3].sarr[4] = vz_getSel("protocolc");
    clscls->ivars[3].sarr[5] = vz_getSel("protocolv");
    clscls->ivars[3].sarr[6] = vz_getSel("mthdc");
    clscls->ivars[3].sarr[7] = vz_getSel("mthdv");
    mthdcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * mthdcls->ivars[2].num);
    mthdcls->ivars[3].sarr[0] = vz_getSel("sel");
    mthdcls->ivars[3].sarr[1] = vz_getSel("imp");
    selcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * selcls->ivars[2].num);
    selcls->ivars[3].sarr[0] = vz_getSel("value");
    impcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * impcls->ivars[2].num);
    impcls->ivars[3].sarr[0] = vz_getSel("value");
    
    
    // protocolc
    objcls->ivars[4].num = 0;
    clscls->ivars[4].num = 0;
    mthdcls->ivars[4].num = 0;
    selcls->ivars[4].num = 0;
    impcls->ivars[4].num = 0;

    
    // protocolv
    objcls->ivars[5].arr = (id*) malloc(0);
    clscls->ivars[5].arr = (id*) malloc(0);
    mthdcls->ivars[5].arr = (id*) malloc(0);
    selcls->ivars[5].arr = (id*) malloc(0);
    impcls->ivars[5].arr = (id*) malloc(0);
    
    
    // mthdc
    objcls->ivars[6].num = 4;
    clscls->ivars[6].num = 2;
    mthdcls->ivars[6].num = 0;
    selcls->ivars[6].num = 0;
    impcls->ivars[6].num = 0;
    
    mthdcls->isa->ivars[6].num = 0;
    selcls->isa->ivars[6].num = 0;
    impcls->isa->ivars[6].num = 0;
    
    
    // mthdv
    objcls->ivars[7].arr = (id*) malloc(sizeof(id) * objcls->ivars[6].num);
    clscls->ivars[7].arr = (id*) malloc(sizeof(id) * clscls->ivars[6].num);
    mthdcls->ivars[7].arr = (id*) malloc(sizeof(id) * mthdcls->ivars[6].num);
    selcls->ivars[7].arr = (id*) malloc(sizeof(id) * selcls->ivars[6].num);
    impcls->ivars[7].arr = (id*) malloc(sizeof(id) * impcls->ivars[6].num);

    
    // object methods
    objcls->ivars[7].arr[0] = vz_object_alloc(mthdcls->ivars[2].num);
    objcls->ivars[7].arr[0]->isa = mthdcls;
    objcls->ivars[7].arr[0]->refs = 1;
    objcls->ivars[7].arr[0]->weaks = 0;
    objcls->ivars[7].arr[0]->ivars[0].sel = vz_getSel("Init()");
    objcls->ivars[7].arr[0]->ivars[1].imp = [] vz_def {
        return self;
    };
    
    objcls->ivars[7].arr[1] = vz_object_alloc(mthdcls->ivars[2].num);
    objcls->ivars[7].arr[1]->isa = mthdcls;
    objcls->ivars[7].arr[1]->refs = 1;
    objcls->ivars[7].arr[1]->weaks = 0;
    objcls->ivars[7].arr[1]->ivars[0].sel = vz_getSel("Retain()");
    objcls->ivars[7].arr[1]->ivars[1].imp = [] vz_def {
        self->refs++;
        return self;
    };
    
    objcls->ivars[7].arr[2] = vz_object_alloc(mthdcls->ivars[2].num);
    objcls->ivars[7].arr[2]->isa = mthdcls;
    objcls->ivars[7].arr[2]->refs = 1;
    objcls->ivars[7].arr[2]->weaks = 0;
    objcls->ivars[7].arr[2]->ivars[0].sel = vz_getSel("Release()");
    objcls->ivars[7].arr[2]->ivars[1].imp = [] vz_def {
        if (self->refs <= 1) {
            vz_msg_send(self, "Deinit()", 0);
        } else {
            self->refs--;
        }
        return nil;
    };
    
    objcls->ivars[7].arr[3] = vz_object_alloc(mthdcls->ivars[2].num);
    objcls->ivars[7].arr[3]->isa = mthdcls;
    objcls->ivars[7].arr[3]->refs = 1;
    objcls->ivars[7].arr[3]->weaks = 0;
    objcls->ivars[7].arr[3]->ivars[0].sel = vz_getSel("Deinit()");
    objcls->ivars[7].arr[3]->ivars[1].imp = [] vz_def {
        free(self);
        return nil;
    };
    
    // class methods
    clscls->ivars[7].arr[0] = vz_object_alloc(mthdcls->ivars[2].num);
    clscls->ivars[7].arr[0]->isa = mthdcls;
    clscls->ivars[7].arr[0]->refs = 1;
    clscls->ivars[7].arr[0]->weaks = 0;
    clscls->ivars[7].arr[0]->ivars[0].sel = vz_getSel("Alloc()");
    clscls->ivars[7].arr[0]->ivars[1].imp = [] vz_def {
        NUM ivars = self->ivars[2].num;
        for (id c = self->ivars[0].obj; c != nil; c = c->ivars[0].obj) {
            ivars += c->ivars[2].num;
        }
        
        id rv = vz_object_alloc(ivars);
        rv->isa = self;
        rv->refs = 1;
        rv->weaks = 0;
        return rv;
    };
    
    clscls->ivars[7].arr[1] = vz_object_alloc(mthdcls->ivars[2].num);
    clscls->ivars[7].arr[1]->isa = mthdcls;
    clscls->ivars[7].arr[1]->refs = 1;
    clscls->ivars[7].arr[1]->weaks = 0;
    clscls->ivars[7].arr[1]->ivars[0].sel = vz_getSel("AddMethod(:)");
    clscls->ivars[7].arr[1]->ivars[1].imp = [] vz_def {
        NUM mthdc = self->ivars[6].num;
        id* mthdv = self->ivars[7].arr;
        
        id* tmp = (id*) malloc(sizeof(id) * (mthdc + 1));
        
        for (NUM k = 0; k < mthdc; k++) {
            tmp[(int64_t) k] = mthdv[(int64_t) k];
        }
        tmp[(int64_t) mthdc] = vz_msg_send(argv[0], "Retain()", 0);
        
        self->ivars[6].num += 1;
        self->ivars[7].arr = tmp;
        free(mthdv);
        
        return nil;
    };
    
    
    
    // SetSel(:)
    {
        id mthd = vz_msg_send(mthdcls, "Alloc()", 0);
        mthd = vz_msg_send(mthd, "Init()", 0);
        vz_object_setIvar(mthd, "sel", (id) vz_getSel("SetSel(:)"));
        mthd->ivars[1].imp = [] vz_def {
            SEL s = vz_sel_unbox(argv[0]);
            vz_object_setIvar(self, "sel", (id) s);
            return nil;
        };
    }
    
    // SetImp(:)
    {
        id mthd = vz_msg_send(mthdcls, "Alloc()", 0);
        mthd = vz_msg_send(mthd, "Init()", 0);
        vz_object_setIvar(mthd, "imp", (id) vz_getSel("SetImp(:)"));
        mthd->ivars[1].imp = [] vz_def {
            
        };
    }
    
}
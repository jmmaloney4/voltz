// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

int C_argc;
const char** C_argv;

void vz_bootstrap_runtime(int argc, const char** argv) {
    
    C_argc = argc;
    C_argv = argv;
    
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
    
    mthdcls->isa->isa = clscls;
    selcls->isa->isa = clscls;
    impcls->isa->isa = clscls;
    
    
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
    
    mthdcls->isa->ivars[0].obj = clscls;
    selcls->isa->ivars[0].obj = clscls;
    impcls->isa->ivars[0].obj = clscls;
    
    
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
    clscls->ivars[3].sarr[0] = vz_sel_get("super");
    clscls->ivars[3].sarr[1] = vz_sel_get("name");
    clscls->ivars[3].sarr[2] = vz_sel_get("ivars");
    clscls->ivars[3].sarr[3] = vz_sel_get("ivarn");
    clscls->ivars[3].sarr[4] = vz_sel_get("protocolc");
    clscls->ivars[3].sarr[5] = vz_sel_get("protocolv");
    clscls->ivars[3].sarr[6] = vz_sel_get("mthdc");
    clscls->ivars[3].sarr[7] = vz_sel_get("mthdv");
    mthdcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * mthdcls->ivars[2].num);
    mthdcls->ivars[3].sarr[0] = vz_sel_get("sel");
    mthdcls->ivars[3].sarr[1] = vz_sel_get("imp");
    selcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * selcls->ivars[2].num);
    selcls->ivars[3].sarr[0] = vz_sel_get("value");
    impcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * impcls->ivars[2].num);
    impcls->ivars[3].sarr[0] = vz_sel_get("value");
    
    
    // protocolc
    objcls->ivars[4].num = 0;
    clscls->ivars[4].num = 0;
    mthdcls->ivars[4].num = 0;
    printf("%p\n", selcls->ivars[4].obj);
    selcls->ivars[4].num = 0;
    impcls->ivars[4].num = 0;
    
    
    // protocolv
    objcls->ivars[5].arr = (id*) malloc(sizeof(id) * objcls->ivars[4].num);
    clscls->ivars[5].arr = (id*) malloc(sizeof(id) * clscls->ivars[4].num);
    mthdcls->ivars[5].arr = (id*) malloc(sizeof(id) * mthdcls->ivars[4].num);
    selcls->ivars[5].arr = (id*) malloc(sizeof(id) * selcls->ivars[4].num);
    impcls->ivars[5].arr = (id*) malloc(sizeof(id) * impcls->ivars[4].num);
    
    
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
    
    
    // class methods
    clscls->ivars[7].arr[0] = vz_object_alloc(mthdcls->ivars[2].num + objcls->ivars[2].num);
    clscls->ivars[7].arr[0]->isa = mthdcls;
    clscls->ivars[7].arr[0]->refs = 1;
    clscls->ivars[7].arr[0]->weaks = 0;
    vz_object_setIvar(clscls->ivars[7].arr[0], "sel", (id) vz_sel_get("Alloc"));
    vz_object_setIvar(clscls->ivars[7].arr[0], "imp", (id) vz_def({
        NUM ivars = self->ivars[2].num;
        for (id c = self->ivars[0].obj; c != nil; c = c->ivars[0].obj) {
            ivars += c->ivars[2].num;
        }
        
        id rv = vz_object_alloc(ivars);
        rv->isa = self;
        rv->refs = 1;
        rv->weaks = 0;
        return rv;
    }));
    
    clscls->ivars[7].arr[1] = vz_object_alloc(mthdcls->ivars[2].num + objcls->ivars[2].num);
    clscls->ivars[7].arr[1]->isa = mthdcls;
    clscls->ivars[7].arr[1]->refs = 1;
    clscls->ivars[7].arr[1]->weaks = 0;
    vz_object_setIvar(clscls->ivars[7].arr[1], "sel", (id) vz_sel_get("AddMethod:"));
    vz_object_setIvar(clscls->ivars[7].arr[1], "imp", (id) vz_def({
        NUM mthdc = self->ivars[6].num;
        id* mthdv = self->ivars[7].arr;
        
        id* tmp = (id*) malloc(sizeof(id) * (mthdc + 1));
        
        for (NUM k = 0; k < mthdc; k++) {
            tmp[(int64_t) k] = mthdv[(int64_t) k];
        }
        tmp[(int64_t) mthdc] = vz_msg_send(argv[0], "Retain", 0);
        
        self->ivars[6].num += 1;
        self->ivars[7].arr = tmp;
        free(mthdv);
        
        return nil;
    }));
    
    // object methods
    objcls->ivars[7].arr[0] = vz_object_alloc(mthdcls->ivars[2].num + objcls->ivars[2].num);
    objcls->ivars[7].arr[0]->isa = mthdcls;
    objcls->ivars[7].arr[0]->refs = 1;
    objcls->ivars[7].arr[0]->weaks = 0;
    vz_object_setIvar(objcls->ivars[7].arr[0], "sel", (id) vz_sel_get("Init"));
    vz_object_setIvar(objcls->ivars[7].arr[0], "imp", (id) vz_def({
        return self;
    }));
    
    objcls->ivars[7].arr[1] = vz_object_alloc(mthdcls->ivars[2].num + objcls->ivars[2].num);
    objcls->ivars[7].arr[1]->isa = mthdcls;
    objcls->ivars[7].arr[1]->refs = 1;
    objcls->ivars[7].arr[1]->weaks = 0;
    vz_object_setIvar(objcls->ivars[7].arr[1], "sel", (id) vz_sel_get("Retain"));
    vz_object_setIvar(objcls->ivars[7].arr[1], "imp", (id) vz_def({
        self->refs++;
        return self;
    }));
    
    objcls->ivars[7].arr[2] = vz_object_alloc(mthdcls->ivars[2].num + objcls->ivars[2].num);
    objcls->ivars[7].arr[2]->isa = mthdcls;
    objcls->ivars[7].arr[2]->refs = 1;
    objcls->ivars[7].arr[2]->weaks = 0;
    objcls->ivars[7].arr[2]->ivars[0].sel = vz_sel_get("Release");
    objcls->ivars[7].arr[2]->ivars[1].imp = vz_def({
        if (self->refs <= 1) {
            vz_msg_send(self, "Deinit", 0);
        } else {
            self->refs--;
        }
        return nil;
    });
    
    objcls->ivars[7].arr[3] = vz_object_alloc(mthdcls->ivars[2].num + objcls->ivars[2].num);
    objcls->ivars[7].arr[3]->isa = mthdcls;
    objcls->ivars[7].arr[3]->refs = 1;
    objcls->ivars[7].arr[3]->weaks = 0;
    objcls->ivars[7].arr[3]->ivars[0].sel = vz_sel_get("Deinit");
    objcls->ivars[7].arr[3]->ivars[1].imp = vz_def({
        free(self);
        return nil;
    });
    
    // SetSel:
    id setsel = vz_msg_send(mthdcls, "Alloc", 0);
    setsel = vz_msg_send(setsel, "Init", 0);
    vz_object_setIvar(setsel, "sel", (id) vz_sel_get("SetSel:"));
    setsel->ivars[1].imp = vz_def({
        SEL s = vz_sel_unbox(argv[0]);
        vz_object_setIvar(self, "sel", (id) s);
        return nil;
    });
    vz_msg_send(mthdcls, "AddMethod:", 1, setsel);
    
    
    // SetImp:
    id setimp = vz_msg_send(mthdcls, "Alloc", 0);
    setimp = vz_msg_send(setimp, "Init", 0);
    vz_object_setIvar(setimp, "sel", (id) vz_sel_get("SetImp:"));
    setimp->ivars[1].imp = vz_def({
        IMP i = vz_imp_unbox(argv[0]);
        vz_object_setIvar(self, "imp", (id) i);
        return nil;
    });
    vz_msg_send(mthdcls, "AddMethod:", 1, setimp);
    
    // Subclass
    id subclass = vz_msg_send(mthdcls, "Alloc", 0);
    subclass = vz_msg_send(subclass, "Init", 0);
    vz_object_setIvar(subclass, "sel", (id) vz_sel_get("Subclass"));
    subclass->ivars[1].imp = vz_def({
        id clscls = vz_class_get("std::Class");
        id rv = vz_msg_send(clscls, "Alloc", 0);
        rv = vz_msg_send(rv, "Init", 0);
        rv->isa = vz_msg_send(clscls, "Alloc", 0);
        rv->isa = vz_msg_send(rv->isa, "Init", 0);
        rv->isa->isa = clscls;
        rv->isa->ivars[0].obj = self->isa;
        rv->refs = 1;
        rv->weaks = 0;
        rv->ivars[0].obj = vz_msg_send(self, "Retain", 0);
        rv->ivars[2].num = 0;
        rv->ivars[4].num = 0;
        rv->ivars[6].num = 0;
        return rv;
    });
    vz_msg_send(clscls, "AddMethod:", 1, subclass);
    
    vz_class_register(objcls->ivars[1].str, objcls);
    vz_class_register(clscls->ivars[1].str, clscls);
    vz_class_register(mthdcls->ivars[1].str, mthdcls);
    vz_class_register(selcls->ivars[1].str, selcls);
    vz_class_register(impcls->ivars[1].str, impcls);
    vz_class_register(mthdcls->isa->ivars[1].str, mthdcls);
    vz_class_register(selcls->isa->ivars[1].str, selcls);
    vz_class_register(impcls->isa->ivars[1].str, impcls);
    
    id reg = vz_msg_send(mthdcls, "Alloc", 0);
    reg = vz_msg_send(reg, "Init", 0);
    id regsel = vz_sel_box(vz_sel_get("Register"));
    id regimp = vz_imp_box(vz_def({
        vz_class_register(vz_class_name(self), self);
        return nil;
    }));
    vz_msg_send(reg, "SetSel:", 1, regsel);
    vz_msg_send(reg, "SetImp:", 1, regimp);
    vz_msg_send(clscls, "AddMethod:", 1, reg);
    
    vz_number_init();
    
}
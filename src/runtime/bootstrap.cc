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
    vz_object_setIvar(subclass, "sel", (id) vz_sel_get("Subclass:::"));
    subclass->ivars[1].imp = vz_def({
        id clscls = vz_class_get("std::Class");
        id rv = vz_msg_send(clscls, "Alloc", 0);
        rv = vz_msg_send(rv, "Init", 0);
        rv->isa = vz_msg_send(clscls, "Alloc", 0);
        rv->isa = vz_msg_send(rv->isa, "Init", 0);
        rv->isa->isa = clscls;
        rv->isa->ivars[0].obj = vz_msg_send(self->isa, "Retain", 0);
        rv->isa->ivars[1].str = vz_string_unbox(argv[1]);
        rv->isa->ivars[2].num = 0;
        rv->isa->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * rv->isa->ivars[2].num);
        rv->isa->ivars[4].num = 0;
        rv->isa->ivars[5].arr = (id*) malloc(sizeof(id) * rv->isa->ivars[4].num);
        rv->isa->ivars[6].num = 0;
        rv->isa->ivars[7].arr = (id*) malloc(sizeof(id) * rv->isa->ivars[6].num);
        rv->refs = 1;
        rv->weaks = 0;
        rv->ivars[0].obj = vz_msg_send(self, "Retain", 0);
        rv->ivars[1].str = vz_string_unbox(argv[0]);
        rv->ivars[2].num = vz_num_unbox(argv[2]);
        rv->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * rv->ivars[2].num);
        rv->ivars[4].num = 0;
        rv->ivars[5].arr = (id*) malloc(sizeof(id) * rv->ivars[4].num);
        rv->ivars[6].num = 0;
        rv->ivars[7].arr = (id*) malloc(sizeof(id) * rv->ivars[6].num);

        return rv;
    });
    vz_msg_send(clscls, "AddMethod:", 1, subclass);
    
    // AddIvar
    id addivar = vz_msg_send(mthdcls, "Alloc", 0);
    addivar = vz_msg_send(addivar, "Init", 0);
    vz_object_setIvar(addivar, "sel", (id) vz_sel_get("AddIvar:"));
    addivar->ivars[1].imp = vz_def({
        SEL* tmp = (SEL*) malloc(sizeof(SEL) * self->ivars[2].num + 1);
        for (NUM k = 0; k < self->ivars[2].num; k++) {
            tmp[(int64_t)k] = self->ivars[2].sarr[(int64_t)k];
        }
        
        const char* s = vz_string_unbox(argv[0]);
        tmp[(int64_t) self->ivars[2].num] = vz_sel_get(s);
        free((void*) s);
        
        SEL* old = self->ivars[3].sarr;
        self->ivars[3].sarr = tmp;
        free(old);
        
        self->ivars[2].num += 1;
        
        return nil;
    });
    vz_msg_send(clscls, "AddMethod:", 1, addivar);
    
    vz_class_register(objcls->ivars[1].str, objcls);
    vz_class_register(clscls->ivars[1].str, clscls);
    vz_class_register(mthdcls->ivars[1].str, mthdcls);
    vz_class_register(selcls->ivars[1].str, selcls);
    vz_class_register(impcls->ivars[1].str, impcls);
    
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
    
    
    id strcls = vz_object_alloc(clscls->ivars[2].num + objcls->ivars[2].num);
    strcls->isa = vz_object_alloc(clscls->ivars[2].num + objcls->ivars[2].num);
    strcls->ivars[0].obj = objcls;
    strcls->isa->ivars[0].obj = clscls;
    strcls->ivars[1].str = "std::String";
    strcls->isa->ivars[1].str = "std::String.isa";
    strcls->ivars[2].num = 2;
    strcls->isa->ivars[2].num = 0;
    strcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * strcls->ivars[2].num);
    strcls->ivars[3].sarr[0] = vz_sel_get("value");
    strcls->ivars[3].sarr[1] = vz_sel_get("length");
    strcls->isa->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * strcls->isa->ivars[2].num);
    strcls->ivars[4].num = 0;
    strcls->isa->ivars[4].num = 0;
    strcls->ivars[5].arr = (id*) malloc(sizeof(id) * strcls->ivars[4].num);
    strcls->isa->ivars[5].arr = (id*) malloc(sizeof(id) * strcls->isa->ivars[4].num);
    strcls->ivars[6].num = 0;
    strcls->isa->ivars[6].num = 0;
    strcls->ivars[7].arr = (id*) malloc(sizeof(id) * strcls->ivars[6].num);
    strcls->isa->ivars[7].arr = (id*) malloc(sizeof(id) * strcls->isa->ivars[6].num);
    vz_class_register(strcls->ivars[1].str, strcls);
    
    id numcls = vz_object_alloc(clscls->ivars[2].num + objcls->ivars[2].num);
    numcls->isa = vz_object_alloc(clscls->ivars[2].num + objcls->ivars[2].num);
    numcls->ivars[0].obj = objcls;
    numcls->isa->ivars[0].obj = clscls;
    numcls->ivars[1].str = "std::Number";
    numcls->isa->ivars[1].str = "std::Number.isa";
    numcls->ivars[2].num = 1;
    numcls->isa->ivars[2].num = 0;
    numcls->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * numcls->ivars[2].num);
    numcls->ivars[3].sarr[0] = vz_sel_get("value");
    numcls->isa->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * numcls->isa->ivars[2].num);
    numcls->ivars[4].num = 0;
    numcls->isa->ivars[4].num = 0;
    numcls->ivars[5].arr = (id*) malloc(sizeof(id) * numcls->ivars[4].num);
    numcls->isa->ivars[5].arr = (id*) malloc(sizeof(id) * numcls->isa->ivars[4].num);
    numcls->ivars[6].num = 0;
    numcls->isa->ivars[6].num = 0;
    numcls->ivars[7].arr = (id*) malloc(sizeof(id) * numcls->ivars[6].num);
    numcls->isa->ivars[7].arr = (id*) malloc(sizeof(id) * numcls->isa->ivars[6].num);
    
    vz_class_register(numcls->ivars[1].str, numcls);
    
    vz_protocol_init();
    vz_number_init();
    vz_string_init();
    vz_io_init();
}
// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

void vz_protocol_init() {
    id objcls = vz_class_get("std::Object");
    id name = vz_string_box("std::Protocol");
    id iname = vz_string_box("std::Protocol.isa");
    id ivarc = vz_num_box(5);
    id protocol = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    
    protocol->ivars[3].sarr[0] = vz_sel_get("name");
    protocol->ivars[3].sarr[1] = vz_sel_get("superc");
    protocol->ivars[3].sarr[2] = vz_sel_get("superv");
    protocol->ivars[3].sarr[3] = vz_sel_get("selc");
    protocol->ivars[3].sarr[4] = vz_sel_get("selv");
    
    vz_class_register(protocol->ivars[1].str, protocol);
    
    id mthdcls = vz_class_get("std::Method");
    
    // AddSelector:
    id addsel = vz_msg_send(mthdcls, "Alloc", 0);
    addsel = vz_msg_send(addsel, "Init", 0);
    id sel = vz_sel_box(vz_sel_get("AddSelector:"));
    id imp = vz_imp_box(vz_def({
        SEL* n = (SEL*) malloc(sizeof(SEL) * (self->ivars[3].num + 1));
        for (NUM k = 0; k < self->ivars[3].num; k++) {
            n[(int64_t) k] = self->ivars[4].sarr[(int64_t) k];
        }
        
        n[(int64_t) self->ivars[3].num] = vz_sel_unbox(argv[0]);
        
        SEL* old = self->ivars[4].sarr;
        self->ivars[4].sarr = n;
        free(old);
        
        return nil;
    }));
    vz_msg_send(addsel, "SetSel:", 1, sel);
    vz_msg_send(addsel, "SetImp:", 1, imp);
    vz_msg_send(protocol, "AddMethod:", 1, addsel);
    
    // Init(name, superc)
    id init = vz_msg_send(mthdcls, "Alloc", 0);
    init = vz_msg_send(init, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Init::"));
    imp = vz_imp_box(vz_def({
        self = vz_msg_send_super(self, "Init", 0);
        if (self) {
            self->ivars[0].str = vz_string_unbox(argv[0]);
            self->ivars[1].num = vz_num_unbox(argv[1]);
            self->ivars[2].arr = (id*) malloc(sizeof(id) * self->ivars[1].num);
            self->ivars[3].num = 0;
            self->ivars[4].arr = (id*) malloc(sizeof(id) * self->ivars[3].num);
        }
        return self;
    }));
    
    // Conforms?:
    /*
    id conforms = vz_msg_send(mthdcls, "Alloc", 0);
    conforms = vz_msg_send(conforms, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Conforms?:"));
    imp = vz_imp_box(vz_def({
        id tmp = vz_msg_send(self, "SelectorCount", 0);
        NUM selc = vz_num_unbox(tmp);
        vz_msg_send(tmp, "Release", 0);
        
        id selv = vz_msg_send(self, "Selectors", 0);
        
        for (NUM k = 0; k < selc; k++) {
            for (id c = vz_msg_send(argv[0], "Retain", 0); c != nil;) {
                tmp = vz_msg_send(c, "MethodCount", 0);
                NUM mthdc = vz_num_unbox(tmp);
                vz_msg_send(tmp, "Release", 0);
                for (NUM i = 0; i < mthdc; i++) {
                    id index = vz_num_box(k);
                    id sel = vz_msg_send(selv, "[]:", 1, index);
                    id mthd =
                    c->ivars[7].arr[(int64_t)i]
                    if ( == vz_sel_unbox(sel)) {
                        
                    }
                    vz_msg_send(index, "Release", 0);
                }
                id n = vz_msg_send(c, "Super", 0);
                vz_msg_send(c, "Release", 0);
                c = n;
            }
        }
        
        return nil;
    }));
     */
    
    
}

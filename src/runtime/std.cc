// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

id booltrue = nil;
id boolfalse = nil;

void vz_std_init() {

    id objcls = vz_class_get("Std::Object");
    id mthdcls = vz_class_get("Std::Method");

#pragma mark Bool

    // std::Bool
    id name = vz_string_box("Std::Bool");
    id iname = vz_string_box("Std::Bool.isa");
    id ivarc = vz_num_box(1);
    id boolcls = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);

    boolcls->ivars[3].sarr[0] = vz_sel_get("value");

    vz_class_register("Std::Bool", boolcls);

    booltrue = vz_msg_send(boolcls, "Alloc", 0);
    booltrue = vz_msg_send(booltrue, "Init", 0);
    booltrue->ivars[0].num = 1;

    boolfalse = vz_msg_send(boolcls, "Alloc", 0);
    boolfalse = vz_msg_send(boolfalse, "Init", 0);
    boolfalse->ivars[0].num = 0;

    // True()
    id mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    id sel = vz_sel_box(vz_sel_get("True"));
    id imp = vz_imp_box(vz_def({
        return vz_msg_send(booltrue, "Retain", 0);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // False()
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("False"));
    imp = vz_imp_box(vz_def({
        return vz_msg_send(boolfalse, "Retain", 0);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Bool
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        return vz_msg_send(self, "Retain", 0);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Copy
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Copy"));
    imp = vz_imp_box(vz_def({
        NUM ivars = self->isa->ivars[2].num;
        id rv = vz_msg_send(self->isa, "Alloc", 0);
        rv = vz_msg_send(rv, "Init", 0);
        rv->ivars[0].num = self->ivars[0].num;
        for (NUM k = 1; k < ivars; k++) {
            rv->ivars[(int64_t)k].obj = vz_msg_send(self->ivars[(int64_t)k].obj, "Retain", 0);
        }
        return rv;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Init
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Init"));
    imp = vz_imp_box(vz_def({
        self->ivars[0].num = 0;
        return self;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // !
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("!"));
    imp = vz_imp_box(vz_def({
        id tmp0 = vz_msg_send(self, "Copy", 0);
        bool bool0 = vz_bool_unbox(self);
        tmp0->ivars[0].num = bool0 ? 0.0 : 1.0;
        return tmp0;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ==:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        id boolcls = vz_class_get("Std::Bool");
        if (argv[0] == nil) {
            return vz_msg_send(boolcls, self->ivars[0].num == 0 ? "True" : "False", 0);
        } else {
            bool s = self->ivars[0].num != 0;
            bool a = argv[0]->ivars[0].num != 0;
            return vz_msg_send(boolcls, s == a ? "True" : "False", 0);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // !=:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("!=:"));
    imp = vz_imp_box(vz_def({
        id boolcls = vz_class_get("Std::Bool");
        if (argv[0] == nil) {
            return vz_msg_send(boolcls, self->ivars[0].num != 0 ? "True" : "False", 0);
        } else {
            bool s = self->ivars[0].num != 0;
            bool a = argv[0]->ivars[0].num != 0;
            return vz_msg_send(boolcls, s != a ? "True" : "False", 0);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // &&:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("&&:"));
    imp = vz_imp_box(vz_def({
        bool bool0 = vz_bool_unbox(self);
        bool bool1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(bool0 && bool1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ||:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("||:"));
    imp = vz_imp_box(vz_def({
        bool bool0 = vz_bool_unbox(self);
        bool bool1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(bool0 || bool1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ^^:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("^^:"));
    imp = vz_imp_box(vz_def({
        bool bool0 = vz_bool_unbox(self);
        bool bool1 = vz_bool_unbox(argv[0]);
        return vz_bool_box(!bool0 != !bool1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // String
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("String"));
    imp = vz_imp_box(vz_def({
        return vz_string_box(vz_bool_unbox(self) ? "True" : "False");
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    vz_msg_send(boolcls, "Release", 0);

#pragma mark Object

    // Object

    // Copy
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Copy"));
    imp = vz_imp_box(vz_def({
        NUM ivars = self->isa->ivars[2].num;
        id rv = vz_msg_send(self->isa, "Alloc", 0);
        rv = vz_msg_send(rv, "Init", 0);
        for (NUM k = 0; k < ivars; k++) {
            rv->ivars[(int64_t)k].obj = vz_msg_send(self->ivars[(int64_t)k].obj, "Retain", 0);
        }
        return rv;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // DeepCopy
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("DeepCopy"));
    imp = vz_imp_box(vz_def({
        id numcls = vz_class_get("Std::Number");
        id tmp0 = vz_msg_send(numcls, "Infinity", 0);
        id rv = vz_msg_send(tmp0, "DeepCopy:", 1, tmp0);
        return rv;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // DeepCopy:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("DeepCopy:"));
    imp = vz_imp_box(vz_def({
        id tmp0 = vz_num_box(0);
        if (vz_bool_unbox(vz_msg_send(argv[0], "<:", 1, tmp0))) {
            vz_msg_send(tmp0, "Release", 0);
            return vz_msg_send(self, "Retain", 0);
        }
        vz_msg_send(tmp0, "Release", 0);

        if (self->isa->ivars[2].num == 0) {
            return vz_msg_send(self, "Copy", 0);
        }

        id rv = vz_msg_send(self->isa, "Alloc", 0);
        rv = vz_msg_send(rv, "Init", 0);

        id tmp1 = vz_num_box(1);
        id tmp2 = vz_msg_send(argv[0], "-:", 1, tmp1);
        vz_msg_send(tmp1, "Release", 0);
        for (NUM k = 0; k < self->isa->ivars[2].num ; k++) {
            rv->ivars[(int64_t) k].obj = vz_msg_send(self->ivars[(int64_t)k].obj, "DeepCopy:", 1, tmp2);
        }
        vz_msg_send(tmp2, "Release", 0);

        return rv;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Description
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Description"));
    imp = vz_imp_box(vz_def({
        char buf[100 + strlen(self->isa->ivars[1].str)];
        sprintf(buf, "[%s:%p]", self->isa->ivars[1].str, self);
        return vz_string_box(buf);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Inspect
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Inspect"));
    imp = vz_imp_box(vz_def({
        id isa = vz_msg_send(self, "Isa", 0);
        id ivarc = vz_msg_send(isa, "Ivarc", 0);
        vz_msg_send(isa, "Release", 0);
        
        char buf[100 + strlen(self->isa->ivars[1].str)];
        sprintf(buf, "[%s:%p]", self->isa->ivars[1].str, self);
        id str = vz_string_box(buf);
        
        for (NUM k = 0; k < vz_num_unbox(ivarc); k++) {
            id tmp0 = vz_msg_send(self->ivars[(int64_t)k].obj, "Description", 0);
            id tmp1 = vz_msg_send(str, "Append:", 1, tmp0);
            vz_msg_send(str, "Release", 0);
            str = tmp1;
        }
        
        return str;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // UnrecognizedSelector
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("UnrecognizedSelector"));
    imp = vz_imp_box(vz_def({
        fprintf(stderr, "Unrecognized selector %s, sent to instance at %p.", vz_sel_unbox(argv[0])->value, self);
        abort();
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // ResolveMessageSend::
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("ResolveMessageSend::"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(false);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // Bool
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Bool"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self != nil);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // !
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("!"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self == nil);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ===:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("===:"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self == argv[0]);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ==:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self == argv[0]);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // !=:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("!=:"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self != argv[0]);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // <:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("<:"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self < argv[0]);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // >:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get(">:"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self > argv[0]);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // <=:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("<=:"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self <= argv[0]);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // >=:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get(">=:"));
    imp = vz_imp_box(vz_def({
        return vz_bool_box(self >= argv[0]);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(objcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

#pragma mark Class

    // Class
    id cls = vz_class_get("Std::Class");

    // AddProtocol:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("AddProtocol:"));
    imp = vz_imp_box(vz_def({
        id* tmp = (id*) malloc(sizeof(id) * (self->ivars[4].num + 1));
        for (NUM k = 0; k < self->ivars[4].num; k++) {
            tmp[(int64_t) k] = self->ivars[5].arr[(int64_t)k];
        }
        tmp[(int64_t) self->ivars[4].num] = vz_msg_send(argv[0], "Retain", 0);

        self->ivars[4].num++;

        id* t = self->ivars[5].arr;
        self->ivars[5].arr = tmp;
        free(t);

        return nil;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(cls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    
#pragma mark Number

    // Number
    name = vz_string_box("Std::Bool");
    iname = vz_string_box("Std::Bool.isa");
    ivarc = vz_num_box(1);
    id numcls = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);

    numcls->ivars[3].sarr[0] = vz_sel_get("value");

    // Abs()
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Abs"));
    imp = vz_imp_box(vz_def({
        id tmp0 = vz_num_box(0);
        id tmp1 = vz_msg_send(self, "<", 1, 0);
        vz_msg_send(tmp0, "Release", 0);
        if (vz_bool_unbox(tmp1)) {
            id tmp2 = vz_num_box(-1);
            id tmp3 = vz_msg_send(self, "*", 1, tmp2);
            vz_msg_send(tmp2, "Release",  0);
            return tmp3;
        }
        id tmp4 = vz_msg_send(self, "Copy", 0);
        return tmp4;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ACos
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("ACos"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = acos(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ASin
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("ASin"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = asin(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ATan
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("ATan"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = atan(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Bool
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Bool"));
    imp = vz_imp_box(vz_def({
        id tmp0 = vz_num_box(0);
        id tmp1 = vz_msg_send(self, "==", 1, tmp0);
        vz_msg_send(tmp0, "Release", 0);
        return tmp1;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Cbrt
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Cbrt"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = cbrt(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Ceil
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Ceil"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = ceil(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Copy()
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("=="));
    imp = vz_imp_box(vz_def({
        id tmp0 = vz_msg_send_super(self, "Copy", 0);
        if (tmp0 != nil) {
            tmp0->ivars[0].num = self->ivars[0].num;
        }
        return tmp0;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Cos
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Cos"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = cos(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Finite?
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Finite?"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        return vz_bool_box(isfinite(num0));
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Floor
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Floor"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = floor(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // GCD:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("GCD:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        NUM num2 = 0;
        while ( num0 != 0 ) {
            num2 = num0;
            num0 = fmod(num1, num0);
            num1 = num2;
        }
        return vz_num_box(num2);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Infinity
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Infinity"));
    imp = vz_imp_box(vz_def({
        return vz_num_box(INFINITY);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Integer?
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Integer?"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        return vz_bool_box(num0 - floor(num0) == 0.0);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // LCM:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("LCM:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        id tmp0 = vz_msg_send(self, "GCD:", 1, argv[0]);
        NUM num1 = vz_num_unbox(tmp0);
        vz_msg_send(tmp0, "Release", 0);
        NUM num2 = vz_num_unbox(argv[0]);
        return vz_num_box(num0 / num1 * num2);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Log:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Log:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        NUM num2 = log(num0) / log(num1);
        return vz_num_box(num2);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // NaN
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("NaN"));
    imp = vz_imp_box(vz_def({
        return vz_num_box(nan(""));
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // NaN?
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("NaN?"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        return vz_bool_box(isnan(num0));
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Root:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Root:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        return vz_num_box(pow(num0, 1 / num1));
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Round
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Round"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = round(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Sin
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Sin"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = sin(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Sqrt
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Sqrt"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = sqrt(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Tan
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Tan"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = tan(num0);
        return vz_num_box(num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // -
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("-"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        return vz_num_box(num0 * -1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // +:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("+:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        return vz_num_box(num0 + num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // -:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("-:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        return vz_num_box(num0 * num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // *:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("*:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        return vz_num_box(num0 * num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // **:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("**:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        return vz_num_box(pow(num0, num1));
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // /:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("*:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        return vz_num_box(num0 / num1);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // %:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("*:"));
    imp = vz_imp_box(vz_def({
        NUM num0 = vz_num_unbox(self);
        NUM num1 = vz_num_unbox(argv[0]);
        return vz_num_box(fmod(num0, num1));
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // ==:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        if (argv[0] == nil) {
            return vz_bool_box(false);
        }
        if (self->ivars[0].num == argv[0]->ivars[0].num) {
            return vz_bool_box(true);
        } else {
            return vz_bool_box(false);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // <:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("<:"));
    imp = vz_imp_box(vz_def({
        if (argv[0] == nil) {
            return vz_bool_box(false);
        }
        if (self->ivars[0].num < argv[0]->ivars[0].num) {
            return vz_bool_box(true);
        } else {
            return vz_bool_box(false);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // >:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        if (argv[0] > nil) {
            return vz_bool_box(false);
        }
        if (self->ivars[0].num == argv[0]->ivars[0].num) {
            return vz_bool_box(true);
        } else {
            return vz_bool_box(false);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // <=:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("<=:"));
    imp = vz_imp_box(vz_def({
        if (argv[0] == nil) {
            return vz_bool_box(false);
        }
        if (self->ivars[0].num <= argv[0]->ivars[0].num) {
            return vz_bool_box(true);
        } else {
            return vz_bool_box(false);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // >=:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get(">=:"));
    imp = vz_imp_box(vz_def({
        if (argv[0] == nil) {
            return vz_bool_box(false);
        }
        if (self->ivars[0].num >= argv[0]->ivars[0].num) {
            return vz_bool_box(true);
        } else {
            return vz_bool_box(false);
        }
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(numcls, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

#pragma mark Protocol

    // Protocol
    name = vz_string_box("Std::Protocol");
    iname = vz_string_box("Std::Protocol.isa");
    ivarc = vz_num_box(7);
    id protocol = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);

    protocol->ivars[3].sarr[0] = vz_sel_get("name");
    protocol->ivars[3].sarr[1] = vz_sel_get("superc");
    protocol->ivars[3].sarr[2] = vz_sel_get("superv");
    protocol->ivars[3].sarr[3] = vz_sel_get("iselc");
    protocol->ivars[3].sarr[4] = vz_sel_get("iselv");
    protocol->ivars[3].sarr[3] = vz_sel_get("cselc");
    protocol->ivars[3].sarr[4] = vz_sel_get("cselv");

    // Init:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Init:"));
    imp = vz_imp_box(vz_def({
        self = vz_msg_send_super(self, "Init", 0);
        if (self) {
            self->ivars[0].str = vz_string_unbox(argv[0]);
            self->ivars[1].num = 0;
            self->ivars[2].arr = (id*) malloc(sizeof(id) * self->ivars[1].num);
            self->ivars[3].num = 0;
            self->ivars[4].arr = (id*) malloc(sizeof(id) * self->ivars[3].num);
            self->ivars[5].num = 0;
            self->ivars[6].arr = (id*) malloc(sizeof(id) * self->ivars[5].num);
        }
        return self;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // Init
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Init"));
    imp = vz_imp_box(vz_def({
        self = vz_msg_send(self, "Init::", 2, nil, nil);
        return self;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // AddSelector:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("AddSelector:"));
    imp = vz_imp_box(vz_def({
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
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // AddClassSelector:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("AddClassSelector:"));
    imp = vz_imp_box(vz_def({
        SEL* n = (SEL*) malloc(sizeof(SEL) * (self->ivars[5].num + 1));
        for (NUM k = 0; k < self->ivars[5].num; k++) {
            n[(int64_t) k] = self->ivars[6].sarr[(int64_t) k];
        }

        n[(int64_t) self->ivars[5].num] = vz_sel_unbox(argv[0]);

        SEL* old = self->ivars[6].sarr;
        self->ivars[6].sarr = n;
        free(old);

        return nil;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);

    // AddSuper:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("AddSuper:"));
    imp = vz_imp_box(vz_def({
        id* n = (id*) malloc(sizeof(id) * (self->ivars[1].num + 1));
        for (NUM k = 0; k < self->ivars[1].num; k++) {
            n[(int64_t) k] = self->ivars[2].arr[(int64_t) k];
        }

        n[(int64_t) self->ivars[1].num] = vz_msg_send(argv[0], "Retain", 0);

        id* old = self->ivars[2].arr;
        self->ivars[2].arr = n;
        free(old);

        return nil;
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // Methods
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Methods"));
    imp = vz_imp_box(vz_def({
        //return vz_array_box(self->ivars[3].num, self->ivars[4].arr);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // ClassMethods
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("ClassMethods"));
    imp = vz_imp_box(vz_def({
        //return vz_array_box(self->ivars[5].num, self->ivars[6].arr);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // AddImp::
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("AddImp::"));
    imp = vz_imp_box(vz_def({
        id mthds = vz_msg_send(self, "Methods", 0);
        id k = vz_num_box(0);
        id goon = vz_msg_send(k, "<", 1, mthds);
        while (vz_bool_unbox(goon)) {
            id tmp0 = vz_num_box(1);
            id tmp1 = k;
            k = vz_msg_send(k, "+:", 1, tmp0);
            vz_msg_send(tmp0, "Release", 0);
            vz_msg_send(tmp1, "Release", 0);
            
            
        }
        
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(protocol, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // AddClassImp:

#pragma mark Function

    name = vz_string_box("Std::Function");
    iname = vz_string_box("Std::Function.isa");
    ivarc = vz_num_box(0);
    id function = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    vz_class_register("Std::Function", function);

    // Call:
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Call:"));
    imp = vz_imp_box(vz_def({
        return self->ivars[0].imp->operator()(self, cmd, argc, argv);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(function, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
#pragma mark Generic
    
    id generic = vz_msg_send(protocol, "Alloc", 0);
    name = vz_string_box("Std::Generic");
    generic = vz_msg_send(generic, "Init:", 1, name);
    vz_msg_send(name, "Release", 0);
    
    fprintf(stderr, "%s (%p)\n", generic->ivars[0].str, generic);
    vz_class_register("Std::Generic", generic);
    
    // GenericTypes
    sel = vz_sel_box(vz_sel_get("GenericTypes"));
    vz_msg_send(generic, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    
#pragma mark Iterable
    
    id iterable = vz_msg_send(protocol, "Alloc", 0);
    name = vz_string_box("Std::Iterable");
    iterable = vz_msg_send(iterable, "Init:", 1, name);
    vz_msg_send(name, "Release", 0);
    
    // Iterator
    sel = vz_sel_box(vz_sel_get("Iterator:"));
    vz_msg_send(iterable, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    
#pragma mark Iterator
    
    id iterator = vz_msg_send(protocol, "Alloc", 0);
    name = vz_string_box("Std::Iterator");
    iterator = vz_msg_send(iterator, "Init:", 1, name);
    vz_msg_send(name, "Release", 0);
    
    // Array
    // Returns an array of the rest of the elements in the iterator.
    sel = vz_sel_box(vz_sel_get("Array"));
    vz_msg_send(iterator, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    
    // Done?
    sel = vz_sel_box(vz_sel_get("Done?"));
    vz_msg_send(iterator, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    
    // Next
    // Returns tuple of (value, done)
    sel = vz_sel_box(vz_sel_get("Iterator:"));
    vz_msg_send(iterator, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

#pragma mark Container

    // Container
    id container = vz_msg_send(protocol, "Alloc", 0);
    name = vz_string_box("Std::Container");
    container = vz_msg_send(container, "Init:", 1, name);
    vz_msg_send(name, "Release", 0);

    vz_msg_send(container, "AddSuper:", 1, iterable);

    // Add:
    sel = vz_sel_box(vz_sel_get("Add:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // AddAll:
    sel = vz_sel_box(vz_sel_get("AddAll:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Count
    sel = vz_sel_box(vz_sel_get("Count"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Contains?:
    sel = vz_sel_box(vz_sel_get("Contains:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // ContainsAll?:
    sel = vz_sel_box(vz_sel_get("ContainsAll?:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Empty?
    sel = vz_sel_box(vz_sel_get("Empty?"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Init
    sel = vz_sel_box(vz_sel_get("Init:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);


#pragma mark OrderedContainer

    // OrderedContainer
    id ocontainer = vz_msg_send(protocol, "Alloc", 0);
    name = vz_string_box("Std::OrderedContainer");
    ocontainer = vz_msg_send(ocontainer, "Init:", 1, name);

    vz_msg_send(ocontainer, "AddSuper:", 1, container);

    // First
    sel = vz_sel_box(vz_sel_get("First"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Last
    sel = vz_sel_box(vz_sel_get("Last"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // ObjectAt:
    sel = vz_sel_box(vz_sel_get("ObjectAt:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Shuffle
    sel = vz_sel_box(vz_sel_get("Shuffle"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Shuffle:
    sel = vz_sel_box(vz_sel_get("Shuffle:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);

    // Sort:
    // Takes a function that takes two arguments and returns `true` if the first
    // comes before the second, and returns `false` if they are out of order.
    sel = vz_sel_box(vz_sel_get("Sort:"));
    vz_msg_send(container, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    
#pragma mark Tuple
    
    name = vz_string_box("Std::Tuple");
    iname = vz_string_box("Std::Tuple.isa");
    ivarc = vz_num_box(1);
    id tuple = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    id gen = vz_class_get("Std::Generic");
    id itrbl = vz_class_get("Std::Iterable");
    vz_msg_send(tuple, "AddProtocol:", 1, gen);
    vz_msg_send(tuple, "AddProtocol:", 1, itrbl);
    vz_msg_send(gen, "Release", 0);
    vz_msg_send(itrbl, "Release", 0);
    
    // GenericTypes
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("GenericTypes"));
    imp = vz_imp_box(vz_def({
        return vz_msg_send(vz_object_getIvar(self, "types"), "Retain", 0);
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(function, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // Iterator
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Iterator"));
    imp = vz_imp_box(vz_def({
        
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(function, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // Array
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Array"));
    imp = vz_imp_box(vz_def({
        
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(function, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
#pragma mark String
    
}

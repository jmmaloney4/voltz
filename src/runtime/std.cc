// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <math.h>

id booltrue = nil;
id boolfalse = nil;

void vz_std_init() {
    
    id objcls = vz_class_get("std::Object");
    id mthdcls = vz_class_get("std::Method");
    
    // std::Bool
    id name = vz_string_box("std::Bool");
    id iname = vz_string_box("std::Bool.isa");
    id ivarc = vz_num_box(1);
    id boolcls = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    vz_class_register("std::Bool", boolcls);
    
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
    
    // ==
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        id boolcls = vz_class_get("std::Bool");
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
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // !=
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        id boolcls = vz_class_get("std::Bool");
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
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    // String()
    mthd = vz_msg_send(mthdcls, "Alloc", 0);
    mthd = vz_msg_send(mthd, "Init", 0);
    sel = vz_sel_box(vz_sel_get("==:"));
    imp = vz_imp_box(vz_def({
        return vz_string_box(vz_bool_unbox(self) ? "True" : "False");
    }));
    vz_msg_send(mthd, "SetSel:", 1, sel);
    vz_msg_send(mthd, "SetImp:", 1, imp);
    vz_msg_send(sel, "Release", 0);
    vz_msg_send(imp, "Release", 0);
    vz_msg_send(boolcls->isa, "AddMethod:", 1, mthd);
    vz_msg_send(mthd, "Release", 0);
    
    vz_msg_send(boolcls, "Release", 0);
    
    // Number
    name = vz_string_box("std::Bool");
    iname = vz_string_box("std::Bool.isa");
    ivarc = vz_num_box(1);
    id numcls = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
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
}

// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VOLTZ_STD_H
#define VOLTZ_STD_H

#include <voltz.h>

#define SUBCLASS(super, var, name, ivarc)                                      \
    id var = nil;                                                              \
    {                                                                          \
        id var##_name  = vz_string_box(name);                                  \
        id var##_iname = vz_string_box(name ".Isa");                           \
        id var##_ivarc = vz_num_box(ivarc);                                    \
        var = vz_msg_send(super, "Subclass:::", 3, var##_name, var##_iname,    \
                          var##_ivarc);                                        \
        vz_msg_send(var##_name, "Release", 0);                                 \
        vz_msg_send(var##_iname, "Release", 0);                                \
        vz_msg_send(var##_ivarc, "Release", 0);                                \
    }

#define ADD_MTHD(cls, sel, imp)                                                \
    {                                                                          \
        id _mthdcls = vz_class_get("std::Method");                             \
        id _mthd    = vz_msg_send(_mthdcls, "Alloc", 0);                       \
        id _sel     = vz_sel_box(vz_sel_get(sel));                             \
        id _imp     = vz_imp_box(vz_def(imp));                                 \
        _mthd = vz_msg_send(_mthd, "Init::", 2, _sel, _imp);                   \
        vz_msg_send(cls, "AddMethod:", 1, _mthd);                              \
        vz_msg_send(_mthdcls, "Release", 0);                                   \
        vz_msg_send(_mthd, "Release", 0);                                      \
        vz_msg_send(_sel, "Release", 0);                                       \
        vz_msg_send(_imp, "Release", 0);                                       \
    }

bool InitObjectClass();
bool InitClassClass();
bool InitBoolClass();
bool InitNumberClass();

#endif // VOLTZ_STD_H

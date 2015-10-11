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

#define PROTOCOL(name, var)                                                    \
    id var = nil;                                                              \
    {                                                                          \
        id var##_name   = vz_string_box(name);                                 \
        id protocol_cls = vz_class_get("std::Protocol");                       \
        var             = vz_msg_send(protocol_cls, "Alloc", 0);               \
        var = vz_msg_send(var, "Init:", 1, var##_name);                        \
        vz_msg_send(var##_name, "Release", 0);                                 \
        vz_msg_send(protocol_cls, "Release", 0);                               \
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

#define ADD_SEL(prt, sel)                                                      \
    {                                                                          \
        id s = vz_sel_box(vz_sel_get(sel));                                    \
        vz_msg_send(prt, "AddSelector:", 1, s);                                \
        vz_msg_send(s, "Release", 0);                                          \
    }

bool InitObjectClass();
bool InitClassClass();
bool InitProtocolClass();
bool InitBoolClass();
bool InitNumberClass();
bool InitByteClass();
bool InitArrayClass();
bool InitSelectorClass();

#endif // VOLTZ_STD_H

// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <stdio.h>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id SendMsg(id target, SEL sel, NUM argc, ...) {
    va_list ap;
    va_start(ap, argc);
    id rv = SendMsgV(target, sel, argc, ap);
    va_end(ap);
    return rv;
}

id SendMsgV(id target, SEL sel, NUM argc, va_list ap) {
    id* args = (id*) alloca(sizeof(id) * argc);
    for (NUM k = 0; k < argc; k++) {
        args[(int64_t) k] = va_arg(ap, id);
    }

    return SendMsgA(target, sel, argc, args);
}

id vz_msg_send_saI(id target, SEL sel, NUM argc, id* args) {
    if (target == nil) {
        return nil;
    }

    for (id c = target->isa; c != nil; c = GetClassSuper(c)) {
        for (NUM k = 0; k < GetClassMethodCount(c); k++) {
            if (c->ivars[7].arr[(int64_t) k]->ivars[0].sel == sel) {
                return c->ivars[7].arr[(int64_t) k]->ivars[1].imp->operator()(
                    target, sel, argc, args);
            }
        }
    }
    id s     = BoxSelector(sel);
    id argsa = BoxArray(argc, args);
    id tmp0 = voltz::SendMsg(target, ResolveMessageSend__, 2, sel, argsa);
    if (!UnboxBool(tmp0)) {
        voltz::SendMsg(target, UnrecognizedSelector_, 1, s);
    }
    voltz::SendMsg(s, Release, 0);
    voltz::SendMsg(argsa, Release, 0);
    voltz::SendMsg(tmp0, Release, 0);
    return nil;
}

id (*voltz::SendMsg)(id target, SEL sel, NUM argc, ...) = SendMsg;
id (*voltz::SendMsgV)(id target, SEL sel, NUM argc, va_list ap) = SendMsgV;
id (*voltz::SendMsgA)(id target, SEL sel, NUM argc, id* args) = SendMsgA;

// vz_msg_super

id SendMsgSuper(id target, SEL sel, NUM argc, ...) {
    va_list ap;
    va_start(ap, argc);
    id rv = SendMsgSuperV(target, sel, argc, ap);
    va_end(ap);
    return rv;
}

id SendMsgSuperV(id target, SEL sel, NUM argc, va_list ap) {
    id* args = (id*) alloca(sizeof(id) * argc);
    for (NUM k = 0; k < argc; k++) {
        args[(int64_t) k] = va_arg(ap, id);
    }

    return SendMsgSuperA(target, sel, argc, args);
}

id SendMsgSuperA(id target, SEL sel, NUM argc, id* args) {
    if (target == nil) {
        return nil;
    }

    for (id c = target->isa->ivars[0].obj; c != nil; c = GetClassSuper(c)) {
        for (NUM k = 0; k < GetClassMethodCount(c); k++) {
            if (c->ivars[7].arr[(int64_t) k]->ivars[0].sel == sel) {
                return c->ivars[7].arr[(int64_t) k]->ivars[1].imp->operator()(
                    target, sel, argc, args);
            }
        }
    }

    id s     = BoxSelector(sel);
    id argsa = BoxArrayA(argc, args);
    id tmp0 = voltz::SendMsg(target, ResolveMessageSend__, 2, sel, argsa);
    if (!UnboxBool(tmp0)) {
        voltz::SendMsg(target, UnrecognizedSelector_, 1, s);
    }
    voltz::SendMsg(s, Release, 0);
    voltz::SendMsg(argsa, Release, 0);
    voltz::SendMsg(tmp0, Release, 0);
    return nil;
}

id (*voltz::SendMsgSuper)(id target, SEL sel, NUM argc, ...) = SendMsgSuper;
id (*voltz::SendMsgSuperV)(id target, SEL sel, NUM argc,
                           va_list ap) = SendMsgSuperV;
id (*voltz::SendMsgSuperA)(id target, SEL sel, NUM argc,
                           id* args) = SendMsgSuperA;

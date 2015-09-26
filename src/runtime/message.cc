// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <stdio.h>

extern "C" id(*vz_msg_send_super)(id target, const char* sel, NUM argc, ...);
extern "C" id(*vz_msg_send_super_v)(id target, const char* sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_super_a)(id target, const char* sel, NUM argc, id* args);
extern "C" id(*vz_msg_send_super_s)(id target, SEL sel, NUM argc, ...);
extern "C" id(*vz_msg_send_super_sv)(id target, SEL sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_super_sa)(id target, SEL sel, NUM argc, id* args);

id vz_msg_sendI(id target, const char* sel, NUM argc, ...) {
    va_list ap;
    va_start(ap, argc);
    id rv = vz_msg_send_sv(target, vz_sel_get(sel), argc, ap);
    va_end(ap);
    return rv;
}

id vz_msg_send_vI(id target, const char* sel, NUM argc, va_list ap) {
    return vz_msg_send_sv(target, vz_sel_get(sel), argc, ap);
}

id vz_msg_send_aI(id target, const char* sel, NUM argc, id* args) {
    return vz_msg_send_sa(target, vz_sel_get(sel), argc, args);
}

id vz_msg_send_sI(id target, SEL sel, NUM argc, ...) {
    va_list ap;
    va_start(ap, argc);
    id rv = vz_msg_send_sv(target, sel, argc, ap);
    va_end(ap);
    return rv;
}

id vz_msg_send_svI(id target, SEL sel, NUM argc, va_list ap) {
    id* args = (id*) alloca(sizeof(id) * argc);
    for (NUM k = 0; k < argc; k++) {
        args[(int64_t)k] = va_arg(ap, id);
    }
    
    return vz_msg_send_sa(target, sel, argc, args);
}

id vz_msg_send_saI(id target, SEL sel, NUM argc, id* args) {
    if (target == nil) {
        return nil;
    }
    
    for (id c = target->isa; c != nil; c = vz_class_super(c)) {
        for (NUM k = 0; k < vz_class_mthdc(c); k++) {
            if (c->ivars[7].arr[(int64_t)k]->ivars[0].sel == sel) {
                return c->ivars[7].arr[(int64_t)k]->ivars[1].imp->operator()(target, sel, argc, args);
            }
        }
    }
    
    fprintf(stderr, "%s (%p) does not implement the method %s\n", vz_class_name(target->isa), target->isa, sel->value);
    abort();
}

id(*vz_msg_send)(id target, const char* sel, NUM argc, ...) = vz_msg_sendI;
id(*vz_msg_send_v)(id target, const char* sel, NUM argc, va_list ap) = vz_msg_send_vI;
id(*vz_msg_send_a)(id target, const char* sel, NUM argc, id* args) = vz_msg_send_aI;
id(*vz_msg_send_s)(id target, SEL sel, NUM argc, ...) = vz_msg_send_sI;
id(*vz_msg_send_sv)(id target, SEL sel, NUM argc, va_list ap) = vz_msg_send_svI;
id(*vz_msg_send_sa)(id target, SEL sel, NUM argc, id* args) = vz_msg_send_saI;


// vz_msg_super

id vz_msg_send_superI(id target, const char* sel, NUM argc, ...) {
    va_list ap;
    va_start(ap, argc);
    id rv = vz_msg_send_super_sv(target, vz_sel_get(sel), argc, ap);
    va_end(ap);
    return rv;
}

id vz_msg_send_super_vI(id target, const char* sel, NUM argc, va_list ap) {
    return vz_msg_send_super_sv(target, vz_sel_get(sel), argc, ap);
}

id vz_msg_send_super_aI(id target, const char* sel, NUM argc, id* args) {
    return vz_msg_send_super_sa(target, vz_sel_get(sel), argc, args);
}

id vz_msg_send_super_sI(id target, SEL sel, NUM argc, ...) {
    va_list ap;
    va_start(ap, argc);
    id rv = vz_msg_send_super_sv(target, sel, argc, ap);
    va_end(ap);
    return rv;
}

id vz_msg_send_super_svI(id target, SEL sel, NUM argc, va_list ap) {
    id* args = (id*) alloca(sizeof(id) * argc);
    for (NUM k = 0; k < argc; k++) {
        args[(int64_t)k] = va_arg(ap, id);
    }
    
    return vz_msg_send_super_sa(target, sel, argc, args);
}

id vz_msg_send_super_saI(id target, SEL sel, NUM argc, id* args) {
    if (target == nil) {
        return nil;
    }
    
    for (id c = target->isa->ivars[0].obj; c != nil; c = vz_class_super(c)) {
        for (NUM k = 0; k < vz_class_mthdc(c); k++) {
            if (c->ivars[7].arr[(int64_t)k]->ivars[0].sel == sel) {
                return c->ivars[7].arr[(int64_t)k]->ivars[1].imp->operator()(target, sel, argc, args);
            }
        }
    }
    
    fprintf(stderr, "%s (%p) does not implement the method %s\n", vz_class_name(target->isa), target->isa, sel->value);
    abort();
}

id(*vz_msg_send_super)(id target, const char* sel, NUM argc, ...) = vz_msg_send_superI;
id(*vz_msg_send_super_v)(id target, const char* sel, NUM argc, va_list ap) = vz_msg_send_super_vI;
id(*vz_msg_send_super_a)(id target, const char* sel, NUM argc, id* args) = vz_msg_send_super_aI;
id(*vz_msg_send_super_s)(id target, SEL sel, NUM argc, ...) = vz_msg_send_super_sI;
id(*vz_msg_send_super_sv)(id target, SEL sel, NUM argc, va_list ap) = vz_msg_send_super_svI;
id(*vz_msg_send_super_sa)(id target, SEL sel, NUM argc, id* args) = vz_msg_send_super_saI;

// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

VM voltz::VoltzVM;

SEL selectors::Alloc                 = GetSelector("Alloc");
SEL selectors::Init                  = GetSelector("Init");
SEL selectors::Retain                = GetSelector("Retain");
SEL selectors::Release               = GetSelector("Release");
SEL selectors::AddMethod_            = GetSelector("AddMethod:");
SEL selectors::New                   = GetSelector("New");
SEL selectors::Deinit                = GetSelector("Deinit");
SEL selectors::SetSel_               = GetSelector("SetSel:");
SEL selectors::SetImp_               = GetSelector("SetImp:");
SEL selectors::sel                   = GetSelector("sel");
SEL selectors::imp                   = GetSelector("imp");
SEL selectors::Init__                = GetSelector("Init::");
SEL selectors::New__                 = GetSelector("New::");
SEL selectors::Subclass___           = GetSelector("Subclass:::");
SEL selectors::Register              = GetSelector("Register");
SEL selectors::Isa                   = GetSelector("Isa");
SEL selectors::True                  = GetSelector("True");
SEL selectors::False                 = GetSelector("False");
SEL selectors::Count                 = GetSelector("Count");
SEL selectors::value                 = GetSelector("value");
SEL selectors::ResolveMessageSend__  = GetSelector("ResolveMessageSend::");
SEL selectors::UnrecognizedSelector_ = GetSelector("UnrecognizedSelector:");

id voltz::classes::Object   = nil;
id voltz::classes::Class    = nil;
id voltz::classes::Method   = nil;
id voltz::classes::Selector = nil;
id voltz::classes::Imp      = nil;
id voltz::classes::Number   = nil;
id voltz::classes::Byte     = nil;
id voltz::classes::String   = nil;
id voltz::classes::Char     = nil;
id voltz::classes::Bool     = nil;
id voltz::classes::Array    = nil;
id voltz::classes::Tuple    = nil;

id BoxBool(bool value) {
    id rv = SendMsg(Bool, value ? True : False, 0);
    return rv;
}

id (*voltz::BoxBool)(bool) = BoxBool;

bool UnboxBool(id obj) {
    if (obj == nil) {
        return false;
    }
    return obj->ivars[0].num != 0;
}

bool (*voltz::UnboxBool)(id) = UnboxBool;

id* UnboxArray(id obj, NUM* crv) {
    id count = SendMsg(obj, Count, 0);
    NUM c = UnboxNumber(count);
    if (crv != nil) {
        *crv = c;
    }
    id* rv = (id*) malloc(sizeof(id) * c);
    for (NUM k = 0; k < c; k++) {
        rv[(int64_t) k] = SendMsg(obj->ivars[1].arr[(int64_t) k], Retain, 0);
    }
    SendMsg(count, Release, 0);
    return rv;
}

id* (*voltz::UnboxArray)(id, NUM*) = UnboxArray;

id BoxArray(NUM count, ...) {
    va_list ap;
    va_start(ap, count);
    id rv = BoxArrayV(count, ap);
    va_end(ap);
    return rv;
}

id (*voltz::BoxArray)(NUM, ...) = BoxArray;

id BoxArrayV(NUM count, va_list ap) {
    id* args = (id*) malloc(sizeof(id) * count);
    for (NUM k = 0; k < count; k++) {
        args[(int64_t) k] = va_arg(ap, id);
    }

    id rv = BoxArrayA(count, args);
    free(args);
    return rv;
}

id (*voltz::BoxArrayV)(NUM, va_list) = BoxArrayV;

id BoxArrayA(NUM count, id* args) {
    id rv = SendMsg(Array, New, 0);

    rv->ivars[0].num = count;
    rv->ivars[1].arr = (id*) malloc(sizeof(id) * count);
    for (NUM k = 0; k < count; k++) {
        rv->ivars[1].arr[(int64_t) k] = SendMsg(args[(int64_t) k], Retain, 0);
    }

    return rv;
}

id (*voltz::BoxArrayA)(NUM, id*) = BoxArrayA;

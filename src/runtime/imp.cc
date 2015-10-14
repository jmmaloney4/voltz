// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id BoxImp(IMP imp) {
    id rv            = SendMsg(Imp, Alloc, 0);
    rv->ivars[0].imp = imp;
    return rv;
}

id (*voltz::BoxImp)(IMP) = BoxImp;

IMP UnboxImp(id obj) {
    IMP rv = new std::function<id(id, SEL, NUM, id*) >(*obj->ivars[0].imp);
    return rv;
}

IMP (*voltz::UnboxImp)(id) = UnboxImp;
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

id BoxNumber(NUM value) {
    id rv            = SendMsg(Number, New, 0);
    rv->ivars[0].num = value;
    return rv;
}

id (*voltz::BoxNumber)(NUM) = BoxNumber;

NUM UnboxNumber(id obj) {
    if (obj == nil) {
        return 0;
    }
    return obj->ivars[0].num;
}

NUM (*voltz::UnboxNumber)(id) = UnboxNumber;

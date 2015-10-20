// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id BoxByte(BYTE value) {
    id rv            = SendMsg(Byte, New, 0);
    rv->ivars[0].num = (NUM) value;
    return rv;
}

id (*voltz::BoxByte)(BYTE) = BoxByte;

BYTE UnboxByte(id obj) { return (BYTE) obj->ivars[0].num; }

BYTE (*voltz::UnboxByte)(id) = UnboxByte;
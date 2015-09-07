// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"

id vz_imp_boxI(IMP imp) {
    id impcls = vz_class_get("std::Imp");
    id rv = vz_msg_send(impcls, "Alloc", 0);
    rv = vz_msg_send(rv, "Init", 0);
    
    rv->ivars[0].imp = imp;
    
    return rv;
}

id (*vz_imp_box)(IMP) = vz_imp_boxI;

IMP vz_imp_unboxI(id obj) {
    return obj->ivars[0].imp;
}

IMP (*vz_imp_unbox)(id) = vz_imp_unboxI;
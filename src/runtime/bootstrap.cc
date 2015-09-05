// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

extern "C" void vz_bootstrap_runtime(int argc, const char** argv) {
    
    id objcls = vz_object_alloc(8);
    id clscls = vz_object_alloc(8);
    id numcls = vz_object_alloc(1);
    id charcls = vz_object_alloc(1);
    id stringcls = vz_object_alloc(2);
    
    
    
}
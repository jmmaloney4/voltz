// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include "std.h"

extern "C" const char* VoltzModuleName = "std";

extern "C" bool VoltzModuleInitialize_std() {

    if (!InitObjectClass()) {
        return false;
    }

    if (!InitClassClass()) {
        return false;
    }

    if (!InitBoolClass()) {
        return false;
    }

    if (!InitNumberClass()) {
        return false;
    }

    return true;
}
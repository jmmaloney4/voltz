// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <ctime>
#include <cstdio>

double StartupTime;

int main(int argc, const char** argv) {

    clock_t begin, end;
    begin = clock();

    vz_bootstrap_runtime(argc, argv);

    end = clock();

    StartupTime = (end - begin) / CLOCKS_PER_SEC;

#ifdef VOLTZ_DEBUG
    printf("Took %f seconds to startup.\n", StartupTime);
#endif

    vz_linker_entry(nil, nil);
}

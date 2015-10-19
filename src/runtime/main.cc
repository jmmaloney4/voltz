// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <ctime>
#include <cstdio>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

double voltz::StartupTime;

void Main(int argc, const char** argv, const char* lib, const char* cls) {

    clock_t begin, end;
    begin = clock();

    BootstrapRuntime(argc, argv);

    end = clock();

    StartupTime = (end - begin) / CLOCKS_PER_SEC;

#ifdef VOLTZ_DEBUG
    printf("Took %f seconds to startup.\n", StartupTime);
#endif

    LoadModule("std");

    LoadModule(lib);
    id maincls = GetClass(cls);
    id rv      = SendMsg(maincls, GetSelector("Main::"), 2, BoxNumber(argc), nil);
}

void (*voltz::Main)(int argc, const char** argv, const char* lib,
                    const char* cls) = ::Main;

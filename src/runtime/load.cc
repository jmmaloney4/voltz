// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <cstdlib>
#include <cstdio>
#include <dlfcn.h>
#include <cstring>

bool vz_load_moduleI(const char* name) {

    const char* vz_path = getenv(VOLTZ_PATH_ENVVAR);
    if (!vz_path) {
        const char* home = getenv("HOME");
        vz_path = "/voltz/modules/:/opt/voltz/modules/";
        char buf[strlen(home) + strlen(vz_path) + 2];
        sprintf(buf, "%s%s", home, vz_path);
        vz_path = strdup(buf);
    } else {
        vz_path = strdup(vz_path);
    }

    char* str = strdup(vz_path);
    char* token;
    while ((token = strsep(&str, ":")) != NULL) {

        char buf[strlen(token) + strlen(name) + strlen(VOLTZ_MODULE_EXT) + 3];
        sprintf(buf, "%s/%s.%s", token, name, VOLTZ_MODULE_EXT);
        printf("%s\n", buf);

        void* lib = dlopen(buf, RTLD_LOCAL | RTLD_NODELETE);

        if (!lib) {
            continue;
        }

        bool (*initfn)() = (bool (*) ()) dlsym(lib, "VoltzModuleInitialize");
        bool initrv = initfn();

        free(str);
        free((void*) vz_path);
        dlclose(lib);
        return initrv;
    }

    free(str);
    free((void*) vz_path);

    return true;
}

bool (*vz_load_module)(const char*) = vz_load_moduleI;
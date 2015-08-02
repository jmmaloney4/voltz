// main.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"

using namespace voltz;

int main() {
    FILE* f = fopen("/Users/jack/Desktop/voltz/demo.vzs", "r");
    int64_t c = 0;
    Instruction* i = LoadAssemblyFile(f, &c);
    
    for (int64_t k = 0; k < c; k++) {
        printf("%s\n", GetNameForInstruction(i[k].type));
    }
}

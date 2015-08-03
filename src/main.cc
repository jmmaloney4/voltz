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
    
    FILE* o = fopen("/Users/jack/Desktop/out.vzs", "w");
    WriteAssemblyFile(o, i, c);
}
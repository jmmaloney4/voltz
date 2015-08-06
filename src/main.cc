// main.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace voltz;

int main(int argc, const char** argv) {
    
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <assemble | disassemble> [file] [outfile]\n", argv[0]);
        exit(1);
    }
    
    FILE* file = fopen(argv[2], "r");
    if (!file) {
        fprintf(stderr, "Bad Filename: %s\n", argv[2]);
        exit(1);
    }
    
    FILE* outfile = fopen(argv[3], "w");
    if (!file) {
        fprintf(stderr, "Bad Filename: %s\n", argv[3]);
        exit(1);
    }
    
    if (strcmp(argv[1], "assemble") == 0) {
        int64_t size = 0;
        Instruction* i = LoadAssemblyFile(file, &size);
        
        WriteBinaryFile(outfile, i, size);
    } else if (strcmp(argv[1], "disassemble") == 0) {
        int64_t size = 0;
        Instruction* i = LoadBinaryFile(file, &size);
        
        WriteAssemblyFile(outfile, i, size);
    }
    
}
/* ----------------------------------------------------------------------------
 
 Copyright (c) 2014, Jack Maloney
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 ---------------------------------------------------------------------------- */

#include "mach.h"
#include <stdlib.h>

union ivar {
public:
    id obj;
    int_t i64;
    flt_t f64;
    Imp imp;
    Sel sel;
    
    operator id() { return this->obj; }
    ivar operator=(id x) { this->obj = x; return *this; }
};

struct object {
public:
    int_t refs;
    Class isa;
    ObjectType type;
    ivar ivars[0];
};

ObjectType GetType(id x) {
    return x->type;
}

int_t GetRefs(id x) {
    return x->refs;
}

void SetRefs(id x, int_t r) {
    x->refs = r;
}

void IncRefs(id x) {
    x->refs++;
}

void DecRefs(id x) {
    x->refs--;
}

Class GetClass(id x) {
    return x->isa;
}

bool IsOfKind(id x, Class c) {
    for (; c != NULL; c = ClassSuper(c)) {
        if (c == x->isa) {
            return true;
        }
    }
    return false;
}

MACH_MTHD(ObjectAlloc) {
    id rv = (id) malloc(sizeof(struct object) + (ClassIVarc((Class) self) * sizeof(ivar)));
    rv->isa = (Class) self;
    rv->refs = 1;
    rv->type = ObjectTypeObj;
    return rv;
}

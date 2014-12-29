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

#include "machrt.h"

Class MAClsGetMetaCls(Class c) {
    return c->isa;
}

Class MAClsGetSuper(Class c) {
    return c->super;
}

const char* MAClsGetName(Class c) {
    return c->name;
}

int_t MAClsGetMthdc(Class c) {
    return c->mthdc;
}

int_t MAClsGetIvarc(Class c) {
    return c->ivarc;
}

Imp MAClsGetImpForSel(Class c, Sel s) {
    for (int_t k = 0; k < c->mthdc; k++) {
        if (c->mthdd[k].sel == s) {
            return c->mthdd[k].imp;
        }
    }
    return NULL;
}

void MAClsSetImpForSel(Class c, Sel s, Imp i) {
    for (int_t k = 0; k < c->mthdc; k++) {
        if (c->mthdd[k].sel == s) {
            c->mthdd[k].imp = i;
        }
    }
}

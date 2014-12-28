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

#ifndef MACHRT_MACHRT_H
#define MACHRT_MACHRT_H

#include "include/config.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifdef __cplusplus
#define MACH_IMP(name) extern "C" id name (id self, Sel cmd, id* argv)
#else
#define MACH_IMP(name) id name (id self, Sel cmd, id* argv)
#endif

typedef struct mach_object* id;
typedef struct mach_class* Class;
typedef struct mach_selector* Sel;
typedef struct mach_method Method;
typedef id (*Imp) (id, Sel, id*);

struct mach_method {
    Sel sel;
    Imp imp;
};

struct mach_selector {
    const char* str;
    int_t args;
    Bool rets;
};

#ifdef __cplusplus
extern "C" {
#endif
    
    Class MAObjGetClass(id x);
    int_t MAObjGetRefs(id x);
    void MAObjSetRefs(id x, int_t k);
    void MAObjIncRefs(id x);
    void MAObjDecRefs(id x);
    
    Class MAClsGetMetaCls(Class c);
    Class MAClsGetSuper(Class c);
    const char* MAClsGetName(Class c);
    int_t MAClsGetMthdc(Class c);
    int_t MAClsGetIvarc(Class c);
    Imp MAClsGetImpForSel(Class c, Sel s);
    void MAClsSetImpForSel(Class c, Sel s, Imp i);
    
    Sel MAGetSel(const char* str);
    
#ifdef __cplusplus
}
#endif

#endif

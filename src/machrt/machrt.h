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
#include <pthread.h>
#include <setjmp.h>
#include <stdarg.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

/**
 *  A NULL instance.
 */
#define nil ((MAId)0)

#ifdef __cplusplus
#define MACH_IMP(name) extern "C" id name (ExecContext cntx, id* argv)
#else
#define MACH_IMP(name) id name (ExecContext cntx, id* argv)
#endif

typedef struct MAObject_* MAId;
typedef struct MAClass_* MAClass;
typedef struct MAMethod_ MAMethod;
typedef struct MASel_* MASel;
typedef struct MAExecContext_* MAExecContext;
typedef struct MAImp_ MAImp;
typedef struct MAModule_* MAModule;

struct MAImp_ {
    MAId (*val) (MAExecContext, MAId*);
    MAInt args;
};

struct MAObject_ {
    MAClass isa;
    MAInt refs;
    MAId ivars[0];
};

struct MAMethod_ {
    MASel sel;
    MAImp imp;
};

struct MAClass_ {
    MAClass isa;
    MAClass super;
    const char* name;
    MAInt ivarc;
    MAInt mthdc;
    MAMethod mthdd[0];
};

struct MASel_ {
    const char* str;
};

struct MAModule_ {
    MAImp* imps;
    MAInt impc;
    const char** impn;
    
    MAClass* classes;
    MAInt classc;
    const char** classn;
};

#ifdef __cplusplus
extern "C" {
#endif
    
    MAId MAExecMethod(MAId obj, MASel sel, MAExecContext cntx, ...);
    MAId MAExecMethodVA(MAId obj, MASel sel, MAExecContext cntx, va_list ap);
    MAId MAExecMethodAR(MAId obj, MASel sel, MAExecContext cntx, MAId* args);
    
    MABool MAIsOfKind(MAId obj, MAClass cls);
    
    MASel MAGetSel(const char* val);
    
    void MALoadModule(const char* name);
    MAClass MAGetClass(const char* name);
    MAImp MAGetImp(const char* name);
    
    extern MAClass MAObject;
    
    extern MASel AllocSel;
    
#ifdef __cplusplus
}
#endif

#endif

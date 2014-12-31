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

#ifndef NULL
#define NULL ((void*)0)
#endif

/**
 *  A NULL instance.
 */
#define nil ((MAId)0)

#ifdef __cplusplus
#define MACH_IMP(name) extern "C" id name (id self, Sel cmd, ExecContext cntx, id* argv)
#else
#define MACH_IMP(name) id name (id self, Sel cmd, ExecContext cntx, id* argv)
#endif

typedef struct MAObject* MAId;
typedef struct MAClass* MAClass;
typedef struct MAMethod MAMethod;
typedef struct MASelector* MASel;
typedef struct MAExecContext* MAExecContext;
typedef MAId (*MAImp) (MAId, MASel, MAExecContext, MAId*);

struct MAObject {
    MAClass isa;
    MAInt refs;
    MAId ivars[0];
};

struct MAMethod {
    MASel sel;
    MAImp imp;
};

struct MAClass {
    MAClass isa;
    MAClass super;
    const char* name;
    MAInt ivarc;
    MAInt mthdc;
    MAMethod mthdd[0];
};

struct MASelector {
    const char* str;
    MAInt args;
    MABool rets;
};

#ifdef __cplusplus
extern "C" {
#endif
    
    /** 
     *  Send the specified message to a given object.
     *  
     *  @param targ
     *      The target object.
     *  @param sel
     *      The selector of the message to send.
     *  @param cntx
     *      The Execution Context that the message should be run on.
     *  @param ...
     *      A comma-seperated list of the arguments to be passed when the 
     *      message is sent.
     *
     *  @return The return value of the message, or nil if @c targ is nil.
     */
    MAId MASendMsg(MAId targ, MASel sel, MAExecContext cntx, ...);
    
    /**
     *  Get the class of a given object.
     *  
     *  @param obj
     *      The object to get the class of.
     *
     *  @return The class of @c obj.
     */
    inline MAClass MAObjGetClass(MAId obj) {
        return obj->isa;
    }
    
    /**
     *  Get the superclass of a given class.
     *
     *  @param cls
     *      The class to get the superclass of.
     *
     *  @return The superclass of @c cls.
     */
    inline MAClass MAClsGetSuper(MAClass cls) {
        return cls->super;
    }
    
    /**
     *  Get the number of methods a given class has.
     *  
     *  @param cls
     *      The class to get the method count of.
     *  
     *  @return The number of methods @c cls has.
     */
    MAInt MAClsGetMthdc(MAClass cls) {
        return cls->mthdc;
    }
    
#ifdef __cplusplus
}
#endif

#endif

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
#include <stdlib.h>
#include <stdarg.h>

void InitializeRuntime() {
    
}

MAId MAExecMethod(MAId obj, MASel sel, MAExecContext cntx, ...) {
    va_list ap;
    va_start(ap, cntx);
    MAId rv = MAExecMethodVA(obj, sel, cntx, ap);
    va_end(ap);
    return rv;
}

MAImp MAGetImp_(MAClass cls, MASel sel) {
    for (; cls != NULL; cls = cls->super) {
        for (MAInt k = 0; k < cls->mthdc; k++) {
            if (cls->mthdd[k].sel == sel) {
                return cls->mthdd[k].imp;
            }
        }
    }
    MAImp l = { NULL, -1 };
    return l;
}

MAId MAExecMethodVA(MAId obj, MASel sel, MAExecContext cntx, va_list ap) {
    if (obj == nil) {
        return nil;
    }
    
    MAImp i = MAGetImp_(obj->isa, sel);
    MAId* arr = alloca(sizeof(MAId) * i.args);
    for (MAInt k = 0; k < i.args; k++) {
        arr[k] = va_arg(ap, MAId);
    }
    return i.val(cntx, arr);
}

MAId MAExecMethodAR(MAId obj, MASel sel, MAExecContext cntx, MAId* args) {
    if (obj == nil) {
        return nil;
    }
    
    return MAGetImp_(obj->isa, sel).val(cntx, args);
}

MABool MAIsOfKind(MAId obj, MAClass cls) {
    if (obj == nil) {
        return false;
    }
    
    for (; cls != NULL; cls = cls->super) {
        if (obj->isa == cls) {
            return true;
        }
    }
    return false;
}

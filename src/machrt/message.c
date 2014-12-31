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
#include <stdarg.h>
#include <stdlib.h>

MAId MASendMsg(MAId targ, MASel sel, MAExecContext cntx, ...) {
    if (targ == nil) {
        return nil;
    }
    
    //  iterate through each class in the hierarchy starting at the bottom, the
    //  class of the target object. Then iterate through each method to find the
    //  one that matches the specified selector.
    for (MAClass c = MAObjGetClass(targ); c != NULL; c = MAClsGetSuper(c)) {
        MAInt mc = MAClsGetMthdc(c);
        for (MAInt k = 0; k < mc; k++) {
            if (c->mthdd[k].sel == sel) {
                MAId* arr = malloc(sizeof(MAId) * sel->args);
                va_list ap;
                va_start(ap, cntx);
                for (MAInt i = 0; i < sel->args; i++) {
                    arr[i] = va_arg(ap, MAId);
                }
                va_end(ap);
                
                MAId rv = c->mthdd[k].imp(targ, sel, cntx, arr);
                free(arr);
                return rv;
            }
        }
    }
    
    abort();
}
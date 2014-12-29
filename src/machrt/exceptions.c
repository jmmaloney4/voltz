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

void MAPushExceptionFrame(ExecContext cntx, MAJmpBuf catchbuf) {
    struct mach_exception_frame_stack_node* n = malloc(sizeof(struct mach_exception_frame_stack_node));
    n->catchbuf = catchbuf;
    n->next = cntx->estack.node;
    cntx->estack.node = n;
}

MAJmpBuf MAPopExceptionFrame(ExecContext cntx) {
    struct mach_exception_frame_stack_node* n = cntx->estack.node;
    struct mach_exception_frame_stack_node* n2 = cntx->estack.node->next;
    cntx->estack.node = n2;
    MAJmpBuf rv = n->catchbuf;
    free(n);
    return rv;
}

void MAThrowException(ExecContext cntx, id excep) {
    cntx->excep = excep;
    MAJmpBuf buf = MAPopExceptionFrame(cntx);
    longjmp(buf.val, 0);
}


#define try { \
MAJmpBuf buf; \
if (!setjmp(buf.val)) { \
MAPushExceptionFrame(cntx, buf);

#define catch } else {

#define finally

#define throw(cntx, excep) MAThrowException(cntx, excep)

#define yrt }}

#include <stdio.h>

void a(ExecContext c) {
    printf("throw\n");
    throw(c, nil);
}

void test() {
    
    printf("hello\n");
    
    ExecContext cntx = malloc(sizeof(struct mach_exec_context));
    cntx->uid = 0;
    
    try {
        a(cntx);
    } catch {
        printf("catch: %p\n", cntx->excep);
    }
    yrt

    free(cntx);
}

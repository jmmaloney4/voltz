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
#include <string.h>

#define MASelTableSize 5000

struct MASelTableNode {
    struct mach_selector sel;
    struct MASelTableNode* next;
};

struct MASelTableNode** MASelTable;

int_t MASelHash(const char* str, int_t* args, Bool* r) {
    int_t hash = 5417;
    *r = (*str++ == ':');
    *args = 0;
    while (*str) {
        char c = *str++;
        *args += (c == ':' ? 1 : 0);
        hash = hash * 101 + c;
    }
    return hash;
}

Sel MAGetSel(const char* str) {
    if (!MASelTable) {
        MASelTable = malloc(sizeof(struct MASelTableNode) * MASelTableSize);
    }
    
    int_t args;
    Bool rets;
    int_t hash = MASelHash(str, &args, &rets);
    hash %= MASelTableSize;
    
    struct MASelTableNode* node = MASelTable[hash];
    for (; true; node = node->next) {
        if (strcmp(node->sel.str, str) == 0) {
            return &node->sel;
        }
        if (node->next == NULL) {
            break;
        }
    }
    
    struct MASelTableNode* n = malloc(sizeof(struct MASelTableNode));
    n->next = NULL;
    node->next = n;
    n->sel.args = args;
    n->sel.rets = rets;
    n->sel.str = str;
    
    return &n->sel;
}

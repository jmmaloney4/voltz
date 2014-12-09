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
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mem_mutex0;
pthread_mutex_t mem_mutex1;
pthread_mutex_t mem_mutex2;
pthread_mutex_t mem_mutex3;
pthread_mutex_t mem_mutex4;

void InitializeMutexes() {
    pthread_mutex_init(&mem_mutex0, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex1, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex2, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex3, (pthread_mutexattr_t*) NULL);
    pthread_mutex_init(&mem_mutex4, (pthread_mutexattr_t*) NULL);
}

pthread_mutex_t* GetMutex(id x) {
    switch (((long) x) % 4) {
        case 0:
            return &mem_mutex0;
            break;
        case 1:
            return &mem_mutex1;
            break;
        case 2:
            return &mem_mutex2;
            break;
        case 3:
            return &mem_mutex3;
            break;
        case 4:
            return &mem_mutex4;
            break;
        default:
            return (pthread_mutex_t*) NULL;
            break;
    }
}

MACH_MTHD(ObjectRetain) {
    pthread_mutex_t* mut = GetMutex(self);
    pthread_mutex_lock(mut);
    IncRefs(self);
    pthread_mutex_unlock(mut);
    return self;
}

MACH_MTHD(ObjectRelease) {
    pthread_mutex_t* mut = GetMutex(self);
    pthread_mutex_lock(mut);
    DecRefs(self);
    if (GetRefs(self) <= 0) {
        SendMsg(self, GetSel(u8"Deinit()"));
        free(self);
        pthread_mutex_unlock(mut);
        return nil;
    }
    pthread_mutex_unlock(mut);
    return self;
}

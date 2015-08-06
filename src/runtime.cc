// runtime.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"

using namespace voltz;

#if defined (__GNUC__)
#define ATTRIBUTE_TLS __thread
#elif defined (_MSC_VER)
#define ATTRIBUTE_TLS __declspec(thread)
#else // !__GNUC__ && !_MSC_VER
#error "Define a thread local storage qualifier for your compiler/platform!"
#endif

ATTRIBUTE_TLS Thread CurrentThread;

inline void SetCurrentThread(Thread t) {
    CurrentThread = t;
}

inline Thread GetCurrentThread() {
    return CurrentThread;
}

Object SendMessage(Object target, Selector sel, int64_t argc, ...) {
    
    if (target == nil) {
        return nil;
    }
    
    for (Class c = target->isa; c != nil; c = c->super) {
        for (int64_t k = 0; k < c->mthdc; k++) {
            if (c->mthdv[k]->sel == sel) {
                
                
                
            }
        }
    }
    
}

void voltz::Release(Object o) {
    
}

Object voltz::Retain(Object o) {
    return o;
}

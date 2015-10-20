// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <thread>
#include <cstdlib>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id CreateThread(IMP fn) {
    id thrd = SendMsg(Thread, New, 0);
    SetInstanceVariable(thrd, imp, (id) fn);
    SetInstanceVariable(thrd, rv, nil);
    SetInstanceVariable(thrd, handle, nil);
    return thrd;
}

id (*voltz::CreateThread)(IMP) = ::CreateThread;

void StartThread(id thrd, NUM argc, ...) {
    va_list ap;
    va_start(ap, argc);
    StartThreadV(thrd, argc, ap);
    va_end(ap);
}

void (*voltz::StartThread)(id, NUM, ...) = ::StartThread;

void StartThreadV(id thrd, NUM argc, va_list ap) {
    id* args = (id*) alloca(sizeof(id) * argc);
    for (NUM k = 0; k < argc; k++) {
        args[(int64_t) k] = va_arg(ap, id);
    }

    StartThreadA(thrd, argc, args);
}

void (*voltz::StartThreadV)(id, NUM, va_list) = ::StartThreadV;

void StartThreadA(id thrd, NUM argc, id* args) {
    // IMP fn = (IMP)GetInstanceVariable(thrd, imp);
    // std::thread* handle = new std::thread(fn, thrd, nil, args);
    // SetInstanceVariable(thrd, selectors::handle, (id)handle);
}

void (*voltz::StartThreadA)(id, NUM, id*) = ::StartThreadA;

id JoinThread(id thrd) {
    std::thread* handle =
        (std::thread*) GetInstanceVariable(thrd, selectors::handle);
    handle->join();
    return GetInstanceVariable(thrd, rv);
}

__thread id CurrentThread = nil;

id GetCurrentThread() { return CurrentThread; }

void SetCurrentThread(id thrd) { CurrentThread = thrd; }

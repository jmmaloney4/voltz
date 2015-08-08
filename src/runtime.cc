// runtime.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"
#include <stdlib.h>
#include <queue>
#include <thread>

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

void voltz::Push(Thread t, Object o) {
    t->tp++;
    t->stack[t->tp] = Retain(o);
}

Object voltz::Pop(Thread t) {
    Object rv = t->stack[t->tp];
    t->tp--;
    
    return rv;
}

// UPDATE ME once threads are working.
Object CallImpOnCurrentThread(Imp imp, Object self, Selector sel, int64_t argc, Object* args) {
    Thread t = GetCurrentThread();
    
    t->mutex.lock();
    
    Push(t, (Object) t->tp);
    Push(t, self);
    
    t->code = imp;
    
    t->mutex.unlock();
}

Object voltz::SendMessage(Object target, Selector sel, int64_t argc, ...) {
    
    if (target == nil) {
        return nil;
    }
    
    for (Class c = target->isa; c != nil; c = c->super) {
        for (int64_t k = 0; k < c->mthdc; k++) {
            if (c->mthdv[k]->sel == sel) {
                
                Object* args = (Object*) alloca(sizeof(Object) * argc);
                va_list ap;
                va_start(ap, argc);
                for (int64_t k = 0; k < argc; k++) {
                    args[k] = Retain(va_arg(ap, Object));
                }
                
                Object rv = CallImpOnCurrentThread(c->mthdv[k]->imp, target, sel, argc, args);
                return rv;
            }
        }
    }
    
    return nil;
}

void voltz::Release(Object o) {
    SendMessage(o, GetSelector("Release()"), 0);
}

Object voltz::Retain(Object o) {
    Object rv = SendMessage(o, GetSelector("Retain()"), 0);
    return rv;
}

std::queue<Thread> ThreadQueue;
const int64_t ThreadTableSize = 0x10;
std::thread* ThreadTable[ThreadTableSize];

void ThreadStartFunc() {
    
}

void VoltzMain(const char* path) {
    
    FILE* file = fopen(path, "r");
    int64_t size = 0;
    Instruction* insts = LoadBinaryFile(file, &size);
    if (size == -1 && insts == NULL) {
        insts = LoadAssemblyFile(file, &size);
    }
    
    // Object Class
    Class ObjectCls = new voltz_class();
    ObjectCls->isa = new voltz_class();
    ObjectCls->isa->isa = ObjectCls->isa;
    
    ObjectCls->super = NULL;
    ObjectCls->name = "std::Object";
    ObjectCls->protocolc = 0;
    ObjectCls->protocols = new Protocol[ObjectCls->protocolc]();
    ObjectCls->ivarc = 0;
    ObjectCls->mthdc = 0;
    ObjectCls->mthdv = new Method[ObjectCls->mthdc]();
    
    ObjectCls->isa->super = ObjectCls;
    ObjectCls->isa->name = "std::Object.isa";
    ObjectCls->isa->protocolc = 0;
    ObjectCls->isa->protocols = new Protocol[ObjectCls->isa->protocolc]();
    ObjectCls->isa->ivarc = 0;
    ObjectCls->isa->mthdc = 1;
    ObjectCls->isa->mthdv = new Method[ObjectCls->isa->mthdc]();
    
    RegisterObjectForName(ObjectCls, ObjectCls->name);
    
    // Protocol Class
    Class ProtocolCls = new voltz_class();
    ProtocolCls->isa = new voltz_class();
    ProtocolCls->isa->isa = ObjectCls->isa;
    
    ProtocolCls->super = ObjectCls;
    ProtocolCls->name = "std::Protocol";
    ProtocolCls->protocolc = 0;
    ProtocolCls->protocols = new Protocol[ProtocolCls->protocolc]();
    ProtocolCls->ivarc = 0;
    ProtocolCls->mthdc = 0;
    ProtocolCls->mthdv = new Method[ProtocolCls->mthdc]();
    
    ProtocolCls->isa->super = ObjectCls->isa;
    ProtocolCls->isa->name = "std::Protocol.isa";
    ProtocolCls->isa->protocolc = 0;
    ProtocolCls->isa->protocols = new Protocol[ProtocolCls->isa->protocolc]();
    ProtocolCls->isa->mthdc = 0;
    ProtocolCls->isa->mthdv = new Method[ProtocolCls->isa->mthdc]();
    
    RegisterObjectForName(ProtocolCls, ProtocolCls->name);
    
    // Selector Class
    Class SelectorCls = new voltz_class();
    SelectorCls->isa = new voltz_class();
    SelectorCls->isa->isa = ObjectCls->isa;
    
    SelectorCls->super = ObjectCls;
    SelectorCls->name = "std::Selector";
    SelectorCls->protocolc = 0;
    SelectorCls->protocols = new Protocol[SelectorCls->protocolc]();
    SelectorCls->ivarc = 0;
    SelectorCls->mthdc = 0;
    SelectorCls->mthdv = new Method[SelectorCls->mthdc]();

    SelectorCls->isa->super = ObjectCls->isa;
    SelectorCls->isa->name = "std::Selector.isa";
    SelectorCls->isa->protocolc = 0;
    SelectorCls->isa->protocols = new Protocol[SelectorCls->isa->protocolc]();
    SelectorCls->isa->mthdc = 0;
    SelectorCls->isa->mthdv = new Method[SelectorCls->isa->mthdc]();

    RegisterObjectForName(SelectorCls, SelectorCls->name);
    
    // Imp Class
    Class ImpCls = new voltz_class();
    ImpCls->isa = new voltz_class();
    ImpCls->isa->isa = ObjectCls->isa;
    
    ImpCls->super = ObjectCls;
    ImpCls->name = "std::Imp";
    ImpCls->protocolc = 0;
    ImpCls->protocols = new Protocol[ImpCls->protocolc]();
    ImpCls->ivarc = 0;
    ImpCls->mthdc = 0;
    ImpCls->mthdv = new Method[ImpCls->mthdc]();
    
    ImpCls->isa->super = ObjectCls->isa;
    ImpCls->isa->name = "std::Imp.isa";
    ImpCls->isa->protocolc = 0;
    ImpCls->isa->protocols = new Protocol[ImpCls->isa->protocolc]();
    ImpCls->isa->mthdc = 0;
    ImpCls->isa->mthdv = new Method[ImpCls->isa->mthdc]();

    RegisterObjectForName(ImpCls, ImpCls->name);
    
    // Method Class
    Class MethodCls = new voltz_class();
    MethodCls->isa = new voltz_class();
    MethodCls->isa->isa = ObjectCls->isa;
    
    MethodCls->super = ObjectCls;
    MethodCls->name = "std::Method";
    MethodCls->protocolc = 0;
    MethodCls->protocols = new Protocol[MethodCls->protocolc]();
    MethodCls->ivarc = 0;
    MethodCls->mthdc = 0;
    MethodCls->mthdv = new Method[MethodCls->mthdc]();
    
    MethodCls->isa->super = ObjectCls->isa;
    MethodCls->isa->name = "std::Method.isa";
    MethodCls->isa->protocolc = 0;
    MethodCls->isa->protocols = new Protocol[MethodCls->isa->protocolc]();
    MethodCls->isa->mthdc = 0;
    MethodCls->isa->mthdv = new Method[MethodCls->isa->mthdc]();
    
    RegisterObjectForName(MethodCls, MethodCls->name);
    
    // Thread Class
    
    Class ThreadCls = new voltz_class();
    ThreadCls->isa = new voltz_class();
    ThreadCls->isa->isa = ObjectCls->isa;
    
    ThreadCls->super = ObjectCls;
    ThreadCls->name = "std::Thread";
    ThreadCls->protocolc = 0;
    ThreadCls->protocols = new Protocol[ThreadCls->protocolc]();
    ThreadCls->ivarc = 0;
    ThreadCls->mthdc = 0;
    ThreadCls->mthdv = new Method[ThreadCls->mthdc]();
    
    ThreadCls->isa->super = ObjectCls->isa;
    ThreadCls->isa->name = "std::Thread.isa";
    ThreadCls->isa->protocolc = 0;
    ThreadCls->isa->protocols = new Protocol[ThreadCls->isa->protocolc]();
    ThreadCls->isa->mthdc = 0;
    ThreadCls->isa->mthdv = new Method[ThreadCls->isa->mthdc]();
    
    RegisterObjectForName(ThreadCls, ThreadCls->name);
    
    Thread thread = new voltz_thread();
    thread->isa = ThreadCls;
    thread->refs = 1;
    thread->weaks = 0;
    thread->id = 0;
    thread->code = nil;
    thread->loc = 0;
    thread->stksz = 0x100;
    thread->stack = new Object[thread->stksz]();
    thread->tp = 0;
    
    ThreadQueue.push(thread);
    
    for (int64_t k = 0; k < ThreadTableSize; k++) {
        ThreadTable[k] = new std::thread(ThreadStartFunc);
    }
    
    Method Alloc = new voltz_method();
    Alloc->isa = MethodCls;
    Alloc->refs = 1;
    Alloc->weaks = 0;
    Alloc->sel = new voltz_selector();
    Alloc->sel->isa = SelectorCls;
    Alloc->sel->refs = 1;
    Alloc->sel->weaks = 0;
    Alloc->sel->value = "Alloc()";
    Alloc->imp = new voltz_imp();
    Alloc->imp->isa = ImpCls;
    Alloc->imp->refs = 1;
    Alloc->imp->weaks = 0;
    Alloc->imp->count = 3;
    Alloc->imp->instructions = new Instruction[Alloc->imp->count]();
    Alloc->imp->instructions[0] = Instruction(Instruction::LDSELF);
    Alloc->imp->instructions[1] = Instruction(Instruction::BLTIN);
    Alloc->imp->instructions[1].value.bltin = Instruction::Alloc;
    Alloc->imp->instructions[2] = Instruction(Instruction::RET);
    
    ObjectCls->isa->mthdv[0] = Alloc;
    
}

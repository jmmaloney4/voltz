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

const int64_t InitFuncSize = 0x10;
Instruction InitFunc[InitFuncSize] = {
    
};

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
    ObjectCls->mthdc = 1;
    ObjectCls->mthdv = new Method[ObjectCls->mthdc]();
    
    ObjectCls->isa->super = ObjectCls;
    ObjectCls->isa->name = "std::Class";
    ObjectCls->isa->protocolc = 0;
    ObjectCls->isa->protocols = new Protocol[ObjectCls->isa->protocolc]();
    ObjectCls->isa->ivarc = 0;
    ObjectCls->isa->mthdc = 4;
    ObjectCls->isa->mthdv = new Method[ObjectCls->isa->mthdc]();
    
    RegisterObjectForName(ObjectCls, ObjectCls->name);
    RegisterObjectForName(ObjectCls->isa, ObjectCls->isa->name);
    
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
    /*
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
    */
    Imp code = new voltz_imp();
    code->isa = ImpCls;
    code->refs = 1;
    code->weaks = 0;
    code->count = size;
    code->instructions = insts;
    
    Method Alloc = new voltz_method();
    Alloc->isa = MethodCls;
    Alloc->refs = 1;
    Alloc->weaks = 0;
    Alloc->sel = new voltz_selector();
    Alloc->sel->isa = SelectorCls;
    Alloc->sel->refs = 1;
    Alloc->sel->weaks = 0;
    Alloc->sel->value = "Alloc()";
    AddSelector(Alloc->sel);
    Alloc->imp = new voltz_imp();
    Alloc->imp->isa = ImpCls;
    Alloc->imp->refs = 1;
    Alloc->imp->weaks = 0;
    Alloc->imp->count = 3;
    Alloc->imp->instructions = new Instruction[Alloc->imp->count]();
    Alloc->imp->instructions[0] = Instruction(Instruction::LDSELF);
    Alloc->imp->instructions[1] = Instruction(Instruction::BLTIN, Instruction::Alloc);
    Alloc->imp->instructions[2] = Instruction(Instruction::RET);
    
    ObjectCls->isa->mthdv[0] = Alloc;
    
    Method Init = new voltz_method();
    Init->isa = MethodCls;
    Init->refs = 1;
    Init->weaks = 0;
    Init->sel = new voltz_selector();
    Init->sel->isa = SelectorCls;
    Init->sel->refs = 1;
    Init->sel->weaks = 0;
    Init->sel->value = "Init()";
    AddSelector(Init->sel);
    Init->imp = new voltz_imp();
    Init->imp->isa = ImpCls;
    Init->imp->refs = 1;
    Init->imp->weaks = 0;
    Init->imp->count = 2;
    Init->imp->instructions = new Instruction[Init->imp->count]();
    Init->imp->instructions[0] = Instruction(Instruction::LDSELF);
    Init->imp->instructions[1] = Instruction(Instruction::BLTIN, Instruction::Init);
    Init->imp->instructions[1] = Instruction(Instruction::RET);
    
    ObjectCls->mthdv[0] = Init;
    
    Method AddMethod = new voltz_method();
    AddMethod->isa = MethodCls;
    AddMethod->refs = 1;
    AddMethod->weaks = 0;
    AddMethod->sel = new voltz_selector();
    AddMethod->sel->isa = SelectorCls;
    AddMethod->sel->refs = 1;
    AddMethod->sel->weaks = 0;
    AddMethod->sel->value = "AddMethod(:std::Method)";
    AddSelector(AddMethod->sel);
    AddMethod->imp = new voltz_imp();
    AddMethod->imp->isa = ImpCls;
    AddMethod->imp->refs = 1;
    AddMethod->imp->weaks = 0;
    AddMethod->imp->count = 4;
    AddMethod->imp->instructions = new Instruction[AddMethod->imp->count]();
    AddMethod->imp->instructions[0] = Instruction(Instruction::LDARG, (int64_t) 0);
    AddMethod->imp->instructions[1] = Instruction(Instruction::LDSELF);
    AddMethod->imp->instructions[2] = Instruction(Instruction::BLTIN, Instruction::AddMethod);
    AddMethod->imp->instructions[3] = Instruction(Instruction::RET);
    
    ObjectCls->isa->mthdv[1] = AddMethod;
    
    Method SubClass = new voltz_method();
    SubClass->isa = MethodCls;
    SubClass->refs = 1;
    SubClass->weaks = 0;
    SubClass->sel = new voltz_selector();
    SubClass->sel->isa = SelectorCls;
    SubClass->sel->refs = 1;
    SubClass->sel->weaks = 0;
    SubClass->sel->value = "SubClass(:std::String)";
    AddSelector(SubClass->sel);
    SubClass->imp = new voltz_imp();
    SubClass->imp->isa = ImpCls;
    SubClass->imp->refs = 1;
    SubClass->imp->weaks = 0;
    SubClass->imp->count = 4;
    SubClass->imp->instructions = new Instruction[SubClass->imp->count]();
    SubClass->imp->instructions[0] = Instruction(Instruction::LDARG, (int64_t) 0);
    SubClass->imp->instructions[1] = Instruction(Instruction::LDSELF);
    SubClass->imp->instructions[2] = Instruction(Instruction::BLTIN, Instruction::SubClass);
    SubClass->imp->instructions[3] = Instruction(Instruction::RET);
    
    ObjectCls->isa->mthdv[2] = SubClass;
    
    Method Register = new voltz_method();
    Register->isa = MethodCls;
    Register->refs = 1;
    Register->weaks = 0;
    Register->sel = new voltz_selector();
    Register->sel->isa = SelectorCls;
    Register->sel->refs = 1;
    Register->sel->weaks = 0;
    Register->sel->value = "Register()";
    AddSelector(Register->sel);
    Register->imp = new voltz_imp();
    Register->imp->isa = ImpCls;
    Register->imp->refs = 1;
    Register->imp->weaks = 0;
    Register->imp->count = 4;
    Register->imp->instructions = new Instruction[Register->imp->count]();
    Register->imp->instructions[0] = Instruction(Instruction::LDARG, (int64_t) 0);
    Register->imp->instructions[1] = Instruction(Instruction::LDSELF);
    Register->imp->instructions[2] = Instruction(Instruction::BLTIN, Instruction::Register);
    Register->imp->instructions[3] = Instruction(Instruction::RET);
    
    ObjectCls->isa->mthdv[3] = Register;
    
    // ldclos {
    //
    // }
    // ldnil
    //
    // ldint 0
    // ldsel "Alloc()"
    // ldclass "std::Method"
    // msg
    //
    // store 4
    // popr 4
    //
    // load 1
    // ldsel "MySel()"
    // ldint 2
    // ldsel "Init(imp:std::Imp,sel:std::Selector)"
    // load 4
    // msg
    //
    // store 6
    // popr 6
    //
    // load 0
    // ldint 1
    // ldsel "AddMethod(:std::Method)"
    // ldclass "module::MyClass"
    // msg
    //
    // popr 7
    // retn
}

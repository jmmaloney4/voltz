// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

int voltz::C_argc;
const char** voltz::C_argv;

std::mutex VoltzMemMutex0;
std::mutex VoltzMemMutex1;
std::mutex VoltzMemMutex2;
std::mutex VoltzMemMutex3;
std::mutex VoltzMemMutex4;

std::mutex* VoltzGetMemMutex(id obj) {
    switch (((int64_t) obj) % 5) {
    case 0:
        return &VoltzMemMutex0;
    case 1:
        return &VoltzMemMutex1;
    case 2:
        return &VoltzMemMutex2;
    case 3:
        return &VoltzMemMutex3;
    case 4:
        return &VoltzMemMutex4;
    default:
        abort();
        break;
    }
}

void voltz::BootstrapRuntime(int argc, const char** argv) {

    C_argc = argc;
    C_argv = argv;

    VoltzVM.classtbl = (vz_classTable_entry**) malloc(
        sizeof(vz_classTable_entry*) * vz_classTable_size);
    VoltzVM.globaltbl = (vz_globalTable_entry**) malloc(
        sizeof(vz_globalTable_entry*) * vz_globalTable_size);
    VoltzVM.seltbl = (vz_selTable_entry**) malloc(sizeof(vz_selTable_entry*) *
                                                  vz_selTable_size);

    InitSelectors();

    Object   = AllocObject(8);
    Class    = AllocObject(8);
    Method   = AllocObject(8);
    Selector = AllocObject(8);
    Imp      = AllocObject(8);

    Object->isa = Class;
    Class->isa  = Class;

    Method->isa   = AllocObject(8);
    Selector->isa = AllocObject(8);
    Imp->isa      = AllocObject(8);

    Method->isa->isa   = Class;
    Selector->isa->isa = Class;
    Imp->isa->isa      = Class;

    Object->refs  = 1;
    Object->weaks = 0;

    Class->refs  = 1;
    Class->weaks = 0;

    Method->refs  = 1;
    Method->weaks = 0;

    Selector->refs  = 1;
    Selector->weaks = 0;

    Imp->refs  = 1;
    Imp->weaks = 0;

    // super classes
    Object->ivars[0].obj   = nil;
    Class->ivars[0].obj    = Object;
    Method->ivars[0].obj   = Object;
    Selector->ivars[0].obj = Object;
    Imp->ivars[0].obj      = Object;

    Method->isa->ivars[0].obj   = Class;
    Selector->isa->ivars[0].obj = Class;
    Imp->isa->ivars[0].obj      = Class;

    // names
    Object->ivars[1].str   = "std::Object";
    Class->ivars[1].str    = "std::Class";
    Method->ivars[1].str   = "std::Method";
    Selector->ivars[1].str = "std::Selector";
    Imp->ivars[1].str      = "std::Imp";

    Method->isa->ivars[1].str   = "std::Method.Isa";
    Selector->isa->ivars[1].str = "std::Selector.Isa";
    Imp->isa->ivars[1].str      = "std::Imp.Isa";

    // ivars
    Object->ivars[2].num   = 0;
    Class->ivars[2].num    = 8;
    Method->ivars[2].num   = 2;
    Selector->ivars[2].num = 1;
    Imp->ivars[2].num      = 1;

    Method->isa->ivars[2].num   = 0;
    Selector->isa->ivars[2].num = 0;
    Imp->isa->ivars[2].num      = 0;

    // ivarn
    Object->ivars[3].sarr    = (SEL*) malloc(sizeof(SEL) * Object->ivars[2].num);
    Class->ivars[3].sarr     = (SEL*) malloc(sizeof(SEL) * Class->ivars[2].num);
    Class->ivars[3].sarr[0]  = GetSelector("super");
    Class->ivars[3].sarr[1]  = GetSelector("name");
    Class->ivars[3].sarr[2]  = GetSelector("ivars");
    Class->ivars[3].sarr[3]  = GetSelector("ivarn");
    Class->ivars[3].sarr[4]  = GetSelector("protocolc");
    Class->ivars[3].sarr[5]  = GetSelector("protocolv");
    Class->ivars[3].sarr[6]  = GetSelector("mthdc");
    Class->ivars[3].sarr[7]  = GetSelector("mthdv");
    Method->ivars[3].sarr    = (SEL*) malloc(sizeof(SEL) * Method->ivars[2].num);
    Method->ivars[3].sarr[0] = GetSelector("sel");
    Method->ivars[3].sarr[1] = GetSelector("imp");
    Selector->ivars[3].sarr =
        (SEL*) malloc(sizeof(SEL) * Selector->ivars[2].num);
    Selector->ivars[3].sarr[0] = GetSelector("value");
    Imp->ivars[3].sarr         = (SEL*) malloc(sizeof(SEL) * Imp->ivars[2].num);
    Imp->ivars[3].sarr[0]      = GetSelector("value");

    // protocolc
    Object->ivars[4].num   = 0;
    Class->ivars[4].num    = 0;
    Method->ivars[4].num   = 0;
    Selector->ivars[4].num = 0;
    Imp->ivars[4].num      = 0;

    // protocolv
    Object->ivars[5].arr   = (id*) malloc(sizeof(id) * Object->ivars[4].num);
    Class->ivars[5].arr    = (id*) malloc(sizeof(id) * Class->ivars[4].num);
    Method->ivars[5].arr   = (id*) malloc(sizeof(id) * Method->ivars[4].num);
    Selector->ivars[5].arr = (id*) malloc(sizeof(id) * Selector->ivars[4].num);
    Imp->ivars[5].arr      = (id*) malloc(sizeof(id) * Imp->ivars[4].num);

    // mthdc
    Object->ivars[6].num   = 4;
    Class->ivars[6].num    = 3;
    Method->ivars[6].num   = 0;
    Selector->ivars[6].num = 0;
    Imp->ivars[6].num      = 0;

    Method->isa->ivars[6].num   = 0;
    Selector->isa->ivars[6].num = 0;
    Imp->isa->ivars[6].num      = 0;

    // mthdv
    Object->ivars[7].arr   = (id*) malloc(sizeof(id) * Object->ivars[6].num);
    Class->ivars[7].arr    = (id*) malloc(sizeof(id) * Class->ivars[6].num);
    Method->ivars[7].arr   = (id*) malloc(sizeof(id) * Method->ivars[6].num);
    Selector->ivars[7].arr = (id*) malloc(sizeof(id) * Selector->ivars[6].num);
    Imp->ivars[7].arr      = (id*) malloc(sizeof(id) * Imp->ivars[6].num);

    // class methods
    Class->ivars[7].arr[0] =
        AllocObject(Method->ivars[2].num + Object->ivars[2].num);
    Class->ivars[7].arr[0]->isa   = Method;
    Class->ivars[7].arr[0]->refs  = 1;
    Class->ivars[7].arr[0]->weaks = 0;
    SetInstanceVariable(Class->ivars[7].arr[0], sel, (id) Alloc);
    SetInstanceVariable(Class->ivars[7].arr[0], imp, (id) vz_def({
                            NUM ivars = self->ivars[2].num;
                            for (id c = self->ivars[0].obj; c != nil;
                                 c = c->ivars[0].obj) {
                                ivars += c->ivars[2].num;
                            }

                            id rv     = AllocObject(ivars);
                            rv->isa   = self;
                            rv->refs  = 1;
                            rv->weaks = 0;
                            return rv;
                        }));

    Class->ivars[7].arr[1] =
        AllocObject(Method->ivars[2].num + Object->ivars[2].num);
    Class->ivars[7].arr[1]->isa   = Method;
    Class->ivars[7].arr[1]->refs  = 1;
    Class->ivars[7].arr[1]->weaks = 0;
    SetInstanceVariable(Class->ivars[7].arr[1], sel, (id) AddMethod_);
    SetInstanceVariable(Class->ivars[7].arr[1], imp, (id) vz_def({
                            NUM mthdc = self->ivars[6].num;
                            id* mthdv = self->ivars[7].arr;

                            id* tmp = (id*) malloc(sizeof(id) * (mthdc + 1));

                            for (NUM k = 0; k < mthdc; k++) {
                                tmp[(int64_t) k] = mthdv[(int64_t) k];
                            }
                            tmp[(int64_t) mthdc] = SendMsg(argv[0], Retain, 0);

                            self->ivars[6].num += 1;
                            self->ivars[7].arr = tmp;
                            free(mthdv);

                            return nil;
                        }));

    Class->ivars[7].arr[2] =
        AllocObject(Method->ivars[2].num + Object->ivars[2].num);
    Class->ivars[7].arr[2]->isa   = Method;
    Class->ivars[7].arr[2]->refs  = 1;
    Class->ivars[7].arr[2]->weaks = 0;
    SetInstanceVariable(Class->ivars[7].arr[2], sel, (id) New);
    SetInstanceVariable(Class->ivars[7].arr[2], imp, (id) vz_def({
                            id rv = SendMsg(self, Alloc, 0);
                            rv    = SendMsg(rv, Init, 0);
                            return rv;
                        }));

    // object methods
    Object->ivars[7].arr[0] =
        AllocObject(Method->ivars[2].num + Object->ivars[2].num);
    Object->ivars[7].arr[0]->isa   = Method;
    Object->ivars[7].arr[0]->refs  = 1;
    Object->ivars[7].arr[0]->weaks = 0;
    SetInstanceVariable(Object->ivars[7].arr[0], sel, (id) Init);
    SetInstanceVariable(Object->ivars[7].arr[0], imp,
                        (id) vz_def({ return self; }));

    Object->ivars[7].arr[1] =
        AllocObject(Method->ivars[2].num + Object->ivars[2].num);
    Object->ivars[7].arr[1]->isa   = Method;
    Object->ivars[7].arr[1]->refs  = 1;
    Object->ivars[7].arr[1]->weaks = 0;
    SetInstanceVariable(Object->ivars[7].arr[1], sel, (id) Retain);
    SetInstanceVariable(Object->ivars[7].arr[1], imp, (id) vz_def({
                            std::mutex* mtx = VoltzGetMemMutex(self);
                            mtx->lock();
                            self->refs++;
                            mtx->unlock();
                            return self;
                        }));

    Object->ivars[7].arr[2] =
        AllocObject(Method->ivars[2].num + Object->ivars[2].num);
    Object->ivars[7].arr[2]->isa          = Method;
    Object->ivars[7].arr[2]->refs         = 1;
    Object->ivars[7].arr[2]->weaks        = 0;
    Object->ivars[7].arr[2]->ivars[0].sel = Release;
    Object->ivars[7].arr[2]->ivars[1].imp = vz_def({
        std::mutex* mtx = VoltzGetMemMutex(self);
        mtx->lock();
        if (self->refs <= 1) {
            mtx->unlock();
            SendMsg(self, Deinit, 0);
        } else {
            self->refs--;
            mtx->unlock();
        }
        return nil;
    });

    Object->ivars[7].arr[3] =
        AllocObject(Method->ivars[2].num + Object->ivars[2].num);
    Object->ivars[7].arr[3]->isa          = Method;
    Object->ivars[7].arr[3]->refs         = 1;
    Object->ivars[7].arr[3]->weaks        = 0;
    Object->ivars[7].arr[3]->ivars[0].sel = Deinit;
    Object->ivars[7].arr[3]->ivars[1].imp = vz_def({
        free(self);
        return nil;
    });

    // SetSel:
    id setsel = SendMsg(Method, Alloc, 0);
    setsel = SendMsg(setsel, Init, 0);
    SetInstanceVariable(setsel, sel, (id) SetSel_);
    setsel->ivars[1].imp = vz_def({
        SEL s = UnboxSelector(argv[0]);
        SetInstanceVariable(self, sel, (id) s);
        return nil;
    });
    SendMsg(Method, AddMethod_, 1, setsel);
    SendMsg(setsel, Release, 0);

    // SetImp:
    id setimp = SendMsg(Method, Alloc, 0);
    setimp = SendMsg(setimp, Init, 0);
    SetInstanceVariable(setimp, sel, (id) SetImp_);
    setimp->ivars[1].imp = vz_def({
        IMP i = UnboxImp(argv[0]);
        SetInstanceVariable(self, imp, (id) i);
        return nil;
    });
    SendMsg(Method, AddMethod_, 1, setimp);
    SendMsg(setimp, Release, 0);

    // Init::
    id init = SendMsg(Method, New, 0);
    SetInstanceVariable(init, sel, (id) Init__);
    init->ivars[1].imp = vz_def({
        self = SendMsgSuper(self, Init, 0);
        if (self) {
            id sel = SendMsg(argv[0], Retain, 0);
            id imp = SendMsg(argv[1], Retain, 0);
            SendMsg(self, SetSel_, 1, sel);
            SendMsg(self, SetImp_, 1, imp);
        }
        return self;
    });
    SendMsg(Method, AddMethod_, 1, init);
    SendMsg(init, Release, 0);

    // New::
    id nw = SendMsg(Method, Alloc, 0);
    nw = SendMsg(nw, Init, 0);
    SetInstanceVariable(nw, sel, (id) New__);
    nw->ivars[1].imp = vz_def({
        id rv        = SendMsg(self, Alloc, 0);
        rv           = SendMsg(rv, Init__, 2, argv[0], argv[1]);
        return rv;
    });
    SendMsg(Method->isa, AddMethod_, 1, nw);
    SendMsg(nw, Release, 0);

    // Subclass
    id subclass = SendMsg(Method, New, 0);
    SetInstanceVariable(subclass, sel, (id) Subclass___);
    subclass->ivars[1].imp    = vz_def({
        id rv                 = SendMsg(Class, New, 0);
        rv->isa               = SendMsg(Class, New, 0);
        rv->isa->isa          = Class;
        rv->isa->ivars[0].obj = SendMsg(self->isa, Retain, 0);
        rv->isa->ivars[1].str = UnboxString(argv[1]);
        rv->isa->ivars[2].num = 0;
        rv->isa->ivars[3].sarr =
            (SEL*) malloc(sizeof(SEL) * rv->isa->ivars[2].num);
        rv->isa->ivars[4].num = 0;
        rv->isa->ivars[5].arr =
            (id*) malloc(sizeof(id) * rv->isa->ivars[4].num);
        rv->isa->ivars[6].num = 0;
        rv->isa->ivars[7].arr =
            (id*) malloc(sizeof(id) * rv->isa->ivars[6].num);
        rv->refs          = 1;
        rv->weaks         = 0;
        rv->ivars[0].obj  = SendMsg(self, Retain, 0);
        rv->ivars[1].str  = UnboxString(argv[0]);
        rv->ivars[2].num  = UnboxNumber(argv[2]);
        rv->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * rv->ivars[2].num);
        rv->ivars[4].num  = 0;
        rv->ivars[5].arr  = (id*) malloc(sizeof(id) * rv->ivars[4].num);
        rv->ivars[6].num  = 0;
        rv->ivars[7].arr  = (id*) malloc(sizeof(id) * rv->ivars[6].num);

        return rv;
    });
    SendMsg(Class, AddMethod_, 1, subclass);
    SendMsg(subclass, Release, 0);

    RegisterClass(Object->ivars[1].str, Object);
    RegisterClass(Class->ivars[1].str, Class);
    RegisterClass(Method->ivars[1].str, Method);
    RegisterClass(Selector->ivars[1].str, Selector);
    RegisterClass(Imp->ivars[1].str, Imp);

    id reg    = SendMsg(Method, New, 0);
    id regsel = BoxSelector(Register);
    id regimp = BoxImp(vz_def({
        RegisterClass(GetClassName(self), self);
        return nil;
    }));
    SendMsg(reg, SetSel_, 1, regsel);
    SendMsg(reg, SetImp_, 1, regimp);
    SendMsg(Class, AddMethod_, 1, reg);
    SendMsg(regsel, Release, 0);
    SendMsg(regimp, Release, 0);
    SendMsg(reg, Release, 0);

    id isa    = SendMsg(Method, New, 0);
    id isasel = BoxSelector(Isa);
    id isaimp = BoxImp(vz_def({ return SendMsg(self->isa, Retain, 0); }));
    SendMsg(isa, SetSel_, 1, isasel);
    SendMsg(isa, SetImp_, 1, isaimp);
    SendMsg(Object, AddMethod_, 1, isa);
    SendMsg(isasel, Release, 0);
    SendMsg(isaimp, Release, 0);
    SendMsg(isa, Release, 0);

    String                    = AllocObject(Class->ivars[2].num + Object->ivars[2].num);
    String->isa               = AllocObject(Class->ivars[2].num + Object->ivars[2].num);
    String->ivars[0].obj      = Object;
    String->isa->ivars[0].obj = Class;
    String->ivars[1].str      = "std::String";
    String->isa->ivars[1].str = "std::String.Isa";
    String->ivars[2].num      = 2;
    String->isa->ivars[2].num = 0;
    String->ivars[3].sarr     = (SEL*) malloc(sizeof(SEL) * String->ivars[2].num);
    String->ivars[3].sarr[0]  = GetSelector("value");
    String->ivars[3].sarr[1] = GetSelector("length");
    String->isa->ivars[3].sarr =
        (SEL*) malloc(sizeof(SEL) * String->isa->ivars[2].num);
    String->ivars[4].num      = 0;
    String->isa->ivars[4].num = 0;
    String->ivars[5].arr = (id*) malloc(sizeof(id) * String->ivars[4].num);
    String->isa->ivars[5].arr =
        (id*) malloc(sizeof(id) * String->isa->ivars[4].num);
    String->ivars[6].num      = 0;
    String->isa->ivars[6].num = 0;
    String->ivars[7].arr = (id*) malloc(sizeof(id) * String->ivars[6].num);
    String->isa->ivars[7].arr =
        (id*) malloc(sizeof(id) * String->isa->ivars[6].num);
    RegisterClass(String->ivars[1].str, String);

    Number                    = AllocObject(Class->ivars[2].num + Object->ivars[2].num);
    Number->isa               = AllocObject(Class->ivars[2].num + Object->ivars[2].num);
    Number->ivars[0].obj      = Object;
    Number->isa->ivars[0].obj = Class;
    Number->ivars[1].str      = "std::Number";
    Number->isa->ivars[1].str = "std::Number.Isa";
    Number->ivars[2].num      = 1;
    Number->isa->ivars[2].num = 0;
    Number->ivars[3].sarr     = (SEL*) malloc(sizeof(SEL) * Number->ivars[2].num);
    Number->ivars[3].sarr[0] = GetSelector("value");
    Number->isa->ivars[3].sarr =
        (SEL*) malloc(sizeof(SEL) * Number->isa->ivars[2].num);
    Number->ivars[4].num      = 0;
    Number->isa->ivars[4].num = 0;
    Number->ivars[5].arr = (id*) malloc(sizeof(id) * Number->ivars[4].num);
    Number->isa->ivars[5].arr =
        (id*) malloc(sizeof(id) * Number->isa->ivars[4].num);
    Number->ivars[6].num      = 0;
    Number->isa->ivars[6].num = 0;
    Number->ivars[7].arr = (id*) malloc(sizeof(id) * Number->ivars[6].num);
    Number->isa->ivars[7].arr =
        (id*) malloc(sizeof(id) * Number->isa->ivars[6].num);
    RegisterClass(Number->ivars[1].str, Number);

    id name  = BoxString("std::Byte");
    id iname = BoxString("std::Byte.Isa");
    id ivarc = BoxNumber(1);
    Byte = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
    SendMsg(name, Release, 0);
    SendMsg(iname, Release, 0);
    SendMsg(ivarc, Release, 0);
    SetClassInstanceVariableName(Byte, 0, value);
    RegisterClass("std::Byte", Byte);

    name  = BoxString("std::Char");
    iname = BoxString("std::Char.Isa");
    ivarc = BoxNumber(1);
    Char = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
    SendMsg(name, Release, 0);
    SendMsg(iname, Release, 0);
    SendMsg(ivarc, Release, 0);
    SetClassInstanceVariableName(Char, 0, value);
    RegisterClass("std::Char", Char);

    name  = BoxString("std::Bool");
    iname = BoxString("std::Bool.Isa");
    ivarc = BoxNumber(1);
    Bool = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
    SendMsg(name, Release, 0);
    SendMsg(iname, Release, 0);
    SendMsg(ivarc, Release, 0);
    SetClassInstanceVariableName(Bool, 0, value);
    RegisterClass("std::Bool", Bool);

    name  = BoxString("std::Array");
    iname = BoxString("std::Array.Isa");
    ivarc = BoxNumber(2);
    Array = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
    SendMsg(name, Release, 0);
    SendMsg(iname, Release, 0);
    SendMsg(ivarc, Release, 0);
    SetClassInstanceVariableName(Array, 0, count);
    SetClassInstanceVariableName(Array, 1, value);
    RegisterClass("std::Array", Array);

    name  = BoxString("std::Tuple");
    iname = BoxString("std::Tuple.Isa");
    ivarc = BoxNumber(2);
    Tuple = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
    SendMsg(name, Release, 0);
    SendMsg(iname, Release, 0);
    SendMsg(ivarc, Release, 0);
    SetClassInstanceVariableName(Tuple, 0, count);
    SetClassInstanceVariableName(Tuple, 1, value);
    RegisterClass("std::Tuple", Tuple);

    name   = BoxString("std::Thread");
    iname  = BoxString("std::Thread.Isa");
    ivarc  = BoxNumber(5);
    Thread = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
    SendMsg(name, Release, 0);
    SendMsg(iname, Release, 0);
    SendMsg(ivarc, Release, 0);
    SetClassInstanceVariableName(Thread, 0, handle);
    SetClassInstanceVariableName(Thread, 1, imp);
    SetClassInstanceVariableName(Thread, 2, rv);
    SetClassInstanceVariableName(Thread, 3, callstack);
    SetClassInstanceVariableName(Thread, 4, excpstack);
    RegisterClass("std::Thread", Thread);

    name      = BoxString("std::Exception");
    iname     = BoxString("std::Exception.Isa");
    ivarc     = BoxNumber(2);
    Exception = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
    SendMsg(name, Release, 0);
    SendMsg(iname, Release, 0);
    SendMsg(ivarc, Release, 0);
    SetClassInstanceVariableName(Exception, 0, message);
    SetClassInstanceVariableName(Exception, 1, backtrace);
    RegisterClass("std::Exception", Exception);
    /*
        name      = BoxString("std::ExceptionFrame");
        iname     = BoxString("std::ExceptionFrame.Isa");
        ivarc     = BoxNumber(2);
        Exception = SendMsg(Object, Subclass___, 3, name, iname, ivarc);
        SendMsg(name, Release, 0);
        SendMsg(iname, Release, 0);
        SendMsg(ivarc, Release, 0);
        SetClassInstanceVariableName(Exception, 0, message);
        SetClassInstanceVariableName(Exception, 0, backtrace);
        RegisterClass("std::Exception", Exception);
     */
}

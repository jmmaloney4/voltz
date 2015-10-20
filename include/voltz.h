// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

// Voltz API Overview
//
// id SendMsg(id, SEL, NUM, ...)
// id SendMsgV(id, SEL, NUM, ap_list)
// id SendMsgA(id, SEL, NUM, id*)
//
// id SendMsgSuper(id, SEL, NUM, ...)
// id SendMsgSuperV(id, SEL, NUM, ap_list)
// id SendMsgSuperA(id, SEL, NUM, id*)
//
// SEL GetSelector(const char*)
// Class GetClass(const char*)
// void RegisterClass(id, const char*)
//
// id CreateThread(IMP)
// void StartThread(id, NUM, ...);
// void StartThreadV(id, NUM, va_list)
// void StartThreadA(id, NUM, id*)
// id JoinThread(id)
// id GetCurrentThread()
//
// void PushExceptionFrame(JmpBuf)
// JmpBuf PopExceptionFrame()
//
// id GetIsa(id)
// NUM GetReferences(id)
// NUM GetWeakReferences(id)
// id GetInstanceVariable(id, SEL)
// id GetInstanceVariable(id, const char*)
// id GetNumberInstanceVariable(id, SEL)
// id GetNumberInstanceVariable(id, const char*)
// void SetInstanceVariable(id, SEL, id)
// void SetInstanceVariable(id, const char*, id)
// void SetNumberInstanceVariable(id, SEL, NUM)
// void SetNumberInstanceVariable(id, const char*, NUM)
//
// id GetClassSuper(id)
// const char* GetClassName(id)
// NUM GetClassInstanceVariableCount(id)
// SEL* GetClassInstanceVariableNames(id)
// NUM GetClassProtocolCount(id)
// id* GetClassProtocols(id)
// NUM GetClassMethodCount(id)
// id* GetClassMethods(id)
//
// id BoxNumber(NUM)
// id BoxByte(BYTE)
// id BoxString(const char*)
// id BoxChar(NUM)
// id BoxBool(bool)
// id BoxSelector(SEL)
// id BoxImp(IMP)
// id BoxArray(NUM, ...)
// id BoxArrayV(NUM, va_list)
// id BoxArrayA(NUM, id*)
// id BoxTuple(NUM, ...)
//
// NUM UnboxNumber(id)
// BYTE UnboxByte(id)
// const char* UnboxString(id)
// NUM UnboxChar(id)
// bool UnboxBool(id)
// SEL UnboxSel(id)
// IMP UnboxImp(id)
// id* UnobxArray(id, NUM*)
// void UnboxTuple(id, ...)

#ifndef VOLTZ_VOLTZ_H
#define VOLTZ_VOLTZ_H

#include <cstdint>
#include <cstdarg>
#include <functional>
#include <cstddef>
#include <csetjmp>

namespace voltz {

#ifdef DEBUG
#define VOLTZ_DEBUG 1
#endif

#define VZ_MAJOR_VERSION 0
#define VZ_MINOR_VERSION 0
#define VZ_PATCH_VERSION 5

#define vz_def(func)                                                           \
    (new std::function<id(id, SEL, NUM, id*)>(                                 \
        [](id self, SEL cmd, NUM argc, id* argv) -> id { func }))

#define vz_def_capture(list, func)                                             \
    new std::function<id(id, SEL, NUM, id*)>(                                  \
        [list](id self, SEL cmd, NUM argc, id* argv) -> id { func })

#define nil NULL

#define SetJmp(buf) setjmp(buf.value)
#define LongJmp(buf, val) longjmp(buf.value, val)

#define Try(code)

#define Catch(code)
#define Finally(code)

#define VOLTZ_PATH_ENVVAR "VOLTZ_PATH"
#define VOLTZ_MODULE_EXT "vzm"

    extern "C" double StartupTime;

    extern "C" int C_argc;
    extern "C" const char** C_argv;

    typedef struct vz_object* id;
    typedef struct vz_sel* SEL;
    typedef double NUM;
    typedef uint8_t BYTE;
    typedef std::function<id(id, SEL, NUM, id*)>* IMP;
    typedef struct vz_vm VM;
    typedef struct { jmp_buf value; } JmpBuf;

    extern "C" VM VoltzVM;

    union vz_ivar {
        id obj;
        SEL sel;
        NUM num;
        IMP imp;
        const char* str;
        id* arr;
        SEL* sarr;
    };

    struct vz_object {
        id isa;
        NUM refs;
        NUM weaks;
        vz_ivar ivars[0];
    };

    struct vz_sel {
        const char* value;
    };

    /* Class
         * - super
         * - name
         * - ivars (for this class only)
         * - ivarn
         * - protocolc
         * - protocolv
         * - mthdc
         * - mthdv
         */

    /* Protocol
         * - name
         * - superc
         * - superv
         * - imthdc
         * - imthdv
         * - cmthdc
         * - cmthdv
         */

    /* Array
         * - count
         * - value
         */

    /* Tuple
         * - count
         * - value
         * - types
         */

    /* Thread
         * - handle
         * - imp
         * - rv
         * - callstack
         * - excpstack
         */

    extern "C" id (*BoxNumber)(NUM value);
    extern "C" id (*BoxByte)(BYTE value);
    extern "C" id (*BoxString)(const char* value);
    extern "C" id (*BoxChar)(NUM value);
    extern "C" id (*BoxBool)(bool value);
    extern "C" id (*BoxSelector)(SEL value);
    extern "C" id (*BoxImp)(IMP value);
    extern "C" id (*BoxArray)(NUM count, ...);
    extern "C" id (*BoxArrayV)(NUM count, va_list ap);
    extern "C" id (*BoxArrayA)(NUM count, id* value);
    extern "C" id (*BoxTuple)(NUM count, ...);

    extern "C" NUM (*UnboxNumber)(id obj);
    extern "C" BYTE (*UnboxByte)(id obj);
    extern "C" const char* (*UnboxString)(id obj);
    extern "C" NUM (*UnboxChar)(id obj);
    extern "C" bool (*UnboxBool)(id obj);
    extern "C" SEL (*UnboxSelector)(id obj);
    extern "C" IMP (*UnboxImp)(id obj);
    extern "C" NUM (*UnboxTuple)(NUM count, ...);
    extern "C" id* (*UnboxArray)(id obj, NUM* count);

    extern "C" id GetIsa(id);
    extern "C" NUM GetReferences(id);
    extern "C" NUM GetWeakReferences(id);

    extern "C" SEL (*GetSelector)(const char* value);
    extern "C" id (*GetInstanceVariable)(id obj, SEL name);
    extern "C" NUM (*GetNumberInstanceVariable)(id obj, SEL name);
    extern "C" void (*SetInstanceVariable)(id obj, SEL name, id value);
    extern "C" void (*SetNumberInstanceVariable)(id obj, SEL name, NUM value);
    extern "C" id (*GetGlobal)(const char* name);
    extern "C" void (*SetGlobal)(const char* name, id value);
    extern "C" id (*GetClass)(const char* name);
    extern "C" void (*RegisterClass)(const char* name, id cls);
    extern "C" id (*GetClassSuper)(id cls);
    extern "C" const char* (*GetClassName)(id cls);

    extern "C" NUM (*GetClassMethodCount)(id cls);
    extern "C" NUM (*GetClassInstanceVariableCount)(id cls);
    extern "C" const SEL* (*GetClassInstanceVariableNames)(id cls);

    extern "C" void (*SetClassInstanceVariableName)(id cls, NUM index,
                                                    SEL name);

    extern "C" id (*CreateThread)(IMP fn);
    extern "C" void (*StartThread)(id thrd, NUM argc, ...);
    extern "C" void (*StartThreadV)(id thrd, NUM argc, va_list ap);
    extern "C" void (*StartThreadA)(id thrd, NUM argc, id*);
    extern "C" id (*JoinThread)(id thrd);

    extern "C" void (*Main)(int argc, const char** argv, const char* lib,
                            const char* cls);

    extern "C" bool (*LoadModule)(const char* name);

    extern "C" id (*SendMsg)(id target, SEL sel, NUM argc, ...);
    extern "C" id (*SendMsgV)(id target, SEL sel, NUM argc, va_list ap);
    extern "C" id (*SendMsgA)(id target, SEL sel, NUM argc, id* args);

    extern "C" id (*SendMsgSuper)(id target, SEL sel, NUM argc, ...);
    extern "C" id (*SendMsgSuperV)(id target, SEL sel, NUM argc, va_list ap);
    extern "C" id (*SendMsgSuperA)(id target, SEL sel, NUM argc, id* args);
}
#endif // VOLTZ_VOLTZ_H

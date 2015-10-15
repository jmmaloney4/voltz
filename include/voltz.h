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
//
// void PushExceptionStack(id)
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
#define VZ_PATCH_VERSION 4

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

    extern double StartupTime;

    extern int C_argc;
    extern const char** C_argv;

    typedef struct vz_object* id;
    typedef struct vz_sel* SEL;
    typedef double NUM;
    typedef uint8_t BYTE;
    typedef std::function<id(id, SEL, NUM, id*)>* IMP;
    typedef struct vz_vm VM;
    typedef struct { jmp_buf value; } JmpBuf;

    extern VM VoltzVM;

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
     */

    /** Box a NUM into an object of type Number.
     *
     */
    extern id (*BoxNumber)(NUM value);

    /** Box a BYTE into an object of type Byte.
     *
     */
    extern id (*BoxByte)(BYTE value);

    /** Box a const char* into an object of type String.
     *
     */
    extern id (*BoxString)(const char* value);

    /** Box a NUM (representing a Unicode Code Point) into an object of type
     * Char.
     *
     */
    extern id (*BoxChar)(NUM value);

    /** Box a bool into an object of type Bool.
     *
     */
    extern id (*BoxBool)(bool value);

    /** Box a SEL into a object of type Selector.
     *
     */
    extern id (*BoxSelector)(SEL value);

    /** Box an IMP into a object of type Imp.
     *
     */
    extern id (*BoxImp)(IMP value);

    /** Box an array into an object of type Array.
     *
     *  Sets the generic type to Object.
     */
    extern id (*BoxArray)(NUM count, ...);

    /** Box an array into an object of type Array.
     *
     *  Sets the generic type to Object.
     */
    extern id (*BoxArrayV)(NUM count, va_list ap);

    /** Box an array into an object of type Array.
     *
     *  Sets the generic type to Object.
     */
    extern id (*BoxArrayA)(NUM count, id* value);

    /** Box objects into an object of type tuple.
     *
     */
    extern id (*BoxTuple)(NUM count, ...);

    /** Unbox an object of type Number into a NUM.
     *
     */
    extern NUM (*UnboxNumber)(id obj);

    /** Unbox an object of type Number into a NUM.
     *
     */
    extern BYTE (*UnboxByte)(id obj);

    /** Unbox an object of type String into a const char*.
     *
     *  The return value of this function must be freed after use.
     *
     */
    extern const char* (*UnboxString)(id obj);

    /** Unbox an object of type Char into NUM representing the Unicode Code
     *  Point for that character.
     *
     */
    extern NUM (*UnboxChar)(id obj);

    /** Unbox an object of type Bool.
     *
     */
    extern bool (*UnboxBool)(id obj);

    /** Unbox an object of type Selector into a SEL.
     *
     */
    extern SEL (*UnboxSelector)(id obj);

    /** Unbox an object of type Imp into a IMP.
     *
     *  Return value must be deleted after use.
     *
     */
    extern IMP (*UnboxImp)(id obj);

    /** Unbox an object of type Tuple.
     *
     *  @param count The number of pointers that get passed into @c ...
     *  @param ... A set of id* that will get filled with the values in the
     * tuple,
     *  pass @c nil to denote that that a value is unwanted.
     *
     *  @return The number of objects in the tuple, regardless of @c count.
     */
    extern NUM (*UnboxTuple)(NUM count, ...);

    /** Unbox an object of type Array into an id*.
     *
     *  The return value of this function must be free'd after use.
     *
     *  @c count is filled in with the number of elements in the returned array.
     *  If @c count is @c nil, nothing happens to it.
     */
    extern id* (*UnboxArray)(id obj, NUM* count);

    /** Returns a SEL representing @c value.
     *
     */
    extern SEL (*GetSelector)(const char* value);

    /** Get an object's instance variable that is stored for @c name.
     *
     *  Don't use this except in the setter and getter methods for this class,
     * as
     *  this can mess up the internal state of an object.
     *
     */
    extern id (*GetInstanceVariable)(id obj, SEL name);

    /** Get an object's instance variable that is stored for @c name as a NUM.
     *
     *  Don't use this except in the setter and getter methods for this class,
     * as
     *  this can mess up the internal state of an object.
     *
     */
    extern NUM (*GetNumberInstanceVariable)(id obj, SEL name);

    /** Set an object's instance variable for @c name, to @c value.
     *
     *  Don't use this except in the setter and getter methods for this class,
     * as
     *  this can mess up the internal state of an object.
     */
    extern void (*SetInstanceVariable)(id obj, SEL name, id value);

    /** Set an object's instance variable for @c name, to a NUM @c value.
     *
     *  Don't use this except in the setter and getter methods for this class,
     * as
     *  this can mess up the internal state of an object.
     */
    extern void (*SetNumberInstanceVariable)(id obj, SEL name, NUM value);

    /** Get the type of an object.
     *
     *  Returns nil if @c obj is nil.
     *
     */
    extern id (*GetType)(id obj);

    /** Gets the global variable for the given name.
     *
     */
    extern id (*GetGlobal)(const char* name);

    /** Sets the global variable for the given name.
     *
     */
    extern void (*SetGlobal)(const char* name, id value);

    /** Lookup a class by name.
     *
     */
    extern id (*GetClass)(const char* name);

    /** Register a class to a name.
     *
     */
    extern void (*RegisterClass)(const char* name, id cls);

    /** Get a class' superclass.
     *
     */
    extern id (*GetClassSuper)(id cls);

    /** Get a class' name. Must be freed after use.
     *
     */
    extern const char* (*GetClassName)(id cls);

    /** Get the number of methods a class implements.
     *
     */
    extern NUM (*GetClassMethodCount)(id cls);

    /** Get the number of instance variables a class defines.
     *
     */
    extern NUM (*GetClassInstanceVariableCount)(id cls);

    /** Get the names of the class' instance variables. This is the actual array
     *  used in the class, do NOT modify it and do NOT free it.
     *
     */
    extern const SEL* (*GetClassInstanceVariableNames)(id cls);

    /** Set the name for a class' instance variable.
     *
     */
    extern void (*SetClassInstanceVariableName)(id cls, NUM index, SEL name);

    extern id (*CreateThread)(IMP fn);
    extern void (*StartThread)(id thrd, NUM argc, ...);
    extern void (*StartThreadV)(id thrd, NUM argc, va_list ap);
    extern void (*StartThreadA)(id thrd, NUM argc, id*);
    extern id (*JoinThread)(id thrd);

    /** Implemented by the linker to load modules for an executable.
     *
     */
    extern "C" void LinkerEntry(id argc, id argv);

    /** Loads the module with the specified name. Searches the VOLTZ_PATH
     *  enviroment variable.
     */
    extern bool (*LoadModule)(const char* name);

    extern id (*SendMsg)(id target, SEL sel, NUM argc, ...);
    extern id (*SendMsgV)(id target, SEL sel, NUM argc, va_list ap);
    extern id (*SendMsgA)(id target, SEL sel, NUM argc, id* args);

    extern id (*SendMsgSuper)(id target, SEL sel, NUM argc, ...);
    extern id (*SendMsgSuperV)(id target, SEL sel, NUM argc, va_list ap);
    extern id (*SendMsgSuperA)(id target, SEL sel, NUM argc, id* args);
}
#endif // VOLTZ_VOLTZ_H

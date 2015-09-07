// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>
#include <stdarg.h>
#include <functional>
#include <cstddef>

#define VZ_MAJOR_VERSION 0
#define VZ_MINOR_VERSION 0
#define VZ_PATCH_VERSION 1

#define vz_def(func) new std::function<id(id, SEL, NUM, id*)>([] (id self,    \
        SEL cmd, NUM argc, id* argv) -> id {func})

#define vz_def_capture(list, func) new std::function<id(id, SEL, NUM, id*)>([list] (id self,    \
SEL cmd, NUM argc, id* argv) -> id {func})

const std::nullptr_t nil = NULL;

extern int C_argc;
extern const char** C_argv;

typedef struct vz_object* id;
typedef struct vz_sel* SEL;
typedef double NUM;
typedef std::function<id(id, SEL, NUM, id*)>* IMP;

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


/** Box a NUM into an object of type Number.
 *
 */
extern "C" id(*vz_num_box)(NUM value);

/** Box a const char* into an object of type String.
 *
 */
extern "C" id(*vz_string_box)(const char* value);

/** Box a NUM (representing a Unicode Code Point) into an object of type Char.
 *
 */
extern "C" id(*vz_char_box)(NUM value);

/** Box a SEL into a object of type Selector.
 *
 */
extern "C" id(*vz_sel_box)(SEL value);

/** Box an IMP into a object of type Imp.
 *
 */
extern "C" id(*vz_imp_box)(IMP value);

/** Unbox an object of type Number into a NUM.
 *
 */
extern "C" NUM(*vz_num_unbox)(id obj);

/** Unbox an object of type String into a const char*.
 *
 *  The return value of this function must be freed after use.
 *
 */
extern "C" const char*(*vz_string_unbox)(id obj);

/** Unbox an object of type Char into NUM representing the Unicode Code
 *  Point for that character.
 *
 */
extern "C" NUM(*vz_char_unbox)(id obj);

/** Unbox an object of type Selector into a SEL.
 *
 */
extern "C" SEL(*vz_sel_unbox)(id obj);

/** Unbox an object of type Imp into a IMP.
 *
 */
extern "C" IMP(*vz_imp_unbox)(id obj);

/** Returns a SEL representing @c value.
 *
 */
extern "C" SEL(*vz_sel_get)(const char* value);

/** Get an object's instance variable that is stored for @c name.
 * 
 *  Don't use this except in the setter and getter methods for this class, as 
 *  this can mess up the internal state of an object.
 *
 */
extern "C" id(*vz_object_getIvar)(id obj, const char* name);

/** Get an object's instance variable that is stored for @c name.
 *
 *  Don't use this except in the setter and getter methods for this class, as
 *  this can mess up the internal state of an object.
 *
 */
extern "C" id(*vz_object_getIvar_s)(id obj, SEL name);

/** Set an object's instance variable for @c name, to @c value.
 *
 *  Don't use this except in the setter and getter methods for this class, as
 *  this can mess up the internal state of an object.
 */
extern "C" void(*vz_object_setIvar)(id obj, const char* name, id value);

/** Set an object's instance variable for @c name, to @c value.
 *
 *  Don't use this except in the setter and getter methods for this class, as
 *  this can mess up the internal state of an object.
 */
extern "C" void(*vz_object_setIvar_s)(id obj, SEL name, id value);

/** Get the type of an object.
 *
 *  Returns nil if @c obj is nil.
 *
 */
extern "C" id(*vz_object_getType)(id obj);

/** Gets the global variable for the given name.
 *
 */
extern "C" id(*vz_global_get)(const char* name);

/** Sets the global variable for the given name.
 *
 */
extern "C" void(*vz_global_set)(const char* name, id value);

/** Lookup a class by name.
 *
 */
extern "C" id(*vz_class_get)(const char* name);

/** Register a class to a name.
 *
 */
extern "C" void(*vz_class_register)(const char* name, id cls);

/** Get a class' superclass.
 *
 */
extern "C" id(*vz_class_super)(id cls);

/** Get a class' name. Must be freed after use.
 *
 */
extern "C" const char* (*vz_class_name)(id cls);

/** Get the number of methods a class implements.
 *
 */
extern "C" NUM (*vz_class_mthdc)(id cls);

/** Get the number of instance variables a class defines.
 *
 */
extern "C" NUM (*vz_class_ivarc)(id cls);

/** Get the names of the class' instance variables. This is the actual array 
 *  used in the class, do NOT modify it and do NOT free it.
 *
 */
extern "C" const SEL* (*vz_class_ivarn)(id cls);

/** Implemented by the linker to load modules for an executable.
 *
 */
extern "C" void vz_linker_entry(id argc, id argv);

extern "C" id(*vz_msg_send)(id target, const char* sel, NUM argc, ...);
extern "C" id(*vz_msg_send_v)(id target, const char* sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_a)(id target, const char* sel, NUM argc, id* args);
extern "C" id(*vz_msg_send_s)(id target, SEL sel, NUM argc, ...);
extern "C" id(*vz_msg_send_sv)(id target, SEL sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_sa)(id target, SEL sel, NUM argc, id* args);

extern "C" id(*vz_msg_send_super)(id target, const char* sel, NUM argc, ...);
extern "C" id(*vz_msg_send_super_v)(id target, const char* sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_super_a)(id target, const char* sel, NUM argc, id* args);
extern "C" id(*vz_msg_send_super_s)(id target, SEL sel, NUM argc, ...);
extern "C" id(*vz_msg_send_super_sv)(id target, SEL sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_super_sa)(id target, SEL sel, NUM argc, id* args);

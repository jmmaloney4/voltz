// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>
#include <stdarg.h>
#include <functional>
#include <cstddef>

#define VOLTZ_FN (id self, SEL cmd, NUM argc, id* argv) -> id

const std::nullptr_t nil = NULL;

extern int C_argc;
extern const char** C_argv;

typedef struct vz_object* id;
typedef struct vz_sel* SEL;
typedef double NUM;
typedef std::function<id(id, SEL, NUM, id*)> IMP;

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

/** Returns a SEL representing @c value.
 *
 */
extern "C" SEL(*vz_getSel)(const char* value);

/** Get an object's instance variable that is stored for @c name.
 * 
 *  Don't use this except in the setter and getter methods for this class, as 
 *  this can mess up the internal state of an object.
 *
 */
extern "C" id(*vz_object_ivarForName)(const char* name);

/** Set an object's instance variable for @c name, to @c value.
 *
 *  Don't use this except in the setter and getter methods for this class, as
 *  this can mess up the internal state of an object.
 */
extern "C" void(*vz_object_setIvarForName)(const char* name, id value);

/** Get the type of an object.
 *
 *  Returns nil if @c obj is nil.
 *
 */
extern "C" id(*vz_object_getType)(id obj);


extern "C" id(*vz_msg_send)(id target, const char* sel, NUM argc, ...);
extern "C" id(*vz_msg_send_s)(id target, SEL sel, NUM argc, ...);
extern "C" id(*vz_msg_send_v)(id target, const char* sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_a)(id target, const char* sel, NUM argc, id* args);
extern "C" id(*vz_msg_send_sv)(id target, SEL sel, NUM argc, va_list ap);
extern "C" id(*vz_msg_send_sa)(id target, SEL sel, NUM argc, id* args);



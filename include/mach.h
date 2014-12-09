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

#ifndef _mach_h
#define _mach_h

#ifndef __cplusplus
#error "mach Requires A C++ Compiler"
#endif

#ifndef NULL
#define NULL nullptr
#endif

#define nil ((id)NULL)

#define MACH_DEPRECATED __attribute__((deprecated))

typedef long long int_t;
typedef double flt_t;

typedef struct object* id;
typedef struct _class* Class;
typedef struct sel* Sel;
typedef id (*Imp)(id, Sel, id*);

#define MACH_MTHD(name) id name (id self, Sel cmd, id* argv)

enum ObjectType {
    ObjectTypeObj,
    ObjectTypeCls,
    ObjectTypeMCls
};

/** Initializes the runtime. MUST be the fist function called. */
void InitializeRuntime();

/** Loads the specified Module, so that classes may be loaded from it. */
void LoadModule(const char* path);
/** Loads the specified Class. */
void LoadClass(const char* cls, const char* ns);

/** Returns true if the specified object is an instance of c, or any of c's
 subclasses, otherwise it returns false. */
bool IsOfKind(id x, Class c);
/** Returns a selector representing the specified string. */
Sel GetSel(const char* value);
/** Sends the specified message to the specified object, and returns the result
 of the method. */
id SendMsg(id target, Sel cmd, ...);
/** Returns the value of the specified ivar from the specified object. */
#define ivar(c, of, o) \
o->ivars[(((Class)c)->super != NULL ? ((Class)c)->super->ivarc : 0) + of]
/** Sets the specified ivar of the specified object to the specified value. */
#define setivar(c, of, o, v) \
o->ivars[(((Class)c)->super != NULL ? ((Class)c)->super->ivarc : 0) + of] = v;
/** Creates a class with the specified name, superclass, method count, metaclass
 method count, and ivar count. */
Class CreateClass(const char* name, Class super, int_t mthdc, int_t imthdc,
                  int_t ivarc);
/** Returns the specified Class's method count. */
int_t ClassMthdc(Class c);
/** Returns the specified Class's ivar count. */
int_t ClassIVarc(Class c);
/** Returns the specified Class's name. */
const char* ClassName(Class c);
/** Returns the specified object's (or class's) type. */
ObjectType GetType(id x);
/** Returns the specified object's refrence count. */
int_t GetRefs(id x);
/** Sets the specified object's refrence count to the specified value. */
void SetRefs(id x, int_t r);
/** Increments the specified object's refrence count. */
void IncRefs(id x);
/** Decrements the specified object's refrence count. */
void DecRefs(id x);
/** Returns the specified object's class. */
Class GetClass(id x);

/** Returns a String object representing the specified string. The caller
    does not need to keep the string in memory after the function returns. This 
    assumes that the specified string is encoded as UTF-8. */
id StringLit(const char* str);
/** Returns a Int object representing the specified int. */
id IntLit(int_t i);
/** Returns a Float object representing the specified float. */
id FloatLit(flt_t f);
/** Returns a Char object representing the specified Unicode value, which for 
    ASCII happens to be the same as the actual characters. */
id CharLit(int_t unv);
/** Returns a Bool object representing the specified boolean value. */
id BoolLit(bool bl);
/** Returns a Range object representing a range starting and ending with the
    specified values. Start and end are both inclusive. */
id RangeLit(int_t start, int_t end);
/** Returns a Closure object representing a closure, with the specified 
    implementation, and the specified number of variables and values. */
id ClosureLit(Imp imp, int_t vars, ...);
/** Returns a Selector object representing the specified Sel. */
id SelectorLit(Sel sel);

/** Converts the specified String object into a UTF-8 encoded C string. The
    caller is responsible for free()-ing the returned string. */
char* StringCvt(id str);
/** Converts the specified Int object into an equivalent C int_t. */
int_t IntCvt(id i);
/** Converts the specified Float object into an equivailent C flt_t. */
flt_t FloatCvt(id f);
/** Converts the specified Char object into a C int_t representing the Unicode
    value of the object. */
int_t CharCvt(id c);
/** Converts the specified Bool object into an equivalent C++ bool. */
bool BoolCvt(id b);
/** Returns the variable count for the specified Closure object. */
int_t ClosureVarc(id c);
/** Converts the specified Selector object into a C Sel. */
Sel SelectorCvt(id s);

#endif

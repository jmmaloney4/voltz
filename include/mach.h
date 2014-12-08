//
//  mach.h
//  
//
//  Created by Jack Maloney on 12/4/14.
//
//

#ifndef _mach_h
#define _mach_h

#ifndef __cplusplus
#error "mach Requires A C++ Compiler"
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef long long int_t;
typedef double flt_t;

typedef struct object* id;
typedef struct _class* Class;
typedef struct sel* Sel;
typedef id (*Imp)(id, Sel, id*);

enum ObjectType {
    ObjectTypeObj,
    ObjectTypeCls,
    ObjectTypeMCls
};

union ivar {
    id obj;
    Class cls;
    int_t i64;
    flt_t f64;
    void* data;
    
    operator id() { return this->obj; }
    ivar operator=(id obj) { this->obj = obj; return *this; }
};

struct object {
public:
    Class isa;
    int_t refs;
    ObjectType type;
    
    // Dynamically Allocated
    union ivar ivars[0];
};

struct _class : public object {
public:
    Class super;
    const char* name;
    int_t mthdc;
    int_t ivarc;
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

#define ivar(c, of, o) \
o->ivars[(((Class)c)->super != NULL ? ((Class)c)->super->ivarc : 0) + of]
#define sivar(c, of, o, v) \
o->ivars[(((Class)c)->super != NULL ? ((Class)c)->super->ivarc : 0) + of] = v;

/** Returns an object representing the specified string. The caller
    does not need to keep the string in memory after the function returns. This 
    assumes that the specified string is encoded as UTF-8, which can be achived 
    in C++ by putting 'u8' in front of a string literal, 
    like so: u8"Hello, World".  */
id StringLit(const char* str);
/** Returns an object representing the specified int. */
id IntLit(int_t i);
/** Returns an object representing the specified float. */
id FloatLit(flt_t f);
/** Returns an object representing the specified Unicode value, which for ASCII
    happens to be the same as the actual characters. */
id CharLit(int_t unv);
/** Returns an object representing the specified boolean value. */
id BoolLit(bool bl);
/** Returns an object representing a range starting and ending with the
    specified values. Start and end are both inclusive. */
id RangeLit(int_t start, int_t end);

/** Converts the specified string object into a UTF-8 encoded C string. The caller is
    responsible for free()-ing the returned string. */
char* StringCvt(id str);
/** Converts the specified int object into an equivalent C int_t. */
int_t IntCvt(id i);
/** Converts the specified float object into an equivailent C flt_t. */
flt_t FloatCvt(id f);
/** Converts the specified char object into a C int_t representing the Unicode 
    value of the object. */
int_t CharCvt(id c);
/** Converts the specified char object into an equivalent C++ bool. */
bool BoolCvt(id b);

#endif

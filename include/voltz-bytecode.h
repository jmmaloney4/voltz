// voltz-bytecode.h
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VOLTZ_BYTECODE_H
#define VOLTZ_BYTECODE_H

#include <stdint.h>
#include <stdio.h>

const int64_t MAGIC_NUMBER = 0x6A626F7A746C6F76;
const int64_t NOARG = 9223372036854775807;

namespace voltz {
    
    struct Instruction {
        enum Type {
            NOP = 0x0,
            
            BLTIN = 0x1,
            BREAK = 0x2,
            IMPORT = 0x3,
            PRINT = 0x4,
            
            MSG = 0x10,
            MSGSPR = 0x11,
            RET = 0x12,
            RETN = 0x13,
            POP = 0x14,
            POPR = 0x15,
            POPA = 0x16, // Pop all values int the current frame off
            POPAR = 0x17,
            DUP = 0x18,
            DUPR = 0x19,
            LOAD = 0x1a, // Copy a value from the stack to the top
            LOADR = 0x1b,
            STORE = 0x1c,
            STORER = 0x1d,
            SET = 0x1e,
            JMP = 0x1f,
            JMPCND = 0x2a,
            YIELD = 0x2b,
            
            LDSELF = 0x30,
            LDIVAR = 0x31,
            STIVAR = 0x32,
            LDIVARC = 0x33,
            
            LDARGC = 0x34,
            LDSZ = 0x35,
            LDGBL = 0x36,
            STGBL = 0x37,
            
            LDNIL = 0x40,
            LDINT = 0x41,
            LDFLT = 0x42,
            LDCHAR = 0x43,
            LDSTR = 0x44,
            LDTRUE = 0x45,
            LDFALSE = 0x46,
            LDSEL = 0x47,
            LDCLOS = 0x48,
            LDCLASS = 0x49,
        };
        
        enum Builtin {
            Alloc = 0x0,
            
        };
        
        union Value {
            int64_t i64;
            double f64;
            char c8;
            const char* str;
            char data[8];
            Builtin bltin;
            struct {
                int64_t count;
                Instruction* insts;
            } closure;
        };
        
        Type type;
        Value value;
        
        Instruction() { this->type = NOP; }
        Instruction(Type t) { this->type = t; }
        Instruction(Type t, Value v) { this->type = t; this->value = v; }
    };
    
    const char* GetNameForInstruction(Instruction::Type t);
    Instruction::Type GetInstructionForName(const char* name);
        
    Instruction* LoadAssemblyFile(FILE* file, int64_t* instc);
    Instruction* LoadBinaryFile(FILE* file, int64_t* instc);
    void WriteAssemblyFile(FILE* file, Instruction* insts, int64_t instc);
    void WriteBinaryFile(FILE* file, Instruction* insts, int64_t instc);
}

#endif
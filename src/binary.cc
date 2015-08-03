// binary.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"

using namespace voltz;

int64_t CharsToInt(uint8_t* chars) {
    // Don't modify argument
    uint8_t tmp;
    tmp = chars[0];
    bool neg = false;
    if (tmp & 0x80) {
        tmp &= 0x7f;
        neg = true;
    }
    
    int64_t rv = chars[7] + (chars[6] * 0x100) + (chars[5] * 0x10000) + (chars[4] * 0x1000000) + (chars[3] * 0x100000000) + (chars[2] * 0x10000000000) + (chars[1] * 0x1000000000000) + (tmp * 0x100000000000000);
    if (neg) {
        rv *= -1;
    }
    return rv;
    
}

void IntToChars(int64_t i, uint8_t* chars) {
    int64_t num = i;
    bool neg = false;
    if (i & 0x8000000000000000) {
        neg = true;
        num *= -1;
    }
    
    chars[0] = num / 0x100000000000000;
    num = num % 0x100000000000000;
    chars[1] = num / 0x1000000000000;
    num = num % 0x1000000000000;
    chars[2] = num / 0x10000000000;
    num = num % 0x10000000000;
    chars[3] = num / 0x100000000;
    num = num % 0x100000000;
    chars[4] = num / 0x1000000;
    num = num % 0x1000000;
    chars[5] = num / 0x10000;
    num = num % 0x10000;
    chars[6] = num / 0x100;
    num = num % 0x100;
    chars[7] = num;
    
    if (neg) {
        chars[0] += 0x80;
    }
}

int64_t ReadBinaryInt(FILE* file) {
    uint8_t chars[8];
    for (int k = 0; k < 8; k++) {
        chars[k] = fgetc(file);
    }
    int64_t rv = CharsToInt(chars);
    return rv;
}

const char* ReadBinaryString(FILE* file) {
    int64_t len = ReadBinaryInt(file);
    if (len == NOARG) {
        return (const char*) NOARG;
    }
    char* rv = new char[sizeof(char) * (len + 1)]();
    
    for (int64_t k = 0; k < len; k++) {
        rv[k] = fgetc(file);
    }
    rv[len] = '\0';
    return rv;
}

Instruction ReadBinaryInstruction(FILE* file) {
    Instruction::Type i = (Instruction::Type) fgetc(file);
    Instruction rv = Instruction(i);
    switch (i) {
        case Instruction::NOP:
        case Instruction::BREAK:
        case Instruction::MSG:
        case Instruction::MSGSPR:
        case Instruction::RET:
        case Instruction::RETN:
        case Instruction::POPA:
        case Instruction::POPAR:
        case Instruction::DUP:
        case Instruction::DUPR:
        case Instruction::SET:
        case Instruction::YIELD:
        case Instruction::LDSELF:
        case Instruction::LDIVARC:
        case Instruction::LDARGC:
        case Instruction::LDSZ:
        case Instruction::LDNIL:
        case Instruction::LDTRUE:
        case Instruction::LDFALSE: {
            // No Arguments
            break;
        }
        case Instruction::POP:
        case Instruction::POPR:
        case Instruction::LOAD:
        case Instruction::LOADR:
        case Instruction::STORE:
        case Instruction::STORER:
        case Instruction::JMP:
        case Instruction::JMPCND:
        case Instruction::LDIVAR:
        case Instruction::STIVAR: {
            // Optional Integer Argument
            int64_t arg = ReadBinaryInt(file);
            rv.value.i64 = arg;
            break;
        }
        case Instruction::LDGBL:
        case Instruction::LDSEL:
        case Instruction::LDCLASS: {
            // Optional String Argument
            const char* arg = ReadBinaryString(file);
            rv.value.str = arg;
            break;
        }
        case Instruction::BLTIN:
        case Instruction::LDINT: {
            // Required Integer Argument
            int64_t arg = ReadBinaryInt(file);
            rv.value.i64 = arg;
            break;
        }
        case Instruction::LDFLT: {
            // Required Float Argument
            break;
        }
        case Instruction::LDCHAR: {
            // Required Character Argument
            int64_t arg = ReadBinaryInt(file);
            rv.value.i64 = arg;
            break;
        }
        case Instruction::IMPORT:
        case Instruction::PRINT:
        case Instruction::LDSTR: {
            // Required String Argument
            const char* str = ReadBinaryString(file);
            rv.value.str = str;
            break;
        }
        case Instruction::LDCLOS: {
            // Required Closure Argument
            int64_t count = ReadBinaryInt(file);
            
            Instruction* instv = new Instruction[count]();
            for (int64_t k = 0; k < count; k++) {
                instv[k] = ReadBinaryInstruction(file);
            }
            rv.value.closure.count = count;
            rv.value.closure.insts = instv;
        }
    }
    
    return rv;
}

Instruction* voltz::LoadBinaryFile(FILE *file, int64_t *instc) {
    
    int64_t magic = ReadBinaryInt(file);
    if (magic != MAGIC_NUMBER) {
        *instc = -1;
        return NULL;
    }
    
    int64_t count = ReadBinaryInt(file);
    
    Instruction* rv = new Instruction[count]();
    
    for (int64_t k = 0; k < count; k++) {
        
    }
    
}
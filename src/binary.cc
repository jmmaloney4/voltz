// binary.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"
#include <string.h>
#include <math.h>

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

bool BigEndian(void) {
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};
    
    return bint.c[0] == 1;
}

// Implemented in assembly.cc, used because floats are stored as a string
// even in the binary format, because otherwise they're a pain to deal with.
double ParseFloatFromString(const char* str);

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
            rv.value.i64 = 0;
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
        case Instruction::STIVAR:
        case Instruction::LDARG: {
            // Optional Integer Argument
            int64_t arg = ReadBinaryInt(file);
            rv.value.i64 = arg;
            break;
        }
        case Instruction::STGBL:
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
            uint8_t arr[8];
            fread(arr, sizeof(uint8_t), 8, file);
            
            double d = 0;
            
            if (BigEndian()) {
                memcpy(&d, arr, sizeof(uint8_t) * 8);
            } else {
                // Flip Endianness
                uint8_t tmp[8];
                tmp[0] = arr[7];
                tmp[1] = arr[6];
                tmp[2] = arr[5];
                tmp[3] = arr[4];
                tmp[4] = arr[3];
                tmp[5] = arr[2];
                tmp[6] = arr[1];
                tmp[7] = arr[0];
                
                arr[0] = tmp[0];
                arr[1] = tmp[1];
                arr[2] = tmp[2];
                arr[3] = tmp[3];
                arr[4] = tmp[4];
                arr[5] = tmp[5];
                arr[6] = tmp[6];
                arr[7] = tmp[7];
                
                memcpy(&d, arr, sizeof(uint8_t) * 8);
            }
            
            rv.value.f64 = d;
            
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
            break;
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
        rv[k] = ReadBinaryInstruction(file);
    }
    
    *instc = count;
    return rv;
}

void WriteBinaryInstruction(FILE* file, Instruction i) {
    
    uint8_t t = (uint8_t) i.type;
    fwrite(&t, sizeof(uint8_t), 1, file);
    
    switch (i.type) {
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
        case Instruction::STIVAR:
        case Instruction::LDARG: {
            // Optional Integer Argument
            uint8_t chars[8];
            IntToChars(i.value.i64, chars);
            fwrite(chars, sizeof(uint8_t), 8, file);
            break;
        }
        case Instruction::STGBL:
        case Instruction::LDGBL:
        case Instruction::LDSEL:
        case Instruction::LDCLASS: {
            // Optional String Argument
            int64_t len = strlen(i.value.str);
            uint8_t chars[8 + len];
            IntToChars(len, chars);
            for (int64_t k = 0; k < len; k++) {
                chars[8 + k] = i.value.str[k];
            }
            
            fwrite(chars, sizeof(uint8_t), len + 8, file);
            break;
        }
        case Instruction::BLTIN:
        case Instruction::LDINT: {
            // Required Integer Argument
            uint8_t chars[8];
            IntToChars(i.value.i64, chars);
            fwrite(chars, sizeof(uint8_t), 8, file);
            break;
        }
        case Instruction::LDFLT: {
            // Required Float Argument
            uint8_t arr[8];
            memcpy(arr, &i.value.f64, 8);
            if (!BigEndian()) {
                // Flip Endianness
                uint8_t tmp[8];
                tmp[0] = arr[7];
                tmp[1] = arr[6];
                tmp[2] = arr[5];
                tmp[3] = arr[4];
                tmp[4] = arr[3];
                tmp[5] = arr[2];
                tmp[6] = arr[1];
                tmp[7] = arr[0];
                
                arr[0] = tmp[0];
                arr[1] = tmp[1];
                arr[2] = tmp[2];
                arr[3] = tmp[3];
                arr[4] = tmp[4];
                arr[5] = tmp[5];
                arr[6] = tmp[6];
                arr[7] = tmp[7];
            }
            
            fwrite(arr, sizeof(uint8_t), 8, file);
            
            break;
        }
        case Instruction::LDCHAR: {
            uint8_t chars[8];
            IntToChars(i.value.i64, chars);
            fwrite(chars, sizeof(uint8_t), 8, file);
            break;
        }
        case Instruction::IMPORT:
        case Instruction::PRINT:
        case Instruction::LDSTR: {
            // Required String Argument
            int64_t len = strlen(i.value.str);
            uint8_t chars[8 + len];
            IntToChars(len, chars);
            for (int64_t k = 0; k < len; k++) {
                chars[8 + k] = i.value.str[k];
            }
            
            fwrite(chars, sizeof(uint8_t), len + 8, file);
            break;
        }
        case Instruction::LDCLOS: {
            // Required Closure Argument
            uint8_t chars[8];
            IntToChars(i.value.closure.count, chars);
            fwrite(chars, sizeof(uint8_t), 8, file);
            
            for (int64_t k = 0; k < i.value.closure.count; k++) {
                WriteBinaryInstruction(file, i.value.closure.insts[k]);
            }
            break;
        }

    }
    
}

void voltz::WriteBinaryFile(FILE *file, voltz::Instruction *insts, int64_t instc) {
    
    uint8_t chars[8];
    IntToChars(MAGIC_NUMBER, chars);
    fwrite(chars, sizeof(uint8_t), 8, file);
    
    IntToChars(instc, chars);
    fwrite(chars, sizeof(uint8_t), 8, file);
    
    for (int64_t k = 0; k < instc; k++) {
        WriteBinaryInstruction(file, insts[k]);
    }
    
}
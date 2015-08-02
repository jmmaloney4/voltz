// assembly.cc
// Copyright (c) 2015 Jack Maloney All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace voltz;

bool IsLetter(char c) {
    return c >= 'a' && c <= 'z';
}

bool IsNumber(char c) {
    return c >= '0' && c <= '9';
}

void EatWhitespace(FILE* file) {
    for (char c = fgetc(file); c == '\0' || c == ' ' || c == '\t' || c == '\n'; c = fgetc(file)) {}
    fseek(file, -1, SEEK_CUR);
}

void EatLine(FILE* file) {
    for (char c = fgetc(file); c != '\n'; c = fgetc(file)) {}
}

const char* ReadQuotedString(FILE* file) {
    
    char c = fgetc(file);
    if (c != '"') {
        return NULL;
    }
    
    int64_t sz = 0;
    char* str = new char[1]();
    str[0] = '\0';
    
    for (c = fgetc(file); true; c = fgetc(file)) {
        if (c == '"') {
            break;
        }
        
        sz++;
        char* tmp = new char[sz + 1]();
        for (int64_t k = 0; k < (sz - 1); k++) {
            tmp[k] = str[k];
        }
        tmp[sz - 1] = c;
        tmp[sz] = '\0';
        
        delete[] str;
        str = tmp;
    }
    
    return str;
}

const char* ReadString(FILE* file) {
    int64_t count = 0;
    
    char c = fgetc(file);
    if (c == '"') {
        fseek(file, -1, SEEK_CUR);
        return ReadQuotedString(file);
    }
    
    for (; (c != ' ' && c != '\t' && c != '\n'); c = fgetc(file)) {
        if (c == EOF) {
            return NULL;
        }
        count++;
    }
    if (count == 0) {
        return NULL;
    }
    
    fseek(file, (count + 1) * -1, SEEK_CUR);
    
    char* str = new char[count + 1]();
    for (int64_t k = 0; k < count; k++) {
        str[k] = fgetc(file);
    }
    str[count] = '\0';
    
    return str;
}

int64_t ParseIntFromString(const char* str) {
    int64_t len = strlen(str);
    for (int64_t k = 0; k < len; k++) {
        if (!IsNumber(str[k])) {
            printf("Parse Error!\n");
            exit(1);
        }
    }
    
    int64_t rv = 0;
    for (int64_t k = 0; k < len; k++) {
        rv += (str[k] - '0') * pow(10, (len - 1) - k);
    }
    
    return rv;
}

double ParseFloatFromString(const char* str) {
    int64_t len = strlen(str);
    
    char* end = NULL;
    double rv = strtod(str, &end);
    if (str + (sizeof(char) * len) != end) {
        printf("Parse Error!\n");
        exit(1);
    }
    
    return rv;
}

const char* ParseEscapeCharacters(const char* str) {
    int64_t len = strlen(str);
    
    char* rv = new char[len + 1]();
    
    int64_t index = 0;
    for (int64_t k = 0; k < len; k++, index++) {
        if (str[k] == '\\' && (k + 1) < len) {
            switch (str[k + 1]) {
                case '0': {
                    rv[index] = '\0';
                    break;
                }
                case 'n': {
                    rv[index] = '\n';
                    break;
                }
                case 't': {
                    rv[index] = '\t';
                    break;
                }
                case 'r': {
                    rv[index] = '\r';
                    break;
                }
                case '\\': {
                    rv[index] = '\\';
                    break;
                }
                default: {
                    rv[index] = str[2];
                    break;
                }
            }
            k++;
        } else {
            rv[index] = str[k];
        }
    }
    
    return rv;
}

Instruction ReadInstruction(FILE* file) {
    Instruction rv;
    
    EatWhitespace(file);
    const char* inst = ReadString(file);
    if (!inst) {
        rv.type = Instruction::NOP;
        return rv;
    }
    rv.type = GetInstructionForName(inst);
    
    delete[] inst;
    
    switch (rv.type) {
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
            EatLine(file);
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
            EatWhitespace(file);
            
            char c = fgetc(file);
            if (!IsNumber(c)) {
                break;
            }
            fseek(file, -1, SEEK_CUR);
            
            const char* str = ReadString(file);
            int64_t i = ParseIntFromString(str);
            rv.value.i64 = i;
            
            delete[] str;
            
            EatLine(file);
            break;
        }
        case Instruction::LDGBL:
        case Instruction::LDSEL:
        case Instruction::LDCLASS: {
            // Optional String Argument
            EatWhitespace(file);
            
            char c = fgetc(file);
            if (c != '"') {
                rv.value.str = NULL;
                break;
            }
            fseek(file, -1, SEEK_CUR);
            
            const char* str = ReadString(file);
            const char* s = ParseEscapeCharacters(str);
            
            rv.value.str = s;
            
            delete[] str;
            
            EatLine(file);
            break;
        }
            
        case Instruction::BLTIN:
        case Instruction::LDINT: {
            // Required Integer Argument
            EatWhitespace(file);
            
            const char* str = ReadString(file);
            int64_t i = ParseIntFromString(str);
            rv.value.i64 = i;
            
            delete[] str;
            
            EatLine(file);
            break;
        }
        case Instruction::LDFLT: {
            // Required Float Argument
            EatWhitespace(file);
            
            const char* str = ReadString(file);
            double f = ParseFloatFromString(str);
            rv.value.f64 = f;
            
            delete[] str;
            
            EatLine(file);
            break;
        }
        case Instruction::LDCHAR: {
            // Required Character Argument
            EatWhitespace(file);
            
            const char* str = ReadString(file);
            
            if (strlen(str) < 3) {
                printf("Parse Error!\n");
                exit(1);
            }
            
            char c = '\0';
            
            if (str[0] != '\'') {
                printf("Parse Error!\n");
                exit(1);
            }
            
            if (str[1] == '\\') {
                switch (str[2]) {
                    case '0': {
                        c = '\0';
                        break;
                    }
                    case 'n': {
                        c = '\n';
                        break;
                    }
                    case 't': {
                        c = '\t';
                        break;
                    }
                    case 'r': {
                        c = '\r';
                        break;
                    }
                    case '\\': {
                        c = '\\';
                        break;
                    }
                    default: {
                        c = str[2];
                        break;
                    }
                }
            }
            
            rv.value.c8 = c;
            
            delete[] str;
            
            EatLine(file);
            break;
        }
        case Instruction::IMPORT:
        case Instruction::PRINT:
        case Instruction::LDSTR: {
            // Required String Argument
            EatWhitespace(file);
            
            const char* str = ReadString(file);
            const char* s = ParseEscapeCharacters(str);
            
            rv.value.str = s;
            
            delete[] str;
            
            EatLine(file);
            break;
        }
        case Instruction::LDCLOS: {
            // Required Closure Argument
            EatWhitespace(file);
            
            char c = fgetc(file);
            if (c != '{') {
                printf("Parse Error!\n");
                exit(1);
            }
            
            int64_t instc = 0;
            Instruction* insts = new Instruction[0]();
            
            for (Instruction i = ReadInstruction(file); true; i = ReadInstruction(file)) {
                instc++;
                Instruction* tmp = new Instruction[instc]();
                for (int64_t k = 0; k < (instc - 1); k++) {
                    tmp[k] = insts[k];
                }
                tmp[instc - 1] = i;
                
                delete [] insts;
                insts = tmp;
                
                char c = fgetc(file);
                if (c == '}') {
                    break;
                }
            }
            
            rv.value.insts = insts;
            
            EatLine(file);
            break;
        }
    }
    
    return rv;
}

Instruction* voltz::LoadAssemblyFile(FILE* file, int64_t* instc) {
    
    int64_t size = 0;
    Instruction* rv = new Instruction[0]();
    
    for (Instruction i = ReadInstruction(file); true; i = ReadInstruction(file)) {
        size++;
        Instruction* n = new Instruction[size]();
        for (int64_t k = 0; k < (size - 1); k++) {
            n[k] = rv[k];
        }
        n[size - 1] = i;
        
        delete[] rv;
        rv = n;
        
        char c = fgetc(file);
        if (c == EOF) {
            break;
        } else {
            fseek(file, -1, SEEK_CUR);
        }
    }
    
    *instc = size;
    return rv;
}

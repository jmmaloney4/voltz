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

const char* InsertNewlineEscapes(const char* str) {
    int64_t size = 0;
    char* rv = new char[1]();
    rv[0] = '\0';
    
    int64_t len = strlen(str);
    
    for (int64_t k = 0; k < len; k++) {
        int64_t newsize;
        if (str[k] == '\n') {
            newsize = size + 2;
        } else {
            newsize = size + 1;
        }
        
        char* tmp = new char[newsize + 1]();
        for (int64_t j = 0; j < size; j++) {
            tmp[j] = rv[j];
        }
        tmp[newsize] = '\0';
        
        if (str[k] == '\n') {
            tmp[size] = '\\';
            tmp[size + 1] = 'n';
        } else {
            tmp[size] = str[k];
        }
        
        delete[] rv;
        rv = tmp;
        size = newsize;
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
                rv.value.i64 = NOARG;
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
                rv.value.i64 = NOARG;
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
        // TODO: UTF8 Support
        case Instruction::LDCHAR: {
            // Required Character Argument
            EatWhitespace(file);
            
            const char* str = ReadString(file);
            int64_t len = strlen(str);
            
            if (len > 6) {
                printf("Parse Error!\n");
                exit(1);
            }
            
            uint64_t c = 0;
            
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
            } else if (((uint8_t) str[1]) >= 0x80) {
                // UTF-8
                if (((uint8_t) str[1]) >= 0xf0 && len == 6) {
                    // 4-byte
                    c = (((uint8_t) str[1]) - 240) * 262144 + (((uint8_t) str[2]) - 128) * 4096 + (((uint8_t) str[3]) - 128) * 64 + (((uint8_t) str[4]) - 128);
                } else if (((uint8_t) str[1]) >= 0xe0 && len == 5) {
                    // 3-byte
                    c = (((uint8_t) str[1]) - 224) * 4096 + (((uint8_t) str[2]) - 128) * 64 + (((uint8_t) str[3]) - 128);
                } else if (((uint8_t) str[1]) >= 0xc0 && len == 4) {
                    // 2-byte
                    c = ((((uint8_t) str[1]) - 192) * 64) + ((uint8_t) str[2]) - 128;
                } else {
                    printf("Bad UTF-8 Character!\n");
                    exit(1);
                }
            } else if (len == 3) {
                c = str[1];
            } else {
                printf("Parse Error!\n");
                exit(1);
            }
            
            rv.value.i64 = c;
            
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
            // FIXME: Nested Calls to LDCLOS
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
                
                EatWhitespace(file);
                char c = fgetc(file);
                if (c == '}') {
                    break;
                }
                fseek(file, -1, SEEK_CUR);
            }
            
            rv.value.closure.count = instc;
            rv.value.closure.insts = insts;
            
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

void WriteAssemblyInstruction(FILE* file, Instruction i, int64_t indent) {
    
    for (int64_t k = 0; k < indent; k++) {
        fprintf(file, "\t");
    }
    
    fprintf(file, "%s", GetNameForInstruction(i.type));
    
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
            // No Argument
            fprintf(file, "\n");
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
            if (i.value.i64 != NOARG) {
                fprintf(file, " %lli\n", i.value.i64);
            }
            break;
        }
        case Instruction::LDGBL:
        case Instruction::LDSEL:
        case Instruction::LDCLASS: {
            // Optional String Argument
            if (i.value.str != (const char*) NOARG) {
                const char* str = InsertNewlineEscapes(i.value.str);
                fprintf(file, " \"%s\"\n", str);
                delete[] str;
            }
            break;
        }
        case Instruction::BLTIN:
        case Instruction::LDINT: {
            // Required Integer Argument
            fprintf(file, " %lli\n", i.value.i64);
            break;
        }
        case Instruction::LDFLT: {
            // Required Float Argument
            fprintf(file, " %f\n", i.value.f64);
            break;
        }
            // TODO: UTF8 Support
        case Instruction::LDCHAR: {
            // Required Character Argument
            
            if (i.value.i64 == '\n') {
                printf(" '\\n'\n");
                break;
            }
            
            char cs[5] = {0};
            
            if (i.value.i64 < 0x80) cs[0] = i.value.i64;
            else if (i.value.i64 < 0x800) {
                cs[0] = 192 + i.value.i64 / 64;
                cs[1] = 128 + i.value.i64 % 64;
            }
            else if (i.value.i64 - 0xd800u < 0x800) {
                printf("Parse Error!\n");
                exit(1);
            }
            else if (i.value.i64 < 0x10000) {
                cs[0] = 224 + i.value.i64 / 4096;
                cs[1] = 128 + i.value.i64 / 64 % 64;
                cs[2] = 128 + i.value.i64 % 64;
            }
            else if (i.value.i64 < 0x110000) {
                cs[0] = 240 + i.value.i64 / 262144;
                cs[1] = 128 + i.value.i64 / 4096 % 64;
                cs[2] = 128 + i.value.i64 / 64 % 64;
                cs[3] = 128 + i.value.i64 % 64;
            }
            else {
                printf("Parse Error!\n");
                exit(1);
            }
            
            fprintf(file, " '%s'\n", cs);
            break;
        }
        case Instruction::IMPORT:
        case Instruction::PRINT:
        case Instruction::LDSTR: {
            // Required String Argument
            const char* str = InsertNewlineEscapes(i.value.str);
            fprintf(file, " \"%s\"\n", str);
            delete[] str;
            break;
        }
            // FIXME: Nested Calls to LDCLOS
        case Instruction::LDCLOS: {
            // Required Closure Argument
            fprintf(file, " {\n");
            
            for (int64_t k = 0; k < i.value.closure.count; k++) {
                WriteAssemblyInstruction(file, i.value.closure.insts[k], indent + 1);
            }
            for (int64_t k = 0; k < indent; k++) {
                fprintf(file, "\t");
            }
            fprintf(file, "}\n");
            
            break;
        }
            
    }
    
}

void voltz::WriteAssemblyFile(FILE* file, voltz::Instruction* insts, int64_t instc) {
    for (int64_t k = 0; k < instc; k++) {
        WriteAssemblyInstruction(file, insts[k], 0);
    }
}

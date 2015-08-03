// bytecode.cc
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

const char* voltz::GetNameForInstruction(Instruction::Type t) {
    switch (t) {
        case voltz::Instruction::NOP: return "nop";
        case voltz::Instruction::BLTIN: return "bltin";
        case voltz::Instruction::BREAK: return "break";
        case voltz::Instruction::IMPORT: return "import";
        case voltz::Instruction::PRINT: return "print";
            
        case voltz::Instruction::MSG: return "msg";
        case voltz::Instruction::MSGSPR: return "msgspr";
        case voltz::Instruction::RET: return "ret";
        case voltz::Instruction::RETN: return "retn";
        case voltz::Instruction::POP: return "pop";
        case voltz::Instruction::POPR: return "popr";
        case voltz::Instruction::POPA: return "popa";
        case voltz::Instruction::POPAR: return "popar";
        case voltz::Instruction::DUP: return "dup";
        case voltz::Instruction::DUPR: return "dupr";
        case voltz::Instruction::LOAD: return "load";
        case voltz::Instruction::LOADR: return "loadr";
        case voltz::Instruction::STORE: return "store";
        case voltz::Instruction::STORER: return "storer";
        case voltz::Instruction::SET: return "set";
        case voltz::Instruction::JMP: return "jmp";
        case voltz::Instruction::JMPCND: return "jmpcnd";
        case voltz::Instruction::YIELD: return "yield";
            
        case voltz::Instruction::LDSELF: return "ldself";
        case voltz::Instruction::LDIVAR: return "ldivar";
        case voltz::Instruction::STIVAR: return "stivar";
        case voltz::Instruction::LDIVARC: return "ldivarc";
            
        case voltz::Instruction::LDARGC: return "ldargc";
        case voltz::Instruction::LDSZ: return "ldsz";
        case voltz::Instruction::LDGBL: return "ldgbl";
            
        case voltz::Instruction::LDNIL: return "ldnil";
        case voltz::Instruction::LDINT: return "ldint";
        case voltz::Instruction::LDFLT: return "ldflt";
        case voltz::Instruction::LDCHAR: return "ldchar";
        case voltz::Instruction::LDSTR: return "ldstr";
        case voltz::Instruction::LDTRUE: return "ldtrue";
        case voltz::Instruction::LDFALSE: return "ldfalse";
        case voltz::Instruction::LDSEL: return "ldsel";
        case voltz::Instruction::LDCLOS: return "ldclos";
        case voltz::Instruction::LDCLASS: return "ldclass";
    }
    
    printf("%02x\n", (uint32_t) t);
    
}

Instruction::Type voltz::GetInstructionForName(const char* name) {
    if (strcmp(name, "nop") == 0) {
        return Instruction::NOP;
    }
    if (strcmp(name, "bltin") == 0) {
        return Instruction::BLTIN;
    }
    if (strcmp(name, "break") == 0) {
        return Instruction::BREAK;
    }
    if (strcmp(name, "import") == 0) {
        return Instruction::IMPORT;
    }
    if (strcmp(name, "print") == 0) {
        return Instruction::PRINT;
    }
    if (strcmp(name, "msg") == 0) {
        return Instruction::MSG;
    }
    if (strcmp(name, "msgspr") == 0) {
        return Instruction::MSGSPR;
    }
    if (strcmp(name, "ret") == 0) {
        return Instruction::RET;
    }
    if (strcmp(name, "retn") == 0) {
        return Instruction::RETN;
    }
    if (strcmp(name, "pop") == 0) {
        return Instruction::POP;
    }
    if (strcmp(name, "popr") == 0) {
        return Instruction::POPR;
    }
    if (strcmp(name, "popa") == 0) {
        return Instruction::POPA;
    }
    if (strcmp(name, "popar") == 0) {
        return Instruction::POPAR;
    }
    if (strcmp(name, "dup") == 0) {
        return Instruction::DUP;
    }
    if (strcmp(name, "dupr") == 0) {
        return Instruction::DUPR;
    }
    if (strcmp(name, "load") == 0) {
        return Instruction::LOAD;
    }
    if (strcmp(name, "loadr") == 0) {
        return Instruction::LOADR;
    }
    if (strcmp(name, "store") == 0) {
        return Instruction::STORE;
    }
    if (strcmp(name, "storer") == 0) {
        return Instruction::STORER;
    }
    if (strcmp(name, "set") == 0) {
        return Instruction::SET;
    }
    if (strcmp(name, "jmp") == 0) {
        return Instruction::JMP;
    }
    if (strcmp(name, "jmpcnd") == 0) {
        return Instruction::JMPCND;
    }
    if (strcmp(name, "yield") == 0) {
        return Instruction::YIELD;
    }
    
    if (strcmp(name, "ldself") == 0) {
        return Instruction::LDSELF;
    }
    if (strcmp(name, "ldivar") == 0) {
        return Instruction::LDIVAR;
    }
    if (strcmp(name, "stivar") == 0) {
        return Instruction::STIVAR;
    }
    if (strcmp(name, "ldivarc") == 0) {
        return Instruction::LDIVARC;
    }
    
    if (strcmp(name, "ldargc") == 0) {
        return Instruction::LDARGC;
    }
    if (strcmp(name, "ldsz") == 0) {
        return Instruction::LDSZ;
    }
    if (strcmp(name, "ldgbl") == 0) {
        return Instruction::LDGBL;
    }
    
    if (strcmp(name, "ldnil") == 0) {
        return Instruction::LDNIL;
    }
    if (strcmp(name, "ldint") == 0) {
        return Instruction::LDINT;
    }
    if (strcmp(name, "ldflt") == 0) {
        return Instruction::LDFLT;
    }
    if (strcmp(name, "ldchar") == 0) {
        return Instruction::LDCHAR;
    }
    if (strcmp(name, "ldstr") == 0) {
        return Instruction::LDSTR;
    }
    if (strcmp(name, "ldtrue") == 0) {
        return Instruction::LDTRUE;
    }
    if (strcmp(name, "ldfalse") == 0) {
        return Instruction::LDFALSE;
    }
    if (strcmp(name, "ldsel") == 0) {
        return Instruction::LDSEL;
    }
    if (strcmp(name, "ldclos") == 0) {
        return Instruction::LDCLOS;
    }
    if (strcmp(name, "ldclass") == 0) {
        return Instruction::LDCLASS;
    }
    return Instruction::NOP;
}

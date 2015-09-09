// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <stdlib.h>
#include <stdio.h>

void vz_io_init() {
    id objcls = vz_class_get("std::Object");
    id protocolcls = vz_class_get("std::Protocol");
    
    id outputstream = vz_msg_send(protocolcls, "Alloc", 0);
    id name = vz_string_box("std::io::OutputStream");
    id superc = vz_num_box(0);
    outputstream = vz_msg_send(outputstream, "Init::", 2, name, superc);
    id writesel = vz_sel_box(vz_sel_get("Write:"));
    vz_msg_send(outputstream, "AddSelector:", 1, writesel);
    vz_class_register(outputstream->ivars[0].str, outputstream);
    
    vz_msg_send(name, "Release", 0);
    vz_msg_send(superc, "Release", 0);
    vz_msg_send(writesel, "Release", 0);
    
    id charoutputsream = vz_msg_send(protocolcls, "Alloc", 0);
    name = vz_string_box("std::io::CharacterOutputStream");
    superc = vz_num_box(1);
    charoutputsream = vz_msg_send(charoutputsream, "Init::", 2, name, superc);
    charoutputsream->ivars[2].arr[0] = vz_msg_send(outputstream, "Retain", 0);
    id sel = vz_sel_box(vz_sel_get("Init:"));
    vz_msg_send(charoutputsream, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    sel = vz_sel_box(vz_sel_get("Write:"));
    vz_msg_send(charoutputsream, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    sel = vz_sel_box(vz_sel_get("Write::"));
    vz_msg_send(charoutputsream, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    sel = vz_sel_box(vz_sel_get("WriteString:"));
    vz_msg_send(charoutputsream, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    sel = vz_sel_box(vz_sel_get("WriteString::"));
    vz_msg_send(charoutputsream, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    vz_class_register(charoutputsream->ivars[0].str, charoutputsream);
    
    id characterencoder = vz_msg_send(protocolcls, "Alloc", 0);
    name = vz_string_box("std::io::CharacterEncoder");
    superc = vz_num_box(0);
    characterencoder = vz_msg_send(characterencoder, "Init::", 2, name, superc);
    sel = vz_sel_box(vz_sel_get("Encode:"));
    vz_msg_send(characterencoder, "AddSelector:", 1, sel);
    vz_msg_send(sel, "Release", 0);
    vz_class_register(characterencoder->ivars[0].str, characterencoder);
    
    id mthdcls = vz_class_get("std::Method");
    
    name = vz_string_box("std::io::UTF8CharacterEncoder");
    id iname = vz_string_box("std::io::UTF8CharacterEncoder.isa");
    id ivarc = vz_num_box(0);
    id utf8charencoder = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    vz_class_register(utf8charencoder->ivars[1].str, utf8charencoder);
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    id encode = vz_msg_send(mthdcls, "Alloc", 0);
    encode = vz_msg_send(encode, "Init", 0);
    sel = vz_sel_box(vz_sel_get("Encode:"));
    id imp = vz_imp_box(vz_def({
        // Need bytes and arrays implemented
    }));
    
    
    name = vz_string_box("std::io::FileOutputStream");
    iname = vz_string_box("std::io::FileOutputStream.isa");
    ivarc = vz_num_box(1);
    id fileoutputstream = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    fileoutputstream->ivars[3].sarr[0] = vz_sel_get("file");
    vz_msg_send(name, "Release", 0);
    vz_msg_send(iname, "Release", 0);
    vz_msg_send(ivarc, "Release", 0);
    
    vz_class_register(fileoutputstream->ivars[1].str, fileoutputstream);
    
    id writestr = vz_msg_send(mthdcls, "Alloc", 0);
    writestr = vz_msg_send(writestr, "Init", 0);
    sel = vz_sel_box(vz_sel_get("WriteString:"));
    imp = vz_imp_box(vz_def({
        FILE* f = (FILE*) vz_object_getIvar(self, "file");
        const char* str = vz_string_unbox(argv[0]);
        fprintf(f, "%s", str);
        free((void*) str);
        return nil;
    }));
    vz_msg_send(writestr, "SetSel:", 1, sel);
    vz_msg_send(writestr, "SetImp:", 1, imp);
    vz_msg_send(fileoutputstream, "AddMethod:", 1, writestr);
}

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
    
    
    
    id name = vz_string_box("std::io::FileOutputStream");
    id iname = vz_string_box("std::io::FileOutputStream.isa");
    id ivarc = vz_num_box(1);
    id fileoutputstream = vz_msg_send(objcls, "Subclass:::", 3, name, iname, ivarc);
    fileoutputstream->ivars[3].sarr = (SEL*) malloc(sizeof(SEL) * fileoutputstream->ivars[2].num);
    fileoutputstream->ivars[3].sarr[0] = vz_sel_get("file");
    
    vz_class_register(fileoutputstream->ivars[1].str, fileoutputstream);
    
    id mthdcls = vz_class_get("std::Method");
    
    id writestr = vz_msg_send(mthdcls, "Alloc", 0);
    writestr = vz_msg_send(writestr, "Init", 0);
    id sel = vz_sel_box(vz_sel_get("WriteString:"));
    id imp = vz_imp_box(vz_def({
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

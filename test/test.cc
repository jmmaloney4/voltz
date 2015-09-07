// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include <gtest/gtest.h>

void vz_linker_entry(id, id) {
    ::testing::InitGoogleTest(&C_argc, (char**) C_argv);
    int rv = RUN_ALL_TESTS();
    if (rv != 0) {
        abort();
    }
}

TEST(voltz, SelectorIntegrity) {
    
    SEL sel = vz_sel_get("TestSelector::");
    SEL sel2 = vz_sel_get("TestSelector::");
    
    EXPECT_EQ(sel, sel2);
    
    sel = vz_sel_get("AnotherSelector::");
    sel2 = vz_sel_get("AnotherSelector::");
    
    EXPECT_EQ(sel, sel2);
    
    sel = vz_sel_get("_!@#");
    sel2 = vz_sel_get("_!@#");
    
    EXPECT_EQ(sel, sel2);
    
}

TEST(voltz, test) {
    id objcls = vz_class_get("std::Object");
    //id cls = vz_msg_send(objcls, "Subclass::", 0);
}

TEST(voltz, HelloWorld) {
    id fos = vz_class_get("std::io::FileOutputStream");
    id sout = vz_msg_send(fos, "Alloc", 0);
    sout = vz_msg_send(sout, "Init", 0);
    vz_object_setIvar(sout, "file", (id) stdout);
    
    id str = vz_string_box("Hello, World!\n");
    vz_msg_send(sout, "WriteString:", 1, str);
}
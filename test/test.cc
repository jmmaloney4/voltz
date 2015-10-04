// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "runtime/voltz-internal.h"
#include <gtest/gtest.h>

void vz_linker_entry(id, id) {
    ::testing::InitGoogleTest(&C_argc, (char**) C_argv);
    int rv = RUN_ALL_TESTS();
    exit(rv);
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

TEST(voltz, Bool) {
    id t = vz_bool_box(true);
    EXPECT_EQ(true, vz_bool_unbox(t));
    id f = vz_bool_box(false);
    EXPECT_EQ(false, vz_bool_unbox(f));
}

TEST(voltz, HelloWorld) {
    id fos = vz_class_get("Std::IO::FileOutputStream");
    id sout = vz_msg_send(fos, "Alloc", 0);
    sout = vz_msg_send(sout, "Init", 0);
    vz_object_setIvar(sout, "file", (id) stdout);
    
    id str = vz_string_box("Hello, World!\n");
    vz_msg_send(sout, "WriteString:", 1, str);
}

TEST(voltz, RetainRelease) {
    id objcls = vz_class_get("Std::Object");
    id obj = vz_msg_send(objcls, "Alloc", 0);
    obj = vz_msg_send(obj, "Init", 0);
    
    id refs = vz_msg_send(obj, "Refrences", 0);
    id weaks = vz_msg_send(obj, "WeakRefrences", 0);
    EXPECT_EQ(1, vz_num_unbox(refs));
    EXPECT_EQ(0, vz_num_unbox(weaks));
    
    vz_msg_send(refs, "Release", 0);
    vz_msg_send(weaks, "Release", 0);
    
    vz_msg_send(obj, "Retain", 0);
    
    refs = vz_msg_send(obj, "Refrences", 0);
    weaks = vz_msg_send(obj, "WeakRefrences", 0);
    EXPECT_EQ(2, vz_num_unbox(refs));
    EXPECT_EQ(0, vz_num_unbox(weaks));
    
    vz_msg_send(refs, "Release", 0);
    vz_msg_send(weaks, "Release", 0);
    
    vz_msg_send(obj, "Release", 0);

    refs = vz_msg_send(obj, "Refrences", 0);
    weaks = vz_msg_send(obj, "WeakRefrences", 0);
    EXPECT_EQ(1, vz_num_unbox(refs));
    EXPECT_EQ(0, vz_num_unbox(weaks));
    
    vz_msg_send(refs, "Release", 0);
    vz_msg_send(weaks, "Release", 0);

    vz_msg_send(obj, "Release", 0);
    vz_msg_send(objcls, "Release", 0);
}

TEST(voltz, BoolEvalMethod) {
    id objcls = vz_class_get("Std::Object");
    id obj = vz_msg_send(objcls, "Alloc", 0);
    obj = vz_msg_send(obj, "Init", 0);
    
    id tmp0 = vz_msg_send(obj, "Bool", 0);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(nil, "Bool", 0);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj, "!", 0);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    // Weird behavior, but as of now it is correct.
    tmp0 = vz_msg_send(nil, "!", 0);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    vz_msg_send(objcls, "Release", 0);
    vz_msg_send(obj, "Release", 0);
}

TEST(voltz, ComparisonOperators) {
    id objcls = vz_class_get("Std::Object");
    
    id obj1 = vz_msg_send(objcls, "Alloc", 0);
    obj1 = vz_msg_send(obj1, "Init", 0);
    id obj2 = vz_msg_send(objcls, "Alloc", 0);
    obj2 = vz_msg_send(obj2, "Init", 0);
    
    // Tests default object behavior, not nessisarily true for all classes.
    
    id tmp0 = vz_msg_send(obj1, "==:", 1, obj1);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, "!=:", 1, obj1);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    
    tmp0 = vz_msg_send(obj1, "==:", 1, obj2);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, "!=:", 1, obj2);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);

    
    tmp0 = vz_msg_send(obj1, "===:", 1, obj1);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, "===:", 1, obj2);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    
    tmp0 = vz_msg_send(obj1, "!==:", 1, obj1);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, "!==:", 1, obj2);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);

    
    tmp0 = vz_msg_send(obj1, "<:", 1, obj1);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, "<:", 1, obj2);
    EXPECT_EQ((obj1 < obj2), vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    
    tmp0 = vz_msg_send(obj1, ">:", 1, obj1);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, ">:", 1, obj2);
    EXPECT_EQ((obj1 > obj2), vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    
    tmp0 = vz_msg_send(obj1, "<=:", 1, obj1);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, "<=:", 1, obj2);
    EXPECT_EQ((obj1 <= obj2), vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    
    tmp0 = vz_msg_send(obj1, ">=:", 1, obj1);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(obj1, ">=:", 1, obj2);
    EXPECT_EQ((obj1 >= obj2), vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
}

TEST(voltz, BoolOperators) {
    id t = vz_bool_box(true);
    id f = vz_bool_box(false);

    id tmp0 = vz_msg_send(t, "!", 0);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "!", 0);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    
    tmp0 = vz_msg_send(t, "&&:", 1, t);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(t, "&&:", 1, f);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "&&:", 1, t);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "&&:", 1, f);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);

    
    tmp0 = vz_msg_send(t, "||:", 1, t);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(t, "||:", 1, f);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "||:", 1, t);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "||:", 1, f);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    
    tmp0 = vz_msg_send(t, "^^:", 1, t);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(t, "^^:", 1, f);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "^^:", 1, t);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "^^:", 1, f);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);

    
    tmp0 = vz_msg_send(t, "==:", 1, t);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(t, "!=:", 1, t);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "==:", 1, f);
    EXPECT_EQ(true, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
    
    tmp0 = vz_msg_send(f, "!=:", 1, f);
    EXPECT_EQ(false, vz_bool_unbox(tmp0));
    vz_msg_send(tmp0, "Release", 0);
}

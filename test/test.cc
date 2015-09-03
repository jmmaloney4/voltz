// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include <gtest/gtest.h>

using namespace voltz;

void voltz::VoltzLinkerEntry(Int argc, Array argv) {
    ::testing::InitGoogleTest(&Cargc, (char**) Cargv);
    int rv = RUN_ALL_TESTS();
    if (rv != 0) {
        abort();
    }
}

TEST(voltz, BoxInt) {
    Int orv = BoxInt(1234);
    int64_t irv = UnboxInt(orv);

    Selector release = GetSelector("Release():std::Void");
    SendMsg((Object) orv, release, 0);
    SendMsg((Object) release, release, 0);
    
    EXPECT_EQ(1234, irv);
}


TEST(voltz, BoxFloat) {
    Float orv = BoxFloat(12341.123412341234);
    double drv = UnboxFloat(orv);

    EXPECT_EQ(12341.123412341234, drv);
    
    Selector release = GetSelector("Release():std::Void");
    SendMsg((Object) orv, release, 0);
    SendMsg((Object) release, release, 0);
}


TEST(voltz, BoxChar) {
    Char orv = BoxChar(U'℃');
    int64_t crv = UnboxChar(orv);
    
    EXPECT_EQ(U'℃', crv);
    
    Selector release = GetSelector("Release():std::Void");
    SendMsg((Object) orv, release, 0);
    SendMsg((Object) release, release, 0);
}

TEST(voltz, BoxString) {
    const char* str = "Hello, World!\n";
    String orv = BoxString(str);
    char* srv = UnboxString(orv);

    Selector release = GetSelector("Release():std::Void");
    SendMsg((Object) orv, release, 0);
    SendMsg((Object) release, release, 0);
    
    EXPECT_STREQ(str, srv);
}

TEST(voltz, BoxArray) {
    Object* arr = (Object*) malloc(sizeof(Object));
    arr[0] = (Object) nil;
    
    
    Array orv = BoxArray(1, arr);
    
    Selector arrop = GetSelector("[](:std::Int):T");
    
    Int index = BoxInt(0);
    
    Object obj = SendMsg((Object) orv, arrop, 1, index);
    
    EXPECT_EQ(arr[0], obj);
    
    Selector release = GetSelector("Release():std::Void");
    SendMsg((Object) orv, release, 0);
    SendMsg((Object) release, release, 0);
}

TEST(voltz, GetSelector) {
    
    const char* str = "SomeSelector(name:count:args:string:release:)";
    Selector sel1 = GetSelector(str);
    
    Selector sel2 = GetSelector(str);
    
    Selector release = GetSelector("Release():std::Void");
    SendMsg((Object) sel1, release, 0);
    SendMsg((Object) sel2, release, 0);
    SendMsg((Object) release, release, 0);
    
    EXPECT_EQ(sel1, sel2);
}

TEST(voltz, Registry) {
    Selector alloc = GetSelector("Allocate():std::Object");
    Selector init = GetSelector("Initialize():std::Object");
    Selector release = GetSelector("Release():std::Void");
    Class objectClass = (Class) GetRegisteredObject("std::Object");
    
    Object obj = SendMsg((Object) objectClass, alloc, 0);
    obj = SendMsg(obj, init, 0);
    
    RegisterObject(obj, "SomeObject");
    
    Object o = GetRegisteredObject("SomeObject");
    
    EXPECT_EQ(obj, o);
    
    SendMsg((Object) alloc, release, 0);
    SendMsg((Object) init, release, 0);
    SendMsg( obj, release, 0);
    SendMsg(o, release, 0);
    SendMsg((Object) release, release, 0);
    
}

TEST(voltz, HelloWorld) {
    Object std_out = GetRegisteredObject("std::io::StdOut");
    String helloworld = BoxString("Hello, World!\n");
    Selector write = GetSelector("Write(:)");
    SendMsg(std_out, write, 1, helloworld);
    
    Selector release = GetSelector("Release():std::Void");
    SendMsg(std_out, release, 0);
    SendMsg((Object) helloworld, release, 0);
    SendMsg((Object) write, release, 0);
    SendMsg((Object) release, release, 0);
}

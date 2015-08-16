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

    Selector release = GetSelector("Release()");
    SendMsg((Object) orv, release, 0);
    SendMsg((Object) release, release, 0);
    
    EXPECT_EQ(1234, irv);
}

/*
TEST(voltz, BoxFloat) {
    Float orv = BoxFloat(12341.123412341234);
    double drv = UnboxFloat(orv);

    EXPECT_EQ(12341.123412341234, drv);
}
*/

TEST(voltz, BoxString) {
    const char* str = "Hello, World!\n";
    String orv = BoxString(str);
    char* srv = UnboxString(orv);

    Selector release = GetSelector("Release()");
    SendMsg((Object) orv, release, 0);
    SendMsg((Object) release, release, 0);
    
    EXPECT_STREQ(str, srv);
}

TEST(voltz, GetSelector) {
    
    const char* str = "SomeSelector(name:count:args:string:release:)";
    Selector sel1 = GetSelector(str);
    
    Selector sel2 = GetSelector(str);
    
    Selector release = GetSelector("Release()");
    SendMsg((Object) sel1, release, 0);
    SendMsg((Object) sel2, release, 0);
    SendMsg((Object) release, release, 0);
    
    EXPECT_EQ(sel1, sel2);
}

TEST(voltz, HelloWorld) {
    Object std_out = GetRegisteredObject("std::io::stdout");
    String helloworld = BoxString("Hello, World!\n");
    Selector write = GetSelector("Write(:)");
    SendMsg(std_out, write, 1, helloworld);
    
    Selector release = GetSelector("Release()");
    SendMsg(std_out, release, 0);
    SendMsg((Object) helloworld, release, 0);
    SendMsg((Object) write, release, 0);
    SendMsg((Object) release, release, 0);
}

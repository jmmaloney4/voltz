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

    Release((Object) orv);
    
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

    Release((Object) orv);
    
    EXPECT_STREQ(str, srv);
}

TEST(voltz, GetSelector) {
    
    String str = BoxString("SomeSelector(name:count:args:string:release:)");
    Selector sel1 = GetSelector(str);
    
    Selector sel2 = GetSelector(str);
    
    EXPECT_EQ(sel1, sel2);
}



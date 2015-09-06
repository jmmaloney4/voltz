// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include <voltz.h>
#include <gtest/gtest.h>

TEST(voltz, getsel) {
    
    SEL sel = vz_getSel("TestSelector(::)");
    SEL sel2 = vz_getSel("TestSelector(::)");
    
    EXPECT_EQ(sel, sel2);
    
}

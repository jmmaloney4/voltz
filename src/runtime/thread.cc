// Copyright (C) 2015 Jack Maloney. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.

#include "voltz-internal.h"
#include <thread>

using namespace voltz;
using namespace voltz::selectors;
using namespace voltz::classes;

id CreateThread(IMP fn) { id thrd = SendMsg(Thread, New, 0); }

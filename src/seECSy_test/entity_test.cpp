#include "stdafx.h"

#include "gtest\gtest.h"
#include "sexy.h"

using namespace tyleo;

TEST(Entity, ConstructorTest)
{
    EXPECT_NO_THROW(Entity{});
}

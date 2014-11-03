#include "stdafx.h"

#include "gtest\gtest.h"
#include "sexy.h"

#include "test_components.h"
#include "test_systems.h"

using namespace sexy_test;
using namespace tyleo;

TEST(System, ConstructorTest0)
{
    using namespace sys0;

    EXPECT_NO_THROW(TestSystem testSystem{});
}

TEST(System, ConstructorTest1)
{
    using namespace sys1;

    EXPECT_NO_THROW(TestSystem testSystem{});
}

TEST(System, ConstructorTest2)
{
    using namespace sys2;

    EXPECT_NO_THROW(TestSystem testSystem{});
}

TEST(System, CreateEntityTest0)
{
    using namespace sys0;

    TestSystem testSystem{};
    Entity entity0{ testSystem.CreateEntity() };
    Entity entity1{ testSystem.CreateEntity() };

    EXPECT_EQ(entity0, 1);
    EXPECT_EQ(entity1, 2);
}

TEST(System, UpdateTest0)
{
    using namespace sys0;

    TestSystem testSystem{};

    EXPECT_NO_THROW(testSystem.Update());
}
TEST(System, UpdateTest1)
{
    using namespace sys1;

    TestSystem testSystem{};

    EXPECT_NO_THROW(testSystem.Update());
}

TEST(System, UpdateTest2)
{
    using namespace sys2;

    TestSystem testSystem{};

    EXPECT_NO_THROW(testSystem.Update());
}

TEST(System, AddEntityTest0)
{
    using namespace sys0;

    TestSystem testSystem{};
    Entity entity0{ testSystem.CreateEntity() };
    Entity entity1{ testSystem.CreateEntity() };

    EXPECT_EQ(entity0, 1);
    EXPECT_EQ(entity1, 2);
}

TEST(System, AddEntityTest1)
{
    using namespace sys1;

    TestSystem testSystem{};
    Entity entity0{ testSystem.CreateEntity() };
    Entity entity1{ testSystem.CreateEntity() };

    EXPECT_EQ(entity0, 1);
    EXPECT_EQ(entity1, 2);
}

TEST(System, AddEntityTest2)
{
    using namespace sys2;

    TestSystem testSystem{};
    Entity entity0{ testSystem.CreateEntity() };
    Entity entity1{ testSystem.CreateEntity() };

    EXPECT_EQ(entity0, 1);
    EXPECT_EQ(entity1, 2);
}

TEST(System, AddComponentToEntity0)
{
    using namespace sys1;

    TestSystem testSystem{};

    Entity entity0{ testSystem.CreateEntity() };
    TestComponent0Ptr testComponent{ testSystem.AddComponentToEntity<TestComponent0>(entity0) };
}

TEST(System, AddComponentToEntity1)
{
    using namespace sys2;

    int constructorParam0{ 0 };

    TestSystem testSystem{};

    Entity entity0{ testSystem.CreateEntity() };
    TestComponent0Ptr testComponent0{ testSystem.AddComponentToEntity<TestComponent0>(entity0) };
    TestComponent1Ptr testComponent1{ testSystem.AddComponentToEntity<TestComponent1>(entity0, constructorParam0) };
}

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

    int constructorParam0{ 0 };

    TestSystem testSystem{};
    Entity entity{ testSystem.CreateEntity() };
    TestComponent1Ptr & component{ testSystem.AddComponentToEntity<TestComponent1>(entity, constructorParam0) };

    EXPECT_NO_THROW(testSystem.Update());
    EXPECT_NO_THROW(testSystem.Update());

    EXPECT_EQ(1, component->GetData());
}

TEST(System, CreateEntityTest0)
{
    using namespace sys0;

    TestSystem testSystem{};
    Entity entity0{ testSystem.CreateEntity() };
    Entity entity1{ testSystem.CreateEntity() };

    EXPECT_EQ(entity0, 1);
    EXPECT_EQ(entity1, 2);

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 2);

    EXPECT_NO_THROW(testSystem.Update());

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 2);
}

TEST(System, CreateEntityTest1)
{
    using namespace sys1;

    TestSystem testSystem{};
    Entity entity0{ testSystem.CreateEntity() };
    Entity entity1{ testSystem.CreateEntity() };

    EXPECT_EQ(entity0, 1);
    EXPECT_EQ(entity1, 2);

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 2);

    EXPECT_NO_THROW(testSystem.Update());

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 2);
}

TEST(System, CreateEntityTest2)
{
    using namespace sys2;

    TestSystem testSystem{};
    Entity entity0{ testSystem.CreateEntity() };
    Entity entity1{ testSystem.CreateEntity() };

    EXPECT_EQ(entity0, 1);
    EXPECT_EQ(entity1, 2);

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 2);

    EXPECT_NO_THROW(testSystem.Update());

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 2);
}

TEST(System, AddComponentToEntity0)
{
    using namespace sys1;

    TestSystem testSystem{};

    Entity entity0{ testSystem.CreateEntity() };
    TestComponent0Ptr & testComponent0{ testSystem.AddComponentToEntity<TestComponent0>(entity0) };

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);

    EXPECT_ANY_THROW(testSystem.GetComponentFromEntity<TestComponent0>(entity0));

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);

    TestComponent0Ptr & testComponent1{ testSystem.GetComponentFromEntity<TestComponent0>(entity0) };

    EXPECT_EQ(testComponent0, testComponent1);
}

TEST(System, AddComponentToEntity1)
{
    using namespace sys2;

    int constructorParam0{ 0 };

    TestSystem testSystem{};

    Entity entity0{ testSystem.CreateEntity() };
    TestComponent0Ptr & testComponent00{ testSystem.AddComponentToEntity<TestComponent0>(entity0) };
    TestComponent1Ptr & testComponent10{ testSystem.AddComponentToEntity<TestComponent1>(entity0, constructorParam0) };

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 2);

    EXPECT_ANY_THROW(testSystem.GetComponentFromEntity<TestComponent0>(entity0));
    EXPECT_ANY_THROW(testSystem.GetComponentFromEntity<TestComponent1>(entity0));

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfEntities(), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 2);

    TestComponent0Ptr & testComponent01{ testSystem.GetComponentFromEntity<TestComponent0>(entity0) };
    TestComponent1Ptr & testComponent11{ testSystem.GetComponentFromEntity<TestComponent1>(entity0) };

    EXPECT_EQ(testComponent00, testComponent01);
    EXPECT_EQ(testComponent10, testComponent11);
}

TEST(System, RemoveComponentFromEntity0)
{
    using namespace sys1;

    TestSystem testSystem{};

    Entity entity0{ testSystem.CreateEntity() };
    testSystem.AddComponentToEntity<TestComponent0>(entity0);

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 0);

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 1);

    testSystem.RemoveComponentFromEntity<TestComponent0>(entity0);

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 0);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 1);

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 0);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 0);
}

TEST(System, RemoveComponentFromEntity1)
{
    using namespace sys2;

    int constructorParam0{ 0 };

    TestSystem testSystem{};

    Entity entity0{ testSystem.CreateEntity() };
    testSystem.AddComponentToEntity<TestComponent0>(entity0);
    testSystem.AddComponentToEntity<TestComponent1>(entity0, constructorParam0);

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 2);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 0);

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 2);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 2);

    testSystem.RemoveComponentFromEntity<TestComponent0>(entity0);

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 2);

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 1);

    testSystem.RemoveComponentFromEntity<TestComponent1>(entity0);

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 0);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 1);

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 0);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 0);
}

TEST(System, DestroyEntityTest0)
{
    using namespace sys1;

    TestSystem testSystem{};

    Entity entity0{ testSystem.CreateEntity() };
    testSystem.AddComponentToEntity<TestComponent0>(entity0);

    testSystem.Update();

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 1);

    testSystem.DestroyEntity(entity0);

    EXPECT_EQ(testSystem.GetNumberOfComponents(entity0), 1);
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 1);

    testSystem.Update();

    EXPECT_ANY_THROW(testSystem.GetNumberOfComponents(entity0));
    EXPECT_EQ(testSystem.GetNumberOfComponents(), 0);
}

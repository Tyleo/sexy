#include "stdafx.h"

#include <cstdint>

#include "gtest/gtest.h"
#include "sexy/sexy.h"

#include "components.h"
#include "events.h"
#include "system.h"

using namespace sexy;
using namespace sexy_test;

TEST(SystemTest, ConstructorTest0)
{
    ASSERT_NO_THROW(TestSystem0{});
}

TEST(SystemTest, CreateEntityTest0)
{
    TestSystem0 testSystem{};

    const auto expected = 1;
    const auto actual = testSystem.CreateEntity();

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, AddComponentTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity = testSystem.CreateEntity();

    ASSERT_NO_THROW(testSystem.AddComponent<CTestComponent0>(entity));
}

TEST(SystemTest, RemoveComponentTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity = testSystem.CreateEntity();

    testSystem.AddComponent<CTestComponent0>(entity);

    ASSERT_NO_THROW(testSystem.RemoveComponent<CTestComponent0>(entity));
}

TEST(SystemTest, GetComponentTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity = testSystem.CreateEntity();

    auto expected = testSystem.AddComponent<CTestComponent0>(entity);

    testSystem.Update();

    auto actual = testSystem.GetComponent<CTestComponent0>(entity);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, GetComponentsTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity0 = testSystem.CreateEntity();
    const auto entity1 = testSystem.CreateEntity();

    testSystem.AddComponent<CTestComponent0>(entity0);
    testSystem.AddComponent<CTestComponent0>(entity1);

    testSystem.Update();

    auto iterable = testSystem.GetComponents<CTestComponent0>();

    const auto expected = 2;
    auto actual = 0;

    for (auto it : iterable)
    {
        ++actual;
    }

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, UpdateTest0)
{
    TestSystem1 testSystem{};

    ASSERT_NO_THROW(testSystem.Update());
}

TEST(SystemTest, PreSendAllTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);
    TYPEDEF_C(TestComponent1, BasicEntity);

    TestSystem1 testSystem{};

    const auto expected = 2;
    int actual = 0;

    testSystem.SendAll<PreTestEvent>(&actual);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, SendAllTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);
    TYPEDEF_C(TestComponent1, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity0 = testSystem.CreateEntity();
    const auto entity1 = testSystem.CreateEntity();

    auto & testComponent0 = testSystem.AddComponent<CTestComponent0>(entity0);
    auto & testComponent1 = testSystem.AddComponent<CTestComponent1>(entity1);

    testSystem.Update();

    const auto expected = 2;
    int actual = 0;

    testSystem.SendAll<TestEvent>(&actual);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, PostSendAllTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);
    TYPEDEF_C(TestComponent1, BasicEntity);

    TestSystem1 testSystem{};

    testSystem.Update();

    const auto expected = 2;
    int actual = 0;

    testSystem.SendAll<PostTestEvent>(&actual);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, SendAllTargetTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity0 = testSystem.CreateEntity();

    auto & testComponent0 = testSystem.AddComponent<CTestComponent0>(entity0);

    testSystem.Update();

    const auto expected = 1;
    int actual = 0;

    testSystem.SendAllTarget<TestEvent>(entity0, &actual);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, PreSendTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto expected = 1;
    int actual = 0;

    testSystem.Send<PreTestEvent, CTestComponent0>(&actual);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, SendTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity0 = testSystem.CreateEntity();

    auto & testComponent0 = testSystem.AddComponent<CTestComponent0>(entity0);

    testSystem.Update();

    const auto expected = 1;
    int actual = 0;

    testSystem.Send<TestEvent, CTestComponent0>(&actual);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, SendTargetTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto entity0 = testSystem.CreateEntity();

    auto & testComponent0 = testSystem.AddComponent<CTestComponent0>(entity0);

    testSystem.Update();

    const auto expected = 1;
    int actual = 0;

    testSystem.SendTarget<TestEvent, CTestComponent0>(entity0, &actual);

    ASSERT_EQ(expected, actual);
}

TEST(SystemTest, PostSendTest0)
{
    TYPEDEF_C(TestComponent0, BasicEntity);

    TestSystem1 testSystem{};

    const auto expected = 1;
    int actual = 0;

    testSystem.Send<PostTestEvent, CTestComponent0>(&actual);

    ASSERT_EQ(expected, actual);
}

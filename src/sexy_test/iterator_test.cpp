#include "stdafx.h"

#include <vector>
#include <unordered_map>

#include "gtest/gtest.h"
#include "sexy/sexy.h"

using namespace sexy;
using namespace std;

TEST(IteratorTest, ConstructorTest)
{
    vector<int> testVector{ 1, 2, 3 };

    auto emptyLambda = [](int & value) -> int &{ return value; };
    Iterable<int, std::vector<int>> it(testVector);
    auto x = it.begin();

    auto z = *x;
}

TEST(IteratorTest, ConstructorTest1)
{
    unordered_map<int, int> testMap;
    testMap.emplace(std::make_pair(1, 1));
    testMap.emplace(std::make_pair(2, 2));
    testMap.emplace(std::make_pair(3, 3));

    auto emptyLambda = [](std::pair<const int, int> &value) -> const int &{ return value.first; };
    Iterable<const int, std::unordered_map<int, int>, decltype(emptyLambda)> it(testMap);
    auto x = it.begin();

    auto z = *x;
    ++z;
}

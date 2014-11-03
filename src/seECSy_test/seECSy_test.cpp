// seECSy_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "gtest\gtest.h"

using namespace testing;

int main(int argc, char ** argv)
{
    InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    getchar();

    return EXIT_SUCCESS;
}

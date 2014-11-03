#pragma once

#include "sexy.h"

#include "test_components.h"

namespace sexy_test
{
    namespace sys0
    {
        REGISTER_SYSTEM_BEGIN(TestSystemi);
        REGISTER_SYSTEM_END();

        BEGIN_SYSTEM(TestSystem)
        END_SYSTEM();
    }

    namespace sys1
    {
        REGISTER_SYSTEM_BEGIN(TestSystem);
            REGISTER_COMPONENT(TestComponent0);
        REGISTER_SYSTEM_END();

        BEGIN_SYSTEM(TestSystem, TestComponent0)
        END_SYSTEM();
    }

    namespace sys2
    {
        REGISTER_SYSTEM_BEGIN(TestSystem);
            REGISTER_COMPONENT(TestComponent0);
            REGISTER_COMPONENT(TestComponent1);
        REGISTER_SYSTEM_END();

        BEGIN_SYSTEM(TestSystem, TestComponent0, TestComponent1)
        END_SYSTEM();
    }
}

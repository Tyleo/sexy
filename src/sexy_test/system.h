#pragma once

#include "sexy/sexy.h"

#include "component.h"

namespace sexy_test
{
    class TestSystem0 final : public sexy::System<sexy::BasicSystemRegister<TestSystem0>>
    {

    };

    class TestSystem1 final : public sexy::System<sexy::BasicSystemRegister<TestSystem1>,
                                                  sexy::BasicComponentRegister<TestComponent0>,
                                                  sexy::BasicComponentRegister<TestComponent1>>
    {
    private:
        using Base = sexy::System<sexy::BasicSystemRegister<TestSystem1>,
                                  sexy::BasicComponentRegister<TestComponent0>,
                                  sexy::BasicComponentRegister<TestComponent1>>;

    public:
        void FlushAddBuffers()
        {
            Base::FlushAddBuffers();
        }

        void FlushRemoveBuffers()
        {
            Base::FlushRemoveBuffers();
        }
    };
}

#pragma once

#include <type_traits>

#include "sexy/sexy.h"

#include "events.h"

namespace sexy_test
{
    template <typename TSystem>
    class TestComponent0 final : public sexy::Component<TSystem>
    {
        COMPONENT_INTERNALS;
    private:
        static void Pre(PreTestEvent, int * const & data)
        {
            ++*data;
        }

        void On(TestEvent, int * const & data)
        {
            ++*data;
        }

        static void Post(PostTestEvent, int * const & data)
        {
            ++*data;
        }

    public:
        TestComponent0(Entity ownerEntity) : sexy::Component<TSystem>(ownerEntity)
        { }
    };

    template <typename TSystem>
    class TestComponent1 final : public sexy::Component<TSystem>
    {
        COMPONENT_INTERNALS;
    private:
        static void Pre(PreTestEvent, int * const & data)
        {
            ++*data;
        }

        void On(TestEvent, int * const & data)
        {
            ++*data;
        }

        static void Post(PostTestEvent, int * const & data)
        {
            ++*data;
        }

    public:
        TestComponent1(Entity ownerEntity) : sexy::Component<TSystem>(ownerEntity)
        { }
    };
}

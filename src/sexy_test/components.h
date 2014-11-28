#pragma once

#include <type_traits>

#include "sexy/sexy.h"

#include "events.h"

namespace sexy_test
{
    template <typename TEntity>
    class TestComponent0 final : public sexy::Component<TEntity>
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
        TestComponent0(TEntity ownerEntity) : sexy::Component<TEntity>(ownerEntity)
        { }
    };

    template <typename TEntity>
    class TestComponent1 final : public sexy::Component<TEntity>
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
        TestComponent1(TEntity ownerEntity) : sexy::Component<TEntity>(ownerEntity)
        { }
    };
}

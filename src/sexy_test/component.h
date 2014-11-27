#pragma once

#include "sexy/sexy.h"

#include "event.h"

namespace sexy_test
{
    template <typename TEntity>
    class TestComponent0 final : public sexy::Component<TEntity>
    {
        COMPONENT_INTERNALS;
    public:
        template <typename TSystem>
        void Start(TSystem & system)
        {

        }

        template <>
        static void Pre<PreTestEvent>(int * const & data)
        {
            ++*data;
        }

        template <>
        void On<TestEvent>(int * const & data)
        {
            ++*data;
        }

        template <>
        static void Post<PostTestEvent>(int * const & data)
        {
            ++*data;
        }

        TestComponent0(TEntity ownerEntity) : sexy::Component<TEntity>(ownerEntity)
        { }
    };

    template <typename TEntity>
    class TestComponent1 final : public sexy::Component<TEntity>
    {
        COMPONENT_INTERNALS;
    public:
        template <typename TSystem>
        void Start(TSystem & system)
        {

        }

        template <>
        static void Pre<PreTestEvent>(int * const & data)
        {
            ++*data;
        }

        template <>
        void On<TestEvent>(int * const & data)
        {
            ++*data;
        }

        template <>
        static void Post<PostTestEvent>(int * const & data)
        {
            ++*data;
        }

        TestComponent1(TEntity ownerEntity) : sexy::Component<TEntity>(ownerEntity)
        { }
    };
}

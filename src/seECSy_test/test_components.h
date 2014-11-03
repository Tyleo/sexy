#pragma once

#include "sexy.h"

namespace sexy_test
{
    BEGIN_COMPONENT(TestComponent0)
    END_COMPONENT();

    BEGIN_COMPONENT(TestComponent1)
    private:
        int _data;

    public:
        int GetData()
        {
            return _data;
        }

        void Update()
        {
            ++_data;
        }

        void Start(int data)
        {
            _data = data;
        }

        TestComponent1(TSystem & ownerSystem, tyleo::Entity ownerEntity, int data) : tyleo::Component<TSystem>(ownerSystem, ownerEntity),
                                                                                     _data{ data }
        {}
    END_COMPONENT();
}

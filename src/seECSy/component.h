#pragma once

#include <cstdint>
#include <memory>

#include "entity.h"

namespace tyleo
{
    using ComponentTypeId = uint_fast16_t;

    template <typename TSystem>
    class Component
    {
    private:
        TSystem & _ownerSystem;
        Entity _ownerEntity;

    protected:
        TSystem & GetOwnerSystem()
        {
            return _ownerSystem;
        }

    public:
        Entity GetOwnerEntity()
        {
            return _ownerEntity;
        }

        // CRTP Method
        void Update() {}

        // CRTP Method
        template <typename ... TArgs>
        void Start(TArgs ... args) {}

        // CRTP Method
        void End() {}

        Component() = default;

        Component(TSystem & ownerSystem, Entity ownerEntity) : _ownerSystem{ ownerSystem },
                                                               _ownerEntity{ ownerEntity }
        {}
    };

    template <typename TComponent>
    using ComponentPtr = std::shared_ptr<TComponent>;

#define BEGIN_COMPONENT(COMPONENT_NAME) \
    template <typename TSystem> \
    class COMPONENT_NAME##Template : public tyleo::Component<TSystem> \
        { \
    public: \
        COMPONENT_NAME##Template() = default; \
         \
        COMPONENT_NAME##Template(TSystem & ownerSystem, tyleo::Entity ownerEntity) : tyleo::Component<TSystem>(ownerSystem, ownerEntity) \
            {} \
         \
    private: \
        

#define END_COMPONENT() \
    }
}

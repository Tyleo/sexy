#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "component.h"
#include "entity.h"
#include "system_impl.h"

namespace tyleo
{
    template <typename TSystem, typename ... TComponents>
    class System : private impl::SystemImpl<TSystem, TComponents ...>
    {
    private:
        using EntityToComponentTypeMap = std::unordered_map<Entity, std::unordered_set<ComponentTypeId>>;
        using ComponentsToRemoveList = std::vector<Entity>;
        using ComponentsToRemoveListPtr = std::shared_ptr<ComponentsToRemoveList>;
        using MasterComponentsToRemoveMap = std::unordered_map<ComponentTypeId, ComponentsToRemoveListPtr>;

        EntityToComponentTypeMap _entityToComponentTypeMap;
        MasterComponentsToRemoveMap _masterComponentsToRemoveMap;

        std::vector<Entity> _entitiesToRemove;

        std::vector<Entity> _deadEntities;
        Entity _entityCounter;

        template <typename TComponentToGetListFrom>
        ComponentsToRemoveListPtr GetComponentsToRemoveListPtr()
        {
            return impl::SystemImpl<TSystem, TComponents ...>::GetComponentsToRemoveListPtr<TComponentToGetListFrom>();
        }

        void AddToMasterRemoveMap() { }

        template <typename TComponent, typename ... TComponentsInternal>
        void AddToMasterRemoveMap()
        {
            _masterComponentsToRemoveMap.emplace(make_pair(GetComponentTypeId<TComponent>(), GetComponentsToRemoveListPtr<TComponent>()));
        }

        void RemoveEntities()
        {
            for (auto entity : _entitiesToRemove)
            {
                _deadEntities.emplace_back(entity);

                for (auto componentTypeId : _entityToComponentTypeMap.at(entity))
                {
                    _masterComponentsToRemoveMap.at(componentTypeId)->emplace_back(entity);
                }
            }

            _entitiesToRemove.clear();
        }

        void AddComponents()
        {
            impl::SystemImpl<TSystem, TComponents ...>::AddComponents();
        }

        void RemoveComponents()
        {
            impl::SystemImpl<TSystem, TComponents ...>::RemoveComponents();
        }

    public:
        void Update()
        {
            RemoveEntities();
            RemoveComponents();

            impl::SystemImpl<TSystem, TComponents ...>::Update();

            AddComponents();
        }

        Entity CreateEntity()
        {
            Entity returnValue;

            if (_deadEntities.empty())
            {
                returnValue = _entityCounter;
                ++_entityCounter;
            }
            else
            {
                auto deadEntityIt = --_deadEntities.end();
                returnValue = *deadEntityIt;
                _deadEntities.erase(deadEntityIt);
            }

            _entityToComponentTypeMap.emplace(std::make_pair(returnValue, std::unordered_set<ComponentTypeId>{}));
            return returnValue;
        }

        void DestroyEntity(Entity entity)
        {
            _entitiesToRemove.emplace_back(entity);
        }

        template <typename TComponent>
        TComponent & GetComponentFromEntity(Entity entity)
        {
            return *static_cast<TComponent *>(impl::SystemImpl<TComponents ...>::GetComponentFromEntity<TComponent>(entity).get());
        }

        template <typename TComponent, typename ... TArgs>
        ComponentPtr<TComponent> AddComponentToEntity(Entity entity, TArgs & ... args)
        {
            ComponentPtr<TComponent> componentPtr{ impl::SystemImpl<TSystem, TComponents ...>::AddComponentToEntity<TComponent>(entity) };
            componentPtr->Start(args ...);
            return componentPtr;
        }

        template <typename TComponent>
        void RemoveComponentFromEntity(Entity entity)
        {
            impl::SystemImpl<TSystem, TComponents ...>::RemoveComponentFromEntity<TComponent>(entity);
        }

        System() : impl::SystemImpl<TSystem, TComponents ...>(),
                   _masterComponentsToRemoveMap(),
                   _entityToComponentTypeMap(),
                   _entitiesToRemove(),
                   _deadEntities(0),
                   _entityCounter(1)
        {}
    };

#define REGISTER_SYSTEM_BEGIN(SYSTEM_NAME) \
    class SYSTEM_NAME; \
    namespace \
        { \
        using RegisteredSystem = SYSTEM_NAME; \
        }

#define REGISTER_COMPONENT(COMPONENT_NAME) \
    using COMPONENT_NAME = COMPONENT_NAME##Template<RegisteredSystem>; \
    using COMPONENT_NAME##Ptr = tyleo::ComponentPtr<COMPONENT_NAME>;

#define REGISTER_SYSTEM_END()


#define BEGIN_SYSTEM(SYSTEM_NAME, ...) \
    class SYSTEM_NAME : public tyleo::System<SYSTEM_NAME, ##__VA_ARGS__> \
    {

#define END_SYSTEM() \
    }
}
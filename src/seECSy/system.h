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

        void AddComponentRemoveListToMasterRemoveMap()
        {
            impl::SystemImpl<TSystem, TComponents ...>::AddComponentRemoveListToMasterRemoveMap(_masterComponentsToRemoveMap);
        }

        template <typename TComponent, typename ... TComponentsInternal>
        void AddToMasterRemoveMap()
        {
            _masterComponentsToRemoveMap.emplace(make_pair(GetComponentTypeId<TComponent>(), GetComponentsToRemoveListPtr<TComponent>()));
        }

        void RemoveEntities()
        {
            for (auto entity : _entitiesToRemove)
            {
                for (auto componentTypeId : _entityToComponentTypeMap.at(entity))
                {
                    _masterComponentsToRemoveMap.at(componentTypeId)->emplace_back(entity);
                }

                _entityToComponentTypeMap.erase(entity);
                _deadEntities.emplace_back(entity);
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

        Entity GetNumberOfEntities()
        {
            return _entityToComponentTypeMap.size();
        }

        size_t GetNumberOfComponents()
        {
            return impl::SystemImpl<TSystem, TComponents ...>::GetNumberOfComponents();
        }

        ComponentTypeId GetNumberOfComponents(Entity entity)
        {
            return _entityToComponentTypeMap.at(entity).size();
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
        ComponentTypeId GetComponentTypeId()
        {
            return impl::SystemImpl<TSystem, TComponents ...>::GetComponentTypeId<TComponent>();
        }

        template <typename TComponent>
        ComponentPtr<TComponent> GetComponentFromEntity(Entity entity)
        {
            return impl::SystemImpl<TSystem, TComponents ...>::GetComponentFromEntity<TComponent>(entity);
        }

        template <typename TComponent, typename ... TArgs>
        ComponentPtr<TComponent> AddComponentToEntity(Entity entity, TArgs & ... args)
        {
            auto componentPtr = std::make_shared<TComponent>(*static_cast<TSystem *>(this), entity, args ...);
            impl::SystemImpl<TSystem, TComponents ...>::AddComponentToEntity<TComponent>(componentPtr, entity);
            _entityToComponentTypeMap.at(entity).emplace(GetComponentTypeId<TComponent>());
            return componentPtr;
        }

        template <typename TComponent>
        void RemoveComponentFromEntity(Entity entity)
        {
            impl::SystemImpl<TSystem, TComponents ...>::RemoveComponentFromEntity<TComponent>(entity);
            _entityToComponentTypeMap.at(entity).erase(GetComponentTypeId<TComponent>());
        }

        System() : impl::SystemImpl<TSystem, TComponents ...>(),
                   _masterComponentsToRemoveMap(),
                   _entityToComponentTypeMap(),
                   _entitiesToRemove(),
                   _deadEntities(0),
                   _entityCounter(1)
        {
            AddComponentRemoveListToMasterRemoveMap();
        }
    };

#define REGISTER_SYSTEM_BEGIN(SYSTEM_NAME) \
    class SYSTEM_NAME; \
    namespace \
    { \
        using RegisteredSystem = SYSTEM_NAME; \
    }

#define REGISTER_COMPONENT(COMPONENT_NAME) \
    using COMPONENT_NAME = component_templates::COMPONENT_NAME<RegisteredSystem>; \
    using COMPONENT_NAME##Ptr = tyleo::ComponentPtr<COMPONENT_NAME>;

#define REGISTER_SYSTEM_END()


#define BEGIN_SYSTEM(SYSTEM_NAME, ...) \
    class SYSTEM_NAME : public tyleo::System<SYSTEM_NAME, ##__VA_ARGS__> \
    {

#define END_SYSTEM() \
    }
}
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "component.h"
#include "entity.h"

namespace tyleo
{
    namespace impl
    {
        template <typename TSystem, typename ... TComponents>
        class SystemImpl;

        template <typename TSystem>
        class SystemImpl<TSystem>
        {
        private:
            using ComponentsToRemoveList = std::vector<Entity> ;
            using ComponentsToRemoveListPtr = std::shared_ptr<ComponentsToRemoveList> ;
            using MasterComponentsToRemoveMap = std::unordered_map<ComponentTypeId, ComponentsToRemoveListPtr>;

        protected:
            void AddComponents() {}

            void RemoveComponents() {}

            void Update() {}

            void AddComponentRemoveListToMasterRemoveMap(MasterComponentsToRemoveMap & masterComponentsToRemoveMap) {}

            size_t GetNumberOfComponents()
            {
                return 0;
            }

            template <typename TComponentTypeIdToGet>
            ComponentTypeId GetComponentTypeId()
            {
                static_assert(false, "You are using a component type that your system does not support.");
            }

            template <typename TComponentToGet>
            ComponentPtr<TComponentToGet> GetComponentFromEntity(Entity entityId)
            {
                static_assert(false, "You are using a component type that your system does not support.");
            }

            template <typename TComponentToAdd>
            ComponentPtr<TComponentToAdd> AddComponentToEntity(Entity entityId)
            {
                static_assert(false, "You are using a component type that your system does not support.");
            }
        };

        template <typename TSystem, typename TComponent, typename ... TComponents>
        class SystemImpl<TSystem, TComponent, TComponents ...> : public SystemImpl<TSystem, TComponents ...>
        {
        private:
            using EntityToComponentPtrMap = std::unordered_map<Entity, ComponentPtr<TComponent>>;
            using ComponentsToAddList = std::vector<std::pair<Entity, ComponentPtr<TComponent>>>;
            using ComponentsToAddListPtr = std::shared_ptr<ComponentsToAddList>;
            using ComponentsToRemoveList = std::vector<Entity>;
            using ComponentsToRemoveListPtr = std::shared_ptr<ComponentsToRemoveList>;
            using MasterComponentsToRemoveMap = std::unordered_map<ComponentTypeId, ComponentsToRemoveListPtr>;

            EntityToComponentPtrMap _entityToComponentPtrMap;

            ComponentsToAddListPtr _componentsToAddListPtr;
            ComponentsToRemoveListPtr _componentsToRemoveListPtr;

        protected:
            void AddComponentRemoveListToMasterRemoveMap(MasterComponentsToRemoveMap & masterComponentsToRemoveMap)
            {
                masterComponentsToRemoveMap.emplace(std::make_pair(GetComponentTypeId<TComponent>(), _componentsToRemoveListPtr));
                SystemImpl<TSystem, TComponents ...>::AddComponentRemoveListToMasterRemoveMap(masterComponentsToRemoveMap);
            }

            void AddComponents()
            {
                for (auto entityComponentPtrPair : *_componentsToAddListPtr)
                {
                    _entityToComponentPtrMap.emplace(entityComponentPtrPair);
                }
                _componentsToAddListPtr->clear();

                SystemImpl<TSystem, TComponents ...>::AddComponents();
            }

            void RemoveComponents()
            {
                for (auto entity : *_componentsToRemoveListPtr)
                {
                    _entityToComponentPtrMap.erase(entity);
                }
                _componentsToRemoveListPtr->clear();

                SystemImpl<TSystem, TComponents ...>::RemoveComponents();
            }

            void Update()
            {
                for (auto & entityIdComponentPtrPair : _entityToComponentPtrMap)
                {
                    static_cast<TComponent *>(entityIdComponentPtrPair.second.get())->Update();
                }

                SystemImpl<TSystem, TComponents ...>::Update();
            }

            size_t GetNumberOfComponents()
            {
                return SystemImpl<TSystem, TComponents ...>::GetNumberOfComponents() + _entityToComponentPtrMap.size();
            }

            template <typename TComponentTypeIdToGet>
            ComponentTypeId GetComponentTypeId()
            {
                return SystemImpl<TSystem, TComponents ...>::GetComponentTypeId<TComponentTypeIdToGet>();
            }

            template <>
            ComponentTypeId GetComponentTypeId<TComponent>()
            {
                return sizeof...(TComponents) + 1;
            }

            template <typename TComponentToGet>
            ComponentPtr<TComponentToGet> GetComponentFromEntity(Entity entityId)
            {
                return SystemImpl<TSystem, TComponents ...>::GetComponentFromEntity<TComponentToGet>(entityId);
            }

            template <>
            ComponentPtr<TComponent> GetComponentFromEntity<TComponent>(Entity entityId)
            {
                return _entityToComponentPtrMap.at(entityId);
            }

            template <typename TComponentToAdd>
            ComponentPtr<TComponentToAdd> AddComponentToEntity(ComponentPtr<TComponentToAdd> & componentPtr, Entity entity)
            {
                return SystemImpl<TSystem, TComponents ...>::AddComponentToEntity<TComponentToAdd>(componentPtr, entity);
            }

            template <>
            ComponentPtr<TComponent> AddComponentToEntity<TComponent>(ComponentPtr<TComponent> & componentPtr, Entity entity)
            {
                _componentsToAddListPtr->emplace_back(std::make_pair(entity, componentPtr));
                return componentPtr;
            }

            template <typename TComponentToRemove>
            void RemoveComponentFromEntity(Entity entity)
            {
                SystemImpl<TSystem, TComponents ...>::RemoveComponentFromEntity<TComponentToRemove>(entity);
            }

            template <>
            void RemoveComponentFromEntity<TComponent>(Entity entity)
            {
                _componentsToRemoveListPtr->emplace_back(entity);
            }

            SystemImpl() : SystemImpl<TSystem, TComponents ...>(),
                            _entityToComponentPtrMap(),
                           _componentsToAddListPtr(new ComponentsToAddList()),
                           _componentsToRemoveListPtr(new ComponentsToRemoveList())
            {}
        };
    }
}

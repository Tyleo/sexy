#pragma once

#include <type_traits>
#include <utility>

#include "events.h"
#include "component_register.h"
#include "system_register.h"

namespace sexy
{
    namespace impl
    {
        template <typename TSystemRegister,
                  typename ... TComponentRegisters>
        class SystemImpl;

        template <typename TSystemRegister>
        class SystemImpl<TSystemRegister>
        {
        private:
            ENABLE_SYSTEM_REGISTER_TYPEDEFS(TSystemRegister);
            
            using This = SystemImpl<TSystemRegister>;

        protected:
            template <typename TComponent>
            using FindBase = void;

            template <typename TComponent>
            using ComponentIterable = void;

            inline void FlushAddBuffers() { }

            inline void FlushRemoveBuffers() { }

            inline void SetupMasterRemoveMap(ComponentTypeIdToEntityBufferPtrMap & masterRemoveMap) { }

        public:
            template <typename TEvent, typename ... TArgs>
            static inline void PreSendAll(const TArgs & ... args) { }

            template <typename TEvent, typename ... TArgs>
            inline void SendAll(const TArgs & ... args) { }

            template <typename TEvent, typename ... TArgs>
            inline void SendAllTarget(const Entity target, const TArgs & ... args) { }

            template <typename TEvent, typename ... TArgs>
            static inline void PostSendAll(const TArgs & ... args) { }
        };

        template <typename TSystemRegister,
                  typename TComponentRegister,
                  typename ... TComponentRegisters>
        class SystemImpl<TSystemRegister,
                         TComponentRegister,
                         TComponentRegisters ...> : protected SystemImpl<TSystemRegister,
                                                                         TComponentRegisters ... >
        {
        private:
            ENABLE_SYSTEM_REGISTER_TYPEDEFS(TSystemRegister);
            ENABLE_COMPONENT_REGISTER_TYPEDEFS(TComponentRegister);

            using This = SystemImpl<TSystemRegister, TComponentRegister, TComponentRegisters ...>;
            using Base = SystemImpl<TSystemRegister, TComponentRegisters ...>;
            using CComponent = UComponent<Entity>;
            using CComponentPtr = ComponentPtr<CComponent>;
            using CEntityToComponentPtrMap = EntityToComponentPtrMap<Entity, CComponentPtr>;

            CEntityToComponentPtrMap  _components;
            EntityComponentPtrBuffer<Entity, CComponentPtr> _componentsToAdd;
            // TODO: Storing this buffer as a pointer requires an extra indirection for access.
            EntityBufferPtr _componentsToRemove;

        protected:
            template <typename TComponent>
            using FindBase = typename std::conditional<std::is_same<TComponent, CComponent>::value, This, typename Base::template FindBase<TComponent>>::type;
            template <typename TComponent>
            using ComponentIterable = typename std::conditional<std::is_same<TComponent, CComponent>::value, Iterable<CComponentPtr, CEntityToComponentPtrMap, EntityToComponentPtrMapFunctor>, typename Base::template ComponentIterable<TComponent>>::type;

            inline void FlushAddBuffers()
            {
                for(const auto & entityComponentPtrPair : _componentsToAdd)
                {
                    _components.emplace(entityComponentPtrPair);
                }

                Base::FlushAddBuffers();

                for (const auto & entityComponentPtrPair : _componentsToAdd)
                {
                    entityComponentPtrPair.second->On<events::Initialize>(this);
                }

                _componentsToAdd.clear();
            }

            inline void FlushRemoveBuffers()
            {
                for (const auto & entity : *_componentsToRemove)
                {
                    _components.find(entity)->second->On<events::Uninitialize>(this);
                }

                Base::FlushRemoveBuffers();

                for (const auto entity : *_componentsToRemove)
                {
                    _components.erase(entity);
                }

                _componentsToRemove->clear();
            }

            inline void SetupMasterRemoveMap(ComponentTypeIdToEntityBufferPtrMap & masterRemoveMap)
            {
                masterRemoveMap.emplace(std::make_pair(This::GetComponentTypeId<CComponent>(), _componentsToRemove));
            }

        public:
            template <typename ... TArgs>
            inline const CComponentPtr AddComponent(const Entity entity, const TArgs & ... args)
            {
                const CComponentPtr newComponent{ new CComponent{ entity, args ... } };
                _componentsToAdd.emplace_back(std::make_pair(entity, newComponent));
                return newComponent;
            }

            inline void RemoveComponent(const Entity entity)
            {
                _componentsToRemove->emplace_back(entity);
            }

            inline const CComponentPtr GetComponent(const Entity entity)
            {
                return _components.find(entity)->second;
            }

            inline ComponentIterable<CComponent> GetComponents()
            {
                return ComponentIterable<CComponent>{ _components };
            }

            template <typename TComponent>
            inline const ComponentTypeId GetComponentTypeId()
            {
                return sizeof ... (TComponentRegisters) + 1;
            }

            template <typename TEvent, typename ... TArgs>
            static inline void PreSendAll(const TArgs & ... args)
            {
                PreSend<TEvent>(args ...);
                Base::PreSendAll<TEvent>(args ...);
            }

            template <typename TEvent, typename ... TArgs>
            inline void SendAll(const TArgs & ... args)
            {
                Send<TEvent>(args ...);
                Base::SendAll<TEvent>(args ...);
            }

            template <typename TEvent, typename ... TArgs>
            inline void SendAllTarget(const Entity target, const TArgs & ... args)
            {
                if (_components.find(target) != _components.end())
                {
                    GetComponent(target)->On<TEvent>(args ...);
                }
                Base::SendAllTarget<TEvent>(target, args ...);
            }

            template <typename TEvent, typename ... TArgs>
            static inline void PostSendAll(const TArgs & ... args)
            {
                PostSend<TEvent>(args ...);
                Base::PostSendAll<TEvent>(args ...);
            }

            template <typename TEvent, typename ... TArgs>
            static inline void PreSend(const TArgs & ... args)
            {
                CComponent::Pre<TEvent>(args ...);
            }

            template <typename TEvent, typename ... TArgs>
            inline void Send(const TArgs & ... args)
            {
                for (auto & component : GetComponents())
                {
                    component->On<TEvent>(args ...);
                }
            }

            template <typename TEvent, typename ... TArgs>
            inline void SendTarget(const Entity target, const TArgs & ... args)
            {
                GetComponent(target)->On<TEvent>(args ...);
            }

            template <typename TEvent, typename ... TArgs>
            static inline void PostSend(const TArgs & ... args)
            {
                CComponent::Post<TEvent>(args ...);
            }

            SystemImpl() : _components{},
                           _componentsToAdd{},
                           _componentsToRemove{ new EntityBuffer{} }
            { }
        };
    }
}

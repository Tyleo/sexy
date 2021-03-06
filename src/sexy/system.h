#pragma once

#include <chrono>
#include <utility>

#include "events.h"
#include "iterator.h"
#include "system_impl.h"
#include "typedefs.h"

namespace sexy
{
    template <typename TSystemRegister,
              typename ... TComponentRegisters>
    class System : private impl::SystemImpl<TSystemRegister,
                                            TComponentRegisters ...>
    {
        ENABLE_SYSTEM_REGISTER_TYPEDEFS(TSystemRegister);

    private:
        using This = System<TSystemRegister, TComponentRegisters ...>;
        using Base = impl::SystemImpl<TSystemRegister, TComponentRegisters ...>;

        template <typename TComponent>
        using FindBase = typename Base::template FindBase<TComponent>;

        template <typename TComponent>
        using ComponentIterable = typename Base::template ComponentIterable<TComponent>;

        Entity _entityCounter;
        EntityBuffer _entityRemoveBuffer;
        EntityBuffer _deadEntityBuffer;

        EntityToComponentTypeIdSetMap _entityToComponentTypesMap;
        ComponentTypeIdToEntityBufferPtrMap _masterComponentsToRemoveMap;

        std::chrono::steady_clock::time_point _lastTimePoint;
        std::chrono::duration<float, std::ratio<1, 1>> _deltaTime;

        void SetupMasterRemoveMap()
        {
            Base::SetupMasterRemoveMap(_masterComponentsToRemoveMap);
        }

    protected:
        void FlushAddBuffers()
        {
            Base::PreSendAll<events::Initialize>();
            Base::FlushAddBuffers();
            Base::PostSendAll<events::Initialize>();
        }

        void FlushRemoveBuffers()
        {
            for (const auto entity : _entityRemoveBuffer)
            {
                for (const auto componentTypeId : _entityToComponentTypesMap.at(entity))
                {
                    _masterComponentsToRemoveMap.at(componentTypeId)->emplace_back(entity);
                }

                _entityToComponentTypesMap.erase(entity);
                _deadEntityBuffer.emplace_back(entity);
            }

            _entityRemoveBuffer.clear();

            Base::FlushRemoveBuffers();
        }

    public:
        inline void CustomUpdate() { }

        inline void Update()
        {
            auto currentTimePoint = std::chrono::steady_clock::now();
            _deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTimePoint - _lastTimePoint);
            _lastTimePoint = currentTimePoint;

            static_cast<CSystem * const>(this)->CustomUpdate();

            SendAll<events::Update>(static_cast<CSystem *>(this));

            FlushAddBuffers();
            FlushRemoveBuffers();
        }

        const float GetDeltaTime() const
        {
            return _deltaTime.count();
        }

        const Entity CreateEntity()
        {
            Entity returnValue;

            if (_deadEntityBuffer.empty())
            {
                returnValue = ++_entityCounter;
            }
            else
            {
                auto deadEntityIt = --_deadEntityBuffer.end();
                returnValue = *deadEntityIt;
                _deadEntityBuffer.erase(deadEntityIt);
            }

            _entityToComponentTypesMap.emplace(std::make_pair(returnValue, ComponentTypeIdSet{}));
            return returnValue;
        }

        void RemoveEntity(const Entity entity)
        {
            _entityRemoveBuffer.emplace_back(entity);
        }

        template <typename TComponent, typename ... TArgs>
        const ComponentPtr<TComponent> AddComponent(const Entity entity, const TArgs & ... args)
        {
            const ComponentPtr<TComponent> & newComponent{ FindBase<TComponent>::AddComponent(entity, args ...) };
            _entityToComponentTypesMap.at(entity).emplace(GetComponentTypeId<TComponent>());
            return newComponent;
        }

        template <typename TComponent>
        void RemoveComponent(const Entity entity)
        {
            FindBase<TComponent>::RemoveComponent(entity);
        }

        template <typename TComponent>
        const ComponentPtr<TComponent> GetComponent(const Entity entity)
        {
            return FindBase<TComponent>::GetComponent(entity);
        }

        template <typename TComponent>
        ComponentIterable<TComponent> GetComponents()
        {
            return FindBase<TComponent>::GetComponents();
        }

        template <typename TComponent>
        static const ComponentTypeId GetComponentTypeId()
        {
            return Base::GetComponentTypeId<TComponent>();
        }

        template <typename TEvent, typename ... TArgs>
        void SendAll(const TArgs & ... args)
        {
            Base::PreSendAll<TEvent>(args ...);
            Base::SendAll<TEvent>(args ...);
            Base::PostSendAll<TEvent>(args ...);
        }

        template <typename TEvent, typename TComponent, typename ... TArgs>
        void Send(const TArgs & ... args)
        {
            FindBase<TComponent>::PreSend<TEvent>(args ...);
            FindBase<TComponent>::Send<TEvent>(args ...);
            FindBase<TComponent>::PostSend<TEvent>(args ...);
        }

        template <typename TEvent, typename ... TArgs>
        void SendAllTarget(const Entity target, const TArgs & ... args)
        {
            Base::SendAllTarget<TEvent>(target, args ...);
        }

        template <typename TEvent, typename TComponent, typename ... TArgs>
        void SendTarget(const Entity target, const TArgs & ... args)
        {
            FindBase<TComponent>::SendTarget<TEvent>(target, args ...);
        }

        System() : _entityCounter{},
                   _entityRemoveBuffer{},
                   _deadEntityBuffer{},
                   _entityToComponentTypesMap{},
                   _masterComponentsToRemoveMap{},
                   _lastTimePoint{ std::chrono::steady_clock::now() },
                   _deltaTime{}
        {
            SetupMasterRemoveMap();
        }
    };
}

#pragma once

#include <utility>

namespace sexy
{
    /// \struct SystemDescription system_description.h "sexy/system_description.h"
    /// \brief Contains information about a system type and how it should be implemented.
    /// \tparam TEntity The type of entity used by the system.
    /// \tparam TComponentTypeId The type of Id to give each component. Every type of Component will have a
    ///                          unique Id.
    /// \tparam TEntityBuffer The type of simple growable buffer of entities. Mainly used for keeping track
    ///                       of new and dead entities.
    /// \tparam TEntityBufferPtr A type of pointer which points to an EntityBuffer.
    /// \tparam TComponentPtr A type of pointer which points to a Component.
    /// \tparam TComponentTypeIdSet The type of set used to hold ComponentTypeIds.
    /// \tparam TEntityToComponentTypeIdSetMap A type of map which allows an entity to retrieve a set of
    ///                                        ComponentTypeIds for the Components it owns.
    /// \tparam TComponentTypeIdToEntityBufferPtrMap A type of map which allows an EntityBuffer to be
    ///                                              located via a ComponentTypeId. Used for removing
    ///                                              entities.
    template <typename TEntity,
              typename TComponentTypeId,
              template <typename> class TEntityBuffer,
              template <typename> class TEntityBufferPtr,
              template <typename> class TComponentPtr,
              template <typename> class TComponentTypeIdSet,
              template <typename, typename> class TEntityToComponentTypeIdSetMap,
              template <typename, typename> class TComponentTypeIdToEntityBufferPtrMap>
    struct SystemDescription final
    {
        /// \typedef Entity = TEntity
        /// \brief The type of entity used by the system.
        using Entity = TEntity;

        /// \typedef ComponentTypeId = TComponentTypeId
        /// \brief The type of Id to give each type of component. Every type of component will have a unique
        ///        Id.
        using ComponentTypeId = TComponentTypeId;

        /// \typedef EntityBuffer = TEntityBuffer<Entity>
        /// \brief The type of simple growable buffer of entities. Mainly used for keeping track of new and
        ///        dead entities.
        using EntityBuffer = TEntityBuffer<Entity>;

        /// \typedef EntityBufferPtr = TEntityBufferPtr<EntityBuffer>
        /// \brief A type of pointer which points to an EntityBuffer.
        using EntityBufferPtr = TEntityBufferPtr<EntityBuffer>;

        /// \typedef ComponentPtr = TComponentPtr<TComponent>
        /// \brief A type of pointer which points to a Component.
        /// \tparam TComponent The type of component this ComponentPtr points to.
        template <typename TComponent>
        using ComponentPtr = TComponentPtr<TComponent>;

        /// \typedef ComponentTypeIdSet = TComponetTypeIdSet<ComponentTypeId>
        /// \brief The type of set used to hold ComponentTypeIds.
        using ComponentTypeIdSet = TComponentTypeIdSet<ComponentTypeId>;

        /// \typedef EntityToComponentTypeIdSetMap = TEntityToComponentTypeIdSetMap<Entity, ComponentTypeIdSet>
        /// \brief A type of map which allows an entity to retrieve a set of ComponentTypeIds for the
        ///        Components it owns.
        using EntityToComponentTypeIdSetMap = TEntityToComponentTypeIdSetMap<Entity, ComponentTypeIdSet>;

        /// \typedef ComponentTypeIdToEntityBufferPtrMap = TComponentTypeIdToEntityBufferPtrMap<ComponentTypeId, EntityBufferPtr>
        /// \brief A type of map which allows an EntityBuffer to be located via a ComponentTypeId. Used for
        ///        removing Entities.
        using ComponentTypeIdToEntityBufferPtrMap = TComponentTypeIdToEntityBufferPtrMap<ComponentTypeId, EntityBufferPtr>;
    };
}

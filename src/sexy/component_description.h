#pragma once

#include <utility>

namespace sexy
{
    /// \struct ComponentDescription component_description.h "sexy/component_description.h"
    /// \brief Contains information about how a component type should be handled by a system.
    /// \tparam TEntityFilter The type of filter to use to make a guess about whether an entity has a
    ///                       component. Some useful filters are Bloom Filters or Cuckoo Filters.
    /// \tparam TEntityComponentPtrBuffer The type of buffer to use as temporary storage for new Entities.
    /// \tparam TEntityToComponentPtrMap A type of map which allows an component to be located for a given
    ///                                  entity.
    /// \tparam TEntityToComponentPtrMapFunctor A functor which converts the item an EntityToComponentPtrMap
    ///                                         iterator points to into a single item.
    template <template <typename> class TEntityFilter,
              template <typename> class TEntityComponentPtrBuffer,
              template <typename, typename> class TEntityToComponentPtrMap,
              typename TEntityToComponentPtrMapFunctor>
    struct ComponentDescription final
    {
        /// \typedef using EntityFilter = TEntityFilter<TEntity>
        /// \brief The type of filter to use to make a guess about whether an entity has a component. Some
        ///        useful filters are Bloom Filters or Cuckoo Filters.
        /// \tparam TEntity The type of entity to filter.
        template <typename TEntity>
        using EntityFilter = TEntityFilter<TEntity>;

        /// \typedef using EntityComponentPtrBuffer = TEntityComponentPtrBuffer<std::pair<TEntity, TComponentPtr>>
        /// \brief The type of buffer to use as temporary storage for new Entities.
        /// \tparam TEntity The type of Entity to store.
        /// \tparam TComponentPtr The type of ComponentPtr to store.
        template <typename TEntity, typename TComponentPtr>
        using EntityComponentPtrBuffer = TEntityComponentPtrBuffer<std::pair<TEntity, TComponentPtr>>;

        /// \typedef EntityToComponentPtrMap = TEntityToComponentPtrMap<Entity, ComponentPtr<TComponent>>
        /// \brief A type of map which allows an component to be located for a given entity.
        /// \tparam TEntity The type of entity to use to locate the ComponentPtr.
        /// \tparam TComponent The type of ComponentPtr this EntityToComponentPtrMap provides the location of.
        template <typename TEntity, typename TComponentPtr>
        using EntityToComponentPtrMap = TEntityToComponentPtrMap<TEntity, TComponentPtr>;

        /// \typedef EntityToComponentPtrMapFunctor = TEntityToComponentPtrMapFunctor
        /// \brief A functor which converts the item an EntityToComponentPtrMap iterator points to into a
        ///        single item.
        using EntityToComponentPtrMapFunctor = TEntityToComponentPtrMapFunctor;
    };
}

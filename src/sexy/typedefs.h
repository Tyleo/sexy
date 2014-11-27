#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "component_description.h"
#include "component_register.h"
#include "system_description.h"
#include "system_register.h"

namespace sexy
{
    /// \typedef BasicEntity = uint_fast16_t
    /// \brief A default entity type for those who don't wish to provide a custom entity type.
    using BasicEntity = uint_fast16_t;

    /// \typedef BasicComponentTypeId = uint_fast16_t
    /// \brief A default component type id type for those who don't wish to provide a custom component type
    ///        id type.
    using BasicComponentTypeId = uint_fast8_t;

    /// \typedef BasicBuffer = std::vector<TItem>
    /// \brief A default buffer type for those who don't wish to provide a custom buffer type.
    /// \tparam TItem The type of the item this buffer contains.
    template <typename TItem>
    using BasicBuffer = std::vector<TItem>;

    /// \typedef BasicSet = std::unordered_set<TItem>
    /// \brief A default set type for those who don't wish to provide a custom set type.
    /// \tparam TItem The type of the item this set contains.
    template <typename TItem>
    using BasicSet = std::unordered_set<TItem>;

    /// \typedef BasicMap = std::unordered_map<TKey, TValue>
    /// \brief A default map type for those who don't wish to provide a custom map type.
    /// \tparam TKey The type of items used as keys in this map.
    /// \tparam TValue The type of items stored in this map.
    template <typename TKey, typename TValue>
    using BasicMap = std::unordered_map<TKey, TValue>;

    /// \typedef BasicPtr = std::shared_ptr<TITem>
    /// \brief A default pointer type for those who don't wish to provide a custom pointer type.
    /// \tparam TItem The type of item this pointer points to.
    template <typename TItem>
    using BasicPtr = std::shared_ptr<TItem>;

    /// \struct BasicMapToItemIteratorAdapter typedefs.h "sexy/typedefs.h"
    /// \brief Adapts a map iterator so that only items are iterated.
    struct BasicMapToItemIteratorAdapter final
    {
        /// \fn operator ()
        /// \brief Returns the second item from a dereferenced map iterator.
        /// \tparam TIterator The type of item to the map iterator returns when dereferenced.
        /// \param item The item to get the second item from.
        /// \returns The second item from the item param.
        template <typename TItem>
        auto operator () (TItem & item) -> decltype(item.second) &
        {
            return item.second;
        }
    };

    /// \struct BasicFilter typedefs.h "sexy/typedefs.h"
    /// \brief A default filter type for those who don't wish to provide a custom filter type.
    /// \tparam TItem The type of item this filter filters.
    template <typename TItem>
    struct BasicFilter final
    {
        /// \fn AddItem
        /// \brief Adds an item to the filter.
        /// \param item The item to add.
        inline void AddItem(const TItem & item) { }

        /// \fn RemoveItem
        /// \brief Removes an item from the filter.
        /// \param item The item to remove.
        inline void RemoveItem(const TItem & item) { }

        /// \fn HasItem
        /// \brief Tests whether the filter contains the item.
        /// \param item The item to check the filter for.
        inline bool HasItem(const TItem & item) { return true; }
    };

    /// \typedef BasicSystemDescription
    /// \brief A default system description type for those who don't wish to provide a custom system
    ///        description type.
    using BasicSystemDescription = SystemDescription<BasicEntity,
                                                     BasicComponentTypeId,
                                                     BasicBuffer,
                                                     BasicPtr,
                                                     BasicPtr,
                                                     BasicSet,
                                                     BasicMap,
                                                     BasicMap>;

    /// \typedef BasicComponentDescription
    /// \brief A default component description type for those who don't wish to provide a custom component
    ///        description type.
    using BasicComponentDescription = ComponentDescription<BasicFilter,
                                                           BasicBuffer,
                                                           BasicMap,
                                                           BasicMapToItemIteratorAdapter>;

    /// \typedef BasicSystemRegister = SystemRegister<TSystem, BasicSystemDescription>
    /// \brief A basic system register which only requires a system type.
    /// \tparam TSystem The type of system to register.
    template <typename TSystem>
    using BasicSystemRegister = SystemRegister<TSystem, BasicSystemDescription>;

    /// \typedef BasicComponentRegister = ComponentRegister<TComponent, BasicComponentDescription>
    /// \brief A basic component register which only requires a component type.
    /// \tparam TComponent The type of component to register.
    template <template <typename> class TComponent>
    using BasicComponentRegister = ComponentRegister<TComponent, BasicComponentDescription>;
}

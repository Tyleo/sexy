#pragma once

namespace sexy
{
    /// \struct ComponentRegister component_register.h "sexy/component_register.h"
    /// \brief Contains a component type and information about how that component type should be handled by
    ///        a system.
    /// \tparam TComponent The type of component we are providing information about.
    /// \tparam TComponentDescription Provides information about the component type should be handled by a
    ///                               system.
    template <template <typename> class TComponent,
              typename TComponentDescription>
    struct ComponentRegister final
    {
        /// \typedef Component = TComponent
        /// \brief The type of component we are providing information about.
        /// \tparam TEntity The type of entity this component belongs to.
        template <typename TEntity>
        using Component = TComponent<TEntity>;

        /// \typedef ComponentDescription = TComponentDescription
        /// \brief Provides information about the component type should be handled by a system.
        using ComponentDescription = TComponentDescription;
    };

    /// \def ENABLE_COMPONENT_REGISTER_TYPEDEFS
    /// \brief Floods the current namespace with the typedefs contained in a ComponentRegister. This makes
    ///        them easier to access.
    /// \tparam TComponentRegister The ComponentRegister to make accessible.
    #define ENABLE_COMPONENT_REGISTER_TYPEDEFS(TComponentRegister) \
        private: \
        template <typename TEntity> \
        using UComponent = typename TComponentRegister::template Component<TEntity>; \
        template <typename TEntity> \
        using EntityFilter = typename TComponentRegister::ComponentDescription::template EntityFilter<TEntity>; \
        template <typename TEntity, typename TComponentPtr> \
        using EntityComponentPtrBuffer = typename TComponentRegister::ComponentDescription::template EntityComponentPtrBuffer<TEntity, TComponentPtr>; \
        template <typename TEntity, typename TComponentPtr> \
        using EntityToComponentPtrMap = typename TComponentRegister::ComponentDescription::template EntityToComponentPtrMap<TEntity, TComponentPtr>; \
        using EntityToComponentPtrMapFunctor = typename TComponentRegister::ComponentDescription::EntityToComponentPtrMapFunctor;
}

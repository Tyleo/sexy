#pragma once

namespace sexy
{
    /// \struct SystemRegister system_register.h "sexy/system_register.h"
    /// \brief Contains a system type and information about how the system's implementation.
    /// \tparam TSystem The type of system we are providing information about.
    /// \tparam TSystemDescription Provides information about how the system should be implemented.
    template <typename TSystem,
              typename TSystemDescription>
    struct SystemRegister final
    {
        /// \typedef System = TSystem
        /// \brief The type of system we are providing information about.
        using System = TSystem;

        /// \typedef SystemDescription = TSystemDescription
        /// \brief Provides information about how the system should be implemented.
        using SystemDescription = TSystemDescription;
    };

    /// \def ENABLE_SYSTEM_REGISTER_TYPEDEFS
    /// \brief Floods the current namespace with the typedefs contained in a SystemRegister. This makes
    ///        them easier to access.
    /// \tparam TSystemRegister The SystemRegister to make accessible.
    #define ENABLE_SYSTEM_REGISTER_TYPEDEFS(TSystemRegister) \
        public: \
        using CSystem = typename TSystemRegister::System; \
        using Entity = typename TSystemRegister::SystemDescription::Entity; \
        private: \
        using ComponentTypeId = typename TSystemRegister::SystemDescription::ComponentTypeId; \
        using EntityBuffer = typename TSystemRegister::SystemDescription::EntityBuffer; \
        using EntityBufferPtr = typename TSystemRegister::SystemDescription::EntityBufferPtr; \
        template <typename TComponent> \
        using ComponentPtr = typename TSystemRegister::SystemDescription::template ComponentPtr<TComponent>; \
        using ComponentTypeIdSet = typename TSystemRegister::SystemDescription::ComponentTypeIdSet; \
        using EntityToComponentTypeIdSetMap = typename TSystemRegister::SystemDescription::EntityToComponentTypeIdSetMap; \
        using ComponentTypeIdToEntityBufferPtrMap = typename TSystemRegister::SystemDescription::ComponentTypeIdToEntityBufferPtrMap;
}

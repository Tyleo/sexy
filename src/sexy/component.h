#pragma once

// This namespace is only here because it makes me feel better. :)
namespace sexy
{
    template <typename TSystem>
    class Component
    {
    protected:
        using System = TSystem;
        using Entity = typename TSystem::Entity;
        using ComponentTypeId = typename TSystem::ComponentTypeId;

    private:
        Entity _ownerEntity;

    public:
        const Entity GetOwnerEntity() const
        {
            return _ownerEntity;
        }

        Component(const Entity ownerEntity) : _ownerEntity{ ownerEntity }
        { }

        Component() = default;
    };

    #define TYPEDEF_C(Component, TSystem, ...) \
        using C##Component = Component<TSystem, ##__VA_ARGS__>;

    #define COMPONENT_INTERNALS \
        public: \
        template <typename TEvent, typename ... TArgs> \
        inline static void Pre(const TArgs & ... args) \
        { \
            Pre(TEvent{}, args ...); \
        } \
        template <typename TEvent, typename ... TArgs> \
        inline static void Pre(TEvent, const TArgs & ...) { } \
        template <typename TEvent, typename ... TArgs> \
        inline void On(const TArgs & ... args) \
        { \
            On(TEvent{}, args ...); \
        } \
        template <typename TEvent, typename ... TArgs> \
        inline void On(TEvent, const TArgs & ...) { } \
        template <typename TEvent, typename ... TArgs> \
        inline static void Post(const TArgs & ... args) \
        { \
            Post(TEvent{}, args ...); \
        } \
        template <typename TEvent, typename ... TArgs> \
        inline static void Post(TEvent, const TArgs & ...) { } \
        private:

    #define COMPONENT_START() \
        template <typename TSystem> \
        void Start(TSystem & system)

    #define COMPONENT_PRE(Event, ...) \
        template <> \
        static void Pre<Event>(__VA_ARGS__)

    #define COMPONENT_ON(Event, ...) \
        template <> \
        void On<Event>(__VA_ARGS__)

    #define COMPONENT_POST(Event, ...) \
        template <> \
        static void Post<Event>(__VA_ARGS__)
        
}

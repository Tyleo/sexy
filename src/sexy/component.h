#pragma once

// This namespace is only here because it makes me feel better. :)
namespace sexy
{
    template <typename TEntity>
    class Component
    {
    private:
        TEntity _ownerEntity;

    public:
        const TEntity GetOwnerEntity() const
        {
            return _ownerEntity;
        }

        Component(const TEntity ownerEntity) : _ownerEntity{ ownerEntity }
        { }

        Component() = default;
    };

    #define TYPEDEF_C(Component, Entity) \
        using C##Component = Component<Entity>;

    #define COMPONENT_INTERNALS \
        public: \
        template <typename TEvent, typename ... TArgs> \
        static void Pre(const TArgs & ...) { } \
        template <typename TEvent, typename ... TArgs> \
        void On(const TArgs & ...) { } \
        template <typename TEvent, typename ... TArgs> \
        static void Post(const TArgs & ...) { } \
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
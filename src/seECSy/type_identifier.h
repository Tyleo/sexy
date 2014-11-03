#pragma once

namespace tyleo
{
    template <typename ... TTypes>
    class TypeIdentifier;

    template <typename TReturn>
    class TypeIdentifier<TReturn>
    {
    public:
        template <typename TTypeToIdentify>
        static TReturn GetTypeId()
        {
            return 0;
        }
    };

    template <typename TReturn, typename TType, typename ... TTypes>
    class TypeIdentifier<TReturn, TType, TTypes ...> : public TypeIdentifier<TReturn, TTypes ...>
    {
    public:
        template <typename TTypeToIdentify>
        static TReturn GetTypeId()
        {
            return TypeIdentifier<TReturn, TTypes ...>::GetTypeId<TTypeToIdentify>();
        }

        template <>
        static TReturn GetTypeId<TType>()
        {
            return sizeof...(TTypes) + 1;
        }
    };
}

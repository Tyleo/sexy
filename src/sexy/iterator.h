#pragma once

namespace sexy
{
    namespace
    {
        /// \struct PassThrough iterator.h "sexy/iterator.h"
        /// \brief A functor which accepts a reference to a value and returns a reference to the same value.
        /// \tparam TValue The type of the value.
        template <typename TValue>
        struct PassThrough final
        {
            /// \fn operator ()
            /// \brief Accepts a reference to a value and returns a reference to the same value.
            /// \param value The value to return.
            /// \return A reference to the original value.
            TValue & operator () (TValue & value) const
            {
                return value;
            }
        };
    }

    /// \class Iterator iterator.h "sexy/iterator.h"
    /// \brief A class which adapts an iterator so that it may return a different type when dereferenced.
    /// \tparam TItem The type of item to return when dereferenced.
    /// \tparam TInternalIterator The type of iterator being adapted.
    /// \tparam TInternalIteratorToItem The type of a functor which adapts the iterator.
    template <typename TItem, typename TInternalIterator, typename TInternalIteratorToItem = PassThrough<TItem>>
    class Iterator final
    {
    private:
        TInternalIterator _internalIterator;

    public:
        /// \fn operator *
        /// \brief Dereferences the iterator.
        /// \return The value the iterator points to.
        TItem & operator * ()
        {
            return TInternalIteratorToItem{}(*_internalIterator);
        }

        /// \fn operator ->
        /// \brief Dereferences the iterator.
        /// \return The value the iterator points to.
        TItem & operator -> ()
        {
            return TInternalIteratorToItem{}(*_internalIterator);
        }

        /// \fn operator ++
        /// \brief Advances the iterator.
        /// \return The advanced iterator.
        Iterator & operator ++ ()
        {
            ++_internalIterator;
            return *this;
        }

        /// \fn operator ++
        /// \brief Advances the iterator.
        /// \return A copy of the iterator before it was advanced.
        Iterator operator ++ (int)
        {
            Iterator temp(*this);
            ++*this;
            return temp;
        }

        /// \fn operator --
        /// \brief Moves the iterator back.
        /// \return The moved-back iterator.
        Iterator & operator -- ()
        {
            --_internalIterator;
            return *this;
        }

        /// \fn operator --
        /// \brief Moves the iterator back.
        /// \return A copy of the iterator before it was moved-back.
        Iterator operator -- (int)
        {
            Iterator temp(*this);
            --*this;
            return temp;
        }

        /// \fn operator ==
        /// \brief Returns true if this class equals the param.
        /// \param other The object to test for equality.
        /// \returns True if this object is equal to other.
        const bool operator == (const Iterator & other) const
        {
            return _internalIterator == other._internalIterator;
        }

        /// \fn operator !=
        /// \brief Returns true if this class is not equal to  the param.
        /// \param other The object to test for equality.
        /// \returns True if this object is not equal to other.
        const bool operator != (const Iterator & other) const
        {
            return _internalIterator != other._internalIterator;
        }

        /// \fn Iterator
        /// \brief Constructs a new iterator.
        /// \param internalIterator The iterator to adapt.
        /// \return A new iterator.
        Iterator(TInternalIterator internalIterator) : _internalIterator{ internalIterator }
        { }
    };

    /// \class Iterable iterator.h "sexy/iterator.h"
    /// \brief Adapts a collection so that it iterators may return a different type when dereferenced.
    /// \tparam TItem The type to return when the iterator is dereferenced.
    /// \tparam TInternalCollection The type of collection to adapt.
    /// \tparam TInternalIteratorToItem The type of a functor which adapts the iterator.
    template <typename TItem, typename TInternalCollection, typename TInternalIteratorToItem = PassThrough<TItem>>
    class Iterable final
    {
    private:
        TInternalCollection & _internalCollection;

    public:
        /// \fn begin
        /// \brief Returns an iterator at the beginning of the collection.
        /// \return An iterator at the beginning of the collection.
        Iterator<TItem, typename TInternalCollection::iterator, TInternalIteratorToItem> begin()
        {
            return Iterator<TItem, typename TInternalCollection::iterator, TInternalIteratorToItem>{ _internalCollection.begin() };
        }

        /// \fn end
        /// \brief Returns an iterator past the end of the collection.
        /// \return An iterator past the end of the collection.
        Iterator<TItem, typename TInternalCollection::iterator, TInternalIteratorToItem> end()
        {
            return Iterator<TItem, typename TInternalCollection::iterator, TInternalIteratorToItem>{ _internalCollection.end() };
        }

        /// \fn Iterable
        /// \brief Constructs a new iterable.
        /// \param collection The collection to adapt.
        /// \return A new iterable.
        Iterable(TInternalCollection & collection) : _internalCollection{ collection }
        { }

        Iterable() = default;
    };
}

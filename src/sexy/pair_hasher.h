#pragma once

namespace sexy
{
    /// \struct PairHasher pair_hasher.h "sexy/pair_hasher.h"
    /// \brief A functor which hashes pairs.
    /// \tparam TPair The type of pair to hash.
    template <typename TPair>
    struct PairHasher
    {
        /// \fn operator ()
        /// \brief Hashes pairs.
        /// \param pair The pair to hash.
        /// \return A hash of the pair.
        const std::size_t operator () (const TPair & pair) const
        {
            return pair.first ^ pair.second;
        }
    };
}

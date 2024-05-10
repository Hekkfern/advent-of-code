#pragma once

#include <utility>

namespace utils::hash {

template <class T>
void hash_combine(std::size_t& seed, T const& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

} // namespace utils::hash

template <typename S, typename T>
struct std::hash<std::pair<S, T>> {
    std::size_t operator()(std::pair<S, T> const& v) const
    {
        std::size_t seed = 0;
        utils::hash::hash_combine(seed, v.first);
        utils::hash::hash_combine(seed, v.second);
        return seed;
    }
};

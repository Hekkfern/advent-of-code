#pragma once

#include <range/v3/algorithm/find.hpp>

namespace utils::algorithms {

template <typename T>
void remove_duplicates_without_reordering(std::vector<T>& v)
{
    auto first{v.begin()};
    auto last{v.end()};
    auto new_last{first};
    for (auto current = first; current != last; ++current) {
        if (ranges::find(first, new_last, *current) == new_last) {
            if (new_last != current) {
                *new_last = *current;
            }
            ++new_last;
        }
    }
    v.erase(new_last, v.end());
}
} // namespace utils::algorithms

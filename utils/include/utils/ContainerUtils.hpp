#pragma once

#include <algorithm>

namespace utils::ContainerUtils {

/**
 * @brief
 *
 * @tparam Iterator
 * @tparam T
 *
 * @param[in] begin
 * @param[in] end
 * @param[in] item
 *
 * @return
 */
template <typename Iterator>
bool contains(
    Iterator begin,
    Iterator end,
    const typename std::iterator_traits<Iterator>::reference item)
{
    return std::find(begin, end, item) != end;
}

} // namespace utils::ContainerUtils

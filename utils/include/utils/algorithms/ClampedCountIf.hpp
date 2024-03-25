#pragma once

#include <algorithm>
#include <iterator>
#include <ranges>

namespace utils::algorithms {

/**
 * @brief      Count the elements of a sequence for which a predicate is true,
 *             and it aborts the count if it reaches the count value @p
 *             maxCount.
 *
 * @param[in]  first     An input iterator.
 * @param[in]  last      An input iterator.
 * @param[in]  maxCount  The max count value that makes the algorithm to stop
 *                       counting.
 * @param[in]  pred      Unary predicate which returns true for the elements to
 *                       count.
 *
 * @return     Number of counted items, or @p maxCount if the counter is higher.
 */
template <class I, class S, class Pred, typename Proj = std::identity>
requires std::input_iterator<I> && std::sentinel_for<S, I> && std::
    indirect_unary_predicate<Pred, std::projected<I, Proj>>
constexpr typename std::iterator_traits<I>::difference_type clamped_count_if(
    I first,
    S last,
    typename std::iterator_traits<I>::difference_type const maxCount,
    Pred pred,
    Proj proj = Proj{})
{
    typename std::iterator_traits<I>::difference_type count{0};
    for (; first != last; ++first) {
        if (std::invoke(pred, std::invoke(proj, *first))) {
            ++count;
            if (count >= maxCount) {
                break;
            }
        }
    }
    return count;
}

/**
 * @brief      Count the elements of a sequence for which a predicate is true,
 *             and it aborts the count if it reaches the count value @p
 *             maxCount.
 *
 * @param[in]  rng       A range.
 * @param[in]  maxCount  The max count value that makes the algorithm to stop
 *                       counting.
 * @param[in]  pred      Unary predicate which returns true for the elements to
 *                       count.
 *
 * @return     Number of counted items, or @p maxCount if the counter is higher.
 */
template <class Rng, class Pred, typename Proj = std::identity>
requires std::ranges::input_range<Rng>
constexpr typename std::iterator_traits<
    std::ranges::iterator_t<Rng>>::difference_type
clamped_count_if(
    Rng&& rng,
    typename std::iterator_traits<
        std::ranges::iterator_t<Rng>>::difference_type const maxCount,
    Pred pred,
    Proj proj = Proj{})
{
    return clamped_count_if(
        std::begin(rng),
        std::end(rng),
        std::move(maxCount),
        std::move(pred),
        std::move(proj));
}

} // namespace utils::algorithms

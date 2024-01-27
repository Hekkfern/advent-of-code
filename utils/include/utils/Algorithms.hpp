#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <ranges>

namespace utils::algorithms {

/**
 * @brief      Count the elements of a sequence for which a predicate is true.
 *
 *  @param  first  An input iterator.
 *  @param  last   An input iterator.
 * @param[in]  value    The max count value that makes the algorithm to stop
 * counting.
 * @param[in]  pred     The predicate
 *
 * @tparam     InputIt  { description }
 * @tparam     T        { description }
 * @tparam     Pred     { description }
 *
 * @return     Number of until.
 */
template <class I, class S, class Pred, typename Proj = std::identity>
requires std::input_iterator<I> && std::sentinel_for<S, I> && std::
    indirect_unary_predicate<Pred, std::projected<I, Proj>>
constexpr typename std::iterator_traits<I>::difference_type count_if_until(
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

template <class Rng, class Pred, typename Proj = std::identity>
requires std::ranges::input_range<Rng>
constexpr typename std::iterator_traits<
    std::ranges::iterator_t<Rng>>::difference_type
count_if_until(
    Rng&& rng,
    typename std::iterator_traits<
        std::ranges::iterator_t<Rng>>::difference_type const maxCount,
    Pred pred,
    Proj proj = Proj{})
{
    return count_if_until(
        std::begin(rng),
        std::end(rng),
        std::move(maxCount),
        std::move(pred),
        std::move(proj));
}

} // namespace utils::algorithms

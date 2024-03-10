#pragma once

#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>

namespace utils::algorithms {

auto stepped_iota(int start, int step)
{
    return ranges::views::iota(0)
        | ranges::views::transform([start, step](int x) {
               return x * step + start;
           });
}

auto stepped_iota(int start, int end, int step)
{
    return ranges::views::iota(0, (end - start + step - 1) / step)
        | ranges::views::transform([start, step](int x) {
               return x * step + start;
           });
}

} // namespace utils::algorithms

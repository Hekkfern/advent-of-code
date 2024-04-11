#include "HashHelper.hpp"

#include <range/v3/algorithm/for_each.hpp>

namespace aoc_2023_15 {

namespace {

uint64_t calculateHash(uint64_t const initialValue, char const c)
{
    return (initialValue + static_cast<uint64_t>(c)) * 17ULL % 256ULL;
}

} // namespace

uint64_t calculateHash(std::string_view const str)
{
    uint64_t result{0ULL};
    ranges::for_each(str, [&result](char const c) -> void {
        result = calculateHash(result, c);
    });
    return result;
}

} // namespace aoc_2023_15

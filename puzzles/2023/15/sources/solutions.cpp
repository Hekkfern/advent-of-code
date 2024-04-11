#include "solutions.hpp"

#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>
#include <string_view>
#include <utils/File.hpp>

namespace aoc_2023_15 {

// ---------- Private Methods ----------

uint64_t calculateHash(uint64_t const initialValue, char const c)
{
    return (initialValue + static_cast<uint64_t>(c)) * 17ULL % 256ULL;
}

uint64_t calculateHash(std::string_view const str)
{
    uint64_t result{0ULL};
    ranges::for_each(str, [&result](char const c) -> void {
        result = calculateHash(result, c);
    });
    return result;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    std::string content{*utils::file::readFirstLine(filePath)};
    auto splitContent
        = content | ranges::views::split(',')
        | ranges::views::transform([](auto&& str_range) -> std::string_view {
              return std::string_view(
                  &*str_range.begin(), std::ranges::distance(str_range));
          });
    std::size_t accummulated{ranges::fold_left(
        splitContent,
        0ULL,
        [](uint64_t const initialValue, std::string_view const str)
            -> uint64_t { return initialValue + calculateHash(str); })};

    return std::to_string(accummulated);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_15
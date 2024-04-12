#include "solutions.hpp"

#include "HashHelper.hpp"
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>
#include <string_view>
#include <utils/File.hpp>

namespace aoc_2023_15 {

// ---------- Private Methods ----------

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    std::string const content{*utils::file::readFirstLine(filePath)};
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
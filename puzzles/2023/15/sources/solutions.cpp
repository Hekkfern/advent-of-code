#include "solutions.hpp"

#include "HashHelper.hpp"
#include "Lens.hpp"
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/transform.hpp>
#include <string_view>
#include <utils/File.hpp>
#include <utils/String.hpp>
#include <vector>

namespace aoc_2023_15 {

// ---------- Private Methods ----------

using Book = std::vector<std::vector<Lens>>;

uint64_t calculateFocusingPower(Book const& book)
{
    return ranges::fold_left(
        ranges::views::enumerate(book),
        0ULL,
        [](uint64_t const accum,
           std::pair<uint32_t, std::vector<Lens>> const& box) -> uint64_t {
            return accum
                + ranges::fold_left(
                       ranges::views::enumerate(box.second),
                       0ULL,
                       [boxIndex = box.first](
                           uint64_t const accum,
                           std::pair<uint32_t, Lens> const& lens) -> uint64_t {
                           return accum
                               + (boxIndex + 1ULL) * (lens.first + 1ULL)
                               * lens.second.getFocalLength();
                       });
        });
}

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
    std::string const content{*utils::file::readFirstLine(filePath)};
    auto splitContent
        = content | ranges::views::split(',')
        | ranges::views::transform([](auto&& str_range) -> std::string_view {
              return std::string_view(
                  &*str_range.begin(), std::ranges::distance(str_range));
          });
    Book book(256ULL);
    ranges::for_each(splitContent, [&book](std::string_view const str) -> void {
        auto const symbolPosition{str.find_first_of("=-")};
        std::string const label{str.substr(0, symbolPosition)};
        auto& box{book.at(calculateHash(label))};
        if (str[symbolPosition] == '=') {
            auto const focalLength{
                *utils::string::toNumber<uint8_t>(str[symbolPosition + 1])};
            if (auto it{ranges::find_if(
                    box,
                    [label](Lens const& lens) -> bool {
                        return lens.getLabel() == label;
                    })};
                it != box.end()) {
                it->setFocalLength(focalLength);
            } else {
                box.emplace_back(label, focalLength);
            }
        } else { // str[symbolPosition] == '-'
            std::erase_if(box, [label](Lens const& lens) -> bool {
                return lens.getLabel() == label;
            });
        }
    });
    return std::to_string(calculateFocusingPower(book));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_15
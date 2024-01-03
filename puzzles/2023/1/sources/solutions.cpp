#include "solutions.hpp"

#include <optional>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/reverse.hpp>
#include <unordered_map>
#include <utility>
#include <utils/File.hpp>

namespace aoc_2023_1 {

// ---------- Private Methods ----------

const std::unordered_map<std::string, uint32_t> NumberTextMap{
    {"one", 1U},
    {"two", 2U},
    {"three", 3U},
    {"four", 4U},
    {"five", 5U},
    {"six", 6U},
    {"seven", 7U},
    {"eight", 8U},
    {"nine", 9U}};

/**
 * @brief      ???
 *
 * @param[in]      substr        The line
 *
 * @return     { description_of_the_return_value }
 */
std::optional<uint32_t> analyzeItemInWeirdLine(std::string_view substr)
{
    /* simple digits */
    char const firstChar{substr[0]};
    if (std::isdigit(firstChar) != 0 && firstChar != '0') {
        return firstChar - '0';
    }

    /* words as digits */
    auto match{ranges::find_if(
        NumberTextMap,
        [substr](std::pair<std::string, uint32_t> const& item) -> bool {
            return substr.starts_with(item.first);
        })};
    if (match != std::cend(NumberTextMap)) {
        return match->second;
    }

    /* Nothing */
    return {};
}

/**
 * @brief      Parses a single line of the input file for the Part 1.
 *
 * @param[in]  line  A single line of text obtained from the input file.
 *
 * @return     A string with two digits.
 */
uint32_t parseSimpleLine(const std::string_view line)
{
    /**
     * @brief      Determines whether the specified character is not a digit.
     *
     * @param[in]  c     Character to check.
     *
     * @return     True if the specified character is not a digit, False
     *             otherwise.
     */
    static constexpr auto is_not_digit = [](char const c) -> bool {
        return !isdigit(c) || c == '0';
    };
    /**
     * @brief      Drops all the items at the beginning of the container until
     *             it finds a digit.
     */
    static constexpr auto first_digit = ranges::views::drop_while(is_not_digit);
    /**
     * @brief      Drops all the items at the end of the container until it
     *             finds a digit.
     */
    static constexpr auto last_digit = ranges::views::reverse | first_digit;
    /**
     * @brief      Converts the first element of a range to an integer value.
     *
     * @param      rng   The range.
     *
     * @return     Corresponding integer value.
     */
    static constexpr auto convertToNumber = [](auto&& rng) -> uint32_t {
        return *rng.begin() - '0';
    };

    return convertToNumber(line | first_digit) * 10
        + convertToNumber(line | last_digit);
}

/**
 * @brief      Parses a single line of the input file for the Part 2.
 *
 * @param[in]  line  A single line of text obtained from the input file.
 *
 * @return     A string with two digits.
 */
uint32_t parseWeirdLine(const std::string_view line)
{
    uint32_t first{0};
    uint32_t last{0};
    for (auto const pos :
         ranges::views::iota(std::begin(line), std::end(line))) {
        std::string_view substr{pos, std::end(line)};
        auto const value{analyzeItemInWeirdLine(substr)};
        if (!value) {
            continue;
        }
        if (first == 0) {
            first = *value;
        }
        last = *value;
    }
    return first * 10 + last;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint32_t value{0U};

    utils::file::parseAndIterate(
        filePath, [&value](std::string_view const line) -> void {
            value += parseSimpleLine(line);
        });

    return std::to_string(value);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    uint32_t value{0U};

    utils::file::parseAndIterate(
        filePath, [&value](std::string_view const line) -> void {
            value += parseWeirdLine(line);
        });

    return std::to_string(value);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_1

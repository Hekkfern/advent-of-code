#include "solutions.hpp"

#include <array>
#include <optional>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <unordered_map>
#include <utility>
#include <utils/File.hpp>
#include <utils/String.hpp>

namespace aoc_2023_1 {

// ---------- Private Methods ----------

const std::unordered_map<std::string, char> NumberTextMap{
    {"one", '1'},
    {"two", '2'},
    {"three", '3'},
    {"four", '4'},
    {"five", '5'},
    {"six", '6'},
    {"seven", '7'},
    {"eight", '8'},
    {"nine", '9'}};

/**
 * \brief ???
 * \param line
 * \param position aa. Value >=0.
 * \param onlyDigits
 * \return
 */
std::optional<char> analyzeItemInLine(
    std::string const& line,
    const std::size_t position,
    bool const onlyDigits = true)
{
    char const ch{line[position]};
    if (std::isdigit(ch) != 0 && ch != '0') {
        return ch;
    }
    if (!onlyDigits) {
        const std::string remainingLine{line.substr(position)};
        std::pair<std::string, char> numberMatched;
        if (ranges::any_of(
                NumberTextMap,
                [&remainingLine,
                 &numberMatched](std::pair<std::string, char> const& item) {
                    const bool isMatch{remainingLine.starts_with(item.first)};
                    if (isMatch) {
                        numberMatched = item;
                    }
                    return isMatch;
                })) {
            return numberMatched.second;
        }
    }
    return {};
}

/**
 * \brief ???
 * \param[in] line ???
 * \return The first and last digit. Otherwise, -1.
 */
std::string parseLine(std::string const& line)
{
    bool firstFound{false};
    std::array<char, 2> result{-1, -1};
    for (char const& ch : line) {
        if (std::isdigit(ch) == 0 || ch == '0') {
            continue;
        }
        if (!firstFound) {
            result[0] = ch;
            result[1] = ch;
            firstFound = true;
        }
        result[1] = ch;
    }
    return std::string{std::begin(result), std::end(result)};
}

std::string parseWeirdLine(std::string const& line)
{
    std::array<char, 2> result{-1, -1};
    std::size_t resultIndex{0};
    for (std::size_t index{0}; index < line.length();) {
        auto const analysisResult{analyzeItemInLine(line, index, false)};
        if (!analysisResult) {
            ++index;
            continue;
        }
        if (resultIndex == 0) {
            ranges::for_each(result, [value = *analysisResult](char& ch) {
                ch = value;
            });
        } else {
            result[resultIndex] = *analysisResult;
        }
        ++index;
        if (resultIndex == 0) {
            ++resultIndex;
        }
    }
    return std::string{std::begin(result), std::end(result)};
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::string const& filename)
{
    uint32_t value{0U};

    utils::file::parseAndIterate(
        filename, [&value](std::string const& line) -> void {
            auto const lineDigits{parseLine(line)};
            value += *utils::string::toNumber<uint32_t>(lineDigits);
        });

    return std::to_string(value);
}

std::string solvePart2(std::string const& filename)
{
    uint32_t value{0U};

    utils::file::parseAndIterate(
        filename, [&value](std::string const& line) -> void {
            auto const lineDigits{parseWeirdLine(line)};
            value += *utils::string::toNumber<uint32_t>(lineDigits);
        });

    return std::to_string(value);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_1
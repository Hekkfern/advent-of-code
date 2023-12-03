#include "solutions.hpp"

#include <array>
#include <fstream>
#include <utils/String.hpp>

namespace aoc_2023_1 {

// ---------- Private Methods ----------

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
        if (!std::isdigit(ch) || ch == '0') {
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

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::string const& filename)
{
    std::ifstream stream{filename};
    std::string line;
    uint32_t value{0U};

    while (std::getline(stream, line)) {
        auto const lineDigits{parseLine(line)};
        value += utils::string::toNumber<uint32_t>(lineDigits);
    }

    return std::to_string(value);
}

std::string solvePart2(std::string const& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_1
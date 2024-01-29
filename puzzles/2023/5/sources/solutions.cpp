#include "solutions.hpp"

#include "Almanac.hpp"
#include <fstream>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <sstream>
#include <utils/String.hpp>

namespace aoc_2023_5 {

// ---------- Private Methods ----------

std::unordered_map<uint32_t, uint32_t> parseMapLine(std::string const& line)
{
    std::stringstream ss{line};
    uint32_t destinationStart, sourceStart, rangeLength;
    ss >> destinationStart >> sourceStart >> rangeLength;
    std::unordered_map<uint32_t, uint32_t> map;
    
    return map;
}

Almanac parseInputFile(std::filesystem::path const& filePath) noexcept
{
    constexpr auto SpaceSeparator{" "};

    Almanac almanac;
    std::ifstream fileStream{filePath.string()};
    std::string line;

    // seeds
    std::getline(fileStream, line);
    auto seedNumbersStr{utils::string::split(
        utils::string::trim(utils::string::split(line, ":")[1]),
        SpaceSeparator)};
    almanac.seeds
        = seedNumbersStr
        | ranges::views::transform([](std::string const& str) -> uint32_t {
              return *utils::string::toNumber<uint32_t>(str);
          })
        | ranges::to<std::vector>;
    std::getline(fileStream, line); // capture empty line

    // seed-to-soil
    std::getline(fileStream, line); // capture "seed-to-soil map:"
    do {
        std::getline(fileStream, line);

    } while (!utils::string::trim(line).empty());

    return almanac;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_5
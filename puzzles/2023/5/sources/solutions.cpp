#include "solutions.hpp"

#include "Almanac.hpp"
#include <fstream>
#include <range/v3/algorithm/min_element.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <sstream>
#include <utils/String.hpp>

namespace aoc_2023_5 {

// ---------- Private Methods ----------

void parseRangeLine(RangeMap& map, std::string const& line)
{
    std::stringstream ss{line};
    uint64_t destinationStart, sourceStart, rangeLength;
    ss >> destinationStart >> sourceStart >> rangeLength;
    map.addSection(destinationStart, sourceStart, rangeLength);
}

void parseMap(std::ifstream& fileStream, RangeMap& map)
{
    std::string line;

    std::getline(fileStream, line); // capture "XXXXXXX map:"

    for (auto& res = std::getline(fileStream, line);
         res && !utils::string::trim(line).empty();
         std::getline(fileStream, line)) {
        parseRangeLine(map, line);
    }
}

std::vector<uint64_t> parseIndividualSeeds(std::ifstream& fileStream)
{
    constexpr auto SpaceSeparator{" "};

    std::string line;
    std::getline(fileStream, line);
    auto seedNumbersStr{utils::string::split(
        utils::string::trim(utils::string::split(line, ":")[1]),
        SpaceSeparator)};
    std::vector<uint64_t> seeds{
        seedNumbersStr
        | ranges::views::transform([](std::string const& str) -> uint64_t {
              return *utils::string::toNumber<uint64_t>(str);
          })
        | ranges::to<std::vector>};
    std::getline(fileStream, line); // capture empty line
    return seeds;
}

std::vector<std::pair<uint64_t, uint64_t>>
parseRangeSeeds(std::ifstream& fileStream)
{
    // todo
}

Almanac parseInputFileForPart1(std::filesystem::path const& filePath) noexcept
{

    Almanac almanac;
    std::ifstream fileStream{filePath.string()};
    std::string line;

    // seeds
    parseIndividualSeeds(fileStream);

    // seed-to-soil
    parseMap(fileStream, almanac.seed2SoilMap);
    // soil-to-fertilizer
    parseMap(fileStream, almanac.soil2FertilizerMap);
    // fertilizer-to-water
    parseMap(fileStream, almanac.fertilizer2WaterMap);
    // water-to-light
    parseMap(fileStream, almanac.water2LightMap);
    // light-to-temperature
    parseMap(fileStream, almanac.light2TemperatureMap);
    // temperature-to-humidity
    parseMap(fileStream, almanac.temperature2HumidityMap);
    // humidity-to-location
    parseMap(fileStream, almanac.humidity2LocationMap);

    return almanac;
}

Almanac parseInputFileForPart2(std::filesystem::path const& filePath) noexcept
{

    Almanac almanac;
    std::ifstream fileStream{filePath.string()};
    std::string line;

    // seeds
    almanac.seeds = parseRangeSeeds(fileStream);

    // seed-to-soil
    parseMap(fileStream, almanac.seed2SoilMap);
    // soil-to-fertilizer
    parseMap(fileStream, almanac.soil2FertilizerMap);
    // fertilizer-to-water
    parseMap(fileStream, almanac.fertilizer2WaterMap);
    // water-to-light
    parseMap(fileStream, almanac.water2LightMap);
    // light-to-temperature
    parseMap(fileStream, almanac.light2TemperatureMap);
    // temperature-to-humidity
    parseMap(fileStream, almanac.temperature2HumidityMap);
    // humidity-to-location
    parseMap(fileStream, almanac.humidity2LocationMap);

    return almanac;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const almanac{parseInputFileForPart1(filePath)};
    auto locations{
        almanac.seeds
        | ranges::views::transform(
            [&almanac = std::as_const(almanac)](uint64_t const seed) {
                return almanac.getSeedLocation(seed);
            })};
    return std::to_string(*ranges::min_element(locations));
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_5

#include "solutions.hpp"

#include "Almanac.hpp"
#include "Almanac2.hpp"
#include <fstream>
#include <range/v3/algorithm/min_element.hpp>
#include <range/v3/view/transform.hpp>
#include <sstream>
#include <utils/String.hpp>
#include <utils/interval/IntervalSet.hpp>

namespace aoc_2023_5 {

// ---------- Private Methods ----------

void parseRangeLine(RangeMap& map, std::string const& line)
{
    std::stringstream ss{line};
    int64_t destinationStart, sourceStart, rangeLength;
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

std::vector<int64_t> parseIndividualSeeds(std::ifstream& fileStream)
{
    std::string line;
    std::getline(fileStream, line); // capture "seeds: XX XX XX"

    std::stringstream ss{line};
    std::vector<int64_t> seeds;
    std::string dummy;
    ss >> dummy;
    int64_t seed;
    while (ss) {
        ss >> seed;
        seeds.emplace_back(seed);
    }

    std::getline(fileStream, line); // capture empty line
    return seeds;
}

utils::interval::IntervalSet<int64_t>
parseRangedSeeds(std::ifstream& fileStream)
{
    std::string line;
    std::getline(fileStream, line); // capture "seeds: XX XX XX"

    std::stringstream ss{line};
    std::vector<utils::interval::Interval<int64_t>> seeds;
    std::string dummy;
    ss >> dummy;
    int64_t seedStart, seedLength;
    while (ss) {
        ss >> seedStart >> seedLength;
        if (seedLength == 0) {
            continue;
        }
        seeds.emplace_back(utils::interval::Interval<int64_t>::createWithSize(
            seedStart, seedLength));
    }

    std::getline(fileStream, line); // capture empty line
    return utils::interval::IntervalSet{std::move(seeds)};
}

Almanac parseInputFileForPart1(std::filesystem::path const& filePath) noexcept
{
    Almanac almanac;
    std::ifstream fileStream{filePath.string()};
    std::string line;

    // seeds
    almanac.seeds = parseIndividualSeeds(fileStream);

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

Almanac2 parseInputFileForPart2(std::filesystem::path const& filePath) noexcept
{
    Almanac2 almanac;
    std::ifstream fileStream{filePath.string()};
    std::string line;

    // seeds
    almanac.seeds = parseRangedSeeds(fileStream);

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
            [&almanac = std::as_const(almanac)](int64_t const seed) {
                return almanac.getSeedLocation(seed);
            })};
    return std::to_string(*ranges::min_element(locations));
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const almanac{parseInputFileForPart2(filePath)};
    auto const locations{almanac.getSeedRangeLocations(almanac.seeds)};
    return std::to_string(locations.get()[0].getMin());
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_5

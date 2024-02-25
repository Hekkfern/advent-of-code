#include "solutions.hpp"

#include "Race.hpp"
#include <algorithm>
#include <fstream>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/algorithm/upper_bound.hpp>
#include <range/v3/view/iota.hpp>
#include <ranges>
#include <utils/String.hpp>
#include <vector>

namespace aoc_2023_6 {

// ---------- Private Methods ----------

std::vector<Race> parseInputForPart1(std::filesystem::path const& filePath)
{
    std::ifstream fileStream{filePath.string()};
    if (!fileStream.is_open()) {
        return {};
    }

    std::vector<Race> result;
    std::string line;
    std::string dummyStr;
    uint64_t value;
    // read times
    std::getline(fileStream, line);
    std::stringstream timesStream{line};
    timesStream >> dummyStr;
    while (timesStream >> value) {
        auto& race = result.emplace_back();
        race.time = value;
    }
    // read distances
    std::getline(fileStream, line);
    std::stringstream distancesStream{line};
    distancesStream >> dummyStr;
    uint64_t i{0U};
    while (distancesStream >> value) {
        result[i].distance = value;
        ++i;
    }

    return result;
}

Race parseInputForPart2(std::filesystem::path const& filePath)
{
    std::ifstream fileStream{filePath.string()};
    if (!fileStream.is_open()) {
        return {};
    }

    std::vector<Race> result;
    std::string line;
    std::string dummyStr;
    std::string value;
    Race race{};
    // read time
    std::getline(fileStream, line);
    std::stringstream timesStream{line};
    timesStream >> dummyStr;
    std::string timeStr;
    while (timesStream >> value) {
        timeStr += value;
    }
    race.time = *utils::string::toNumber<uint64_t>(timeStr);
    // read distance
    std::getline(fileStream, line);
    std::stringstream distancesStream{line};
    distancesStream >> dummyStr;
    std::string distanceStr;
    while (distancesStream >> value) {
        distanceStr += value;
    }
    race.distance = *utils::string::toNumber<uint64_t>(distanceStr);

    return race;
}

uint64_t
calculateDistance(uint64_t const totalTime, uint64_t const pressButtonTime)
{
    return (totalTime - pressButtonTime) * pressButtonTime;
}

uint64_t countRaceWins(Race const& race)
{
    // find first index that wins
    auto firstWinIt{std::ranges::upper_bound(
        std::ranges::iota_view(1ULL, race.time),
        race.distance,
        [&race](uint32_t value, uint32_t const item) {
            return calculateDistance(race.time, item) > value;
        })};
    if (*firstWinIt == race.time) {
        return 0ULL;
    }
    // find last index that wins
    auto lastWinIt{std::ranges::upper_bound(
        std::ranges::iota_view(1ULL, race.time) | std::views::reverse,
        race.distance,
        [&race](uint32_t value, uint32_t const item) {
            return calculateDistance(race.time, item) > value;
        })};
    if (*lastWinIt == race.time) {
        return 0ULL;
    }
    uint64_t const result{*lastWinIt - *firstWinIt + 1ULL};
    return result;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const input{parseInputForPart1(filePath)};
    uint64_t const result{ranges::fold_left(
        input, 1ULL, [](uint64_t const accum, Race const& race) -> uint64_t {
            return accum * countRaceWins(race);
        })};
    return std::to_string(result);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const race{parseInputForPart2(filePath)};
    return std::to_string(countRaceWins(race));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_6
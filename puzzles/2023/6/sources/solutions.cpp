#include "solutions.hpp"

#include "Race.hpp"
#include <cmath>
#include <fstream>
#include <range/v3/algorithm/fold_left.hpp>
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

bool isExactDouble(double const value)
{
    return std::fmod(value, 1) < std::numeric_limits<double>::epsilon()
        && std::fmod(value, 1) > -std::numeric_limits<double>::epsilon();
}

uint64_t countRaceWins(Race const& race)
{
    // find first index that wins
    double const raceTime{static_cast<double>(race.time)};
    double const raceDistance{static_cast<double>(race.distance)};
    double const firstWinD{
        (raceTime - std::sqrt((raceTime * raceTime) - (4.0 * raceDistance)))
        / 2.0};
    // find last index that wins
    double const lastWinD{
        (raceTime + std::sqrt((raceTime * raceTime) - (4.0 * raceDistance)))
        / 2.0};

    auto const lastIndex = isExactDouble(lastWinD)
        ? static_cast<uint64_t>(lastWinD - 1.0)
        : static_cast<uint64_t>(std::floor(lastWinD));
    auto const firstIndex = isExactDouble(lastWinD)
        ? static_cast<uint64_t>(firstWinD + 1.0)
        : static_cast<uint64_t>(std::ceil(firstWinD));
    return lastIndex - firstIndex + 1ULL;
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
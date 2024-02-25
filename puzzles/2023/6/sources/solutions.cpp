#include "solutions.hpp"

#include "Race.hpp"
#include <fstream>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/view/iota.hpp>
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
    uint64_t winCounter{0ULL};
    for (uint64_t i : ranges::views::iota(1ULL, race.time)) {
        if (calculateDistance(race.time, i) > race.distance) {
            ++winCounter;
        }
    }
    return winCounter;
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
#include "solutions.hpp"

#include "Game.h"
#include <cstdint>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <regex>
#include <utils/File.hpp>
#include <utils/String.hpp>

namespace aoc_2023_2 {

// ---------- Private Methods ----------

Game parseInputLine(std::string_view const line) noexcept
{
    static constexpr auto IdSeparator{":"};
    static constexpr auto SpaceSeparator{" "};
    static constexpr auto RoundSeparator{";"};
    static constexpr auto ColorSeparator{","};

    Game game;

    // split gameid from rounds
    auto parts{utils::string::split(line, IdSeparator)};

    // extract Game Id
    game.gameId = *utils::string::toNumber<GameId>(
        utils::string::split(parts[0], SpaceSeparator)[1]);

    // extract rounds
    std::string roundsLine{utils::string::trim(parts[1])};
    auto rounds{utils::string::split(roundsLine, RoundSeparator)};
    for (auto const& round : rounds) {
        GameRound gameRound;
        auto colors{
            utils::string::split(utils::string::trim(round), ColorSeparator)};
        for (auto const& color : colors) {
            auto colorItems{utils::string::split(
                utils::string::trim(color), SpaceSeparator)};
            std::string colorKey{utils::string::trim(colorItems[1])};
            if (colorKey == "green") {
                gameRound.numGreenBalls = *utils::string::toNumber<uint32_t>(
                    colorItems[0]);
            } else if (colorKey == "red") {
                gameRound.numRedBalls = *utils::string::toNumber<uint32_t>(
                    colorItems[0]);
            } else if (colorKey == "blue") {
                gameRound.numBlueBalls = *utils::string::toNumber<uint32_t>(
                    colorItems[0]);
            }
        }
        game.rounds.emplace_back(gameRound);
    }

    return game;
}

bool isGamePossible(Game const& game) noexcept
{
    static constexpr uint32_t MaxNumGreenBalls{13U};
    static constexpr uint32_t MaxNumRedBalls{12U};
    static constexpr uint32_t MaxNumBlueBalls{14U};

    return ranges::all_of(game.rounds, [](GameRound const& round) -> bool {
        return round.numGreenBalls <= MaxNumGreenBalls
            && round.numRedBalls <= MaxNumRedBalls
            && round.numBlueBalls <= MaxNumBlueBalls;
    });
}

void setMaxNumBalls(uint32_t& currentMinBalls, uint32_t const candidateMinBalls)
{
    currentMinBalls = std::max(currentMinBalls, candidateMinBalls);
}

uint32_t calculateMinPower(Game const& game) noexcept
{
    uint32_t maxGreenBalls{0U};
    uint32_t maxRedBalls{0U};
    uint32_t maxBlueBalls{0U};

    ranges::for_each(
        game.rounds,
        [&maxGreenBalls, &maxRedBalls, &maxBlueBalls](
            GameRound const& round) -> void {
            setMaxNumBalls(maxGreenBalls, round.numGreenBalls);
            setMaxNumBalls(maxRedBalls, round.numRedBalls);
            setMaxNumBalls(maxBlueBalls, round.numBlueBalls);
        });

    return maxGreenBalls * maxRedBalls * maxBlueBalls;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint32_t accumGameIds{0U};

    utils::file::parseAndIterate(
        filePath, [&accumGameIds](std::string_view const line) -> void {
            auto const game{parseInputLine(line)};
            if (isGamePossible(game)) {
                accumGameIds += game.gameId;
            }
        });

    return std::to_string(accumGameIds);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    uint32_t accumPower{0U};

    utils::file::parseAndIterate(
        filePath, [&accumPower](std::string_view const line) -> void {
            auto const game{parseInputLine(line)};
            accumPower += calculateMinPower(game);
        });

    return std::to_string(accumPower);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_2
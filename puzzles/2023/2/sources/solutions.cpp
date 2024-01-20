#include "solutions.hpp"

#include "Game.h"
#include <regex>
#include <utils/File.hpp>
#include <utils/String.hpp>

namespace aoc_2023_2 {

// ---------- Private Methods ----------

Game parseInputLine(std::string_view const line)
{
    constexpr auto IdSeparator{":"};
    constexpr auto SpaceSeparator{" "};
    constexpr auto RoundSeparator{";"};

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
        // TODO
    }

    return game;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint32_t accumGameIds{0U};

    utils::file::parseAndIterate(
        filePath, [&accumGameIds](std::string_view const line) -> void {
            auto game{parseInputLine(line)};
            if (game.isPossible()) {
                accumGameIds += game.gameId;
            }
        });

    return std::to_string(accumGameIds);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_2
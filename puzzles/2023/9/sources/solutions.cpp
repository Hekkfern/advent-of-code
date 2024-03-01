#include "solutions.hpp"

#include "History.hpp"
#include <iterator>
#include <sstream>
#include <utils/File.hpp>

namespace aoc_2023_9 {

// ---------- Private Methods ----------

History parseInputLine(std::string_view const line) noexcept
{
    std::stringstream ss{std::string{line}};
    std::vector<int64_t> values(
        std::istream_iterator<int64_t>(ss), std::istream_iterator<int64_t>());
    return History{std::move(values)};
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    int64_t accumNextValues{0LL};

    utils::file::parseAndIterate(
        filePath, [&accumNextValues](std::string_view const line) -> void {
            auto const history{parseInputLine(line)};
            accumNextValues += history.extrapolateRight();
        });

    return std::to_string(accumNextValues);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    int64_t accumNextValues{0LL};

    utils::file::parseAndIterate(
        filePath, [&accumNextValues](std::string_view const line) -> void {
            auto const history{parseInputLine(line)};
            accumNextValues += history.extrapolateLeft();
        });

    return std::to_string(accumNextValues);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_9

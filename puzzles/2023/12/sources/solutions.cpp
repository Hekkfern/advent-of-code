#include "solutions.hpp"

#include "Record.hpp"
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <sstream>
#include <utils/File.hpp>
#include <utils/String.hpp>

namespace aoc_2023_12 {

// ---------- Private Methods ----------

Record parseInputLine(std::string_view const line)
{
    std::stringstream ss{std::string{line}};
    std::string springsStr;
    std::string contiguousInfoStr;
    ss >> springsStr >> contiguousInfoStr;
    std::vector<std::string> contiguousInfoSplitStr{
        utils::string::split(contiguousInfoStr, ",")};
    std::vector<int32_t> contiguousInfo{
        contiguousInfoSplitStr
        | ranges::views::transform([](std::string const& str) -> int32_t {
              return *utils::string::toNumber<int32_t>(str);
          })
        | ranges::to<std::vector>};
    return Record{std::move(springsStr), std::move(contiguousInfo)};
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint64_t accumNumSolutions{0ULL};
    utils::file::parseAndIterate(
        filePath, [&accumNumSolutions](std::string_view const line) -> void {
            Record record{parseInputLine(line)};
            accumNumSolutions += record.solveOriginal();
        });
    return std::to_string(accumNumSolutions);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    uint64_t accumNumSolutions{0ULL};
    utils::file::parseAndIterate(
        filePath, [&accumNumSolutions](std::string_view const line) -> void {
            Record record{parseInputLine(line)};
            accumNumSolutions += record.solveUnfolded();
        });
    return std::to_string(accumNumSolutions);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_12

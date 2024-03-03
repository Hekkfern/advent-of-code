#include "solutions.hpp"

#include "Record.hpp"
#include "Spring.hpp"
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
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
    std::vector<Spring> springs{
        springsStr | ranges::view::transform([](char const c) -> Spring {
            return Spring(c);
        })
        | ranges::to<std::vector>};
    std::vector<std::string> contiguousInfoSplitStr{
        utils::string::split(contiguousInfoStr, ",")};
    std::vector<int32_t> contiguousInfo{
        contiguousInfoSplitStr
        | ranges::view::transform([](std::string const& str) -> int32_t {
              return *utils::string::toNumber<int32_t>(str);
          })
        | ranges::to<std::vector>};
    return Record{std::move(springs), std::move(contiguousInfo)};
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    uint64_t accumNumSolutions{0ULL};
    utils::file::parseAndIterate(
        filePath, [](std::string_view const line) -> void {
            /* parse line */
            Record record{parseInputLine(line)};
            // TODO
        });
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_12
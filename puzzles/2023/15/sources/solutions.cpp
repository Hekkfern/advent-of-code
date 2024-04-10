#include "solutions.hpp"

#include <fstream>
#include <range/v3/algorithm/fold_left.hpp>
#include <string_view>

namespace aoc_2023_15 {

// ---------- Private Methods ----------

uint64_t calculateHash(uint64_t initialValue, char const c)
{
    return (initialValue + static_cast<uint64_t>(c)) * 17ULL % 256ULL;
}

uint64_t calculateHash(std::string_view const str)
{
    return ranges::fold_left(
        str, 0ULL, [](uint64_t const initialValue, char const c) {
            return calculateHash(initialValue, c);
        });
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    std::ifstream fin(filePath);
    std::size_t accummulated{ranges::fold_left(
        std::istreambuf_iterator{fin}, std::istreambuf_iterator{}, []() {})};

    return std::to_string(accummulated);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_15
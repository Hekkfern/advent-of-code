#include "solutions.hpp"

#include <fstream>
#include <range/v3/
#include <range/v3/algorithm/fold_left.hpp>

namespace aoc_2023_15 {

// ---------- Private Methods ----------

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    std::ifstream fin(filePath);
    std::size_t accummulated{ranges::fold_left(std::istreambuf_iterator{fin},std::istreambuf_iterator{}, [](){})};


    return std::to_string(accummulated);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_15
#pragma once

#include <string>
#include <vector>

namespace aoc_2023_13 {

class Pattern {
public:
    explicit Pattern(std::vector<std::string>&& data)
        : mData{data} {}

private:
    std::vector<std::string> mData;
};

} // namespace aoc_2023_13

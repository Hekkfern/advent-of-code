#pragma once

#include <array>
#include <string>
#include <utility>
#include "Instruction.hpp"

namespace aoc_2023_8 {

class NetworkNode {
public:
    NetworkNode(std::array<std::string, 2> nextNodes);

    std::string navigate(const Instruction instruction);
private:
    std::array<std::string, 2> mNextNodes;
};

} // namespace aoc_2023_8

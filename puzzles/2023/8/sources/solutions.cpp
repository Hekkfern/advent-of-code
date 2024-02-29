#include "solutions.hpp"

#include "Map.hpp"
#include <cassert>
#include <fstream>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>

namespace aoc_2023_8 {

// ---------- Private Methods ----------

Map parseInput(std::filesystem::path const& filePath)
{
    Map map;

    std::ifstream fileStream{filePath.string()};
    if (!fileStream.is_open()) {
        return {};
    }

    std::string line;
    std::getline(fileStream, line); // read instructions
    auto instructions{
        line | ranges::views::transform([](char const c) -> Instruction {
            switch (c) {
            case 'L':
                return Instruction::Left;
            case 'R':
                return Instruction::Right;
            default:
                assert(false);
                return {};
            }
        })
        | ranges::to<std::vector>};
    map.addInstructions(std::move(instructions));
    std::getline(fileStream, line); // empty line

    while (std::getline(fileStream, line)) {
        std::stringstream ss{line};
        std::string nodeId, dummy, firstNode, secondNode;
        ss >> nodeId >> dummy >> firstNode >> secondNode;
        NetworkNode networkNode{
            firstNode.substr(1, 3), secondNode.substr(0, 3)};
        map.addNode(std::move(nodeId), std::move(networkNode));
    }

    return map;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto const map{parseInput(filePath)};
    return std::to_string(map.navigateFromAAAToZZZ());
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto const map{parseInput(filePath)};
    return std::to_string(map.navigateFromAllXXAToAllXXZ());
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_8

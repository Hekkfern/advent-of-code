#include "solutions.hpp"

#include "Valve.hpp"
#include <fstream>
#include <regex>
#include <utils/String.hpp>
#include <utils/graph/Graph.hpp>

using namespace utils::graph;

namespace aoc_2022_16 {

// ---------- Private Methods ----------

static constexpr uint32_t TimeToOpenAValve{1U};
static constexpr uint32_t TimeToMoveToNextValve{1U};

struct ParsedValve {
    std::string mName;
    uint32_t mFlowRate;
    std::vector<std::string> mNeighborNames;
};

ParsedValve parseInputLine(const std::string& line)
{
    std::smatch regexResult;
    constexpr auto Pattern{
        R"(Valve ([A-Z]{2} has flow rate=([0-9]+); tunnel(?:s?) lead(?:s?) to valve(?:s?) ([A-Z, ]+)))"};
    if (!std::regex_match(line, regexResult, std::regex(Pattern))) {
        throw std::logic_error("Regex failed in parsing the line");
    }
    return ParsedValve{
        std::string{regexResult[1]},
        utils::string::toNumber<uint32_t>(regexResult[2]),
        std::vector<std::string>{{regexResult[3]}}};
}

std::vector<ParsedValve> parseInput(std::ifstream& fileStream)
{
    std::string line;
    std::vector<ParsedValve> parsedValves;
    while (std::getline(fileStream, line)) {
        parsedValves.emplace_back(parseInputLine(line));
    }

    return parsedValves;
}

Graph<Valve, uint32_t> buildGraph(std::vector<ParsedValve>&& parsedValves)
{
    Graph<Valve, uint32_t> graph;
    // add vertices
    for (const auto& parsedValve : parsedValves) {
        graph.addVertex(
            std::string{parsedValve.mName},
            Valve{parsedValve.mName, parsedValve.mFlowRate});
    }
    // add edges
    for (const auto& parsedValve : parsedValves) {
        for (const auto& neighborName : parsedValve.mNeighborNames) {
            graph.addUndirectedEdge(parsedValve.mName, neighborName, 1U);
        }
    }
    return graph;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{filename};
    auto graph{buildGraph(parseInput(fileStream))};
    uint32_t timeCounter{0U};
    auto startingValve{graph.getVertex("AA")};

    return std::to_string(1);
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_16

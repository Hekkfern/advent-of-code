#include "solutions.hpp"

#include "Valve.hpp"
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <unordered_set>
#include <utils/String.hpp>
#include <utils/graph/Algorithms.hpp>
#include <utils/graph/Graph.hpp>
#include <vector>

using namespace utils::graph;

namespace aoc_2022_16 {

// ---------- Private Methods ----------

constexpr uint32_t TimeToOpenAValve{1U};
constexpr uint32_t TimeToMoveToNextValve{1U};
constexpr uint32_t TotalTime{30U};

struct ParsedValve {
    std::string mName;
    uint32_t mFlowRate;
    std::vector<std::string> mNeighborNames;
};

ParsedValve parseInputLine(const std::string& line)
{
    // parse line
    std::smatch lineRegexResult;
    const std::regex LinePattern{
        R"(Valve ([A-Z]{2}) has flow rate=([0-9]+); tunnel(?:s?) lead(?:s?) to valve(?:s?) ([A-Z, ]+))"};
    if (!std::regex_match(line, lineRegexResult, LinePattern)) {
        throw std::logic_error("Regex failed in parsing the line");
    }
    // parse neighbors inside line
    std::regex_token_iterator<std::string::iterator> rend;
    const std::regex NeighborPattern{R"([A-Z]{2})"};
    std::string neighborString{lineRegexResult[3]};
    std::regex_token_iterator<std::string::iterator> matchIt{
        std::begin(neighborString), std::end(neighborString), NeighborPattern};
    std::vector<std::string> neighborNames;
    while (matchIt != rend) {
        neighborNames.emplace_back(*matchIt++);
    }
    return ParsedValve{
        std::string{lineRegexResult[1]},
        utils::string::toNumber<uint32_t>(lineRegexResult[2]),
        std::move(neighborNames)};
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
            graph.addUndirectedEdge(
                parsedValve.mName, neighborName, TimeToMoveToNextValve);
        }
    }
    // look for shortest paths between vertices
    graph = applyFloydWarshall(graph);
    // delete all the vertex with zero flowrate (except "AA")
    graph.removeVertexIf([](const Vertex<Valve, uint32_t>& vertex) -> bool {
        return vertex.getName() != "AA" && vertex.getInfo().getFlowRate() == 0U;
    });
    return graph;
}

uint32_t calculateEventualPressureRelease(
    const uint32_t currentPressure,
    const uint32_t flowRate,
    const uint32_t time)
{
    return currentPressure + flowRate * (TotalTime - time);
}

uint32_t analyzeValve(
    const Graph<Valve, uint32_t>& graph,
    const Vertex<Valve, uint32_t>& thisVertex,
    const uint32_t time,
    const uint32_t totalPressure,
    std::unordered_set<std::string>& openValves)
{
    uint32_t maxTotalPressure{totalPressure};
    uint32_t newTime{time};
    // open valve
    if (thisVertex.getInfo().getFlowRate() != 0U) {
        maxTotalPressure = calculateEventualPressureRelease(
            totalPressure, thisVertex.getInfo().getFlowRate(), time);
        newTime += TimeToOpenAValve;
    }
    openValves.emplace(thisVertex.getName());

    // try to open more valves
    for (auto& [nextVertexName, nextVertex] : graph.getVertices()) {
        // moving to this valve is useless, as it is already open
        if (openValves.contains(nextVertexName)) {
            continue;
        }
        // calculate time to move to this valve
        const uint32_t timeToGoToNextValve{
            thisVertex.getEdges().at(nextVertexName).getWeight()};
        // moving to this valve and opening it would take
        // more time than we have
        if (newTime + timeToGoToNextValve >= TotalTime) {
            continue;
        }
        // recurse with this valve open. if it is an improvement, remember
        const uint32_t candidateTotalPressure{analyzeValve(
            graph,
            nextVertex,
            time + timeToGoToNextValve,
            maxTotalPressure,
            openValves)};
        maxTotalPressure = std::max(maxTotalPressure, candidateTotalPressure);
    }
    openValves.erase(thisVertex.getName());
    return maxTotalPressure;
}

uint32_t searchMaximumFlowPath(const Graph<Valve, uint32_t>& graph)
{
    std::unordered_set<std::string> openValves;
    auto& startingValve{graph.getVertex("AA")};
    return analyzeValve(graph, startingValve, 0U, 0U, openValves);
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::ifstream fileStream{filename};
    const auto globalGraph{buildGraph(parseInput(fileStream))};
    const auto pressure{searchMaximumFlowPath(globalGraph)};
    return std::to_string(pressure);
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_16

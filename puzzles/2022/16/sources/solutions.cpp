#include "solutions.hpp"

#include "Valve.hpp"
#include <fstream>
#include <regex>
#include <unordered_set>
#include <utils/String.hpp>
#include <utils/graph/Algorithms.hpp>
#include <utils/graph/Graph.hpp>

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
            graph.addUndirectedEdge(
                parsedValve.mName, neighborName, TimeToMoveToNextValve);
        }
    }
    // look for shortest paths between vertices
    graph = applyFloydWarshall(graph);
    // delete all the vertex with zero flowrate (except "AA")
    for (auto& [vertexName, vertexItem] : graph.getVertices()) {
        if (vertexName != "AA" && vertexItem.getInfo().getFlowRate() == 0U) {
            graph.removeVertex(vertexName);
        }
    }
    return graph;
}

uint32_t calculateTotalPressureWhenValveOpens(
    const uint32_t currentPressure,
    const uint32_t flowRate,
    const uint32_t time)
{
    return currentPressure + flowRate * (TotalTime - time);
}

uint32_t analyzeValve(
    const Graph<Valve, uint32_t>& graph,
    const Vertex<Valve, uint32_t>& valve,
    uint32_t currentTime,
    uint32_t currentPressure,
    std::unordered_set<std::string>& openValves)
{
    uint32_t maxTotalPressure{};

    // try to open more valves
    for (auto& next : graph.getVertices()) {
        // moving to this valve is useless, as it is already open
        if (openValves.contains(valve.getName())) {
            continue;
        }
        uint32_t timeToGoToNextValve{valve.getEdges(). + 1};
        // moving to this valve and opening it would take
        // more time than we have
        if (currentTime + timeToGoToNextValve >= TotalTime) {
            continue;
        }
        // the flow as we move to the next valve and open it
        int64_t new_total = total + time_delta * get_flow(open);
        open.insert(next);
        // recurse with this valve open, if it is an improvement, remember
        int64_t value = dfs(next, time + time_delta, new_total, open);
        maxTotalPressure = std::max(maxTotalPressure, value);
        open.erase(next);
    }
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

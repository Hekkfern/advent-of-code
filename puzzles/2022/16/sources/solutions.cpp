#include "solutions.hpp"

#include "Valve.hpp"
#include <fstream>
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
constexpr uint32_t TotalTimeWithoutElephant{30U};
constexpr uint32_t TotalTimeWithElephant{TotalTimeWithoutElephant - 4U};

struct ParsedValve {
    std::string mName;
    uint32_t mFlowRate;
    std::vector<std::string> mNeighborNames;
};

ParsedValve parseInputLine(std::string const& line)
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
    for (auto const& parsedValve : parsedValves) {
        graph.addVertex(
            std::string{parsedValve.mName},
            Valve{parsedValve.mName, parsedValve.mFlowRate});
    }
    // add edges
    for (auto const& parsedValve : parsedValves) {
        for (auto const& neighborName : parsedValve.mNeighborNames) {
            graph.addUndirectedEdge(
                parsedValve.mName, neighborName, TimeToMoveToNextValve);
        }
    }
    // look for shortest paths between vertices
    graph = applyFloydWarshall(graph);
    // delete all the vertex with zero flowrate (except "AA")
    graph.removeVertexIf([](Vertex<Valve, uint32_t> const& vertex) -> bool {
        return vertex.getName() != "AA" && vertex.getInfo().getFlowRate() == 0U;
    });
    return graph;
}

uint32_t calculateEventualPressureRelease(
    const uint32_t currentPressure,
    const uint32_t flowRate,
    const uint32_t totalTime,
    const uint32_t time)
{
    return currentPressure + flowRate * (totalTime - time);
}

/**
 * @brief      Generates the list of names of the "useful" valves, i.e, the ones
 *             with non-zero flow.
 *
 * @param[in]  graph  The graph to get the valve names from.
 *
 * @return     { description_of_the_return_value }
 */
std::unordered_set<std::string>
generateValveNameList(Graph<Valve, uint32_t> const& graph)
{
    std::unordered_set<std::string> usefulValves;
    usefulValves.reserve(graph.getVertices().size());
    for (auto const& vertex : graph.getVertices()) {
        if (vertex.second.getInfo().getFlowRate() > 0U) {
            usefulValves.emplace(vertex.second.getName());
        }
    }
    return usefulValves;
}

/**
 * @brief      { function_description }
 *
 * @warning    Recursive method.
 *
 * @param[in]  graph            The graph.
 * @param[in]  currentValve     The current valve name.
 * @param[in]  time             The current time.
 * @param[in]  totalTime        The total available time.
 * @param[in]  totalPressure    The total pressure released so far.
 * @param[in]  availableValves  The list of valves which can be opened and whose
 *                              flow is not zero.
 *
 * @return     The maximum possible releasable pressure found so far.
 */
uint32_t analyzeValveAlone(
    Graph<Valve, uint32_t> const& graph,
    std::string const& currentValve,
    const uint32_t time,
    const uint32_t totalTime,
    const uint32_t totalPressure,
    std::unordered_set<std::string>& openedValves,
    std::unordered_set<std::string>& availableValves)
{
    uint32_t newTotalPressure{totalPressure};
    uint32_t newTime{time};
    auto& thisVertex{graph.getVertex(currentValve)};
    // open valve
    if (thisVertex.getInfo().getFlowRate() != 0U) {
        newTime += TimeToOpenAValve;
        newTotalPressure = calculateEventualPressureRelease(
            totalPressure,
            thisVertex.getInfo().getFlowRate(),
            totalTime,
            newTime);
    }
    openedValves.emplace(thisVertex.getName());
    // try to open more valves
    uint32_t maxTotalPressure{newTotalPressure};
    for (auto& nextVertexName : availableValves) {
        // moving to this valve is useless, as it is already open
        if (openedValves.contains(nextVertexName)) {
            continue;
        }
        // calculate time to move to this valve
        const uint32_t timeToGoToNextValve{
            thisVertex.getEdges().at(nextVertexName).getWeight()};
        // moving to this valve and opening it would take
        // more time than we have
        if (newTime + timeToGoToNextValve >= totalTime) {
            continue;
        }
        // recurse with this valve open. if it is an improvement, remember
        const uint32_t candidateTotalPressure{analyzeValveAlone(
            graph,
            nextVertexName,
            newTime + timeToGoToNextValve,
            totalTime,
            newTotalPressure,
            openedValves,
            availableValves)};
        maxTotalPressure = std::max(maxTotalPressure, candidateTotalPressure);
    }
    openedValves.erase(thisVertex.getName());
    return maxTotalPressure;
}

/**
 * @brief      { function_description }
 *
 * @param[in]  graph  The graph.
 *
 * @return     { description_of_the_return_value }
 */
uint32_t searchMaximumFlowPathAlone(Graph<Valve, uint32_t> const& graph)
{
    std::unordered_set<std::string> openedValves;
    std::unordered_set<std::string> availableValves{
        generateValveNameList(graph)};
    return analyzeValveAlone(
        graph,
        "AA",
        0U,
        TotalTimeWithoutElephant,
        0U,
        openedValves,
        availableValves);
}

/**
 * @brief      { function_description }
 *
 * @warning    Recursive method.
 *
 * @param[in]  graph            The graph.
 * @param[in]  currentValve     The current valve name.
 * @param[in]  time             The current time.
 * @param[in]  totalTime        The total available time.
 * @param[in]  totalPressure    The total pressure released so far.
 * @param[in]  availableValves  The list of valves which can be opened and whose
 *                              flow is not zero.
 *
 * @return     The maximum possible releasable pressure found so far.
 */
uint32_t analyzeValveWithElephant(
    Graph<Valve, uint32_t> const& graph,
    std::string const& currentValve,
    const uint32_t time,
    const uint32_t totalTime,
    const uint32_t totalPressure,
    std::unordered_set<std::string>& openedValves,
    std::unordered_set<std::string>& availableValves)
{
    uint32_t newTotalPressure{totalPressure};
    uint32_t newTime{time};
    auto& thisVertex{graph.getVertex(currentValve)};
    // open valve
    if (thisVertex.getInfo().getFlowRate() != 0U) {
        newTime += TimeToOpenAValve;
        newTotalPressure = calculateEventualPressureRelease(
            totalPressure,
            thisVertex.getInfo().getFlowRate(),
            totalTime,
            newTime);
    }
    availableValves.erase(thisVertex.getName());

    /* Let the elephant run around from "AA" at time zero */
    /* This maximum represents the case when we do not open any more valves,
     * but we let the elephant run around. */
    std::unordered_set<std::string> elephantAvailableValves{availableValves};
    for (auto& v : openedValves) {
        elephantAvailableValves.erase(v);
    }
    std::unordered_set<std::string> elephantOpenedValves;
    const uint32_t maxElephantTotalPressure{analyzeValveAlone(
        graph,
        "AA",
        0U,
        totalTime,
        0U,
        elephantOpenedValves,
        elephantAvailableValves)};

    /* Let's forget the elephant and try to get a better flow by opening more
     * valves. */
    uint32_t maxTotalPressure{newTotalPressure + maxElephantTotalPressure};
    for (auto& nextVertexName : availableValves) {
        // moving to this valve is useless, as it is already open
        if (openedValves.contains(nextVertexName)) {
            continue;
        }
        // calculate time to move to this valve
        const uint32_t timeToGoToNextValve{
            thisVertex.getEdges().at(nextVertexName).getWeight()};
        // moving to this valve and opening it would take
        // more time than we have
        if (newTime + timeToGoToNextValve >= totalTime) {
            continue;
        }
        // recurse with this valve open. if it is an improvement, remember
        const uint32_t candidateTotalPressure{analyzeValveWithElephant(
            graph,
            nextVertexName,
            newTime + timeToGoToNextValve,
            totalTime,
            newTotalPressure,
            openedValves,
            availableValves)};
        maxTotalPressure = std::max(maxTotalPressure, candidateTotalPressure);
    }
    availableValves.emplace(thisVertex.getName());
    return maxTotalPressure;
}

/**
 * @brief      { function_description }
 *
 * @param[in]  graph  The graph.
 *
 * @return     { description_of_the_return_value }
 */
uint32_t searchMaximumFlowPathWithElephant(Graph<Valve, uint32_t> const& graph)
{
    std::unordered_set<std::string> openedValves;
    std::unordered_set<std::string> availableValves{
        generateValveNameList(graph)};
    return analyzeValveWithElephant(
        graph,
        "AA",
        0U,
        TotalTimeWithElephant,
        0U,
        openedValves,
        availableValves);
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::string const& filename)
{
    std::ifstream fileStream{filename};
    auto const globalGraph{buildGraph(parseInput(fileStream))};
    auto const pressure{searchMaximumFlowPathAlone(globalGraph)};
    return std::to_string(pressure);
}

std::string solvePart2(std::string const& filename)
{
    std::ifstream fileStream{filename};
    auto const globalGraph{buildGraph(parseInput(fileStream))};
    auto const pressure{searchMaximumFlowPathWithElephant(globalGraph)};
    return std::to_string(pressure);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_16

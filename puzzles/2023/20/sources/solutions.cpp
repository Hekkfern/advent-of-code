#include "solutions.hpp"

#include "Broadcaster.hpp"
#include "Conjunction.hpp"
#include "FlipFlop.hpp"
#include "IModule.hpp"
#include "Mesh.h"
#include "utils/extensions/ContainerTools.h"
#include <memory>
#include <numeric>
#include <queue>
#include <range/v3/algorithm/fold_left.hpp>
#include <range/v3/view/map.hpp>
#include <utils/File.hpp>
#include <utils/String.hpp>

namespace aoc_2023_20 {

// ---------- Private Methods ----------

/**
 * @brief Parse the destinations of a module.
 *
 * @param line
 * @return std::vector<std::string>
 */
[[nodiscard]] std::vector<std::string>
parseDestinations(std::string_view const line)
{
    std::vector<std::string> destinations;

    // Find the position of "->"
    auto pos = line.find("->");
    if (pos == std::string_view::npos) {
        return {}; // No "->" found, return empty list
    }

    // Extract the part after "->"
    auto destinationPart = line.substr(pos + 3);

    return utils::string::split(destinationPart, ", ");
}

/**
 * @brief Parse a line and create the corresponding module. Then, it is added to
 * the mesh.
 */
void parseLine(Mesh& mesh, std::string_view const line)
{
    /* check first char to know the module type */
    switch (line[0]) {
    case '%': {
        /* it is a flip-flop */
        std::string name{line.substr(1, line.find(' ') - 1)};
        FlipFlop module{name};
        for (auto const& destination : parseDestinations(line)) {
            module.addDestination(destination);
        }
        mesh.addModule<FlipFlop>(std::move(module));
        break;
    }
    case '&': {
        /* it is a conjunction */
        std::string name{line.substr(1, line.find(' ') - 1)};
        Conjunction module{name};
        for (auto const& destination : parseDestinations(line)) {
            module.addDestination(destination);
        }
        mesh.addModule<Conjunction>(std::move(module));
        break;
    }
    default: {
        /* it is a broadcaster */
        Broadcaster module;
        for (auto const& destination : parseDestinations(line)) {
            module.addDestination(destination);
        }
        mesh.addModule<Broadcaster>(std::move(module));
        break;
    }
    }
}

/**
 *
 * @param filePath
 * @return
 */
[[nodiscard]] Mesh parseInput(std::filesystem::path const& filePath) noexcept
{
    Mesh mesh;
    /* parse the file */
    bool const result{utils::file::parseAndIterate(
        filePath, [&mesh](std::string_view const line) -> void {
            parseLine(mesh, line);
        })};
    if (!result) {
        return {};
    }
    /* set up the mesh */
    mesh.setup();
    return mesh;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto mesh{parseInput(filePath)};
    uint64_t lowPulses{0U};
    uint64_t highPulses{0U};
    for (uint32_t i = 0U; i < 1000U; ++i) {
        std::queue<Signal> signalsQueue;
        /* process the button signal */
        static Signal const buttonSignal{
            "button", "broadcaster", SignalValue::Low};
        signalsQueue.emplace(buttonSignal);
        ++lowPulses;
        /* process the signals */
        auto signalToProcess{utils::extensions::try_take_front(signalsQueue)};
        while (signalToProcess) {
            auto const outputSignals{mesh.process(*signalToProcess)};
            for (auto const& outputSignal : outputSignals) {
                /* increase signal counters */
                if (outputSignal.value == SignalValue::Low) {
                    ++lowPulses;
                } else {
                    ++highPulses;
                }
                /* add the signal to the queue */
                signalsQueue.push(outputSignal);
            }
            signalToProcess = utils::extensions::try_take_front(signalsQueue);
        }
    }
    return std::to_string(lowPulses * highPulses);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    auto mesh{parseInput(filePath)};
    /* find the conjunctions connected to the conjunction connected to rx node
     */
    auto const previousNodeToRx{mesh.getModulesConnectedTo("rx")[0]};
    auto const morePreviousNodesToRx{
        mesh.getModulesConnectedTo(previousNodeToRx)};
    uint64_t buttonPresses{0ULL};
    std::unordered_map<ModuleName, uint64_t> last;
    std::unordered_map<ModuleName, uint64_t> loops;
    while (loops.size() < morePreviousNodesToRx.size()) {
        std::queue<Signal> signalsQueue;
        /* process the button signal */
        static Signal const buttonSignal{
            "button", "broadcaster", SignalValue::Low};
        signalsQueue.emplace(buttonSignal);
        ++buttonPresses;
        /* process the signals */
        auto signalToProcess{utils::extensions::try_take_front(signalsQueue)};
        while (signalToProcess) {
            auto const outputSignals{mesh.process(*signalToProcess)};
            for (auto const& outputSignal : outputSignals) {
                /* look for high signals to the layer of conjunctions prior to
                 * rx node */
                if (previousNodeToRx == outputSignal.destination
                    && outputSignal.value == SignalValue::High) {
                    if (last.contains(outputSignal.origin)) {
                        loops.emplace(
                            outputSignal.origin,
                            buttonPresses - last[outputSignal.origin]);
                    }
                    last.emplace(outputSignal.origin, buttonPresses);
                }
                /* add the signal to the queue */
                signalsQueue.push(outputSignal);
            }
            signalToProcess = utils::extensions::try_take_front(signalsQueue);
        }
    }
    return std::to_string(ranges::fold_left(
        loops | ranges::views::values, 1ULL, std::lcm<uint64_t, uint64_t>));
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_20
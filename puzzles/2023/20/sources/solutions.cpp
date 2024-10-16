#include "solutions.hpp"

#include "Broadcaster.hpp"
#include "Conjunction.hpp"
#include "FlipFlop.hpp"
#include "IModule.hpp"
#include "utils/String.hpp"
#include <memory>
#include <utils/File.hpp>

namespace aoc_2023_20 {

// ---------- Private Methods ----------

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

[[nodiscard]] std::unique_ptr<IModule> parseLine(std::string_view const line)
{
    /* check first char to know the module type */
    switch (line[0]) {
    case '%': {
        /* it is a flip-flop */
        std::string name{line.substr(1, line.find(' ') - 1)};
        auto module{std::make_unique<FlipFlop>(name)};
        for (auto const& destination : parseDestinations(line)) {
            module->addDestination(destination);
        }
        return module;
    }
    case '&': {
        /* it is a conjunction */
        std::string name{line.substr(1, line.find(' ') - 1)};
        auto module{std::make_unique<Conjunction>(name)};
        for (auto const& destination : parseDestinations(line)) {
            module->addDestination(destination);
        }
        return module;
    }
    default: {
        /* it is a broadcaster */
        auto module{std::make_unique<Broadcaster>()};
        for (auto const& destination : parseDestinations(line)) {
            module->addDestination(destination);
        }
        return module;
    }
    }
}

[[nodiscard]] std::vector<std::unique_ptr<IModule>>
parseInput(std::filesystem::path const& filePath) noexcept
{
    std::vector<std::unique_ptr<IModule>> modules;
    /* parse the file */
    bool const result{utils::file::parseAndIterate(
        filePath, [&modules](std::string_view const line) -> void {
            modules.emplace_back(parseLine(line));
        })};
    if (!result) {
        return {};
    }
    /* set inputs of Conjunctions */
    //TODO
    return modules;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    auto modules{parseInput(filePath)};
    return "";
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    (void)filePath;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_20
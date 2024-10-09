#include "solutions.hpp"

#include "part1/Part.h"
#include "part1/System.h"
#include <fstream>

namespace aoc_2023_19 {

// ---------- Private Methods ----------

/**
 * @brief      Parses one line of characters defining a full workflow.
 *
 * @param[in]  line  The line of characters defining a full workflow. For
 * example, "px{a<2006:qkq,m>2090:A,rfg}".
 *
 * @return     Instance containing the parsed data.
 */
part1::Workflow parseWorkflowForPart1(std::string_view const line)
{
    // extract name
    auto const nameEnd{line.find('{')};
    auto const name{line.substr(0, nameEnd)};
    part1::Workflow workflow{name};

    // extract rules
    auto const rulesStr{line.substr(nameEnd + 1, line.size() - nameEnd - 2)};
    auto const ruleStrings{utils::string::split(rulesStr, ",")};
    for (auto const& ruleString : ruleStrings) {
        // split condition and action
        auto const ruleStringSplit{utils::string::split(ruleString, ":")};
        if (ruleStringSplit.size() < 2) {
            // it is the unconditional rule at the end of the workflow
            workflow.addRule(part1::Rule{"", ruleString});
        } else {
            workflow.addRule(
                part1::Rule{ruleStringSplit[0], ruleStringSplit[1]});
        }
    }
    return workflow;
}

/**
 * @brief      Parses one line of characters defining a part.
 *
 * @param[in]  line  The line to parse. For example,
 *                   "{x=787,m=2655,a=1222,s=2876}".
 *
 * @return     Instance containing the parsed data.
 */
part1::Part parsePartForPart1(std::string_view line)
{
    line.remove_prefix(1);
    line.remove_suffix(1);
    auto const partStrings{utils::string::split(line, ",")};
    std::array<uint32_t, 4> partValues{};
    for (std::size_t i{0}; i < partStrings.size(); ++i) {
        partValues[i] = *utils::string::toNumber<uint32_t>(
            partStrings[i].substr(2));
    }
    return part1::Part{partValues};
}

/**
 * @brief         Parses the whole section in the input file containing all the
 *                workflow definitions.
 *
 * @param[in,out] fileStream  The file stream.
 *
 * @return        Instance containing the parsed data.
 */
part1::System parseWorkflowSystemForPart1(std::ifstream& fileStream)
{
    std::string line;
    part1::System system;
    while (std::getline(fileStream, line) && not line.empty()) {
        system.addWorkflow(parseWorkflowForPart1(line));
    }
    return system;
}

/**
 * @brief         Parses the whole section in the input file containing all the
 *                part definitions.
 *
 * @param[in,out] fileStream  The file stream.
 *
 * @return        Instance containing the parsed data.
 */
std::vector<part1::Part> parsePartsForPart1(std::ifstream& fileStream)
{
    std::string line;
    std::vector<part1::Part> parts;
    while (std::getline(fileStream, line) && not line.empty()) {
        parts.emplace_back(parsePartForPart1(line));
    }
    return parts;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(std::filesystem::path const& filePath)
{
    std::ifstream inputFile{filePath};
    auto const system{parseWorkflowSystemForPart1(inputFile)};
    auto const parts{parsePartsForPart1(inputFile)};
    uint32_t partSum{0U};
    for (auto const& part : parts) {
        if (system.run(part) == part1::System::RunResult::Accepted) {
            partSum += part.sum();
        }
    }
    return std::to_string(partSum);
}

std::string solvePart2(std::filesystem::path const& filePath)
{
    std::ifstream inputFile{filePath};
    auto const system{parseWorkflowSystemForPart2(inputFile)};
    uint64_t numCombinations{0ULL};

    return std::to_string(numCombinations);
}

// ---------- End of Public Methods ----------

} // namespace aoc_2023_19

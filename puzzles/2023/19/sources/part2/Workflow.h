#pragma once

#include "Part.h"
#include "Rule.h"
#include <string>
#include <unordered_map>

namespace aoc_2023_19::part2 {

class Workflow {
public:
    /**
     * @brief      { struct_description }
     */
    enum class Result { Accepted, Rejected, GoTo };
    /**
     * @brief      { struct_description }
     */
    struct RunResult {
        Result result;
        std::string goToWorkflow{""};
    };
    /**
     * @brief      Constructs a new instance.
     * @param name
     */
    explicit Workflow(std::string_view const name);
    /**
     * @brief     Adds a rule to the workflow.
     *
     * @param[in] rule ??
     */
    void addRule(Rule const& rule);
    /**
     * @brief      { function_description }
     *
     * @param part
     *
     * @return
     */
    [[nodiscard]] RunResult run(Part const& part) const noexcept;
    /**
     * @brief      { function_description }
     *
     * @return
     */
    [[nodiscard]] std::string getName() const noexcept;

private:
    std::string mName;
    std::vector<Rule> mRules{};
};

} // namespace aoc_2023_19

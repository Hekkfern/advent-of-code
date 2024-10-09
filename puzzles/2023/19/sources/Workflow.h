#pragma once

#include "Part.h"
#include "Rule.h"
#include <string>
#include <unordered_map>

namespace aoc_2023_19 {

class Workflow {
public:
    /**
     * @brief      Enum describing the result of @ref run method execution.
     */
    enum class Result { Accepted, Rejected, GoTo };
    /**
     * @brief      Returned data structure by @ref run method.
     */
    struct RunResult {
        Result result;
        std::string goToWorkflow{""};
    };
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  name  Identifier of the workflow.
     */
    explicit Workflow(std::string_view const name);
    /**
     * @brief      Adds a rule to the workflow.
     *
     * @param[in]  rule  Rule to add.
     */
    void addRule(Rule const& rule);
    /**
     * @brief      Processes the part against the list of rules forming this
     *             workflow.
     *
     * @param[in]  part  The part to process.
     *
     * @return     The result.
     */
    [[nodiscard]] RunResult run(Part const& part) const noexcept;
    /**
     * @brief      Gets the identifier of the workflow.
     *
     * @return     The identifier.
     */
    [[nodiscard]] std::string getName() const noexcept;

private:
    /**
     * Identifier.
     */
    std::string mName;
    /**
     * List of rules, in order.
     */
    std::vector<Rule> mRules{};
};

} // namespace aoc_2023_19

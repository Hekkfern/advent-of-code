#pragma once

#include "Rule.h"
#include <string>
#include <unordered_map>

namespace aoc_2023_19::part2 {

class Workflow {
public:
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
     * @brief      Gets the identifier of the workflow.
     *
     * @return     The identifier.
     */
    [[nodiscard]] std::string getName() const noexcept;
    /**
     * @brief ???
     *
     * @return ???
     */
    [[nodiscard]] std::vector<Rule> const& getRules() const noexcept;

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

} // namespace aoc_2023_19::part2

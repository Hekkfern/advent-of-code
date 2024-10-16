#include "Workflow.hpp"

namespace aoc_2023_19::part1 {

Workflow::Workflow(std::string_view const name)
    : mName{name}
{
}

void Workflow::addRule(Rule const& rule) noexcept { mRules.emplace_back(rule); }

Workflow::RunResult Workflow::run(Part const& part) const noexcept
{
    for (auto const& rule : mRules) {
        Rule::RunResult const ruleResult{rule.run(part)};
        switch (ruleResult.result) {
        case Rule::Result::Accepted:
            return RunResult{Result::Accepted};
        case Rule::Result::Rejected:
            return RunResult{Result::Rejected};
        case Rule::Result::Skip:
            continue;
        case Rule::Result::GoTo:
            return RunResult{Result::GoTo, ruleResult.goToWorkflow};
        }
    }
    /* impossible */
    return RunResult{Result::Rejected};
}

std::string Workflow::getName() const noexcept { return mName; }

} // namespace aoc_2023_19::part1

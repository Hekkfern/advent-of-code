#include "Workflow.hpp"

namespace aoc_2023_19::part2 {

Workflow::Workflow(std::string_view const name)
    : mName{name}
{
}

void Workflow::addRule(Rule const& rule) { mRules.emplace_back(rule); }

std::string Workflow::getName() const noexcept { return mName; }

std::vector<Rule> const& Workflow::getRules() const noexcept { return mRules; }

} // namespace aoc_2023_19::part2

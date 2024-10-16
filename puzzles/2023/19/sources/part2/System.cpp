#include "System.hpp"

namespace aoc_2023_19::part2 {

namespace {

void searchAccepted(
    utils::extensions::UnorderedStringMap<Workflow> const& workflows,
    std::vector<PartRange>& accepted,
    Rule::ActionData const& actionData,
    PartRange value)
{
    // Accepted
    if (actionData.type == Rule::ActionType::Accepted) {
        accepted.push_back(value);
        return;
    }
    // Rejected
    if (actionData.type == Rule::ActionType::Rejected) {
        return;
    }

    // Process the workflow
    for (Rule const& rule : workflows.at(*actionData.destination).getRules()) {
        // No condition means that we are jumping to a new label
        if (not rule.hasCondition()) {
            searchAccepted(workflows, accepted, rule.getAction(), value);
            continue;
        }

        // Get the "true" and "false" chunks
        auto [jump, next] = rule.process(value);
        if (jump) {
            // recurse
            searchAccepted(workflows, accepted, rule.getAction(), *jump);
        }
        // If the "false" chunk doesn't contain any values, we are done
        if (not next) // dead-end
        {
            break;
        }
        // Otherwise update the relevant member with the "false" values and
        // continue
        value = *next;
    }
}

} // namespace

void System::addWorkflow(Workflow const& workflow) noexcept
{
    mWorkflows.emplace(workflow.getName(), workflow);
}

std::vector<PartRange> System::search() const noexcept
{
    std::vector<PartRange> accepted;
    searchAccepted(mWorkflows, accepted, {Rule::ActionType::GoTo, "in"}, {});
    return accepted;
}

} // namespace aoc_2023_19::part2

#include "System.h"

namespace aoc_2023_19::part2 {

void System::addWorkflow(Workflow const& workflow) noexcept
{
    mWorkflows.emplace(workflow.getName(), workflow);
}

std::vector<part2::PartRange> System::search() const noexcept
{
    // TODO
}

} // namespace aoc_2023_19::part2

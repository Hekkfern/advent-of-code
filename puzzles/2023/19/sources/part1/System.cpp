#include "System.hpp"

namespace aoc_2023_19::part1 {

void System::addWorkflow(Workflow const& workflow) noexcept
{
    mWorkflows.emplace(workflow.getName(), workflow);
}

System::RunResult System::run(Part const& part) const noexcept
{
    constexpr std::string_view firstWorkflowName{"in"};

    std::string currentWorkflow{firstWorkflowName};
    while (true) {
        auto const workFlowResult{mWorkflows.at(currentWorkflow).run(part)};
        switch (workFlowResult.result) {
        case Workflow::Result::GoTo:
            currentWorkflow = workFlowResult.goToWorkflow;
            break;
        case Workflow::Result::Accepted:
            return RunResult::Accepted;
        case Workflow::Result::Rejected:
            return RunResult::Rejected;
        }
    }
}

} // namespace aoc_2023_19::part1

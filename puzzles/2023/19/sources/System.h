#pragma once

#include "Workflow.h"
#include <utils/extensions/StringCollections.h>

namespace aoc_2023_19 {

class System {
public:
    /**
     * @brief      { struct_description }
     */
    enum class RunResult { Accepted, Rejected };

    /**
     * @brief      Constructs a new instance.
     */
    explicit System(
        utils::extensions::UnorderedStringMap<Workflow> const& workflows)
        : mWorkflows{workflows}
    {
    }
    /**
     * @brief      { function_description }
     *
     * @param[in] part
     *
     * @return
     */
    RunResult run(Part const& part)
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

private:
    utils::extensions::UnorderedStringMap<Workflow> mWorkflows{};
};

} // namespace aoc_2023_19

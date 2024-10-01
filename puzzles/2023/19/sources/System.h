#pragma once

#include "Workflow.h"
#include <unordered_map>

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
    explicit System(std::unordered_map<std::string, Workflow> const& workflows)
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
        auto const firstWorkflow{mWorkflows.at("in").run(part)};
        switch (firstWorkflow.result) {
        case Workflow::Result::GoTo:
            // TODO
            break;
        case Workflow::Result::Accepted:
            return RunResult::Accepted;
        case Workflow::Result::Rejected:
            return RunResult::Rejected;
        }
    }

private:
    std::unordered_map<std::string, Workflow> mWorkflows{};
};

} // namespace aoc_2023_19

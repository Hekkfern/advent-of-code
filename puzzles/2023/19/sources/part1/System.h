#pragma once

#include "Workflow.h"
#include <utils/extensions/StringCollections.h>

namespace aoc_2023_19::part1 {

class System {
public:
    /**
     * @brief      Enum describing the result of @ref run method execution.
     */
    enum class RunResult { Accepted, Rejected };

    /**
     * @brief      Constructs a new instance.
     */
    explicit System() = default;
    /**
     * @brief      Adds a workflow to the system.
     *
     * @param[in]  workflow  Item to add.
     */
    void addWorkflow(Workflow const& workflow) noexcept;
    /**
     * @brief      Processes the part against the chain of workflows, starting
     *             from the workflow named as "in".
     *
     * @param[in]  part  The part to process.
     *
     * @return     The result.
     */
    [[nodiscard]] RunResult run(Part const& part) const noexcept;

private:
    /**
     * List of workflows.
     */
    utils::extensions::UnorderedStringMap<Workflow> mWorkflows{};
};

} // namespace aoc_2023_19

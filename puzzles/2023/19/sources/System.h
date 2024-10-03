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
    explicit System() = default;
    /**
     * @brief      Adds a workflow to the system.
     *
     * @param[in] workflow Item to add.
     */
    void addWorkflow(Workflow const& workflow);
    /**
     * @brief      { function_description }
     *
     * @param[in] part
     *
     * @return
     */
    RunResult run(Part const& part);

private:
    utils::extensions::UnorderedStringMap<Workflow> mWorkflows{};
};

} // namespace aoc_2023_19

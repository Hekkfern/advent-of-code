#pragma once

#include "Workflow.hpp"
#include <utils/extensions/StringCollections.h>

namespace aoc_2023_19::part2 {

class System {
public:
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
     * @return     The result.
     */
    [[nodiscard]] std::vector<part2::PartRange> search() const noexcept;

private:
    /**
     * List of workflows.
     */
    utils::extensions::UnorderedStringMap<Workflow> mWorkflows{};
};

} // namespace aoc_2023_19::part2

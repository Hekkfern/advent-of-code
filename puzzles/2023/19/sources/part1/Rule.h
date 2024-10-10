#pragma once

#include "Part.h"
#include <cassert>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <utils/String.hpp>

namespace aoc_2023_19::part1 {

class Rule {
public:
    /**
     * @brief      Enum describing the result of @ref run method execution.
     */
    enum class Result { Accepted, Rejected, GoTo, Skip };
    /**
     * @brief      Returned data structure by @ref run method.
     */
    struct RunResult {
        Result result;
        std::string goToWorkflow{""};
    };
    /**
     * @brief      Types of actions to do when the condition is true.
     */
    enum class ActionType { Accepted, Rejected, GoTo };

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  conditionStatement  The condition statement. Its format must
     *                                 be like "x<10" or "m>145", or an empty
     *                                 string.
     * @param[in]  actionStatement     String describing the action of the rule.
     *                                 It can be "A", "R" or the name of another
     *                                 workflow.
     */
    Rule(std::string_view conditionStatement, std::string_view actionStatement);
    /**
     * @brief      Processes the given part against this rule.
     *
     * @param[in]  part  The part to analyze.
     *
     * @return     The result.
     */
    [[nodiscard]] RunResult run(Part const& part) const noexcept;

private:
    /**
     * Projection of the category field of @ref Part structure.
     */
    std::function<uint32_t&(Part&)> mCategoryProjection;
    /**
     * Lambda defining the condition of this rule.
     */
    std::function<bool(uint32_t value)> mCondition{nullptr};
    /**
     * Type of the action to do if the @ref mCondition is true.
     */
    ActionType mActionType;
    /**
     * If @ref mActionType is @ref ActionType::GoTo, this field tells the name
     * of the workflow to jump to.
     */
    std::string mGoToDestination{""};
};

} // namespace aoc_2023_19::part1

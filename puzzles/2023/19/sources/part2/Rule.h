#pragma once

#include "PartRange.h"
#include <cassert>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <utils/String.hpp>

namespace aoc_2023_19::part2 {

class Rule {
public:
    /**
     * @brief      { struct_description }
     */
    enum class ActionType { Accepted, Rejected, GoTo };

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  conditionStatement  The condition statement. In the format of
     * "x<10", or an empty string.
     * @param[in]  actionStatement              The action
     */
    Rule(std::string_view conditionStatement, std::string_view actionStatement);
    /**
     * @brief     { function_description }
     * @return ???
     */
    [[nodiscard]] std::pair<std::optional<PartRange>, std::optional<PartRange>>
    process(PartRange const& part) const noexcept;

private:
    /**
     * Projection of the category field of @ref PartRange structure.
     */
    std::function<Range&(PartRange&)> mCategoryProjection;
    /**
     * Lambda defining the condition of this rule.
     */
    std::function<std::pair<std::optional<Range>, std::optional<Range>>(
        Range const& range)>
        mCondition{nullptr};
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

} // namespace aoc_2023_19::part2

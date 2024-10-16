#pragma once

#include "PartRange.hpp"
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
     * @brief      { struct_description }
     */
    struct ActionData {
        ActionType type;
        std::optional<std::string> destination{};
    };

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  conditionStatement  The condition statement. In the format of
     * "x<10", or an empty string.
     * @param[in]  actionStatement              The action
     */
    Rule(std::string_view conditionStatement, std::string_view actionStatement);
    /**
     * @brief      { struct_description }
     *
     * @return
     */
    [[nodiscard]] bool hasCondition() const noexcept;
    /**
     * @brief      { struct_description }
     *
     * @return
     */
    [[nodiscard]] ActionData getAction() const noexcept;
    /**
     * @brief     { function_description }
     *
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
    ActionData mAction;
};

} // namespace aoc_2023_19::part2

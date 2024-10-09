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
    Rule(
        std::string_view const conditionStatement,
        std::string_view const actionStatement);
    /**
     *
     * @return ???
     */
    [[nodiscard]] std::optional<
        std::pair<std::optional<PartRange>, std::optional<PartRange>>>
    analyze(PartRange const& part) const noexcept;

private:
    /**
     * { item_description }
     */
    std::function<std::pair<std::optional<PartRange>, std::optional<PartRange>>(
        PartRange const& part)>
        mCondition{nullptr};
    /**
     * { item_description }
     */
    ActionType mActionType;
    /**
     * { item_description }
     */
    std::string mGoToDestination{""};
};

} // namespace aoc_2023_19::part2

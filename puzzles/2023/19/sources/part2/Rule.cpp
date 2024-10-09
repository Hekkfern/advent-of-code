#include "Rule.h"

namespace aoc_2023_19::part2 {

Rule::Rule(
    std::string_view const conditionStatement,
    std::string_view const actionStatement)
{
    if (actionStatement == "A") {
        mActionType = ActionType::Accepted;
    } else if (actionStatement == "R") {
        mActionType = ActionType::Rejected;
    } else {
        if (not conditionStatement.empty()) {
            mCondition =
                [memberName = conditionStatement[0],
                 conditionSymbol = conditionStatement[1],
                 thresholdValue = *utils::string::toNumber<uint32_t>(
                     conditionStatement.substr(2))](PartRange const& part)
                -> std::
                    pair<std::optional<PartRange>, std::optional<PartRange>> {

                    };
        }
    };
}
std::optional<std::pair<std::optional<PartRange>, std::optional<PartRange>>>
Rule::analyze(PartRange& part) const noexcept
{
}

} // namespace aoc_2023_19::part2

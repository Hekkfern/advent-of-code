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
        mActionType = ActionType::GoTo;
        mGoToDestination = actionStatement;
    }
    if (not conditionStatement.empty()) {
        std::string const categoryStr{conditionStatement[0]};
        std::string const conditionSymbol{conditionStatement[1]};
        uint32_t const thresholdValue{
            *utils::string::toNumber<uint32_t>(conditionStatement.substr(2))};
        if (categoryStr == "x") {
            mCategoryProjection = &PartRange::x;
        } else if (categoryStr == "m") {
            mCategoryProjection = &PartRange::m;
        } else if (categoryStr == "a") {
            mCategoryProjection = &PartRange::a;
        } else if (categoryStr == "s") {
            mCategoryProjection = &PartRange::s;
        } else {
            /* impossible */
            assert(false);
        }
        if (conditionSymbol == "<") {
            mCondition = [thresholdValue](uint32_t const value) -> bool {
                return value < thresholdValue;
            };
        } else if (conditionSymbol == ">") {
            mCondition = [thresholdValue](uint32_t const value) -> bool {
                return value > thresholdValue;
            };
        } else {
            /* impossible */
            assert(false);
        }
    }
}
std::optional<std::pair<std::optional<PartRange>, std::optional<PartRange>>>
Rule::analyze(PartRange& part) const noexcept
{
}

} // namespace aoc_2023_19::part2

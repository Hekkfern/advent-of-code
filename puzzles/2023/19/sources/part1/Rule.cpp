#include "Rule.hpp"

namespace aoc_2023_19::part1 {

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
            mCategoryProjection = &Part::x;
        } else if (categoryStr == "m") {
            mCategoryProjection = &Part::m;
        } else if (categoryStr == "a") {
            mCategoryProjection = &Part::a;
        } else if (categoryStr == "s") {
            mCategoryProjection = &Part::s;
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

Rule::RunResult Rule::run(Part const& part) const noexcept
{
    if (not mCondition
        || std::invoke(
            mCondition,
            std::invoke(mCategoryProjection, const_cast<Part&>(part)))) {
        switch (mActionType) {
        case ActionType::Accepted:
            return RunResult{Result::Accepted};
        case ActionType::Rejected:
            return RunResult{Result::Rejected};
        default:
            return RunResult{Result::GoTo, mGoToDestination};
        }
    }
    return RunResult{Result::Skip};
}

} // namespace aoc_2023_19::part1

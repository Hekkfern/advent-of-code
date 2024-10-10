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
            mCondition =
                [thresholdValue
                 = static_cast<int32_t>(thresholdValue)](Range const& range)
                -> std::pair<std::optional<Range>, std::optional<Range>> {
                if (range.hasOneValue()) {
                    return std::make_pair(std::nullopt, std::nullopt);
                }
                using enum utils::interval::Location;
                switch (range.where(thresholdValue)) {
                case LeftOutside:
                case LeftBoundary:
                    return std::make_pair(std::nullopt, range);
                case RightBoundary:
                    return std::make_pair(
                        Range{range.getMin(), thresholdValue - 1},
                        Range{thresholdValue, thresholdValue});
                case RightOutside:
                    return std::make_pair(range, std::nullopt);
                case Within:
                    return std::make_pair(
                        Range{range.getMin(), thresholdValue - 1},
                        Range{thresholdValue, range.getMax()});
                }
            };
        } else if (conditionSymbol == ">") {
            mCondition =
                [thresholdValue
                 = static_cast<int32_t>(thresholdValue)](Range const& range)
                -> std::pair<std::optional<Range>, std::optional<Range>> {
                if (range.hasOneValue()) {
                    return std::make_pair(std::nullopt, std::nullopt);
                }
                using enum utils::interval::Location;
                switch (range.where(thresholdValue)) {
                case LeftOutside:
                    return std::make_pair(range, std::nullopt);
                case LeftBoundary:
                    return std::make_pair(
                        Range(thresholdValue + 1, range.getMax()),
                        Range{thresholdValue, thresholdValue});
                case RightBoundary:
                case RightOutside:
                    return std::make_pair(std::nullopt, range);
                case Within:
                    return std::make_pair(
                        Range{thresholdValue + 1, range.getMax()},
                        Range{range.getMin(), thresholdValue});
                }
            };
        } else {
            /* impossible */
            assert(false);
        }
    }
}

Rule::RunResult Rule::analyze(PartRange const& part) const noexcept
{
    if (not mCondition) {
        switch (mActionType) {
        case ActionType::Accepted:
            return Rule::RunResult{Result::Finished, part, std::nullopt};
        case ActionType::Rejected:
            return Rule::RunResult{Result::Finished, std::nullopt, part};
        default:
            return Rule::RunResult{Result::GoTo, part, part, mGoToDestination};
        }
    }
    auto const conditionResult{std::invoke(
        mCondition,
        std::invoke(mCategoryProjection, const_cast<PartRange&>(part)))};
    return Rule::RunResult{
        Result::Finished,
        conditionResult.first,
        conditionResult.second,
        mGoToDestination};
}

} // namespace aoc_2023_19::part2

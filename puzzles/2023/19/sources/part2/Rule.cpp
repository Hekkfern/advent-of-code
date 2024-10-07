#include "Rule.h"

namespace aoc_2023_19::part2 {

Rule::Rule(
    std::string_view const conditionStatement, std::string_view const action)
{
    mAction = action;
    if (not conditionStatement.empty()) {
        mCondition =
            [memberName = conditionStatement[0],
             conditionSymbol = conditionStatement[1],
             thresholdValue = *utils::string::toNumber<uint32_t>(
                 conditionStatement.substr(2))](PartRange& part) -> bool {
            switch (memberName) {
            case 'x':
                return conditionSymbol == '<'
                    ? part.x < thresholdValue
                    : part.x > thresholdValue;
            case 'm':
                return conditionSymbol == '<'
                    ? part.m < thresholdValue
                    : part.m > thresholdValue;
            case 'a':
                return conditionSymbol == '<'
                    ? part.a < thresholdValue
                    : part.a > thresholdValue;
            case 's':
                return conditionSymbol == '<'
                    ? part.s < thresholdValue
                    : part.s > thresholdValue;
            default:
                /* impossible */
                assert(false);
            }
        };
    } else {
        mCondition = nullptr;
    }
}

Rule::RunResult Rule::run(Part const& part) const noexcept
{
    if (!mCondition || mCondition(part)) {
        if (mAction == "A") {
            return RunResult{Result::Accepted};
        }
        if (mAction == "R") {
            return RunResult{Result::Rejected};
        }
        return RunResult{Result::GoTo, mAction};
    }
    return RunResult{Result::Skip};
}

} // namespace aoc_2023_19::part2

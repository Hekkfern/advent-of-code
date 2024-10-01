#pragma once

#include "Part.h"
#include <cassert>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <utils/String.hpp>

namespace aoc_2023_19 {

class Rule {
public:
    /**
     * @brief      { struct_description }
     */
    enum class Result { Accepted, Rejected, GoTo, Skip };
    /**
     * @brief      { struct_description }
     */
    struct RunResult {
        Result result;
        std::string goToWorkflow{""};
    };

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  conditionStatement  The condition statement. In the format of
     * "x<10", or an empty string.
     * @param[in]  action              The action
     */
    Rule(
        std::string_view const conditionStatement,
        std::string_view const action)
    {
        mAction = action;
        if (not conditionStatement.empty()) {
            mCondition =
                [memberName = conditionStatement[0],
                 conditionSymbol = conditionStatement[1],
                 thresholdValue = *utils::string::toNumber<uint32_t>(
                     conditionStatement.substr(2))](Part const& part) -> bool {
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
    /**
     * @brief      { function_description }
     *
     * @param      part  The part
     *
     * @return     The run result.
     */
    [[nodiscard]] RunResult run(Part const& part) const noexcept
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

private:
    /**
     * { item_description }
     */
    std::function<bool(Part const& part)> mCondition;
    /**
     * { item_description }
     */
    std::string mAction;
};

} // namespace aoc_2023_19

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
        std::string_view const action);
    /**
     * @brief      { function_description }
     *
     * @param      part  The part
     *
     * @return     The run result.
     */
    [[nodiscard]] RunResult run(Part const& part) const noexcept;

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

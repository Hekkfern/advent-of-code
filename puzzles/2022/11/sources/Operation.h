#pragma once

#include "Types.h"
#include <optional>

namespace aoc_2022_11 {

enum class Operator { ADD, MULTIPLY };

class Operation {
public:
    Operation(Operator op, std::optional<WorryLevel> operand);
    WorryLevel operator()(WorryLevel oldValue);
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other   Other instance to compare with.
     *
     * @return     The result of the equality.
     */
    bool operator==(Operation const& other);

private:
    const Operator mOperator;
    const std::optional<WorryLevel> mOperand;
};

} // namespace aoc_2022_11

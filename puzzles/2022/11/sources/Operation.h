#pragma once

#include "Types.h"
#include <optional>

enum class Operator { ADD, MULTIPLY };

class Operation {
public:
    Operation(Operator op, std::optional<WorryLevel> operand);
    WorryLevel operator()(WorryLevel oldValue);

private:
    const Operator mOperator;
    const std::optional<WorryLevel> mOperand;
};

#include "Operation.h"

Operation::Operation(const Operator op, const std::optional<WorryLevel> operand)
    : mOperator{ op }
    , mOperand{ operand }
{
}

WorryLevel Operation::operator()(const WorryLevel oldValue)
{
    const WorryLevel rhs{ !mOperand ? *mOperand : oldValue };
    if (mOperator == Operator::MULTIPLY) {
        return (oldValue * rhs);
    } else if (mOperator == Operator::ADD) {
        return (oldValue + rhs);
    } else {
        throw std::logic_error("Invalid operator");
    }
}

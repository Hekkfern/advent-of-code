#pragma once

#include "Types.h"
#include <optional>

enum class Operator { ADD, MULTIPLY };

class Operation {
public:
    Operation(Operator op, std::optional<WorryLevel> operand);
    WorryLevel operator()(WorryLevel oldValue);

private:
    /**
     * Friend relationship of the equality operator overload.
     */
    friend bool operator==(const Operation& lhs, const Operation& rhs);

    const Operator mOperator;
    const std::optional<WorryLevel> mOperand;
};

/**
 * @brief      Equality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the equality.
 */
bool operator==(const Operation& lhs, const Operation& rhs);

/**
 * @brief      Inequality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the inequality.
 */
bool operator!=(const Operation& lhs, const Operation& rhs);

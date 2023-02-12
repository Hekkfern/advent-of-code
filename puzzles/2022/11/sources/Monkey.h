#pragma once

#include "Operation.h"
#include <cstdint>
#include <unordered_map>
#include <vector>

using MonkeyId = uint8_t;

class Monkey {
public:
    Monkey(
        MonkeyId id,
        Operation&& operation,
        WorryLevel divisor,
        MonkeyId targetTrue,
        MonkeyId targetFalse,
        std::vector<WorryLevel>&& items = {});
    MonkeyId getId() const;
    uint32_t inspectAndThrowAll(
        std::unordered_map<MonkeyId, Monkey>& monkeys,
        bool reliefEnabled);

private:
    /**
     * Friend relationship of the equality operator overload.
     */
    friend bool operator==(const Monkey& lhs, const Monkey& rhs);

    const MonkeyId mId;
    Operation mOperation;
    const WorryLevel mDivisor;
    const MonkeyId mTargetTrue;
    const MonkeyId mTargetFalse;
    std::vector<WorryLevel> mItems{};
};

/**
 * @brief      Equality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the equality.
 */
bool operator==(const Monkey& lhs, const Monkey& rhs);

/**
 * @brief      Inequality operator.
 *
 * @param[in]  lhs   The left hand side of the operation.
 * @param[in]  rhs   The right hand side of the operation.
 *
 * @return     The result of the inequality.
 */
bool operator!=(const Monkey& lhs, const Monkey& rhs);

template <> struct std::hash<Monkey> {
    std::size_t operator()(const Monkey& k) const
    {
        return (std::hash<MonkeyId>()(k.getId()));
    }
};

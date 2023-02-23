#pragma once

#include "Operation.h"
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace aoc_2022_11 {

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
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other   Other instance to compare with.
     *
     * @return     The result of the equality.
     */
    bool operator==(const Monkey& other);

private:
    const MonkeyId mId;
    Operation mOperation;
    const WorryLevel mDivisor;
    const MonkeyId mTargetTrue;
    const MonkeyId mTargetFalse;
    std::vector<WorryLevel> mItems{};
};

} // namespace aoc_2022_11

template <> struct std::hash<aoc_2022_11::Monkey> {
    std::size_t operator()(const aoc_2022_11::Monkey& k) const
    {
        return (std::hash<aoc_2022_11::MonkeyId>()(k.getId()));
    }
};

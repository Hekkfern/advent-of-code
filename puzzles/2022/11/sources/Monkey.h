#pragma once

#include "Operation.h"
#include <cstdint>
#include <vector>

using MonkeyId = uint8_t;

class Monkey {
public:
    Monkey(
        MonkeyId id,
        Operation operation,
        WorryLevel divisor,
        WorryLevel targetTrue,
        WorryLevel targetFalse);

private:
    const MonkeyId mId;
    const Operation mOperation;
    const WorryLevel mDivisor;
    const WorryLevel mTargetTrue;
    const WorryLevel mTargetFalse;
    std::vector<WorryLevel> mItems{};
};

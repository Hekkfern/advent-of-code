#include "Monkey.h"

Monkey::Monkey(
    MonkeyId id,
    Operation&& operation,
    WorryLevel divisor,
    WorryLevel targetTrue,
    WorryLevel targetFalse,
    std::vector<WorryLevel>&& items)
    : mId{ id }
    , mOperation{ std::move(operation) }
    , mDivisor{ divisor }
    , mTargetTrue{ targetTrue }
    , mTargetFalse{ targetFalse }
    , mItems{ items }
{
}
void Monkey::inspectAndThrowAll(std::unordered_map<MonkeyId, Monkey>& monkeys) {
    
}

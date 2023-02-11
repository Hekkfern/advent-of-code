#include "Monkey.h"

Monkey::Monkey(
    MonkeyId id,
    Operation&& operation,
    WorryLevel divisor,
    MonkeyId targetTrue,
    MonkeyId targetFalse,
    std::vector<WorryLevel>&& items)
    : mId{ id }
    , mOperation{ std::move(operation) }
    , mDivisor{ divisor }
    , mTargetTrue{ targetTrue }
    , mTargetFalse{ targetFalse }
    , mItems{ items }
{
}

MonkeyId Monkey::getId() const { return mId; }

uint32_t Monkey::inspectAndThrowAll(
    std::unordered_map<MonkeyId, Monkey>& monkeys)
{
    uint32_t inspectionsCounter{ 0U };
    for (auto& item : mItems) {
        // monkey inspect the object
        item = mOperation(item);
        // you are relief
        item /= WorryLevel{ 3U };
        // test your worry level and throw to the target monkey
        const MonkeyId target{ (item % mDivisor == 0) ? mTargetTrue
                                                      : mTargetFalse };
        monkeys.at(target).mItems.emplace_back(item);
        ++inspectionsCounter;
    }
    return inspectionsCounter;
}

bool operator==(const Monkey& lhs, const Monkey& rhs)
{
    return (lhs.mId == rhs.mId) && (lhs.mOperation == rhs.mOperation)
        && (lhs.mDivisor == rhs.mDivisor)
        && (lhs.mTargetTrue == rhs.mTargetTrue)
        && (lhs.mTargetFalse == rhs.mTargetFalse) && (lhs.mItems == rhs.mItems);
}

bool operator!=(const Monkey& lhs, const Monkey& rhs) { return !(lhs == rhs); }

#include "Monkey.h"

namespace aoc_2022_11 {

Monkey::Monkey(
    MonkeyId id,
    Operation&& operation,
    WorryLevel divisor,
    MonkeyId targetTrue,
    MonkeyId targetFalse,
    std::vector<WorryLevel>&& items)
    : mId{id}
    , mOperation{std::move(operation)}
    , mDivisor{divisor}
    , mTargetTrue{targetTrue}
    , mTargetFalse{targetFalse}
    , mItems{items}
{
}

MonkeyId Monkey::getId() const { return mId; }

uint32_t Monkey::inspectAndThrowAll(
    std::unordered_map<MonkeyId, Monkey>& monkeys, bool reliefEnabled)
{
    uint32_t inspectionsCounter{0U};
    for (auto& item : mItems) {
        WorryLevel itemValue = 0U;
        // monkey inspect the object
        itemValue = mOperation(item);
        // check your relief
        if (reliefEnabled) {
            itemValue /= WorryLevel{3U};
        } else {
            itemValue %= mDivisor;
        }
        // test your worry level and throw to the target monkey
        const MonkeyId target{
            (itemValue % mDivisor == 0) ? mTargetTrue : mTargetFalse};
        monkeys.at(target).mItems.emplace_back(itemValue);
        ++inspectionsCounter;
    }
    // delete all the items of this monkey
    mItems.clear();

    return inspectionsCounter;
}

bool Monkey::operator==(Monkey const& other)
{
    return (mId == other.mId) && (mOperation == other.mOperation)
        && (mDivisor == other.mDivisor) && (mTargetTrue == other.mTargetTrue)
        && (mTargetFalse == other.mTargetFalse) && (mItems == other.mItems);
}

} // namespace aoc_2022_11

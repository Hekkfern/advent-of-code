#include "Monkey.h"

Monkey::Monkey(
    MonkeyId id,
    Operation operation,
    WorryLevel divisor,
    WorryLevel targetTrue,
    WorryLevel targetFalse)
    : mId{ id }
    , mOperation{ operation }
    , mDivisor{ divisor }
    , mTargetTrue{ targetTrue }
    , mTargetFalse{ targetFalse }
{
}

#pragma once

#include <cstdint>

namespace aoc_2022_5 {

using StackId = uint32_t;

struct CraneInstruction {
    uint32_t mNumCrates;
    StackId mOriginStackId;
    StackId mDestinationStackId;
};

class CrateStack {
public:


private:
    StackId mId;
};

}

#pragma once

#include <cassert>

namespace aoc_2023_12 {

class Spring {
public:
    enum Status { Unknown, Operational, Damaged } status{};

    explicit Spring(char const c)
        : status{parse(c)}
    {
    }

    explicit Spring(Status const s)
        : status{s}
    {
    }

private:
    [[nodiscard]] static Status parse(char const c)
    {
        if (c == '.') {
            return Operational;
        } else if (c == '#') {
            return Damaged;
        } else if (c == '?') {
            return Unknown;
        } else {
            assert(false);
        }
    }
};

} // namespace aoc_2023_12

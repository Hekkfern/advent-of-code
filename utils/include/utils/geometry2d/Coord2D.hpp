#pragma once

#include "../Concepts.hpp"

namespace utils::geometry2d {

template <SignedIntegerType T = int32_t>
struct Coord2D {
    T mX;
    T mY;
};

} // namespace utils::geometry2d

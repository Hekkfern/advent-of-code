#pragma once

#include "../Concepts.hpp"

namespace utils::geometry3d {

template <SignedIntegerType T = int32_t>
struct Coord3D {
    T mX;
    T mY;
    T mZ;
};

} // namespace utils::geometry3d

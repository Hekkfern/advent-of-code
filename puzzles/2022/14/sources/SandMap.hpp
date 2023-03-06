#pragma once

#include <unordered_set>
#include <utils/geometry2d/BoundingBox2D.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2022_14 {

class SandMap {
public:
    void addRockLine(
        const utils::geometry2d::Point2D& start,
        const utils::geometry2d::Point2D& end);
    bool addSandGrain();
    uint32_t getNumberOfSandGrains() const;

private:
    utils::geometry2d::BoundingBox2D mBoundingBox;
    std::unordered_set<utils::geometry2d::Point2D> mRocks;
    std::unordered_set<utils::geometry2d::Point2D> mSand;
};

} // namespace aoc_2022_14

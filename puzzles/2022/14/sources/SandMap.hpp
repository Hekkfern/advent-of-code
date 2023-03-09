#pragma once

#include <optional>
#include <unordered_set>
#include <utils/geometry2d/BoundingBox2D.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2022_14 {

class SandMap {
public:
    void addRockLine(
        const utils::geometry2d::Point2D& start,
        const utils::geometry2d::Point2D& end);
    /**
     * @brief      Adds a sand grain and moves across the map until it stays
     *             steady or it falls down infinitely.
     *
     * @return     True if the grain stayed steady. False, otherwise.
     */
    bool addSandGrain();
    uint32_t getNumberOfSandGrains() const;

private:
    std::optional<utils::geometry2d::Point2D> sandGoDown(
        const utils::geometry2d::Point2D& position);
    std::optional<utils::geometry2d::Point2D> sandSlide(
        const utils::geometry2d::Point2D& position,
        const utils::geometry2d::Direction2D& direction2D);
    bool isOutside(const utils::geometry2d::Point2D& position) const;

    utils::geometry2d::BoundingBox2D mBoundingBox{};
    std::unordered_set<utils::geometry2d::Point2D> mRocks{};
    std::unordered_set<utils::geometry2d::Point2D> mSand{};
};

} // namespace aoc_2022_14

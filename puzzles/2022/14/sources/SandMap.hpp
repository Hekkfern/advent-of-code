#pragma once

#include <optional>
#include <unordered_set>
#include <utils/geometry2d/BoundingBox2D.hpp>
#include <utils/geometry2d/Point2D.hpp>

namespace aoc_2022_14 {

class SandMap {
public:
    void addRockLine(
        const utils::geometry2d::Point2D<int32_t>& start,
        const utils::geometry2d::Point2D<int32_t>& end);
    /**
     * @brief      Adds a sand grain and moves across the map until it stays
     *             steady or it falls down infinitely.
     *
     * @return     True if the grain stayed steady. False, otherwise.
     */
    bool addSandGrainInConstrainedSpace();
    bool addSandGrainInInfiniteSpace();
    uint32_t getNumberOfSandGrains() const;
    void enableInfiniteFloor();

private:
    std::optional<utils::geometry2d::Point2D<int32_t>>
    sandGoDown(const utils::geometry2d::Point2D<int32_t>& position);
    std::optional<utils::geometry2d::Point2D<int32_t>> sandSlide(
        const utils::geometry2d::Point2D<int32_t>& position,
        const utils::geometry2d::Direction2D& direction2D);
    bool isOutside(const utils::geometry2d::Point2D<int32_t>& position) const;

    utils::geometry2d::BoundingBox2D<int32_t> mBoundingBox{};
    int32_t mAssumedFloorHeight{2U};
    bool mInfiniteFloorEnabled{false};
    std::unordered_set<utils::geometry2d::Point2D<int32_t>> mRocks{};
    std::unordered_set<utils::geometry2d::Point2D<int32_t>> mSand{};
};

} // namespace aoc_2022_14

#pragma once

#include <cstdint>
#include <optional>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/SquareDiamond2D.hpp>

namespace aoc_2022_15 {

class SensorInfo {
public:
    SensorInfo(
        utils::geometry2d::Point2D<int32_t>&& sensorPosition,
        utils::geometry2d::Point2D<int32_t>&& beaconPosition);
    const utils::geometry2d::Point2D<int32_t>& getSensorPosition() const;
    const utils::geometry2d::Point2D<int32_t>& getBeaconPosition() const;
    uint64_t getDistance() const;
    std::optional<utils::geometry2d::Point2D<int32_t>> stepAroundOutside();
    bool isCovered(const utils::geometry2d::Point2D<int32_t>& testPoint) const;
    bool
    hasBeaconAt(const utils::geometry2d::Point2D<int32_t>& testPoint) const;

private:
    utils::geometry2d::Point2D<int32_t> mSensorPosition;
    utils::geometry2d::Point2D<int32_t> mBeaconPosition;
    uint64_t mDistance;
    utils::geometry2d::SquareDiamond2D<int32_t> mSquareDiamond2D;
};

} // namespace aoc_2022_15

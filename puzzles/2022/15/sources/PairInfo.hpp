#pragma once

#include <cstdint>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

namespace aoc_2022_15 {

class PairInfo {
public:
    PairInfo(
        utils::geometry2d::Point2D&& sensorPosition,
        utils::geometry2d::Point2D&& beaconPosition);
    const utils::geometry2d::Point2D& getSensorPosition() const;
    const utils::geometry2d::Point2D& getBeaconPosition() const;
    const utils::geometry2d::Vector2D& getDifferenceVector() const;
    uint32_t getDistance() const;

private:
    const utils::geometry2d::Point2D mSensorPosition;
    const utils::geometry2d::Point2D mBeaconPosition;
    const utils::geometry2d::Vector2D mSensorToBeaconVector;
    const uint32_t mDistance;
};

} // namespace aoc_2022_15

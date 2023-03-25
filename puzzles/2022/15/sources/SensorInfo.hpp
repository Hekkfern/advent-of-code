#pragma once

#include <cstdint>
#include <optional>
#include <utils/geometry2d/Point2D.hpp>
#include <utils/geometry2d/Vector2D.hpp>

namespace aoc_2022_15 {

class SensorInfo {
public:
    SensorInfo(
        utils::geometry2d::Point2D&& sensorPosition,
        utils::geometry2d::Point2D&& beaconPosition);
    const utils::geometry2d::Point2D& getSensorPosition() const;
    const utils::geometry2d::Point2D& getBeaconPosition() const;
    uint32_t getDistance() const;
    std::optional<utils::geometry2d::Point2D> stepAroundPerimeter()
        const noexcept;
    bool isCovered(const utils::geometry2d::Point2D& testPoint) const;
    bool hasBeaconAt(const utils::geometry2d::Point2D& testPoint) const;

private:
    const utils::geometry2d::Point2D mSensorPosition;
    const utils::geometry2d::Point2D mBeaconPosition;
    const uint32_t mDistance;
    std::optional<utils::geometry2d::Point2D> mLastPerimeterPosition;
};

} // namespace aoc_2022_15

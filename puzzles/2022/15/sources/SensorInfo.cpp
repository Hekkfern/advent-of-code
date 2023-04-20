#include "SensorInfo.hpp"

#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2022_15 {

SensorInfo::SensorInfo(
    utils::geometry2d::Point2D<int32_t>&& sensorPosition,
    utils::geometry2d::Point2D<int32_t>&& beaconPosition)
    : mSensorPosition{std::move(sensorPosition)}
    , mBeaconPosition{std::move(beaconPosition)}
    , mDistance{Vector2D<int32_t>{sensorPosition, beaconPosition}.distance()}
    , mSquareDiamond2D(sensorPosition, mDistance)
{
}

uint64_t SensorInfo::getDistance() const { return mDistance; }

const Point2D<int32_t>& SensorInfo::getSensorPosition() const
{
    return mSensorPosition;
}

const Point2D<int32_t>& SensorInfo::getBeaconPosition() const
{
    return mBeaconPosition;
}

std::optional<Point2D<int32_t>> SensorInfo::stepAroundOutside()
{
    return mSquareDiamond2D.stepAroundOutside();
}

bool SensorInfo::isCovered(const Point2D<int32_t>& testPoint) const
{
    return mSquareDiamond2D.isInside(testPoint);
}

bool SensorInfo::hasBeaconAt(const Point2D<int32_t>& testPoint) const
{
    return mBeaconPosition == testPoint;
}

} // namespace aoc_2022_15

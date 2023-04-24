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

Point2D<int32_t> const& SensorInfo::getSensorPosition() const
{
    return mSensorPosition;
}

Point2D<int32_t> const& SensorInfo::getBeaconPosition() const
{
    return mBeaconPosition;
}

std::optional<Point2D<int32_t>> SensorInfo::stepAroundOutside()
{
    return mSquareDiamond2D.stepAroundOutside();
}

bool SensorInfo::isCovered(Point2D<int32_t> const& testPoint) const
{
    return mSquareDiamond2D.isInside(testPoint);
}

bool SensorInfo::hasBeaconAt(Point2D<int32_t> const& testPoint) const
{
    return mBeaconPosition == testPoint;
}

} // namespace aoc_2022_15

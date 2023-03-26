#include "SensorInfo.hpp"

#include <utils/geometry2d/Vector2D.hpp>

using namespace utils::geometry2d;

namespace aoc_2022_15 {

SensorInfo::SensorInfo(
    utils::geometry2d::Point2D&& sensorPosition,
    utils::geometry2d::Point2D&& beaconPosition)
    : mSensorPosition{ std::move(sensorPosition) }
    , mBeaconPosition{ std::move(beaconPosition) }
    , mDistance{ Vector2D{ sensorPosition, beaconPosition }.distance() }
    , mSquareDiamond2D(sensorPosition, mDistance)
{
}

uint32_t SensorInfo::getDistance() const { return mDistance; }

const Point2D& SensorInfo::getSensorPosition() const { return mSensorPosition; }

const Point2D& SensorInfo::getBeaconPosition() const { return mBeaconPosition; }

std::optional<Point2D> SensorInfo::stepAroundPerimeter() const noexcept
{
    return mSquareDiamond2D.stepAroundPerimeter();
}

bool SensorInfo::isCovered(const Point2D& testPoint) const
{
    return mSquareDiamond2D.isInside(testPoint);
}

bool SensorInfo::hasBeaconAt(const Point2D& testPoint) const
{
    return mBeaconPosition == testPoint;
}

} // namespace aoc_2022_15

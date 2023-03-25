#include "SensorInfo.hpp"

using namespace utils::geometry2d;

namespace aoc_2022_15 {

SensorInfo::SensorInfo(
    utils::geometry2d::Point2D&& sensorPosition,
    utils::geometry2d::Point2D&& beaconPosition)
    : mSensorPosition{ std::move(sensorPosition) }
    , mBeaconPosition{ std::move(beaconPosition) }
    , mDistance{ Vector2D{ sensorPosition, beaconPosition }.distance() }
{
}

uint32_t SensorInfo::getDistance() const { return mDistance; }

const Point2D& SensorInfo::getSensorPosition() const { return mSensorPosition; }

const Point2D& SensorInfo::getBeaconPosition() const { return mBeaconPosition; }

std::optional<Point2D> SensorInfo::stepAroundPerimeter() const noexcept
{
    const auto& [sensorCoordX, sensorCoordY] = mSensorPosition.getCoordinates();
    if (!mLastPerimeterPosition) {
        // First step around the perimeter, start on top
        return std::make_optional<Point2D>(
            sensorCoordX, (sensorCoordY - static_cast<int32_t>(mDistance) - 1));
    }

    const auto& [lastPositionCoordX, lastPositionCoordY]
        = mLastPerimeterPosition->getCoordinates();
    if ((lastPositionCoordY < sensorCoordY)
        && (lastPositionCoordX >= sensorCoordX)) {
        return std::make_optional<Point2D>(
            lastPositionCoordX + 1,
            lastPositionCoordY + 1); // upper right, downwards
    } else if (
        (lastPositionCoordY >= sensorCoordY)
        && (lastPositionCoordX > sensorCoordX)) {
        return std::make_optional<Point2D>(
            lastPositionCoordX - 1,
            lastPositionCoordY + 1); // lower right, downwards
    } else if (
        (lastPositionCoordY > sensorCoordY)
        && (lastPositionCoordX <= sensorCoordX)) {
        return std::make_optional<Point2D>(
            lastPositionCoordX - 1,
            lastPositionCoordY - 1); // lower left, upwards
    } else if (
        (lastPositionCoordY <= sensorCoordY)
        && (lastPositionCoordX < sensorCoordX)) {
        if ((lastPositionCoordX + 1) == sensorCoordX) {
            return std::nullopt; // circumference completed
        } else {
            return std::make_optional<Point2D>(
                lastPositionCoordX + 1,
                lastPositionCoordY - 1); // upper left, upwards
        }
    } else {
        assert(false);
        return std::nullopt;
    }
}

bool SensorInfo::isCovered(const Point2D& testPoint) const
{
    return Vector2D{ mSensorPosition, testPoint }.distance() <= mDistance;
}
bool SensorInfo::hasBeaconAt(const Point2D& testPoint) const
{
    return mBeaconPosition == testPoint;
}

} // namespace aoc_2022_15

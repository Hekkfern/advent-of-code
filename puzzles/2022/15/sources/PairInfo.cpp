#include "PairInfo.hpp"

using namespace utils::geometry2d;

namespace aoc_2022_15 {

PairInfo::PairInfo(
    utils::geometry2d::Point2D&& sensorPosition,
    utils::geometry2d::Point2D&& beaconPosition)
    : mSensorPosition{ std::move(sensorPosition) }
    , mBeaconPosition{ std::move(beaconPosition) }
    , mSensorToBeaconVector{ Vector2D{ sensorPosition, beaconPosition } }
    , mDistance{ mSensorToBeaconVector.distance() }
{
}

uint32_t PairInfo::getDistance() const { return mDistance; }

const utils::geometry2d::Point2D& PairInfo::getSensorPosition() const
{
    return mSensorPosition;
}

const utils::geometry2d::Point2D& PairInfo::getBeaconPosition() const
{
    return mBeaconPosition;
}

const utils::geometry2d::Vector2D& PairInfo::getDifferenceVector() const
{
    return mSensorToBeaconVector;
}

} // namespace aoc_2022_15

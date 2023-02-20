#pragma once

#include "Vector2D.hpp"

namespace utils::geometry2d {

class Direction2D {
public:
    enum Value { Up, Left, Down, Right, UpLeft, DownLeft, UpRight, DownRight };

    /**
     * @brief      Default constructor.
     */
    Direction2D() = delete;
    /**
     * @brief      Initialization constructor.
     *
     * @param[in]  v     Value to initialize the object with.
     */
    constexpr Direction2D(Value v)
        : mValue(v)
    {
    }
    /**
     * @brief      @ref Value conversion operator.
     */
    constexpr operator Value() const { return mValue; }
    /**
     * @brief      Bool conversion operator.
     */
    explicit operator bool() const = delete;

    /**
     * @brief      Returns a string representation of the object.
     *
     * @return     String representation of the object.
     */
    constexpr const char* toString() const
    {
        switch (mValue) {
        case Value::Up:
            return "up";
        case Value::Left:
            return "left";
        case Value::Down:
            return "down";
        case Value::Right:
            return "right";
        case Value::UpLeft:
            return "upleft";
        case Value::DownLeft:
            return "downleft";
        case Value::DownRight:
            return "downright";
        case Value::UpRight:
            return "upright";
        default:
            /* Invalid value */
            return "";
        }
    }

    Vector2D toVector2D() const
    {
        int32_t coordX = 0;
        int32_t coordY = 0;
        switch (mValue) {
        case Direction2D::Left:
        case Direction2D::DownLeft:
        case Direction2D::UpLeft:
            --coordX;
            break;
        case Direction2D::Right:
        case Direction2D::UpRight:
        case Direction2D::DownRight:
            ++coordX;
            break;
        default:
            /* NO STATEMENTS */
            break;
        }
        switch (mValue) {
        case Direction2D::Down:
        case Direction2D::DownRight:
        case Direction2D::DownLeft:
            --coordY;
            break;
        case Direction2D::Up:
        case Direction2D::UpRight:
        case Direction2D::UpLeft:
            ++coordY;
            break;
        default:
            /* NO STATEMENTS */
            break;
        }
        return Vector2D{ coordX, coordY };
    }

private:
    /**
     * Internal value.
     */
    Value mValue;
};

} // namespace utils::geometry2d

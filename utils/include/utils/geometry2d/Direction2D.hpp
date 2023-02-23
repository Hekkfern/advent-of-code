#pragma once

#include "Vector2D.hpp"
#include <string>

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
    std::string toString() const
    {
        using namespace std::string_literals;

        switch (mValue) {
        case Value::Up:
            return "up"s;
        case Value::Left:
            return "left"s;
        case Value::Down:
            return "down"s;
        case Value::Right:
            return "right"s;
        case Value::UpLeft:
            return "upleft"s;
        case Value::DownLeft:
            return "downleft"s;
        case Value::DownRight:
            return "downright"s;
        case Value::UpRight:
            return "upright"s;
        default:
            /* Invalid value */
            return ""s;
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
    constexpr Value getValue() const { return mValue; }

private:
    /**
     * Internal value.
     */
    Value mValue;
};

} // namespace utils::geometry2d

template <> struct std::hash<utils::geometry2d::Direction2D> {
    std::size_t operator()(const utils::geometry2d::Direction2D& k) const
    {
        return std::hash<utils::geometry2d::Direction2D::Value>()(k.getValue());
    }
};

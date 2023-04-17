#pragma once

#include <string>

namespace utils::geometry2d {

/**
 * @brief      This class describes a direction in 2D space. It includes the
 *             four orthogonal directions as well as all their combinations.
 */
class Direction2D {
public:
    /**
     * @brief      Values of the direction (diagonal directions included).
     */
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
    [[nodiscard]] std::string toString() const
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
    /**
     * @brief      Gets the value.
     *
     * @return     The value.
     */
    [[nodiscard]] constexpr Value getValue() const { return mValue; }

private:
    /**
     * Internal value.
     */
    Value mValue;
};

} // namespace utils::geometry2d

template <>
struct std::hash<utils::geometry2d::Direction2D> {
    std::size_t operator()(const utils::geometry2d::Direction2D& k) const
    {
        return std::hash<utils::geometry2d::Direction2D::Value>()(k.getValue());
    }
};

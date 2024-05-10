#pragma once

#include <cassert>
#include <string>

namespace utils::geometry2d {

/**
 * @brief      Describes a direction in 2D space. It includes the four
 *             orthogonal directions as well as all their combinations.
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
    Direction2D() noexcept = delete;
    /**
     * @brief      Initialization constructor.
     *
     * @param[in]  v     Value to initialize the object with.
     */
    constexpr Direction2D(Value v) noexcept
        : mValue(v)
    {
    }
    /**
     * @brief      @ref Value conversion operator.
     */
    constexpr operator Value() const noexcept { return mValue; }
    /**
     * @brief      Bool conversion operator.
     */
    explicit operator bool() const noexcept = delete;
    /**
     * @brief Inverts the direction
     */
    [[nodiscard]] constexpr Direction2D invert() const noexcept
    {
        switch (mValue) {
        case Up:
            return Down;
        case Left:
            return Right;
        case Down:
            return Up;
        case Right:
            return Left;
        case UpLeft:
            return DownRight;
        case DownLeft:
            return UpRight;
        case UpRight:
            return DownLeft;
        case DownRight:
            return UpLeft;
        default:
            /* Invalid value */
            assert(false);
        }
    }
    /**
     * @brief      Returns a string representation of the object.
     *
     * @return     String representation of the object.
     */
    [[nodiscard]] std::string toString() const noexcept
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
            assert(false);
        }
    }
    /**
     * @brief      Gets the value.
     *
     * @return     The value.
     */
    [[nodiscard]] constexpr Value getValue() const noexcept { return mValue; }

private:
    /**
     * Internal value.
     */
    Value mValue;
};

} // namespace utils::geometry2d

template <>
struct std::hash<utils::geometry2d::Direction2D> {
    std::size_t operator()(utils::geometry2d::Direction2D const& k) const
    {
        return std::hash<utils::geometry2d::Direction2D::Value>()(k.getValue());
    }
};

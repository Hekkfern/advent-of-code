#pragma once

#include "../Concepts.hpp"
#include "../Hash.hpp"
#include "Direction2D.hpp"

namespace utils::geometry2d {

/**
 * @brief      Describes spacial coordinates in a 2-dimension system.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <IntegerType T = int32_t>
class Coordinate2D {
public:
    /**
     * @brief      Default constructor
     */
    constexpr explicit Coordinate2D() noexcept = default;
    /**
     * @brief      Parametrized constructor
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    constexpr explicit Coordinate2D(T x, T y) noexcept
        : mX{x}
        , mY{y}
    {
    }
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    [[nodiscard]] constexpr T getX() const noexcept { return mX; }
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    [[nodiscard]] constexpr T getY() const noexcept { return mY; }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool
    operator==(Coordinate2D const& other) const noexcept
    {
        return mX == other.mX && mY == other.mY;
    }
    /**
     * @brief      Represents this class as a @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const
    {
        return "[" + std::to_string(mX) + "," + std::to_string(mY) + "]";
    }
    /**
     * @brief      Getter for structured binding
     *
     * @tparam     N     Number of tuple-like parameters.
     *
     * @return     The value of the internal variable, according to @p N.
     */
    template <std::size_t N>
    [[nodiscard]] decltype(auto) get() const
    {
        if constexpr (N == 0) {
            return mX;
        } else if constexpr (N == 1) {
            return mY;
        }
    }
    /**
     * @brief      Calculates the resulting coordinates of applying an unitary
     * movement towards the given direction to the current coordinates.
     *
     * @param[in]  direction  The direction of the movement.
     *
     * @return     Resulting position of the movement.
     */
    [[nodiscard]] constexpr std::optional<Coordinate2D<T>>
    move(Direction2D const& direction) const noexcept
    {
        T coordX{0};
        T coordY{0};
        switch (direction.getValue()) {
        case Direction2D::Left:
        case Direction2D::DownLeft:
        case Direction2D::UpLeft:
            if (mX == std::numeric_limits<T>::min()) {
                return {};
            }
            --coordX;
            break;
        case Direction2D::Right:
        case Direction2D::UpRight:
        case Direction2D::DownRight:
            if (mX == std::numeric_limits<T>::max()) {
                return {};
            }
            ++coordX;
            break;
        default:
            /* NO STATEMENTS */
            break;
        }
        switch (direction.getValue()) {
        case Direction2D::Down:
        case Direction2D::DownRight:
        case Direction2D::DownLeft:
            if (mY == std::numeric_limits<T>::min()) {
                return {};
            }
            --coordY;
            break;
        case Direction2D::Up:
        case Direction2D::UpRight:
        case Direction2D::UpLeft:
            if (mY == std::numeric_limits<T>::min()) {
                return {};
            }
            ++coordY;
            break;
        default:
            /* NO STATEMENTS */
            break;
        }
        return Coordinate2D<T>{mX + coordX, mY + coordY};
    }

    /**
     * @brief      Calculates the hash of this instance
     *
     * @return     Hash of the instance
     */
    [[nodiscard]] std::size_t calculateHash() const noexcept
    {
        std::size_t seed{0ULL};
        utils::hash::hash_combine(seed, mX);
        utils::hash::hash_combine(seed, mY);
        return seed;
    }

private:
    /**
     * @brief      "Insert string into stream" operator.
     *
     * @param[in]  os    The output stream.
     * @param[in]  obj   The instance.
     *
     * @return     The updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, Coordinate2D const& obj)
    {
        os << obj.toString();
        return os;
    }

    /**
     * Stores coordinate X.
     */
    T mX{0};
    /**
     * Stores coordinate Y.
     */
    T mY{0};
};

} // namespace utils::geometry2d

template <IntegerType T>
struct std::hash<utils::geometry2d::Coordinate2D<T>> {
    std::size_t
    operator()(utils::geometry2d::Coordinate2D<T> const& instance) const
    {
        return instance.calculateHash();
    }
};

/* Support for structured binding */
template <class T>
struct std::tuple_size<utils::geometry2d::Coordinate2D<T>>
    : std::integral_constant<std::size_t, 2> { };
/* Support for structured binding */
template <class T>
struct std::tuple_element<0, utils::geometry2d::Coordinate2D<T>> {
    using type = T;
};
/* Support for structured binding */
template <class T>
struct std::tuple_element<1, utils::geometry2d::Coordinate2D<T>> {
    using type = T;
};

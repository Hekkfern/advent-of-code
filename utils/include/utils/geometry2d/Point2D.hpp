#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <utils/Concepts.hpp>
#include <utils/Hash.hpp>

namespace utils::geometry2d {

/**
 * @brief      Describes a point in 2D space.
 *
 * @tparam     T     Type of the coordinate values.
 */
template <SignedIntegerType T = int32_t>
class Point2D {
public:
    static constexpr uint32_t Dimension{2U};
    /**
     * @brief      Default constructor.
     */
    constexpr explicit Point2D() noexcept = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    constexpr explicit Point2D(T x, T y) noexcept
        : mX{x}
        , mY{y}
    {
    }
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    [[nodiscard]] constexpr std::array<T, Dimension>
    getCoordinates() const noexcept
    {
        return std::to_array({mX, mY});
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
     * @brief      Gets a list of all the colliding points.
     *
     * @return     List of colliding points.
     */
    [[nodiscard]] constexpr std::array<Point2D, 2 * Dimension>
    getNeighbors() const noexcept
    {
        return std::to_array(
            {Point2D{mX, mY + 1},
             Point2D{mX + 1, mY},
             Point2D{mX, mY - 1},
             Point2D{mX - 1, mY + 1}});
    }
    /**
     * @brief      Sets the coordinate X.
     *
     * @param[in]  x     The coordinate X.
     *
     * @return     New instance with the new coordinate.
     */
    [[nodiscard]] constexpr Point2D setX(T const x) const noexcept
    {
        Point2D result{*this};
        result.mX = x;
        return result;
    }
    /**
     * @brief      Sets the coordinate Y.
     *
     * @param[in]  y     The coordinate Y.
     *
     * @return     New instance with the new coordinate.
     */
    [[nodiscard]] constexpr Point2D setY(T const y) const noexcept
    {
        Point2D result{*this};
        result.mY = y;
        return result;
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] constexpr bool
    operator==(Point2D<T> const& other) const noexcept
        = default;
    /**
     * @brief      Invert the coordinates respect origin.
     *
     * @return     The resulting object.
     */
    [[nodiscard]] constexpr Point2D invert() const noexcept
    {
        return Point2D{-mX, -mY};
    }
    /**
     * @brief      Negation operator.
     *
     * @return     The result of the subtraction
     */
    [[nodiscard]] constexpr Point2D operator-() const noexcept
    {
        return invert();
    }
    /**
     * @brief      Mirror respect X axis.
     *
     * @return     The resulting object.
     */
    [[nodiscard]] constexpr Point2D mirrorX() const noexcept
    {
        return Point2D{mX, -mY};
    }
    /**
     * @brief      Mirror respect Y axis.
     *
     * @return     The resulting object.
     */
    [[nodiscard]] constexpr Point2D mirrorY() const noexcept
    {
        return Point2D{-mX, mY};
    }
    /**
     * @brief      Factory method to create a new Point based on the selected
     *             coordinates.
     *
     * @param[in]  x     The coordinate X.
     * @param[in]  y     The coordinate Y.
     *
     * @tparam     U     Type of the input coordinates.
     *
     * @return     New point.
     */
    template <std::integral U>
    [[nodiscard]] constexpr static Point2D<T> create(U x, U y) noexcept
    {
        return Point2D{static_cast<T>(x), static_cast<T>(y)};
    }
    /**
     * @brief      Represents this class as a @ref std::string
     *
     * @return     String representing this class.
     */
    [[nodiscard]] std::string toString() const noexcept
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
     * @brief      Calculates the hash of this instance
     *
     * @return     Hash of the instance
     */
    [[nodiscard]] constexpr std::size_t calculateHash() const noexcept
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
     * @param[in]  obj   The object.
     *
     * @return     The updated output stream.
     */
    friend std::ostream&
    operator<<(std::ostream& os, Point2D<T> const& obj) noexcept
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

template <SignedIntegerType T>
struct std::hash<utils::geometry2d::Point2D<T>> {
    std::size_t
    operator()(utils::geometry2d::Point2D<T> const& obj) const noexcept
    {
        return obj.calculateHash();
    }
};

/* Support for structured binding */
template <class T>
struct std::tuple_size<utils::geometry2d::Point2D<T>>
    : std::integral_constant<
          std::size_t,
          utils::geometry2d::Point2D<T>::Dimension> { };
template <class T>
struct std::tuple_element<0, utils::geometry2d::Point2D<T>> {
    using type = T;
};
template <class T>
struct std::tuple_element<1, utils::geometry2d::Point2D<T>> {
    using type = T;
};

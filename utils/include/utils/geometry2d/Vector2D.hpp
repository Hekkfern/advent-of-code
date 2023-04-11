#pragma once

#include <cstdint>
#include <memory>
#include <utility>

namespace utils::geometry2d {

class Point2D;

/**
 * @brief      This class describes a Vector (i.e. a directional arrow) in 2D
 *             space.
 */
class Vector2D {
public:
    /**
     * @brief      Default constructor.
     */
    Vector2D();
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     Coordinate X.
     * @param[in]  y     Coordinate Y.
     */
    explicit Vector2D(int32_t x, int32_t y);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  origin       The origin point.
     * @param[in]  destination  The destination point.
     */
    explicit Vector2D(const Point2D& origin, const Point2D& destination);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  coords  Pair of coordinates (X,Y).
     */
    explicit Vector2D(const std::pair<int32_t, int32_t>& coords);
    /**
     * @brief      Gets the coordinates.
     *
     * @return     The coordinates as a pair (X,Y).
     */
    std::pair<int32_t, int32_t> getCoordinates() const;
    /**
     * @brief      Gets the coordinate X.
     *
     * @return     The coordinate X.
     */
    int32_t getX() const;
    /**
     * @brief      Gets the coordinate Y.
     *
     * @return     The coordinate Y.
     */
    int32_t getY() const;
    /**
     * @brief      Gets the absolute length of each coordinate.
     *
     * @return     Pair of absolute coordinates (X,Y).
     */
    std::pair<size_t, size_t> size() const;
    /**
     * @brief      { function_description }
     *
     * @return     { description_of_the_return_value }
     */
    uint32_t range() const;
    /**
     * @brief      Calculates the Manhattan Distance.
     *
     * @return     The Manhattan Distance value.
     *
     * @see        https://en.wikipedia.org/wiki/Taxicab_geometry
     */
    uint32_t distance() const;
    /**
     * @brief      Modifies the vector so the lengths becomes one (positive or negative) up most, keeping the same
     *             direction.
     */
    void normalize();
    /**
     * @brief      Creates a normalized vector from this one.
     *
     * @return     The normalized vector.
     */
    Vector2D getNormalized() const;
    /**
     * @brief      Determines if the vector is empty, i.e., both coordinates are
     *             zero.
     *
     * @return     True if it is empty, False otherwise.
     */
    bool isZero() const;
    /**
     * @brief      Determines if it is a horitzontal vector, i.e. its coordinate
     *             Y is zero.
     *
     * @return     True if it is horizontal, False otherwise.
     */
    bool isHorizontal() const;
    /**
     * @brief      Determines if it is a vertical vector, i.e. its coordinate X
     *             is zero.
     *
     * @return     True if it is vertical, False otherwise.
     */
    bool isVertical() const;
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    bool operator==(const Vector2D& other) const;
    /**
     * @brief      Addition operator, which sums the coordinates of both
     *             objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the addition.
     */
    Vector2D operator+(const Vector2D& other) const;
    /**
     * @brief      Negation operator, which inverts the sign of both coordinates
     *             of the vector, i.e. inverts the direction of the vector.
     *
     * @return     The inverted vector.
     */
    Vector2D operator-() const;
    /**
     * @brief      Substraction operator, which substracts the coordinates of
     *             both objects.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the substraction.
     */
    Vector2D operator-(const Vector2D& other) const;
    /**
     * @brief      Factory method to create a new Vector based on the selected
     *             coordinates.
     *
     * @param[in]  x     The coordinate X.
     * @param[in]  y     The coordinate Y.
     *
     * @tparam     T     Type of the coordinates.
     *
     * @return     New vector.
     */
    template <std::integral T> [[nodiscard]] static Vector2D create(T x, T y)
    {
        return Vector2D{ static_cast<int32_t>(x), static_cast<int32_t>(y) };
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector2D);

    /**
     * Stores coordinate X.
     */
    int32_t mX = 0;
    /**
     * Stores coordinate Y.
     */
    int32_t mY = 0;
};

/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  vector2D  The vector to scale.
 * @param[in]  value     The scalar value to scale by.
 *
 * @return     Scaled vector by a scalar.
 */
Vector2D operator*(const Vector2D& vector2D, const int32_t value);
/**
 * @brief      Multiplication operator, which multiplies the coordinates of a
 *             vector by a scalar value.
 *
 * @param[in]  value     The scalar value to scale by.
 * @param[in]  vector2D  The vector to scale.
 *
 * @return     Scaled vector by a scalar.
 */
Vector2D operator*(const int32_t value, const Vector2D& vector2D);
/**
 * @brief      "Insert string into stream" operator.
 *
 * @param      os        The output stream.
 * @param[in]  vector2D  The vector.
 *
 * @return     The updated output stream.
 */
std::ostream& operator<<(std::ostream& os, const Vector2D& vector2D);

} // namespace utils::geometry2d

template <> struct std::hash<utils::geometry2d::Vector2D> {
    std::size_t operator()(const utils::geometry2d::Vector2D& k) const noexcept
    {
        return std::hash<int32_t>()(k.getX()) ^ std::hash<int32_t>()(k.getY());
    }
};
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/Math.hpp>

using namespace utils::math;

TEST_CASE("[Math] modulusFloor() method", "[utils][Math]")
{
    SECTION("Run-time")
    {
        REQUIRE(modulusFloor(4, 3) == 1);
        REQUIRE(modulusFloor(3, 3) == 0);
        REQUIRE(modulusFloor(2, 3) == 2);
        REQUIRE(modulusFloor(1, 3) == 1);
        REQUIRE(modulusFloor(0, 3) == 0);
        REQUIRE(modulusFloor(-1, 3) == 2);
        REQUIRE(modulusFloor(-2, 3) == 1);
        REQUIRE(modulusFloor(-3, 3) == 0);
        REQUIRE(modulusFloor(-4, 3) == 2);
    }
    SECTION("Compile-time")
    {
        STATIC_REQUIRE(modulusFloor(4, 3) == 1);
        STATIC_REQUIRE(modulusFloor(3, 3) == 0);
        STATIC_REQUIRE(modulusFloor(2, 3) == 2);
        STATIC_REQUIRE(modulusFloor(1, 3) == 1);
        STATIC_REQUIRE(modulusFloor(0, 3) == 0);
        STATIC_REQUIRE(modulusFloor(-1, 3) == 2);
        STATIC_REQUIRE(modulusFloor(-2, 3) == 1);
        STATIC_REQUIRE(modulusFloor(-3, 3) == 0);
        STATIC_REQUIRE(modulusFloor(-4, 3) == 2);
    }
}

TEST_CASE("[Math] lcm() method", "[utils][Math]")
{
    SECTION("Two values") { REQUIRE(lcm(3, 6) == 6); }

    SECTION("More than two values") { REQUIRE(lcm(3, 6, 12, 36) == 36); }
}

TEST_CASE("[Math] gcd() method", "[utils][Math]")
{
    SECTION("Two values") { REQUIRE(gcd(15, 70) == 5); }

    SECTION("More than two values") { REQUIRE(gcd(30, 40, 60) == 10); }
}

TEST_CASE("[Math] getLowestDegreePolynomial() method", "[utils][Math]")
{
    // Helper function to compare two vectors within a tolerance
    static auto const areVectorsApproxEqual =
        [](std::vector<double> const& v1,
           std::vector<double> const& v2,
           double tolerance = 1e-9) -> bool {
        if (v1.size() != v2.size())
            return false;
        for (std::size_t i = 0; i < v1.size(); ++i) {
            if (std::abs(v1[i] - v2[i]) > tolerance) {
                return false;
            }
        }
        return true;
    };

    SECTION("Input with three different points")
    {
        SECTION("Resulting in a simple parabola")
        {
            std::vector<std::pair<double, double>> const coords{
                {1.0, 1.0}, {2.0, 4.0}, {3.0, 9.0}};
            auto const result{getLowestDegreePolynomial(coords)};
            // f(x) = x^2
            std::vector<double> const expected{0.0, 0.0, 1.0};
            REQUIRE(areVectorsApproxEqual(result, expected));
        }
        SECTION("Resulting in a line")
        {
            std::vector<std::pair<double, double>> const coords{
                {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
            auto const result{getLowestDegreePolynomial(coords)};
            // f(x) = x
            std::vector<double> const expected{0.0, 1.0, 0.0};
            REQUIRE(areVectorsApproxEqual(result, expected));
        }
        SECTION("Resulting in a complex parabola")
        {
            std::vector<std::pair<double, double>> const coords{
                {0.0, -1.0}, {1.0, 1.0}, {4.0, 1.0}};
            auto const result{getLowestDegreePolynomial(coords)};
            // f(x) = -0.5x^2 + 2.5x - 1
            std::vector<double> const expected{-1.0, 2.5, -0.5};
            REQUIRE(areVectorsApproxEqual(result, expected));
        }
    }

    SECTION("Input with no points")
    {
        std::vector<std::pair<double, double>> const coords{};
        auto const result{getLowestDegreePolynomial(coords)};
        // No polynomial possible
        std::vector<double> const expected;
        REQUIRE(result == expected);
    }

    SECTION("Input with one point")
    {
        std::vector<std::pair<double, double>> const coords{{2.0, 4.0}};
        auto const result{getLowestDegreePolynomial(coords)};
        // f(x) = 4
        std::vector<double> const expected{4.0};
        REQUIRE(areVectorsApproxEqual(result, expected));
    }
}

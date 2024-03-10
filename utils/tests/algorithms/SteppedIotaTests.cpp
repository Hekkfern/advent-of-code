#define CATCH_CONFIG_MAIN
#include "utils/algorithms/SteppedIota.hpp"
#include <catch.hpp>

using namespace utils::algorithms;

TEST_CASE("[Algorithms] stepped_iota method", "[utils][Algorithms]")
{
    SECTION("Without limit")
    {
        int count{0};
        for (int const x : stepped_iota(0, 2)) {
            if (x == 10)
                break;
            ++count;
        }
        CHECK(count == 5);
    }
    SECTION("With limit")
    {
        int count{0};
        for (int const x : stepped_iota(0, 10, 2)) {
            (void)x;
            ++count;
        }
        CHECK(count == 5);
    }
}

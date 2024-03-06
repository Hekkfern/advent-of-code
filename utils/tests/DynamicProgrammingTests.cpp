#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/DynamicProgramming.hpp>

using namespace utils::dp;

TEST_CASE(
    "[DynamicProgramming] longestCommonSubsequence() method",
    "[utils][DynamicProgramming]")
{
    std::string const pattern1{"RGBGARGA"};
    std::string const pattern2{"BGRARG"};
    CHECK(longestCommonSubsequence(pattern1, pattern2) == 5);
}

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/File.hpp>

TEST_CASE("[File] readFirstLine method", "[utils][File]")
{
    auto const firstline{utils::file::readFirstLine("test_assets/File1.txt")};
    CHECK(firstline);
    CHECK_FALSE(firstline->empty());
}

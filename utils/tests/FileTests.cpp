#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utils/File.hpp>

TEST_CASE("[File] readFirstLine method", "[utils][File]")
{
    SECTION("File exists")
    {
        SECTION("File with content")
        {
            auto const firstline{utils::file::readFirstLine(
                "test_assets/FileWithTextLines.txt")};
            CHECK(firstline);
            CHECK_FALSE(firstline->empty());
            CHECK(*firstline == "My first line");
        }
        SECTION("Empty file")
        {
            auto const firstline{
                utils::file::readFirstLine("test_assets/EmptyFile.txt")};
            CHECK(firstline);
            CHECK(firstline->empty());
        }
    }
    SECTION("File doesn't exist")
    {
        auto const firstline{utils::file::readFirstLine("unknown.txt")};
        CHECK_FALSE(firstline);
    }
}

TEST_CASE("[File] readWholeFile method", "[utils][File]")
{
    SECTION("File exists")
    {
        SECTION("File with content")
        {
            auto const text{utils::file::readWholeFile(
                "test_assets/FileWithTextLines.txt")};
            CHECK(text);
            CHECK_FALSE(text->empty());
            CHECK(*text == "My first line\nThe second line");
        }
        SECTION("Empty file")
        {
            auto const text{
                utils::file::readFirstLine("test_assets/EmptyFile.txt")};
            CHECK(text);
            CHECK(text->empty());
        }
    }
    SECTION("File doesn't exist")
    {
        auto const text{utils::file::readWholeFile("unknown.txt")};
        CHECK_FALSE(text);
    }
}

TEST_CASE("[File] readListOfStrings method", "[utils][File]")
{
    SECTION("File exists")
    {
        SECTION("File with content")
        {
            auto const lines{utils::file::readListOfStrings(
                "test_assets/FileWithTextLines.txt")};
            CHECK(lines);
            CHECK(lines->size() == 2);
            CHECK((*lines)[0] == "My first line");
            CHECK((*lines)[1] == "The second line");
        }
        SECTION("Empty file")
        {
            auto const lines{
                utils::file::readFirstLine("test_assets/EmptyFile.txt")};
            CHECK(lines);
            CHECK(lines->empty());
        }
    }
    SECTION("File doesn't exist")
    {
        auto const lines{utils::file::readListOfStrings("unknown.txt")};
        CHECK_FALSE(lines);
    }
}

TEST_CASE("[File] readListOfNumbers method", "[utils][File]")
{
    SECTION("File exists")
    {
        SECTION("File with content")
        {
            SECTION("File with numbers")
            {
                auto const numbers{utils::file::readListOfNumbers(
                    "test_assets/FileWithNumberLines.txt")};
                CHECK(numbers);
                CHECK(numbers->size() == 3);
                CHECK((*numbers)[0] == 1LL);
                CHECK((*numbers)[1] == 2LL);
                CHECK((*numbers)[2] == 3LL);
            }
            SECTION("File with text")
            {
                auto const numbers{utils::file::readListOfNumbers(
                    "test_assets/FileWithTextLines.txt")};
                CHECK(numbers);
                CHECK(numbers->empty());
            }
        }
        SECTION("Empty file")
        {
            auto const numbers{
                utils::file::readListOfNumbers("test_assets/EmptyFile.txt")};
            CHECK(numbers);
            CHECK(numbers->empty());
        }
    }
    SECTION("File doesn't exist")
    {
        auto const numbers{utils::file::readListOfNumbers("unknown.txt")};
        CHECK_FALSE(numbers);
    }
}

TEST_CASE("[File] readGroupsOfNumbers method", "[utils][File]")
{
    SECTION("File exists")
    {
        SECTION("File with content")
        {
            SECTION("File with numbers")
            {
                SECTION("With groups")
                {
                    auto const numbers{utils::file::readGroupsOfNumbers(
                        "test_assets/FileWithGroupedNumbers.txt")};
                    CHECK(numbers);
                    CHECK(numbers->size() == 3);
                    CHECK((*numbers)[0].size() == 2);
                    CHECK((*numbers)[0][0] == 1);
                    CHECK((*numbers)[0][1] == 2);
                    CHECK((*numbers)[1].size() == 2);
                    CHECK((*numbers)[1][0] == 3);
                    CHECK((*numbers)[1][1] == 4);
                    CHECK((*numbers)[2].size() == 1);
                    CHECK((*numbers)[2][0] == 5);
                }
                SECTION("Without groups")
                {
                    auto const numbers{utils::file::readGroupsOfNumbers(
                        "test_assets/FileWithNumberLines.txt")};
                    CHECK(numbers);
                    CHECK(numbers->size() == 1);
                    CHECK((*numbers)[0].size() == 3);
                    CHECK((*numbers)[0][0] == 1);
                    CHECK((*numbers)[0][1] == 2);
                    CHECK((*numbers)[0][2] == 3);
                }
            }
            SECTION("File with text")
            {
                auto const numbers{utils::file::readGroupsOfNumbers(
                    "test_assets/FileWithTextLines.txt")};
                CHECK(numbers);
                CHECK(numbers->empty());
            }
        }
        SECTION("Empty file")
        {
            auto const numbers{
                utils::file::readGroupsOfNumbers("test_assets/EmptyFile.txt")};
            CHECK(numbers);
            CHECK(numbers->empty());
        }
    }
    SECTION("File doesn't exist")
    {
        auto const numbers{utils::file::readGroupsOfNumbers("unknown.txt")};
        CHECK_FALSE(numbers);
    }
}


TEST_CASE("[File] readMatrixOfChars method", "[utils][File]")
{
    SECTION("File exists")
    {
        SECTION("File with content")
        {
                auto const data{utils::file::readMatrixOfChars(
                    "test_assets/FileWithMatrixOfChars.txt")};
                CHECK(data);
                CHECK(data->size() == 2ULL);
                CHECK((*data)[0].size() == 3ULL);
                CHECK((*data)[0][0] == 'a');
                CHECK((*data)[0][1] == 'b');
                CHECK((*data)[0][2] == 'c');
                CHECK((*data)[1].size() == 3ULL);
                CHECK((*data)[1][0] == 'd');
                CHECK((*data)[1][1] == 'e');
                CHECK((*data)[1][2] == 'f');

        }
        SECTION("Empty file")
        {
            auto const data{
                utils::file::readMatrixOfChars("test_assets/EmptyFile.txt")};
            CHECK(data);
            CHECK(data->empty());
        }
    }
    SECTION("File doesn't exist")
    {
        auto const data{utils::file::readMatrixOfChars("unknown.txt")};
        CHECK_FALSE(data);
    }
}

TEST_CASE("[File] readMatrixOfDigits method", "[utils][File]")
{
    SECTION("File exists")
    {
        SECTION("File with content")
        {
            auto const data{utils::file::readMatrixOfDigits(
                "test_assets/FileWithMatrixOfDigits.txt")};
            CHECK(data);
            CHECK(data->size() == 2ULL);
            CHECK((*data)[0].size() == 3ULL);
            CHECK((*data)[0][0] == 1U);
            CHECK((*data)[0][1] == 2U);
            CHECK((*data)[0][2] == 3U);
            CHECK((*data)[1].size() == 3ULL);
            CHECK((*data)[1][0] == 4U);
            CHECK((*data)[1][1] == 5U);
            CHECK((*data)[1][2] == 6U);

        }
        SECTION("Empty file")
        {
            auto const data{
                utils::file::readMatrixOfDigits("test_assets/EmptyFile.txt")};
            CHECK(data);
            CHECK(data->empty());
        }
    }
    SECTION("File doesn't exist")
    {
        auto const data{utils::file::readMatrixOfDigits("unknown.txt")};
        CHECK_FALSE(data);
    }
}

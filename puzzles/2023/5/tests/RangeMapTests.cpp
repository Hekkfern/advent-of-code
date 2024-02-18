#include "../sources/RangeMap.hpp"
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace aoc_2023_5;
using namespace utils::interval;

TEST_CASE("[RangeMap] Convert single key", "[2023][2023_5][RangeMap]")
{
    RangeMap rangeMap;
    SECTION("Empty map") { CHECK(rangeMap.convert(12LL) == 12LL); }
    SECTION("Map with one single item")
    {
        rangeMap.addSection(100, 20, 10);
        SECTION("Key is contained in the map")
        {
            CHECK(rangeMap.convert(27LL) == 107LL);
        }
        SECTION("Key is not contained in the map")
        {
            CHECK(rangeMap.convert(12LL) == 12LL);
        }
    }
    SECTION("Map with multiple items")
    {
        rangeMap.addSection(100, 20, 10);
        rangeMap.addSection(55, 35, 10);
        SECTION("Key is contained in the map")
        {
            CHECK(rangeMap.convert(27LL) == 107LL);
            CHECK(rangeMap.convert(36LL) == 56LL);
        }
        SECTION("Key is not contained in the map")
        {
            CHECK(rangeMap.convert(12LL) == 12LL);
        }
    }
}

TEST_CASE("[RangeMap] Convert interval key", "[2023][2023_5][RangeMap]")
{
    RangeMap rangeMap;
    SECTION("Empty map") { CHECK(rangeMap.convert(12LL) == 12LL); }
    SECTION("Map with one single item")
    {
        rangeMap.addSection(100, 20, 10);
        SECTION("Key is contained in the map")
        {
            Interval const input{27LL, 28LL};
            auto const result{rangeMap.convert(input)};
            REQUIRE(input.size() == result.count());
            REQUIRE(result.get().size() == 1);
            CHECK(result.get()[0] == Interval{107LL, 108LL});
        }
        SECTION("Key is not contained in the map")
        {
            Interval const input{12LL, 13LL};
            auto const result{rangeMap.convert(input)};
            REQUIRE(input.size() == result.count());
            REQUIRE(result.get().size() == 1);
            CHECK(result.get()[0] == Interval{12LL, 13LL});
        }
        SECTION("Key is semi-contained (left) in the map")
        {
            Interval const input{18LL, 22LL};
            auto const result{rangeMap.convert(input)};
            REQUIRE(input.size() == result.count());
            REQUIRE(result.get().size() == 2);
            CHECK(result.get()[0] == Interval{18LL, 19LL});
            CHECK(result.get()[1] == Interval{100LL, 102LL});
        }
        SECTION("Key is semi-contained (right) in the map")
        {
            Interval const input{28LL, 33LL};
            auto const result{rangeMap.convert(input)};
            REQUIRE(input.size() == result.count());
            REQUIRE(result.get().size() == 2);
            CHECK(result.get()[0] == Interval{30LL, 33LL});
            CHECK(result.get()[1] == Interval{108LL, 109LL});
        }
    }
    SECTION("Map with multiple items")
    {
        rangeMap.addSection(100, 20, 10);
        rangeMap.addSection(55, 35, 10);
        rangeMap.sort();
        SECTION("Key is contained in the map")
        {
            SECTION("In first range")
            {
                Interval const input{27LL, 28LL};
                auto const result{rangeMap.convert(input)};
                REQUIRE(input.size() == result.count());
                REQUIRE(result.get().size() == 1);
                CHECK(result.get()[0] == Interval{107LL, 108LL});
            }
            SECTION("In second range")
            {
                Interval const input{36LL, 37LL};
                auto const result{rangeMap.convert(input)};
                REQUIRE(input.size() == result.count());
                REQUIRE(result.get().size() == 1);
                CHECK(result.get()[0] == Interval{56LL, 57LL});
            }
        }
        SECTION("Key is not contained in the map")
        {
            Interval const input{12LL, 13LL};
            auto const result{rangeMap.convert(input)};
            REQUIRE(input.size() == result.count());
            REQUIRE(result.get().size() == 1);
            CHECK(result.get()[0] == Interval{12LL, 13LL});
        }
        SECTION("Key is semi-contained (left) in the map")
        {
            Interval const input{18LL, 22LL};
            auto const result{rangeMap.convert(input)};
            REQUIRE(input.size() == result.count());
            REQUIRE(result.get().size() == 2);
            CHECK(result.get()[0] == Interval{18LL, 19LL});
            CHECK(result.get()[1] == Interval{100LL, 102LL});
        }
        SECTION("Key is semi-contained (right) in the map")
        {
            Interval const input{28LL, 33LL};
            auto const result{rangeMap.convert(input)};
            REQUIRE(input.size() == result.count());
            REQUIRE(result.get().size() == 2);
            CHECK(result.get()[0] == Interval{30LL, 33LL});
            CHECK(result.get()[1] == Interval{108LL, 109LL});
        }
    }
}

TEST_CASE("[RangeMap] Real scenario", "[2023][2023_5][RangeMap]")
{
    RangeMap rangeMap;
    rangeMap.addSection(3078006360LL, 2182201339LL, 30483272LL);
    rangeMap.addSection(803630304LL, 624445326LL, 165226844LL);
    rangeMap.addSection(2393736333LL, 2745251526LL, 281120946LL);
    rangeMap.addSection(717936870LL, 789672170LL, 85693434LL);
    rangeMap.addSection(598717319LL, 410599330LL, 27984688LL);
    rangeMap.addSection(3999095007LL, 2024628810LL, 157572529LL);
    rangeMap.addSection(3605588191LL, 3026372472LL, 22322803LL);
    rangeMap.addSection(3555659576LL, 2678166775LL, 3396919LL);
    rangeMap.addSection(968857148LL, 438584018LL, 1780307LL);
    rangeMap.addSection(3216227818LL, 2212684611LL, 87459567LL);
    rangeMap.addSection(2302084376LL, 4122083708LL, 91651957LL);
    rangeMap.addSection(970637455LL, 0LL, 188112122LL);
    rangeMap.addSection(507182228LL, 299146916LL, 40412346LL);
    rangeMap.addSection(1372302034LL, 1689624457LL, 202945009LL);
    rangeMap.addSection(1370123632LL, 191483770LL, 2178402LL);
    rangeMap.addSection(324787204LL, 193662172LL, 105484744LL);
    rangeMap.addSection(3116425470LL, 2671328191LL, 6838584LL);
    rangeMap.addSection(626702007LL, 875365604LL, 82756204LL);
    rangeMap.addSection(1575247043LL, 978774853LL, 317322423LL);
    rangeMap.addSection(3134996187LL, 4213735665LL, 81231631LL);
    rangeMap.addSection(2024628810LL, 2681563694LL, 63687832LL);
    rangeMap.addSection(714565222LL, 188112122LL, 3371648LL);
    rangeMap.addSection(547594574LL, 1620884480LL, 51122745LL);
    rangeMap.addSection(3529388087LL, 3374604163LL, 26271489LL);
    rangeMap.addSection(709458211LL, 973428243LL, 5107011LL);
    rangeMap.addSection(2713008276LL, 3985570976LL, 98361735LL);
    rangeMap.addSection(2088316642LL, 3048695275LL, 213767734LL);
    rangeMap.addSection(3627910994LL, 2300144178LL, 371184013LL);
    rangeMap.addSection(2674857279LL, 4083932711LL, 38150997LL);
    rangeMap.addSection(1229789645LL, 958121808LL, 15306435LL);
    rangeMap.addSection(4156667536LL, 3328662676LL, 45941487LL);
    rangeMap.addSection(0LL, 1296097276LL, 324787204LL);
    rangeMap.addSection(3108489632LL, 3320726838LL, 7935838LL);
    rangeMap.addSection(4202609023LL, 3667512001LL, 92358273LL);
    rangeMap.addSection(1352266801LL, 978535254LL, 239599LL);
    rangeMap.addSection(1352506400LL, 1672007225LL, 17617232LL);
    rangeMap.addSection(1245096080LL, 440364325LL, 107170721LL);
    rangeMap.addSection(2811370011LL, 3400875652LL, 266636349LL);
    rangeMap.addSection(430271948LL, 547535046LL, 76910280LL);
    rangeMap.addSection(1158749577LL, 339559262LL, 71040068LL);
    rangeMap.addSection(3559056495LL, 3262463009LL, 46531696LL);
    rangeMap.addSection(3123264054LL, 3308994705LL, 11732133LL);
    rangeMap.addSection(3303687385LL, 3759870274LL, 225700702LL);
    rangeMap.sort();
    Interval const input{
        Interval<int64_t>::createWithSize(195281306LL, 62641412LL)};
    auto const result{rangeMap.convert(input)};
    REQUIRE(input.size() == result.count());
    REQUIRE(result.get().size() == 1);
    CHECK(result.get()[0] == Interval{326406338LL, 389047749LL});
}
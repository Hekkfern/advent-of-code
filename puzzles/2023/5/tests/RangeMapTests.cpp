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

TEST_CASE(
    "[RangeMap] Real scenario with seed range number 7",
    "[2023][2023_5][RangeMap]")
{
    // Stage 1
    RangeMap rangeMap1;
    rangeMap1.addSection(3078006360LL, 2182201339LL, 30483272LL);
    rangeMap1.addSection(803630304LL, 624445326LL, 165226844LL);
    rangeMap1.addSection(2393736333LL, 2745251526LL, 281120946LL);
    rangeMap1.addSection(717936870LL, 789672170LL, 85693434LL);
    rangeMap1.addSection(598717319LL, 410599330LL, 27984688LL);
    rangeMap1.addSection(3999095007LL, 2024628810LL, 157572529LL);
    rangeMap1.addSection(3605588191LL, 3026372472LL, 22322803LL);
    rangeMap1.addSection(3555659576LL, 2678166775LL, 3396919LL);
    rangeMap1.addSection(968857148LL, 438584018LL, 1780307LL);
    rangeMap1.addSection(3216227818LL, 2212684611LL, 87459567LL);
    rangeMap1.addSection(2302084376LL, 4122083708LL, 91651957LL);
    rangeMap1.addSection(970637455LL, 0LL, 188112122LL);
    rangeMap1.addSection(507182228LL, 299146916LL, 40412346LL);
    rangeMap1.addSection(1372302034LL, 1689624457LL, 202945009LL);
    rangeMap1.addSection(1370123632LL, 191483770LL, 2178402LL);
    rangeMap1.addSection(324787204LL, 193662172LL, 105484744LL);
    rangeMap1.addSection(3116425470LL, 2671328191LL, 6838584LL);
    rangeMap1.addSection(626702007LL, 875365604LL, 82756204LL);
    rangeMap1.addSection(1575247043LL, 978774853LL, 317322423LL);
    rangeMap1.addSection(3134996187LL, 4213735665LL, 81231631LL);
    rangeMap1.addSection(2024628810LL, 2681563694LL, 63687832LL);
    rangeMap1.addSection(714565222LL, 188112122LL, 3371648LL);
    rangeMap1.addSection(547594574LL, 1620884480LL, 51122745LL);
    rangeMap1.addSection(3529388087LL, 3374604163LL, 26271489LL);
    rangeMap1.addSection(709458211LL, 973428243LL, 5107011LL);
    rangeMap1.addSection(2713008276LL, 3985570976LL, 98361735LL);
    rangeMap1.addSection(2088316642LL, 3048695275LL, 213767734LL);
    rangeMap1.addSection(3627910994LL, 2300144178LL, 371184013LL);
    rangeMap1.addSection(2674857279LL, 4083932711LL, 38150997LL);
    rangeMap1.addSection(1229789645LL, 958121808LL, 15306435LL);
    rangeMap1.addSection(4156667536LL, 3328662676LL, 45941487LL);
    rangeMap1.addSection(0LL, 1296097276LL, 324787204LL);
    rangeMap1.addSection(3108489632LL, 3320726838LL, 7935838LL);
    rangeMap1.addSection(4202609023LL, 3667512001LL, 92358273LL);
    rangeMap1.addSection(1352266801LL, 978535254LL, 239599LL);
    rangeMap1.addSection(1352506400LL, 1672007225LL, 17617232LL);
    rangeMap1.addSection(1245096080LL, 440364325LL, 107170721LL);
    rangeMap1.addSection(2811370011LL, 3400875652LL, 266636349LL);
    rangeMap1.addSection(430271948LL, 547535046LL, 76910280LL);
    rangeMap1.addSection(1158749577LL, 339559262LL, 71040068LL);
    rangeMap1.addSection(3559056495LL, 3262463009LL, 46531696LL);
    rangeMap1.addSection(3123264054LL, 3308994705LL, 11732133LL);
    rangeMap1.addSection(3303687385LL, 3759870274LL, 225700702LL);
    rangeMap1.sort();
    Interval const input1{
        Interval<int64_t>::createWithSize(2129467491LL, 226193957LL)};
    auto const result1{rangeMap1.convert(input1)};
    REQUIRE(input1.size() == result1.count());
    REQUIRE(result1.get().size() == 4);
    CHECK(result1.get()[0] == Interval{3078006360LL, 3108489631LL});
    CHECK(result1.get()[1] == Interval{3216227818LL, 3303687384LL});
    CHECK(result1.get()[2] == Interval{3627910994LL, 3683428263LL});
    CHECK(result1.get()[3] == Interval{4103933688LL, 4156667535LL});

    // Stage 2
    RangeMap rangeMap2;
    rangeMap2.addSection(2937874770LL, 2957653952LL, 339980892);
    rangeMap2.addSection(1886469734LL, 2145122669LL, 192293654);
    rangeMap2.addSection(3277855662LL, 822424488LL, 19779182);
    rangeMap2.addSection(2622882196LL, 2393077006LL, 314992574);
    rangeMap2.addSection(3449876679LL, 3769116301LL, 525850995);
    rangeMap2.addSection(583550735LL, 842203670LL, 1302918999);
    rangeMap2.addSection(2145755543LL, 345297835LL, 477126653);
    rangeMap2.addSection(2078763388LL, 2890661797LL, 66992155);
    rangeMap2.addSection(2650514LL, 2708069580LL, 182592217);
    rangeMap2.addSection(0LL, 2337416323LL, 2650514);
    rangeMap2.addSection(530540566LL, 2340066837LL, 53010169);
    rangeMap2.addSection(185242731LL, 0LL, 345297835);
    rangeMap2.addSection(3975727674LL, 3449876679LL, 319239622);
    rangeMap2.sort();
    utils::interval::IntervalSet<int64_t> result2;
    for (auto const& item : result1) {
        result2 = result2.join(rangeMap2.convert(item));
    }
    REQUIRE(result1.count() == result2.count());
    REQUIRE(result2.get().size() == 5);
    CHECK(result2.get()[0] == Interval{3058227178LL, 3088710449LL});
    CHECK(result2.get()[1] == Interval{3196448636LL, 3277855661LL});
    CHECK(result2.get()[2] == Interval{3297634844LL, 3303687384LL});
    CHECK(result2.get()[3] == Interval{3784694066LL, 3837427913LL});
    CHECK(result2.get()[4] == Interval{4153761989LL, 4209279258LL});
}
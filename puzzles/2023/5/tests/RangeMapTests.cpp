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
    "[RangeMap] Real scenario for Part 2 with seed range number 7",
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
    rangeMap2.addSection(2937874770LL, 2957653952LL, 339980892LL);
    rangeMap2.addSection(1886469734LL, 2145122669LL, 192293654LL);
    rangeMap2.addSection(3277855662LL, 822424488LL, 19779182LL);
    rangeMap2.addSection(2622882196LL, 2393077006LL, 314992574LL);
    rangeMap2.addSection(3449876679LL, 3769116301LL, 525850995LL);
    rangeMap2.addSection(583550735LL, 842203670LL, 1302918999LL);
    rangeMap2.addSection(2145755543LL, 345297835LL, 477126653LL);
    rangeMap2.addSection(2078763388LL, 2890661797LL, 66992155LL);
    rangeMap2.addSection(2650514LL, 2708069580LL, 182592217LL);
    rangeMap2.addSection(0LL, 2337416323LL, 2650514LL);
    rangeMap2.addSection(530540566LL, 2340066837LL, 53010169LL);
    rangeMap2.addSection(185242731LL, 0LL, 345297835LL);
    rangeMap2.addSection(3975727674LL, 3449876679LL, 319239622LL);
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

    // Stage 3
    RangeMap rangeMap3;
    rangeMap3.addSection(861477134LL, 5168332LL, 68211907LL);
    rangeMap3.addSection(136969509LL, 2229711837LL, 29094441LL);
    rangeMap3.addSection(2823248929LL, 1150509810LL, 118368045LL);
    rangeMap3.addSection(3678888284LL, 3073610919LL, 53498438LL);
    rangeMap3.addSection(3948051821LL, 3682691325LL, 96234592LL);
    rangeMap3.addSection(1302827191LL, 2387840795LL, 504257794LL);
    rangeMap3.addSection(1198743248LL, 1926818347LL, 104083943LL);
    rangeMap3.addSection(1807084985LL, 1104177008LL, 46332802LL);
    rangeMap3.addSection(2143096098LL, 619653304LL, 259805223LL);
    rangeMap3.addSection(2063436946LL, 2385211148LL, 2629647LL);
    rangeMap3.addSection(2066066593LL, 445026117LL, 35759449LL);
    rangeMap3.addSection(358008423LL, 537865723LL, 81787581LL);
    rangeMap3.addSection(621204445LL, 0LL, 5168332LL);
    rangeMap3.addSection(2724438904LL, 1861632296LL, 65186051LL);
    rangeMap3.addSection(1853417787LL, 2258806278LL, 126404870LL);
    rangeMap3.addSection(3933311080LL, 4141091197LL, 14740741LL);
    rangeMap3.addSection(851739278LL, 2892098589LL, 9737856LL);
    rangeMap3.addSection(4044286413LL, 3029323079LL, 44287840LL);
    rangeMap3.addSection(1979822657LL, 1778018007LL, 83614289LL);
    rangeMap3.addSection(2101826042LL, 2084781230LL, 3070511LL);
    rangeMap3.addSection(4088574253LL, 4268409625LL, 26557671LL);
    rangeMap3.addSection(929689041LL, 111346117LL, 211974050LL);
    rangeMap3.addSection(3566310597LL, 4155831938LL, 112577687LL);
    rangeMap3.addSection(439796004LL, 2030902290LL, 53878940LL);
    rangeMap3.addSection(166063950LL, 1490707297LL, 191944473LL);
    rangeMap3.addSection(8760514LL, 888219041LL, 128208995LL);
    rangeMap3.addSection(3794695843LL, 3778925917LL, 57203243LL);
    rangeMap3.addSection(3029323079LL, 3127109357LL, 409045756LL);
    rangeMap3.addSection(2792635116LL, 77722143LL, 30613813LL);
    rangeMap3.addSection(3438368835LL, 4013149435LL, 127941762LL);
    rangeMap3.addSection(3732386722LL, 3620382204LL, 62309121LL);
    rangeMap3.addSection(2402901321LL, 1682651770LL, 95366237LL);
    rangeMap3.addSection(0LL, 879458527LL, 8760514LL);
    rangeMap3.addSection(493674944LL, 2901836445LL, 39780529LL);
    rangeMap3.addSection(3851899086LL, 3536155113LL, 81411994LL);
    rangeMap3.addSection(2498267558LL, 1268877855LL, 221829442LL);
    rangeMap3.addSection(4117947021LL, 3836129160LL, 177020275LL);
    rangeMap3.addSection(2789624955LL, 108335956LL, 3010161LL);
    rangeMap3.addSection(1141663091LL, 480785566LL, 57080157LL);
    rangeMap3.addSection(2104896553LL, 406826572LL, 38199545LL);
    rangeMap3.addSection(533455473LL, 1016428036LL, 87748972LL);
    rangeMap3.addSection(626372777LL, 2087851741LL, 141860096LL);
    rangeMap3.addSection(2720097000LL, 73380239LL, 4341904LL);
    rangeMap3.addSection(4115131924LL, 3617567107LL, 2815097LL);
    rangeMap3.addSection(768232873LL, 323320167LL, 83506405LL);
    rangeMap3.sort();
    utils::interval::IntervalSet<int64_t> result3;
    for (auto const& item : result2) {
        result3 = result3.join(rangeMap3.convert(item));
    }
    REQUIRE(result2.count() == result3.count());
    REQUIRE(result3.get().size() == 8);
    CHECK(result3.get()[3] == Interval{3678888284LL, 3693987814LL});
    CHECK(result3.get()[6] == Interval{4073190512LL, 4088574252LL});
    CHECK(result3.get()[1] == Interval{3199848566LL, 3205901106LL});
    CHECK(result3.get()[0] == Interval{3098662358LL, 3180069383LL});
    CHECK(result3.get()[5] == Interval{3945981872LL, 3948051820LL});
    CHECK(result3.get()[2] == Interval{3566310597LL, 3619757917LL});
    CHECK(result3.get()[4] == Interval{3800463992LL, 3851899085LL});
    CHECK(result3.get()[7] == Interval{4117947021LL, 4119245774LL});

    // Stage 4
    RangeMap rangeMap4;
    rangeMap4.addSection(3846882465LL, 367033980LL, 98093832LL);
    rangeMap4.addSection(1878565977LL, 3292746518LL, 62917983LL);
    rangeMap4.addSection(4255729420LL, 661438934LL, 39237876LL);
    rangeMap4.addSection(469590509LL, 2191298319LL, 301681796LL);
    rangeMap4.addSection(381948234LL, 1999013894LL, 87642275LL);
    rangeMap4.addSection(3688496086LL, 199351627LL, 156562666LL);
    rangeMap4.addSection(1300818753LL, 2086656169LL, 104642150LL);
    rangeMap4.addSection(806539912LL, 2798447654LL, 224466318LL);
    rangeMap4.addSection(1265336919LL, 355914293LL, 11119687LL);
    rangeMap4.addSection(1405460903LL, 1914042148LL, 28882526LL);
    rangeMap4.addSection(2577391070LL, 1942924674LL, 56089220LL);
    rangeMap4.addSection(3680239306LL, 4136990116LL, 8256780LL);
    rangeMap4.addSection(1941483960LL, 700676810LL, 607954854LL);
    rangeMap4.addSection(3845058752LL, 3022913972LL, 1823713LL);
    rangeMap4.addSection(4239658038LL, 1308631664LL, 16071382LL);
    rangeMap4.addSection(2566162195LL, 4254580741LL, 11228875LL);
    rangeMap4.addSection(1671792383LL, 3831845903LL, 10462472LL);
    rangeMap4.addSection(3944976297LL, 3842308375LL, 294681741LL);
    rangeMap4.addSection(3290662499LL, 3160062910LL, 132683608LL);
    rangeMap4.addSection(2549438814LL, 1324703046LL, 16723381LL);
    rangeMap4.addSection(3423346107LL, 1341426427LL, 27108304LL);
    rangeMap4.addSection(1031006230LL, 3355664501LL, 234330689LL);
    rangeMap4.addSection(1276456606LL, 4145246896LL, 24362147LL);
    rangeMap4.addSection(3450454411LL, 54538430LL, 144813197LL);
    rangeMap4.addSection(1682254855LL, 465127812LL, 196311122LL);
    rangeMap4.addSection(54538430LL, 1403802338LL, 272790856LL);
    rangeMap4.addSection(2633480290LL, 2492980115LL, 305467539LL);
    rangeMap4.addSection(3595267608LL, 4169609043LL, 84971698LL);
    rangeMap4.addSection(3242064105LL, 3644614138LL, 48598394LL);
    rangeMap4.addSection(3077581200LL, 4265809616LL, 29157680LL);
    rangeMap4.addSection(771272305LL, 1368534731LL, 35267607LL);
    rangeMap4.addSection(1434343429LL, 1676593194LL, 237448954LL);
    rangeMap4.addSection(327329286LL, 3589995190LL, 54618948LL);
    rangeMap4.addSection(3106738880LL, 3024737685LL, 135325225LL);
    rangeMap4.addSection(2938947829LL, 3693212532LL, 138633371LL);
    rangeMap4.sort();
    utils::interval::IntervalSet<int64_t> result4;
    for (auto const& item : result3) {
        result4 = result4.join(rangeMap4.convert(item));
    }
    REQUIRE(result3.count() == result4.count());
    REQUIRE(result4.get().size() == 13);
    CHECK(result4.get()[0] == Interval{327329286LL, 357092013LL});
    CHECK(result4.get()[1] == Interval{1241652326LL, 1265336918LL});
    CHECK(result4.get()[2] == Interval{1671792383LL, 1682254854LL});
    CHECK(result4.get()[3] == Interval{2938947829LL, 2939723111LL});
    CHECK(result4.get()[4] == Interval{3046199289LL, 3077581199LL});
    CHECK(result4.get()[5] == Interval{3180663553LL, 3242064104LL});
    CHECK(result4.get()[6] == Interval{3276338251LL, 3290662498LL});
    CHECK(result4.get()[7] == Interval{3290662499LL, 3310668972LL});
    CHECK(result4.get()[8] == Interval{3330448155LL, 3336500695LL});
    CHECK(result4.get()[9] == Interval{3944976297LL, 3954567007LL});
    CHECK(result4.get()[10] == Interval{4048649794LL, 4050719742LL});
    CHECK(result4.get()[11] == Interval{4175858434LL, 4191242174LL});
    CHECK(result4.get()[12] == Interval{4220614943LL, 4221913696LL});
}

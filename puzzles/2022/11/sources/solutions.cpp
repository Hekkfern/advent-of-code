#include "solutions.hpp"

#include "Monkey.h"
#include "Operation.h"
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <unordered_map>
#include <utils/StringUtils.hpp>

namespace aoc_2022_11 {

// ---------- Private Methods ----------

Monkey parseMonkey(std::ifstream& fileStream)
{
    std::string line;
    std::smatch regexResult;
    // line 1
    std::getline(fileStream, line);
    constexpr auto PatternLine1{ R"(Monkey (\d+):)" };
    if (!std::regex_match(line, regexResult, std::regex(PatternLine1))) {
        throw std::logic_error(
            "Regex failed in parsing the line 1 of a Monkey description");
    }
    MonkeyId monkeyId{ utils::StringUtils::toNumber<uint8_t>(regexResult[1]) };
    // line 2
    std::getline(fileStream, line);
    constexpr auto PatternLine2{ R"(  Starting items: (.+))" };
    if (!std::regex_match(line, regexResult, std::regex(PatternLine2))) {
        throw std::logic_error(
            "Regex failed in parsing the line 2 of a Monkey description");
    }
    auto itemTexts{ utils::StringUtils::split(regexResult[1]) };
    auto monkeyItems = itemTexts
        | ranges::views::transform([](const std::string& s) {
                           return utils::StringUtils::toNumber<WorryLevel>(s);
                       })
        | ranges::to<std::vector>();
    // line 3
    std::getline(fileStream, line);
    constexpr auto PatternLine3{ R"(  Operation: new = old (.+) (.+))" };
    if (!std::regex_match(line, regexResult, std::regex(PatternLine3))) {
        throw std::logic_error(
            "Regex failed in parsing the line 3 of a Monkey description");
    }
    Operator monkeyOperator{ Operator::ADD };
    std::optional<WorryLevel> monkeyOperand;
    switch (std::string(regexResult[1])[0]) {
    case '+':
        monkeyOperator = Operator::ADD;
        break;
    case '*':
        monkeyOperator = Operator::MULTIPLY;
        break;
    default:
        throw std::logic_error("Invalid operator");
    }
    monkeyOperand = (regexResult[2] == "old")
        ? std::nullopt
        : std::make_optional(
            utils::StringUtils::toNumber<WorryLevel>(regexResult[2]));
    Operation monkeyOperation{ monkeyOperator, monkeyOperand };
    // line 4
    std::getline(fileStream, line);
    constexpr auto PatternLine4{ R"(  Test: divisible by (.+))" };
    if (!std::regex_match(line, regexResult, std::regex(PatternLine4))) {
        throw std::logic_error(
            "Regex failed in parsing the line 4 of a Monkey description");
    }
    WorryLevel monkeyDivisor{ utils::StringUtils::toNumber<WorryLevel>(
        regexResult[1]) };
    // line 5
    std::getline(fileStream, line);
    constexpr auto PatternLine5{ R"(    If true: throw to Monkey (.+))" };
    if (!std::regex_match(line, regexResult, std::regex(PatternLine5))) {
        throw std::logic_error(
            "Regex failed in parsing the line 5 of a Monkey description");
    }
    MonkeyId monkeyTargetTrue{ utils::StringUtils::toNumber<MonkeyId>(
        regexResult[1]) };
    // line 6
    std::getline(fileStream, line);
    constexpr auto PatternLine6{ R"(    If false: throw to Monkey (.+))" };
    if (!std::regex_match(line, regexResult, std::regex(PatternLine6))) {
        throw std::logic_error(
            "Regex failed in parsing the line 6 of a Monkey description");
    }
    MonkeyId monkeyTargetFalse{ utils::StringUtils::toNumber<MonkeyId>(
        regexResult[1]) };
    // generate Monkey
    return Monkey{ monkeyId,          std::move(monkeyOperation),
                   monkeyDivisor,     monkeyTargetTrue,
                   monkeyTargetFalse, std::move(monkeyItems) };
}

std::unordered_map<MonkeyId, Monkey> parseInput(const std::string& filename)
{
    std::ifstream inputFile{ filename };
    std::unordered_map<MonkeyId, Monkey> monkeys;

    std::string line;
    do {
        Monkey monkey{ parseMonkey(inputFile) };
        const MonkeyId id{ monkey.getId() };
        monkeys.emplace(id, std::move(monkey));
    } while (std::getline(inputFile, line));

    return monkeys;
}

// ---------- End of Private Methods ----------

// ---------- Public Methods ----------

std::string solvePart1(const std::string& filename)
{
    std::unordered_map<MonkeyId, Monkey> monkeys{ parseInput(filename) };
}

std::string solvePart2(const std::string& filename)
{
    (void)filename;
    return "";
}

// ---------- End of Public Methods ----------

} // namespace aoc_2022_11
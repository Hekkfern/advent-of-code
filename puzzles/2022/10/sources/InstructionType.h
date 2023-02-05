#pragma once

#include <string>

namespace aoc_2022_10 {

enum class InstructionType { ADDX, NOOP };

constexpr auto AddxInstructionName{ "addx" };
constexpr auto NoopInstructionName{ "noop" };

InstructionType convertInstructionType(const std::string& text)
{
    InstructionType result{};
    if (text == AddxInstructionName) {
        result = InstructionType::ADDX;
    } else {
        result = InstructionType::NOOP;
    }
    return result;
}

std::string convertInstructionType(InstructionType value)
{
    switch (value) {
    case InstructionType::ADDX:
        return AddxInstructionName;
    case InstructionType::NOOP:
        return NoopInstructionName;
    default:
        return "";
    }
}

} // namespace aoc_2022_10

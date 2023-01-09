#include "AocUtils.hpp"

#include <iostream>

namespace utils::AocUtils {

void printPart1Solution(
    const std::string_view solution,
    const std::chrono::microseconds execTime)
{
    std::cout << "-----Part 1-----\nValue: " << solution
              << "\nExecution time: " << execTime.count() << " us" << std::endl;
}

void printPart2Solution(
    const std::string_view solution,
    const std::chrono::microseconds execTime)
{
    std::cout << "-----Part 2-----\nValue: " << solution
              << "\nExecution time: " << execTime.count() << " us" << std::endl;
}

} // namespace utils::AocUtils

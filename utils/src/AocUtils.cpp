#include "AocUtils.hpp"

#include <iostream>

namespace utils::AocUtils {

void printPart1Solution(
    const std::string_view solution,
    std::chrono::nanoseconds execTime)
{
    std::cout << "-----Part 1-----\nValue: " << solution
              << "\nExecution time: " << execTime.count() << " ns" << std::endl;
}

void printPart2Solution(
    const std::string_view solution,
    std::chrono::nanoseconds execTime)
{
    std::cout << "-----Part 1-----\nValue: " << solution
              << "\nExecution time: " << execTime.count() << " ns" << std::endl;
}

} // namespace utils::AocUtils

#include "AocUtils.hpp"

#include <iostream>

namespace utils::AocUtils {

void printPart1Solution(
    const std::string_view solution,
    const std::chrono::milliseconds execTime)
{
    std::cout << "-----Part 1-----\nValue: " << solution
              << "\nExecution time: " << execTime.count() << " ms" << std::endl;
}

void printPart2Solution(
    const std::string_view solution,
    const std::chrono::milliseconds execTime)
{
    std::cout << "-----Part 2-----\nValue: " << solution
              << "\nExecution time: " << execTime.count() << " ms" << std::endl;
}

} // namespace utils::AocUtils

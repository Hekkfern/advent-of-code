#include "TimeUtils.hpp"

namespace utils::TimeUtils {

std::chrono::duration<std::chrono::seconds> calculateExecutionTime(
    std::function<std::string()> action)
{
    auto start = std::chrono::high_resolution_clock::now();
    action();
    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}

} // namespace utils::TimeUtils

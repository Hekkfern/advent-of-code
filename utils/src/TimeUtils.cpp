#include "TimeUtils.hpp"

namespace utils::TimeUtils {

std::chrono::nanoseconds calculateExecutionTime(
    std::function<void()>&& action)
{
    const auto start = std::chrono::high_resolution_clock::now();
    action();
    const auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}

} // namespace utils::TimeUtils

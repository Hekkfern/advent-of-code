#include "TimeUtils.hpp"

namespace utils::TimeUtils {

std::chrono::milliseconds calculateExecutionTime(std::function<void()>&& action)
{
    const auto start = std::chrono::high_resolution_clock::now();
    action();
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

} // namespace utils::TimeUtils

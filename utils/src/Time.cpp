#include "Time.hpp"

namespace utils::time {

std::chrono::microseconds calculateExecutionTime(std::function<void()>&& action)
{
    const auto start = std::chrono::high_resolution_clock::now();
    action();
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

} // namespace utils::time

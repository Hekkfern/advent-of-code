#include "Time.hpp"

namespace utils::time {

std::chrono::microseconds calculateExecutionTime(std::function<void()>&& action)
{
    auto const start = std::chrono::high_resolution_clock::now();
    action();
    auto const end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

} // namespace utils::time

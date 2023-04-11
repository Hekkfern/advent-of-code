#pragma once

#include <chrono>
#include <functional>

namespace utils::time {

[[nodiscard]] std::chrono::microseconds calculateExecutionTime(
    std::function<void()>&& action);

}

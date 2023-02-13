#pragma once

#include <chrono>
#include <functional>

namespace utils::time {

std::chrono::microseconds calculateExecutionTime(std::function<void()>&& action);

}

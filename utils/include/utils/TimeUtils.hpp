#pragma once

#include <chrono>
#include <functional>

namespace utils::TimeUtils {

std::chrono::microseconds calculateExecutionTime(std::function<void()>&& action);

}
